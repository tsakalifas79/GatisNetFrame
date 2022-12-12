#include "miaoumsg.h"

MiaouMsg::MiaouMsg()
{
    src.mac  = "Poutses";
    src.type = "Poutses";
    src.name = "Kaltses";
    dst.mac  = "Mounia";
    dst.type = "Mounia";
    dst.name = "Vrakia";
}

MiaouMsg::MiaouMsg(const QByteArray &dat) {
    QJsonDocument msg = QJsonDocument::fromJson(dat);
    fromJson(msg);
//    qDebug()<<"\nJSON File: " << msg;
}

MiaouMsg::MiaouMsg(const DevID &&srcIn, const DevID &&dstIn, const QJsonDocument &dataIn, const MsgIdFlag &&msgIdIn) {
    src = std::move(srcIn);
    dst = std::move(dstIn);
    data = std::move(dataIn);
    msgID = msgIdIn;
}

void MiaouMsg::setSrc(const DevID &mdev)
{
    src.type = mdev.type;
    src.name = mdev.name;
    src.mac = mdev.mac;
}

void MiaouMsg::setDst(const DevID &mdev)
{
    dst.type = mdev.type;
    dst.name = mdev.name;
    dst.mac = mdev.mac;
}

void MiaouMsg::fromJson(const QJsonDocument &dataIn) {
//    QJsonValue s = dataIn["SRC"];
    QJsonDocument s = QJsonDocument::fromJson(dataIn["SRC"].toString().toUtf8());
    src.type = s["TYPE"].toString();
    src.name = s["NAME"].toString();
    src.mac  = s["MAC"].toString();
//    qDebug()<<"SrcObj:" << s << dataIn["SRC"]<< src.type<< src.name<< src.mac;
//    qDebug()<<"SrcObj1:" << src.type<< src.name<< src.mac<< s["TYPE"].toString()<< s["NAME"]<< s["MAC"].toString();

//    QJsonValue d = dataIn["DST"];
    QJsonDocument d = QJsonDocument::fromJson(dataIn["DST"].toString().toUtf8());
    dst.type = d["TYPE"].toString();
    dst.name = d["NAME"].toString();
    dst.mac  = d["MAC"].toString();
//    qDebug()<<"DstObj:" << d << dataIn["DST"] ;
//    qDebug()<<"DstObj1:" << dst.type<< dst.name<< dst.mac<< d["TYPE"].toString()<< d["NAME"]<< d["MAC"].toString();

    msgID = dataIn["MSGID"].toString().toULongLong();

//    qDebug()<<"msgidObj:" << msgID;

    data = QJsonDocument::fromJson(dataIn["DATA"].toString().toUtf8());
//    qDebug()<<"DataObj:" << data << dataIn["DATA"];
}

QJsonDocument MiaouMsg::toJson() const {

    QJsonObject all;
    QJsonObject s;
    s["TYPE"] = src.type;
    s["NAME"] = src.name;
    s["MAC"] = src.mac;

//    qDebug()<< "Test SRC: " << s <<src.type << src.name << src.mac;

    QJsonObject d;
    d["TYPE"] = dst.type;
    d["NAME"] = dst.name;
    d["MAC"] = dst.mac;

//    qDebug()<< "Test DST: " << d <<dst.type << dst.name << dst.mac;


    all["SRC"] = s;
    all["DST"] = d;
    all["MSGID"] = QString::number(msgID);
    all["DATA"] = data.object();

//    qDebug()<< "Test DST: " << data;

    QJsonDocument doc;
    doc.setObject(all);

//    qDebug()<< "Test DOC: " << doc;
//    qDebug()<< "Test ALL: " << all;
    return doc;
}
