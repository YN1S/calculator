#include "calcui.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

CalcUI::CalcUI(QWidget *parent)
    : QWidget(parent)
{
    const int countRowButton = 5;
    const int countColButton = 4;

    _displaySolving = new QLineEdit;
    _displaySolving->setReadOnly(true);
    _displaySolving->setText(0);
    _displaySolving->setAlignment(Qt::AlignRight);
    _displaySolving->setStyleSheet("QLineEdit { font-size: 18pt}");
    _displaySolving->setMinimumSize(150, 50);

    _displayPreviusValue = new QLabel;
    _displayPreviusValue->setText(0);
    _displayPreviusValue->setAlignment(Qt::AlignRight);

    QChar buttons[countRowButton][countColButton] =
        {{'C', ' ', '%', '/'},
         {'7', '8', '9', '*'},
         {'4', '5', '6', '-'},
         {'1', '2', '3', '+'},
         {'0', ' ', '.', '='} };

    QGridLayout* pUIGridLayout = new QGridLayout;
    pUIGridLayout->addWidget(_displaySolving, 0, 0, 1, 4);
    pUIGridLayout->addWidget(_displayPreviusValue, 1, 0, 1, 4);

    for(int row = 0; row < countRowButton; ++row)
    {
        for(int col = 0; col < countColButton; ++col)
        {
            if(buttons[row][col] == '0' || buttons[row][col] == 'C')
            {
                pUIGridLayout->addWidget(createButton(buttons[row][col]), row + 2, col, 1, 2);
                continue;
            }
            if(buttons[row][col] == ' ') continue;
            pUIGridLayout->addWidget(createButton(buttons[row][col]), row + 2, col);
        }
    }

    setLayout(pUIGridLayout);
}

QPushButton *CalcUI::createButton(const QChar &str)
{
    QPushButton* pcmd = new QPushButton{str};
    pcmd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(pcmd, &QPushButton::clicked, this, &CalcUI::mySlot);
    buttonAndState.insert({pcmd, stateOfButton(str)});
    return pcmd;
}

state CalcUI::stateOfButton(const QChar &str)
{
    switch(str.unicode())
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return inputSign;
    case '=':
        return inputEqual;
    case 'C':
        return inputErase;
    case '.':
        return inputDot;
    case '%':
        return inputPercent;
    default:
        return inputNumber;
    }
}

void CalcUI::mySlot()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    if(button)
    {
        QString letter = button->text();
        _displaySolving->setText(logic.calculator(letter.at(0), buttonAndState[button]));
        _displayPreviusValue->setText(logic.getPreviusValues());
    }
}



