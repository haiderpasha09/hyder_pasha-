#include "Programmer.h"
#include "ui_Programmer.h"
#include <QMessageBox>

programmer::programmer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::programmer)
{
    ui->setupUi(this);

    head = nullptr;
    songID = 0;
    totalSongs = 0;
    cueID = 0;
    stepID = 0;
    isCueSelected = true;
    ui->btnAddCue->setDisabled(true);
    //qRegisterMetaType<PopUpReturn>("PopUpReturn");

    loadSonList();
    //qDebug() << "size and location of this widet  " <<  this->size() << " -- " << this->geometry();

    //QElapsedTimer *qTim = new QElapsedTimer();
    //    ui->centralWidget->setMaximumSize(QSize(220,220));

    ui->songs_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->songs_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller::grabGesture(ui->songs_scrollArea->viewport(),QScroller::LeftMouseButtonGesture);
//
//    ui->seq_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->seq_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    QScroller::grabGesture(ui->seq_scrollArea->viewport(),QScroller::LeftMouseButtonGesture);

    ui->cue_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->cue_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller::grabGesture(ui->cue_scrollArea->viewport(),QScroller::LeftMouseButtonGesture);

    ui->step_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->step_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller::grabGesture(ui->step_scrollArea->viewport(),QScroller::LeftMouseButtonGesture);

    //    screen_3 * screen3;
    //    connect(ui->widget , SIGNAL(deleteSong_SIGNAL()) , this , SLOT(deleteSong_SLOT()));


    //    qTim->start();

    //    qDebug() << "_ _ " << qTim->elapsed();

    //ui->stackedWidget->setGeometry(0,0,240,10);
    //ui->stackedWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    //loadSongs();
    songList* tp = head; // pointer for triversing
    totalSongs = 0;
    while (tp != nullptr){
        addSongBtns(tp->songID, tp->songName , tp->SeqOrTrig, tp->TimeCode );
        tp = tp->nextNode;
        totalSongs++;
    }
    if (totalSongs == 0){
        ui->btnAddCue->hide();
        ui->btnCueTitle->hide();
    } else {
        ui->songs_scrollArea->setMinimumHeight(totalSongs*30+4);
        int maxh = 260-80;
        if(totalSongs*30+4>maxh)ui->songs_scrollArea->setMinimumHeight(maxh);
    }
    //loadCue();
    ui->btnCueTitle->setText("Select Song");
}
void programmer::saveSonList(void ){
    QFile saveFile(QStringLiteral("save.json"));


    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return ;
    }
    songList * tp = head;
    QJsonObject ShowObject;
    QJsonArray SongArray;
    while(tp != nullptr){
        //write(SongObject);
        QJsonObject SongObject;
        //mCue.write(CueObject);
        SongObject["Name"] = tp->songName;
        SongObject["TimeOrTrigger"] = tp->SeqOrTrig;
        SongObject["SongID"] = tp->songID;
        SongObject["TimeCode"] = tp->TimeCode;
        //SongObject["name"] = mName;
        QJsonArray CueArray;
        for (const Cue &mCue : tp->cueVec) {
            QJsonObject CueObject;
            //npc.write(npcObject);
            CueObject["Name"] = mCue.cueName;
            CueObject["ID"] = mCue.cueID;
            CueObject["TimeCode"] = mCue.timeCode;
            QJsonArray StepArray;
            for (const Step &mStep : mCue.cueSteps) {
                QJsonObject StepObject;
                //npc.write(npcObject);
                StepObject["Name"] = mStep.Name;
                StepObject["Fade"] = mStep.Fade;
                StepObject["StepID"] = mStep.stepID;
                StepObject["Duration"] = mStep.Duration;
                StepObject["TimeCode"] = mStep.TimeCode;
                StepArray.append(StepObject);
            }
            CueObject["Steps"] = StepArray;
            CueArray.append(CueObject);
        }
        SongObject["Cues"] = CueArray;
        SongArray.append(SongObject);
        tp = tp->nextNode;
    }
    ShowObject["Song"] = SongArray;
    QJsonDocument saveDoc(ShowObject);
    saveFile.write(saveDoc.toJson());
}

void programmer::loadSonList(void ){
    QFile loadFile(QStringLiteral("save.json"));


    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return ;
    }

    QByteArray SongData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(SongData));

    int soID = 0;
    int CuID = 0;
    int StID = 0;

    //float TimeCode;

    songList * tp = head;
    //read(loadDoc.object());
    if (loadDoc.object().contains("Song") && loadDoc.object()["Song"].isArray()){
        //mPlayer.read(json["player"].toObject());
        //TimeCode = 0;
        QJsonArray jsSong = loadDoc.object()["Song"].toArray();
        for (int sIn = 0; sIn < jsSong.size(); ++sIn){
            QJsonObject songObject = jsSong[sIn].toObject();
            songList * newNode = new songList(0, "" , 0);
           //  case 1 - empty list
            if (head == nullptr ){
                head = newNode;
            } else tp->nextNode = newNode;
            tp = newNode;

            newNode->songName = songObject["Name"].toString();
            newNode->SeqOrTrig = songObject["TimeOrTrigger"].toInt();
            newNode->songID = soID++;
            newNode->TimeCode = songObject["TimeCode"].toDouble();
            //1TimeCode = newNode->TimeCode;
            songID = newNode->songID+1;
            if (songObject.contains("Cues") && songObject["Cues"].isArray()){
                QJsonArray jsCue = songObject["Cues"].toArray();
                for (int cIn = 0; cIn < jsCue.size(); ++cIn){
                    QJsonObject CueObject = jsCue[cIn].toObject();
                    Cue mCue;
                    mCue.cueName = CueObject["Name"].toString();
                    mCue.cueID = CuID++;
                    mCue.timeCode = CueObject["TimeCode"].toDouble();
                    newNode->addCue(mCue);
                    if (CueObject.contains("Steps") && CueObject["Steps"].isArray()){
                        QJsonArray jsSteps = CueObject["Steps"].toArray();
                        for (int stIn = 0; stIn < jsSteps.size(); ++stIn){
                            QJsonObject StepObject = jsSteps[stIn].toObject();
                            Step mstep;
                            mstep.Name = StepObject["Name"].toString();
                            mstep.Fade = StepObject["Fade"].toInt();
                            mstep.stepID = StID++;
                            mstep.Duration = StepObject["Duration"].toInt();
                            mstep.TimeCode = StepObject["TimeCode"].toDouble();
                            //TimeCode += mstep.Duration;
                            newNode->addStepInCue(mCue.cueID , mstep);
                        }
                    }
                }
            }
        }
    }
    songID = soID;
    stepID = StID;
    cueID = CuID;
}

QString programmer::ConvertTimeCode(int SOrT, float num)
{
    char buf[100];
    if((SOrT == 0) || (SOrT == 2)) sprintf(buf,"Trigger");
    if(SOrT == 1) sprintf(buf,"Time Code");
    if(SOrT == 3)
    sprintf(buf,"Time Code\n%02d:%02d:%02d:%02d", (int)num/3600,((int)num/60)%60, ((int)num)%60, (int)(num*100)%100 );
    return buf;
}

