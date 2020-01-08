# include "net.h"
# include <time.h>
sbuf_t sbuf;
char * host;
char * port;
int rw;
void * thread(void * vargp){
    int kk;
    pthread_detach(pthread_self());
    rio_t rio;
    char buf[MAXLINE];
    while(1){
        kk = sbuf_remove(&sbuf);
	int clientfd = open_clientfd(host,port);
	rio_readinitb(&rio,clientfd);
    	int n;
    	if(rw == 0){
            // read
	    memcpy(buf,"0\n",2);
            rio_writen(clientfd,buf,strlen(buf));
	    if(kk%3 == 0)
		memcpy(buf,"yqc\n",LLL);
	    else if (kk%3 == 1)
		memcpy(buf,"yxh\n",LLL);
	    else memcpy(buf,"yx\n",LLL);
	    rio_writen(clientfd,buf,LLL);
	    if((n=rio_readlineb(&rio,buf,strlen(buf)))!=0){
	      printf("client received: %s\n",buf);
	    }
	    else
	      printf("client received nothing\n");
        }
        else{
            // write
	    memcpy(buf,"1\n",2);
            rio_writen(clientfd,buf,strlen(buf));
	    // TODO: input shorturl here
	    memcpy(buf,"longurl\n",LLL);
	    rio_writen(clientfd,buf,LLL);
	    //printf("client has written to server\n");
        }
	close(clientfd);
    }
    pthread_exit(NULL);
    return NULL;
}
int main (int argc, char ** argv){
    int t1 = time(NULL);
    int clientfd;
    char buf[MAXLINE];
    rio_t rio;
    if(argc!=6){
        fprintf(stderr,"usage: %s <host> <port> <read-or-write> <threads> <thread-pool-size>\n",argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];
    rw = argv[3][0]-'0';
    int threads = atoi(argv[4]);
    int poolsize = atoi(argv[5]);
    sbuf_init(&sbuf,poolsize);
    pthread_t tid;
    int i = 0;
    for(;i<poolsize;i++){
        pthread_create(&tid,NULL,thread,NULL);
    }
    i++;
    while(i < threads){
	sbuf_insert(&sbuf,i++);
	if(i%100 == 0)
	    printf("%d requests finished\n",i);
    }
    int t2 = time(NULL);
    printf("time spent: %d second\n",t2 - t1);


    exit(0);
}
