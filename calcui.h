#ifndef CALCUI_H
#define CALCUI_H

#include <QWidget>
#include <map>
#include "calclogic.h"
#include "state.h"

class QPushButton;
class QLabel;
class QLineEdit;

class CalcUI : public QWidget
{
    Q_OBJECT

public:
    CalcUI(QWidget *parent = nullptr);

private: // Переменные
    QLineEdit* _displaySolving;
    QLabel* _displayPreviusValue;

    std::map<QObject*, state> buttonAndState;

    CalcLogic logic;

private: // Функции
    QPushButton* createButton(const QChar& str);
    state stateOfButton(const QChar &str);

public slots:
    void mySlot();

};
#endif // CALCUI_H
