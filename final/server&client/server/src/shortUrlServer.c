# include "net.h"
# include "hiredis.h"
sbuf_t sbuf;
void setRedis(redisContext *conn, redisReply *reply, char *hostname,  int port, char *password, char* keyUrl, char* valueUrl) {
     unsigned int j;
     struct timeval timeout = { 1, 500000 }; // 1.5 seconds
     conn = redisConnectWithTimeout(hostname, port, timeout);
     if (conn == NULL || conn->err) {
		if (conn) {
             printf("Connection error: %s\n", conn->errstr);
             redisFree(conn);
		} else {
             printf("Connection error: can't allocate redis context\n");
		}
     exit(1);
     }
     /* AUTH */
     reply = redisCommand(conn, "AUTH %s", password);
     // printf("AUTH: %s\n", reply->str);
     freeReplyObject(reply);

     /* Set */
     reply = redisCommand(conn,"SET %s %s", keyUrl, valueUrl);
     // printf("SET: %s\n", reply->str);
     freeReplyObject(reply);
     
     /* Disconnects and frees the context */
     redisFree(conn);
}
void getRedis(redisContext *conn, redisReply *reply, char *hostname,  int port, char *password, char* keyUrl, char* valueUrl) {
     unsigned int j;
     struct timeval timeout = { 1, 500000 }; // 1.5 seconds
     conn = redisConnectWithTimeout(hostname, port, timeout);
     if (conn == NULL || conn->err) {
		if (conn) {
             printf("Connection error: %s\n", conn->errstr);
             redisFree(conn);
		} else {
             printf("Connection error: can't allocate redis context\n");
		}
     exit(1);
     }
     /* AUTH */
     reply = redisCommand(conn, "AUTH %s", password);
     if(!reply || !reply->str){
	 if(reply){
	   freeReplyObject(reply);
	 }
	 redisFree(conn);
         printf("server couldn't get authorization\n");
	 valueUrl[0] = '\0';
	 return;
     }
     printf("AUTH: %s\n", reply->str);
     // reeReplyObject(reply);
     /* Get */
     reply = redisCommand(conn,"GET %s", keyUrl);
     if(!reply || !reply->str){
	 if(reply){
	   freeReplyObject(reply);
	 }
	 redisFree(conn);
         printf("server couldn't find any result\n");
	 valueUrl[0] = '\0';
	 return;
     }
     strcpy(valueUrl, reply->str);
     printf("GET URL: %s\n", reply->str);
     freeReplyObject(reply);

     /* Disconnects and frees the context */
     redisFree(conn);
}
void dealWithLongUrl (int connfd) 
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;
    rio_readinitb(&rio,connfd);
    redisContext *conn;
    redisReply *reply;
    char longUrl[LLL];
    char shortUrl[LLL];
    int i;
    if((n = rio_readlineb(&rio,buf,LLL))!= 0){
        i = buf[0]-'0';
	// if i == 0 read else write
	printf("server received type %d request\n",i);
	if(i!=0 && i!=1){
	  printf("server received invalid input\n");
	  return;
	}
    }
    if((n = rio_readlineb(&rio,buf,LLL))!= 0){
	printf("server received :%s\n",buf);
	for(int i = 0; i < n;i++){
	  if(buf[i] == '\n')
	  {
	    buf[i] = '\0';
	    break;
	  }
	}
	buf[n] = '\0';
	if(i == 0){
	    getRedis(conn,reply,"35.171.129.219",6379,"1",buf,longUrl);
	    // longUrl[0]='\0';
	    if(strlen(longUrl) == 0){
	        rio_writen(connfd,"could not find any result\n",27);
		return;
	    }
	    rio_writen(connfd,longUrl,strlen(longUrl));
	}
	else{
	    // for simplicity transform each of 3 chars into 2 chars
	    char ch0,ch1,ch2;
	    char res0,res1;
	    int size = strlen(buf);
	    int cur = 0;
	    int rescnt = 0;
	    while(cur+2 <= size){
	        ch0 = buf[cur];
		ch1 = buf[cur+1];
		ch2 = buf[cur+2];
		res0 = ((ch0-'0')<<3) + ((ch1-'0')>>2);
		res1 = ((ch1-'0')<<5) + ((ch2-'0')<<1);
		shortUrl[rescnt++] = res0;
		shortUrl[rescnt++] = res1;
		cur += 3;
	    }   
	    if(cur == size - 1){
		ch0 = buf[cur];
		ch1 = buf[cur+1];
	        res0 = ((ch0-'0')<<3) + ((ch1-'0')>>2);
		res1 = ((ch1-'0')<<5);
		shortUrl[rescnt++] = res0;
		shortUrl[rescnt++] = res1;
	    }
	    else if(cur == size){
	        ch0 = buf[cur];
		res0 = ((ch0-'0')<<3);
		shortUrl[rescnt++] = res0;
	    }
	    // transformation done
	    shortUrl[rescnt++] = '\n';
	    shortUrl[rescnt++] = '\0';
	    setRedis(conn,reply,"35.171.129.219",6379,"1",shortUrl,buf);
	    rio_writen(connfd,shortUrl,rescnt);
	}
        
    }
}
void * thread (void *vargp){
    pthread_detach(pthread_self());
    while(1){
	int connfd = sbuf_remove(&sbuf);
        dealWithLongUrl(connfd);
        close(connfd);
    }
    pthread_exit(NULL);
    return NULL;
}
int main(int argc,char ** argv){
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;
    // char client_hostname[MAXLINE],client_port[MAXLINE];
    if(argc !=3){
        fprintf(stderr,"usage: %s <port> <pool_size>\n",argv[0]);
        exit(0);
    }
    listenfd = open_listenfd(argv[1]);
    int poolsize = atoi(argv[2]);
    sbuf_init(&sbuf,poolsize);
    for(int i = 0; i<poolsize;i++){
      pthread_create(&tid,NULL,thread,NULL);
    }

    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd,(SA *)&clientaddr,&clientlen);
	sbuf_insert(&sbuf,connfd);
    }
    exit(0);
}
