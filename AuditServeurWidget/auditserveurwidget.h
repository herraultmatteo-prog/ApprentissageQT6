#ifndef AUDITSERVEURWIDGET_H
#define AUDITSERVEURWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class AuditServeurWidget;
}
QT_END_NAMESPACE

class AuditServeurWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AuditServeurWidget(QWidget *parent = nullptr);
    ~AuditServeurWidget() override;

private slots:
    void on_pushButtonLancerServeur_clicked();
    void onQTcpServer_NewConnection();
    void onQTcpSocket_readyRead();
    void onQTcpSocket_disconnected();
    void onQTcpSocketErrorOccured(QAbstractSocket::SocketError socketError);
    void onQProcess_readyReadStandardOutput();

private:
    Ui::AuditServeurWidget *ui;
    QProcess *process;
    QTcpServer *socketEcouteServeur;
    QTcpSocket *socketDialogueClient;

};
#endif // AUDITSERVEURWIDGET_H
