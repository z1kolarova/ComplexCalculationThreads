#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "eratosthenesworker.h"
#include "factorialworker.h"

#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pbFactorial->setValue(0);
    ui->pbEratosthenes->setValue(0);

    FactorialWorker* worker1 = new FactorialWorker;
    EratosthenesWorker* worker2 = new EratosthenesWorker;

    worker1->moveToThread(&thread1);
    worker2->moveToThread(&thread2);

    thread1.start();
    thread2.start();

    //SIGNALS & SLOTS
    connect(ui->btnFactorialStart, &QPushButton::clicked, this, &MainWindow::startFactorialCalculation);
    connect(this, &MainWindow::beginWorkFactorial, worker1, &FactorialWorker::doWork);
    connect(worker1, &FactorialWorker::reportProgress, this->ui->pbFactorial, &QProgressBar::setValue);
    connect(worker1, &FactorialWorker::resultReady, this, &MainWindow::completeFactorialCalculation);
    connect(this->ui->btnFactorialPauseOrResume, &QPushButton::clicked, worker1, &FactorialWorker::pauseOrResume);
    connect(worker1, &FactorialWorker::pausedSuccessfully, this, &MainWindow::pauseFactorialCalculation);
    connect(worker1, &FactorialWorker::resumedSuccessfully, this, &MainWindow::resumeFactorialCalculation);
    connect(this->ui->btnFactorialCancel, &QPushButton::clicked, worker1, &FactorialWorker::cancel);
    connect(this->ui->btnFactorialCancel, &QPushButton::clicked, this, &MainWindow::cancelFactorialCalculation);

    connect(ui->btnEratosthenesStart, &QPushButton::clicked, this, &MainWindow::startPrimeNumbersSearch);
    connect(this, &MainWindow::beginWorkErathostenes, worker2, &EratosthenesWorker::doWork);
    connect(worker2, &EratosthenesWorker::reportProgress, this->ui->pbEratosthenes, &QProgressBar::setValue);
    connect(worker2, &EratosthenesWorker::resultReady, this, &MainWindow::completePrimeNumbersSearch);
    connect(this->ui->btnEratosthenesPauseOrResume, &QPushButton::clicked, worker2, &EratosthenesWorker::pauseOrResume);
    connect(worker2, &EratosthenesWorker::pausedSuccessfully, this, &MainWindow::pausePrimeNumbersSearch);
    connect(worker2, &EratosthenesWorker::resumedSuccessfully, this, &MainWindow::resumePrimeNumbersSearch);
    connect(this->ui->btnEratosthenesCancel, &QPushButton::clicked, worker2, &EratosthenesWorker::cancel);
    connect(this->ui->btnEratosthenesCancel, &QPushButton::clicked, this, &MainWindow::cancelPrimeNumbersSearch);
}

MainWindow::~MainWindow()
{
    thread1.quit();
    thread1.wait();
    thread2.quit();
    thread2.wait();
    delete ui;
}

void MainWindow::startFactorialCalculation()
{
    qulonglong factorialOf;
    if(MainWindow::valueIsQreaterThanZeroVerification(this->ui->leFactorialValue, factorialOf))
    {
        ui->pbFactorial->setValue(0);
        ui->lblFactorialResultValue->setText("---výpočet probíhá---");
        ui->btnFactorialStart->setEnabled(false);
        ui->btnFactorialPauseOrResume->setEnabled(true);
        ui->btnFactorialCancel->setEnabled(true);

        emit beginWorkFactorial(factorialOf);
    }
}

void MainWindow::pauseFactorialCalculation()
{
    ui->lblFactorialResultValue->setText("---výpočet byl pozastaven---");
    ui->btnFactorialPauseOrResume->setText("Obnovit výpočet");
    ui->btnFactorialCancel->setEnabled(false);
}

void MainWindow::resumeFactorialCalculation()
{
    ui->lblFactorialResultValue->setText("---výpočet probíhá---");
    ui->btnFactorialStart->setEnabled(false);
    ui->btnFactorialPauseOrResume->setText("Pozastavit výpočet");
    ui->btnFactorialCancel->setEnabled(true);
}

void MainWindow::cancelFactorialCalculation()
{
    ui->lblFactorialResultValue->setText("---výpočet byl zrušen---");
    ui->pbFactorial->setValue(0);
    ui->btnFactorialStart->setEnabled(true);
    ui->btnFactorialPauseOrResume->setEnabled(false);
    ui->btnFactorialCancel->setEnabled(false);
}

void MainWindow::completeFactorialCalculation(string resultAsString)
{
    ui->lblFactorialResultValue->setText(resultAsString.c_str());
    ui->pbFactorial->setValue(100);
    ui->btnFactorialStart->setEnabled(true);
    ui->btnFactorialPauseOrResume->setEnabled(false);
    ui->btnFactorialCancel->setEnabled(false);
}

void MainWindow::startPrimeNumbersSearch()
{
    qulonglong ceilingValue;
    if(MainWindow::valueIsQreaterThanZeroVerification(this->ui->leErastothenesValue, ceilingValue))
    {
        ui->pbEratosthenes->setValue(0);
        ui->lblEratosthenesResultValue->setText("---hledání probíhá---");
        ui->btnEratosthenesStart->setEnabled(false);
        ui->btnEratosthenesPauseOrResume->setEnabled(true);
        ui->btnEratosthenesCancel->setEnabled(true);

        emit beginWorkErathostenes(ceilingValue);
    }
}

void MainWindow::pausePrimeNumbersSearch()
{
    ui->lblEratosthenesResultValue->setText("---hledání bylo pozastaveno---");
    ui->btnEratosthenesPauseOrResume->setText("Obnovit hledání");
    ui->btnEratosthenesCancel->setEnabled(false);
}

void MainWindow::resumePrimeNumbersSearch()
{
    ui->lblEratosthenesResultValue->setText("---hledání probíhá---");
    ui->btnEratosthenesStart->setEnabled(false);
    ui->btnEratosthenesPauseOrResume->setText("Pozastavit hledání");
    ui->btnEratosthenesCancel->setEnabled(true);
}

void MainWindow::cancelPrimeNumbersSearch()
{
    ui->lblEratosthenesResultValue->setText("---hledání bylo zrušeno---");
    ui->pbEratosthenes->setValue(0);
    ui->btnEratosthenesStart->setEnabled(true);
    ui->btnEratosthenesPauseOrResume->setEnabled(false);
    ui->btnEratosthenesCancel->setEnabled(false);
}

void MainWindow::completePrimeNumbersSearch(string resultAsString)
{
    ui->lblEratosthenesResultValue->setText(resultAsString.c_str());
    ui->pbEratosthenes->setValue(100);
    ui->btnEratosthenesStart->setEnabled(true);
    ui->btnEratosthenesPauseOrResume->setEnabled(false);
    ui->btnEratosthenesCancel->setEnabled(false);
}

bool MainWindow::valueIsQreaterThanZeroVerification(QLineEdit *textSource, qulonglong &cislo)
{
    bool isLongLong;
    cislo = textSource->text().toULongLong(&isLongLong);
    if(!isLongLong || cislo <= 0)
    {
        QMessageBox::warning(this, tr("Výpočetník"),
                             tr("Hodnota musí být kladné číslo."),
                             QMessageBox::Ok);
    }
    return isLongLong;
}
