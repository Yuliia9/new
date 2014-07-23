#include "server.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextCodec>
#include <QFile>


QT_USE_NAMESPACE


//constructor
Server::Server(quint16 port, QObject *parent):
     QObject(parent),
     pWebSocketServer(new QWebSocketServer(QStringLiteral("Server"),
                                                 QWebSocketServer::NonSecureMode, this)),
     pClients()
{
    /*Tells the server to listen for incoming connections*/
    if (pWebSocketServer->listen(QHostAddress::Any, port))
     {
        qDebug() << "Server listening on port" << port;
        connect(pWebSocketServer, &QWebSocketServer::newConnection,
                this, &Server::onNewConnection);
        connect(pWebSocketServer, &QWebSocketServer::closed, this, &Server::closed);

    }
 }


//destructor
Server::~Server()
{
    pWebSocketServer->close();
    pClients.clear();
}



void Server::onNewConnection()
{
    //Returns the next pending connection as a connected QWebSocket object
    QWebSocket *pSocket = pWebSocketServer->nextPendingConnection();
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);

    //adds new client to the list
    pClients.insert(pSocket, "");
}



void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (pClient)
    {
        pClients.remove(pClient);
        pClient->deleteLater();
    }
}




/*
* @brief					Process text messages from users
*                           first byte of message is action that user wants to do
* @param	[QString]       _message - text message from user
* @return	void
*/
void Server::processTextMessage(QString _message)
{
    qDebug() << "Text Message received";

    QWebSocket* pClient = qobject_cast<QWebSocket* >(sender());
    if(pClient == NULL)
    {
        qDebug() << "Unapropriate user connection\n";
        return;
    }

    QString response;
    response.append(_message[0]);
    response += "|";
    QStringList substrings = _message.split("|") ;

    if(substrings.length() == 1)
    {
        qDebug()<< "Unpropriate user's request";
        response += FAIL;
        if(pClient)
        {
            pClient->sendTextMessage(response);
        }
        return;
    }


    /*Process user request, first character represent the user's action */
    switch(_message[0].digitValue())
    {

    case authorization:
    {
        QString login, password;
        password = substrings.value( substrings.length() - 1 );
        login = substrings.value(substrings.length()- 2 );
        response += onAuthorization(login, password);
    }
        break;

    case sendVideo:
    {
        QString filename = substrings.value(substrings.length() - 1 );
        if(pClients.contains(pClient))
        {
            pClients[pClient] = filename;
        }
        else
        {
            pClients.insert(pClient, filename);
        }
        connect(pClient, &QWebSocket::binaryMessageReceived, this, &Server::processBinaryMessage);
        return;
     }
        break;

    case seeHistory:
        response += onSeeHistory(substrings.value(substrings.length() - 1 ));
        break;

    case addPicture:
    {
        QString filename = substrings.value(substrings.length() - 1 );
        if(pClients.contains(pClient))
        {
            pClients[pClient] = filename;
        }
        else
        {
            pClients.insert(pClient, filename);
        }
        connect(pClient, &QWebSocket::binaryMessageReceived, this, &Server::processBinaryMessage);
        return;
     }
        break;

    case addUser:
    {
        qDebug() << _message;
        QString login, password;
        quint16 id;
        password = substrings.value( substrings.length() - 2 );
        login = substrings.value(substrings.length()- 3 );
        id = substrings.value(substrings.length() - 1 ).toInt();
        response += onAddUser(login, password, id);
    }
     break;

     /*if server doesn't support user's request*/
    default:
        response += FAIL;
        break;
    }
    if(pClient)
    {
        pClient->sendTextMessage(response);
    }
}


QString Server::onAuthorization(QString login, QString password)
{
    qDebug() << "Action: Authorization";

    /*Go to database and check user
    *  if user password is correct send SUCCESS and users rigths: admin, simple user or advanced user
    *  otherwise send FAIL
    */
    QString result = SUCCESS + "|";
    result += QString::number(Admin);
    return result;
}


QString Server::onSeeHistory(QString username)
{
    qDebug() << "Action: See History";
    QString history;

    QFile file("D://project/history.txt");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Cann't open file of user's actions";
        history += FAIL;
        return history;
    }
    //read history to string
    history += SUCCESS  + "|";
    QTextStream in(&file);
    QStringList strings;
        while (!in.atEnd())
        {
            strings += in.readLine();
        }
    file.close();
    QList<QString>::iterator i;
    for (i = strings.begin(); i != strings.end(); ++i)
    {
        QStringList substrings = (*i).split("*");
        if(substrings.value(1) == username)
        {
            history += (*i) + "\n";
        }
    }
    return history;
}


QString Server::onAddUser(QString login, QString password, quint16 id)
{
    qDebug() << "Adding new user";
    return SUCCESS;
}


/*
* @brief					Process binary messages from users
*                           first byte of message is action that user wants to do
*                           next goes name of file that user wants to send
*                           then filesize
*                           next binary messages will be bytes of file
* @param	[QByteArray]    data - binary message
* @return	void
*/
void Server::processBinaryMessage(QByteArray data)
{
    QWebSocket* pClient = qobject_cast<QWebSocket* >(sender());
    if(!pClient)
    {
        qDebug() << "User disconnect";
        return;
    }

    QString filename = pClients[pClient];
    QString path = "D:\\" + filename;
    QFile file(path);
    if(!file.open(QIODevice::Append))
    {
        qDebug() << "Cann't open the file";
        return;
    }
    file.write(data, data.size());
    file.close();

    QStringList substrings = filename.split(".");
    QString response;
    if(substrings.value(substrings.length() -1 ).toLower() == "avi")
    {
        response = QString::number(sendVideo) + "|";
    }
    else
    {
        response = QString::number(addPicture) + "|";
    }
    response += SUCCESS;
    if(pClient)
    {
        pClient->sendTextMessage(response);
    }
}





