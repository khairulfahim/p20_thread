#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <pthread.h>
#include <QObject>
#include <queue>
#include <QImage>
#include <QBitArray>

class SendThread : public QObject {
    Q_OBJECT // Add Q_OBJECT macro here
public:
    SendThread();
    ~SendThread();
    //void sendImage(const QBitArray &sendBit);
    //void signalClear();

private:
    static void* sendLoop(void* arg);

    pthread_t thread;
    pthread_mutex_t mutex;
    std::queue<QBitArray> imageQueue;
    std::queue<bool> clearQueue;
    bool running;

signals:
    void betweenSent(const QBitArray &sendBit);
    void betweenClear();

public slots:
    void sendImage(const QBitArray &sendBit);
    void signalClear();
};

#endif // SENDTHREAD_H
