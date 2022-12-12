#include "gatisconsole.h"
#include "./ui_gatisconsole.h"
#include "outipi.h"

GatisConsole::GatisConsole(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GatisConsole)
{
    ui->setupUi(this);

    OutiPi *udp1 = new OutiPi(&tstDev1);
//    OutiPi *udp2 = new OutiPi(&tstDev2);

    tstDev1.setSelf("HOUSIOS", "OBLACK", "TSI");
    tstDev2.setSelf("TSAO", "OWHITE", "MPA");

    MiaouMsg msg;
    msg.setSrc(tstDev1.getSelf());
    msg.setDst(tstDev2.getSelf());
    msg.msgID = 6969;



    udp1->give(msg);

    QThread::currentThread()->msleep(50);

    msg.setSrc(tstDev1.getSelf());
    msg.setDst(tstDev2.getSelf());
    msg.msgID = 696969;
    msg.data = QJsonDocument {
            QJsonObject{
                {"kalts", true},
                {"pote", "xthes"}}
        };



    udp1->give(msg);

//    udp2->give(msg);
}

GatisConsole::~GatisConsole()
{
    delete ui;
}