void programmer::insertNode(const int &id, const QString &s_name, const QString &s_time)
{
    songList * newNode = new songList(id, s_name , s_time);

    ui->btnCueTitle->setText(s_name);
    currentSelected = id;

    //  case 1 - empty list
    if (head == nullptr ){
        head = newNode;
    }
    else {
        songList * curr = head;
        songList * trail = nullptr; // pointing to the prvious node of current node

        // traverse list to find insert location
        while (curr != nullptr) {
            if ( curr->songID >= newNode->songID ) // we are one ahead of the desired location
            {
                break; // location found then break
            }
            else{
                trail = curr;
                curr = curr->nextNode;
            }

        }
        // case 2 - instert at head
        if (curr == head){
            newNode->nextNode = head;
            head = newNode;
        }
        else{
            // case 3 - insert at any location
            newNode->nextNode = curr;
            trail->nextNode = newNode;
        }

    }
    totalSongs++;
    addSongBtns(newNode->songID, newNode->songName , newNode->SeqOrTrig, newNode->TimeCode );

    currentSelectedNode = newNode;
    // adding default one cue
//    addCue(cueID , QString::number(currentSelectedNode->songID) +" Cue name " + QString::number(cueID) , 0);
//    cueID++;

//    loadCue();

    //    displaySongs();
}
//void screen_1::refreshButtons(){
//    songList* tp = head; // pointer for triversing
//    //emptySongs(ui->song_verticalLayout_songs , ui->song_verticalLayout_timecode);
//    while (tp != nullptr){
//
//        //        addSongBtns(newNode->songID, newNode->songName , newNode->songTimeCode );
//        addSongBtns(tp->songID, tp->songName , tp->SeqOrTrig, tp->TimeCode );
//        tp = tp->nextNode;
//    }
//
//}
void programmer::loadSongs(){
    songList* tp = head; // pointer for triversing
    totalSongs = 0;
    emptySongs(ui->song_verticalLayout_songs , ui->song_verticalLayout_timecode);
    while (tp != nullptr){

        //        addSongBtns(newNode->songID, newNode->songName , newNode->songTimeCode );
        addSongBtns(tp->songID, tp->songName , tp->SeqOrTrig, tp->TimeCode );
        tp = tp->nextNode;
        totalSongs++;
        ui->btnAddCue->setEnabled(true);
    }

}
void programmer::emptySongs(QLayout *layout, QLayout *layout2){
    if ( layout->layout() != NULL )
    {
        QLayoutItem* item;
        QLayoutItem * item2;
        while ( ( item = layout->takeAt( 0 ) ) != NULL && ( item2 = layout2->takeAt( 0 ) ) != NULL  )
        {
            delete item->widget();
            delete item;
            delete item2->widget();
            delete item2;
        }
        //        delete m_view->layout();
    }
}
void programmer::deleteNode(const int & id)
{
    // case 1 - empty linked list
    if(head == nullptr){
        qDebug() << "Nothing to delete -  List is empty ";
    }
    else{
        songList * curr = head;
        songList * trail = nullptr; // 1 node behind he curre

        // triverse //  find node to delete
        while ( curr != nullptr){
            if ( curr->songID == id) // found the node
            {
                break;
            }
            else {
                trail = curr;
                curr = curr->nextNode;
            }

        }
        // case 2 - not found the node
        if (curr == nullptr){
            qDebug() << " ID- > " << id << "doesnot exist";
        }
        else // if found then 2 cases
        {
            // case 3 delete from the head
            if( head == curr ){
                // change head to next node of first node
                head = head->nextNode;
            }
            // case 4 delete beyond head
            else {
                trail->nextNode = curr->nextNode;
            }
        }
        delete curr;
        //        currentSelectedNode = trail->nextNode;
        totalSongs--;
    }
}
void programmer::displaySongs(){
    songList* tp = head; // pointer for triversing

    while (tp != nullptr){

        qDebug() << tp->songID;
        qDebug() << tp->songName;
        qDebug() << tp->songTimeCode;
        //        addSongBtns(tp->songID, tp->songName , tp->songTimeCode );
        tp = tp->nextNode;
    }
    qDebug() << " ------------------";
}
void programmer::addSongBtns(int id , QString name , int SorT, float time)
{

    songBtns = new mButtons(this);  // Create a dynamic button object
    timeCodeBtns = new mButtons(this);  // Create a dynamic button object

    connect(songBtns, SIGNAL(released()), this, SLOT(slotGetNumber()));
    connect(songBtns, SIGNAL(btnAdded_SIGNAL()), this, SLOT(scrollDown_SLOT()));
    connect(timeCodeBtns, SIGNAL(released()), this, SLOT(slotGetNumber()));
    //connect(timeCodeBtns, SIGNAL(btnAdded_SIGNAL()), this, SLOT(scrollDown_SLOT()));
    connect(timeCodeBtns, SIGNAL(editButton_SIGNAL()), this, SLOT(editSongStep_SLOT()));


    ////////////setting style sheet
    if (gAccess.selectedButton == 1 && gAccess.selectedSong == id)
        songBtns->setStyleSheet(blueBtnClrSel);
    else
        songBtns->setStyleSheet(blueBtnClr);

    songBtns->setButtonType("song");
    songBtns->setID(id);


    timeCodeBtns->setButtonType("songTime");
    if (gAccess.selectedButton == 2 && gAccess.selectedSong == id)
        timeCodeBtns->setStyleSheet(blueBtnClrSel);
    else
        timeCodeBtns->setStyleSheet(blueBtnClr);

    timeCodeBtns->setID(id);
    songBtns->setText(name);
    timeCodeBtns->setText(ConvertTimeCode(SorT, time));
    /* Adding a button to the bed with a vertical layout
       * */
    ui->song_verticalLayout_songs->addWidget(songBtns);
    ui->song_verticalLayout_timecode->addWidget(timeCodeBtns);
    /* Connect the signal to the slot pressing buttons produce numbers
       * */



    //ui->songs_scrollArea->scroll();
    //??ui->btnCueTitle->setText(name);

    //ui->songs_scrollArea->ensureWidgetVisible(songBtns,0,0); // for auto scroll down

    ui->song_verticalLayout_songs->addStretch(1);
    ui->song_verticalLayout_timecode->addStretch(1);
    //ui->song_verticalLayout_songs->spacerItem()->setGeometry( QRect {0,0,0,5});
}


programmer::~programmer()
{
    delete ui;
    //delete addSongPopUp;
}

void programmer::loadCue()
{
    emptyCue(ui->cue_verticalLayout_name , ui->cue_verticalLayout_timecode);
    if ( currentSelectedNode != NULL)
    {
        QVector<Cue> cueVec = currentSelectedNode->getCues();

        for (int i = 0 ; i < cueVec.size() ; i++ ){
            Cue mCue = cueVec.at(i);
            addCueButtons(mCue);
        }
       // ui->stackedWidget_2->setMinimumHeight(cueVec.size()*30+4);
        //    ui->cue_scrollArea->setMinimumHeight(cueID*30+4);
    }
    //    qDebug() << "####################################### " ;
    ui->stackedWidget_2->setCurrentIndex(1);
}



