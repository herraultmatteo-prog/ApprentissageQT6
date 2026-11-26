#include "auditserveurwidget.h"
#include "ui_auditserveurwidget.h"

AuditServeurWidget::AuditServeurWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuditServeurWidget)
{
    ui->setupUi(this);
    process = new QProcess;
    socketEcouteServeur = new QTcpServer;
    socketDialogueClient = new QTcpSocket;
    socketEcouteServeur = new QTcpServer();

    connect(socketEcouteServeur, &QTcpServer::newConnection, this, &AuditServeurWidget::onQTcpServer_NewConnection);
    connect(process, &QProcess::readyReadStandardOutput, this, &AuditServeurWidget::onQProcess_readyReadStandardOutput);
}

AuditServeurWidget::~AuditServeurWidget()
{
    delete ui;
}

void AuditServeurWidget::on_pushButtonLancerServeur_clicked()
{
    QByteArray donnees = socketDialogueClient->readAll();
    quint16 port = ui->lineEditPort->text().toInt();
    ui->textEditInformations->append("Message du client : " + QString(donnees));

    if(!socketEcouteServeur->listen(QHostAddress::Any, port))
        ui->textEditInformations->append( "Echec au lancement du serveur : " + socketEcouteServeur->errorString());
    else
        ui->textEditInformations->append( "Serveur lancé sur le port : " + QString::number(port));
}

void AuditServeurWidget::onQTcpServer_NewConnection()
{
    socketDialogueClient = socketEcouteServeur->nextPendingConnection();
    connect(socketDialogueClient, &QTcpSocket::readyRead, this, &AuditServeurWidget::onQTcpSocket_readyRead);
    connect(socketDialogueClient, &QTcpSocket::disconnected, this, &AuditServeurWidget::onQTcpSocket_disconnected);
    connect(socketDialogueClient, &QTcpSocket::errorOccurred, this, &AuditServeurWidget::onQTcpSocketErrorOccured);

    ui->textEditInformations->append("Client connecté");
}

void AuditServeurWidget::onQTcpSocket_readyRead()
{
    if (socketDialogueClient)
    {
        QByteArray data = socketDialogueClient->readAll();
        ui->textEditInformations->append("Données reçues : " + QString(data));

        QString reponse;
        switch (data[0])
        {
        case 'u':
            reponse = getenv("USER"); // sous Windows USERNAME
            socketDialogueClient->write(reponse.toLatin1());
            break;

        case 'c':
            reponse = QHostInfo::localHostName();
            socketDialogueClient->write(reponse.toLatin1());
            break;

        case 'o':
            process->start("uname",QStringList("-o"));
            break;

        case 'a':
            process->start("uname",QStringList("-p"));
            break;
        }
    }
}

void AuditServeurWidget::onQTcpSocket_disconnected()
{
    ui->textEditInformations->append("Client déconnecté");
    socketDialogueClient->deleteLater();
    socketDialogueClient = nullptr;
}

void AuditServeurWidget::onQTcpSocketErrorOccured(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    ui->textEditInformations->append(socketDialogueClient->errorString());
}

void AuditServeurWidget::onQProcess_readyReadStandardOutput()
{
    QString reponse = process->readAllStandardOutput();
    if(!reponse.isEmpty())
        socketDialogueClient->write(reponse.toLatin1());
}

