#ifndef SERVEUR_H
#define SERVEUR_H

#include <QWidget>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui {
class Serveur;
}
QT_END_NAMESPACE

class Serveur : public QWidget
{
    Q_OBJECT

public:
    explicit Serveur(QWidget *parent = nullptr);
    ~Serveur() override;


private slots:
    void on_pushButtonDiffuser_clicked();

    void on_pushButtonAjouterMessage_clicked();

    void on_pushButtonCreerAlerte_clicked();

    void on_pushButtonSupprimerMessage_clicked();

    void on_pushButtonModifierMeteo_clicked();

    void onTimerInformation_timeout();

    void onTimerHeure_timeout();

    void LancerTimerHeure();

    void EnvoyerDatagram(const QByteArray data);

private:
    Ui::Serveur *ui;
    QUdpSocket *socketServeur;
    QTimer *timerInformation;
    QTimer *timerHeure;
    QNetworkDatagram datagram;
    int indexMessage;
    bool alerte;
    bool alternanceAlerte;
};
#endif // SERVEUR_H
