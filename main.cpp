#include "mqttdisplay.h"
#include "mqttpublisherthread.h"
#include "mqttsubscriberthread.h"

#include <QApplication>
#include <mosquittopp.h>
#include <memory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MqttDisplay *widget(new MqttDisplay());
    widget->show();

    return a.exec();
}
