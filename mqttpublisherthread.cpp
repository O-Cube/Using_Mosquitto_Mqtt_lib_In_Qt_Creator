#include "mqttpublisherthread.h"
#include "mqttpublisherclient.h"

#include <cstdlib>
#include <cstdio>
#include <QDebug>

const char *topic1 = "current/temperature";
const char *topic2 = "current/pressure";
const char *topic3 = "current/humidity";
const char *topic4 = "current/volume";
const char *topic5 = "current/height";

MqttPublisherThread::MqttPublisherThread(QObject *parent)
    : QThread(parent)
    , pub_client(new MqttPublisherClient(this))
{
    srand (time(NULL));
    memset(str_value, '\0', BLOCK_SIZE);
}

MqttPublisherThread::~MqttPublisherThread()
{
    delete pub_client;
}

void MqttPublisherThread::run()
{
    int value;
    int rv;

    while (true) {

        QThread::sleep(1);

        /* randomly produce value for topic1 and publish */
        value = rand() % 101;
        snprintf(str_value, BLOCK_SIZE, "%d", value);
        rv = pub_client->publish(NULL, topic1, BLOCK_SIZE, (void *)str_value);
        if (rv != MOSQ_ERR_SUCCESS) {
            qDebug() << "Unsuccessful publish to " << topic1;
        }

        QThread::sleep(1);

        /* randomly produce value for topic2 and publish */
        value = rand() % 101;
        snprintf(str_value, BLOCK_SIZE, "%d", value);
        rv = pub_client->publish(NULL, topic2, BLOCK_SIZE, (void *)str_value);
        if (rv != MOSQ_ERR_SUCCESS) {
            qDebug() << "Unsuccessful publish to " << topic2;
        }

        QThread::sleep(1);

        /* randomly produce value for topic3 and publish */
        value = rand() % 101;
        snprintf(str_value, BLOCK_SIZE, "%d", value);
        rv = pub_client->publish(NULL, topic3, BLOCK_SIZE, (void *)str_value);
        if (rv != MOSQ_ERR_SUCCESS) {
            qDebug() << "Unsuccessful publish to " << topic3;
        }

        QThread::sleep(1);

        /* randomly produce value for topic4 and publish */
        value = rand() % 101;
        snprintf(str_value, BLOCK_SIZE, "%d", value);
        rv = pub_client->publish(NULL, topic4, BLOCK_SIZE, (void *)str_value);
        if (rv != MOSQ_ERR_SUCCESS) {
            qDebug() << "Unsuccessful publish to " << topic4;
        }

        QThread::sleep(1);

        /* randomly produce value for topic1 and publish */
        value = rand() % 101;
        snprintf(str_value, BLOCK_SIZE, "%d", value);
        rv = pub_client->publish(NULL, topic5, BLOCK_SIZE, (void *)str_value);
        if (rv != MOSQ_ERR_SUCCESS) {
            qDebug() << "Unsuccessful publish to " << topic5;
        }
    }
}
