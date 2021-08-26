#include "AbstractSocket.hxx"
#include <QNetworkInterface>

GCM_BEGIN

AbstractSocket::AbstractSocket(QObject *parent) : QObject(parent)
{

}

AbstractSocket::~AbstractSocket()
{

}

const QStringList AbstractSocket::getLocalIp(const QAbstractSocket::NetworkLayerProtocol ptc)
{
    const auto &&addresses = QNetworkInterface::allAddresses();
    bool flag = QAbstractSocket::AnyIPProtocol == ptc || QAbstractSocket::UnknownNetworkLayerProtocol == ptc;
    QStringList list;
    for (const auto& x : addresses) {
        if (flag || x.protocol() == ptc) {
            list << x.toString();
        }
    }
    return list;
}

void AbstractSocket::setLocalAddr(const QString &ip)
{
    localAddr = QHostAddress(ip);
}

void AbstractSocket::setLocalPort(const quint16 port)
{
    localPort = port;
}

void AbstractSocket::setLocalHost(const QString &ip, const quint16 port)
{
    localAddr = QHostAddress(ip);
    localPort = port;
}

void AbstractSocket::setRemoteAddr(const QString &ip)
{
    remoteAddr = QHostAddress(ip);
}

void AbstractSocket::setRemotePort(const quint16 port)
{
    remotePort = port;
}

void AbstractSocket::setRemoteHost(const QString &ip, const quint16 port)
{
    remoteAddr = QHostAddress(ip);
    remotePort = port;
}

void AbstractSocket::setSendEncode(const STR_ENCODE se)
{
    sendEncode = se;
}

void AbstractSocket::setRecvEncode(const STR_ENCODE se)
{
    recvEncode = se;
}

GCM_END
