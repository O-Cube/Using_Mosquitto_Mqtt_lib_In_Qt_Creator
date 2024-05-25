#ifndef MQTTSUBSCRIBERTHREAD_H
#define MQTTSUBSCRIBERTHREAD_H

#include <QThread>

class MqttSubscriberClient;

class MqttSubscriberThread : public QThread
{
    Q_OBJECT
public:
    explicit MqttSubscriberThread(QObject *parent = nullptr);
    ~MqttSubscriberThread();

    int *get_values() const;

protected:
    void run() override;
private:
    MqttSubscriberClient *sub_client;
};

#endif // MQTTSUBSCRIBERTHREAD_H
