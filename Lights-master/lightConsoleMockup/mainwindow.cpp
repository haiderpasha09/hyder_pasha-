#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dials.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    this->setWindowState(Qt::WindowMinimized);
    //this->setWindowState(windowState() | Qt::WindowFullScreen);
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    //this->showFullScreen();

    qDebug() << "ui->widget_3 size and location of this widget  " <<  ui->centralwidget->size() << " -- " << ui->widget_LT->geometry();

//    s2 = new screen_2;
//    screen_3 screen3;
//    screen_3 * cwidget = new screen_3(this);
//    screen_1 * cwidget1= new screen_1(this);
//    connect(ui->widget_11 , SIGNAL(deleteSong_SIGNAL()) , ui->widget_6 , SLOT(deleteSong_SLOT()));


//    screen_3 screen3;
//    screen_1 screen1;
//    connect(&screen3 , SIGNAL(deleteSong()) , &screen1 , SLOT(deleteSong()));

//    f = new Form();
//    f->move(0,0);
////    f->mapToGlobal(QPoint(0,0));
///




//    s2->setAttribute( Qt::WA_QuitOnClose, false );

//    s3 = new screen_3();
//    s3->show();

//    s3->setAttribute( Qt::WA_QuitOnClose, false );

//    s4 = new screen_4();
//    s4->show();

//    s4->setAttribute( Qt::WA_QuitOnClose, false );

    //ui->widget_11->heightForWidth()


    Stg = new Stage;
    QHBoxLayout *StLay = new QHBoxLayout;
    StLay->setContentsMargins(0,0,0,0);
        StLay->addWidget(Stg);
        ui->widget_MT->setLayout(StLay);

     leftControls * s3 = new leftControls;
     ui->gLLeftWindow->layout()->addWidget(s3);

     ui->gLLeftWindow->layout()->setContentsMargins(0,0,0,0);

     connect(ui->widget_Dials, SIGNAL(DialChange_Signal(int, int)), Stg, SLOT(Dials_Changed_SLOT(int, int)));

//     connect(ui->widget_10, SIGNAL(HomeButtonClicked()), this, SLOT(LoadHome()));
     connect(ui->widget_Controller, SIGNAL(ProgramButtonClicked()), this, SLOT(LoadProgrammer()));
 //    auto layout = ;
     //s2->setObjectName(ui->widget_4.objectName());
     //ui->gLLeftWindow->layout()->addWidget(s3);
    connect(ui->widget_Controller, SIGNAL(FixtureWinSignal()), this, SLOT(LoadFixtureWinSlot()));

     //programmer * s1 = new programmer;
     //QHBoxLayout *BHLay = new QHBoxLayout;
     //BHLay->setContentsMargins(0,0,0,0);
     //    BHLay->addWidget(s1);
     //    ui->widget_LT->setLayout(BHLay);
     LoadProgrammer();



    QTimer::singleShot(500 , this, SLOT(connection_SLOT()) );



    QRect P = ui->centralwidget->geometry();
    P.setWidth(P.width());
    //QSize Q = event->size();
    Wid = 0;
//    if (P.width()> W){
        Wid = P.width()-54;
        qDebug() << "Application Width" << P;
        ui->LeftControlsSpacer->changeSize(20,Wid*3/60);

        ui->widget_LT->setMinimumWidth(Wid/3);
        ui->widget_LT->setMinimumHeight(Wid*3/16);
        qDebug() << ui->widget_LT->geometry();

        //ui->widget_3->setGeometry(0,0,P.width()/3, P.height()/3);
        ui->widget_MT->setMinimumWidth(Wid/3);
        ui->widget_MT->setMinimumHeight(Wid*3/16);
        qDebug() << ui->widget_MT->geometry();

        //ui->widget_6->setGeometry(0,0,P.width()/3, P.height()/3);
        ui->widget_RT->setMinimumWidth(Wid/3);
        ui->widget_RT->setMinimumHeight(Wid*3/16);
        qDebug() << ui->widget_RT->geometry();

        //ui->widget_5->setGeometry(0,0,P.width()/3, P.height()/3);
        ui->widget_Controller->setMinimumWidth(Wid/3);
        ui->widget_Controller->setMinimumHeight(Wid*3/16);
        qDebug() << ui->widget_Controller->geometry();

        ui->widget_RB->setMinimumWidth(Wid/3);
        ui->widget_RB->setMinimumHeight((Wid*3/16)*25/18);

        ui->widget_MB->setMinimumWidth(Wid/3);
        ui->widget_MB->setMinimumHeight((Wid*3/16)*25/18);

        ui->widget_LB->setMinimumWidth(Wid/3);
        ui->widget_LB->setMinimumHeight((Wid*3/16)*25/18);

        ui->widget_Dials->setMinimumHeight(Wid/12);
