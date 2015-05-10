#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rbt.h"
#include <QStatusBar>
#include <QMessageBox>
#include <limits>
#include <QFrame>
#include <cmath>
#include "nodegraphic.h"
#include <QLabel>

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
    mainLayout->setRowMinimumHeight(3, 30);
    mainLayout->setColumnMinimumWidth(0, 100);
    mainLayout->setColumnMinimumWidth(1, 200);
    mainLayout->setColumnMinimumWidth(2, 5);
    mainLayout->setColumnMinimumWidth(3, 195);
    mainLayout->setColumnMinimumWidth(4, 200);
    mainLayout->setColumnMinimumWidth(5, 100);

    //Buttons
    insertBtn = new QPushButton("Insert Integer");
    deleteBtn = new QPushButton("Delete Integer");
    searchBtn = new QPushButton("Search Integer");
    toArrayBtn = new QPushButton("Fetch Array");
    toTreeBtn = new QPushButton("Load from Array");

    //Graphics
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    view ->setScene(scene);

    //textLine
    insertLine = new QLineEdit();
    deleteLine = new QLineEdit();
    searchLine = new QLineEdit();
    toTreeLine = new QLineEdit();
    toArrayLine = new QLineEdit();

    insertLine->setPlaceholderText("(1 Integer)");
    insertLine->setAlignment(Qt::AlignCenter);

    deleteLine->setPlaceholderText("(1 Integer)");
    deleteLine->setAlignment(Qt::AlignCenter);

    searchLine->setPlaceholderText("(1 Integer)");
    searchLine->setAlignment(Qt::AlignCenter);

    toTreeLine->setPlaceholderText("(A comma-separated list of integers)");
    toTreeLine->setAlignment(Qt::AlignCenter);

    toArrayLine->setPlaceholderText("Fetch sorted array of integers from RBT");
    toArrayLine->setAlignment(Qt::AlignCenter);

    QFrame *separatorLine = new QFrame();
    separatorLine->setFrameShape(QFrame::VLine);
    separatorLine->setFrameShadow(QFrame::Sunken);

    QLabel *teamName = new QLabel();
    teamName->setText("~ Brought to you by the Red-Black Meteors! ~");
    teamName->setStyleSheet("QLabel { color : crimson; }");
    teamName->setAlignment(Qt::AlignCenter);

    // Place widgets
    mainLayout->addWidget(insertBtn, 1, 1 );
    mainLayout->addWidget(deleteBtn, 2, 1);
    mainLayout->addWidget(searchBtn, 3, 1);
    mainLayout->addWidget(toArrayBtn, 2, 5 );
    mainLayout->addWidget(toTreeBtn, 1, 5 );
    mainLayout->addWidget(insertLine, 1, 0);
    mainLayout->addWidget(deleteLine, 2, 0);
    mainLayout->addWidget(searchLine, 3, 0);
    mainLayout->addWidget(separatorLine, 1, 2, 3, 1);
    mainLayout->addWidget(toTreeLine, 1, 3, 1, 2);
    mainLayout->addWidget(toArrayLine, 2, 3, 1, 2);
    mainLayout->addWidget(teamName, 3, 3, 1, 3);
    mainLayout->addWidget(view, 0, 0, 1, 6);

    // Set slots
    connect(insertBtn, SIGNAL(released()), this, SLOT(insertItem()));
    connect(deleteBtn, SIGNAL(released()), this, SLOT(deleteItem()));
    connect(searchBtn, SIGNAL(released()), this, SLOT(searchItem()));
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
    QAction *search = new QAction("&Search Integer from RBT", menu);

    // Add actions to shortcuts menu
    shortcuts->addAction(add);
    shortcuts->addAction(clear);
    shortcuts->addAction(del);
    shortcuts->addAction(fetch);
    shortcuts->addAction(load);
    shortcuts->addAction(search);

    // Connect actions to shortcuts menu options
    connect(add, SIGNAL(triggered()), this, SLOT(insertItem()));
    connect(clear, SIGNAL(triggered()), this, SLOT(clearTree()));
    connect(del, SIGNAL(triggered()), this, SLOT(deleteItem()));
    connect(fetch, SIGNAL(triggered()), this, SLOT(convertTreeToArray()));
    connect(load, SIGNAL(triggered()), this, SLOT(convertArrayToTree()));
    connect(search, SIGNAL(triggered()), this, SLOT(searchItem()));
}

void MainWindow::insertItem()
{
    insertBtn->setDisabled(true);
    QString s = insertLine->text();
    s = s.trimmed();

    if(s.size() == 0)
    {
        QMessageBox::warning(this, tr("Error"), tr("You need to type in an integer before you can insert it into the red-black tree."));
        insertBtn->setDisabled(false);
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
            insertBtn->setDisabled(false);
            return;
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("You entered an invalid integer!"));
        insertBtn->setDisabled(false);
        return;
    }

    tree.insert(std::make_pair(num, num));
    insertLine->clear();
//    QColor color(255,55,56);
//    QGraphicsItem *item = new NodeGraphic(color, 5, 5, num);
//    QGraphicsItem *item2 = new NodeGraphic(color, 5, 5, num);
//    item->setPos(QPointF(0, 0));
//    item2->setPos(QPointF(60, 60));
//    scene->addItem(item);
//    scene ->addItem(item2);
    setUpTree();
    ui->statusBar->showMessage("Added a new integer: " + QString::number(num));
    insertBtn->setDisabled(false);
}

