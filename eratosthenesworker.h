#ifndef ERATOSTHENESWORKER_H
#define ERATOSTHENESWORKER_H

#include "baseworker.h"

#include <QObject>

class EratosthenesWorker : public BaseWorker {
    Q_OBJECT
public:
    void doWork(qulonglong inputValue) override;
};

#endif // ERATOSTHENESWORKER_H
