#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QMap>
#include <QtCore/QByteArray>

const QString SUCCESS = "0";
const QString FAIL = "1";

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Server : public QObject
{
    Q_OBJECT
public:
    /*life cycle*/
    explicit Server(quint16 port, QObject *parent = Q_NULLPTR);
    ~Server();

Q_SIGNALS:
    void closed();

    /*
signals:
    void makeAuthorization(QString login, QString password);
    */

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString _message);
    void processBinaryMessage(QByteArray data);
    void socketDisconnected();
/*
private slots:
    void onAuthorization(QString login, QString password);
*/
private:
    /*fields*/
    QByteArray package;
    QWebSocketServer* pWebSocketServer;
    QMap <QWebSocket* , QString> pClients;
    QString message;

    QString onAuthorization(QString login, QString password);
    QString onSeeHistory(QString username);
    QString onAddUser(QString login, QString password, quint16 id);

    enum Users
    {
        Admin,
        SimpleUser,
        AdvancedUser
    };

    enum Action{
        authorization,
        sendVideo,
        seeHistory,
        addPicture,
        addUser
    };


};

#endif // SERVER_H
