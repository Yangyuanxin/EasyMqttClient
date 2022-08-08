#include "EasyMqtt.h"

int Index = 0;
pthread_mutex_t Mutex;
struct TopicHandler_t
{
    const char *Topic;
    void (*CallBack)(const char *Topic,char* Data,unsigned short Len);
};

struct TopicHandler_t Table[MAX_TOPIC];

EasyMqttClient_t *EasyMqttInit(EasyMqttAttr_t *Attr)
{
    EasyMqttClient_t *Client = NULL;
    Client = mqtt_lease();
    if(Client == NULL) 
    {
        return Client;
    }
    mqtt_set_host(Client, Attr->Url);
    mqtt_set_port(Client, Attr->Port);
    mqtt_set_client_id(Client, Attr->ClientId);
    mqtt_set_user_name(Client, Attr->Username);
    mqtt_set_password(Client, Attr->Password);
    mqtt_set_clean_session(Client, 1);
    pthread_mutex_init(&Mutex,NULL);
    return Client;
}

int EasyMqttUnInit(EasyMqttClient_t *Client)
{
    Index = 0;
    memset(Table, 0, sizeof(Table));
    pthread_mutex_destroy(&Mutex);
    return mqtt_release(Client);
}

int EasyMqttConnect(EasyMqttClient_t *Client)
{
    return mqtt_connect(Client);
}

int EasyMqttDisConnect(EasyMqttClient_t *Client)
{
    return mqtt_disconnect(Client);
}

static void TopicHandlerCallBack(void* client, message_data_t* Msg)
{
    (void)client;
    int Index = 0;
    char *Topic = Msg->topic_name;
    unsigned short Len = Msg->message->payloadlen;
    char *Data  = (char *)Msg->message->payload;
    pthread_mutex_lock(&Mutex);
    for(Index = 0; Index < sizeof(Table)/sizeof(Table[0]); Index++)
    {
        if(0 == strcmp(Msg->topic_name,Table[Index].Topic))
        {
            Table[Index].CallBack(Topic,Data,Len);
            break;
        }
    }
    pthread_mutex_unlock(&Mutex);
}

int EasyMqttSubscribe(EasyMqttClient_t *Client, const char *Topic, enum EasyMqttQos_t Qos, 
                    void (*Cb)(const char *Topic, char* Data, unsigned short Len))
{
    if(Index > MAX_TOPIC-1)
    {
        printf("Exceeds the maximum number of topics set:%d!\n", Index);
        return -1;
    }
    Table[Index].Topic = Topic;
    Table[Index].CallBack = Cb;
    Index++;
    return mqtt_subscribe(Client, Topic, (mqtt_qos_t)Qos, TopicHandlerCallBack);
}

int EasyMqttUnsubscribe(EasyMqttClient_t *Client, const char *Topic)
{
    return mqtt_unsubscribe(Client, Topic);
}

int EasyMqttPublish(EasyMqttClient_t *Client, const char *Topic, enum EasyMqttQos_t Qos, char *Data, unsigned short Len)
{
    mqtt_message_t Msg;
    Msg.payload = Data;
    Msg.payloadlen = Len;
    Msg.qos = (mqtt_qos_t)Qos;
    return mqtt_publish(Client, Topic, &Msg);
}


#ifdef EASY_MQTT_TEST
const char *PubTopic[] = 
{
    "topic/EasyMqtt/pub/0123456789/0000",
    "topic/EasyMqtt/pub/0123456789/0001",
    "topic/EasyMqtt/pub/0123456789/0002",
    "topic/EasyMqtt/pub/0123456789/0003",
    "topic/EasyMqtt/pub/0123456789/0004",
};

static void TopicHandler0(const char *Topic, char *Data, unsigned short Len)
{
    printf("\n===TopicHandler0===");
    printf("Topic : %s\n", Topic);
    printf("Msg   : %s\n", Data);
    printf("Len   : %d\n", Len);
}

static void TopicHandler1(const char *Topic, char *Data, unsigned short Len)
{
    printf("\n===TopicHandler1===");
    printf("Topic : %s\n", Topic);
    printf("Msg   : %s\n", Data);
    printf("Len   : %d\n", Len);
}

