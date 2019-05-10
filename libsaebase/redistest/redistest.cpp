// redistest.cpp : �������̨Ӧ�ó������ڵ㡣
//

// test2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../base/redis/include/hiredis/hiredis.h"
#pragma  comment(lib,"../../base/redis/lib/windows/debug/hiredis.lib")
#pragma  comment(lib,"ws2_32.lib")
using namespace std;

#if _MSC_VER
#define snprintf _snprintf
#endif

int main(int argc, char **argv) {

	WSADATA wsaData;
	int nRet;
	if((nRet = WSAStartup(MAKEWORD(2,2),&wsaData)) != 0){
		printf("WSAStartup failed\n");
		exit(0);
	}
	unsigned int j, isunix = 0;
	redisContext *c;
	redisReply *reply;
	const char *hostname = (argc > 1) ? argv[1] : "210.21.48.75";

	if (argc > 2) {
		if (*argv[2] == 'u' || *argv[2] == 'U') {
			isunix = 1;
			/* in this case, host is the path to the unix socket */
			printf("Will connect to unix socket @%s\n", hostname);
		}
	}

	int port = (argc > 2) ? atoi(argv[2]) : 6379;

	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	if (isunix) {
		c = redisConnectUnixWithTimeout(hostname, timeout);
	} else {
		c = redisConnectWithTimeout(hostname, port, timeout);
	}
	if (c == NULL || c->err) {
		if (c) {
			printf("Connection error: %s\n", c->errstr);
			redisFree(c);
		} else {
			printf("Connection error: can't allocate redis context\n");
		}
		exit(1);
	}

	/* PING server */
	reply = (redisReply *)redisCommand(c,"PING");
	printf("PING: %s\n", reply->str);
	freeReplyObject(reply);

	/* Set a key */
	reply =  (redisReply *)redisCommand(c,"SET %s %s", "foo", "hello world");
	printf("SET: %s\n", reply->str);
	freeReplyObject(reply);

	/* Set a key using binary safe API */
	reply =  (redisReply *)redisCommand(c,"SET %b %b", "bar", (size_t) 3, "hello", (size_t) 5);
	printf("SET (binary API): %s\n", reply->str);
	freeReplyObject(reply);

	/* Try a GET and two INCR */
	reply =  (redisReply *)redisCommand(c,"GET foo");
	printf("GET foo: %s\n", reply->str);
	freeReplyObject(reply);

	reply =  (redisReply *)redisCommand(c,"INCR counter");
	printf("INCR counter: %lld\n", reply->integer);
	freeReplyObject(reply);
	/* again ... */
	reply =  (redisReply *)redisCommand(c,"INCR counter");
	printf("INCR counter: %lld\n", reply->integer);
	freeReplyObject(reply);

	/* Create a list of numbers, from 0 to 9 */
	reply =  (redisReply *)redisCommand(c,"DEL mylist");
	freeReplyObject(reply);
	for (j = 0; j < 10; j++) {
		char buf[64];

		snprintf(buf,64,"%u",j);
		reply =  (redisReply *)redisCommand(c,"LPUSH mylist element-%s", buf);
		freeReplyObject(reply);
	}

	/* Let's check what we have inside the list */
	reply =  (redisReply *)redisCommand(c,"LRANGE mylist 0 -1");
	if (reply->type == REDIS_REPLY_ARRAY) {
		for (j = 0; j < reply->elements; j++) {
			printf("%u) %s\n", j, reply->element[j]->str);
		}
	}
	freeReplyObject(reply);

	/* Disconnects and frees the context */
	redisFree(c);

	return 0;
}


// int main()
// {
// 	WSADATA wsaData;
// 	int nRet;
// 	if((nRet = WSAStartup(MAKEWORD(2,2),&wsaData)) != 0){
// 		printf("WSAStartup failed\n");
// 		exit(0);
// 	}
// 	redisContext *conn  = redisConnect("210.21.48.75",6379);
// 	if(conn != NULL && conn->err)
// 	{
// 		printf("connection error: %s\n",conn->errstr);
// 		return 0;
// 	}
// 	redisReply *reply = (redisReply*)redisCommand(conn,"set foo 1234");
// 	freeReplyObject(reply);
// 
// 	reply = (redisReply *)redisCommand(conn,"get foo");
// 	printf("%s\n",reply->str);
// 	freeReplyObject(reply);
// 
// 	redisFree(conn);
// 	return 0;
// }

