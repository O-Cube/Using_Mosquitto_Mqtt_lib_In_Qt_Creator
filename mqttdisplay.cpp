#include "mqttdisplay.h"

#include "mqttpublisherthread.h"
#include "mqttsubscriberthread.h"

#include <QTimer>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <QPixmap>
#include <memory>

MqttDisplay::MqttDisplay(QWidget *parent)
    : QWidget(parent)
    , pub_thread(new MqttPublisherThread(this))
    , sub_thread(new MqttSubscriberThread(this))
    , internal_clock(new QTimer(this))
{
    resize(700, 600);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    pub_thread->start();
    sub_thread->start();

    /* internal clock is periodic with timeout of 1000msec */
    internal_clock->setInterval(1000);
    /* internal clock calls update function every timeout */
    internal_clock->callOnTimeout(this, [this]() {
        update();
    });

    internal_clock->start();
}

MqttDisplay::~MqttDisplay()
{
    pub_thread->quit();
    sub_thread->quit();

    pub_thread->wait();
    sub_thread->wait();

    delete pub_thread;
    delete sub_thread;
    delete internal_clock;
}

void MqttDisplay::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.fillRect(QRect(0, 0, width(), height()), Qt::black);

    std::unique_ptr<QPixmap> map(new QPixmap());
    std::unique_ptr<QPen> pen(new QPen(Qt::white));
    painter.setPen(*pen);

    /* Green gradient */
    map->load(tr("/home/oyandut/MqttSystem/pixmaps/green_bar_95_3.png"));

    painter.drawPixmap(5, 10, *map);
    painter.drawText(QRect(5, 15, 95, 15), Qt::AlignLeft, tr("Temperature"));

    /* Red gradient */
    map->load(tr("/home/oyandut/MqttSystem/pixmaps/red_bar_95_3.png"));

    painter.drawPixmap(5, 35, *map);
    painter.drawText(QRect(5, 40, 95, 15), Qt::AlignLeft, tr("Pressure"));

    /* blue gradient */
    map->load(tr("/home/oyandut/MqttSystem/pixmaps/blue_bar_95_3.png"));

    painter.drawPixmap(5, 60, *map);
    painter.drawText(QRect(5, 65, 95, 15), Qt::AlignLeft, tr("Humidity"));

    /* Gold gradient */
    map->load(tr("/home/oyandut/MqttSystem/pixmaps/yellow_bar_95_3.png"));

    painter.drawPixmap(5, 85, *map);
    painter.drawText(QRect(5, 90, 95, 15), Qt::AlignLeft, tr("Volume"));

    /* brown gradient */
    map->load(tr("/home/oyandut/MqttSystem/pixmaps/brown_bar_95_3.png"));

    painter.drawPixmap(5, 110, *map);
    painter.drawText(QRect(5, 115, 95, 15), Qt::AlignLeft, tr("Pressure"));

    painter.drawLine(QPoint(120, 10), QPoint(120, 560));
    painter.drawLine(QPoint(120, 560), QPoint(680, 560));

    painter.save();

    /* set pen width to 0.1 */
    pen->setWidthF(0.1);
    painter.setPen(*pen);

    /* horizontal grid lines */
    painter.drawLine(QPoint(120, 460), QPoint(680, 460));
    painter.drawLine(QPoint(120, 360), QPoint(680, 360));
    painter.drawLine(QPoint(120, 260), QPoint(680, 260));
    painter.drawLine(QPoint(120, 160), QPoint(680, 160));
    painter.drawLine(QPoint(120, 60), QPoint(680, 60));

    /* vertical grid lines */
    painter.drawLine(QPoint(220, 10), QPoint(220, 560));
    painter.drawLine(QPoint(320, 10), QPoint(320, 560));
    painter.drawLine(QPoint(420, 10), QPoint(420, 560));
    painter.drawLine(QPoint(520, 10), QPoint(520, 560));
    painter.drawLine(QPoint(620, 10), QPoint(620, 560));

    painter.restore();

    painter.save();
    drawBars(MqttDisplay::GREEN, *sub_thread->get_values(), &painter);
    drawBars(MqttDisplay::RED, *(sub_thread->get_values() + 1), &painter);
    drawBars(MqttDisplay::BLUE, *(sub_thread->get_values() + 2), &painter);
    drawBars(MqttDisplay::YELLOW, *(sub_thread->get_values() + 3), &painter);
    drawBars(MqttDisplay::BROWN, *(sub_thread->get_values() + 4), &painter);
    painter.restore();
}

void MqttDisplay::drawBars(Bars bar, int numbars, QPainter *painter)
{
    std::unique_ptr<QPoint> startPoint(new QPoint());
    std::unique_ptr<QPixmap> map(new QPixmap());

    switch(bar) {
    case GREEN:
        startPoint->setX(123);
        startPoint->setY(555);
        map->load(tr("/home/oyandut/MqttSystem/pixmaps/green_bar_95_3.png"));
        break;
    case RED:
        startPoint->setX(223);
        startPoint->setY(555);
        map->load(tr("/home/oyandut/MqttSystem/pixmaps/red_bar_95_3.png"));
        break;
    case BLUE:
        startPoint->setX(323);
        startPoint->setY(555);
        map->load(tr("/home/oyandut/MqttSystem/pixmaps/blue_bar_95_3.png"));
        break;
    case YELLOW:
        startPoint->setX(423);
        startPoint->setY(555);
        map->load(tr("/home/oyandut/MqttSystem/pixmaps/yellow_bar_95_3.png"));
        break;
    case BROWN:
        startPoint->setX(523);
        startPoint->setY(555);
        map->load(tr("/home/oyandut/MqttSystem/pixmaps/brown_bar_95_3.png"));
        break;
    }

    for (int i = 0; i < numbars; i++) {
        painter->drawPixmap(*startPoint, *map);
        startPoint->setY(startPoint->y() - 5);
    }
}
