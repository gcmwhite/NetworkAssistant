#include "UdpSocket.hxx"
#include <QUdpSocket>
#include <QNetworkProxy>
#include <QNetworkDatagram>

GCM_BEGIN

UdpSocket::UdpSocket(QObject *parent) : AbstractSocket(parent)
{
    socket = new QUdpSocket(this);
    socket->setProxy(QNetworkProxy::NoProxy);
    //错误提示
    connect(socket,&QUdpSocket::errorOccurred,this,[this](){
        emit sigErrorStr(socket->errorString());
    });
    //接收到数据
    connect(socket,&QUdpSocket::readyRead,this,&UdpSocket::onReceived);
}

UdpSocket::~UdpSocket()
{
    socket->close();
}

void UdpSocket::open()
{
    emit sigOpenStatus(OPEN_STATUS::OPENING);
    bool open = socket->bind(localAddr,localPort);
    emit sigOpenStatus(open ? OPEN_STATUS::OPENDED : OPEN_STATUS::OPEN_FAILED);
}

void UdpSocket::close()
{
    socket->close();
    emit sigOpenStatus(OPEN_STATUS::CLOSED);
}

void UdpSocket::sendString(const QString &str8)
{
    QNetworkDatagram datagram;
    datagram.setDestination(remoteAddr,remotePort);
    switch (sendEncode) {
        case STR_ENCODE::GBK: datagram.setData(str8.toLocal8Bit()); break;
        case STR_ENCODE::UTF8: datagram.setData(str8.toUtf8()); break;
        case STR_ENCODE::HEX: datagram.setData(QByteArray::fromHex(str8.toUtf8())); break;
    }
    socket->writeDatagram(datagram);
}

void UdpSocket::sendByte(const QByteArray &byte)
{
    socket->writeDatagram(byte,remoteAddr,remotePort);
}

void UdpSocket::onReceived()
{
    QString str;
    while (socket->hasPendingDatagrams()) {
        const QNetworkDatagram&& datagram = socket->receiveDatagram();
        switch (recvEncode) {
            case STR_ENCODE::GBK: str = QString::fromLocal8Bit(datagram.data()); break;
            case STR_ENCODE::HEX: str = datagram.data().toHex(' ').toUpper(); break;
            case STR_ENCODE::UTF8: str = QString::fromUtf8(datagram.data()); break;
        }
        emit sigReadRead(str,datagram.senderAddress(),datagram.senderPort());
    }
}

GCM_END
