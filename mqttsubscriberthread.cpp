#include "mqttsubscriberthread.h"

#include "mqttsubscriberclient.h"

MqttSubscriberThread::MqttSubscriberThread(QObject *parent)
    : QThread(parent)
    , sub_client(new MqttSubscriberClient(this))
{}

MqttSubscriberThread::~MqttSubscriberThread()
{
    delete sub_client;
}

int *MqttSubscriberThread::get_values() const
{
    return sub_client->values();
}

void MqttSubscriberThread::run()
{
    /* function does not return */
    sub_client->start_loop();
}
