#ifndef MIAOUMSG_H
#define MIAOUMSG_H

#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

struct DevID {
    QString name, type, mac;
//    std::string
};

enum MsgIdFlag {
    DEF = 0b0,
    GET = 0b1,
    PUT = 0b10,
    MAX = 0xFFFFFFFF
};

class MiaouMsg
{
public:
    MiaouMsg();
    MiaouMsg(const MiaouMsg &dat) = default;
    MiaouMsg(const DevID &&srcIn, const DevID &&dstIn, const QJsonDocument &dataIn, const MsgIdFlag &&msgIdIn = MsgIdFlag::DEF);
    MiaouMsg(const QByteArray &dat);

    DevID src, dst;
    size_t msgID = MsgIdFlag::DEF;
    QJsonDocument data;

    void fromJson(const QJsonDocument &dataIn);

    QJsonDocument toJson() const;
    void setSrc(const DevID &mdev);
    void setDst(const DevID &mdev);
};


#endif // MIAOUMSG_H
