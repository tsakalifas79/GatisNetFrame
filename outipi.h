#ifndef OUTIPI_H
#define OUTIPI_H

#include "whiskvice.h"
#include <QUdpSocket>
#include <QThread>

class OutiPi : public QObject, public OutterWorld
{
    Q_OBJECT
    QUdpSocket *udpServer = nullptr;
public:
    OutiPi(WhiskVice *dev);
    ~OutiPi(){}

private slots:
    void slotNewMsg();
    // OutterWorld interface
public:
    void give(const MiaouMsg &msg);
};


#endif // OUTIPI_H
