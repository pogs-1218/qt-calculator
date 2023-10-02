#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QPushButton>
#include <QWidget>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();
    void addOrSubClicked();
    void multOrDivClicked();
    void clearClicked();
    void equalClicked();

private:
    Ui::Calculator *ui;

    bool waitOperand;
    std::vector<double> digitStack;
};
#endif // CALCULATOR_H
