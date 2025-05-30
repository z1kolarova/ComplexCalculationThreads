#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QThread>

#define TASK_MAX_COUNT (3)
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread thread1;
    QThread thread2;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void beginWorkFactorial(qulonglong inputValue);
    void beginWorkErathostenes(qulonglong inputValue);

private slots:
    void startFactorialCalculation();
    void pauseFactorialCalculation();
    void resumeFactorialCalculation();
    void cancelFactorialCalculation();
    void completeFactorialCalculation(string resultAsString);

    void startPrimeNumbersSearch();
    void pausePrimeNumbersSearch();
    void resumePrimeNumbersSearch();
    void cancelPrimeNumbersSearch();
    void completePrimeNumbersSearch(string resultAsString);

private:
    Ui::MainWindow *ui;
    bool valueIsQreaterThanZeroVerification(QLineEdit *textSource, qulonglong &cislo);
};
#endif // MAINWINDOW_H
