#include "client.h"
#include "ui_client.h"
#include <QtCore/QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QVariant>


QT_USE_NAMESPACE

Client::Client(const QUrl &_url, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client),
    url(_url),
    sendedData(0),
    filesize(0),
    i(0)
{
     ui->setupUi(this);

     ui->mainForm->setVisible(false);
     ui->adminFrame->setVisible(false);
     ui->advancUserFrame->setVisible(false);
     ui->fileName->setText("");
     ui->loadedPicture1->setText("");
     ui->loadedPicture2->setText("");
     ui->loadedPicture3->setText("");

     connect(&webSocket, &QWebSocket::connected, this, &Client::onConnected);
     webSocket.open(QUrl(_url));
}


Client::~Client()
{
    webSocket.close();
    delete ui;
}


void Client::onConnected()
{
    ui->resultTextBox->setText("WebSocket connected");

    connect(&webSocket, &QWebSocket::textMessageReceived,
            this, &Client::onTextMessageReceived);
}


void Client::sendTextMessage(QString _message)
{
    webSocket.sendTextMessage(_message);
}


void Client::onTextMessageReceived(QString message)
{
    ui->resultTextBox->setText(message);

    /*Process server's response
     *  first character represent the user's action
     *  second server's result of action */
    QStringList substrings = message.split("|") ;
    if(substrings.length() == 1)
    {
     QMessageBox::information(this, tr("Error"), tr("Error occurs while trying to proccess request"));
     return;
    }


    switch(message[0].digitValue())
    {
    case authorization:
    {
        QString result = substrings.value(substrings.length()- 2 );

        if(result == SUCCESS)
        {
            ui->resultTextBox->setText("Authorization succeed");
            //check user's type
            ui->authorization->setVisible(false);
            ui->mainForm->setVisible(true);
        }
        else
        {
            QMessageBox::information(this, tr("Error"), tr("Authorization failed. Please check login and password"));
            return;
        }

        QString userRigths = substrings.value(substrings.length()- 2 );

        if(userRigths == QString::number(Admin))
      {
          ui->adminFrame->setVisible(true);
          ui->advancUserFrame->setVisible(true);
      }
      else if(userRigths == QString::number(AdvancedUser))
      {
          ui->advancUserFrame->setVisible(true);
       }
      }
    break;

    case seeHistory:
    {
        QString result = substrings.value(substrings.length()- 2 );
        if(result == SUCCESS)
        {
            QString result = substrings.value(substrings.length()- 1 );
            result.replace("*", " ");
            ui->userHistory->setText(result);
        }
        else
        {
            QMessageBox::information(this, tr("Error"), tr("Cann't load history. Please contact to developers to fix the problem."));
        }
     }
        break;



    case sendVideo:
    {
        ui->resultTextBox->setText(message);
        QString result = substrings.value(substrings.length()- 1 );
        if(result == SUCCESS)
        {
            on_SendVideo_clicked();
        }
        else
        {
            QMessageBox::information(this, tr("Error"), tr("Server cann't receive video/picture at the moment"));
        }
     }
        break;

    case addPicture:
    {
        ui->resultTextBox->setText(message);
        QString result = substrings.value(substrings.length()- 1 );
        if(result == SUCCESS)
        {
            on_addPictures_clicked();
        }
        else
        {
            QMessageBox::information(this, tr("Error"), tr("Server cann't receive video/picture at the moment"));
        }
     }
        break;

    case addUser:
    {
        QString result = substrings.value(substrings.length()- 1 );
        if(result == SUCCESS)
        {
            QMessageBox::information(this, tr("Message"), tr("New user was successfully added"));
        }
        else
        {
            QMessageBox::information(this, tr("Warning"), tr("User with this login already exist"));
        }
     }
        break;

     /*if server doesn't support user's request*/
    default:
        QMessageBox::information(this, tr("Error"), tr("Error occurs while trying to proccess request"));
        return;
    }
 }


void Client::on_SIgnIn_clicked()
{
    if(ui->login->text() != "" && ui->password->text()!= "")
    {
        message = QString::number(authorization) + "|";
        login = ui->login->text();
        message += login + "|" + ui->password->text();
        sendTextMessage(message);
    }
    else
    {
        QMessageBox::information(this, tr("Warning"), tr("Please enter login and password"));
    }

}


