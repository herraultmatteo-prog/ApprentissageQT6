#include "detecteurtemporise.h"
#include <QMessageBox>

DetecteurTemporise::DetecteurTemporise(QWidget *parent) :
    Detecteur(parent)
{

    setWindowTitle("détecteur temporisé");
    connect(&timerIntrus,&QTimer::timeout,this,&DetecteurTemporise::onTimerIntrus_timeout);
}

DetecteurTemporise::~DetecteurTemporise()
{
    timerIntrus.stop();
}

void DetecteurTemporise::LancerTempo()
{
    timerIntrus.setSingleShot(true);
    timerIntrus.start(3000);
}

void DetecteurTemporise::onTimerIntrus_timeout()
{
    QMessageBox messageMarche;
    messageMarche.setText(" Intrus a été détecté ");
    messageMarche.exec();
}

void DetecteurTemporise::on_pushButtonIntrus_clicked()
{
    LancerTempo();
}


