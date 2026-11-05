#include "widgetpremierprog.h"
#include "ui_widgetpremierprog.h"
#include <QDebug>

WidgetPremierProg::WidgetPremierProg(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetPremierProg)
{
    ui->setupUi(this);
}

WidgetPremierProg::~WidgetPremierProg()
{
    delete ui;
}

void WidgetPremierProg::on_dial_2_valueChanged(int value)
{
    ui->lineEditValeur->setText(QString::number(value));
}


void WidgetPremierProg::on_lineEditValeur_textChanged(const QString &arg1)
{
    ui->lcdNumberValeur->display(arg1);
    qDebug()<< arg1;
}


void WidgetPremierProg::on_pushButtonDecoder_clicked()
{
    QString texte = ui->lineEditADecoder->text();
    QStringList champs = texte.split(";");
    ui->lineEditNom->setText(champs.at(0));
    ui->lineEditPrenom->setText(champs.at(1));
    qDebug()<< champs;
}

