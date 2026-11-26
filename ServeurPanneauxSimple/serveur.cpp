#include "serveur.h"
#include "ui_serveur.h"
#include <QMessageBox>

Serveur::Serveur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Serveur)
    ,datagram(QByteArray(), QHostAddress::Broadcast, 45454)
{
    ui->setupUi(this);
    socketServeur = new QUdpSocket(this);
    timerInformation = new QTimer(this);
    timerHeure = new QTimer(this);

    indexMessage = 0;
    alerte = false;
    alternanceAlerte = false;

    connect(timerInformation, &QTimer::timeout, this, &Serveur::onTimerInformation_timeout);
    connect(timerHeure, &QTimer::timeout, this, &Serveur::onTimerHeure_timeout);
}

Serveur::~Serveur()
{
    delete ui;
}

void Serveur::on_pushButtonDiffuser_clicked()
{
    if (!timerInformation->isActive()) {


        timerInformation->start(10000);
        timerHeure->start(60000);
        ui->pushButtonDiffuser->setText("Arrêter la diffusion");
        onTimerHeure_timeout();
        onTimerInformation_timeout();

    } else {
        timerInformation->stop();
        timerHeure->stop();
        ui->pushButtonDiffuser->setText("Diffuser");
    }
}


void Serveur::on_pushButtonAjouterMessage_clicked()
{
    if (ui->textEditInformation->toPlainText() != "") {
        ui->listWidgetMessage->addItem(ui->textEditInformation->toPlainText());
        ui->textEditInformation->setText("");
    }
}


void Serveur::on_pushButtonCreerAlerte_clicked()
{
    if (alerte == false) {
        alerte = true;
        alternanceAlerte = true;
        ui->pushButtonCreerAlerte->setText("Supprimer l'alerte");
        onTimerInformation_timeout();
    } else {
        alerte = false;
        alternanceAlerte = false;
        ui->pushButtonCreerAlerte->setText("Créer une alerte");
        onTimerInformation_timeout();
    }
}


void Serveur::on_pushButtonSupprimerMessage_clicked()
{
    if (ui->listWidgetMessage->currentRow() != -1) {
        delete ui->listWidgetMessage->takeItem(ui->listWidgetMessage->currentRow());
    } else {
        QMessageBox::warning(this, "Erreur", "Aucun message sélectionné !");
    }
}


void Serveur::on_pushButtonModifierMeteo_clicked()
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_10);
    out << 'M' << ui->lineEditMeteo->text();
    EnvoyerDatagram(buffer);
}

void Serveur::onTimerInformation_timeout()
{
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_10);

    if (alerte == true && alternanceAlerte == true) {
        out << 'A' << ui->textEditAlerte->toPlainText();
        alternanceAlerte = false;
    } else {
        if (ui->listWidgetMessage->count() > 0) {
            if (indexMessage >= ui->listWidgetMessage->count()) {
                indexMessage = 0;
            }
            out << 'I' << ui->listWidgetMessage->item(indexMessage)->text();
            indexMessage++;
        }
        if (alerte == true) {
            alternanceAlerte = true;
        }
    }

    EnvoyerDatagram(buffer);
}

void Serveur::onTimerHeure_timeout()
{
    QTime heure = QTime::currentTime();
    QByteArray buffer;
    QDataStream out(&buffer, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_10);
    out << 'H' << heure.toString("HH:mm");
    EnvoyerDatagram(buffer);
}

void Serveur::LancerTimerHeure()
{
    onTimerHeure_timeout();

    int msAvantProchaineMinute = (60 - QTime::currentTime().second()) * 1000;

    QTimer::singleShot(msAvantProchaineMinute, this, [this]() {
        if (timerInformation->isActive()) {
            onTimerHeure_timeout();
            timerHeure->start(60000);
        }
    });
}

void Serveur::EnvoyerDatagram(const QByteArray data)
{
    datagram.setData(data); // Configure les données à envoyer
    if (socketServeur->writeDatagram(datagram) == -1) {
        qDebug() << "Erreur lors de l'envoi du datagram :" << socketServeur->errorString();
    } else {
        qDebug() << "Datagram envoyé avec succès : " << data;
    }
}


