#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rbt.h"
#include <QStatusBar>
#include <QMessageBox>
#include <limits>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUpMenu();

    mainWidget = new QWidget();
    mainLayout = new QGridLayout(mainWidget);

    mainLayout->setRowMinimumHeight(0, 340);
    mainLayout->setRowMinimumHeight(1, 30);
    mainLayout->setRowMinimumHeight(2, 30);
    mainLayout->setColumnMinimumWidth(0, 100);
    mainLayout->setColumnMinimumWidth(1, 200);
    mainLayout->setColumnMinimumWidth(2, 5);
    mainLayout->setColumnMinimumWidth(3, 195);
    mainLayout->setColumnMinimumWidth(4, 200);
    mainLayout->setColumnMinimumWidth(5, 100);

    //Buttons
    insertBtn = new QPushButton("Insert Integer");
    deleteBtn = new QPushButton("Delete Integer");
    toArrayBtn = new QPushButton("Fetch Array");
    toTreeBtn = new QPushButton("Load from Array");

    //textLine
    insertLine = new QLineEdit();
    deleteLine = new QLineEdit();
    toTreeLine = new QLineEdit();
    toArrayLine = new QLineEdit();
    toArrayLine->setDisabled(true);

    insertLine->setPlaceholderText("(1 Integer)");
    insertLine->setAlignment(Qt::AlignCenter);

    deleteLine->setPlaceholderText("(1 Integer)");
    deleteLine->setAlignment(Qt::AlignCenter);

    toTreeLine->setPlaceholderText("(A comma-separated list of integers)");
    toTreeLine->setAlignment(Qt::AlignCenter);

    toArrayLine->setPlaceholderText("Fetch sorted array of integers from RBT");
    toArrayLine->setAlignment(Qt::AlignCenter);

    QFrame *separatorLine = new QFrame();
    separatorLine->setFrameShape(QFrame::VLine);
    separatorLine->setFrameShadow(QFrame::Sunken);

    // Place widgets
    mainLayout->addWidget(insertBtn, 1, 1 );
    mainLayout->addWidget(deleteBtn, 2, 1);
    mainLayout->addWidget(toArrayBtn, 2, 5 );
    mainLayout->addWidget(toTreeBtn, 1, 5 );
    mainLayout->addWidget(insertLine, 1, 0);
    mainLayout->addWidget(deleteLine, 2, 0);
    mainLayout->addWidget(separatorLine, 1, 2, 2, 1);
    mainLayout->addWidget(toTreeLine, 1, 3, 1, 2);
    mainLayout->addWidget(toArrayLine, 2, 3, 1, 2);

    // Set slots
    connect(insertBtn, SIGNAL(released()), this, SLOT(insertItem()));
    connect(deleteBtn, SIGNAL(released()), this, SLOT(deleteItem()));
    connect(toArrayBtn, SIGNAL(released()), this, SLOT(convertTreeToArray()));
    connect(toTreeBtn, SIGNAL(released()), this, SLOT(convertArrayToTree()));

    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpMenu()
{
    // Set up menuBar
    QMenuBar *menu = this->menuBar();

    /*--------------
        File menu
    ----------------*/

    QMenu *file = menu->addMenu("&File");

    // Create file menu actions
    QAction *quit = new QAction("&Quit", menu);

    // Add actions to file menu
    file->addAction(quit);

    // Connect actions to file menu options
    connect(quit, SIGNAL(triggered()), this, SLOT(quitApp()));

    /*-------------------
        Shortcuts menu
    ---------------------*/

    QMenu *shortcuts = menu->addMenu("&Shortcuts");

    // Create shortcuts menu actions
    QAction *add = new QAction("&Add Integer to RBT", menu);
    QAction *clear = new QAction("&Clear RBT", menu);
    QAction *del = new QAction("&Delete Integer from RBT", menu);
    QAction *fetch = new QAction("&Fetch Array from RBT", menu);
    QAction *load = new QAction("&Load RBT from Array", menu);

    // Add actions to shortcuts menu
    shortcuts->addAction(add);
    shortcuts->addAction(clear);
    shortcuts->addAction(del);
    shortcuts->addAction(fetch);
    shortcuts->addAction(load);

    // Connect actions to shortcuts menu options
    connect(add, SIGNAL(triggered()), this, SLOT(insertItem()));
    connect(clear, SIGNAL(triggered()), this, SLOT(clearTree()));
    connect(del, SIGNAL(triggered()), this, SLOT(deleteItem()));
    connect(fetch, SIGNAL(triggered()), this, SLOT(convertTreeToArray()));
    connect(load, SIGNAL(triggered()), this, SLOT(convertArrayToTree()));
}

void MainWindow::insertItem()
{
    QString s = insertLine->text();
    s = s.trimmed();

    if(s.size() == 0)
    {
        QMessageBox::warning(this, tr("Error"), tr("You need to type in an integer before you can insert it into the red-black tree."));
        return;
    }

    int num;
    QRegExp re("-?\\d*");
    if(re.exactMatch(s))
    {
        num = s.toInt();
        if(num > INT_MAX || num < INT_MIN)
        {
            QMessageBox::warning(this, tr("Error"), tr("You entered an integer beyond its limits!"));
            return;
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("You entered an invalid integer!"));
        return;
    }

    tree.insert(std::make_pair(num, num));
    insertLine->clear();
    ui->statusBar->showMessage("Added a new integer: " + QString::number(num));
}

void MainWindow::deleteItem()
{
    return;
}

void MainWindow::convertTreeToArray()
{
    std::vector<std::pair<int, int> > vct = tree.treeToSortedVector();
    unsigned int size = vct.size();
    QString s = "";

    if(size == 0)
    {
        QMessageBox::warning(this, tr("Error"), tr("The red-black tree is empty!"));
        return;
    }

    for(unsigned int i = 0; i < size; i++)
    {
        s += QString::number(vct[i].second);
        if(i < size - 1)
        {
            s += ", ";
        }
    }

    QMessageBox::information(this, tr("Success"), tr("Fetched array from red-black tree!"));
    toArrayLine->setText(s);
    return;
}

void MainWindow::convertArrayToTree()
{
    return;
}

void MainWindow::clearTree()
{
    std::cout << tree.getSize() << std::endl;
    if(tree.getSize() == 0)
    {
        QMessageBox::warning(this, tr("Error"), tr("You can't clear an empty red-black tree!"));
        ui->statusBar->showMessage("Error: cannot clear an empty red-black tree");
    }
    else
    {
        tree.cleanRbt();
        QMessageBox::information(this, tr("Success"), tr("The red-black tree has been cleared!"));
        ui->statusBar->showMessage("Success: cleared the red-black tree");
    }
}

void MainWindow::quitApp()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Warning", "Are you sure you want to quit? All of your precious nodes will disappear.", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QMessageBox::information(this, tr("Goodbye"), tr("See you later!"));
        QApplication::quit();
    }
}
