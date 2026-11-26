#include "clavier.h"
#include "ui_clavier.h"
#include <QMessageBox>

Clavier::Clavier(CentraleDalarme *_laCentrale, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Clavier)
    , laCentrale(_laCentrale)
{
    ui->setupUi(this);

    QList<QPushButton*> allButtons = this->findChildren<QPushButton*>();
    foreach(QPushButton* button, allButtons) {
        connect(button, &QPushButton::clicked, this, &Clavier::onQPushButtonClicked);
    }

    connect(&timerLed,&QTimer::timeout,this,&Clavier::onTimerLed_timeout);

    connect(laCentrale, &CentraleDalarme::EtatCentraleChange, this, &Clavier::onEtatCentraleChange);

    leDetecteur = nullptr;
    leDetecteurTemp = nullptr;
}

Clavier::~Clavier()
{
    delete ui;
}

void Clavier::LancerTempo()
{

}



void Clavier::onTimerLed_timeout()
{
    if(ui->checkBoxLedRouge->checkState() == Qt::Checked)
        ui->checkBoxLedRouge->setCheckState(Qt::Unchecked);
    else
        ui->checkBoxLedRouge->setCheckState(Qt::Checked);
}

void Clavier::onQPushButtonClicked()
{
    QPushButton *touche;
    touche=qobject_cast<QPushButton*>(sender());

    QString texteTouche;
    texteTouche = touche->text();

    if (texteTouche == "pushButtonMarche") {
        laCentrale->TraiterBoutonMarche();
    }
    else if (texteTouche == "pushButtonArret") {
        laCentrale->TraiterBoutonArret();
    }
}

void Clavier::onEtatCentraleChange(CentraleDalarme::MODES_DE_MARCHE _etat)
{
    switch(_etat) {

    case CentraleDalarme::REPOS:
        timerLed.stop();
        ui->checkBoxLedVerte->setCheckState(Qt::Unchecked);
        ui->checkBoxLedRouge->setCheckState(Qt::Unchecked);
        break;

    case CentraleDalarme::MODIFICATION_CODE:
        ui->checkBoxLedVerte->setCheckState(Qt::Checked);
        ui->checkBoxLedRouge->setCheckState(Qt::Checked);
        break;

    case CentraleDalarme::ACTIVATION:
        timerLed.start(250);
        break;

    case CentraleDalarme::DESACTIVATION:
        timerLed.start(250);
        break;

    case CentraleDalarme::SURVEILLANCE:
        ui->checkBoxLedVerte->setCheckState(Qt::Checked);
        ui->checkBoxLedRouge->setCheckState(Qt::Unchecked);
        break;

    }
}