void programmer::slotGetNumber()
{

    //m
    /* To determine the object that caused the signal
     * */
    mButtons *button = qobject_cast<mButtons *>(QObject::sender());
    /* Then set the number of buttons in lineEdit,
     * which is contained in the dynamic button
     * */
    //    qDebug() << "Button ID" << button->getID();
    //    qDebug() << button->getSongName();

    /* That is the key number is set to lineEdit field only
     * when we press one of the dynamic keys,
     * and this number corresponds to the button you pressed
     * */

    // setting the button tittle to song name
    currentSelected = button->getID();
    qDebug() << "currentSelected->" << currentSelected;
    int ID = button->getID();

    btnType = button->getButtonType();

    if ( btnType == "song" ){

        //button->setStyleSheet(blueBtnClrSel);
        qDebug() << "Song Pressed";
        // finding the selected node
        setButtonType(1);
        gAccess.selectedSong = button->getID();
        loadSongs();
        songList* tp = head; // pointer for triversing

        while (tp != nullptr){
            if (  ID == tp->songID){
                currentSelectedNode = tp;
            }
            tp = tp->nextNode;
        }
        //currentSelectedNode->setStyleSheet(blueBtnClrSel)
        isCueSelected = true;
        RefreshCues();
        loadCue();
        ui->btnCueTitle->setText(currentSelectedNode->getSongName());
        int CurCue = currentSelectedNode->getCues().size();
        int maxh = ui->widget_4->geometry().height()-80;
        ui->cue_scrollArea->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
        ui->stackedWidget_2->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
        ui->btnCueTitle->setText(currentSelectedNode->songName);
        ui->btnAddCue->setText("Add Cue");

    }
    else if ( btnType == "songTime" ){
        gAccess.selectedSong = button->getID();
        setButtonType(2);

        songList* tp = head; // pointer for triversing

        while (tp != nullptr){
            if (  ID == tp->songID){
                currentSelectedNode = tp;
            }
            tp = tp->nextNode;
        }
        tp = currentSelectedNode;
        if(tp->SeqOrTrig < 2)
            tp->SeqOrTrig = (tp->SeqOrTrig == 0)?1:0;
        else
            tp->SeqOrTrig = (tp->SeqOrTrig == 2)?3:2;
            loadSongs();
//        button->setText(tp->getTimeCode());
        isCueSelected = true;
        RefreshCues();
        loadCue();

        ui->btnCueTitle->setText(currentSelectedNode->getSongName());
        int CurCue = currentSelectedNode->getCues().size();
        int maxh = ui->widget_4->geometry().height()-80;
        ui->cue_scrollArea->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
        ui->stackedWidget_2->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
        if ( !isCueSelected ){
            //            qDebug() << " isCueSelected " ;
            ui->btnAddCue->setText("Add Cue");
            ui->stackedWidget_2->setCurrentIndex(1);
            isCueSelected = true;

            emptySteps(ui->step_verticalLayout_name , ui->step_verticalLayout_fade , ui->step_verticalLayout_duration ,ui->step_verticalLayout_timecode );

            loadSteps();
        }
        ui->btnCueTitle->setText(currentSelectedNode->songName);
    }
    else if ( btnType == "cue"){

        setButtonType(3);
        gAccess.selectedCue =  button->getCueID();
        loadSongs();
        loadCue();
        //        qDebug() << "cue Pressed";
        //        qDebug() << button->getID();
        qDebug() << button->getCueID();

        //btnType = "cue";
    }
    else if ( btnType == "cueTime"){

        setButtonType(4);
        gAccess.selectedCue =  button->getCueID();
        loadSongs();
        loadCue();
        //        qDebug() << "cue Pressed";
        //        qDebug() << button->getID();
        qDebug() << button->getCueID();
        //btnType = "cueTime";
    }
    else if ( btnType == "step"){
        setButtonType(5);
        btnType = "step";
        gAccess.selectedStep = button->getStepID();
        qDebug() << "step Pressed";
        loadSteps();

    }
    else if (btnType == "stepFade" ){
        setButtonType(6);
        gAccess.selectedStep = button->getStepID();
        loadSteps();
    }
    else if (btnType == "stepDuration" ){
        setButtonType(7);
        gAccess.selectedStep = button->getStepID();
        loadSteps();
    }
    else if (btnType == "stepTIme" ){
        setButtonType(8);
        gAccess.selectedStep = button->getStepID();
        loadSteps();
    }
    else if ( btnType == "seq"){

    }

}

void programmer::on_btnAddSongs_clicked()
{
    //madd songs
        qDebug() << " Add songs ";

        showPopup((char *)"Add Song Name", (char *)"Type Song Name Here", SLOT(addSong_SLOT(QVariant)));
        //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(addSong_SLOT(QVariant)));
}
void programmer::ShowGotFocus(){
    addSongPopUp->raise();
}
void programmer::addSong_SLOT(QVariant vname){
    PopUpReturn name = vname.value<PopUpReturn>();
    ui->btnAddCue->show();
    gAccess.selectedSong = songID;
    gAccess.selectedButton = 1;
    insertNode(songID , name.s1 , "Trigger");
    //pDiaShadow->deleteLater();
    //QVector<Cue> cueVec = currentSelectedNode->getCues();
    //ui->cue_scrollArea->setMinimumHeight(cueVec.size()*30+4);
    //ui->step_scrollArea->setMinimumHeight(5);
    songID++;
    loadSongs();
    saveSonList();                                                  //***********************************************
    ui->songs_scrollArea->setMinimumHeight(totalSongs*30+4);
    int maxh = ui->widget_4->geometry().height()-80;
    if(totalSongs*30+4>maxh)ui->songs_scrollArea->setMinimumHeight(maxh);
    songList* tp = head; // pointer for triversing

    while (tp != nullptr){
        if (  songID == tp->songID){
            currentSelectedNode = tp;
        }
        tp = tp->nextNode;
    }
    //currentSelectedNode->setStyleSheet(blueBtnClrSel)
    isCueSelected = true;
    loadCue();
    ui->btnCueTitle->setText(currentSelectedNode->getSongName());
    int CurCue = currentSelectedNode->getCues().size();
    maxh = ui->widget_4->geometry().height()-80;
    ui->cue_scrollArea->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
    ui->stackedWidget_2->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
    ui->btnCueTitle->setText(currentSelectedNode->songName);
    ui->btnAddCue->setText("Add Cue");
}
void programmer::on_btnCountOff_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void programmer::on_btnAddSteps_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}




void programmer::scrollDown_SLOT(){
    /* To determine the object that caused the signal
     * */
    // QScrollBar *bar = ui->songs_scrollArea->horizontalScrollBar();


    //    ui->songs_scrollArea->setVerticalScrollBar();


    //    qDebug() << "scroll down";
    //mButtons *button = qobject_cast<mButtons *>(QObject::sender());

    ui->songs_scrollArea->ensureVisible(ui->songs_scrollArea->maximumWidth(),ui->songs_scrollArea->maximumHeight() +100, 0 , 0);
    // ui->songs_scrollArea->ensureVisible()
    // ui->songs_scrollArea->ensureWidgetVisible( button,0,0); // for auto scroll down

    /* Then set the number of buttons in lineEdit,
     * which is contained in the dynamic button
     * */
    //    qDebug() << " --- " << button->getID();
    //    qDebug() << " --- " <<  button->getSongName();

    /* That is the key number is set to lineEdit field only
     * when we press one of the dynamic keys,
     * and this number corresponds to the button you pressed
     * */
}



void programmer::on_btnAddCue_clicked()
{


    //QPoint position = this->mapToGlobal( this->pos() );
    // pop up signal and slot
    //    connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QString)) , this, SLOT(addCue(QString)));

    if ( currentSelectedNode != nullptr && totalSongs){
        //         qDebug() << "Cue Structure Data ----------- " ;
        //

        if ( isCueSelected ){
            showPopup((char *)"Add Cue Name", (char *)"Type Cue Name Here", SLOT(addCue_SLOT(QVariant)));
            //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(addCue_SLOT(QVariant)));

        }
        else{
            int CurSteps = currentSelectedNode->getStepsFromCue(gAccess.selectedCue).length()+1;
            addSteps( stepID , "Step " + QString::number(CurSteps) , 0 , 0 , 0  );
            ui->stackedWidget_2->setCurrentIndex(0);
            int maxh = ui->widget_4->geometry().height()-80;
            ui->step_scrollArea->setMinimumHeight((CurSteps*30+4)>maxh?maxh:(CurSteps*30+4));
            //ui->cue_scrollArea->setMinimumHeight(CurSteps*30+4);
            ui->stackedWidget_2->setMinimumHeight((CurSteps*30+4)>maxh?maxh:(CurSteps*30+4));
            stepID++;

            //    qDebug() << " Add cue ";
            //addSongPopUp = new PopUp();
            //addSongPopUp->setPopupText("Type Step Name");
            //addSongPopUp->mSetPlaceHolder("Type Step Name Here");
            //addSongPopUp->pDiaShadow->setGeometry(position.x()-10,position.y()-10, this->geometry().width(),this->geometry().height());
            //addSongPopUp->show();
            //popUpExist = true;
            //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QString)) , this, SLOT(addStep_SLOT(QString)));
        }
    }
    else {

            ui->btnAddCue->setDisabled(true);
            qDebug() << "no node selected or size is zero";
        }
    }

