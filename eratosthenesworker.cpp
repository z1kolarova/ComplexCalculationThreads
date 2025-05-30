#include <QThread>
#include <sstream>
#include <iostream>
#include <QCoreApplication>

#include "eratosthenesworker.h"

void EratosthenesWorker::doWork(qulonglong inputValue)
{
    isCancelled = false;
    isPaused = false;

    string resultAsString;

    bool arr[inputValue + 1] = {0};

    qulonglong progressIncrement = inputValue/100;
    qulonglong nextThreshold = progressIncrement;
    int progress = 0;

    qulonglong helper = sqrt(inputValue);

    for (qulonglong j = 2; j <= inputValue; j++)
    {
        QCoreApplication::processEvents();
        if (isCancelled)
        {
            return;
        }

        if (isPaused)
        {
            emit pausedSuccessfully();
            while (isPaused)
            {
                QCoreApplication::processEvents();
            }
            emit resumedSuccessfully();
        }

        if (arr[j] == true)
        {
            continue;
        }

        if (j <= helper)
        {
            for (qulonglong i = 2*j; i <= inputValue; i +=j)
            {
                arr[i] = true;
            }
        }

        resultAsString += " " + to_string(j);

        if(j > nextThreshold)
        {
            progress++;
            nextThreshold += progressIncrement;
            emit reportProgress(progress);
        }
    }

    emit resultReady(resultAsString);
}
