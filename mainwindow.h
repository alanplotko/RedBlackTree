#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSplashScreen>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWindow>
#include <QPixmap>
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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:


private:
    Ui::MainWindow *ui;
    QWidget *mainWidget;
    QGridLayout *mainLayout, *buttonCol1,*buttonCol2;
    QHBoxLayout *buttonLayout;
    QPushButton *insertB,*deleteB,*toArrayB,*toTreeB;
    QLineEdit *dLine,*iLine,*toTLine;
    QFrame *div1,*div2,*div3,*div4,*div5;
    rbt<int> tree;
};

#endif // MAINWINDOW_H
