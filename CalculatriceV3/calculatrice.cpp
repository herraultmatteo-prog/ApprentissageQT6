#include "calculatrice.h"
#include "ui_calculatrice.h"
#include <QJSEngine>

Calculatrice::Calculatrice(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculatrice)
    , NB_TOUCHES(16)
{
    ui->setupUi(this);
    const QString tableDesSymboles[] = {"7", "8", "9", "+" ,"4", "5", "6", "-", "1", "2", "3", "*", "C", "0", "=", "/"};
    grille = new QGridLayout;
    afficheur = new QLineEdit;
    afficheur->setMinimumHeight(50);
    afficheur->setStyleSheet("background-color: rgb(143, 240, 164);");
    touches = new QPushButton*[NB_TOUCHES];
    grille->addWidget(afficheur,0,0,1,4);
    this->setLayout(grille);


    for (int i = 0; i < NB_TOUCHES; ++i) {

        touches[i] = new QPushButton(this);
        touches[i]->setText(tableDesSymboles[i]);
        touches[i]->setMinimumHeight(50);
        touches[i]->setMinimumWidth(50);
        touches[i]->setMaximumHeight(50);
        touches[i]->setMaximumWidth(50);
        layout()->addWidget(touches[i]);
    }

    QList<QPushButton*> allButtons = this->findChildren<QPushButton*>();
    foreach(QPushButton* button, allButtons) {
    connect(button, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
    }
}

Calculatrice::~Calculatrice()
{
    delete ui;
}


void Calculatrice::onQPushButtonClicked()
{
    QPushButton *touche;
    touche=qobject_cast<QPushButton*>(sender());

    /**
     * @brief expression
     * recupere le texte de l'afficheur
     */
    QString expression = afficheur->text();

    QString texteTouche;
    texteTouche = touche->text();

    if(texteTouche != "C" && texteTouche != "=")
    {
        afficheur->setText(expression + texteTouche);
    }
    if(texteTouche == "C"){
        afficheur->clear();
    }

    if(texteTouche == "="){
        QJSEngine calcul;
        QJSValue resultat = calcul.evaluate(expression);
        afficheur->setText(resultat.toString());
    }
}

