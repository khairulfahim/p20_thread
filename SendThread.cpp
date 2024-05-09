#include "SendThread.h"
#include <unistd.h>

SendThread::SendThread() : running(false) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_create(&thread, nullptr, sendLoop, this);
}

SendThread::~SendThread() {
    running = false;
    pthread_join(thread, nullptr);
    pthread_mutex_destroy(&mutex);
}

void SendThread::sendImage(const QBitArray &sendBit) {
    pthread_mutex_lock(&mutex);
    imageQueue.push(sendBit);
    pthread_mutex_unlock(&mutex);
}

void SendThread::signalClear() {
    pthread_mutex_lock(&mutex);
    clearQueue.push(true);
    pthread_mutex_unlock(&mutex);
}

void* SendThread::sendLoop(void* arg) {
    SendThread* sender = static_cast<SendThread*>(arg);
    sender->running = true;

    while (sender->running) {
        pthread_mutex_lock(&sender->mutex);
        if (!sender->imageQueue.empty()) {
            QBitArray sendBit = sender->imageQueue.front();
            sender->imageQueue.pop();
            emit sender->betweenSent(sendBit);
        }

        if (!sender->clearQueue.empty()) {
            // Clear drawing
            sender->clearQueue.pop();
            emit sender->betweenClear();
        }
        pthread_mutex_unlock(&sender->mutex);

        usleep(100); // Adjust sleep duration as needed
    }

    return nullptr;
}
