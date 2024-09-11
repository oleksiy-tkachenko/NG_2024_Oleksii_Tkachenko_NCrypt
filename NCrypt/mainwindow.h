#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SendMessage();
    void RecievedMessage();
    void ConnectionEstablished();
private:
    Ui::MainWindow *ui;
    QTcpSocket* m_socket;


};
#endif // MAINWINDOW_H
