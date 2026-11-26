#include "auditserveurwidget.h"
#include "ui_auditserveurwidget.h"

AuditServeurWidget::AuditServeurWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuditServeurWidget)
{
    ui->setupUi(this);
    socketEcouteServeur = new QTcpServer();

    connect(socketEcouteServeur, &QTcpServer::newConnection, this, &AuditServeurWidget::onQTcpServer_NewConnection);

}

AuditServeurWidget::~AuditServeurWidget()
{
    delete ui;
}

void AuditServeurWidget::on_pushButtonLancerServeur_clicked()
{

    quint16 port = ui->lineEditPort->text().toInt();

    if(!socketEcouteServeur->listen(QHostAddress::Any, port))
        ui->textEditInformations->append( "Echec au lancement du serveur : " + socketEcouteServeur->errorString());
    else
        ui->textEditInformations->append( "Serveur lancé sur le port : " + QString::number(port));
}

void AuditServeurWidget::onQTcpServer_NewConnection()
{
    QTcpSocket *client = socketEcouteServeur->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &AuditServeurWidget::onQTcpSocket_readyRead);
    connect(client, &QTcpSocket::disconnected, this, &AuditServeurWidget::onQTcpSocket_disconnected);
    connect(client, &QTcpSocket::errorOccurred, this, &AuditServeurWidget::onQTcpSocketErrorOccured);


    lesClients.append(client);
    QProcess *process = new QProcess();
    connect(process, &QProcess::readyReadStandardOutput, this, &AuditServeurWidget::onQProcess_readyReadStandardOutput);
    lesProcess.append(process);

    ui->textEditInformations->append("Client connecté");
}

void AuditServeurWidget::onQTcpSocket_readyRead()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (client)
    {
        int indexProcess = lesClients.indexOf(client);
        QByteArray data = client->readAll();
        ui->textEditInformations->append("Données reçues : " + QString(data));

        QString reponse;
        switch (data[0])
        {
        case 'u':
            reponse = getenv("USER"); // sous Windows USERNAME
            client->write(reponse.toLatin1());
            break;

        case 'c':
            reponse = QHostInfo::localHostName();
            client->write(reponse.toLatin1());
            break;

        case 'o':
            if (indexProcess != -1)
                lesProcess.at(indexProcess)->start("uname", QStringList("-o"));
            break;

        case 'a':
            if (indexProcess != -1)
                lesProcess.at(indexProcess)->start("uname", QStringList("-p"));
            break;
        }
    }
}

void AuditServeurWidget::onQTcpSocket_disconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (client)
    {
        int index = lesClients.indexOf(client);
        if (index != -1)
        {
            QProcess *process = lesProcess.at(index);
            lesProcess.removeAt(index);
            process->deleteLater();

            lesClients.removeAt(index);
        }
        client->deleteLater();
        ui->textEditInformations->append("Client déconnecté");
    }
}

void AuditServeurWidget::onQTcpSocketErrorOccured(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (client)
        ui->textEditInformations->append(client->errorString());
}

void AuditServeurWidget::onQProcess_readyReadStandardOutput()
{
    QProcess *process = qobject_cast<QProcess*>(sender());
    if (process)
    {
        int indexClient = lesProcess.indexOf(process);
        QString reponse = process->readAllStandardOutput();

        if (!reponse.isEmpty() && indexClient != -1)
            lesClients.at(indexClient)->write(reponse.toLatin1());
    }
}

