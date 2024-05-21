#ifndef CALCUI_H
#define CALCUI_H

#include <QWidget>

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
    QLabel* _displayAnswer;

private: // Функции
    QPushButton* createButton(const QChar& str);

public slots:
    void mySlot();

};
#endif // CALCUI_H
