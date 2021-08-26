#pragma once

#include "AbstractSocket.hxx"
#include "DllGlobal.hxx"

class QUdpSocket;
GCM_BEGIN

class NETWORK_EXPORT UdpSocket : public AbstractSocket
{
    Q_OBJECT
public:
    explicit UdpSocket(QObject *parent = nullptr);
    ~UdpSocket();
    //打开网络接口
    void open() override;
    //关闭网络接口
    void close() override;
    //发送文本数据
    void sendString(const QString& str8) override;
    //发送数据
    void sendByte(const QByteArray& byte) override;

protected:
    //接收到数据
    void onReceived();

private:
    QUdpSocket    *socket;
};

GCM_END
