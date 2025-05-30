#ifndef FACTORIALWORKER_H
#define FACTORIALWORKER_H

#include "baseworker.h"

#include <QObject>

class FactorialWorker : public BaseWorker {
    Q_OBJECT
public:
    void doWork(qulonglong inputValue) override;
};

#endif // FACTORIALWORKER_H
