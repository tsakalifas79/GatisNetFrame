#include "outipi.h"

OutiPi::OutiPi(WhiskVice *dev) {
    udpServer = new QUdpSocket;

    setDev(dev);
    bool bindOk = udpServer->bind(QHostAddress::AnyIPv4, CATS_PORT, QUdpSocket::ShareAddress);
    bool multiOk = udpServer->joinMulticastGroup(QHostAddress(QStringLiteral(MULTI_GROUP_ADDR)));
//    bool bindOk = udpServer->bind(CATS_PORT, QUdpSocket::ShareAddress);
    connect(udpServer, &QUdpSocket::readyRead, this, &OutiPi::slotNewMsg);
    qDebug() << "OutIiPi" << dev->getSelf().name << bindOk << udpServer->errorString() << udpServer->localAddress();
}

void OutiPi::slotNewMsg() {
    if( ! mDev ) return;
    while ( udpServer->hasPendingDatagrams() ) {
        QByteArray datagram;
        datagram.resize(int(udpServer->pendingDatagramSize()));
        udpServer->readDatagram(datagram.data(), datagram.size());

//        qDebug()<<"Message INPUT: "<< datagram;

        MiaouMsg msg(datagram);
        mDev->take(msg);
    }
}

void OutiPi::give(const MiaouMsg &msg) {

    QUdpSocket *tmpSock = new QUdpSocket(QThread::currentThread()->parent());
    tmpSock->connectToHost(QHostAddress::LocalHost, CATS_PORT, QIODevice::WriteOnly);
    QByteArray raw = msg.toJson().toJson();
    quint64 dataWriten = tmpSock->writeDatagram(raw, QHostAddress::Broadcast, CATS_PORT);
    qDebug()<<"OutiPi::give OUTPUT: "<< msg.toJson();

    Q_ASSERT(dataWriten == raw.size());

    tmpSock->flush();
    tmpSock->disconnectFromHost();
    tmpSock->close();
    tmpSock->deleteLater();

}