void programmer::addStep_SLOT(QVariant vName){
    PopUpReturn name = vName.value<PopUpReturn>();
    addSteps( stepID , name.s1 , 0 , 0 , 0  );
    ui->stackedWidget_2->setCurrentIndex(0);
    stepID++;
}
void programmer::addCue_SLOT(QVariant vName){
    PopUpReturn name = vName.value<PopUpReturn>();
    addCue(cueID , name.s1 , 0);
    gAccess.selectedCue = cueID;
    cueID++;
    //QVector<Cue> cueVec = currentSelectedNode->getCues();
    //ui->stackedWidget_2->setMinimumHeight(ui->cue_scrollArea->minimumHeight()+30);
    int CurCue = currentSelectedNode->getCues().size();
    int maxh = ui->widget_4->geometry().height()-80;
    ui->cue_scrollArea->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
    ui->stackedWidget_2->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
    //ui->cue_scrollArea->setMinimumHeight(ui->cue_scrollArea->minimumHeight()+30);
    ui->stackedWidget_2->setCurrentIndex(1);
    //ui->step_scrollArea->setMinimumHeight(5);
}

void programmer::addCue(int id ,QString name , float time)
{


    /////////////////
    Cue mCue;
    mCue.cueName = name;
    mCue.cueID = id;
    mCue.timeCode = time;

    currentSelectedNode->addCue(mCue);
    addCueButtons(mCue);
    saveSonList();
}


void programmer::addCueButtons(Cue &mCue)
{
    cueBtns = new mButtons(this);  // Create a dynamic button object
    cueTimeCodeBtns = new mButtons(this);  // Create a dynamic button object
    // setting size
    //    cueBtns->setMinimumSize(QSize(140,30));
    //    cueTimeCodeBtns->setMinimumHeight(30);
    /* Set the text with number of button
       * */



    ////////////setting style sheet
    ///
    if (gAccess.selectedButton == 3 && gAccess.selectedCue == mCue.cueID)
        cueBtns->setStyleSheet(blueBtnClrSel);
    else
        cueBtns->setStyleSheet(blueBtnClr);
    cueBtns->setButtonType("cue");
    cueTimeCodeBtns->setButtonType("cueTime");
    if (gAccess.selectedButton == 4 && gAccess.selectedCue == mCue.cueID)
        cueTimeCodeBtns->setStyleSheet(blueBtnClrSel);
    else
        cueTimeCodeBtns->setStyleSheet(blueBtnClr);

    /////////////////

    cueBtns->setText(mCue.cueName);
    cueTimeCodeBtns->setText(ConvertTimeCode(currentSelectedNode->SeqOrTrig, mCue.timeCode));
    /* Adding a button to the bed with a vertical layout
     *
       * */

    cueBtns->setCueID(mCue.cueID);
    cueTimeCodeBtns->setCueID(mCue.cueID);


    ui->cue_verticalLayout_name->addWidget(cueBtns);
    ui->cue_verticalLayout_timecode->addWidget(cueTimeCodeBtns);
    /* Connect the signal to the slot pressing buttons produce numbers
       * */
    connect(cueBtns, SIGNAL(released()), this, SLOT(slotGetNumber()));
    connect(cueTimeCodeBtns, SIGNAL(released()), this, SLOT(slotGetNumber()));

    // currentSelecteButton->addCueBTNS(cueBtns);
    connect( cueBtns , SIGNAL(editButton_SIGNAL()) , this , SLOT(switch_cue2Step()));


    ui->cue_verticalLayout_name->addStretch(1);
    ui->cue_verticalLayout_timecode->addStretch(1);

}
void programmer::emptyCue( QLayout* layout, QLayout* layout2 ){


    if ( layout->layout() != NULL )
    {
        QLayoutItem* item;
        QLayoutItem * item2;
        while ( ( item = layout->takeAt( 0 ) ) != NULL && ( item2 = layout2->takeAt( 0 ) ) != NULL  )
        {
            delete item->widget();
            delete item;
            delete item2->widget();
            delete item2;
        }
        //        delete m_view->layout();
    }
}
void programmer::on_btnSongs_clicked()
{
//    ui->stackedWidget->setCurrentIndex(0);
//    ui->stackedWidget_2->setCurrentIndex(1);
    //loadSongs();
    //qDebug() << ui->horizontalLayout_2->geometry();
}

void programmer::on_btnSeq_clicked()
{
//    ui->stackedWidget->setCurrentIndex(1);
//    ui->stackedWidget_2->setCurrentIndex(0);
//    isCueSelected = true;
    //emptySongs(ui->song_verticalLayout_songs , ui->song_verticalLayout_timecode);
}
void programmer::switch_cue2Step(){
    //    qDebug() << " switch ";
    slotGetNumber();
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->btnAddCue->setText("Add Steps");
    QVector<Step> SVec = currentSelectedNode->getStepsFromCue(gAccess.selectedCue);
    if ( SVec.empty())
    {
        emptySteps(ui->step_verticalLayout_name , ui->step_verticalLayout_fade , ui->step_verticalLayout_duration ,ui->step_verticalLayout_timecode );

        //        Step mStep;
        //        mStep.stepID = 0;
        //        mStep.Name = "Step Name";
        //        mStep.Fade = "Fade Time\nNs";
        //        mStep.Duration = "Duration\nNs";
        //        mStep.TimeCode = "Timecode\n00:00:00:00";

        //        //        currentSelectedNode->addStep(mStep);
        addSteps( stepID , "Step 1" , 0,0,0  );
        stepID++;
    }
    isCueSelected = false;
    //    loadCue();
    loadSteps();
    //mButtons * CButton = (mButtons *)sender();
    //CButton->getCueID();
    Cue mCue =  currentSelectedNode->getCueItem(gAccess.selectedCue);
    ui->btnCueTitle->setText(currentSelectedNode->songName + "(" + mCue.cueName+")");
    //ui->cue_scrollArea->setMinimumHeight(5);
    int CurSteps = currentSelectedNode->getStepsFromCue(gAccess.selectedCue).length();
    int maxh = ui->widget_4->geometry().height()-80;
    ui->step_scrollArea->setMinimumHeight((CurSteps*30+4)>maxh?maxh:(CurSteps*30+4));
    ui->stackedWidget_2->setMinimumHeight((CurSteps*30+4)>maxh?maxh:(CurSteps*30+4));

    //    ui->stackedWidget_2->setMinimumHeight((CurSteps*30+4)>maxh?maxh:(CurSteps*30+4));
    //ui->step_scrollArea->setMinimumHeight(currentSelectedNode->getStepsFromCue(selectedCue).length()*30+4);
}
void programmer::addSteps(int id ,QString name , float fade , float duration , float time ){
    /////////////////
    Step mStep;
    mStep.stepID = id;
    mStep.Name = name;
    mStep.Fade = fade;
    mStep.Duration = duration;
    mStep.cueID = gAccess.selectedCue;
    int CurSteps = currentSelectedNode->getStepsFromCue(gAccess.selectedCue).length();
    QVector<Step> Ss = currentSelectedNode->getStepsFromCue(gAccess.selectedCue);
    if (CurSteps == 0){
        mStep.TimeCode = time;
    } else {
        float TimeCode = Ss.at(CurSteps-1).Duration+Ss.at(CurSteps-1).TimeCode;
        mStep.TimeCode = TimeCode;
    }
    currentSelectedNode->addStepInCue(gAccess.selectedCue , mStep);
    addStepButtons(mStep);
    CurSteps++;
    //int CurSteps = currentSelectedNode->getStepsFromCue(gAccess.selectedCue).length()+1;
    int maxh = ui->widget_4->geometry().height()-80;
    ui->step_scrollArea->setMinimumHeight((CurSteps*30+4)>maxh?maxh:(CurSteps*30+4));
    ui->stackedWidget_2->setMinimumHeight((CurSteps*30+4)>maxh?maxh:(CurSteps*30+4));
    //ui->step_scrollArea->setMinimumHeight(currentSelectedNode->getStepsFromCue(selectedCue).length()*30+4);
    saveSonList();
}

