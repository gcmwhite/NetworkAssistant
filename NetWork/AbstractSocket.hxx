#pragma once

#include "DllGlobal.hxx"
#include <QObject>
#include <QAbstractSocket>
#include <QHostAddress>

GCM_BEGIN

class AbstractSocket : public QObject
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

    //打开状态
    enum class OPEN_STATUS {
        OPENING,
        OPEN_FAILED,
        OPENDED,
        CLOSED,
    };
    Q_ENUM(OPEN_STATUS)

public:
    explicit AbstractSocket(QObject *parent = nullptr);
    ~AbstractSocket();
    //获取本地所有IP地址
    static const QStringList getLocalIp(const QAbstractSocket::NetworkLayerProtocol ptc = QAbstractSocket::IPv4Protocol);
    //设置本地IP地址
    inline void setLocalAddr(const QString& ip);
    //设置本地端口号
    inline void setLocalPort(const quint16 port);
    //设置本地主机
    inline void setLocalHost(const QString& ip,const quint16 port);
    //设置远端IP地址
    inline void setRemoteAddr(const QString& ip);
    //设置远端端口号
    inline void setRemotePort(const quint16 port);
    //设置远端主机
    inline void setRemoteHost(const QString& ip,const quint16 port);
    //设置发送数据编码
    inline void setSendEncode(const STR_ENCODE se);
    //设置接收数据编码
    inline void setRecvEncode(const STR_ENCODE se);
    //打开网络接口
    virtual void open() = 0;
    //关闭网络接口
    virtual void close() = 0;
    //发送文本数据
    virtual void sendString(const QString& str) = 0;
    //发送数据
    virtual void sendByte(const QByteArray& byte) = 0;

signals:
    //错误提示
    void sigErrorStr(const QString& errorStr);
    //打开状态
    void sigOpenStatus(const OPEN_STATUS openStatus);
    //收到数据
    void sigReadRead(const QString& str,const QHostAddress& addr,const quint16 port);

protected:
    QHostAddress localAddr;         //本地IP
    QHostAddress remoteAddr;        //远端IP
    quint16      localPort;         //本地端口号
    quint16      remotePort;        //远端端口号
    STR_ENCODE   sendEncode;        //发送编码
    STR_ENCODE   recvEncode;        //接收编码
};

GCM_END
