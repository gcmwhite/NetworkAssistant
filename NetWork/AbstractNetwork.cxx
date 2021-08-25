#include "AbstractNetwork.hxx"
#include <QNetworkInterface>

GCM_BEGIN

AbstractNetwork::AbstractNetwork(QObject *parent) : QObject(parent)
{

}

AbstractNetwork::~AbstractNetwork()
{

}

const QStringList AbstractNetwork::getLocalIp(const QAbstractSocket::NetworkLayerProtocol ptc)
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

void AbstractNetwork::setLocalAddr(const QString &ip)
{
    localAddr = QHostAddress(ip);
}

void AbstractNetwork::setLocalPort(const quint16 port)
{
    localPort = port;
}

void AbstractNetwork::setLocalHost(const QString &ip, const quint16 port)
{
    localAddr = QHostAddress(ip);
    localPort = port;
}

void AbstractNetwork::setRemoteAddr(const QString &ip)
{
    remoteAddr = ip;
}

void AbstractNetwork::setRemotePort(const quint16 port)
{
    remotePort = port;
}

void AbstractNetwork::setRemoteHost(const QString &ip, const quint16 port)
{
    remoteAddr = QHostAddress(ip);
    remotePort = port;
}

GCM_END
