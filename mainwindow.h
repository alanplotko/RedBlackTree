#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QWindow>
#include <QFrame>
#include <QGridLayout>
#include <QTabWidget>
#include <QIcon>
#include <QFont>
#include <QLineEdit>
#include <QLabel>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <queue>
#include "rbt.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    rbt<int> tree;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void insertItem();
    void deleteItem();
    void searchItem();
    void convertTreeToArray();
    void convertArrayToTree();
    void clearTree();
    void quitApp();

private:
    Ui::MainWindow *ui;
    std::queue<node<int>*> setUpQ;
    QWidget *mainWidget;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGridLayout *mainLayout;
    QPushButton *insertBtn, *deleteBtn, *searchBtn, *toArrayBtn, *toTreeBtn;
    QLineEdit *deleteLine, *searchLine, *insertLine, *toArrayLine, *toTreeLine;
    void setUpMenu();
    void setUpTree();

};

#endif // MAINWINDOW_H
