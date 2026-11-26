#include <iostream>
#include <QtGlobal>
#include <QDebug>
#include "code.h"

using namespace std;

#define TAILLE_CODE 4

int main()
{
    Code monCode(TAILLE_CODE);
    quint8 code[TAILLE_CODE];
    quint8 nouveauCode[TAILLE_CODE];
    int option;
    int i = 0;
    int index = 0;
    int saisie;

    cout << "Entrez un code Valide a 4 chiffre svp " << endl;
    while (i < TAILLE_CODE) {
        cin >> saisie;
        code[i] = saisie;
        i++;
    }

    qDebug() << "tableau saisi " << code[0] << code[1] << code[2] << code[3] ;


    if (monCode.VerifierCode(code)) {
        qDebug() << "entre dans le if";
        cout << "Code valide" << endl;

    } else {
        qDebug() << "entre dans le else";
        cout << "Code invalide" << endl;
    }

    index = 0;

    cout << "Voulez vous modifier le code :" << endl;
    cout << "1 pour oui" << endl;
    cout << "2 pour non" << endl;
    cin >> option;

    if(option == 1) {
        cout << "Veilliez entrer le nouveau code" << endl;
        while (index< TAILLE_CODE) {
            cin >> saisie;
            nouveauCode[index] = saisie;
            index++;

        }
        monCode.Memoriser(nouveauCode);
        cout << "Le code a bien était modifié" << endl;
    }
    else
        cout << "Le code n'est pas modifié" << endl;


    return 0;
}

