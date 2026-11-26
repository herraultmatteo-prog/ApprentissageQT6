#ifndef CODE_H
#define CODE_H

#include <QtGlobal>

using namespace std;

class Code
{
public:
    Code(const int taillCode);
    ~Code();
    bool VerifierCode(const quint8 *unCode);
    void Memoriser(const quint8 *unCode);
private:
    quint8 *codeUsine;
    quint8 *codeUtilisateur;
    int tailleCode;
};

#endif // CODE_H