void programmer::RefreshCues(){

    Step * stp;
    int j = 0;
    float CueTime;
    Cue * CCue;

    CueTime = currentSelectedNode->TimeCode;
    while (currentSelectedNode->cueVec.size() > j){
        CCue = (Cue *) & currentSelectedNode->cueVec.at(j);
        CCue->timeCode = CueTime;
        QVector<Step> stepVec = CCue->cueSteps;// currentSelectedNode->getStepsFromCue(gAccess.selectedCue);
        //stp = stepVec.at(0);

        for (int i = 0; i < CCue->cueSteps.size(); i++){
            stp  = (Step *) & CCue->cueSteps.at(i);
            if (i == 0)
                stp->TimeCode = CCue->timeCode;
            else
                stp->TimeCode = CCue->cueSteps.at(i-1).TimeCode + CCue->cueSteps.at(i-1).Duration;
            CueTime = CCue->cueSteps.at(i).TimeCode + CCue->cueSteps.at(i).Duration;
        }
        //CCue = (Cue *) & currentSelectedNode->cueVec.at(++j);
        //if (CCue != 0) CCue->timeCode = ;
    j++;
    }
    //Cue * CCue = currentSelectedNode->getCue(gAccess.selectedCue);
      //emptySteps(ui->step_verticalLayout_name , ui->step_verticalLayout_fade , ui->step_verticalLayout_duration ,ui->step_verticalLayout_timecode );
//    for (int i = 0; i < ui->cue_verticalLayout_name->count(); i++){
//        CCue = currentSelectedNode->getCue(i);
//        Cue_Name = (mButtons *)ui->cue_verticalLayout_name->layout()->itemAt(i)->widget();
//        Cue_TimeCode = (mButtons *)ui->cue_verticalLayout_timecode->layout()->itemAt(i)->widget();

//        Cue_Name->setText(CCue->cueName);
//        Cue_TimeCode->setText(ConvertTimeCode(3, CCue->timeCode));

//    }

}


