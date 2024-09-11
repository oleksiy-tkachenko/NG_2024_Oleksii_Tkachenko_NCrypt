#include <QCoreApplication>
#include <Server.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server myserver;
    myserver.start("0.0.0.0", 8081);
    return a.exec();
}
