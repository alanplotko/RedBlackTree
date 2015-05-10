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
    void convertTreeToArray();
    void convertArrayToTree();
    void clearTree();
    void quitApp();

private:
    Ui::MainWindow *ui;
    QWidget *mainWidget;
    QGridLayout *mainLayout;
    QPushButton *insertBtn, *deleteBtn, *toArrayBtn, *toTreeBtn;
    QLineEdit *deleteLine, *insertLine, *toArrayLine, *toTreeLine;
    void setUpMenu();

};

#endif // MAINWINDOW_H