void programmer::RefreshSteps(){

    mButtons * stepName;
    mButtons * stepFade;
    mButtons * stepDuration;
    mButtons * stepTimeCode;
    Step stp;

    Cue * CCue = currentSelectedNode->getCue(gAccess.selectedCue);
    QVector<Step> stepVec = CCue->cueSteps;// currentSelectedNode->getStepsFromCue(gAccess.selectedCue);
    stp = stepVec.at(0);
    stp.TimeCode = CCue->timeCode;
    for (int i = 1; i < CCue->cueSteps.size(); i++){
        stp  = CCue->cueSteps.at(i);
        stp.TimeCode = CCue->cueSteps.at(i-1).TimeCode + CCue->cueSteps.at(i-1).Duration;
    }
      //emptySteps(ui->step_verticalLayout_name , ui->step_verticalLayout_fade , ui->step_verticalLayout_duration ,ui->step_verticalLayout_timecode );
    for (int i = 0; i < ui->step_verticalLayout_name->count(); i++){
        stp = stepVec.at(i);
        stepName = (mButtons *)ui->step_verticalLayout_name->layout()->itemAt(i)->widget();
        stepFade = (mButtons *)ui->step_verticalLayout_fade->layout()->itemAt(i)->widget();
        stepDuration = (mButtons *)ui->step_verticalLayout_duration->layout()->itemAt(i)->widget();
        stepTimeCode = (mButtons *)ui->step_verticalLayout_timecode->layout()->itemAt(i)->widget();

        stepName->setText(stp.Name);
        stepFade->setText("Fade Time\n"+QString::number(stp.Fade));
        stepDuration->setText("Duration\n"+QString::number(stp.Duration));
        stepTimeCode->setText(ConvertTimeCode(3, stp.TimeCode));

    }

}
void programmer::loadSteps(){
    emptySteps(ui->step_verticalLayout_name , ui->step_verticalLayout_fade , ui->step_verticalLayout_duration ,ui->step_verticalLayout_timecode );
    if ( currentSelectedNode != NULL)
    {
        QVector<Step> stepVec = currentSelectedNode->getStepsFromCue(gAccess.selectedCue);

        //    qDebug() << " in load /*steps*/ .. length of data"<<  stepVec.length();

        for (int i = 0 ; i < stepVec.length() ; i++ ){
            Step mStep = stepVec.at(i);
            //        qDebug() << mStep.stepID;
            //        qDebug() << mStep.Name;
            //        qDebug() << mStep.Fade;
            //        qDebug() << " \n";

            addStepButtons(mStep);
        }
    }
}
void programmer::addStepButtons(Step &stp){
    //   qDebug() << " Step NAME ------ " << stp.Name;
    stepName = new mButtons(this);  // Create a dynamic button object
    stepFade = new mButtons(this);
    stepDuration = new mButtons(this);  // Create a dynamic button object
    stepTimeCode = new mButtons(this);  // Create a dynamic button object
    // setting size
    //        seqBtn->setMinimumSize(QSize(140,30));
    //        seqTimeCodeBtns->setMinimumHeight(30);
    /* Set the text with number of button
            * */

    ////////////setting style sheet
    if (gAccess.selectedButton == 5 && gAccess.selectedStep == stp.stepID)
        stepName->setStyleSheet(blueBtnClrSel);
    else
        stepName->setStyleSheet(blueBtnClr);
    if (gAccess.selectedButton == 6 && gAccess.selectedStep == stp.stepID)
        stepFade->setStyleSheet(blueBtnClrSel);
    else
        stepFade->setStyleSheet(blueBtnClr);
    if (gAccess.selectedButton == 7 && gAccess.selectedStep == stp.stepID)
        stepDuration->setStyleSheet(blueBtnClrSel);
    else
        stepDuration->setStyleSheet(blueBtnClr);
    if (gAccess.selectedButton == 8 && gAccess.selectedStep == stp.stepID)
        stepTimeCode->setStyleSheet(blueBtnClrSel);
    else
        stepTimeCode->setStyleSheet(blueBtnClr);

    /////////////////
    //        songBtns->setText("button " + QString::number(songBtns->getID()));
    //        timeCodeBtns->setText("button " + QString::number(songBtns->getID()));
    stepName->setText(stp.Name);
    stepFade->setText("Fade Time\n"+QString("000"+QString::number(stp.Fade)).right(3)+" s");
    stepDuration->setText("Duration\n"+QString("000"+QString::number(stp.Duration)).right(3)+" s");
    stepTimeCode->setText(ConvertTimeCode(3, stp.TimeCode));

    stepName->setStepID(stp.stepID);
    stepFade->setStepID(stp.stepID);
    stepDuration->setStepID(stp.stepID);
    stepTimeCode->setStepID(stp.stepID);

    stepName->setButtonType("step");
    stepFade->setButtonType("stepFade");
    stepDuration->setButtonType("stepDuration");
    stepTimeCode->setButtonType("stepTIme");


    /* Adding a button to the bed with a vertical layout
            * */
    ui->step_verticalLayout_name->addWidget(stepName);
    ui->step_verticalLayout_fade->addWidget(stepFade);
    ui->step_verticalLayout_duration->addWidget(stepDuration);
    ui->step_verticalLayout_timecode->addWidget(stepTimeCode);
    /* Connect the signal to the slot pressing buttons produce numbers
            * */
    connect(stepName, SIGNAL(released()), this, SLOT(slotGetNumber()));
    connect(stepFade, SIGNAL(released()), this, SLOT(slotGetNumber()));
    connect(stepDuration, SIGNAL(released()), this, SLOT(slotGetNumber()));
    connect(stepTimeCode, SIGNAL(released()), this, SLOT(slotGetNumber()));
    connect(stepFade, SIGNAL(editButton_SIGNAL()), this, SLOT(editSongStep_SLOT()));
    connect(stepDuration, SIGNAL(editButton_SIGNAL()), this, SLOT(editSongStep_SLOT()));
    connect(stepTimeCode, SIGNAL(editButton_SIGNAL()), this, SLOT(editSongStep_SLOT()));
}
void programmer::emptySteps( QLayout* layout, QLayout* layout2 ,  QLayout* layout3 , QLayout* layout4 ){


    if ( layout->layout() != NULL )
    {
        QLayoutItem* item;
        QLayoutItem * item2;
        QLayoutItem* item3;
        QLayoutItem * item4;
        while ( ( item = layout->takeAt( 0 ) ) != NULL && ( item2 = layout2->takeAt( 0 ) ) != NULL && ( item3 = layout3->takeAt( 0 ) ) != NULL && ( item4 = layout4->takeAt( 0 ) ) != NULL  )
        {
            delete item->widget();
            delete item;
            delete item2->widget();
            delete item2;
            delete item3->widget();
            delete item3;
            delete item4->widget();
            delete item4;
        }
        //        delete m_view->layout();
    }
}
void programmer::deleteSong_SLOT(){

    if (gAccess.selectedButton == 1 || gAccess.selectedButton == 2)
    {
        qDebug() << "Delete song";

        deleteNode(currentSelected);
        loadSongs();
        currentSelectedNode = NULL;
        loadCue();
        loadSteps();
        ui->songs_scrollArea->setMinimumHeight(totalSongs*30+4);
        int maxh = ui->widget_4->geometry().height()-80;
        if(totalSongs*30+4>maxh)ui->songs_scrollArea->setMinimumHeight(maxh);
        ui->btnCueTitle->setText("Select Song");

        ui->cue_scrollArea->setMinimumHeight(4);
        ui->stackedWidget_2->setMinimumHeight(4);

    }
    else if (gAccess.selectedButton == 3 || gAccess.selectedButton == 4){
        qDebug() << "Delete cue";
        qDebug() << "cue ID" << gAccess.selectedCue;
        currentSelectedNode->deleteCue(gAccess.selectedCue);
        loadCue();
        loadSteps();
        int CurCue = currentSelectedNode->getCues().size();
        int maxh = ui->widget_4->geometry().height()-80;
        ui->cue_scrollArea->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
      //  ui->cue_scrollArea->setMinimumHeight(4);
        ui->stackedWidget_2->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
    }
    else if (gAccess.selectedButton == 5 || gAccess.selectedButton == 6 || gAccess.selectedButton == 7 || gAccess.selectedButton == 8){
        qDebug() << "Delete step";

        currentSelectedNode->deleteStepFromCue(gAccess.selectedCue , gAccess.selectedStep);
        loadSteps();
        int CurSteps = currentSelectedNode->getStepsFromCue(gAccess.selectedCue).length();
        int maxh = ui->widget_4->geometry().height()-80;
        ui->step_scrollArea->setMinimumHeight((CurSteps*30+4)>maxh?maxh:(CurSteps*30+4));

    }
    saveSonList();
}
void programmer::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event)
    if ( popUpExist)
    {
        addSongPopUp->setSize(ui->widget->size().height() , ui->widget->size().width());
        QPoint qpAppNewLoc(  (QCursor::pos().x() - iXdeffarace) , (QCursor::pos().y() - iYdeffarance)  );
        qDebug() << qpAppNewLoc.x();
        qDebug() << qpAppNewLoc.y();
        addSongPopUp->rePosition(qpAppNewLoc.x() ,qpAppNewLoc.y());
        //        this->setProperty("pos", qpAppNewLoc);
    }
    gAccess.AppSize = event->size();
    ui->widget_3->setMinimumHeight(event->size().height()/6);
    ui->widget->setMinimumHeight(event->size().height()*5/6);

    qDebug() << "Programmer Screen Size" << event->size();
    QWidget::resizeEvent(event);
}
void programmer::mouseReleaseEvent ( QMouseEvent * event )
{
    Q_UNUSED(event)
    //    b_mousePressed = false;
}

void programmer::mouseMoveEvent ( QMouseEvent * event )
{
    Q_UNUSED(event)

    //    if(b_mousePressed)
    //    {
    //        QPoint qpAppNewLoc(  (QCursor::pos().x() - iXdeffarace) , (QCursor::pos().y() - iYdeffarance)  );
    //        qDebug() << qpAppNewLoc.x();
    //        qDebug() << qpAppNewLoc.y();
    //        addSongPopUp->rePosition(qpAppNewLoc.x() ,qpAppNewLoc.y());
    //        this->setProperty("pos", qpAppNewLoc);
    //    }
}
void programmer::mousePressEvent ( QMouseEvent * event)
{
    Q_UNUSED(event)
    //    b_mousePressed = true;
    //    QPoint qpMousePressedPoint = QCursor::pos();
    //    QPoint qpApploc = this->pos();
    //    iXdeffarace = qpMousePressedPoint.x() - qpApploc.x();
    //    iYdeffarance = qpMousePressedPoint.y() - qpApploc.y();
}

QString programmer::getButtonType(void)
{
    switch (gAccess.selectedButton)
    {
    case 1:
        return "song";
    case 2:
        return "songTime";
    case 3:
        return "cue";
    case 4:
        return "cueTime";
    case 5:
        return "step";
    case 6:
        return "stepFade";
    case 7:
        return "stepDuration";
    case 8:
        return "stepTIme";
    default:
        return "Nil";
    }
}

