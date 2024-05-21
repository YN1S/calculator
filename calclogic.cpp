#include "calclogic.h"

CalcLogic::CalcLogic() {}

QString CalcLogic::calculator(const QChar &str, const state &myState)
{
    if(_result == "Error") clear();
    switch (myState)
    {
    case inputNumber: num(str); break;
    case inputSign: sign(str); break;
    case inputDot: dot(); break;
    case inputErase: clear(); break;
    case inputEqual: equal(); return _result;
    case inputPercent: percent();
    default: break;
    }

    _result = _firstNumber + _sign + _secondNumber;

    return _result;
}

void CalcLogic::num(const QChar &str)
{
    if (_isFirstNumber)
    {
        if (_firstNumber == '0')
            _firstNumber = str;
        else
            _firstNumber.push_back(str);
    }
    else
    {
        if (_secondNumber == '0')
            _secondNumber = str;
        else
            _secondNumber.push_back(str);
    }
}


void CalcLogic::sign(const QChar &str)
{
    if(_isFirstNumber && str == '-' && _firstNumber == "") _firstNumber.push_back('-');
    else if(_firstNumber != "" && _firstNumber != "-" && _secondNumber == "")
    {
        _sign = str;
        _isFirstNumber = false;
    }
}

void CalcLogic::dot()
{
    if(!_dotHaveFirstNumber && _isFirstNumber && !_firstNumber.isEmpty())
    {
        _firstNumber.push_back('.');
        _dotHaveFirstNumber = true;
    }
    else if(!_dotHaveSecondNumber && !_isFirstNumber && !_secondNumber.isEmpty())
    {
        _secondNumber.push_back('.');
        _dotHaveSecondNumber = true;
    }
}

void CalcLogic::equal()
{
    if(!_firstNumber.isEmpty() && !_secondNumber.isEmpty() && _sign != '\0')
    {
        _previousValues = _result;
        switch (_sign.unicode()) {
        case '+':
            _result = QString::number(_firstNumber.toDouble() + _secondNumber.toDouble());
            break;
        case '-':
            _result = QString::number(_firstNumber.toDouble() - _secondNumber.toDouble());
            break;
        case '*':
            _result = QString::number(_firstNumber.toDouble() * _secondNumber.toDouble());
            break;
        case '/':
            if (_secondNumber.toDouble() != 0)
                _result = QString::number(_firstNumber.toDouble() / _secondNumber.toDouble());
            else
                _result = "Error";  // Обработка деления на ноль
            break;
        default:
            _result = "Error";  // Обработка неизвестного оператора
            break;
        }

    _firstNumber = _result;
    _secondNumber.clear();
    _sign = '\0';
    _isFirstNumber = true;
    _dotHaveFirstNumber = _firstNumber.contains('.');
    _dotHaveSecondNumber = false;
    }
}

void CalcLogic::clear()
{
    _firstNumber.clear();
    _secondNumber.clear();
    _sign = '\0';
    _isFirstNumber = true;
    _dotHaveFirstNumber = false;
    _dotHaveSecondNumber = false;
    _result.clear();
}

void CalcLogic::percent()
{
    if(_isFirstNumber) _firstNumber = QString::number(_firstNumber.toDouble() / 100);
    else
    {
        switch(_sign.unicode())
        {
        case '/':
        case '*':
            _secondNumber = QString::number(_secondNumber.toDouble() / 100);
            break;
        case '+':
        case '-':
            _secondNumber = QString::number(_firstNumber.toDouble() * (_secondNumber.toDouble() / 100));
            break;
        }
    }
}

QString CalcLogic::getPreviusValues()
{
    return _previousValues;
}
