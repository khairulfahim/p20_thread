#ifndef RECEIVEWINDOW_H
#define RECEIVEWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QBitArray>

class ReceiveWindow : public QMainWindow {
    Q_OBJECT

public:
    ReceiveWindow(QWidget *parent = nullptr);

public slots:
    void receiveImage(const QBitArray &sendBit);
    void receiveClear();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage receivedImage;
};

#endif // RECEIVEWINDOW_H
