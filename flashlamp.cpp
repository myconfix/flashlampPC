#include "flashlamp.h"
#include "ui_flashlamp.h"
#include <QDebug>

flashlamp::flashlamp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::flashlamp)
{
    client = new QMQTT::Client();

    ui->setupUi(this);


    connect(client, SIGNAL(connected()), this, SLOT(onMQTT_Connected()));
    connect(client, SIGNAL(disconnected()), this, SLOT(onMQTT_disconnected()));

    mqtt_setup();

    if(!client->isConnected())
    {
        qDebug() << "Can not Connect MQTT Server";
    }
}

flashlamp::~flashlamp()
{
    delete ui;
}

void flashlamp::on_Base_Dial_sliderMoved(int position)
{
    ui->base_lcd_number->display(position);
    long y=map(position,0,360,8,25);
    ui->base_pulse_label->setText(QString::number(y));
    mqtt_pub(mqtt_topic_base,QString::number(y));


}

void flashlamp::on_Holder_Dial_sliderMoved(int position)
{
    ui->arm_lcd_number->display(position);
    long y=map(position,0,180,8,25);
    ui->arm_pulse_label->setText(QString::number(y));
    mqtt_pub(mqtt_topic_arm,QString::number(y));
}
void flashlamp::mqtt_setup()
{
    try{
        client->setHost("localhost");
        client->setPort(1883);
        //client->setUsername
        client->connect();

        QMQTT::Message msg(0,"/myconfix/openqt","Hello Flash Lamp");
        client->publish(msg);

    }catch (...){

    }
}
void flashlamp::onMQTT_Connected()
{
    qDebug() << "Connected";
}
void flashlamp::onMQTT_disconnected()
{
    qDebug() << "Disconnected";
}
void flashlamp::mqtt_pub(QString topic, QString value)
{
        QMQTT::Message msg(0,topic,value.toUtf8());
        client->publish(msg);
}

long flashlamp::map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