void programmer::editSongStep_SLOT(){
    // edit
    int bID;
    mButtons *button = qobject_cast<mButtons *>(QObject::sender());
    //mButtons *button = (mButtons*) sender();
    if (button != nullptr){
        btnType = button->getButtonType();
        bID = button->getID();
    } else {
        btnType = getButtonType();
        bID = currentSelectedNode->songID;
    }
    //cID = button->getCueID();
    //sID = button->getStepID();
    if (currentSelectedNode != NULL && totalSongs > 0 )
    {
        //song
        if (btnType == "song" ){

            //selectedCue = button->s();
            editSong(bID,btnType );
        }
        else if (btnType == "songTime" ){
            //selectedCue = button->getStepID();
            editSong(bID,btnType);
        }
        // cue
        else if (btnType == "cue" ){
             if (button != nullptr) gAccess.selectedCue = button->getCueID();
            editCue();
        }
        else if (btnType == "cueTime" ){
             if (button != nullptr) gAccess.selectedCue = button->getCueID();
            editCue();
        }
        // step
        else if (btnType == "step" ){
             if (button != nullptr) gAccess.selectedStep = button->getStepID();
            editStep();
        }
        else if (btnType == "stepFade" ){
             if (button != nullptr) gAccess.selectedStep = button->getStepID();
            editStep();
        }
        else if (btnType == "stepDuration" ){
             if (button != nullptr) gAccess.selectedStep = button->getStepID();
            editStep();
        }
        else if (btnType == "stepTIme" ){
             if (button != nullptr) gAccess.selectedStep = button->getStepID();
            editStep();
        }
        saveSonList();
    }
    else {
        qDebug() << "no ndoe selected";
    }
}
void programmer::showPopup(char * pText, char * pHolder, const char * slot)
{
    UserInput * uiP = new UserInput;
    QRect sz = this->geometry();
    QPoint position;
    position = this->mapToGlobal( this->pos() );
    position.setX(position.x() - 9);
    position.setY(position.y() - 9);
    //uiP->setGeometry(sz);
    //uiP->move(mapToGlobal(QPoint(sz.y(),sz.x())));
    uiP->move(position);
    uiP->setMinimumWidth(sz.width());
    uiP->setMinimumHeight(sz.height());
    uiP->Query(QString(pText), QString(pHolder));
    uiP->show();
    connect(uiP, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, slot);
    //valueEntered_SIGNAL
    /*
    addSongPopUp = new PopUp();
    //position = this->mapToGlobal( this->pos() );
    addSongPopUp->rePosition(fCorner.x(), fCorner.y());
    */
    //addSongPopUp->StartPoint.setX(ui->geometry.x());
     //   StartPoint.setY(parent->y());
    /*
    addSongPopUp->setPopupText(1, pText);
    addSongPopUp->mSetPlaceHolder(1, pHolder);
    addSongPopUp->show();
    popUpExist = true;
    addSongPopUp->pDiaShadow->setWindowOpacity(0.2);
    addSongPopUp->pDiaShadow->setGeometry(fCorner.x()-10,fCorner.y()-10, sCorner.x(),sCorner.y());
    */
   // connect(addSongPopUp->pDiaShadow, SIGNAL(GotFocus()) , this, SLOT(ShowGotFocus()));
   // connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QString)) , this, );

}

void programmer::showInfo(char * pText, const char * slot)
{
    UserInput * uiP = new UserInput;
    QRect sz = this->geometry();
    QPoint position;
    position = this->mapToGlobal( this->pos() );
    position.setX(position.x() - 9);
    position.setY(position.y() - 9);
    uiP->move(position);
    uiP->setMinimumWidth(sz.width());
    uiP->setMinimumHeight(sz.height());
    uiP->Info(1, QString(pText));
    uiP->show();
    connect(uiP, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, slot);

}

void programmer::editStep(){
    if (btnType == "step" ){
        qDebug() << "editing step";
        //addSongPopUp = new PopUp();
        //addSongPopUp->setPopupText("Type Name");
        //addSongPopUp->mSetPlaceHolder("Type Name Here");
        //addSongPopUp->show();
        //popUpExist = true;
        //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QString)) , this, SLOT(editStepName_SLOT(QString)));
    }
    else if (btnType == "stepFade" ){
        qDebug() << "editing stepFade";
        showPopup((char *)"Add Fade", (char *)"Type Fade Here", SLOT(editStepFade_SLOT(QVariant)));
        //addSongPopUp = new PopUp();
        //addSongPopUp->setPopupText("Type Name");
       // addSongPopUp->mSetPlaceHolder("Type Name Here");
        //addSongPopUp->show();
       // popUpExist = true;
        //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(editStepFade_SLOT(QVariant)));
    }
    else if (btnType == "stepDuration" ){
        qDebug() << "editing stepDuration";
        //addSongPopUp = new PopUp();
        //addSongPopUp->setPopupText("Type Name");
        //addSongPopUp->mSetPlaceHolder("Type Name Here");
        //addSongPopUp->show();
        //popUpExist = true;
        showPopup((char *)"Add Duration", (char *)" Type Duration Here", SLOT(editStepDuration_SLOT(QVariant)));
        //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(editStepDuration_SLOT(QVariant)));
    }
    else if (btnType == "stepTIme" ){
        qDebug() << "editing stepTIme";
        //addSongPopUp = new PopUp();
        //addSongPopUp->setPopupText("Type Name");
        //addSongPopUp->mSetPlaceHolder("Type Name Here");
        //addSongPopUp->show();
        //popUpExist = true;
        showPopup((char *)"Add Time code", (char *)"Type Time Here", SLOT(editStepTime_SLOT(QVariant)));
        //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(editStepTime_SLOT(QVariant)));
    }
}
void programmer::editStepName_SLOT(QVariant vName){
    PopUpReturn val = vName.value<PopUpReturn>();
    Step * mStep = currentSelectedNode->getStepItemFromCue(gAccess.selectedCue , gAccess.selectedStep);
    mStep->Name = val.s1;
    //currentSelectedNode->editStep(gAccess.selectedCue , gAccess.selectedStep , mStep);
    loadSteps();
}

void programmer::editStepFade_SLOT(QVariant vName){
    PopUpReturn val = vName.value<PopUpReturn>();
    //Step * nStep = currentSelectedNode->getNextStepItemFromCue(selectedCue , selectedStep);
    Step * mStep = currentSelectedNode->getStepItemFromCue(gAccess.selectedCue , gAccess.selectedStep);

    bool condition = (val.s1.toFloat() > mStep->Duration);
    mStep->Fade = val.s1.toFloat();
    if (condition)
    {
        showInfo((char *)"Duration Time will be effected", SLOT(Time_update_SLOT(QVariant)));
    } else {
        RefreshCues();
        loadSteps();
    }

    /*
        QMessageBox msgBox;
        msgBox.setText("Duration Time will be effected");
        msgBox.setStyleSheet(" min-height: 3em; min-width: 10em; font-weight: bold; color: white; background-color: qlineargradient(spread:pad, x1:0, y1:0.568, x2:1, y2:0.574, stop:0 rgba(79, 79, 79, 255), stop:1 rgba(39, 38, 38, 255));border-style: solid;border-color: rgba(0, 0, 0, 255);border-width: 0px;border-radius: 5px; font-size:10");
        //msgBox.setTextFormat("font-size:10pt; color:#aaaaaa;");
        msgBox.setWindowFlags(Qt::FramelessWindowHint |        // Disable window decoration
                                  Qt::Tool | Qt::Dialog |                       // Discard display in a separate window
                                      Qt::WindowStaysOnTopHint);       // Set on top of all windows
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        QSpacerItem* horizontalSpacer = new QSpacerItem(300, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = (QGridLayout*)msgBox.layout();
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
        int ret = msgBox.exec();
        if (ret == QMessageBox::Ok)
              mStep.Fade = mStep.Duration = val.s1.toFloat();
            Step * mStep2 = currentSelectedNode->getNextStepItemFromCue(gAccess.selectedCue , gAccess.selectedStep);
            if(mStep2 != 0){
                if (mStep2->TimeCode < val.s1.toFloat()){
                     mStep2->TimeCode = val.s1.toFloat();
                }
            }
    } else mStep.Fade = val.s1.toFloat();
    //if(nStep != 0) nStep->TimeCode = mStep.TimeCode + mStep.Duration;
    currentSelectedNode->editStep(gAccess.selectedCue , gAccess.selectedStep , mStep);

    //RefreshSteps();
    */

}

