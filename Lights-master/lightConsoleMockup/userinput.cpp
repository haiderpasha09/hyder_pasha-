#include "userinput.h"
#include "ui_userinput.h"

extern FixtureFuncs FixFuncs[6];

UserInput::UserInput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInput)
{

    setWindowFlags(Qt::FramelessWindowHint |        // Disable window decoration
                   Qt::Tool | Qt::Dialog |                       // Discard display in a separate window
                       Qt::WindowStaysOnTopHint);       // Set on top of all windows

    setAttribute(Qt::WA_TranslucentBackground);     // Indicates that the background will be transparent
    //setAttribute(Qt::WA_ShowWithoutActivating);     // At the show, the widget does not get the focus automatically
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowOpacity(0.9);
    ui->setupUi(this);
    //ui->stackedWidget->setMinimumWidth(this->geometry().width()/2);
    //ui->stackedWidget->setMinimumHeight(this->geometry().height()/2);
}

UserInput::~UserInput()
{
    delete ui;
}
void UserInput::Update(char * l1, char * T1, char * l2, char * T2, char * l3, char * T3, int pRef){
    ui->stackedWidget->setCurrentIndex(3);
    ui->label31->setText(l1);
    ui->lineEdit_31->setPlaceholderText(T1);
    ui->label32->setText(l2);
    ui->lineEdit_32->setPlaceholderText(T2);
    ui->label33->setText(l3);
    ui->lineEdit_33->setPlaceholderText(T3);
    ui->stackedWidget->setMinimumWidth(this->geometry().width()/2);
    ui->stackedWidget->setMinimumHeight(this->geometry().height()*2/3);
    CallerRef = pRef;
}
void UserInput::Query(QString Txt, QString hldr, int pRef)
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->label_2->setText(Txt);
    ui->lineEdit_2->setPlaceholderText(hldr);
    ui->stackedWidget->setMinimumWidth(this->geometry().width()/2);
    ui->stackedWidget->setMinimumHeight(this->geometry().height()/2);
    CallerRef = pRef;
}

void UserInput::Option(QString Txt, QString * options, int numopt, int pRef)
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->label_2->setText(Txt);
    for(int i = 0; i< numopt; i++){
        ui->cbOptions->addItem(options[i]);
    }
    ui->stackedWidget->setMinimumWidth(this->geometry().width()/2);
    ui->stackedWidget->setMinimumHeight(this->geometry().height()/2);
    CallerRef = pRef;
}

void UserInput::Info(int Type, QString txt, int pRef)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->label->setText(txt);
    if (Type == 0) {
        ui->pushButton_Cancel->hide();
    }
    ui->stackedWidget->setMinimumWidth(this->geometry().width()/2);
    ui->stackedWidget->setMinimumHeight(this->geometry().height()/3);
    CallerRef = pRef;
}

void UserInput::FixtureFunctions(int pRef)
{
    CallerRef = pRef;
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget->setMinimumWidth(this->geometry().width()/2);
    ui->stackedWidget->setMinimumHeight(this->geometry().height()/3);
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
        //sizePolicy.setHeightForWidth(scrollArea[g]->sizePolicy().hasHeightForWidth());
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
            btn[g][funcs+2]->setID(g);
            btn[g][funcs+2]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            connect(btn[g][funcs+2], SIGNAL(released()), this, SLOT(SelectionEntered()));
            vLbutton[g]->addWidget(btn[g][funcs+2],1, Qt::AlignTop);
        }
        //verticalLayout_3 = new QVBoxLayout();
        //verticalLayout_3->setSpacing(3);
        //verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        widget = new QWidget();
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        //sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);

        vLbutton[g]->addWidget(widget);

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




        iverticalLayout[g]->addLayout(overticalLayout[g]);
        oHorizlayout->addLayout(iverticalLayout[g]);

    }
    ui->page_Misc->setLayout(oHorizlayout);

}

void UserInput::SelectionEntered(){
    mButtons *button = qobject_cast<mButtons *>(QObject::sender());
    ReturnVals.s1 = button->getButtonType();
    ReturnVals.s2 = QString::number(button->getID());
    vOut.setValue(ReturnVals);
    emit valueEntered_SIGNAL(vOut);
    delete this;
}

void UserInput::show(){
    setWindowOpacity(0.92);
    QWidget::show();
}

void UserInput::on_pbAdd_clicked()
{
    ReturnVals.s1 = ui->lineEdit_2->text();
    if(ReturnVals.s1 == "") ReturnVals.s1 = ui->lineEdit_2->placeholderText();
    ReturnVals.Ref = CallerRef;
    vOut.setValue(ReturnVals);
    emit valueEntered_SIGNAL(vOut);
    delete this;
}

void UserInput::on_pushButton_3_clicked()
{
    ReturnVals.s1 = ui->lineEdit_31->text();
    if(ReturnVals.s1 == "") ReturnVals.s1 = ui->lineEdit_31->placeholderText();
    ReturnVals.s2 = ui->lineEdit_32->text();
    if(ReturnVals.s2 == "") ReturnVals.s2 = ui->lineEdit_32->placeholderText();
    ReturnVals.s3 = ui->lineEdit_33->text();
    if(ReturnVals.s3 == "") ReturnVals.s3 = ui->lineEdit_33->placeholderText();
    ReturnVals.Ref = CallerRef;
    vOut.setValue(ReturnVals);
    emit valueEntered_SIGNAL(vOut);
    delete this;
}

void UserInput::on_pushButton_OK_clicked()
{
    ReturnVals.s1 = ui->label->text();
    ReturnVals.s2 = "OK";
    ReturnVals.Ref = CallerRef;
    vOut.setValue(ReturnVals);
    emit valueEntered_SIGNAL(vOut);
    delete this;
}

void UserInput::on_pushButton_Cancel_clicked()
{
    ReturnVals.s1 = ui->label->text(); //Label value
    ReturnVals.s2 = "Cancel";
    ReturnVals.Ref = CallerRef;
    vOut.setValue(ReturnVals);
    emit valueEntered_SIGNAL(vOut);
    delete this;
}

void UserInput::on_pbAdd2_clicked()
{
    ReturnVals.s1 = ui->cbOptions->currentText(); //Label value
    ReturnVals.s2 = "Options";
    ReturnVals.Ref = CallerRef;
    vOut.setValue(ReturnVals);
    emit valueEntered_SIGNAL(vOut);
    delete this;
}

void UserInput::on_cbOptions_activated(const QString &arg1)
{

}

void UserInput::on_lineEdit_2_returnPressed()
{
    ReturnVals.s1 = ui->lineEdit_2->text();
    if(ReturnVals.s1 == "") ReturnVals.s1 = ui->lineEdit_2->placeholderText();
    ReturnVals.Ref = CallerRef;
    vOut.setValue(ReturnVals);
    emit valueEntered_SIGNAL(vOut);
    delete this;
}
void UserInput::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
        {
         close();

        }
}

MyLineEditt::MyLineEditt(QWidget *parent)
 : QLineEdit(parent)
{}

MyLineEditt::~MyLineEditt()
{}

void MyLineEditt::focusInEvent(QFocusEvent *e)
{
  QLineEdit::focusInEvent(e);
  emit(focussed(true));
}

void MyLineEditt::focusOutEvent(QFocusEvent *e)
{
  QLineEdit::focusOutEvent(e);
  emit(focussed(false));
}

