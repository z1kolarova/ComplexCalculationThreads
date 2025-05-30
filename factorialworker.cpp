#include <QThread>
#include <sstream>
#include <iostream>
#include <QCoreApplication>

#include "factorialworker.h"

void FactorialWorker::doWork(qulonglong inputValue)
{
    isCancelled = false;
    isPaused = false;

    vector<int> arr;
    arr.push_back(1);

    int carry = 0;

    qulonglong progressIncrement = inputValue/100;
    qulonglong nextThreshold = progressIncrement;
    int progress = 0;

    qulonglong j, helper;

    for (j = 1; j <= inputValue; j++)
    {
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

        carry = 0;
        for (size_t i = 0; i < arr.size(); i++)
        {
            helper = arr[i] * j + carry;
            carry = helper / 10;
            arr[i] = helper % 10;
        }
        while(carry != 0)
        {
            arr.push_back(carry % 10);
            carry = carry / 10;
        }

        if(j > nextThreshold)
        {
            progress++;
            nextThreshold += progressIncrement;
            emit reportProgress(progress);
        }

        QCoreApplication::processEvents();
    }

    string resultAsString;
    for (int i = arr.size() - 1; i>=0; i--)
    {
        resultAsString += to_string(arr[i]);
    }

    emit resultReady(resultAsString);
}

