#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QObject>

class Calculator : public QObject
{
    Q_OBJECT
public:
    explicit Calculator(QObject *parent = nullptr);

 //   QString *Answer;



    double static Multiplying(double first, double second);
    double static Divid(double first,double second);
    double static Minus(double first, double second);
    double static Summary(double first,double secnd);

signals:
    void didEqutionSignal(QString string);
public slots:
    void changetosummurySlot();
    void changetoMinusSlot();
    void changetoMultiplyingSlot();
    void changetoDivisionSlot();

    void doMultiplyingSlot(QString string);
    void doSummurySlot(QString string);
    void doMinusSlot(QString string);
    void doDivisionSlot(QString string);

    void doEquationSlot(QString string);
    void clearNumbersSlot();
private:
    double(*mOperationChooseVariable)(double first,double second);
    double mFirstNumberVariable;
    double mSecondNumberVariable;
    bool mIsFirstOperationVariable=true;

    void DoMathOperation(double(*MathOperation)(double first,double second),QString number);
    void CalculateAndswer();
};

#endif // CALCULATOR_H