static void TopicHandler2(const char *Topic, char *Data, unsigned short Len)
{
    printf("\n===TopicHandler2===");
    printf("Topic : %s\n", Topic);
    printf("Msg   : %s\n", Data);
    printf("Len   : %d\n", Len);
}

static void TopicHandler3(const char *Topic, char *Data, unsigned short Len)
{
    printf("\n===TopicHandler3===");
    printf("Topic : %s\n", Topic);
    printf("Msg   : %s\n", Data);
    printf("Len   : %d\n", Len);
}

static void TopicHandler4(const char *Topic, char *Data, unsigned short Len)
{
    printf("\n===TopicHandler4===");
    printf("Topic : %s\n", Topic);
    printf("Msg   : %s\n", Data);
    printf("Len   : %d\n", Len);
}

struct MqttTableTest_t
{
    char *SubTopic;
    void (*Cb)(const char *Topic,char* Data,unsigned short Len);
};

struct MqttTableTest_t MqttTable[] = 
{
    {
        "topic/EasyMqtt/sub/0123456789/0000",
        TopicHandler0
    },
    {
        "topic/EasyMqtt/sub/0123456789/0001",
        TopicHandler1
    },
    {
        "topic/EasyMqtt/sub/0123456789/0002",
        TopicHandler2
    },
    {
        "topic/EasyMqtt/sub/0123456789/003",
        TopicHandler3
    },
    {
        "topic/EasyMqtt/sub/0123456789/004",
        TopicHandler4
    }
};

void EasyMqttTest(void)
{
    int Ret = -1;
    int Index = 0;
    char data[256] = "Hello EasyMqtt";
    
    EasyMqttAttr_t Attr = {
        .Url      = "192.168.4.248",
        .Port     = "30157",
        .ClientId = "EasyMqttMqtt",
        .Username = "EasyMqtt",
        .Password = "123456"
    };
    
    printf("Url      %s\n", Attr.Url);
    printf("Port     %s\n", Attr.Port);
    printf("ClientId %s\n", Attr.ClientId);
    printf("Username %s\n", Attr.Username);
    printf("Password %s\n", Attr.Password);
    
    EasyMqttClient_t *Client = NULL;
    Client = EasyMqttInit(&Attr);
    if(Client == NULL) 
    {
        printf("EasyMqttInit failed!\n");
        return ;
    }
    
    Ret = EasyMqttConnect(Client);
    if(Ret < 0)
    {
       printf("EasyMqttConnect failed!\n");
       return ;
    }
    
    printf("\n===Add sub topic to IotTableSub===\n");
    for(Index = 0 ; Index < sizeof(MqttTable)/sizeof(MqttTable[0]) ; Index++)
    {
        printf("EasyMqttSubscribe %d Topic:%s\n",Index,MqttTable[Index].SubTopic);
        EasyMqttSubscribe(Client,MqttTable[Index].SubTopic, EASY_QOS0,MqttTable[Index].Cb);
    }
    
    while(1) 
    {
        EasyMqttPublish(Client, PubTopic[0], EASY_QOS0, data, strlen(data));
        EasyMqttPublish(Client, PubTopic[1], EASY_QOS0, data, strlen(data));
        sleep(2);
        break;
    }

    for(Index = 0 ; Index < sizeof(MqttTable)/sizeof(MqttTable[0]) ; Index++)
    {
        printf("EasyMqttSubscribe %d Topic:%s",Index,MqttTable[Index].SubTopic);
        EasyMqttUnsubscribe(Client,MqttTable[Index].SubTopic);
    }
    
    Ret = EasyMqttDisConnect(Client);
    if(Ret < 0)
    {
        printf("EasyMqttDisConnect failed!\n");
       return ;
    }
    printf("EasyMqttDisConnect success!\n");
    
    Ret = EasyMqttUnInit(Client);
    if(Ret < 0)
    {
       printf("EasyMqttUnInit failed!\n");
       return ;
    }
    printf("EasyMqttUnInit success!\n");
}
#endif
