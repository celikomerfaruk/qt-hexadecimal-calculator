#include "mainview.h"
#include "ui_mainwiew.h"

int tmpResult = 0;
int tmpOperand = 0;
bool lastCharWasOperator = false;
bool firstOperator = true;
bool lastOperatorIsPlus = false;
bool isNegative = false;
bool lastCharWasEqual = false;

MainView::MainView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainView)
{
    ui->setupUi(this);

    //all buttons are connected to the corresponding function
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_A,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_B,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_C,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_D,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_E,SIGNAL(released()),this,SLOT(onDigitPressed()));
    connect(ui->pushButton_F,SIGNAL(released()),this,SLOT(onDigitPressed()));


    connect(ui->pushButton_minus,SIGNAL(released()),this,SLOT(onMinusPressed()));
    connect(ui->pushButton_plus,SIGNAL(released()),this,SLOT(onPlusPressed()));

    connect(ui->pushButton_equal,SIGNAL(released()),this,SLOT(onEqualPressed()));
    connect(ui->pushButton_Clr,SIGNAL(released()),this,SLOT(onClrPressed()));

}

MainView::~MainView()
{
    delete ui;
}

//When digit is clicked
void MainView::onDigitPressed(){
    if(lastCharWasOperator || lastCharWasEqual){
        ui->display->clear();
    }
    QPushButton *pressed = (QPushButton*)sender();
    if(ui->display->text() == "0"){
        ui->display->setText(pressed->text());
    }else{
        ui->display->setText(ui->display->text() + pressed->text());
    }
    lastCharWasOperator = false;
    lastCharWasEqual = false;
}

//When plus is clicked
void MainView::onPlusPressed(){
    //If lastCharWasOperator ignore it
    if(!lastCharWasOperator){
        bool ok;
        if(isNegative){
            tmpOperand = ui->display->text().toLower().toInt(&ok,16) * -1 ;
            isNegative = false;
        }else{
            tmpOperand = ui->display->text().toLower().toInt(&ok,16);
        }


        if(firstOperator){
            tmpResult = tmpOperand;
            lastOperatorIsPlus = true;
            firstOperator = false;
        }else{
            if(lastOperatorIsPlus){
                tmpResult += tmpOperand;
            }else{
                tmpResult -= tmpOperand;
            }
            lastOperatorIsPlus = true;
        }

        ui->display->clear();
        ui->display->setText(QString::number(tmpResult,16).toUpper());
    }
    tmpOperand = 0;
    lastCharWasOperator = true;
    lastCharWasEqual = false;
}

//When minus is clicked
void MainView::onMinusPressed(){
    //If lastCharWasOperator change the sign of new input.
    if(lastCharWasOperator){
        isNegative = !isNegative;
    }else{
        bool ok;
        if(isNegative){
            tmpOperand = ui->display->text().toLower().toInt(&ok,16) * -1 ;
            isNegative = false;
        }else{
            tmpOperand = ui->display->text().toLower().toInt(&ok,16);
        }
        if(firstOperator){
             tmpResult = tmpOperand;
             lastOperatorIsPlus = false;
             firstOperator = false;
        }else{
            if(lastOperatorIsPlus){
                tmpResult += tmpOperand;
            }else{
                tmpResult -= tmpOperand;
            }
             lastOperatorIsPlus = false;
        }
        ui->display->clear();
        ui->display->setText(QString::number(tmpResult,16).toUpper());
    }

      tmpOperand = 0;
      lastCharWasOperator = true;
      lastCharWasEqual = false;
}

//When clear is clicked
//reset functionality
void MainView::onClrPressed(){
    ui->display->setText("0");
    tmpResult = 0;
    firstOperator = true;
    lastCharWasEqual = false;
    lastCharWasOperator = false;
    isNegative = false;
}

//When equal sign is clicked
void MainView::onEqualPressed(){
    //if enter clicked multiple times ignore it
    if(lastCharWasEqual){
        return;
    }

    if(lastCharWasOperator){
        ui->display->setText(QString::number(tmpResult,16));
    }else{
        bool ok;
        if(isNegative){
            tmpOperand = ui->display->text().toLower().toInt(&ok,16) * -1 ;
            isNegative = false;
        }else{
            tmpOperand = ui->display->text().toLower().toInt(&ok,16);
        }
        if(lastOperatorIsPlus){
            tmpResult += tmpOperand;
        }else{
            tmpResult -= tmpOperand;
        }
        ui->display->setText(QString::number(tmpResult,16).toUpper());

    }
    lastCharWasEqual = true;
    firstOperator = true;
    lastCharWasOperator = false;
}
