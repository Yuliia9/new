#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

const QString SUCCESS = "0";
const QString FAIL = "1";


namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(const QUrl &_url, QWidget *parent = 0);
    ~Client();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void sendTextMessage(QString _message);
    void onTextMessageReceived(QString message);
    void on_SIgnIn_clicked();
    void on_LoadVideo_clicked();
    void on_SendVideo_clicked();
    void on_seeHistory_clicked();
    void on_addUser_clicked();
    void on_loadPictures_clicked();
    void on_addPictures_clicked();

private:
    /*fields*/
    Ui::Client *ui;
    QWebSocket webSocket;
    QUrl url;
    QString login;
    QString message;
    quint64 filesize;
    quint64 sendedData;
    QString path;
    quint16 i;
    QString picturePath[4];


    enum Action{
        authorization,
        sendVideo,
        seeHistory,
        addPicture,
        addUser
    };

    enum Users{
        Admin,
        SimpleUser,
        AdvancedUser
    };
};

#endif // CLIENT_H
