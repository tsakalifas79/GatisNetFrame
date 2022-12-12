#include "whiskvice.h"

const DevID &WhiskVice::getSelf() const
{
    return self;
}

WhiskVice::WhiskVice(const QString &name, const QString &type, const QString &mac) {
    setSelf(name, type, mac);
}

WhiskVice::WhiskVice()
{

}

void WhiskVice::setSelf(const QString &name, const QString &type, const QString &mac) {
    self.name = name;
    self.type = type;
    self.mac  = mac;
}

void WhiskVice::take(const MiaouMsg &msg) {

//    qDebug() << "WhiskVice::take - before" << self.name << others.size();
    qDebug() << "WhiskVice::take INPUT" << msg.src.mac << getSelf().mac << msg.toJson();
    if(msg.src.mac.toStdString() == getSelf().mac.toStdString()) return; //DROP
    if(others.count(msg.src.mac.toStdString()) == 0)
    {
        others.insert( { msg.src.mac.toStdString(), msg.src } );
    }

    qDebug() << "WhiskVice::take INPUT" << self.name << msg.toJson();
//    qDebug() << "WhiskVice::take - after" << self.name << others.size();

    MiaouMsg msgOut;
    msgOut.setSrc(getSelf());
    msgOut.setDst(msg.src);
    msgOut.msgID = msg.msgID;
    msgOut.data = QJsonDocument {
            QJsonObject{
                {"LELELELELELEL", true},
                {"LALALALALALLA", "xthes"}}
        };


}