void programmer::Time_update_SLOT(QVariant vParm){
    Step * mStep = currentSelectedNode->getStepItemFromCue(gAccess.selectedCue , gAccess.selectedStep);
    PopUpReturn val = vParm.value<PopUpReturn>();
    if(val.s1 == "Duration Time will be effected"){
        if(val.s2 == "OK")
          mStep->Duration = mStep->Fade;
    }
    if(val.s1 == "Fade Time will be effected"){
        if(val.s2 == "OK")
          mStep->Fade = mStep->Duration;
    }

    RefreshCues();
    loadSteps();

}

void programmer::editStepDuration_SLOT(QVariant vName){
    PopUpReturn val = vName.value<PopUpReturn>();
    //Step * nStep = currentSelectedNode->getNextStepItemFromCue(selectedCue , selectedStep);
    Step * mStep = currentSelectedNode->getStepItemFromCue(gAccess.selectedCue , gAccess.selectedStep);

    bool condition = (val.s1.toFloat() < mStep->Fade);
    mStep->Duration = val.s1.toFloat();
    if (condition)
    {
        showInfo((char *)"Fade Time will be effected", SLOT(Time_update_SLOT(QVariant)));
    }else {
        RefreshCues();
        loadSteps();
    }
}
void programmer::editStepTime_SLOT(QVariant vName){
    PopUpReturn val = vName.value<PopUpReturn>();
//    Step mStep = currentSelectedNode->getStepItemFromCue(gAccess.selectedCue , gAccess.selectedStep);
    Cue * CCue = currentSelectedNode->getCue(gAccess.selectedCue);
    QVector<Step> stepVec = CCue->cueSteps;// currentSelectedNode->getStepsFromCue(gAccess.selectedCue);
    Step * stpold = (Step *) & stepVec.at(0);
    //stp.TimeCode = CCue->timeCode;
    for (int i = 1; i < CCue->cueSteps.size(); i++){
        Step * stp  = (Step *) & CCue->cueSteps.at(i);
        if(stp->stepID == gAccess.selectedStep){
            if (stpold->TimeCode < val.s1.toFloat()){
                //stp.TimeCode = val.toFloat();
                stpold->Duration = val.s1.toFloat()-stpold->TimeCode;
                if (stpold->Fade > stpold->Duration) stpold->Fade = stpold->Duration;
            } else {
                QMessageBox msgBox;
                msgBox.setText("Time code is lower than possible");
                msgBox.setStyleSheet(" min-height: 3em; min-width: 10em; font-weight: bold; color: white; background-color: qlineargradient(spread:pad, x1:0, y1:0.568, x2:1, y2:0.574, stop:0 rgba(79, 79, 79, 255), stop:1 rgba(39, 38, 38, 255));border-style: solid;border-color: rgba(0, 0, 0, 255);border-width: 0px;border-radius: 5px; font-size:10");
                msgBox.setWindowFlags(Qt::FramelessWindowHint |        // Disable window decoration
                                          Qt::Tool | Qt::Dialog |                       // Discard display in a separate window
                                              Qt::WindowStaysOnTopHint);       // Set on top of all windows
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();
            }
        }
        stpold= stp;
    }

 //   mStep.TimeCode = val.toFloat();
    //mStep.TimeCode = mStep.TimeCode + mStep.Duration;
//    currentSelectedNode->editStep(gAccess.selectedCue , gAccess.selectedStep , mStep);
//    RefreshSteps();
    RefreshCues();
    loadSteps();
}

void programmer::editCue(){
    if (btnType == "cue" ){
        qDebug() << "editing song name";
        //addSongPopUp = new PopUp();
        //addSongPopUp->setPopupText("Type Name");
        //addSongPopUp->mSetPlaceHolder("Type Name Here");
        //addSongPopUp->show();
        //popUpExist = true;
        showPopup((char *)"Edit Cue Name", (char *)"Type Name Here", SLOT(editCueName_SLOT(QVariant)));
        //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(editCueName_SLOT(QVariant)));
    }
    else if (btnType == "cueTime" ){
        qDebug() << "editing songTime";
        //addSongPopUp = new PopUp();
        //addSongPopUp->setPopupText("Type Name");
        //addSongPopUp->mSetPlaceHolder("Type Name Here");
        //addSongPopUp->show();
        //popUpExist = true;
        showPopup((char *)"Edit Time", (char *)"00:00:00:00", SLOT(editCueTime_SLOT(QVariant)));
        //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(editCueTime_SLOT(QVariant)));
    }
}
void programmer::editCueName_SLOT(QVariant vName){
    PopUpReturn val = vName.value<PopUpReturn>();
    Cue mCue =  currentSelectedNode->getCueItem(gAccess.selectedCue);
    mCue.cueName = val.s1;
    currentSelectedNode->editCue(gAccess.selectedCue , mCue);
    loadCue();
}
void programmer::editCueTime_SLOT(QVariant vName){
    PopUpReturn val = vName.value<PopUpReturn>();
    Cue mCue =  currentSelectedNode->getCueItem(gAccess.selectedCue);
    mCue.timeCode = val.s1.toFloat();
    currentSelectedNode->editCue(gAccess.selectedCue , mCue);
    loadCue();
}
void programmer::editSong(int ID, QString btnType){
    //mButtons *button = (mButtons*) sender();
    //btnType = button->getButtonType();
    songList* tp = head; // pointer for triversing
    while (tp != nullptr){
        if (ID == tp->songID){
                currentSelectedNode = tp;
        }
        tp = tp->nextNode;
    }
    ui->btnCueTitle->setText(currentSelectedNode->getSongName());
    if (btnType == "song" ){
        qDebug() << "editing song name";
        //addSongPopUp = new PopUp();
        //addSongPopUp->setPopupText("Type Name");
        //addSongPopUp->mSetPlaceHolder("Type Name Here");
        //addSongPopUp->show();
        //popUpExist = true;


        showPopup((char *)"Edit Name", (char *)"Type Name Here", SLOT(editSongName_SLOT(QVariant)));
        //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, );
    }
    else if (btnType == "songTime" ){
        if ((currentSelectedNode->SeqOrTrig == 1) || (currentSelectedNode->SeqOrTrig == 3)){
            qDebug() << "editing songTime";
            //addSongPopUp = new PopUp();
           // addSongPopUp->setPopupText("Type Time");
            //addSongPopUp->mSetPlaceHolder("00:00:00:00");
            //addSongPopUp->show();
            //popUpExist = true;
            showPopup((char *)"Edit Time code", (char *)"00:00:00:00", SLOT(editSongTime_SLOT(QVariant)));
            //connect(addSongPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(editSongTime_SLOT(QVariant)));
        }
    }
}
void programmer::editSongName_SLOT(QVariant vName){
    PopUpReturn val = vName.value<PopUpReturn>();
    currentSelectedNode->editSong(val.s1, currentSelectedNode->TimeCode);
    loadSongs();
}
void programmer::editSongTime_SLOT(QVariant vName){
    PopUpReturn val = vName.value<PopUpReturn>();
    currentSelectedNode->editSong(currentSelectedNode->getSongName(), val.s1.toFloat());
    currentSelectedNode->SeqOrTrig = 3;
    loadSongs();
}


void programmer::on_btnCueTitle_clicked()
{
    isCueSelected = true;
    loadCue();
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->btnCueTitle->setText(currentSelectedNode->songName);
    ui->btnAddCue->setText("Add Cue");
    int CurCue = currentSelectedNode->getCues().size();
    int maxh = ui->widget_4->geometry().height()-80;
    ui->cue_scrollArea->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
    ui->stackedWidget_2->setMinimumHeight((CurCue*30+4)>maxh?maxh:(CurCue*30+4));
}


