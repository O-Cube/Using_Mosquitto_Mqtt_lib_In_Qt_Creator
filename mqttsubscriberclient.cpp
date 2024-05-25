#include "mqttsubscriberclient.h"

#include <cstdlib>
#include <cstdio>
#include <string>
#include <cstring>
#include <QDebug>

const char *host = "127.0.0.1";
int port = 60001;
const char *username = "Obed";
const char *password = "password";

/* subscribe to all 5 topics asssociated with current/ */
const char *topic = "current/+";

MqttSubscriberClient::MqttSubscriberClient(QObject *parent, const char *id, bool clean_session)
    : QObject(parent)
    , mosquittopp(id, clean_session)
{
    int rc;
    memset(m_values, 0, DATA_SIZE);

    /* set username and password */
    rc = username_pw_set(username, password);
    if (rc != MOSQ_ERR_SUCCESS)
        qDebug() << "Username and password was not successfully set.";
    /* connect to broker */
    rc = mosquittopp::connect(host, port);
    if (rc != MOSQ_ERR_SUCCESS) {
        qDebug() << "Connection to broker was unsuccessful.";
    }
    /* subscribe to desired topics */
    rc = subscribe(NULL, topic);
    if (rc != MOSQ_ERR_SUCCESS) {
        qDebug() << "Subscription was unsuccesful.";
    }
}

MqttSubscriberClient::~MqttSubscriberClient()
{
    mosquittopp::disconnect();
}

int *MqttSubscriberClient::values()
{
    return m_values;
}

void MqttSubscriberClient::start_loop()
{
    /* put client into a forever loop meaning this function does not return unless call fails */
    int rc = loop_forever();
    if (rc != MOSQ_ERR_SUCCESS) {
        qDebug() << "Client could not be put into infinte loop.";
    }
}


void MqttSubscriberClient::on_message(const struct mosquitto_message *msg)
{
    int value;
    int cmp_value;
    char *payload_char;
    char payload[msg->payloadlen];

    payload_char = (char *)msg->payload;
    std::sscanf(payload_char, "%s", payload);

    cmp_value = strcmp(msg->topic, "current/temperature");
    if (!cmp_value) {
        value = std::stoi(payload);
        m_values[0] = value;
        qDebug() << "Temperature: " << value;
    }

    cmp_value = strcmp(msg->topic, "current/pressure");
    if (!cmp_value) {
        value = std::stoi(payload);
        m_values[1] = value;
        qDebug() << "Pressure: " << value;
    }

    cmp_value = strcmp(msg->topic, "current/humidity");
    if (!cmp_value) {
        value = std::stoi(payload_char);
        m_values[2] = value;
        qDebug() << "Humidity: " << value;
    }

    cmp_value = strcmp(msg->topic, "current/volume");
    if (!cmp_value) {
        value = std::stoi(payload);
        m_values[3] = value;
        qDebug() << "Volume: " << value;
    }

    cmp_value = strcmp(msg->topic, "current/height");
    if (!cmp_value) {
        value = std::stoi(payload);
        m_values[4] = value;
        qDebug() << "Height: " << value;
    }
}
