#ifndef MQTTSUBSCRIBERCLIENT_H
#define MQTTSUBSCRIBERCLIENT_H

#include <QObject>
#include <mosquittopp.h>

#define DATA_SIZE 5

using namespace mosqpp;

/***
 * This class goes into an infinte loop upon instantiation. Therefore it should not be intantiated
 * in the main gui thread. It should be instantiated inside a secondary thread.
 ***/

class MqttSubscriberClient : public QObject, public mosquittopp
{
    Q_OBJECT
public:
    explicit MqttSubscriberClient(QObject *parent = nullptr, const char *id = NULL, bool clean_session = true);
    ~MqttSubscriberClient();

    int *values();
    void start_loop();

    void on_message(const struct mosquitto_message *msg) override;
private:
    /* m_values[0] - current/temperature */
    /* m_values[0] - current/pressure */
    /* m_values[0] - current/humidity */
    /* m_values[0] - current/volume */
    /* m_values[0] - current/height */
    int m_values[DATA_SIZE];
};

#endif // MQTTSUBSCRIBERCLIENT_H
