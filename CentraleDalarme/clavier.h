#ifndef CLAVIER_H
#define CLAVIER_H

#include <QWidget>
#include <QTimer>
#include "detecteur.h"
#include "detecteurtemporise.h"
#include "centraledalarme.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Clavier;
}
QT_END_NAMESPACE

class Clavier : public QWidget
{
    Q_OBJECT

public:
    explicit Clavier(CentraleDalarme *_laCentrale, QWidget *parent = nullptr);
    ~Clavier() override;
    void LancerTempo();

public slots:
    void onEtatCentraleChange(CentraleDalarme::MODES_DE_MARCHE _etat);

private slots:
    void onTimerLed_timeout();
    void onQPushButtonClicked();

private:
    Ui::Clavier *ui;
    QTimer timerLed;
    QTimer timerClavier;
    CentraleDalarme *laCentrale;
    Detecteur *leDetecteur;
    DetecteurTemporise *leDetecteurTemp;
};
#endif // CLAVIER_H
