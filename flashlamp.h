#ifndef FLASHLAMP_H
#define FLASHLAMP_H

#include <QWidget>
#include "qmqttlib/qmqtt.h"

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
    void onMQTT_Received(const QMQTT::Message &message);
    void mqtt_setup();
    void mqtt_pub(QString topic,QString value);
    void mqtt_sub(QString topic);

private slots:

    void on_Base_Dial_sliderMoved(int position);

    void on_Arm_Dial_sliderMoved(int position);

    void on_Arm_Dial_valueChanged(int value);

    void on_Base_Dial_valueChanged(int value);

private:
    Ui::flashlamp *ui;
    QMQTT::Client *client;
    QString mqtt_topic_base="/openqt/base";
    QString mqtt_topic_arm="/openqt/arm";
    QString mqtt_topic_sub="/openqt/#";
};

#endif // FLASHLAMP_H
