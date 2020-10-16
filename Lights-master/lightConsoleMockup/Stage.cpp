#include "Stage.h"
#include "ui_Stage.h"

Stage::Stage(QWidget * parent) :
    QWidget(parent),
    ui(new Ui::Stage)
{
    ui->setupUi(this);



    //    scene->setBackgroundBrush(Qt::darkGray);
//    QImage img = QImage("F:\\QT_Projects\\qtGraphicView\\img.png");
//    QPixmap img2pix = QPixmap::fromImage(img);

    QTimer::singleShot(500 , this, SLOT(Timer_Slot()) );


    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

    //    customGraphic *cg = new customGraphic;
    //    cg->setScene(scene);

    //    this->setCentralWidget(cg);
    //    cg->show();
    ui->graphicsView->scale(0.3 , 0.3);
    //qDebug() <<  i*i << " time " << qtim.elapsed();
    ui->graphicsView->setFrameShape(QFrame::NoFrame);
    //    ui->graphicsView->setBackgroundBrush(Qt::black);
        ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
        ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
        ui->graphicsView->setScene(&GScene);

    QSizePolicy sp_retain = ui->pushButton_I1->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->pushButton_I1->setSizePolicy(sp_retain);
//    QSizePolicy sp_retain = ui->pushButton_I1->sizePolicy();
//    sp_retain.setRetainSizeWhenHidden(true);
    ui->pushButton_I2->setSizePolicy(sp_retain);
    ui->pushButton_I3->setSizePolicy(sp_retain);
    ui->pushButton_I4->setSizePolicy(sp_retain);

}


void Stage::AddFixturesSLOT(QVariant vParm ){
    ShowFixtures sfData;
    sfData = vParm.value<ShowFixtures>();
    AddFixtures(sfData.Mnfctr, sfData.Model, sfData.Mode, sfData.Quantity);
}
void Stage::Timer_Slot(void ){

//    QElapsedTimer qtim;

//        qtim.start();
}

void Stage::AddFixtures(QString Man, QString Modl, QString Mode, int Quantity ){
    //ShowFixtures sfData;
    //QGraphicsScene* scene = &GScene;
    //for (i = 0 ; i < 4 ; i++ )
    //{
    int j;
    int StageDisplayLine = 0;
    for(j = 0; j<TotFixtures; j++){
        if(StageDisplayLine < Fixtures[j]->pos().y())
            StageDisplayLine = Fixtures[j]->pos().y();
    }
    if (TotFixtures+Quantity < MAX_NUMBER_OF_FIXTURES){
        for ( j = TotFixtures; j < (TotFixtures + Quantity); j++ )
        {
            Fixtures[j] = new QtRectItem;
            Fixtures[j]->setID(1+j);
            Fixtures[j]->setRect(j * 60, j * 60,50,55);
            //if (i == 1){
            //     if (j<5) rect[i][j]->setPos(j * 60-300, i * 60);
            //     else rect[i][j]->setPos(j * 60 + 300, i * 60);
            //} else
            Fixtures[j]->setPos((j-TotFixtures) * 60, StageDisplayLine + 60);
            //Fixtures[j]->setFlags(QGraphicsItem::ItemIsMovable);
            Fixtures[j]->setBrush(Qt::lightGray);
            Fixtures[j]->setToolTip(Man +" " + Modl + " " + Mode);
            Fixtures[j]->setDetails( Man, Modl, Mode);
            //Fixtures[j]->position.paint();
            GScene.addItem(Fixtures[j]);
        }
    //}
        TotFixtures += Quantity;
    } else {
        //Do something ******************
    }

}

Stage::~Stage()
{
    delete ui;
}

void Stage::Dials_Changed_SLOT(int ID, int Val){
    if (ID == 1 && ListFuncs.size() > 0){
        ui->pushButton_I1->setText(ListFuncs.at(0).name +"\n"+QString::number(Val));
    }
    if (ID == 2 && ListFuncs.size() > 1){
        ui->pushButton_I2->setText(ListFuncs.at(1).name +"\n"+QString::number(Val));
    }
    if (ID == 3 && ListFuncs.size() > 2){
        ui->pushButton_I3->setText(ListFuncs.at(2).name +"\n"+QString::number(Val));
    }
    if (ID == 4 && ListFuncs.size() > 3){
        ui->pushButton_I4->setText(ListFuncs.at(3).name +"\n"+QString::number(Val));
    }
}

void Stage::deleteObjects(){
    // delete rect[del++][del2++];

    for (int i = 0 ; i < 300 ; i++ )
    {
        for (int j = 0; j < 300; j++ )
        {
            //delete rect[i][j];
            // usleep(1);
            QCoreApplication::processEvents();
        }
    }
}

void Stage::resizeEvent(QResizeEvent *event){

    //ui->widget_2->setMinimumHeight(event->size().height()/8);
    //ui->widget->setMinimumHeight(event->size().height()*6/8);


    //ui->pushButton_10->setMinimumWidth(event->size().width()/9);

    qDebug() << "Stage Screen Size" << event->size();

    qDebug() << event->size();
    QWidget::resizeEvent(event);
}

void Stage::on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

void Stage::on_pushButton_4_clicked() //Dimmer Class
{
    const QString bName = "Dimmer";
    static int page;
    unsigned char pages[10];
    if (ListType != bName) {
        getListDial(bName);
        page = 0;
    }
    int i;
    for(i = 0; i < page; i++) pages[i] = '.';
    pages[i] = 'o';
    for(i=page+1; i<((ListFuncs.size()+3)/4); i++)pages[i] = '.';
    pages[i] = 0;
    ui->pushButton_4->setText(bName+"\n" + QString::fromUtf8((char *)pages));
    setDialButtons(page++);
    if (page >= ((ListFuncs.size()+3)/4)) page = 0;
    ListType = bName;
}


