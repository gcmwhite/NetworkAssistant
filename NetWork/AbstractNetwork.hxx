#pragma once

#include "DllGlobal.hxx"
#include <QObject>
#include <QAbstractSocket>
#include <QHostAddress>

GCM_BEGIN

class AbstractNetwork : public QObject
{
    Q_OBJECT

public:
    //字符串需要转换编码格式
    enum class STR_ENCODE {
        GBK,
        UTF8,
        HEX
    };

    Q_ENUM(STR_ENCODE)

public:
    explicit AbstractNetwork(QObject *parent = nullptr);
    ~AbstractNetwork();
    //获取本地所有IP地址
    const QStringList getLocalIp(const QAbstractSocket::NetworkLayerProtocol ptc = QAbstractSocket::IPv4Protocol);
    //设置本地IP地址
    void setLocalAddr(const QString& ip);
    //设置本地端口号
    void setLocalPort(const quint16 port);
    //设置本地主机
    void setLocalHost(const QString& ip,const quint16 port);
    //设置远端IP地址
    void setRemoteAddr(const QString& ip);
    //设置远端端口号
    void setRemotePort(const quint16 port);
    //设置远端主机
    void setRemoteHost(const QString& ip,const quint16 port);
    //打开网络接口
    virtual bool open() = 0;
    //关闭网络接口
    virtual bool close() = 0;
    //发送文本数据
    virtual void sendString(const QString& str,STR_ENCODE se = STR_ENCODE::UTF8) = 0;
    //发送数据
    virtual void sendByte(const QByteArray& byte) = 0;

signals:
    //错误提示
    void sigErrorStr(const QString& errorStr);

private:
    QHostAddress localAddr;         //本地IP
    QHostAddress remoteAddr;        //远端IP
    quint16      localPort;         //本地端口号
    quint16      remotePort;        //远端端口号
};

GCM_END
