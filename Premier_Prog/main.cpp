#include "widgetpremierprog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetPremierProg w;
    w.show();
    return QApplication::exec();
}
