#include "mainwindow.h"
#include <Calculator.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QString *Answers=new QString();
    //  *Answers="0";
    MainWindow w("localhost",2323);
    Calculator calcul;
    // w.Answer=Answers;
    //calcul.Answer=Answers;
    QObject::connect(&w,SIGNAL(makeSummSingal(QString)),&calcul,SLOT(doSummurySlot(QString)));
    QObject::connect(&w,SIGNAL(makeMinusSignal(QString)),&calcul,SLOT(doMinusSlot(QString)));
    QObject::connect(&w,SIGNAL(makeMultiplicationSignal(QString)),&calcul,SLOT(doMultiplyingSlot(QString)));
    QObject::connect(&w,SIGNAL(makeDivisionSignal(QString)),&calcul,SLOT(doDivisionSlot(QString)));

    QObject::connect(&w,SIGNAL(changetoSumSignal()),&calcul,SLOT(changetosummurySlot()));
    QObject::connect(&w,SIGNAL(changetoMinusSignal()),&calcul,SLOT(changetoMinusSlot()));
    QObject::connect(&w,SIGNAL(changetoMultiplicationSignal()),&calcul,SLOT(changetoMultiplyingSlot()));
    QObject::connect(&w,SIGNAL(changetoDivisionSignal()),&calcul,SLOT(changetoDivisionSlot()));

    QObject::connect(&w,SIGNAL(doCalculationSignal(QString)),&calcul,SLOT(doEquationSlot(QString)));
    QObject::connect(&calcul,SIGNAL(didEqutionSignal(QString)),&w,SLOT(showAnswerSlot(QString)));
    QObject::connect(&calcul,SIGNAL(didEqutionSignal(QString)),&w,SLOT(sentToServerSlot(QString)));
    QObject::connect(&w,SIGNAL(toClearNumberSignal()),&calcul,SLOT(clearNumbersSlot()));

    w.show();

    return a.exec();

}
