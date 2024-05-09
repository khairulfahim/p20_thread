#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <pthread.h>
#include <queue>
#include <QObject>
#include <QImage>
#include <QBitArray>

class ReceiveThread : public QObject {
    Q_OBJECT // Add Q_OBJECT macro here
public:
    ReceiveThread();
    ~ReceiveThread();

    //void receiveImage(const QBitArray &sendBit);
    //void receiveClear();

private:
    static void* receiveLoop(void* arg);

    pthread_t thread;
    pthread_mutex_t mutex;
    std::queue<QBitArray> bitQueue;
    std::queue<bool> clearQueue;
    bool running;

signals:
    void imageReceived(const QBitArray &sendBit);
    void clearReceived();

public slots:
    void receiveImage(const QBitArray &sendBit);
    void receiveClear();
};

#endif // RECEIVETHREAD_H
