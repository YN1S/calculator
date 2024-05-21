#include "calcui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcUI calculator;

    calculator.show();

    return a.exec();
}
