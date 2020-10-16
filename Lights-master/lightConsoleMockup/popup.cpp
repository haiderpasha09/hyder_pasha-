#include "popup.h"
#include"ui_FixFunction.h"

extern FixtureFuncs FixFuncs[6];

PopUp::PopUp(int Type, QDialog *parent) : QDialog(parent)
{
    qRegisterMetaType<PopUpReturn>("PopUpReturn");
    QObject::connect(&btn1, SIGNAL(clicked()), this, SLOT(setInputVal_SLOT()));

    setWindowFlags(Qt::FramelessWindowHint |        // Disable window decoration
                   Qt::Tool | //Qt::Dialog |                       // Discard display in a separate window
                       Qt::WindowStaysOnTopHint);       // Set on top of all windows

    setAttribute(Qt::WA_TranslucentBackground);     // Indicates that the background will be transparent
    setAttribute(Qt::WA_ShowWithoutActivating);     // At the show, the widget does not get the focus automatically
    setAttribute(Qt::WA_DeleteOnClose);

    animation.setTargetObject(this);                // Set the target animation
    animation.setPropertyName("popupOpacity");      //
    connect(&animation, &QAbstractAnimation::finished, this, &PopUp::hide);
    this->setMinimumSize(QSize(400,220));


    //   StartPoint.setX(parent->x());
    //   StartPoint.setY(parent->y());
    //set font
    QFont f( "Arial", 16, QFont::Normal);
    label.setFont(f);
    QFont f2( "Arial", 11, QFont::Normal);
    if(Type == 0){                          //For Single item return like songname , duration etc
        btn1.setFont(f2);
        Input1.setFont(f2);
        label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label.setStyleSheet(greyLblClr);
        Input1.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Input1.setStyleSheet("color:white;background-color: rgb(127, 127, 127);"
                                 "border-style: solid;border-color: rgb(120, 120, 120)"
                                 ";border-width: 1px;border-radius: 5px;\n"
                                 "color:rgb(255, 255, 255);\n");
        label.setMinimumHeight(30);
        Input1.setMinimumHeight(30);
        btn1.setText("Apply");
        btn1.setMinimumHeight(30);
        btn1.setStyleSheet(blueBtnClr);
        Vlayout.addStretch(1);
        Vlayout.addWidget(&label);
        Vlayout.addWidget(&Input1);
        Vlayout.addWidget(&btn1);
        Vlayout.addStretch(1);
        setLayout(&Vlayout);
    }
    if(Type == 1){                          //For Three Item return for Manufacturer, Model and Modes
        btn1.setFont(f2);
        Input1.setFont(f2);
        label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label.setStyleSheet(greyLblClr);
        label.setMinimumHeight(30);
        label2.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label2.setStyleSheet(greyLblClr);
        label2.setMinimumHeight(30);
        label3.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label3.setStyleSheet(greyLblClr);
        label3.setMinimumHeight(30);
        Input1.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Input1.setStyleSheet(greyInputClr);
        Input1.setMinimumHeight(30);
        Input2.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Input2.setStyleSheet(greyInputClr);
        Input2.setMinimumHeight(30);
        Input3.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Input3.setStyleSheet(greyInputClr);
        Input3.setMinimumHeight(30);
        btn1.setText("Apply");
        btn1.setMinimumHeight(30);
        btn1.setStyleSheet(blueBtnClr);
        Vlayout.addStretch(1);
        Vlayout.addWidget(&label);
        Vlayout.addWidget(&Input1);
        Vlayout.addWidget(&label2);
        Vlayout.addWidget(&Input2);
        Vlayout.addWidget(&label3);
        Vlayout.addWidget(&Input3);
        Vlayout.addWidget(&btn1);
        Vlayout.addStretch(1);
        setLayout(&Vlayout);
    }
    if(Type == 2) {                       // For
        QWidget * W[6], *iW[6];
        mButtons * btn[6][11];
        QVBoxLayout * L[6], * iL[6];
        QScrollArea * Scr[6];
        //QPushButton btn;
//        btn.setText(FuncGroup[0]);
        HLayout.addStretch(1);
        //int fgrp = 0;{
        for (int fgrp=0; fgrp<6; fgrp++){
            W[fgrp] = new QWidget;
            iW[fgrp] = new QWidget;
            iL[fgrp] = new QVBoxLayout;
            L[fgrp] = new QVBoxLayout;
            Scr[fgrp] = new QScrollArea;
            btn[fgrp][0] = new mButtons;
            btn[fgrp][0]->setStyleSheet(greyBtnClr);
            btn[fgrp][0]->setText(FixFuncs[fgrp].GroupName);
            btn[fgrp][0]->setMinimumHeight(30);
            btn[fgrp][0]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            L[fgrp]->addStretch(1);
            L[fgrp]->addWidget(btn[fgrp][0]);
            for(int funcs = 0; funcs < FixFuncs[fgrp].Name.size(); funcs++){
                btn[fgrp][funcs+1] = new mButtons;
                btn[fgrp][funcs+1]->setStyleSheet(blueBtnClr);
                btn[fgrp][funcs+1]->setText(FixFuncs[fgrp].Name.at(funcs));
                btn[fgrp][funcs+1]->setButtonType(FixFuncs[fgrp].Name.at(funcs));
                btn[fgrp][funcs+1]->setMinimumHeight(30);
                btn[fgrp][funcs+1]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                connect(btn[fgrp][funcs+1], SIGNAL(released()), this, SLOT(SelectionEntered()));
                iL[fgrp]->addWidget(btn[fgrp][funcs+1],1, Qt::AlignTop);
            }
            iL[fgrp]->setAlignment(Qt::AlignTop);
            iL[fgrp]->setContentsMargins(0,0,0,0);
            //iL[fgrp]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
            iW[fgrp]->setLayout(iL[fgrp]);
            iW[fgrp]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

            Scr[fgrp]->setWidget(iW[fgrp]);
            Scr[fgrp]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
            Scr[fgrp]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            Scr[fgrp]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0.551, x2:1, y2:0.54, stop:0 rgba(38, 38, 38, 255), stop:1 rgba(0, 0, 0, 255)); border:none;");
            Scr[fgrp]->setContentsMargins(0,0,0,0);
            Scr[fgrp]->setAlignment(Qt::AlignTop);
            Scr[fgrp]->setMinimumHeight(FixFuncs[fgrp].Name.size()*30);
            L[fgrp]->addWidget(Scr[fgrp]);
            btn[fgrp][10] = new mButtons;
            btn[fgrp][10]->setStyleSheet(greyBtnClr);
            //btn[fgrp][0]->setText(FixFuncs[fgrp].GroupName);
            btn[fgrp][10]->setMinimumHeight(30);
            btn[fgrp][10]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            btn[fgrp][10]->setText("Add");
            L[fgrp]->addWidget(btn[fgrp][10]);
            L[fgrp]->addStretch(1);
            L[fgrp]->setContentsMargins(3,3,3,3);
            L[fgrp]->setAlignment(Qt::AlignTop);
            W[fgrp]->setLayout(L[fgrp]);
            W[fgrp]->layout()->setAlignment(Qt::AlignTop);
            W[fgrp]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
            W[fgrp]->setMinimumWidth(this->size().width()/8);
            W[fgrp]->setContentsMargins(0,0,0,0);
            HLayout.addWidget(W[fgrp], 1, Qt::AlignTop);
            HLayout.setContentsMargins(3,3,3,3);
            HLayout.setSpacing(0);
            HLayout.addStretch(1);
            //HLayout.addLayout(L[fgrp].layout());
        }
    }
        if(Type == 5) {                       // For
            QWidget * FixFunction;
            QVBoxLayout * iverticalLayout[6];
            QVBoxLayout * overticalLayout[6];
            QHBoxLayout * oHorizlayout;
            QHBoxLayout * Horizlayout1[6];
            QHBoxLayout * Horizlayout2[6];
            QHBoxLayout * Horizlayout3[6];
            //QPushButton * tpushButton[6];
            QScrollArea * scrollArea[6];
            QWidget *scrollAreaWidgetContents[6];
            QVBoxLayout * vLbutton[6];
            //QVBoxLayout *verticalLayout_3;
            //QPushButton * bpushButton[6];
            QWidget * widget;
            mButtons * btn[6][11];

            FixFunction = new QWidget;
                    //if (FixFunction->objectName().isEmpty())
            FixFunction->setObjectName(QString::fromUtf8("FixFunction"));
            //FixFunction->resize(113, 300);


            FixFunction->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0.551, x2:1, y2:0.54, stop:0 rgba(38, 38, 38, 255), stop:1 rgba(0, 0, 0, 255));");
            oHorizlayout = new QHBoxLayout(FixFunction);

            for (int g = 0; g < 6; g++){
                Horizlayout1[g] = new QHBoxLayout;
                Horizlayout2[g] = new QHBoxLayout;
                Horizlayout3[g] = new QHBoxLayout;
                iverticalLayout[g] = new QVBoxLayout();
                iverticalLayout[g]->setSpacing(3);
                iverticalLayout[g]->setObjectName(QString::fromUtf8("verticalLayout_2"));
                iverticalLayout[g]->setContentsMargins(2, 2, 2, 2);
                overticalLayout[g] = new QVBoxLayout();
                overticalLayout[g]->setObjectName(QString::fromUtf8("verticalLayout"));
                btn[g][0] = new mButtons;
                btn[g][0]->setObjectName(QString::fromUtf8("pushButton"));
                btn[g][0]->setMinimumSize(QSize(0, 30));
//                btn[g][0]->setStyleSheet(QString::fromUtf8("QPushButton{background-color: qlineargradient(spread:pad, x1:0, y1:0.568, x2:1, y2:0.574, stop:0 rgba(79, 79, 79, 255), stop:1 rgba(39, 38, 38, 255));border-style: solid;border-color: rgba(0, 0, 0, 255);border-width: 0px;border-radius: 5px;} "));
                btn[g][0]->setStyleSheet(greyBtnClr);
                btn[g][0]->setText(FixFuncs[g].GroupName);
                Horizlayout1[g]->addWidget(btn[g][0]);
                overticalLayout[g]->addLayout(Horizlayout1[g]);

                scrollArea[g] = new QScrollArea();
                scrollArea[g]->setObjectName(QString::fromUtf8("scrollArea"));
                scrollArea[g]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                scrollArea[g]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
                sizePolicy.setHorizontalStretch(0);
                sizePolicy.setVerticalStretch(0);
                sizePolicy.setHeightForWidth(scrollArea[g]->sizePolicy().hasHeightForWidth());
                scrollArea[g]->setSizePolicy(sizePolicy);
                scrollArea[g]->setStyleSheet("QScrollArea {background-color:transparent;}");
                scrollArea[g]->setFrameShape(QFrame::NoFrame);
                scrollArea[g]->setWidgetResizable(true);
                scrollAreaWidgetContents[g] = new QWidget();
                scrollAreaWidgetContents[g]->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
                scrollAreaWidgetContents[g]->setGeometry(QRect(0, 0, 88, 16));
                scrollAreaWidgetContents[g]->setStyleSheet(QString::fromUtf8("background-color:transparent; border-width: 0px"));
                scrollArea[g]->setMinimumHeight(FixFuncs[g].Name.size()*30);
                vLbutton[g] = new QVBoxLayout(scrollAreaWidgetContents[g]);
                vLbutton[g]->setSpacing(3);
                vLbutton[g]->setObjectName(QString::fromUtf8("verticalLayout_4"));
                vLbutton[g]->setContentsMargins(0, 0, 0, 0);
                for(int funcs = 0; funcs < FixFuncs[g].Name.size(); funcs++){
                    btn[g][funcs+2] = new mButtons;
                    btn[g][funcs+2]->setStyleSheet(blueBtnClr);
                    btn[g][funcs+2]->setText(FixFuncs[g].Name.at(funcs));
                    btn[g][funcs+2]->setButtonType(FixFuncs[g].Name.at(funcs));
                    btn[g][funcs+2]->setMinimumHeight(30);
                    btn[g][funcs+2]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                    connect(btn[g][funcs+2], SIGNAL(released()), this, SLOT(SelectionEntered()));
                    vLbutton[g]->addWidget(btn[g][funcs+2],1, Qt::AlignTop);
                }
                //verticalLayout_3 = new QVBoxLayout();
                //verticalLayout_3->setSpacing(3);
                //verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

                //verticalLayout_4->addLayout(verticalLayout_3);
                scrollAreaWidgetContents[g]->setLayout(vLbutton[g]);
                scrollArea[g]->setWidget(scrollAreaWidgetContents[g]);
                Horizlayout2[g]->addWidget(scrollArea[g]);
                //Horizlayout2[g]->setStyleSheet(QString::fromUtf8("background-color:transparent; border-width: 0px"));
                overticalLayout[g]->addLayout(Horizlayout2[g]);

                btn[g][1] = new mButtons;
                btn[g][1]->setObjectName(QString::fromUtf8("pushButton_2"));
                btn[g][1]->setMinimumSize(QSize(0, 30));
                btn[g][1]->setStyleSheet(greyBtnClr);
                btn[g][1]->setID(g);
                btn[g][1]->setText("Add");
                Horizlayout3[g]->addWidget(btn[g][1]);
                overticalLayout[g]->addLayout(Horizlayout3[g]);

                widget = new QWidget();
                widget->setObjectName(QString::fromUtf8("widget"));
                QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
                sizePolicy1.setHorizontalStretch(0);
                sizePolicy1.setVerticalStretch(0);
                sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
                widget->setSizePolicy(sizePolicy1);

                overticalLayout[g]->addWidget(widget);


                iverticalLayout[g]->addLayout(overticalLayout[g]);
                oHorizlayout->addLayout(iverticalLayout[g]);

            }
            setLayout(oHorizlayout);

            /*
             * QWidget * W[6], *iW[6];
            mButtons * btn[6][11];
            QVBoxLayout * L[6], * iL[6];
            QScrollArea * Scr[6];
            //QPushButton btn;
    //        btn.setText(FuncGroup[0]);
            HLayout.addStretch(1);
            //int fgrp = 0;{
            for (int fgrp=0; fgrp<6; fgrp++){
                W[fgrp] = new QWidget;
                iW[fgrp] = new QWidget;
                iL[fgrp] = new QVBoxLayout;
                L[fgrp] = new QVBoxLayout;
                Scr[fgrp] = new QScrollArea;
                btn[fgrp][0] = new mButtons;
                btn[fgrp][0]->setStyleSheet(greyBtnClr);
                btn[fgrp][0]->setText(FixFuncs[fgrp].GroupName);
                btn[fgrp][0]->setMinimumHeight(30);
                btn[fgrp][0]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
                L[fgrp]->addStretch(1);
                L[fgrp]->addWidget(btn[fgrp][0]);
                for(int funcs = 0; funcs < FixFuncs[fgrp].Name.size(); funcs++){
                    btn[fgrp][funcs+1] = new mButtons;
                    btn[fgrp][funcs+1]->setStyleSheet(blueBtnClr);
                    btn[fgrp][funcs+1]->setText(FixFuncs[fgrp].Name.at(funcs));
                    btn[fgrp][funcs+1]->setButtonType(FixFuncs[fgrp].Name.at(funcs));
                    btn[fgrp][funcs+1]->setMinimumHeight(30);
                    btn[fgrp][funcs+1]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
                    connect(btn[fgrp][funcs+1], SIGNAL(released()), this, SLOT(SelectionEntered()));
                    iL[fgrp]->addWidget(btn[fgrp][funcs+1],1, Qt::AlignTop);
                }
                iL[fgrp]->setAlignment(Qt::AlignTop);
                iL[fgrp]->setContentsMargins(0,0,0,0);
                //iL[fgrp]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
                iW[fgrp]->setLayout(iL[fgrp]);
                iW[fgrp]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

                Scr[fgrp]->setWidget(iW[fgrp]);
                Scr[fgrp]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
                Scr[fgrp]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
                Scr[fgrp]->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0, y1:0.551, x2:1, y2:0.54, stop:0 rgba(38, 38, 38, 255), stop:1 rgba(0, 0, 0, 255)); border:none;");
                Scr[fgrp]->setContentsMargins(0,0,0,0);
                Scr[fgrp]->setAlignment(Qt::AlignTop);
                Scr[fgrp]->setMinimumHeight(FixFuncs[fgrp].Name.size()*30);
                L[fgrp]->addWidget(Scr[fgrp]);
                btn[fgrp][10] = new mButtons;
                btn[fgrp][10]->setStyleSheet(greyBtnClr);
                //btn[fgrp][0]->setText(FixFuncs[fgrp].GroupName);
                btn[fgrp][10]->setMinimumHeight(30);
                btn[fgrp][10]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
                btn[fgrp][10]->setText("Add");
                L[fgrp]->addWidget(btn[fgrp][10]);
                L[fgrp]->addStretch(1);
                L[fgrp]->setContentsMargins(3,3,3,3);
                L[fgrp]->setAlignment(Qt::AlignTop);
                W[fgrp]->setLayout(L[fgrp]);
                W[fgrp]->layout()->setAlignment(Qt::AlignTop);
                W[fgrp]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
                W[fgrp]->setMinimumWidth(this->size().width()/8);
                W[fgrp]->setContentsMargins(0,0,0,0);
                HLayout.addWidget(W[fgrp], 1, Qt::AlignTop);
                HLayout.setContentsMargins(3,3,3,3);
                HLayout.setSpacing(0);
                HLayout.addStretch(1);
                //HLayout.addLayout(L[fgrp].layout());
            }
        //setLayout(L[fgrp]);
        setLayout(&HLayout);
        */
    }
    if(Type == 3){                          //For Four Item return for Min Max values
        btn1.setFont(f2);
        Input1.setFont(f2);
        label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label.setStyleSheet(greyLblClr);
        label.setMinimumHeight(30);
        label2.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label2.setStyleSheet(greyLblClr);
        label2.setMinimumHeight(30);
        label3.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label3.setStyleSheet(greyLblClr);
        label3.setMinimumHeight(30);
        label4.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label4.setStyleSheet(greyLblClr);
        label4.setMinimumHeight(30);
        label5.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label5.setStyleSheet(greyLblClr);
        label5.setMinimumHeight(30);
        Input1.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Input1.setStyleSheet(greyInputClr);
        Input1.setMinimumHeight(30);
        Input2.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Input2.setStyleSheet(greyInputClr);
        Input2.setMinimumHeight(30);
        Input3.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Input3.setStyleSheet(greyInputClr);
        Input3.setMinimumHeight(30);
        Input4.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Input4.setStyleSheet(greyInputClr);
        Input4.setMinimumHeight(30);
        Input5.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Input5.setStyleSheet(greyInputClr);
        Input5.setMinimumHeight(30);
        btn1.setText("Apply");
        btn1.setMinimumHeight(30);
        btn1.setStyleSheet(blueBtnClr);
        Vlayout.addStretch(1);
        Vlayout.addWidget(&label);
        Vlayout.addWidget(&Input1);
        Vlayout.addWidget(&label2);
        Vlayout.addWidget(&Input2);
        Vlayout.addWidget(&label3);
        Vlayout.addWidget(&Input3);
        Vlayout.addWidget(&label4);
        Vlayout.addWidget(&Input4);
        Vlayout.addWidget(&label5);
        Vlayout.addWidget(&Input5);
        Vlayout.addWidget(&btn1);
        Vlayout.addStretch(1);
        setLayout(&Vlayout);
    }


    //setGeometry(parent->x()+100,parent->y()+40, 400, 220);

        pDiaShadow = new ShadowLib();
        pDiaShadow ->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Dialog | Qt::WindowStaysOnTopHint);
        pDiaShadow->show ();
        pDiaShadow->setAttribute(Qt::WA_TranslucentBackground);     // Indicates that the background will be transparent
        pDiaShadow->setAttribute(Qt::WA_ShowWithoutActivating);     // At the show, the widget does not get the focus automatically
        pDiaShadow->setAttribute(Qt::WA_DeleteOnClose);
        pDiaShadow->setWindowOpacity(0.5);
        pDiaShadow->setFocusPolicy(Qt::NoFocus);
    //   pDiaShadow->setGeometry(position.x()-10,position.y()-10, this->geometry().width(),this->geometry().height());
       connect(pDiaShadow, SIGNAL(GotFocus()) , this, SLOT(RaisePopUp()));
    timer = new QTimer();
}

