#include <QDebug>

#include "clavier.h"

CentraleDalarme::CentraleDalarme(const int _tailleCode, QObject *parent) :
    QObject(parent),
    tailleCode(_tailleCode),
    indiceCourant(0)
{
    combinaison = new quint8[tailleCode];
    int i = 0;

    for (i = 0 ;i < tailleCode; i++)
        combinaison[i] = 0;

    leClavier = new Clavier(this);
    leClavier->show();
}

CentraleDalarme::~CentraleDalarme()
{
    delete[] combinaison;
    delete leClavier;
}

void CentraleDalarme::FabriquerCode(const quint8 chiffre)
{

    if (indiceCourant < tailleCode) {
        combinaison[indiceCourant] = chiffre;
        indiceCourant++;
    }
    else {
        for (int i = 0; i < tailleCode - 1 ; i++){
            combinaison[i] = combinaison[i + 1];
        }
        combinaison[tailleCode - 1] = chiffre;
    }

}

void CentraleDalarme::ModifierCode()
{
    if(indiceCourant == tailleCode)
    {
        mode = MODIFICATION_CODE;
        emit EtatCentraleChange(mode);
    }
}

void CentraleDalarme::TraiterBoutonMarche()
{
    if(indiceCourant == tailleCode)
    {
        if(leCode->VerifierCode(combinaison)){
            mode = ACTIVATION;
            emit EtatCentraleChange(mode);
            timerDelai.start(5000);
        }
    }
}

void CentraleDalarme::Activer()
{

}

void CentraleDalarme::Desactiver()
{

}

void CentraleDalarme::TraiterBoutonArret()
{
    if(indiceCourant == tailleCode)
    {
        if(leCode->VerifierCode(combinaison)){
            mode = DESACTIVATION;
            emit EtatCentraleChange(mode);
        }
    }
}

void CentraleDalarme::onTimerDelai_timeout()
{

}

void CentraleDalarme::onIntrusDetecte()
{

}

