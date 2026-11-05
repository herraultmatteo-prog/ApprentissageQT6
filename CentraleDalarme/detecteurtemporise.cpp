#include "detecteurtemporise.h"
#include <QMessageBox>

DetecteurTemporise::DetecteurTemporise() {

    setWindowTitle("détecteur temporisé");
    connect(&TimerPresence,&QTimer::timeout,this,&DetecteurTemporise::onTimerPresence_timeout);
}

DetecteurTemporise::~DetecteurTemporise()
{
    TimerPresence.stop();
}

void DetecteurTemporise::on_pushButtonIntrus_clicked()
{
    TimerPresence.setSingleShot(true);
    TimerPresence.start(3000);
}

void DetecteurTemporise::onTimerPresence_timeout()
{
    QMessageBox messageMarche;
    messageMarche.setText(" Intrus a été détecté ");
    messageMarche.exec();
}


