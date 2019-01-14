/*******************************************************************************
 * Copyright (c) 2012, 2017 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution. 
 *
 * The Eclipse Public License is available at 
 *   http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at 
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial contribution
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cJSON.h"
#include "MQTTClient.h"
#include <sys/time.h>
#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "demo"  // 整个系统唯一 
#define PUB_NODELIST       CLIENTID"/get/request/esdk/plcNodeList"
#define SUB_NODELIST       "esdk/get/response/"CLIENTID"/plcNodeList"
#define PAYLOAD_NODELIST     "{\"token\": \"12345\",\"timestamp\": \"2018-03-28T08:33:43Z\",\"body\":{\"mac\":\"\"}}"
#define QOS         1
#define TIMEOUT     10000L

volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;

    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("\n");
	
    cJSON *json = cJSON_Parse(message->payload);
	cJSON *body = cJSON_GetObjectItem(json,"body");
	if(body != NULL){
		if(body->type == cJSON_Array)
		{
			int len = cJSON_GetArraySize(body);
			printf("%d nodes:\n", len);			
			printf("MAC\tSTATE\tIP\n");
			for(i=0;i<len;i++){
				cJSON *tmac = cJSON_GetArrayItem(body,i);
				printf("%s\t%s\t%s\n",cJSON_GetStringValue(cJSON_GetObjectItem(tmac,"mac"))
					,cJSON_GetStringValue(cJSON_GetObjectItem(tmac,"state"))
					,cJSON_GetStringValue(cJSON_GetObjectItem(tmac,"ip"))
					);				
			}
		}		
	}

    putchar('\n');
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

void time_test(int long timeout)
{
    struct timeval now, res;
    struct timeval start;
    int long elapsed=0;
    gettimeofday(&start, NULL);
    printf("start.tv_sec=%ld,start.tv_usec=%ld\r\n",start.tv_sec,start.tv_usec);
	while(1)
	{
	
		printf("start.tv_sec=%ld,now.tv_sec=%ld\r\n",start.tv_sec,now.tv_sec);
		gettimeofday(&now, NULL);
		timersub(&now, &start, &res);
		elapsed=(res.tv_sec)*1000 + (res.tv_usec)/1000;
		
		printf("elapsed=%ld,timeout=%ld\r\n",elapsed,timeout);
		if (elapsed >= timeout)
			break;
	}
}
int main(int argc, char* argv[])
{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;	
    MQTTClient_message pubmsg = MQTTClient_message_initializer;	
    MQTTClient_deliveryToken token = 0;
	cJSON *json ; 
	cJSON *mac ; 
	char tokenstr[12];
	
	time_t t ;
    int rc;
    int ch;
    
    //time_test(10000);
    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(EXIT_FAILURE);
    }
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n",
		SUB_NODELIST, CLIENTID, QOS);
    MQTTClient_subscribe(client, SUB_NODELIST, QOS);

	mac = cJSON_CreateObject();
	cJSON_AddStringToObject(mac,"mac","");	

	json = cJSON_CreateObject();
	sprintf(tokenstr,"%d",token);
	cJSON_AddStringToObject(json,"token",tokenstr);
	time(&t);
	cJSON_AddStringToObject(json,"timestamp",ctime(&t));
	cJSON_AddItemToObject(json,"body", mac);

    pubmsg.payload = cJSON_Print(json);;
    pubmsg.payloadlen = (int)strlen(pubmsg.payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, PUB_NODELIST, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of \n%s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), (char*)pubmsg.payload, PUB_NODELIST, CLIENTID);
	cJSON_Delete(json);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("*****************MQTTClient_waitForCompletion=%d\n", rc);
    printf("Message with delivery token %d delivered\n", token);
	usleep(50000);
    MQTTClient_unsubscribe(client, SUB_NODELIST);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}
