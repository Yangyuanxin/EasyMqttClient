#ifndef _EASY_MQTT_H_
#define _EASY_MQTT_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "Common.h"
#include "mqttclient.h"

#define EASY_MQTT_TEST
#define MAX_TOPIC       64

struct TopicHandler_t
{
    const char *Topic;
    void (*CallBack)(const char *Topic,char* Data,unsigned short Len);
};
typedef mqtt_client_t EasyMqttClient_t;

enum EasyMqttQos_t
{
    EASY_QOS0 = 0,
    EASY_QOS1 = 1,
    EASY_QOS2 = 2
};

typedef struct EasyMqttAttr
{
    char *Url;
    char *Port;
    char *ClientId;
    char *Username;
    char *Password;
}EasyMqttAttr_t;

EasyMqttClient_t *EasyMqttInit(EasyMqttAttr_t *Attr);
int EasyMqttUnInit(EasyMqttClient_t *Client);
int EasyMqttConnect(EasyMqttClient_t *Client);
int EasyMqttDisConnect(EasyMqttClient_t *Client);
int EasyMqttSubscribe(EasyMqttClient_t *Client, const char *Topic, enum EasyMqttQos_t Qos, 
                    void (*Cb)(const char *Topic,char* Data,unsigned short Len));
int EasyMqttUnsubscribe(EasyMqttClient_t *Client, const char *Topic);
int EasyMqttPublish(EasyMqttClient_t *Client, const char *Topic, enum EasyMqttQos_t Qos, char *Data, unsigned short Len);

#ifdef EASY_MQTT_TEST
void EasyMqttTest(void);
#endif 
#ifdef __cplusplus
}
#endif

#endif  //ifndef _EASY_MQTT_H_

