#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{

}
MainWindow::MainWindow(const QString& strHost,int nPort,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    mnNextBlockSize=0;
    mpTcpSocket=new QTcpSocket(this);
    mpTcpSocket->connectToHost(strHost,nPort);
   // connect(mpTcpSocket,SIGNAL(connected()), SLOT(ConnectedSlot()));
    connect(mpTcpSocket, SIGNAL(readyRead()),this, SLOT(readyReadSlot()));
    connect(mpTcpSocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
            this,         SLOT(errorSlot      (QAbstractSocket::SocketError))
            );

    ui->setupUi(this);

    QSignalMapper* mapper=new QSignalMapper(this);
    connect(mapper,SIGNAL(mappedString(const QString&)),this,SLOT(addNumbersSlot(const QString&)));

    connect(ui->mPushButton_0,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_0,"0");

    connect(ui->mPushButton_1,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_1,"1");

    connect(ui->mPushButton_2,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_2,"2");

    connect(ui->mPushButton_3,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_3,"3");

    connect(ui->mPushButton_4,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_4,"4");

    connect(ui->mPushButton_5,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_5,"5");

    connect(ui->mPushButton_6,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_6,"6");

    connect(ui->mPushButton_7,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_7,"7");

    connect(ui->mPushButton_8,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_8,"8");

    connect(ui->mPushButton_9,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(ui->mPushButton_9,"9");

    connect(ui->mPushButton_clear,SIGNAL(clicked()),this,SLOT(toClearNumberClickSlot()));
    connect(ui->mPushButton_division,SIGNAL(clicked()),this,SLOT(toDivisionNumberClickSlot()));
    connect(ui->mPushButton_plus,SIGNAL(clicked()),this,SLOT(toPlusNumberClickSlot()));
    connect(ui->mPushButton_minus,SIGNAL(clicked()),this,SLOT(toMinusNumberClickSlot()));
    connect(ui->mPushButton_multiply,SIGNAL(clicked()),this,SLOT(toMultiplyNumberClickSlot()));
    connect(ui->mPushButton_equals,SIGNAL(clicked()),this,SLOT(toEqualNumberClickSlot()));

}

void MainWindow::addNumbersSlot(const QString& digit){

    if(mIsNumberExistVariable){
        ui->OutputLine->setText(ui->OutputLine->text()+digit);
    }
    else if(digit!="0"){
        ui->OutputLine->setText(digit);
        mIsNumberExistVariable=true;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::readyReadSlot(){
    QDataStream in(mpTcpSocket);
    in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    for(;;){
        if(!mnNextBlockSize){
            if(mpTcpSocket->bytesAvailable()<sizeof(quint16)){
                break;
            }
            in>>mnNextBlockSize;
        }
        if(mpTcpSocket->bytesAvailable()<mnNextBlockSize){
            break;
        }
        QTime time;
        QString str;
        in>>time>>str;

        mnNextBlockSize=0;
    }
}
void MainWindow::errorSlot(QAbstractSocket::SocketError err){
    QString strError=
            "Error: "+(err==QAbstractSocket::HostNotFoundError ?
                           "The host was not found." :
                           err==QAbstractSocket::RemoteHostClosedError?
                           "The remote host is closed." :
                            err==QAbstractSocket::ConnectionRefusedError?
                            "The connection was refused.":
                            QString(mpTcpSocket->errorString())
                                   );
    QMessageBox msgBox;
    msgBox.setText(strError);
    msgBox.exec();

}
void MainWindow::sentToServerSlot(QString answer){
    QByteArray arrBlock;
    QDataStream out(&arrBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out<<quint16(0)<<QTime::currentTime()<<answer;
    out.device()->seek(0);
    out<<quint16(arrBlock.size()-sizeof(quint16));

    mpTcpSocket->write(arrBlock);
}
void MainWindow::toClearNumberClickSlot(){
    mIsNumberExistVariable=false;
    ui->OutputLine->setText("0");
}
void MainWindow::toEqualNumberClickSlot(){
    emit MainWindow::doCalculationSignal(ui->OutputLine->text());
}
void MainWindow::showAnswerSlot(QString string){
    ui->OutputLine->setText(string);

}
void MainWindow::toMinusNumberClickSlot(){

    if(!mIsNumberExistVariable){
        emit changetoMinusSignal();
        return;
    }
    emit makeMinusSignal(ui->OutputLine->text());
    mIsNumberExistVariable=false;
}
void MainWindow::toPlusNumberClickSlot(){
    if(!mIsNumberExistVariable){
        emit changetoSumSignal();
        return;
    }
    emit makeSummSingal(ui->OutputLine->text());
    mIsNumberExistVariable=false;
}
void MainWindow::toDivisionNumberClickSlot(){
    if(!mIsNumberExistVariable){
        emit changetoDivisionSignal();
        return;
    }
    emit makeDivisionSignal(ui->OutputLine->text());
    mIsNumberExistVariable=false;
}
void MainWindow::toMultiplyNumberClickSlot(){
    if(!mIsNumberExistVariable){
        emit changetoMultiplicationSignal();
        return;
    }
    emit makeMultiplicationSignal(ui->OutputLine->text());
    mIsNumberExistVariable=false;
}

