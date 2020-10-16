#include "mbuttons.h"

mButtons::mButtons(QWidget *parent) :
    QPushButton(parent)
{
    this->setMinimumHeight(30);
    //    this->setMaximumWidth(80);
       ResID++;            // Increment of counter by one
    buttonID = ResID;    /* Assigning a button number which will be further work with buttons
                         * */
    emit btnAdded_SIGNAL();

    //    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);


//        connect(this, SIGNAL(mousePressedSIGNAL() ), screen, SLOT(switch_cue2Step()));
}
mButtons::~mButtons()
{

}

/* Method to return the value of the button numbers
 * */
void mButtons::setID(int id){
    buttonID = id;
}

void mButtons::setCueID(int id)
{
    cueID = id;
}

int mButtons::getCueID()
{
    return cueID;
}

void mButtons::setStepID(int id)
{
    stepID = id;
}

int mButtons::getStepID()
{
    return  stepID;
}
int mButtons::getID()
{
    return buttonID;
}


void mButtons::setButtonType(QString type){
    btnType = type;
}

QString mButtons::getButtonType(){
    return btnType;
}


/* Initialize static class variable.
 * Static class variable must be initialized without fail
 * */
int mButtons::ResID = 0;
bool preventagain = false;

void mButtons::mousePressEvent(QMouseEvent *)
{
    // Remeber last time mousr was pressed
//    qDebug() << " mousePressEvent";
//qDebug() << "btnType" << btnType;
//    preventagain = false;
//    if(preventagain == false){
        isPressed = true;
        preventagain = true;
        QTimer::singleShot(MY_LONG_PRESS_THRESHOLD, this, SLOT(mousePressedSLOT()));
//    }
//    emit clicked();


}

void mButtons::mouseReleaseEvent(QMouseEvent *)
{
    isPressed = false;
    //  qDebug() << " mouseReleaseEvent";
    if (preventagain == true) {
        emit released();
     }

}
void mButtons::mousePressedSLOT()
{
//    qDebug() << btnType;
    preventagain = false;
//    if ( btnType == "cue" )
//    {
//        if(isPressed){
//            popUp = new PopUp();
//            popUp->setPopupText("Add Step Name");
//            popUp->show();
          //  connect(popUp, SIGNAL(valueEntered_SIGNAL(QString)) , this, SLOT(setBtnVal_SLOT(QString)));
//            this->getSongName();
//            emit switchCue2Step_SIGNAL();
//        }
//    } else {
        if(isPressed){
            emit editButton_SIGNAL();
        }
}




void mButtons::setBtnVal_SLOT(QString val)
{
    this->setText(val);

}
