#include "Server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    m_server = new QTcpServer();

    connect (m_server, &QTcpServer::newConnection, this, &Server::newClient);
}

Server::~Server()
{
    if (m_server->isListening()) {
        qDebug() << "Closing Server...";
        m_server->close();
    }
    delete m_server;
}

void Server::start(QString host, int port)
{
    bool ok = m_server->listen(QHostAddress(host), port);
    if (ok) {
        qDebug() << "We are online!";
    } else {
        qDebug() << "Error creating connection: " << m_server->errorString();
    }
}

void Server::newClient()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    qDebug() << "Client " << client->localAddress().toString();

    connect (client, &QTcpSocket::disconnected, this, &Server::leftClient);
    connect (client, &QTcpSocket::readyRead, this, &Server::messageFromClient);

    m_clients.append(client);
    showClientsAmount();
}

void Server::leftClient()
{
    QTcpSocket *socket = (QTcpSocket *)sender();

    qDebug() << "Client " << socket->localAddress().toString() << " has been left";
    m_clients.removeOne(socket);
    showClientsAmount();
}

void Server::sendToAll(QByteArray message)
{
    for (QTcpSocket *client : m_clients)
        client->write(message);
}

void Server::messageFromClient()
{
    QTcpSocket *socket = (QTcpSocket *)sender();
    QByteArray message = socket->readAll();
    qDebug() << message;
    sendToAll(message);
}
