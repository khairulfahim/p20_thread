#include "SendWindow.h"
#include <QPainter>
#include <QDebug>
#include <QColorDialog>

SendWindow::SendWindow(QWidget *parent) : QMainWindow(parent), drawing(false) {
    setWindowTitle("Send Window");
    image = QImage(size(), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);

    clearButton = new QPushButton("Clear", this);
    clearButton->move(10, 10);
    connect(clearButton, &QPushButton::clicked, this, &SendWindow::clearDrawing);
}

QBitArray SendWindow::bytetobit(const QByteArray &imageData) {
    QBitArray bitArray;
    bitArray.resize(imageData.size() * 8); // Resize the bit array to hold enough bits
    for (int i = 0; i < imageData.size(); ++i) {
        char byte = imageData.at(i);
        for (int j = 0; j < 8; ++j) {
            // Set the corresponding bit in the bit array
            bitArray.setBit(i * 8 + j, (byte >> j) & 1);
        }
    }
    return bitArray;
}

void SendWindow::serializeImage(){
    QByteArray imageData;
    QDataStream stream(&imageData, QIODevice::WriteOnly);
    stream << image;
    //stream << this->image;

    QBitArray sendBit = bytetobit(imageData);
    emit imageSent(sendBit);
}
void SendWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        drawing = true;
        lastPos = event->pos();
    }
}

void SendWindow::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPainter painter(&image);
        painter.setPen(Qt::black);
        painter.drawLine(lastPos, event->pos());
        lastPos = event->pos();
        serializeImage();
        update();
    }
}

void SendWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        //emit imageSent(image.bits());
    }
}

void SendWindow::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void SendWindow::clearDrawing() {
    image.fill(Qt::white);
    update();
    emit clearSignal();
}
