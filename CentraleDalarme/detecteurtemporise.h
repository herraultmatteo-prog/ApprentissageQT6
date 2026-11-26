#ifndef DETECTEURTEMPORISE_H
#define DETECTEURTEMPORISE_H

#include "detecteur.h"
#include <QTimer>

class DetecteurTemporise : public Detecteur
{

public:
    explicit DetecteurTemporise(QWidget *parent = nullptr);
    ~DetecteurTemporise();
    void LancerTempo();

public slots:
    void onTimerIntrus_timeout();

protected slots:
    virtual void on_pushButtonIntrus_clicked();

private:
    QTimer timerIntrus;
};

#endif // DETECTEURTEMPORISE_H
