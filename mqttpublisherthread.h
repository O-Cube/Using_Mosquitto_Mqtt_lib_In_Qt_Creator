#ifndef MQTTPUBLISHERTHREAD_H
#define MQTTPUBLISHERTHREAD_H

#include <QThread>
#define BLOCK_SIZE 5

class MqttPublisherClient;

class MqttPublisherThread : public QThread
{
    Q_OBJECT
public:
    explicit MqttPublisherThread(QObject *parent = nullptr);
    ~MqttPublisherThread();
protected:
    void run() override;
private:
    MqttPublisherClient *pub_client;
    char str_value[BLOCK_SIZE];
};

#endif // MQTTPUBLISHERTHREAD_H
