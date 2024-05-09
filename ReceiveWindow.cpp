#include "ReceiveWindow.h"
#include <QPainter>

ReceiveWindow::ReceiveWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Receive Window");
}

void ReceiveWindow::receiveImage(const QBitArray &sendBit) {
    // Convert the received QBitArray back to a QByteArray
    QByteArray receiveByte(sendBit.size() / 8, '\0');

    // Convert each byte in the QBitArray to a char in the QByteArray
    for (int i = 0; i < sendBit.size(); ++i) {
        receiveByte[i / 8] |= (sendBit[i] ? (1 << (i % 8)) : 0);
    }

    // Deserialize the QByteArray to QImage
    QImage receivedImage;
    receivedImage.loadFromData(receiveByte);
    this->receivedImage = receivedImage;
    update();
}

void ReceiveWindow::receiveClear() {
    // Clear the received image
    receivedImage = QImage();
    update();
}

void ReceiveWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    painter.drawImage(0, 0, receivedImage);
}
