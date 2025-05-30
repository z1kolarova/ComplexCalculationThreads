#ifndef BASEWORKER_H
#define BASEWORKER_H

#include <QMutex>
#include <QObject>

using namespace std;

class BaseWorker : public QObject {
    Q_OBJECT
public:
    virtual void doWork(qulonglong inputValue) = 0;

signals:
    void pausedSuccessfully();
    void resumedSuccessfully();
    void reportProgress(int percentage);
    void resultReady(string result);

public slots:
    void pauseOrResume();
    void cancel();

protected:
    bool isPaused = false;
    bool isCancelled = false;
};

#endif // BASEWORKER_H
