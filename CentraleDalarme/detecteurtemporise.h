#ifndef DETECTEURTEMPORISE_H
#define DETECTEURTEMPORISE_H

#include "detecteur.h"
#include <QTimer>

class DetecteurTemporise : public Detecteur
{
public:
    DetecteurTemporise();
    ~DetecteurTemporise();

private slots:
    virtual void on_pushButtonIntrus_clicked();
    void onTimerPresence_timeout();

private:
    QTimer TimerPresence;
};

#endif // DETECTEURTEMPORISE_H
