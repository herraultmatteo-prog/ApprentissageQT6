#ifndef CENTRALEDALARME_H
#define CENTRALEDALARME_H

#include <QObject>
#include <QTimer>
// #include "clavier.h"
#include "detecteur.h"
#include "detecteurtemporise.h"
#include "code.h"

class Clavier;



class CentraleDalarme : public QObject
{
    Q_OBJECT

public:

    enum MODES_DE_MARCHE {
        REPOS,
        MODIFICATION_CODE,
        SAISIE_NOUVEAU,
        SURVEILLANCE,
        ACTIVATION,
        DESACTIVATION
    };

    explicit CentraleDalarme(const int _tailleCode = 4, QObject *parent = nullptr);
    ~CentraleDalarme();
    void FabriquerCode(const quint8 chiffre);
    void ModifierCode();
    void TraiterBoutonMarche();
    void Activer();
    void Desactiver();
    void TraiterBoutonArret();

signals:
    void EtatCentraleChange(CentraleDalarme::MODES_DE_MARCHE _nouvelEtat);

public slots:
    void onTimerDelai_timeout();
    void onIntrusDetecte();

private:
    const int tailleCode;
    quint8 *combinaison;
    int indiceCourant;
    MODES_DE_MARCHE mode;

    Clavier *leClavier;
    QTimer timerDelai;
    Detecteur *leDetecteur;
    DetecteurTemporise *leDetecteurTempo;
    Code *leCode;
};

#endif // CENTRALEDALARME_H
