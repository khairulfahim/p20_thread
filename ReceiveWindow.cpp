#include "ReceiveWindow.h"
#include <QPainter>

ReceiveWindow::ReceiveWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Receive Window");
}

void ReceiveWindow::deserializeImage(const QByteArray &imageData){
    QDataStream stream(imageData);
    stream >> receivedImage;
    update();
}

QByteArray ReceiveWindow::bittobyte(const QBitArray &sendBit) {
    QByteArray byteArray((sendBit.size() + 7) / 8, '\0'); // Initialize byte array with appropriate size

    // Convert each bit in the QBitArray to a byte in the QByteArray
    for (int i = 0; i < sendBit.size(); ++i) {
        if (sendBit.testBit(i)) {
            byteArray[i / 8] |= (1 << (i % 8)); // Set the corresponding bit in the byte
        }
    }
    return byteArray;
}

void ReceiveWindow::receiveImage(const QBitArray &sendBit) {
    // Convert the received QBitArray back to a QByteArray
    QByteArray receiveByte = bittobyte(sendBit);
    deserializeImage(receiveByte);
}

void ReceiveWindow::receiveClear() {
    // Clear the received image
    receivedImage = QImage(receivedImage.size(), receivedImage.format());
    receivedImage.fill(Qt::white);
    update();
}

void ReceiveWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    painter.drawImage(0, 0, receivedImage);
}
