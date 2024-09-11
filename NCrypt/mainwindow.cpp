#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_socket = new QTcpSocket();
    connect (ui->sendButton, &QPushButton::clicked, this, &MainWindow::SendMessage);
    connect (m_socket, &QTcpSocket::connected, this, &MainWindow::ConnectionEstablished);
    connect (m_socket, &QTcpSocket::readyRead, this, &MainWindow::RecievedMessage);

    m_socket->connectToHost(QHostAddress("192.168.1.3"), 8081);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SendMessage()
{
    QString message = ui->messageBox->toPlainText();
    if(message == ""){return;}
    while (message.endsWith("\n")){
        message.chop(1);
    }
    if(message != ""){
        m_socket->write(message.toLocal8Bit());
        ui->messageBox->clear();
    }
}

void MainWindow::RecievedMessage()
{
    ui->textBox->setText(ui->textBox->text()+"\n"+ QString(m_socket->readAll()));
}

void MainWindow::ConnectionEstablished()
{
    ui->textBox->setText( QString("Connected successfully"));
}
