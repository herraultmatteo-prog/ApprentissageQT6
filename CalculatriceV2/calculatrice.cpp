#include "calculatrice.h"
#include "ui_calculatrice.h"
#include <QJSEngine>

Calculatrice::Calculatrice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculatrice)
{
    ui->setupUi(this);
    // connect(ui->pushButton0,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButton1,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButton2,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButton3,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButton4,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButton5,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButton6,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButton7,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButton8,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButton9,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButtonAdditionner,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButtonDiviser,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButtonMultiplier,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);
    // connect(ui->pushButtonSoustraire,&QPushButton::clicked,this,&Calculatrice::onQPushButtonClicked);

    QList<QPushButton*> allButtons = this->findChildren<QPushButton*>();
    foreach(QPushButton* button, allButtons) {
        if(button->text() != "=" && button->text() != "C") {
            connect(button, &QPushButton::clicked, this, &Calculatrice::onQPushButtonClicked);
        }
    }
}

Calculatrice::~Calculatrice()
{
    delete ui;
}

void Calculatrice::onQPushButtonClicked()
{
    /*
    QString expression = ui->lineEditAfficheur->text();
    expression += "0";
    ui->lineEditAfficheur->setText(expression);
    */

    QPushButton *touche;
    touche=qobject_cast<QPushButton*>(sender());
    QString expression = ui->lineEditAfficheur->text();
    expression += touche->text();
    ui->lineEditAfficheur->setText(expression);
}

void Calculatrice::on_pushButtonEgal_clicked()
{
    QString expression = ui->lineEditAfficheur->text();
    QJSEngine calcul;
    QJSValue resultat = calcul.evaluate(expression);
    ui->lineEditAfficheur->setText(resultat.toString());
}


void Calculatrice::on_pushButtonEffacer_clicked()
{
    ui->lineEditAfficheur->clear();
}

