#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client client(QUrl(QStringLiteral("ws://localhost:80")));
    QObject::connect(&client, &Client::closed, &a, &QCoreApplication::quit);

    client.show();

    return a.exec();
}
