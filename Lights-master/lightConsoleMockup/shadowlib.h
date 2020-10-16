#ifndef SHADOWLIB_H
#define SHADOWLIB_H

#include <QDialog>

class ShadowLib : public QDialog
{
    Q_OBJECT
public:
    explicit ShadowLib(QDialog *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);    // The background will be drawn through the redraw method

signals:
    void GotFocus();
};

#endif // SHADOWLIB_H
