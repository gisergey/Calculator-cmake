#include "Calculator.h"

Calculator::Calculator(QObject *parent)
    : QObject{parent}
{

}
double Calculator::Multiplying(double first, double second){
    return first*second;
}
double Calculator::Divid(double first,double second){
    return first/second;
}
double Calculator::Summary(double first, double second){
    return first+second;
}
double Calculator::Minus(double first, double second){
    return first-second;
}
void Calculator::DoMathOperation(double (*MathOperation)(double, double),QString number){
    if(mIsFirstOperationVariable){
        mFirstNumberVariable=number.toDouble();
        mOperationChooseVariable=MathOperation;
        mIsFirstOperationVariable=false;
    }
    else{
        mFirstNumberVariable=mOperationChooseVariable(Calculator::mFirstNumberVariable,number.toDouble());
        mOperationChooseVariable=MathOperation;
    }
}
void Calculator::clearNumbersSlot(){
    mFirstNumberVariable=0;
    mIsFirstOperationVariable=true;
}
void  Calculator::doSummurySlot(QString number){
   DoMathOperation(Summary,number);
}
void Calculator::doDivisionSlot(QString number){
    DoMathOperation(Divid,number);
}
void Calculator::doMinusSlot(QString number){
    DoMathOperation(Minus,number);
}
void Calculator::doMultiplyingSlot(QString number){
    DoMathOperation(Multiplying,number);

}
void Calculator::changetosummurySlot(){
    mOperationChooseVariable=Summary;
}
void Calculator::changetoMinusSlot(){
    mOperationChooseVariable=Minus;
}
void Calculator::changetoMultiplyingSlot(){
    mOperationChooseVariable=Multiplying;
}
void Calculator::changetoDivisionSlot(){
    mOperationChooseVariable=Divid;
}

void Calculator::doEquationSlot(QString string){
    //отправляет посчитанный ответ в форму
    if(!mIsFirstOperationVariable){
    mFirstNumberVariable=mOperationChooseVariable(mFirstNumberVariable,string.toDouble());
    mIsFirstOperationVariable=true;
    emit didEqutionSignal(QString::number(mFirstNumberVariable));
    }
}