void Stage::getListDial (QString Reference){
    QVector <Channel> SelFixChan;
    bool Flag = false;
    ListFuncs.clear();

    for ( int j = 0; j < TotFixtures; j++ )
    {
        if (Fixtures[j]->selected) {
            SelFixChan = Fixture::GetChannel(Fixtures[j]->Man, Fixtures[j]->Model, Fixtures[j]->Mode);
            for (Channel Ch:SelFixChan){
                if(Ch.Type == Reference){
                    for(Channel Fcn:ListFuncs){
                        if(Ch.name == Fcn.name){
                            Flag = true;
                        }
                    }
                    if(Flag == false) ListFuncs.insert(0,Ch);
                    Flag = false;
                }
            }
        }
    }
}

void Stage::setDialButtons (int page){
    int Val = 0;
    if(ListFuncs.size() > (page*4)+0){
        ui->pushButton_I1->show();
        ui->pushButton_I1->setText(ListFuncs.at((page*4)+0).name +"\n"+QString::number(Val));
    } else {
        ui->pushButton_I1->hide();
    }
    if(ListFuncs.size() > (page*4)+1){
        ui->pushButton_I2->show();
        ui->pushButton_I2->setText(ListFuncs.at((page*4)+1).name +"\n"+QString::number(Val));
    } else {
        ui->pushButton_I2->hide();
    }
    if(ListFuncs.size() > (page*4)+2){
        ui->pushButton_I3->show();
        ui->pushButton_I3->setText(ListFuncs.at((page*4)+2).name +"\n"+QString::number(Val));
    } else {
        ui->pushButton_I3->hide();
    }
    if(ListFuncs.size() > (page*4)+3){
        ui->pushButton_I4->show();
        ui->pushButton_I4->setText(ListFuncs.at((page*4)+3).name +"\n"+QString::number(Val));
    } else {
        ui->pushButton_I4->hide();
    }
}

void Stage::on_pushButton_6_clicked()
{
    const QString bName = "Position";
    static int page;
    unsigned char pages[10];
    if (ListType != bName) {
        getListDial(bName);
        page = 0;
    }
    int i;
    for(i = 0; i < page; i++) pages[i] = '.';
    pages[i] = 'o';
    for(i=page+1; i<((ListFuncs.size()+3)/4); i++)pages[i] = '.';
    pages[i] = 0;
    ui->pushButton_6->setText(bName+"\n" + QString::fromUtf8((char *)pages));
    setDialButtons(page++);
    if (page >= ((ListFuncs.size()+3)/4)) page = 0;
    ListType = bName;
}

void Stage::on_pushButton_8_clicked()
{
    const QString bName = "Color";
    static int page;
    unsigned char pages[10];
    if (ListType != bName) {
        getListDial(bName);
        page = 0;
    }
    int i;
    for(i = 0; i < page; i++) pages[i] = '.';
    pages[i] = 'o';
    for(i=page+1; i<((ListFuncs.size()+3)/4); i++)pages[i] = '.';
    pages[i] = 0;
    ui->pushButton_8->setText(bName+"\n" + QString::fromUtf8((char *)pages));
    setDialButtons(page++);
    if (page >= ((ListFuncs.size()+3)/4)) page = 0;
    ListType = bName;
}

void Stage::on_pushButton_7_clicked()
{
    const QString bName = "Gobo";
    static int page;
    unsigned char pages[10];
    if (ListType != bName) {
        getListDial(bName);
        page = 0;
    }
    int i;
    for(i = 0; i < page; i++) pages[i] = '.';
    pages[i] = 'o';
    for(i=page+1; i<((ListFuncs.size()+3)/4); i++)pages[i] = '.';
    pages[i] = 0;
    ui->pushButton_7->setText(bName+"\n" + QString::fromUtf8((char *)pages));
    setDialButtons(page++);
    if (page >= ((ListFuncs.size()+3)/4)) page = 0;
    ListType = bName;
}

void Stage::on_pushButton_5_clicked()
{
    const QString bName = "Lens";
    static int page;
    unsigned char pages[10];
    if (ListType != bName) {
        getListDial(bName);
        page = 0;
    }
    int i;
    for(i = 0; i < page; i++) pages[i] = '.';
    pages[i] = 'o';
    for(i=page+1; i<((ListFuncs.size()+3)/4); i++)pages[i] = '.';
    pages[i] = 0;
    ui->pushButton_5->setText(bName+"\n" + QString::fromUtf8((char *)pages));
    setDialButtons(page++);
    if (page >= ((ListFuncs.size()+3)/4)) page = 0;
    ListType = bName;
}

void Stage::on_pushButton_clicked()
{
    const QString bName = "Control";
    static int page;
    unsigned char pages[10];
    if (ListType != bName) {
        getListDial(bName);
        page = 0;
    }
    int i;
    for(i = 0; i < page; i++) pages[i] = '.';
    pages[i] = 'o';
    for(i=page+1; i<((ListFuncs.size()+3)/4); i++)pages[i] = '.';
    pages[i] = 0;
    ui->pushButton->setText(bName+"\n" + QString::fromUtf8((char *)pages));
    setDialButtons(page++);
    if (page >= ((ListFuncs.size()+3)/4)) page = 0;
    ListType = bName;
}
