#include "code.h"

Code::Code(const int taillCode):
    tailleCode(taillCode)
{
    codeUtilisateur = new quint8[tailleCode];
    codeUsine = new quint8[tailleCode];

    for (int i = 0; i < tailleCode; i++) {
        codeUtilisateur[i] = 0;
        codeUsine[i] = i + 1;
    }

}

Code::~Code()
{
    delete[] codeUtilisateur;
    delete[] codeUsine;
}

bool Code::VerifierCode(const quint8 *unCode)
{
    int i = 0;
    bool CodeValide = true;

    while (i < tailleCode && CodeValide) {
        if (unCode[i] != codeUtilisateur[i] && unCode[i] != codeUsine[i])
            CodeValide = false ;
        i++;
    }
    return CodeValide;
}

void Code::Memoriser(const quint8 *unCode)
{
    for(int i = 0 ; i < tailleCode ; i++)
        codeUtilisateur[i] = unCode[i];

}
