#include <QApplication>
#include "SendWindow.h"
#include "ReceiveWindow.h"
#include "SendThread.h"
#include "ReceiveThread.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SendThread sendThread;
    ReceiveThread receiveThread;

    SendWindow sendWindow;
    ReceiveWindow receiveWindow;

    // Connect signals and slots
    // SendWindow to SendThread
    QObject::connect(&sendWindow, &SendWindow::imageSent, &sendThread, &SendThread::sendImage);
    QObject::connect(&sendWindow, &SendWindow::clearSignal, &sendThread, &SendThread::signalClear);

    // SendThread to ReceiveThread
    QObject::connect(&sendThread, &SendThread::betweenSent, &receiveThread, &ReceiveThread::receiveImage);
    QObject::connect(&sendThread, &SendThread::betweenClear, &receiveThread, &ReceiveThread::receiveClear);

    // ReceiveThread to ReceiveWindow
    QObject::connect(&receiveThread, &ReceiveThread::imageReceived, &receiveWindow, &ReceiveWindow::receiveImage);
    QObject::connect(&receiveThread, &ReceiveThread::clearReceived, &receiveWindow, &ReceiveWindow::receiveClear);

    sendWindow.show();
    receiveWindow.show();

    return app.exec();
}
