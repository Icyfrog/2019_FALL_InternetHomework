#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis.h>
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
     printf("AUTH: %s\n", reply->str);
     freeReplyObject(reply);

     /* Set */
     reply = redisCommand(conn,"SET %s %s", keyUrl, valueUrl);
     printf("SET: %s\n", reply->str);
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
     printf("AUTH: %s\n", reply->str);
     freeReplyObject(reply);
     
     /* Get */
     reply = redisCommand(conn,"GET %s", keyUrl);
     strcpy(valueUrl, reply->str);
     printf("GET URL: %s\n", reply->str);
     freeReplyObject(reply);

     /* Disconnects and frees the context */
     redisFree(conn);
}


int main(int argc, char **argv) {
    char* t1 = "key: long URL";
    char* t2 = "value: the short URL";
    char t3[50];
    redisContext *conn;
    redisReply *reply;
    setRedis(conn, reply, "127.0.0.1", 6379, "1", t1, t2);
    getRedis(conn, reply, "127.0.0.1", 6379, "1", t1, t3);
    printf("short url: %s", t3);
    return 0;
}
