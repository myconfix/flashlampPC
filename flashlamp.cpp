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
    connect(client, SIGNAL(received(QMQTT::Message)),this, SLOT(onMQTT_Received(QMQTT::Message)));

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
    mqtt_pub(mqtt_topic_base,QString::number(position));

}

void flashlamp::on_Arm_Dial_sliderMoved(int position)
{
    ui->arm_lcd_number->display(position);
    mqtt_pub(mqtt_topic_arm,QString::number(position));
}
void flashlamp::mqtt_setup()
{
    try{
        client->setHost("192.168.43.137");
        client->setPort(1884);
        //client->setUsername
        client->connect();

    }catch (...){

    }
}
void flashlamp::onMQTT_Connected()
{
    qDebug() << "Connected";

    QMQTT::Message msg(0,"/openqt","Hello Flash Lamp PC");
    client->publish(msg);
    mqtt_sub(mqtt_topic_sub);
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
void flashlamp::mqtt_sub(QString topic)
{
    client->subscribe(topic,0);
}
void flashlamp::onMQTT_Received(const QMQTT::Message &message)
{
    qDebug() <<"Topic : " << message.topic();
    qDebug() <<"Value : " << message.payload().toInt();

    if(message.topic() == mqtt_topic_base){
        ui->Base_Dial->setValue(message.payload().toInt());
    }
    if(message.topic() == mqtt_topic_arm){
        ui->Arm_Dial->setValue(message.payload().toInt());
    }
}


void flashlamp::on_Arm_Dial_valueChanged(int value)
{
     ui->arm_lcd_number->display(value);
}

void flashlamp::on_Base_Dial_valueChanged(int value)
{
    ui->base_lcd_number->display(value);
}
