#ifndef MQTTDISPLAY_H
#define MQTTDISPLAY_H

#include <QWidget>

class MqttPublisherThread;
class MqttSubscriberThread;
class QTimer;
class QPainter;
class QPixmap;

class MqttDisplay : public QWidget
{
    Q_OBJECT

public:
    MqttDisplay(QWidget *parent = nullptr);
    ~MqttDisplay();
    enum Bars { GREEN, RED, BLUE, YELLOW, BROWN };
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    MqttPublisherThread *pub_thread = nullptr;
    MqttSubscriberThread *sub_thread = nullptr;
    QTimer *internal_clock = nullptr;
    /* draw bars to canvas */
    void drawBars(Bars bar, int numbars, QPainter *painter);
};
#endif // MQTTDISPLAY_H
