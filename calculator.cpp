#include "calculator.h"
#include "./ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calculator)
    , waitOperand(false)
{
    ui->setupUi(this);
    for (auto button : ui->digitButtonGroup->buttons()) {
        connect(button, &QPushButton::clicked, this, &Calculator::digitClicked);
    }
    for (auto button : ui->addOrSubGroup->buttons()) {
        connect(button, &QPushButton::clicked, this, &Calculator::addOrSubClicked);
    }
    for (auto button : ui->multOrDivGroup->buttons()) {
        connect(button, &QPushButton::clicked, this, &Calculator::multOrDivClicked);
    }
    connect(ui->clearButton, &QPushButton::clicked, this, &Calculator::clearClicked);
    connect(ui->equalButton, &QPushButton::clicked, this, &Calculator::equalClicked);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::digitClicked()
{
    auto display = ui->lineEdit;
    auto button = qobject_cast<QPushButton *>(sender());
    int digit_value = button->text().toInt();
    fprintf(stderr, "%d\n", digit_value);
    if (waitOperand) {
        display->clear();
        waitOperand = false;
    }
    display->setText(display->text() + QString::number(digit_value));
}

void Calculator::addOrSubClicked()
{
    auto currentDisplayDigit = ui->lineEdit->text().toDouble();
    digitStack.push_back(currentDisplayDigit);
    waitOperand = true;
}

void Calculator::multOrDivClicked()
{
    auto currentDisplayDigit = ui->lineEdit->text().toDouble();
    waitOperand = true;
}

void Calculator::clearClicked()
{
    ui->lineEdit->clear();
    digitStack.clear();
}

void Calculator::equalClicked()
{
    auto currentDisplayDigit = ui->lineEdit->text().toDouble();
    digitStack.push_back(currentDisplayDigit);

    double result = 0.0;
    for (const auto digit : digitStack) {
        result += digit;
    }
    ui->lineEdit->setText(QString::number(result));
}
