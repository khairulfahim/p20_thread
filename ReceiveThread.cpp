#include "ReceiveThread.h"
#include <unistd.h>

ReceiveThread::ReceiveThread() : running(false) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_create(&thread, nullptr, receiveLoop, this);
}

ReceiveThread::~ReceiveThread() {
    running = false;
    pthread_join(thread, nullptr);
    pthread_mutex_destroy(&mutex);
}

void ReceiveThread::receiveImage(const QBitArray &sendBit) {
    pthread_mutex_lock(&mutex);
    bitQueue.push(sendBit);
    pthread_mutex_unlock(&mutex);
}

void ReceiveThread::receiveClear() {
    pthread_mutex_lock(&mutex);
    clearQueue.push(true);
    pthread_mutex_unlock(&mutex);
}

void* ReceiveThread::receiveLoop(void* arg) {
    ReceiveThread* receiver = static_cast<ReceiveThread*>(arg);
    receiver->running = true;

    while (receiver->running) {
        pthread_mutex_lock(&receiver->mutex);
        if (!receiver->bitQueue.empty()) {
            QBitArray sendBit = receiver->bitQueue.front();
            receiver->bitQueue.pop();
            //emit signal for received image
            emit receiver->imageReceived(sendBit);
        }

        if (!receiver->clearQueue.empty()) {
            receiver->clearQueue.pop();
            emit receiver->clearReceived();
        }
        pthread_mutex_unlock(&receiver->mutex);

        usleep(100); // Adjust sleep duration as needed
    }

    return nullptr;
}

