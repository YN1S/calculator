#ifndef CALCLOGIC_H
#define CALCLOGIC_H

#include <QString>
#include <map>
#include "state.h"

class CalcLogic
{
public:
    CalcLogic();

private:
    QString _firstNumber;
    QChar _sign;
    QString _secondNumber;

    QString _result {'0'};
    QString _previousValues;

    bool _dotHaveFirstNumber{false};
    bool _dotHaveSecondNumber{false};
    bool _isFirstNumber{true};

public:
    QString calculator(const QChar &str, const state &myState);
    void num(const QChar &str);
    void sign(const QChar& str);
    void dot();
    void equal();
    void clear();
    void percent();
    QString getPreviusValues();

};


#endif // CALCLOGIC_H
