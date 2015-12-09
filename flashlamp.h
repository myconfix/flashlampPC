#ifndef FLASHLAMP_H
#define FLASHLAMP_H

#include <QWidget>
#include "../../qmqttlib/qmqtt.h"

namespace Ui {
class flashlamp;
}

class flashlamp : public QWidget
{
    Q_OBJECT

public:
    explicit flashlamp(QWidget *parent = 0);
    ~flashlamp();


public slots:
    void onMQTT_Connected();
    void onMQTT_disconnected();
    void mqtt_setup();
    void mqtt_pub(QString topic,QString value);

private slots:

    void on_Base_Dial_sliderMoved(int position);

    void on_Holder_Dial_sliderMoved(int position);

private:
    Ui::flashlamp *ui;
    long map(long x, long in_min, long in_max, long out_min, long out_max);
    QMQTT::Client *client;
    QString mqtt_topic_base="/openqt/base";
    QString mqtt_topic_arm="/openqt/arm";
};

#endif // FLASHLAMP_H
