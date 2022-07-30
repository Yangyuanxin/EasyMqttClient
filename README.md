# EasyMqttClient
这是一个基于杰杰大佬所封装的mqttclient精简调用接口版本，进一步降低了使用者的门槛
(Github: https://github.com/jiejieTop/mqttclient)

使用起来非常简单，只有7个接口，分别是：
```
//MQTT初始化
EasyMqttClient_t *EasyMqttInit(EasyMqttAttr_t *Attr);
//MQTT反初始化
int EasyMqttUnInit(EasyMqttClient_t *Client);
//MQTT连接
int EasyMqttConnect(EasyMqttClient_t *Client);
//MQTT断开连接
int EasyMqttDisConnect(EasyMqttClient_t *Client);
//MQTT主题订阅
int EasyMqttSubscribe(EasyMqttClient_t *Client, const char *Topic, enum EasyMqttQos_t Qos, 
                      void (*Cb)(const char *Topic,char* Data,unsigned short Len));
//MQTT主题解除订阅
int EasyMqttUnsubscribe(EasyMqttClient_t *Client, const char *Topic);
//MQTT主题发布
int EasyMqttPublish(EasyMqttClient_t *Client, const char *Topic, enum EasyMqttQos_t Qos, char *Data, unsigned short Len);
```
具体的使用方式可以参考测试样例: 
```
void EasyMqttTest(void);
```
