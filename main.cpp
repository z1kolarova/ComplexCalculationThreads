#include "mainwindow.h"

#include <QApplication>

#include <QThreadPool>
#include <omp.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QThreadPool::globalInstance()->setMaxThreadCount(TASK_MAX_COUNT);
    MainWindow w;
    w.show();
    return a.exec();
}
