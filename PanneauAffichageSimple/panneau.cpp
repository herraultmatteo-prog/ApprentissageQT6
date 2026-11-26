#include "panneau.h"
#include "ui_panneau.h"

Panneau::Panneau(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Panneau)
{
    ui->setupUi(this);
    socketClient = new QUdpSocket(this);

    if (socketClient->bind(45454, QUdpSocket::ShareAddress)) {
        connect(socketClient, &QUdpSocket::readyRead, this, &Panneau::RecevoirMessage);
        qDebug() << "Client prêt à recevoir des messages sur le port 45454";
    } else {
        qDebug() << "Erreur de liaison du client au port 45454";
    }

    // if (socketClient->bind(45454, QUdpSocket::ShareAddress)) {
    //     if (socketClient->joinMulticastGroup(QHostAddress("224.0.1.1"))) {
    //         connect(socketClient, &QUdpSocket::readyRead, this, &Panneau::RecevoirMessage);
    //         qDebug() << "Client rejoint le groupe multicast et est prêt à recevoir des messages";
    //     } else {
    //         qDebug() << "Erreur : impossible de rejoindre le groupe multicast";
    //     }
    // } else {
    //     qDebug() << "Erreur de liaison du client au port 45454";
    // }
}

Panneau::~Panneau()
{
    delete ui;
    delete socketClient;
}

void Panneau::RecevoirMessage()
{
    // while (socketClient->hasPendingDatagrams()) {
    //     QByteArray buffer;
    //     buffer.resize(socketClient->pendingDatagramSize());
    //     socketClient->readDatagram(buffer.data(), buffer.size());
    //     ui->textEditMessage->append(QString::fromUtf8(buffer));
    // }

    while (socketClient->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = socketClient->receiveDatagram();
        QByteArray buffer = datagram.data();
        char type;
        QString message;
        QDataStream in(&buffer, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_6_10);
        in >> type >> message;
        qDebug() << "Type : " << type << ", Message : " << message;
        switch (type) {
            case 'I':
                ui->textEditMessage->append(message);
                break;

            case 'M':
                ui->lineEditMeteo->setText(message);
                qDebug () << message;
                break;

            case 'H':
                ui->timeEditHeure->setTime(QTime::fromString(message, "HH:mm"));
                break;

            case 'A':
                ui->textEditMessage->setProperty("alerte", true);
                ui->textEditMessage->setStyleSheet("color: red; font-weight: bold;");
                ui->textEditMessage->setText(message);
                break;

        }
    }
}
