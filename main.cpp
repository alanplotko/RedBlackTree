#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QRect>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Set window title
    w.setWindowTitle("Red-Black Trees");

    // Set window's initial dimensions
    w.setFixedSize(800, 430);

    // Center window on desktop
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - w.width()) / 2;
    int y = (screenGeometry.height() - w.height()) / 2;
    w.move(x, y);

    // Show window
    w.show();

    return a.exec();
}