void PopUp::RaisePopUp()
{
    this->raise();
    this->setFocus();
}
//PopUp::~PopUp()
//{
//    delete this;
//}

QString PopUp::mGetTimeCode()
{
    return mInput;
}

void PopUp::mSetPlaceHolder(int pos, QString val)
{
    if (pos == 1) Input1.setPlaceholderText(val);
    if (pos == 2) Input2.setPlaceholderText(val);
    if (pos == 3) Input3.setPlaceholderText(val);
    if (pos == 4) Input4.setPlaceholderText(val);
    if (pos == 5) Input5.setPlaceholderText(val);
}

void PopUp::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(QColor(0,0,0,180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect, 10, 10);


    // inner rect
    QRect roundedRect2;
    roundedRect2.setX(rect().x() + 5);
    roundedRect2.setY(rect().y() + 100);
    roundedRect2.setWidth(rect().width() - 10);
    roundedRect2.setHeight(rect().height() - 200);

    painter.setBrush(QBrush(QColor(0,0,0,255)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect2, 10, 10);
}

void PopUp::setPopupText(int pos, const QString &text)
{
    if (pos == 1) label.setText(text);    // Set the text in the Label
    if (pos == 2) label2.setText(text);    // Set the text in the Label
    if (pos == 3) label3.setText(text);    // Set the text in the Label
    if (pos == 4) label4.setText(text);    // Set the text in the Label
    if (pos == 5) label5.setText(text);    // Set the text in the Label
    //adjustSize();           // With the recalculation notice sizes
}

void PopUp::show()
{
    setWindowOpacity(0.0);  // Set the transparency to zero

    animation.setDuration(100);     // Configuring the duration of the animation
    animation.setStartValue(0.0);   // The start value is 0 (fully transparent widget)
    animation.setEndValue(0.92);     // End - completely opaque widget

    //    setGeometry(QApplication::desktop()->availableGeometry().width() - 36 - width() + QApplication::desktop() -> availableGeometry().x(),
    //                QApplication::desktop()->availableGeometry().height() - 36 - height() + QApplication::desktop() -> availableGeometry().y(),
    //                width(),
    //                height());
    //setGeometry(StartPoint.x()+100,StartPoint.y()+40, width(), height());
    QDialog::show();

    animation.start();
    timer->start(200);
}

void PopUp::SelectionEntered(){
    mButtons *button = qobject_cast<mButtons *>(QObject::sender());
    mOutPut.s1 = button->getButtonType();
    vOut.setValue(mOutPut);
    emit valueEntered_SIGNAL(vOut);
    delete pDiaShadow;
    delete this;
}

void PopUp::setInputVal_SLOT()
{

    mOutPut.s1 = Input1.text();
    if(mOutPut.s1 == "") mOutPut.s1 = Input1.placeholderText();
    mOutPut.s2 = Input2.text();
    if(mOutPut.s2 == "") mOutPut.s2 = Input2.placeholderText();
    mOutPut.s3 = Input3.text();
    if(mOutPut.s3 == "") mOutPut.s3 = Input3.placeholderText();
    mOutPut.s4 = Input4.text();
    if(mOutPut.s4 == "") mOutPut.s4 = Input4.placeholderText();
    mOutPut.s5 = Input5.text();
    if(mOutPut.s4 == "") mOutPut.s5 = Input4.placeholderText();

    vOut.setValue(mOutPut);
    emit valueEntered_SIGNAL(vOut);
    //emit ExtraValues(mInput, In2, In3, In4);
    delete pDiaShadow;
    delete this;
}

void PopUp::hideAnimation()
{
    timer->stop();
    animation.setDuration(10);
    animation.setStartValue(1.0);
    animation.setEndValue(0.0);
    animation.start();
    pDiaShadow->deleteLater();
    timer->deleteLater();
}

void PopUp::hide()
{
    // If the widget is transparent, then hide it
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
    }
}

