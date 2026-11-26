#ifndef CALCULATRICE_H
#define CALCULATRICE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculatrice;
}
QT_END_NAMESPACE

class Calculatrice : public QWidget
{
    Q_OBJECT

public:
    explicit Calculatrice(QWidget *parent = nullptr);
    ~Calculatrice() override;

private slots:
    void onQPushButtonClicked();

private:
    Ui::Calculatrice *ui;
    int NB_TOUCHES;
    QPushButton **touches;
    QLineEdit *afficheur;
    QGridLayout *grille;
};
#endif // CALCULATRICE_H
