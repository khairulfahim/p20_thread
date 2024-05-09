#ifndef SENDWINDOW_H
#define SENDWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QMouseEvent>
#include <QPushButton>
#include <QDataStream>
#include <QBitArray>

class SendWindow : public QMainWindow {
    Q_OBJECT

public:
    SendWindow(QWidget *parent = nullptr);
    QBitArray bytetobit(const QByteArray &imageData);

signals:
    void imageSent(const QBitArray &sendBit);
    void clearSignal(); // New signal for clearing the drawing

public slots:
    void clearDrawing();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void serializeImage();

private:
    bool drawing;
    QPoint lastPos;
    QImage image;
    QPushButton *clearButton;
};

#endif // SENDWINDOW_H
