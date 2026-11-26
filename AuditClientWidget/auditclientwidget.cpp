#include "auditclientwidget.h"
#include "ui_auditclientwidget.h"

AuditClientWidget::AuditClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuditClientWidget)
{
    ui->setupUi(this);
    socketClient = new QTcpSocket;
    connect(socketClient,&QTcpSocket::connected, this,&AuditClientWidget::onQTcpSocketConnected);
    connect(socketClient,&QTcpSocket::disconnected, this,&AuditClientWidget::onQTcpSocketDisconnected);
    connect(socketClient,&QTcpSocket::readyRead, this,&AuditClientWidget::onQTcpSocketReadyRead);
    connect(socketClient,&QTcpSocket::errorOccurred, this,&AuditClientWidget::onQTcpSocketErrorOccured);
    connect(socketClient,&QTcpSocket::hostFound, this,&AuditClientWidget::onQTcpSocketHostFound);
    connect(socketClient,&QTcpSocket::stateChanged, this,&AuditClientWidget::onQTcpSocketStateChanged);
    connect(socketClient,&QTcpSocket::aboutToClose, this,&AuditClientWidget::onQTcpSocketAboutToClose);
    connect(socketClient,&QTcpSocket::bytesWritten, this,&AuditClientWidget::onQTcpSocketBytesWritten);
    connect(socketClient,&QTcpSocket::channelBytesWritten, this,&AuditClientWidget::onQTcpSocketChannelBytesWritten);
    connect(socketClient,&QTcpSocket::channelReadyRead, this,&AuditClientWidget::onQTcpSocketChannelReadyRead);
    connect(socketClient,&QTcpSocket::readChannelFinished, this,&AuditClientWidget::onQTcpSocketReadChannelFinished);
    connect(socketClient,&QTcpSocket::destroyed, this,&AuditClientWidget::onQTcpSocketDestroyed);

}

AuditClientWidget::~AuditClientWidget()
{
    delete ui;
    delete socketClient;
}

void AuditClientWidget::on_pushButtonConnexion_clicked()
{
    QString adresseIP = ui->lineEditAdresseIP->text();
    quint16 port = ui->lineEditPort->text().toInt();
    if (ui->pushButtonConnexion->text() == "Connexion") {

        ui->pushButtonConnexion->setText("Deconnexion");

        socketClient->connectToHost(adresseIP, port);
        ui->groupBoxInformationsClient->setEnabled(true);
        // ui->lineEditAdresseIP->setEnabled(false);
        // ui->lineEditPort->setEnabled(false);
    }
    else {

        ui->pushButtonConnexion->setText("Connexion");

        ui->groupBoxInformationsClient->setEnabled(true);
        // ui->lineEditAdresseIP->setEnabled(true);
        // ui->lineEditPort->setEnabled(true);

        socketClient->close();
    }

}


void AuditClientWidget::on_pushButtonOrdinateur_clicked()
{
    typeDeDemande= 'c';
    socketClient->write(&typeDeDemande,1);
}


void AuditClientWidget::on_pushButtonUtilisateur_clicked()
{
    typeDeDemande='u';
    socketClient->write(&typeDeDemande,1);
}


void AuditClientWidget::on_pushButtonArchitecture_clicked()
{
    typeDeDemande= 'a';
    socketClient->write(&typeDeDemande,1);
}


void AuditClientWidget::on_pushButtonOs_clicked()
{
    typeDeDemande='o';
    socketClient->write(&typeDeDemande,1);
}

void AuditClientWidget::onQTcpSocketConnected()
{
    ui->textEditEtat->append("Connecté au serveur");
}

void AuditClientWidget::onQTcpSocketDisconnected()
{
    ui->textEditEtat->append("Déconnecté du serveur");
}

void AuditClientWidget::onQTcpSocketReadyRead()
{
    ui->textEditEtat->append("Des données sont prêtes à être lues");

    if (socketClient){
        QByteArray data = socketClient->readAll();

        switch (typeDeDemande) {

        case 'c':
            ui->lineEditOrdinateur->setText(QString(data));
            break;

        case 'u':
            ui->lineEditUtilisateur->setText(QString(data));
            break;

        case 'a':
            ui->lineEditArchitecture->setText(QString(data));
            break;

        case 'o':
            ui->lineEditOs->setText(QString(data));
            break;
        }
    }
}

void AuditClientWidget::onQTcpSocketErrorOccured(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    ui->textEditEtat->append(socketClient->errorString());
}

void AuditClientWidget::onQTcpSocketHostFound()
{
    ui->textEditEtat->append("Hote trouvé");
}

void AuditClientWidget::onQTcpSocketStateChanged(QAbstractSocket::SocketState SocketState)
{
    ui->textEditEtat->append("Changement d'état");
}

void AuditClientWidget::onQTcpSocketAboutToClose()
{
    ui->textEditEtat->append("La socket va être fermée");
}

void AuditClientWidget::onQTcpSocketBytesWritten(qint64 _bytes)
{
    ui->textEditEtat->append(QString::number(_bytes) + " octets ont été écrits");
}

void AuditClientWidget::onQTcpSocketChannelBytesWritten(int _channel, qint64 _bytes)
{
    ui->textEditEtat->append(QString::number(_bytes) + " octets écrits sur le canal " + QString::number(_channel));
}

void AuditClientWidget::onQTcpSocketChannelReadyRead(int _channel)
{
    ui->textEditEtat->append("Données prêtes à être lues sur le canal " + QString::number(_channel));
}

void AuditClientWidget::onQTcpSocketReadChannelFinished()
{
    ui->textEditEtat->append("Fin de lecture du canal");
}

void AuditClientWidget::onQTcpSocketDestroyed(QObject *_obj)
{
    ui->textEditEtat->append("La socket a été détruite");
}

