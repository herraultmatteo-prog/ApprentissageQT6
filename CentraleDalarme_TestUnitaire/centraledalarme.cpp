#include <QDebug>
#include "centraledalarme.h"
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
        for (int i = 0; i < tailleCode ; i++){
            combinaison[i] = combinaison[i + 1];
        }
        combinaison[tailleCode - 1] = chiffre;
    }

}