void MainWindow::deleteItem()
{
    deleteBtn->setDisabled(true);
    QString s = deleteLine->text();
    s = s.trimmed();

    if(s.size() == 0)
    {
        QMessageBox::warning(this, tr("Error"), tr("You need to type in an integer before you can delete the corresponding node from the red-black tree."));
        deleteBtn->setDisabled(false);
        return;
    }

    int key;
    QRegExp re("-?\\d*");
    if(re.exactMatch(s))
    {
        key = s.toInt();
        if(key > INT_MAX || key < INT_MIN)
        {
            QMessageBox::warning(this, tr("Error"), tr("You entered an integer beyond its limits!"));
            deleteBtn->setDisabled(false);
            return;
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("You entered an invalid integer!"));
        deleteBtn->setDisabled(false);
        return;
    }

    bool result = tree.deleteKey(key);
    deleteLine->clear();
    if(result)
    {
        QMessageBox::information(this, tr("Success"), tr("Node removed from the red-black tree!"));
        ui->statusBar->showMessage("Success: deleted node with key " + QString::number(key));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Node not found in red-black tree!"));
        ui->statusBar->showMessage("Error: could not find node with key " + QString::number(key));
    }
    deleteBtn->setDisabled(false);
}

void MainWindow::searchItem()
{
    searchBtn->setDisabled(true);
    QString s = searchLine->text();
    s = s.trimmed();

    if(s.size() == 0)
    {
        QMessageBox::warning(this, tr("Error"), tr("You need to type in an integer before you can search for the corresponding node in the red-black tree."));
        searchBtn->setDisabled(false);
        return;
    }

    int key;
    QRegExp re("-?\\d*");
    if(re.exactMatch(s))
    {
        key = s.toInt();
        if(key > INT_MAX || key < INT_MIN)
        {
            QMessageBox::warning(this, tr("Error"), tr("You entered an integer beyond its limits!"));
            searchBtn->setDisabled(false);
            return;
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("You entered an invalid integer!"));
        searchBtn->setDisabled(false);
        return;
    }

    node<int> *result = tree.search(key);
    searchLine->clear();
    if(result != nullptr)
    {
        QMessageBox::information(this, tr("Success"), tr("Node found in the red-black tree!"));
        ui->statusBar->showMessage("Success: found node with key " + QString::number(key));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Node not found in red-black tree!"));
        ui->statusBar->showMessage("Error: could not find node with key " + QString::number(key));
    }
    searchBtn->setDisabled(false);
}


void MainWindow::convertTreeToArray()
{
    toArrayBtn->setDisabled(true);
    std::vector<std::pair<int, int> > vct = tree.treeToSortedVector();
    unsigned int size = vct.size();
    QString s = "";

    if(size == 0)
    {
        QMessageBox::warning(this, tr("Error"), tr("The red-black tree is empty!"));
        toArrayLine->clear();
        toArrayBtn->setDisabled(false);
        ui->statusBar->showMessage("Error: cannot fetch array for an empty red-black tree");
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
    toArrayBtn->setDisabled(false);
    ui->statusBar->showMessage("Success: fetched array from the red-black tree");
    return;
}

void MainWindow::convertArrayToTree()
{
    toTreeBtn->setDisabled(true);
    std::vector<std::pair<int, int> > vct;
    QString s = toTreeLine->text();

    if(s.size() == 0)
    {
        QMessageBox::warning(this, tr("Error"), tr("You must provide a valid comma-separated list of integers!"));
        toTreeLine->clear();
        toTreeBtn->setDisabled(false);
        ui->statusBar->showMessage("Error: list of integers is invalid");
        return;
    }

    QStringList lst = s.split(",");

    QRegExp re("-?\\d*");
    int num;

    for(auto word : lst)
    {
        QString trimmedWord = word.trimmed();
        if(re.exactMatch(trimmedWord))
        {
            num = trimmedWord.toInt();
            std::cout << num << std::endl;
            if(num > INT_MAX || num < INT_MIN)
            {
                QMessageBox::warning(this, tr("Error"), tr("You entered an integer beyond its limits!"));
                toTreeBtn->setDisabled(false);
                ui->statusBar->showMessage("Error: list of integers is invalid");
                return;
            }
            vct.push_back(std::make_pair(num, num));
        }
    }

    tree.sortedVectorToTree(vct);

    toTreeLine->clear();
    toTreeBtn->setDisabled(false);
    QMessageBox::information(this, tr("Success"), tr("Loaded array into the red-black tree!"));
    ui->statusBar->showMessage("Success: loaded array into the red-black tree");
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

void MainWindow::setUpTree()
{
    int tHeight = 0;
    int tWidth = 0;
    setUpQ = tree.getNodeBreadthFirst();
    for(int i = 0;i<tree.getSize(); i++)
    {
        if(tWidth < pow(2,tHeight))
        {
            tWidth++;
            setUpQ.pop();
        }
        if(tWidth == pow(2,tHeight))
        {
            tHeight++;
        }
    }

}