void Client::on_LoadVideo_clicked()
{
    path = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "D://",
                "Video Files (*.avi);;"
                );

    if(path == NULL)
    {
        QMessageBox::information(this, tr("Error"), tr("File wasn't selected"));
        return;
    }

    QFile file(path);
    filesize = file.size();

    QStringList substrings = path.split("/");
    QString filename = substrings.value(substrings.length() - 1);

    ui->fileName->setText(filename);

    QString request = QString::number(addPicture) + "|";
    request += filename;
    webSocket.sendTextMessage(request);
}


void Client::on_SendVideo_clicked()
{
    if(path == NULL)
    {
        QMessageBox::information(this, tr("Warning"), tr("Please choose file at first!"));
        return;
    }
    if(filesize == sendedData)
    {
        QMessageBox::information(this, tr("Notification"), tr("Video was successfully send"));
        return;
    }
    ui->fileName->setText("");
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Error"), tr("Cann't load file for reading!"));
        return;
    }
    file.seek(sendedData);
    QByteArray data = file.read(1048576);
    sendedData += (quint64) data.size();
    webSocket.sendBinaryMessage(data);
    file.close();
}


void Client::on_seeHistory_clicked()
{
    sendTextMessage(QString::number(seeHistory) + "|" + login);
}


void Client::on_addUser_clicked()
{
    QString request;
    request += QString::number(addUser) + "|";
    if(ui->newLogin->text() == "" || ui->newPassword->text() == "")
    {
        QMessageBox::information(this, tr("Warning"), tr("Please enter login and password!"));
        return;
    }
    else
    {
        request += ui->newLogin->text() + "|";
        request += ui->newPassword->text() + "|";
    }

    if(ui->simpleUser->isChecked())
    {
        request += QString::number(SimpleUser);
        ui->simpleUser->setAutoExclusive(false);
        ui->simpleUser->setChecked(false);
    }
    else if(ui->advancedUser->isChecked())
    {
        request += QString::number(AdvancedUser);
        ui->advancedUser->setAutoExclusive(false);
        ui->advancedUser->setChecked(false);
    }
    else if(ui->admin->isChecked())
    {
        request += QString::number(Admin);
        ui->admin->setAutoExclusive(false);
        ui->admin->setChecked(false);
    }
    else
    {
      QMessageBox::information(this, tr("Warning"), tr("Please choose user rigths!"));
      return;
    }

    sendTextMessage(request);

    ui->newLogin->setText("");
    ui->newPassword->setText("");

}


void Client::on_loadPictures_clicked()
{
    if(i == 3)
    {
        QMessageBox::information(this, tr("Warning"), tr("Sorry, you already choose three pictures!"));
        return;
    }
    ++i;
    picturePath[i] = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "F://",
                "Image Files (*.jpg)"
                );
    if(picturePath[i] == NULL)
    {
        QMessageBox::information(this, tr("Error"), tr("File wasn't selected"));
        return;
    }

    QStringList substrings = picturePath[i].split("/");
    QString filename = substrings.value(substrings.length() - 1);


    if(ui->loadedPicture1->text() == "")
    {
        ui->loadedPicture1->setText(filename);
        return;
    }
    else if(ui->loadedPicture2->text() == "")
    {
        ui->loadedPicture2->setText(filename);
        return;
    }
    else if(ui->loadedPicture3->text() == "")
    {
        ui->loadedPicture3->setText(filename);
        return;
    }
}


void Client::on_addPictures_clicked()
{
    if(i == 0)
    {
        ui->loadedPicture1->setText("");
        ui->loadedPicture2->setText("");
        ui->loadedPicture3->setText("");
        return;
    }

    if(ui->loadedPicture1->text() =="" || ui->loadedPicture2->text() == ""
            || ui->loadedPicture3->text() == "")
    {
        QMessageBox::information(this, tr("Warning"), tr("Please load three pictures!"));
        return;
    }
    QString request = QString::number(addPicture) + "|";
    QStringList substrings = picturePath[i].split("/");
    request += substrings.value(substrings.length() - 1 );
    webSocket.sendTextMessage(request);

    QFile file(picturePath[i]);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Warning"), tr("Cann't open picture!"));
    }
    QByteArray data = file.readAll();
    webSocket.sendBinaryMessage(data);
    --i;
}
