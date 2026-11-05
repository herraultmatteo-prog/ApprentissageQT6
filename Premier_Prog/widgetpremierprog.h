#ifndef WIDGETPREMIERPROG_H
#define WIDGETPREMIERPROG_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class WidgetPremierProg;
}
QT_END_NAMESPACE

class WidgetPremierProg : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetPremierProg(QWidget *parent = nullptr);
    ~WidgetPremierProg() override;

private slots:
    void on_dial_2_valueChanged(int value);

    void on_lineEditValeur_textChanged(const QString &arg1);

    void on_pushButtonDecoder_clicked();

private:
    Ui::WidgetPremierProg *ui;
};
#endif // WIDGETPREMIERPROG_H