//    }
}

MainWindow::~MainWindow()
{
    //delete d;
    delete ui;

}

void MainWindow::resizeEvent(QResizeEvent *event)
{

    //ui->widget_10->setGeometry(0,0,P.width()/3, P.height()/3);
    // ui->LefTopScreen->layout()->children().at(0)->setProperty(geometry,ui->LefTopScreen->geometry()));
    //ui->LefTopScreen->setGeometry(ui->widget_3->geometry());
    //ui->LefTopScreen->setGeometry(QRect{0,0,ui->widget_3->geometry().width(), ui->widget_3->geometry().height()});
    //qDebug() << ui->widget_3->geometry();
    //qDebug() << ui->LefTopScreen->geometry();
    QWidget::resizeEvent(event);

}

void MainWindow::LoadProgrammer()
{
    programmer * s1 = new programmer;
    QHBoxLayout *BHLay = new QHBoxLayout;
    QRect Sz = ui->widget_LT->geometry();
    //if (ui->widget_LT->size() >0){
    //    ui->widget_LT->layout()->widget()->disconnect();
        delete ui->widget_LT->layout();
    //}
    BHLay->setContentsMargins(0,0,0,0);
        BHLay->addWidget(s1);
        ui->widget_LT->setLayout(BHLay);
        s1->setMinimumWidth(Sz.width());
        s1->setMinimumHeight(Sz.width()*9/16);
    connect(ui->widget_RT, SIGNAL(deleteSong_SIGNAL()) , s1, SLOT(deleteSong_SLOT()));
    connect(ui->widget_RT, SIGNAL(editSong_SIGNAL()) , s1, SLOT(editSongStep_SLOT()));
}
void MainWindow::LoadHome()
{
}

void MainWindow::LoadFixtureWinSlot(void){
    Fixture * Cp = new Fixture;
    QRect Sz = ui->widget_LT->geometry();
    //if (ui->widget_LT->layout()->count()>0){
    //    ui->widget_LT->layout()->widget()->disconnect();
        delete ui->widget_LT->layout();
    //}
    QHBoxLayout *BHLay = new QHBoxLayout;
        BHLay->addWidget(Cp);
        ui->widget_LT->setLayout(BHLay);
        BHLay->setContentsMargins(0,0,0,0);
        Cp->setMinimumWidth(Sz.width());
        Cp->setMinimumHeight(Sz.width()*9/16);
    //Cp->setGeometry(ui->LefTopScreen->geometry());
    qDebug() << Cp->geometry().x() << Cp->geometry().y();
    connect(ui->widget_RT, SIGNAL(deleteSong_SIGNAL()) , Cp , SLOT(DeleteButton(void)));
    connect(Cp, SIGNAL(AddFixturesSIGNAL(QVariant)), ui->widget_Controller, SLOT(AddFixturesSLOT(QVariant)));
    connect(Cp, SIGNAL(AddFixturesSIGNAL(QVariant)), Stg, SLOT(AddFixturesSLOT(QVariant)));
}
void MainWindow::LoadProgrammerWindow(int Song, int Cue, int Step){
    programmer * Cp = new programmer;
    //ui->LefTopScreen->layout()->removeAt(0);
    //QLayoutItem *child;
    //while ((child = ui->widget_3->layout()->layout()->takeAt(0)) != 0)
    //{
    //    delete child;
    //}
    delete ui->widget_LT->layout();
    QHBoxLayout *BHLay = new QHBoxLayout;
        BHLay->addWidget(Cp);


        ui->widget_LT->setLayout(BHLay);
        BHLay->setContentsMargins(0,0,0,0);
        //Cp->gAccess.selectedSong = Song;


    //ui->LefTopScreen->setGeometry(QRect{0,0,ui->widget_3->geometry().width(), ui->widget_3->geometry().height()});

}


void MainWindow::connection_SLOT()
{



//    ui->LefTopScreen->setGeometry( QRect{0,0,ui->widget_3->geometry().width(), ui->widget_3->geometry().height()-50});



//    this->setWindowState(windowState() | Qt::WindowFullScreen);
//    resizeEvent(0);
//    f->show();

//    delete layout;
    //ui->widget_4 = s2;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug() << ui->widget_MT->geometry();
}
