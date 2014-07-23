/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *centralWidget;
    QTextEdit *resultTextBox;
    QWidget *authorization;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *login;
    QLineEdit *password;
    QPushButton *SIgnIn;
    QWidget *mainForm;
    QPushButton *LoadVideo;
    QLabel *fileName;
    QPushButton *SendVideo;
    QTextBrowser *userHistory;
    QPushButton *seeHistory;
    QTextBrowser *videoResult;
    QFrame *adminFrame;
    QLineEdit *newLogin;
    QLineEdit *newPassword;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *addUser;
    QGroupBox *selectRigths;
    QRadioButton *simpleUser;
    QRadioButton *advancedUser;
    QRadioButton *admin;
    QFrame *advancUserFrame;
    QPushButton *loadPictures;
    QLabel *loadedPicture1;
    QPushButton *addPictures;
    QLabel *loadedPicture2;
    QLabel *loadedPicture3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QStringLiteral("Client"));
        Client->resize(485, 546);
        centralWidget = new QWidget(Client);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        resultTextBox = new QTextEdit(centralWidget);
        resultTextBox->setObjectName(QStringLiteral("resultTextBox"));
        resultTextBox->setGeometry(QRect(270, 470, 211, 21));
        authorization = new QWidget(centralWidget);
        authorization->setObjectName(QStringLiteral("authorization"));
        authorization->setGeometry(QRect(30, 10, 271, 81));
        label = new QLabel(authorization);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 51, 21));
        label_2 = new QLabel(authorization);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(0, 30, 61, 21));
        login = new QLineEdit(authorization);
        login->setObjectName(QStringLiteral("login"));
        login->setGeometry(QRect(60, 0, 113, 20));
        password = new QLineEdit(authorization);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(60, 30, 113, 20));
        SIgnIn = new QPushButton(authorization);
        SIgnIn->setObjectName(QStringLiteral("SIgnIn"));
        SIgnIn->setGeometry(QRect(180, 50, 75, 23));
        mainForm = new QWidget(centralWidget);
        mainForm->setObjectName(QStringLiteral("mainForm"));
        mainForm->setGeometry(QRect(50, 0, 371, 181));
        LoadVideo = new QPushButton(mainForm);
        LoadVideo->setObjectName(QStringLiteral("LoadVideo"));
        LoadVideo->setGeometry(QRect(30, 20, 75, 23));
        fileName = new QLabel(mainForm);
        fileName->setObjectName(QStringLiteral("fileName"));
        fileName->setEnabled(false);
        fileName->setGeometry(QRect(120, 30, 46, 13));
        SendVideo = new QPushButton(mainForm);
        SendVideo->setObjectName(QStringLiteral("SendVideo"));
        SendVideo->setGeometry(QRect(250, 20, 75, 23));
        userHistory = new QTextBrowser(mainForm);
        userHistory->setObjectName(QStringLiteral("userHistory"));
        userHistory->setGeometry(QRect(170, 120, 201, 51));
        seeHistory = new QPushButton(mainForm);
        seeHistory->setObjectName(QStringLiteral("seeHistory"));
        seeHistory->setGeometry(QRect(30, 130, 75, 23));
        videoResult = new QTextBrowser(mainForm);
        videoResult->setObjectName(QStringLiteral("videoResult"));
        videoResult->setGeometry(QRect(170, 50, 201, 51));
        adminFrame = new QFrame(centralWidget);
        adminFrame->setObjectName(QStringLiteral("adminFrame"));
        adminFrame->setGeometry(QRect(50, 180, 371, 161));
        adminFrame->setFrameShape(QFrame::NoFrame);
        adminFrame->setFrameShadow(QFrame::Plain);
        adminFrame->setLineWidth(1);
        newLogin = new QLineEdit(adminFrame);
        newLogin->setObjectName(QStringLiteral("newLogin"));
        newLogin->setGeometry(QRect(80, 10, 113, 20));
        newPassword = new QLineEdit(adminFrame);
        newPassword->setObjectName(QStringLiteral("newPassword"));
        newPassword->setGeometry(QRect(80, 40, 113, 20));
        label_3 = new QLabel(adminFrame);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 10, 46, 13));
        label_4 = new QLabel(adminFrame);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 40, 46, 13));
        addUser = new QPushButton(adminFrame);
        addUser->setObjectName(QStringLiteral("addUser"));
        addUser->setGeometry(QRect(240, 60, 75, 23));
        selectRigths = new QGroupBox(adminFrame);
        selectRigths->setObjectName(QStringLiteral("selectRigths"));
        selectRigths->setGeometry(QRect(10, 70, 121, 91));
        simpleUser = new QRadioButton(selectRigths);
        simpleUser->setObjectName(QStringLiteral("simpleUser"));
        simpleUser->setGeometry(QRect(10, 20, 82, 17));
        advancedUser = new QRadioButton(selectRigths);
        advancedUser->setObjectName(QStringLiteral("advancedUser"));
        advancedUser->setGeometry(QRect(10, 40, 101, 17));
        admin = new QRadioButton(selectRigths);
        admin->setObjectName(QStringLiteral("admin"));
        admin->setGeometry(QRect(10, 60, 82, 17));
        advancUserFrame = new QFrame(centralWidget);
        advancUserFrame->setObjectName(QStringLiteral("advancUserFrame"));
        advancUserFrame->setGeometry(QRect(50, 350, 361, 81));
        advancUserFrame->setFrameShape(QFrame::NoFrame);
        advancUserFrame->setFrameShadow(QFrame::Plain);
        loadPictures = new QPushButton(advancUserFrame);
        loadPictures->setObjectName(QStringLiteral("loadPictures"));
        loadPictures->setGeometry(QRect(10, 30, 75, 23));
        loadedPicture1 = new QLabel(advancUserFrame);
        loadedPicture1->setObjectName(QStringLiteral("loadedPicture1"));
        loadedPicture1->setGeometry(QRect(120, 0, 81, 21));
        addPictures = new QPushButton(advancUserFrame);
        addPictures->setObjectName(QStringLiteral("addPictures"));
        addPictures->setGeometry(QRect(240, 30, 75, 23));
        loadedPicture2 = new QLabel(advancUserFrame);
        loadedPicture2->setObjectName(QStringLiteral("loadedPicture2"));
        loadedPicture2->setGeometry(QRect(120, 30, 81, 16));
        loadedPicture3 = new QLabel(advancUserFrame);
        loadedPicture3->setObjectName(QStringLiteral("loadedPicture3"));
        loadedPicture3->setGeometry(QRect(120, 50, 91, 21));
        Client->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Client);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 485, 21));
        Client->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Client);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Client->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Client);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Client->setStatusBar(statusBar);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", 0));
        label->setText(QApplication::translate("Client", "Login", 0));
        label_2->setText(QApplication::translate("Client", "Password", 0));
        SIgnIn->setText(QApplication::translate("Client", "Sign In", 0));
        LoadVideo->setText(QApplication::translate("Client", "load video", 0));
        fileName->setText(QApplication::translate("Client", "fileName", 0));
        SendVideo->setText(QApplication::translate("Client", "send video", 0));
        seeHistory->setText(QApplication::translate("Client", "History", 0));
        label_3->setText(QApplication::translate("Client", "Login", 0));
        label_4->setText(QApplication::translate("Client", "Password", 0));
        addUser->setText(QApplication::translate("Client", "Add User", 0));
        selectRigths->setTitle(QApplication::translate("Client", "user rigths", 0));
        simpleUser->setText(QApplication::translate("Client", "simple user", 0));
        advancedUser->setText(QApplication::translate("Client", "advanced user", 0));
        admin->setText(QApplication::translate("Client", "administrator", 0));
        loadPictures->setText(QApplication::translate("Client", "Load Picturse", 0));
        loadedPicture1->setText(QApplication::translate("Client", "TextLabel", 0));
        addPictures->setText(QApplication::translate("Client", "Add Pictures", 0));
        loadedPicture2->setText(QApplication::translate("Client", "TextLabel", 0));
        loadedPicture3->setText(QApplication::translate("Client", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
