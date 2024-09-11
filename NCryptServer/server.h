#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QVector>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();
public slots:
    void start(QString host, int port);

private slots:
    void newClient();
    void leftClient();
    void sendToAll(QByteArray message);
    void messageFromClient();
signals:

private:
    void showClientsAmount() { qDebug() << "Total clients: " << m_clients.size(); }

    QTcpServer *m_server = nullptr;
    QVector<QTcpSocket *> m_clients;
};

#endif // SERVER_H
