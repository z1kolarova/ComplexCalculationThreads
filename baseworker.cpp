#include "baseworker.h"
#include <QMutexLocker>
#include <iostream>

void BaseWorker::pauseOrResume() {
    isPaused = !isPaused;
}
void BaseWorker::cancel() {
    isCancelled = true;
}