void PopUp::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

float PopUp::getPopupOpacity() const
{
    return popupOpacity;
}

int iXdeffarace = -1;
int iYdeffarance  = -1;
bool b_mousePressed;

void PopUp::mousePressEvent ( QMouseEvent * event)
{
    b_mousePressed = true;
    QPoint qpMousePressedPoint = QCursor::pos();
    QPoint qpApploc = this->pos();
    iXdeffarace = qpMousePressedPoint.x() - qpApploc.x();
    iYdeffarance = qpMousePressedPoint.y() - qpApploc.y();
}

void PopUp::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
    if(event->key() == Qt::Key_Q)
    {
//        qDebug() << "You Pressed Key Q";
    }
    else
    {
//        qDebug() << "You Pressed Other Key" ;
    }
}

void PopUp::keyReleaseEvent(QKeyEvent *event)
{
//    qDebug() << " ----------------- ";
//    qDebug() << event->key();
    if(event->key() == Qt::Key_Escape)
    {
        this->hide();
        hideAnimation();
    }
    else
    {
//        qDebug() << "You Pressed Other Key" ;
    }
}

//********************************************************
void PopUp::mouseReleaseEvent ( QMouseEvent * event )
{
    b_mousePressed = false;
}

//********************************************************
void PopUp::mouseMoveEvent ( QMouseEvent * event )
{
    if(b_mousePressed)
    {
        QPoint qpAppNewLoc(  (QCursor::pos().x() - iXdeffarace) , (QCursor::pos().y() - iYdeffarance)  );
        this->setProperty("pos", qpAppNewLoc);
    }
}
void PopUp::setSize(int h, int w){
    qDebug() << " -> " << h << " - " << w;
    this->setMinimumSize(QSize(w,h));
}
void PopUp::rePosition(int x, int y){
    QPoint qpAppNewLoc( x,y );
    this->setProperty("pos", qpAppNewLoc);
}


