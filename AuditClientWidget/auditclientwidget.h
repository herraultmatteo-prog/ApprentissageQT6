#ifndef AUDITCLIENTWIDGET_H
#define AUDITCLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui {
class AuditClientWidget;
}
QT_END_NAMESPACE

class AuditClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AuditClientWidget(QWidget *parent = nullptr);
    ~AuditClientWidget() override;

private slots:
    void on_pushButtonConnexion_clicked();

    void on_pushButtonOrdinateur_clicked();

    void on_pushButtonUtilisateur_clicked();

    void on_pushButtonArchitecture_clicked();

    void on_pushButtonOs_clicked();

    void onQTcpSocketConnected();

    void onQTcpSocketDisconnected();

    void onQTcpSocketReadyRead();

    void onQTcpSocketErrorOccured(QAbstractSocket::SocketError socketError);

    void onQTcpSocketHostFound();

    void onQTcpSocketStateChanged(QAbstractSocket::SocketState SocketState);

    void onQTcpSocketAboutToClose();

    void onQTcpSocketBytesWritten(qint64 _bytes);

    void onQTcpSocketChannelBytesWritten(int _channel, qint64 _bytes);

    void onQTcpSocketChannelReadyRead(int _channel);

    void onQTcpSocketReadChannelFinished();

    void onQTcpSocketDestroyed(QObject *_obj);

private:
    Ui::AuditClientWidget *ui;
    QTcpSocket *socketClient;
    char typeDeDemande;
};
#endif // AUDITCLIENTWIDGET_H
