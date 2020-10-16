#include "shadowlib.h"

ShadowLib::ShadowLib(QDialog *parent) : QDialog(parent)
{

}
void ShadowLib::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    emit GotFocus();
}
