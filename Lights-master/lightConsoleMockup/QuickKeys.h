#ifndef QuickKeys_H
#define QuickKeys_H

#include <QWidget>
#include <QDebug>
#include "Programmer.h"

namespace Ui {
class QuickKeys;
}

class QuickKeys : public QWidget
{
    Q_OBJECT

public:
    explicit QuickKeys(QWidget *parent = 0);
    ~QuickKeys();
    void Change_Color(int iD, QColor BasColor);

private slots:
    void on_pushButton_2_clicked();


    void on_pbDelete_clicked();

    void on_pbEdit_clicked();

signals:
    void deleteSong_SIGNAL();
    void editSong_SIGNAL();


private:
    Ui::QuickKeys *ui;
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void deleteSong_SLOT();
};

#endif // SCREEN_3_H
