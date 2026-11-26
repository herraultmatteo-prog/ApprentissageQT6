#ifndef PANNEAU_H
#define PANNEAU_H

#include <QWidget>
#include <QUdpSocket>
#include <QNetworkDatagram>

QT_BEGIN_NAMESPACE
namespace Ui {
class Panneau;
}
QT_END_NAMESPACE

class Panneau : public QWidget
{
    Q_OBJECT

public:
    explicit Panneau(QWidget *parent = nullptr);
    ~Panneau() override;

private slots:
    void RecevoirMessage();

private:
    Ui::Panneau *ui;
    QUdpSocket *socketClient;
};
#endif // PANNEAU_H
