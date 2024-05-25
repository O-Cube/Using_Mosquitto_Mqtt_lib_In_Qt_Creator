#ifndef MQTTPUBLISHERCLIENT_H
#define MQTTPUBLISHERCLIENT_H

#include <QObject>
#include <mosquittopp.h>

using namespace mosqpp;

class MqttPublisherClient : public QObject, public mosquittopp
{
    Q_OBJECT
public:
    explicit MqttPublisherClient(QObject *parent = nullptr, char const *id = NULL, bool clean_session = true);

    /* virtual functions */
    void on_publish(int mid) override;
};

#endif // MQTTPUBLISHERCLIENT_H
