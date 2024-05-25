#include "mqttpublisherclient.h"

#include <QDebug>

/* connection parameters of mosquitto broker; with regards to specifications of external running broker */
static int port = 60001;
static const char *host = "127.0.0.1";
static const char *username = "Obed";
static const char *password = "password";
static char msg[20];

static const char *topic1 = "current/temperature";

MqttPublisherClient::MqttPublisherClient(QObject *parent, char const *id, bool clean_session)
    : QObject(parent)
    , mosquittopp(id, clean_session)
{
    int rc;
    /* set username and password */
    rc = username_pw_set(username, password);
    if (rc != MOSQ_ERR_SUCCESS)
        qDebug() << "Username and password was not successfully set.";
    /* connect to mosquitto broker */
    rc = mosquittopp::connect(host, port, 60);
    if (rc != MOSQ_ERR_SUCCESS)
        qDebug() << "Connection to broker was unsuccessful.";
}

void MqttPublisherClient::on_publish(int mid)
{
    Q_UNUSED(mid)
    qDebug() << "Data published.";
}
