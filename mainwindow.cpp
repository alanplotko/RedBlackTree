#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rbt.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainWidget = new QWidget();
    mainLayout = new QGridLayout();
    buttonLayout = new QHBoxLayout();
    buttonCol1 = new QGridLayout();
    buttonCol2 = new QGridLayout();
    mainLayout-> setRowMinimumHeight(0, 300);

    //Buttons
    insertB = new QPushButton("Insert");
    deleteB = new QPushButton("Delete");
    toArrayB = new QPushButton("RBT to Array");
    toTreeB = new QPushButton("Array to RBT");

    //qframe
    div1 = new QFrame();
    div1 ->setFixedSize(1,100);
    div1->setFrameShape(QFrame::VLine);
    div1 ->setFrameShadow(QFrame::Plain);

    div2 = new QFrame();
    div2 ->setFixedSize(1,100);
    div2->setFrameShape(QFrame::HLine);
    div2 ->setFrameShadow(QFrame::Plain);


    //textLine
    iLine = new QLineEdit();
    dLine = new QLineEdit();
    toTLine = new QLineEdit();

    iLine->setMinimumWidth(150);
    dLine->setMinimumWidth( 150);
    toTLine->setMinimumWidth(150);

    iLine->setPlaceholderText("Item to insert");
    dLine->setPlaceholderText("Item to delete");
    toTLine ->setPlaceholderText("Array to insert");


    //add stuff
    buttonCol1 ->addWidget(insertB, 0, 1 );
    buttonCol1 ->addWidget(deleteB, 2, 1);
    buttonCol2 ->addWidget(toArrayB, 0, 1 );
    buttonCol2 ->addWidget(toTreeB, 2, 1 );
    buttonCol1 ->addWidget(iLine, 0, 0 );
    buttonCol1 ->addWidget(dLine, 1, 0);
    buttonCol2 ->addWidget(toTLine, 1, 0);
    buttonLayout ->addLayout(buttonCol1);
    buttonLayout ->addWidget(div1);
    buttonLayout ->addLayout(buttonCol2);
    mainLayout ->addLayout(buttonLayout,1,0);


    mainWidget -> setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
