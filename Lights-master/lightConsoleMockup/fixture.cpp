#include "fixture.h"
#include "ui_fixture.h"

#define OTHER_ITEM_HEIGHT 55

QVector<Manufactur> ManuVec;
FixtureFuncs FixFuncs[6];

Fixture::Fixture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fixture)
{
    ui->setupUi(this);
    //qRegisterMetaType<PopUpReturn>("PopUpReturn");

    //saveFunctionList();
    LoadFunctionList();

    int ManId = 0;

    /*
    Manufactur  ma ;
    ManuVec.append(ma);
    Model mo;
    Manufactur * Man = (Manufactur *) &ManuVec.at(0);
    Man->Name = QString("JAH");
    mo.Name = QString("Hybrid");
    Man->ModelVec.append(mo);
    mo.Name = QString("Versa Advanced");
    Man->ModelVec.append(mo);
    mo.Name = QString("Versa Mini");
    Man->ModelVec.append(mo);
    mo.Name = QString("Versa Pro");
    Man->ModelVec.append(mo);
    Model * Ml = (Model *) &Man->ModelVec.at(0);
    Mode md;
    md.Name = "Mode 1";
    Ml->ModeVec.append(md);
    Mode * Mod = (Mode * ) & Ml->ModeVec.at(0);
    Channel Fn;
    Fn.name = "Green";
    Mod->ChannelVec.append(Fn);
    Channel * Fun = (Channel *) &Mod->ChannelVec.at(0);
    Function PV;
    PV.Name = "Green";
    PV.Min = 0; PV.Max = 3; PV.Start=0; PV.Stop = 5;
    Fun->FuncVec.append(PV);
    PV.Name = "Green";PV.Min = 4; PV.Max = 255; PV.Start=5; PV.Stop = 100;
    Fun->FuncVec.append(PV);
    //ManuVec.at(0).ModelVec.at(0).ModeVec.at(0).ChannelVec.at(0).FuncVec.at(0).Min = 0;
    //mButtons * ManBtns0;
    */
    loadFixtureList();
    InsertManModel("JAH", "Versa Mini", 2);
    InsertManModel("JAH", "Versa Pro", 2);
    saveFixtureList();
    for (Manufactur M:ManuVec){
        //ManBtns = new mButtons(this);  // Create a dynamic button object

        //connect(ManBtns, SIGNAL(released()), this, SLOT(Manufac_Click()));

        ////////////setting style sheet
        //ManBtns->setStyleSheet(blueBtnClr);
        //ManBtns->setText(M.Name);
        //ManBtns->setButtonType("manufacturer");
        //ManBtns->setID(ManId++);
        //ManBtns->setMinimumHeight(20);
        //ui->vertManList->addWidget(ManBtns);
        AddButtonToScrollArea(ManId++, M.Name, blueBtnClr, "manufacturer", 20, ui->vertManList, SLOT(Button_Click()));
        int maxh = ui->widget_10->geometry().height()-OTHER_ITEM_HEIGHT;
        ui->scrollArea_Brand->setMinimumHeight((ManId*20+4)>maxh?maxh:(ManId*20+4));
        //ui->scrollArea_Brand->setMinimumHeight(20);
    }
}

Fixture::~Fixture()
{
    delete ui;
}

QVector <Channel> Fixture::GetChannel(QString pMan, QString pModel, QString pMode){
    for(Manufactur Mf:ManuVec){
        if(Mf.Name == pMan){
        for (Model Md:Mf.ModelVec){
            if(Md.Name == pModel){
            for (Mode Mod:Md.ModeVec){
                if(Mod.Name == pMode){
                    return Mod.ChannelVec;
                }
            }
            }
        }
        }
    }
}

void Fixture::DeleteButton(void){
    //mButtons *button = qobject_cast<mButtons *>(QObject::sender());
    //button->ResID;
    //SelectedButton = button->getButtonType();
    if(SelectedButton == "fixture_model"){
        //SelectedModel = button->getID();
        Manufactur * Mod = (Manufactur * )&ManuVec.at(SelectedMan);
        Mod->ModelVec.remove(SelectedModel);
        HiliteButtoninScrollArea(SelectedModel, blueBtnClr, blueBtnClrSel, ui->vertModList);
        //HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClr, ui->vertManList);
        //ui->pbPatch_3->setStyleSheet("QPushButton{background-color: rgb(0, 170, 0);border-style: solid;border-color: rgb(0, 170, 0);border-width: 5px;border-radius: 5px;}");

    }
    if(SelectedButton == "manufacturer"){
        RemoveButtonfromScrollArea(ui->vertModList);
        ManuVec.remove(SelectedMan);
        //RemoveButtonfromScrollArea(ui->vertModList);

        //int ModId = 0;
        //mButtons *button = qobject_cast<mButtons *>(QObject::sender());

        //SelectedMan = button->getID();
        //for (Model M:ManuVec.at(SelectedMan).ModelVec){
        //    AddButtonToScrollArea(ModId++, M.Name, blueBtnClr, "fixture_model", 20, ui->vertModList, SLOT(Button_Click()));
        //    int maxh = ui->widget_11->geometry().height()-2;
        //    ui->scrollArea_Fixture->setMinimumHeight((ModId*20+4)>maxh?maxh:(ModId*20+4));
        //}
        //HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClrSel, ui->vertManList);
        //ui->pbPatch_3->setStyleSheet("QPushButton{background-color: rgb(170, 0, 0);border-style: solid;border-color: rgb(170, 0, 0);border-width: 5px;border-radius: 5px;}");
        //HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClr, ui->vertModList);

    }
    if(SelectedButton == "fixture_modes"){
        Model * Mod = (Model * )&ManuVec.at(SelectedMan).ModelVec.at(SelectedModel);
        Mod->ModeVec.remove(SelectedMode);
        if(Mod->ModeVec.size() == 0){
            ui->stackedWidget->setCurrentIndex(0);
        }
    }
    if(SelectedButton == "fixture_FuncNum" || SelectedButton == "fixture_Function"){

    }
}

void Fixture::Button_Click(void){
    mButtons *button = qobject_cast<mButtons *>(QObject::sender());
    //button->ResID;
    SelectedButton = button->getButtonType();
    if(button->getButtonType() == "fixture_model"){
        SelectedModel = button->getID();
        HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClrSel, ui->vertModList);
        HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClr, ui->vertManList);
        ui->pbPatch_3->setStyleSheet("QPushButton{background-color: rgb(0, 170, 0);border-style: solid;border-color: rgb(0, 170, 0);border-width: 5px;border-radius: 5px;}");

    }
    if(button->getButtonType() == "manufacturer"){
        RemoveButtonfromScrollArea(ui->vertModList);
        int ModId = 0;
        //mButtons *button = qobject_cast<mButtons *>(QObject::sender());

        SelectedMan = button->getID();
        for (Model M:ManuVec.at(SelectedMan).ModelVec){
            AddButtonToScrollArea(ModId++, M.Name, blueBtnClr, "fixture_model", 20, ui->vertModList, SLOT(Button_Click()));
            int maxh = ui->widget_11->geometry().height()-OTHER_ITEM_HEIGHT;
            ui->scrollArea_Fixture->setMinimumHeight((ModId*20+4)>maxh?maxh:(ModId*20+4));
        }
        HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClrSel, ui->vertManList);
        ui->pbPatch_3->setStyleSheet("QPushButton{background-color: rgb(170, 0, 0);border-style: solid;border-color: rgb(170, 0, 0);border-width: 5px;border-radius: 5px;}");
        HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClr, ui->vertModList);

    }
    if(button->getButtonType() == "fixture_modes"){
        SelectedMode = button->getID();
        int ChanId = 0;
        HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClrSel, ui->verProfileList);
        RemoveButtonfromScrollArea(ui->verFunNum);
        RemoveButtonfromScrollArea(ui->verFunList);
        RemoveButtonfromScrollArea(ui->vertFuncName);
        RemoveButtonfromScrollArea(ui->vertFuncMinVal);
        RemoveButtonfromScrollArea(ui->vertFuncMaxVal);
        RemoveButtonfromScrollArea(ui->vertFuncMinRng);
        RemoveButtonfromScrollArea(ui->vertFuncMaxRng);
        for (Channel F:ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode).ChannelVec){

            AddButtonToScrollArea(ChanId, QString::number(ChanId), blueBtnClr, "fixture_FuncNum", 20, ui->verFunNum, SLOT(Button_Click()));
            AddButtonToScrollArea(ChanId++, F.name, blueBtnClr, "fixture_Function", 20, ui->verFunList, SLOT(Button_Click()));
        }
        int maxh = ui->widget_21->geometry().height()-OTHER_ITEM_HEIGHT;
        ui->scrollArea_11->setMinimumHeight((ChanId*20+4)>maxh?maxh:(ChanId*20+4));
        ui->scrollArea_10->setMinimumHeight(0);
    }
    if(button->getButtonType() == "fixture_FuncNum" || button->getButtonType() == "fixture_Function"){
        SelectedChan = button->getID();
        int FunID = 0;
        HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClr, ui->verProfileList);
        HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClrSel, ui->verFunNum);
        HiliteButtoninScrollArea(button->getID(), blueBtnClr, blueBtnClrSel, ui->verFunList);
        RemoveButtonfromScrollArea(ui->vertFuncName);
        RemoveButtonfromScrollArea(ui->vertFuncMinVal);
        RemoveButtonfromScrollArea(ui->vertFuncMaxVal);
        RemoveButtonfromScrollArea(ui->vertFuncMinRng);
        RemoveButtonfromScrollArea(ui->vertFuncMaxRng);
        for (Function P:ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode).ChannelVec.at(SelectedChan).FuncVec){
            AddButtonToScrollArea(FunID, P.Name, blueBtnClr, "Param_name", 20, ui->vertFuncName, SLOT(Button_Click()));
            AddButtonToScrollArea(FunID, QString::number(P.Min), blueBtnClr, "Param_minval", 20, ui->vertFuncMinVal, SLOT(Button_Click()));
            AddButtonToScrollArea(FunID, QString::number(P.Max), blueBtnClr, "Param_maxval", 20, ui->vertFuncMaxVal, SLOT(Button_Click()));
            AddButtonToScrollArea(FunID, QString::number(P.Start), blueBtnClr, "Param_minrange", 20, ui->vertFuncMinRng, SLOT(Button_Click()));
            AddButtonToScrollArea(FunID++, QString::number(P.Stop), blueBtnClr, "Param_maxrange", 20, ui->vertFuncMaxRng, SLOT(Button_Click())); 
        }
        int maxh = ui->widget_19->geometry().height()-OTHER_ITEM_HEIGHT;
        ui->scrollArea_10->setMinimumHeight((FunID*20+4)>maxh?maxh:(FunID*20+4));
    }
}

void Fixture::AddButtonToScrollArea(int ID, QString Text, QString Style, QString Type, int height, QLayout * ui_scrArea, const char * slotFunc){
    mButtons * Btn;
    Btn = new mButtons(this);
    Btn->setStyleSheet(Style);
    Btn->setText(Text);
    Btn->setButtonType(Type);
    Btn->setID(ID);
    Btn->setMinimumHeight(height);
    ui_scrArea->addWidget(Btn);
    connect(Btn, SIGNAL(released()), this, slotFunc);
}

void Fixture::HiliteButtoninScrollArea(int ID, QString Norm, QString Highlite, QLayout * ui_scrArea){
    if ( ui_scrArea->layout() != NULL){
        QLayoutItem * item;
        mButtons * Button;
        int it = 0;
        while( (item = ui_scrArea->itemAt(it++)) != NULL ) {
            Button = (mButtons *)item->widget();
             Button->setStyleSheet(Norm);
             if(Button->getID() == ID) Button->setStyleSheet(Highlite);
        }
    }
}

void Fixture::RemoveButtonfromScrollArea(QLayout * ui_scrArea){
    if ( ui_scrArea->layout() != NULL){
        QLayoutItem* item;
        while ( ( item = ui_scrArea->takeAt( 0 ) ) != NULL )
        {
                delete item->widget();
                delete item;

        }
    }
}

void Fixture::showPopup(char * l1, char * T1, char * l2, char * T2, char * l3, char * T3,  QPoint fCorner, QPoint sCorner){

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
    uiP->Update(l1, T1, l2, T2, l3, T3);
    uiP->show();
    connect(uiP, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(ReceivePopUpManu(QVariant)));

    /*
    PopUp * FixturePopUp;
    FixturePopUp = new PopUp(1);

    FixturePopUp->rePosition(fCorner.x(), fCorner.y());
    FixturePopUp->setPopupText(1, l1);
    FixturePopUp->mSetPlaceHolder(1, T1);

    FixturePopUp->setPopupText(2, l2);
    FixturePopUp->mSetPlaceHolder(2, T2);

    FixturePopUp->setPopupText(3, l3);
    FixturePopUp->mSetPlaceHolder(3, T3);

    FixturePopUp->show();
    //popUpExist = true;
    FixturePopUp->pDiaShadow->setWindowOpacity(0.2);
    FixturePopUp->pDiaShadow->setGeometry(fCorner.x()-10,fCorner.y()-10, sCorner.x(),sCorner.y());
    connect(FixturePopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(ReceivePopUpManu(QVariant)));
    */
}

void Fixture::resizeEvent(QResizeEvent *event){


   //ui->widget_3->setMinimumHeight(event->size().height()/8);
   //ui->pbCreateNew->setMinimumHeight(event->size().height()/8);
   qDebug() << event->size();
   QWidget::resizeEvent(event);
}
//Manfacturer - Model - Mode - Channel(universe) - Function(parameter)

void Fixture::saveFixtureList(void ){


    QFile saveFixFile(QString("FixtureData.json"));


    if (!saveFixFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return ;
    }
    QJsonObject FixListObject;
    QJsonArray  FixManuArray;

    for(Manufactur Mf:ManuVec){
        QJsonObject FixManuObject;
        FixManuObject["Manufacturer"] = Mf.Name;
        //QString FileName = ManuVec.at(Manu).Name;

        //songList * tp = head;
        QJsonArray ModelArray2;
        QJsonArray ModelArray;
        for (Model Md:Mf.ModelVec){
        while(!ModelArray.isEmpty()) ModelArray.removeAt(0);
            QFile saveFile(QString("Fix_"+Md.Name+".json"));


            if (!saveFile.open(QIODevice::WriteOnly)) {
                qWarning("Couldn't open save file.");
                return ;
            }
            QJsonObject ModelObject2;
            QJsonObject FixModelObject;
            FixModelObject["Manufacturer"] = Mf.Name;
            ModelObject2["Manufacturer"] = Mf.Name;
            ModelObject2["FileName"] = QString("Fix_"+Md.Name+".json");
            ModelObject2["Name"] = Md.Name;
            //write(SongObject);
            QJsonObject ModelObject;
            ModelObject["Name"] = Md.Name;
            QJsonArray ModeArray;

            for (Mode Mod:Md.ModeVec){
                QJsonObject ModeObject;
                ModeObject["Name"] = Mod.Name;
                QJsonArray ChanArray;
                for(Channel Chan:Mod.ChannelVec){
                    QJsonObject ChanObject;
                    ChanObject["Name"] = Chan.name;
                    ChanObject["Type"] = Chan.Type;
                    QJsonArray FunArray;
                    for(Function Fun:Chan.FuncVec){
                        QJsonObject FunObject;
                        FunObject["Name"] = Fun.Name;
                        FunObject["MinVal"] = QString::number(Fun.Min);
                        FunObject["MaxVal"] = QString::number(Fun.Max);
                        FunObject["MinRange"] = QString::number(Fun.Start);
                        FunObject["MaxRange"] = QString::number(Fun.Stop);
                        FunArray.append(FunObject);
                    }
                    ChanObject["Function"] = FunArray;
                    ChanArray.append(ChanObject);
                }
                ModeObject["Channel"] = ChanArray;
                ModeArray.append(ModeObject);
            }
            ModelObject["Mode"] = ModeArray;
            ModelArray.append(ModelObject);
            FixModelObject["Model"] = ModelArray;
            QJsonDocument saveDoc(FixModelObject);
            saveFile.write(saveDoc.toJson());

            ModelArray2.append(ModelObject2);
        }
        FixManuObject["Model"] = ModelArray2;
        FixManuArray.append(FixManuObject);
    }
    FixListObject["Fixtures"] = FixManuArray;
    QJsonDocument saveFixDoc(FixListObject);
    saveFixFile.write(saveFixDoc.toJson());
}


void Fixture::loadFixtureList(void ){
    QFile loadFile(QStringLiteral("FixtureData.json"));


    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        return ;
    }

    QByteArray FixListData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(FixListData));

    if (loadDoc.object().contains("Fixtures") && loadDoc.object()["Fixtures"].isArray()){
        QJsonArray jsFixGrp = loadDoc.object()["Fixtures"].toArray();

        for (int sIn = 0; sIn < jsFixGrp.size(); sIn++){
            QJsonObject FixGrpObject = jsFixGrp[sIn].toObject();
            QString ManuName = FixGrpObject["Manufacturer"].toString();
            //UpdateFixtureData(fpManufacturer, ManuName);
            if (FixGrpObject.contains("Model") && FixGrpObject["Model"].isArray()){
                QJsonArray jaModel = FixGrpObject["Model"].toArray();
                for (int Model = 0; Model<jaModel.size(); Model++){
                    QString ModelName = jaModel[Model].toObject()["Name"].toString();
                    InsertManModel(ManuName, ModelName,1);
                    QString FileName = jaModel[Model].toObject()["FileName"].toString();

                    QFile loadModelFile(FileName);

                    if (!loadModelFile.open(QIODevice::ReadOnly)) {
                        qWarning("Couldn't open load file.");
                        return ;
                    }

                    QByteArray FixModelData = loadModelFile.readAll();
                    QJsonDocument loadModelDoc(QJsonDocument::fromJson(FixModelData));

                    if (loadModelDoc.object().contains("Model") && loadModelDoc.object()["Model"].isArray()){
                        QJsonArray jaFixMdl = loadModelDoc.object()["Model"].toArray();
                        //UpdateFixtureData(fpModel, )
                        for (int mdl = 0; mdl < jaFixMdl.size(); mdl++){
                            QJsonObject joFixMdl = jaFixMdl[mdl].toObject();
                            QString ModelName = joFixMdl["Name"].toString();
                            //UpdateFixtureData(fpModel)
                            if (joFixMdl.contains("Mode") && joFixMdl["Mode"].isArray()){
                                QJsonArray jaMode = joFixMdl["Mode"].toArray();

                                for (int Mode = 0; Mode<jaMode.size(); Mode++){
                                    QJsonObject joFixMode = jaMode[Mode].toObject();
                                    QString ModeName = joFixMode["Name"].toString();
                                    UpdateFixtureData(fpMode, ModeName);
                                    if (joFixMode.contains("Channel") && joFixMode["Channel"].isArray()){
                                        QJsonArray jaChan = joFixMode["Channel"].toArray();

                                        for (int Chan = 0; Chan<jaChan.size(); Chan++){
                                            QJsonObject joFunc = jaChan[Chan].toObject();
                                            QString ChanName = joFunc["Name"].toString();
                                            QString ChanType = joFunc["Type"].toString();
                                            UpdateFixtureData(fpChannel, ChanName, ChanType);
                                            if (joFunc.contains("Function") && joFunc["Function"].isArray()){
                                                QJsonArray jaFunc = joFunc["Function"].toArray();

                                                for (int Func = 0; Func<jaFunc.size(); Func++){
                                                    QJsonObject joChan = jaFunc[Func].toObject();
                                                    QString FuncName = joChan["Name"].toString();
                                                    QString FuncMinVal = joChan["MinVal"].toString();
                                                    QString FuncMaxVal = joChan["MaxVal"].toString();
                                                    QString FuncMinRng = joChan["MinRange"].toString();
                                                    QString FuncMaxRng = joChan["MaxRange"].toString();
                                                    UpdateFixtureData(fpFunction, FuncName, FuncMinVal,
                                                                      FuncMaxVal, FuncMinRng, FuncMaxRng);
                                                    //UpdateModel(ManuName, ModelName, ModeName, ChanName,
                                                    //            FuncName, FuncMinVal, FuncMaxVal, FuncMinRng, FuncMaxRng );
                                                }


                                            }
                                        }
                                    }
                                }
                            }}}

                }
            }

        }
    }
}

void Fixture::UpdateFixtureData(FixParam Parm, QString Val1, QString Val2, QString Val3, QString Val4, QString Val5){
    int ind = 0, man = 0, mod = 0, mode = 0, chan = 0, func = 0;
    if(Parm == fpManufacturer){
        for (Manufactur M:ManuVec){
            ind++;
            if(Val1 == M.Name){
                man = ind;
                SelectedMan = ind-1;
            }
        }
        if(man == 0){
            Manufactur  ma ;
            ma.Name = Val1;
            ManuVec.append(ma);
            man = ManuVec.size();
            SelectedMan = man-1;
        }
    }
   // man--;
   // ind = 0;
    if(Parm == fpModel){
        for (Model Md:ManuVec.at(SelectedMan).ModelVec){
            ind++;
            if(Val1 == Md.Name){
                mod = ind;
                SelectedModel = ind-1;
            }
        }
        if(mod == 0){
            Model  md ;
            md.Name = Val1;
            Manufactur * pman = (Manufactur *) &ManuVec.at(SelectedMan);
            pman->ModelVec.append(md);
            mod = pman->ModelVec.size();
            SelectedModel = mod - 1;
        }
    }
    mod--;
    if(Parm == fpMode){
        Model * pmodel = (Model *) &ManuVec.at(SelectedMan).ModelVec.at(SelectedModel);
        ind = 0;
        for (Mode Mod:pmodel->ModeVec){
            ind++;
            if(Val1 == Mod.Name){
                mode = ind;
                SelectedMode = ind-1;
            }
        }
        if(mode == 0){
            Mode  nmod ;
            nmod.Name = Val1;
            //Mode * pmode = (Mode *) &pmodel->ModeVec.at(mod);
            pmodel->ModeVec.append(nmod);
            mode = pmodel->ModeVec.size();
            SelectedMode = mode - 1;
        }
    }
    mode--;
    if(Parm == fpChannel){
        Mode * pmode = (Mode *) &ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode);
        ind = 0;
    //    for (Channel Chan:pmode->ChannelVec){
    //        ind++;
    //        if(ChanName == Chan.name){
    //            chan = ind;
    //            SelectedMode = ind;
    //        }
    //    }
    //    if(chan == 0){
            Channel  nchan ;
            nchan.name = Val1;
            nchan.Type = Val2;
            //Mode * pmode = (Mode *) &pmodel->ModeVec.at(mod);
            pmode->ChannelVec.append(nchan);
            chan = pmode->ChannelVec.size();
            SelectedChan = chan - 1;
    //    }
    }
    //chan--;
    if(Parm == fpFunction){
        Channel * pchan = (Channel *) &ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode).ChannelVec.at(SelectedChan);
     //   ind = 0;
     //   for (Function Func:pchan->FuncVec){
      //      ind++;
     //       if(FuncName == Func.Name){
     //           func = ind;
                //SelectedMode = ind;
     //       }
     //   }
     //   if(func == 0){
            Function  nfunc ;
            nfunc.Name = Val1;
            nfunc.Min = Val2.toInt();
            nfunc.Max = Val3.toInt();
            nfunc.Start = Val4.toInt();
            nfunc.Stop = Val5.toInt();
            //Mode * pmode = (Mode *) &pmodel->ModeVec.at(mod);
            pchan->FuncVec.append(nfunc);
            //chan = pmodel->ModeVec.size();
            //SelectedChan = mode - 1;
    //    }
    }
}

void Fixture::UpdateModel(QString ManuName, QString ModelName, QString ModeName, QString ChanName,
            QString FuncName, QString FuncMinVal, QString FuncMaxVal, QString FuncMinRng, QString FuncMaxRng ){
    int ind = 0, man = 0, mod = 0, mode = 0, chan = 0, func = 0;
    for (Manufactur M:ManuVec){
        ind++;
        if(ManuName == M.Name){
            man = ind;
            SelectedMan = ind-1;
        }
    }
    if(man == 0){
        Manufactur  ma ;
        ma.Name = ManuName;
        ManuVec.append(ma);
        man = ManuVec.size();
        SelectedMan = man-1;
    }
    man--;
    ind = 0;
    for (Model Md:ManuVec.at(man).ModelVec){
        ind++;
        if(ModelName == Md.Name){
            mod = ind;
            SelectedModel = ind;
        }
    }
    if(mod == 0){
        Model  md ;
        md.Name = ModelName;
        Manufactur * pman = (Manufactur *) &ManuVec.at(man);
        pman->ModelVec.append(md);
        mod = pman->ModelVec.size();
        SelectedModel = mod - 1;
    }
    mod--;
    Model * pmodel = (Model *) &ManuVec.at(man).ModelVec.at(mod);
    ind = 0;
    for (Mode Mod:pmodel->ModeVec){
        ind++;
        if(ModeName == Mod.Name){
            mode = ind;
            SelectedMode = ind;
        }
    }
    if(mode == 0){
        Mode  nmod ;
        nmod.Name = ModeName;
        //Mode * pmode = (Mode *) &pmodel->ModeVec.at(mod);
        pmodel->ModeVec.append(nmod);
        mode = pmodel->ModeVec.size();
        SelectedMode = mode - 1;
    }
    mode--;
    Mode * pmode = (Mode *) &ManuVec.at(man).ModelVec.at(mod).ModeVec.at(mode);
    ind = 0;
    for (Channel Chan:pmode->ChannelVec){
        ind++;
        if(ChanName == Chan.name){
            chan = ind;
            SelectedMode = ind;
        }
    }
    if(chan == 0){
        Channel  nchan ;
        nchan.name = ChanName;
        //Mode * pmode = (Mode *) &pmodel->ModeVec.at(mod);
        pmode->ChannelVec.append(nchan);
        chan = pmode->ChannelVec.size();
        SelectedChan = mode - 1;
    }
    chan--;
    Channel * pchan = (Channel *) &ManuVec.at(man).ModelVec.at(mod).ModeVec.at(mode).ChannelVec.at(chan);
    ind = 0;
    for (Function Func:pchan->FuncVec){
        ind++;
        if(FuncName == Func.Name){
            func = ind;
            //SelectedMode = ind;
        }
    }
    if(func == 0){
        Function  nfunc ;
        nfunc.Name = FuncName;
        nfunc.Min = FuncMinVal.toInt();
        nfunc.Max = FuncMaxVal.toInt();
        nfunc.Start = FuncMinRng.toInt();
        nfunc.Stop = FuncMaxRng.toInt();
        //Mode * pmode = (Mode *) &pmodel->ModeVec.at(mod);
        pchan->FuncVec.append(nfunc);
        //chan = pmodel->ModeVec.size();
        //SelectedChan = mode - 1;
    }
}
void Fixture::saveFunctionList(void ){
    //FixtureFuncs * mFF;//
    QFile saveFile(QStringLiteral("Fix_Funcs.json"));


    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return ;
    }
    //songList * tp = head;
    QJsonObject FixGrpObject;
    QJsonArray GroupArray;
    for (int tp =0; tp<6; tp++){
        //write(SongObject);
        QJsonObject GroupObject;
        GroupObject["GroupName"] = FuncGroup[tp];
        QJsonArray FuncArray;
        for (const QString FF : FixFuncs[tp].Name) {
            //QJsonObject CueObject;
            FuncArray.append(FF);
        }
        GroupObject["Functions"] = FuncArray;
        GroupArray.append(GroupObject);
    }
    FixGrpObject["FixtureGroup"] = GroupArray;
    QJsonDocument saveDoc(FixGrpObject);
    saveFile.write(saveDoc.toJson());
}

void Fixture::LoadFunctionList(void ){
    QFile loadFile(QStringLiteral("Fix_Funcs.json"));


    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open load file.");
        FixFuncs[0].GroupName = FuncGroup[0];
        FixFuncs[0].Name.append("Dimmer");
        FixFuncs[0].Name.append("Shutter");
        FixFuncs[0].Name.append("Strobe");
        FixFuncs[1].GroupName = FuncGroup[1];
        FixFuncs[1].Name.append("Pan");
        FixFuncs[1].Name.append("Tilt");
        FixFuncs[1].Name.append("Pan Fine");
        FixFuncs[1].Name.append("Tilt Fine");
        FixFuncs[2].GroupName = FuncGroup[2];
        FixFuncs[2].Name.append("Red");
        FixFuncs[2].Name.append("Green");
        FixFuncs[2].Name.append("Blue");
        FixFuncs[2].Name.append("White");
        FixFuncs[2].Name.append("Amber");
        FixFuncs[2].Name.append("Lime");
        FixFuncs[3].GroupName = FuncGroup[3];
        FixFuncs[3].Name.append("Gobo Wheel");
        FixFuncs[3].Name.append("Fixed Gobo");
        FixFuncs[3].Name.append("Gobo Shake");
        FixFuncs[3].Name.append("Rotating Gobo");
        FixFuncs[3].Name.append("Rotate Gobo");
        FixFuncs[3].Name.append("Macro Effect");
        FixFuncs[4].GroupName = FuncGroup[4];
        FixFuncs[4].Name.append("Focus");
        FixFuncs[4].Name.append("Zoom");
        FixFuncs[4].Name.append("Auto Zoom");
        FixFuncs[4].Name.append("Frost");
        FixFuncs[4].Name.append("Rotate");
        FixFuncs[5].GroupName = FuncGroup[5];
        FixFuncs[5].Name.append("Control");
        FixFuncs[5].Name.append("Lamp On");
        FixFuncs[5].Name.append("Lamp Off");
        FixFuncs[5].Name.append("Rest");
        return ;
    }

    QByteArray FixGrpData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(FixGrpData));

    if (loadDoc.object().contains("FixtureGroup") && loadDoc.object()["FixtureGroup"].isArray()){
        QJsonArray jsFixGrp = loadDoc.object()["FixtureGroup"].toArray();
        for (int sIn = 0; sIn < 6; sIn++){
            QJsonObject FixGrpObject = jsFixGrp[sIn].toObject();
            QString GrpName = FixGrpObject["GroupName"].toString();
            int Grp;
            for (Grp = 0; Grp<6; Grp++){
                if(FixFuncs[Grp].GroupName == GrpName){
                    break;
                }
            }
            if (Grp == 6) Grp = sIn;
            FixFuncs[Grp].GroupName = GrpName;
            if (FixGrpObject.contains("Functions") && FixGrpObject["Functions"].isArray()){
                QJsonArray jsFuncs = FixGrpObject["Functions"].toArray();
                for (int cIn = 0; cIn < jsFuncs.size(); ++cIn){
                    //QJsonObject CueObject = jsFuncs[cIn].toObject();
                    QString S = jsFuncs[cIn].toString();
                    if(!FixFuncs[Grp].Name.contains(S))
                        FixFuncs[Grp].Name.append(S);
                }
            }
        }
    }
}

//void Fixture::on_pbCreateNew_clicked()
//{
//    qDebug() << this->geometry();
    //qDebug() << ui->pbCreateNew->geometry();
//    qDebug() << height();
//}

void Fixture::on_pbCreateNew_3_clicked()
{
    showPopup((char *)"Brand", (char *)"JAH", (char *)"Device Name", (char *)"Intelligent Profile", (char *)"Number of Operating Modes", (char *)"1", this->mapToGlobal( this->pos()), QPoint(this->geometry().width(),this->geometry().height() ));

}

void Fixture::InsertManModel(QString sMan, QString sModel, uint iMode){
    uint man = 0, mod = 0, ind = 0;

    for (Manufactur M:ManuVec){
        ind++;
        if(sMan == M.Name){
            man = ind;
            SelectedMan = ind-1;
        }
    }
    if(man == 0){
        Manufactur  ma ;
        ma.Name = sMan;
        ManuVec.append(ma);
        man = ManuVec.size();
        SelectedMan = man-1;
    }
    man--;
    ind = 0;
    for (Model Md:ManuVec.at(man).ModelVec){
        ind++;
        if(sModel == Md.Name){
            mod = ind;
            SelectedModel = ind;
        }
    }
    if(mod == 0){
        Model  md ;
        md.Name = sModel;
        Manufactur * pman = (Manufactur *) &ManuVec.at(man);
        pman->ModelVec.append(md);
        mod = pman->ModelVec.size();
        SelectedModel = mod - 1;
    }
    mod--;
    Model * pmode = (Model *) &ManuVec.at(man).ModelVec.at(mod);
    Mode Modes;
    for(ind = pmode->ModeVec.size(); ind<iMode; ind++){
        Modes.Name = "Mode "  + QString::number(ind+1);
        pmode->ModeVec.append(Modes);
    }

}
void Fixture::ReceivePopUpManu(QVariant vParams){
    PopUpReturn uSel = vParams.value<PopUpReturn>();
    //mButtons *button = qobject_cast<mButtons *>(QObject::sender());
    //if(button->getButtonType() == )
    InsertManModel(uSel.s1, uSel.s2, uSel.s3.toUInt());
    SelectedMode = 0;
    ui->stackedWidget->setCurrentIndex(1);
    on_pbEditProfile_3_clicked();
}

void Fixture::on_pbEditProfile_3_clicked()
{
    SelectedMode = 0;
    ui->btnModes->setText(ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).Name);
    int ModId = 0;
    ui->stackedWidget->setCurrentIndex(1);
    ui->pushButton->setFont(QFont("Arial Narrow", -1, 4));
    ui->pushButton_2->setFont(QFont("Arial Narrow", -1, 4));
    RemoveButtonfromScrollArea(ui->verProfileList);
    RemoveButtonfromScrollArea(ui->verFunNum);
    RemoveButtonfromScrollArea(ui->verFunList);
    RemoveButtonfromScrollArea(ui->vertFuncName);
    RemoveButtonfromScrollArea(ui->vertFuncMinVal);
    RemoveButtonfromScrollArea(ui->vertFuncMaxVal);
    RemoveButtonfromScrollArea(ui->vertFuncMinRng);
    RemoveButtonfromScrollArea(ui->vertFuncMaxRng);
    if(ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.size()>0){

        for (Mode M:ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec){

            AddButtonToScrollArea(ModId++, M.Name, blueBtnClr, "fixture_modes", 20, ui->verProfileList, SLOT(Button_Click()));
            int maxh = ui->widget_11->geometry().height()-OTHER_ITEM_HEIGHT;
            ui->scrollArea_Fixture->setMinimumHeight((ModId*20+4)>maxh?maxh:(ModId*20+4));
            //ui->scrollArea_Fixture->setMinimumHeight(20);
        }
        int ChanID = 0;
        if (ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(0).ChannelVec.size()>0){
            for (Channel F:ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(0).ChannelVec){

                AddButtonToScrollArea(ChanID, QString::number(ChanID+1), blueBtnClr, "fixture_FuncNum", 20, ui->verFunNum, SLOT(Button_Click()));
                AddButtonToScrollArea(ChanID++, F.name, blueBtnClr, "fixture_Function", 20, ui->verFunList, SLOT(Button_Click()));

                int maxh = ui->widget_21->geometry().height()-OTHER_ITEM_HEIGHT;
                ui->scrollArea_11->setMinimumHeight((ChanID*20+4)>maxh?maxh:(ChanID*20+4));
                //ui->scrollArea_11->setMinimumHeight(20);
            }
            int FunID = 0;
            if(ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(0).ChannelVec.at(0).FuncVec.size()>0){
                for (Function P:ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(0).ChannelVec.at(0).FuncVec){

                    AddButtonToScrollArea(FunID, ManuVec.at(0).ModelVec.at(0).ModeVec.at(0).ChannelVec.at(0).name, blueBtnClr, "Param_name", 20, ui->vertFuncName, SLOT(Button_Click()));
                    AddButtonToScrollArea(FunID, QString::number(P.Min), blueBtnClr, "Param_minval", 20, ui->vertFuncMinVal, SLOT(Button_Click()));
                    AddButtonToScrollArea(FunID, QString::number(P.Max), blueBtnClr, "Param_maxval", 20, ui->vertFuncMaxVal, SLOT(Button_Click()));
                    AddButtonToScrollArea(FunID, QString::number(P.Start), blueBtnClr, "Param_minrange", 20, ui->vertFuncMinRng, SLOT(Button_Click()));
                    AddButtonToScrollArea(FunID++, QString::number(P.Stop), blueBtnClr, "Param_maxrange", 20, ui->vertFuncMaxRng, SLOT(Button_Click()));

                    int maxh = ui->widget_19->geometry().height()-OTHER_ITEM_HEIGHT;
                    ui->scrollArea_10->setMinimumHeight((FunID*20+4)>maxh?maxh:(FunID*20+4));
                    //ui->scrollArea_10->setMinimumHeight(20);
                }
            }
        }

    }else{
        Model * Ml = (Model *) &ManuVec.at(SelectedMan).ModelVec.at(SelectedModel);
        Mode md;
        md.Name = "Mode 1";
        Ml->ModeVec.append(md);
        AddButtonToScrollArea(ModId++, "Mode 1", blueBtnClr, "fixture_modes", 20, ui->verProfileList, SLOT(Button_Click()));
        int maxh = ui->widget_11->geometry().height()-OTHER_ITEM_HEIGHT;
        ui->scrollArea_Fixture->setMinimumHeight((ModId*20+4)>maxh?maxh:(ModId*20+4));

    }
    RefreshScreen();
}

void Fixture::on_btnAddChannel_clicked()
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
    uiP->FixtureFunctions();
    uiP->show();
    connect(uiP, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(addChannel_SLOT(QVariant)));

    /*
    PopUp * ChannelPopUp = new PopUp(5);
    QPoint pPos;
    pPos = this->mapToGlobal( this->pos());
    ChannelPopUp->rePosition(pPos.y(), pPos.x());
    ChannelPopUp->pDiaShadow->setWindowOpacity(0.2);
    ChannelPopUp->pDiaShadow->setGeometry(pPos.x(),pPos.y()-10, this->geometry().width(),this->geometry().height());
    ChannelPopUp->show();
    connect(ChannelPopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(addChannel_SLOT(QVariant)));
    */
}
void Fixture::addChannel_SLOT(QVariant vParams){
    QString Name = vParams.value<PopUpReturn>().s1;
    QString Type = FixFuncs[vParams.value<PopUpReturn>().s2.toInt()].GroupName;
    //PopUpReturn uParams = vParams.value<PopUpReturn>();
    //QString Name = uParams.s1;
    int ChanID = ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode).ChannelVec.size();
    Mode * Md = (Mode *) &ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode);
    Channel fn;
    fn.name = Name;
    fn.Type = Type;
    Md->ChannelVec.append(fn);
    SelectedChan = ChanID;
    AddButtonToScrollArea(ChanID, QString::number(ChanID+1), blueBtnClr, "fixture_FuncNum", 20, ui->verFunNum, SLOT(Button_Click()));
    AddButtonToScrollArea(ChanID++, fn.name, blueBtnClr, "fixture_Function", 20, ui->verFunList, SLOT(Button_Click()));
    int maxh = ui->widget_21->geometry().height()-OTHER_ITEM_HEIGHT;
    ui->scrollArea_11->setMinimumHeight((ChanID*20+4)>maxh?maxh:(ChanID*20+4));
    RemoveButtonfromScrollArea(ui->vertFuncName);
    RemoveButtonfromScrollArea(ui->vertFuncMinVal);
    RemoveButtonfromScrollArea(ui->vertFuncMaxVal);
    RemoveButtonfromScrollArea(ui->vertFuncMinRng);
    RemoveButtonfromScrollArea(ui->vertFuncMaxRng);
    ui->scrollArea_10->setMinimumHeight(0);
    RefreshScreen();
}

void Fixture::RefreshScreen(void ){
    HiliteButtoninScrollArea(SelectedMode, blueBtnClr, blueBtnClrSel, ui->verProfileList);

    HiliteButtoninScrollArea(SelectedChan, blueBtnClr, blueBtnClrSel, ui->verFunNum);
    HiliteButtoninScrollArea(SelectedChan, blueBtnClr, blueBtnClrSel, ui->verFunList);
}

void Fixture::on_btnAddFunction_clicked()
{
    if (ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode).ChannelVec.size() != 0){
        PopUp * FixturePopUp;
        FixturePopUp = new PopUp(3);
    //    FixturePopUp->rePosition(fCorner.x(), fCorner.y());
        FixturePopUp->setPopupText(1, "Function");
        FixturePopUp->mSetPlaceHolder(1, ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode).ChannelVec.at(SelectedChan).name);
        FixturePopUp->setPopupText(2, "Min Value");
        FixturePopUp->mSetPlaceHolder(2, "000");

        FixturePopUp->setPopupText(3, "Max Value");
        FixturePopUp->mSetPlaceHolder(3, "255");

        FixturePopUp->setPopupText(4, "Min Range");
        FixturePopUp->mSetPlaceHolder(4, "0");
        FixturePopUp->setPopupText(5, "Max Range");
        FixturePopUp->mSetPlaceHolder(5, "100");

        FixturePopUp->show();
        //popUpExist = true;
        FixturePopUp->pDiaShadow->setWindowOpacity(0.2);
    //    FixturePopUp->pDiaShadow->setGeometry(fCorner.x()-10,fCorner.y()-10, sCorner.x(),sCorner.y());
        connect(FixturePopUp, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(ReceivePopUpFunc(QVariant)));
    }
}
void Fixture::ReceivePopUpFunc(QVariant vParams){
    PopUpReturn uParams = vParams.value<PopUpReturn>();
    int FunID = ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode).ChannelVec.at(SelectedChan).FuncVec.size();
    Channel * Chan = (Channel *) &ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode).ChannelVec.at(SelectedChan);
    Function Parm;
    Parm.Name = uParams.s1;
    Parm.Min = uParams.s2.toInt();
    Parm.Max = uParams.s3.toInt();
    Parm.Start = uParams.s4.toInt();
    Parm.Stop = uParams.s5.toInt();
    Chan->FuncVec.append(Parm);
//    ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(0).ChannelVec.at(0).FuncVec.a

    AddButtonToScrollArea(FunID, Parm.Name, blueBtnClr, "Param_name", 20, ui->vertFuncName, SLOT(Button_Click()));
    AddButtonToScrollArea(FunID, QString::number(Parm.Min), blueBtnClr, "Param_minval", 20, ui->vertFuncMinVal, SLOT(Button_Click()));
    AddButtonToScrollArea(FunID, QString::number(Parm.Max), blueBtnClr, "Param_maxval", 20, ui->vertFuncMaxVal, SLOT(Button_Click()));
    AddButtonToScrollArea(FunID, QString::number(Parm.Start), blueBtnClr, "Param_minrange", 20, ui->vertFuncMinRng, SLOT(Button_Click()));
    AddButtonToScrollArea(FunID++, QString::number(Parm.Stop), blueBtnClr, "Param_maxrange", 20, ui->vertFuncMaxRng, SLOT(Button_Click()));

    int maxh = ui->widget_19->geometry().height()-OTHER_ITEM_HEIGHT;
    ui->scrollArea_10->setMinimumHeight((FunID*20+4)>maxh?maxh:(FunID*20+4));

}


void Fixture::on_pbPatch_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    saveFixtureList();
}

void Fixture::on_pbMode_clicked()
{
    QString Modes[5];
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
    int size = ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.size();
    if (size > 1){
        for (int i = 0; i < size; i++){
            Modes[i] = ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(i).Name;
        }
        uiP->Option("Enter Mode Value", Modes, size,  1); //Ref = 1 for Mode
        uiP->show();
        connect(uiP, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(FixtureParams_SLOT(QVariant)));
    }
}


void Fixture::on_pbQuantity_clicked()
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
    uiP->Query("How many Fixtures to Add", "1", 2); //Ref = 2 for Quantity
    uiP->show();
    connect(uiP, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(FixtureParams_SLOT(QVariant)));
}

void Fixture::on_pbUniverse_clicked()
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
    uiP->Query("Enter Universe Value", "0", 3); //Ref = 3 for Universe
    uiP->show();
    connect(uiP, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(FixtureParams_SLOT(QVariant)));
}

void Fixture::on_pbAddress_clicked()
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
    uiP->Query("Enter Address Value", "0", 4); //Ref = 4 for Address
    uiP->show();
    connect(uiP, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(FixtureParams_SLOT(QVariant)));
}

void Fixture::on_pbFixtureID_clicked()
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
    uiP->Query("Enter Starting Fixture ID", "0", 5); //Ref = 5 for FixtureID
    uiP->show();
    connect(uiP, SIGNAL(valueEntered_SIGNAL(QVariant)) , this, SLOT(FixtureParams_SLOT(QVariant)));
}

QString Convert3Dig(int num){QString s = "000"+QString::number(num); return s.right(3);}

void Fixture::FixtureParams_SLOT(QVariant vParams){
PopUpReturn uSel = vParams.value<PopUpReturn>();
    if (uSel.Ref == 1) { //Mode button pressed
        patchData.Mode = uSel.s1;
        ui->pbMode->setText("Mode \n "+uSel.s1);
        DataVals |= 1;
    }
    if (uSel.Ref == 2) { //Quantity button pressed
        patchData.Quantity = uSel.s1.toUInt();
        ui->pbQuantity->setText("Quantity \n "+QString::number(patchData.Quantity));
        DataVals |= 2;
    }
    if (uSel.Ref == 3) { //Universe button pressed
        patchData.Universe = uSel.s1.toUInt();
        ui->pbUniverse->setText("Universe \n "+Convert3Dig(patchData.Universe));
        DataVals |= 4;
    }
    if (uSel.Ref == 4) { //Address button pressed
        patchData.Address = uSel.s1.toUInt();
        ui->pbAddress->setText("Address \n "+Convert3Dig(patchData.Address));
        DataVals |= 8;
    }
    if (uSel.Ref == 5) { //Fixture ID button pressed
        patchData.FixID = uSel.s1.toUInt();
        ui->pbFixtureID->setText("Fixture ID \n "+Convert3Dig(patchData.FixID));
        DataVals |= 16;
    }
    if (DataVals == 31) {

        //ui->pbPatch_3->setStyleSheet();
        ui->pbPatchFix->setStyleSheet("QPushButton{background-color: rgb(0, 170, 0);border-style: solid;border-color: rgb(0, 170, 0);border-width: 5px;border-radius: 5px;}");
    }
}

void Fixture::on_pbPatch_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    int size = ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.size();
    if (size == 1){
        patchData.Mode = ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(0).Name;
        ui->pbMode->setText("Mode \n "+patchData.Mode);
        DataVals |= 1;
    }
}

void Fixture::on_pbPatchFix_clicked()
{
    ShowFixtures sfData;
    QVariant vOut;
    if(DataVals == 31){
        ui->pbFixtureID->setText("Fixture ID");
        ui->pbMode->setText("Mode");
        ui->pbQuantity->setText("Quantity");
        //ui->pbUniverse->setText("Universe");
        //ui->pbAddress->setText("Address");
        patchData.Address += patchData.Quantity;
        patchData.FixID += patchData.Quantity;
        ui->pbAddress->setText("Address \n "+Convert3Dig(patchData.Address));
        ui->pbFixtureID->setText("Fixture ID \n "+Convert3Dig(patchData.FixID));
        ui->pbPatchFix->setStyleSheet("QPushButton{background-color: rgb(170, 0, 0);border-style: solid;border-color: rgb(170, 0, 0);border-width: 5px;border-radius: 5px;}");
        DataVals = 28;
        sfData.ID = patchData.FixID;
        sfData.Mode = ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).ModeVec.at(SelectedMode).Name;
        sfData.Model = ManuVec.at(SelectedMan).ModelVec.at(SelectedModel).Name;
        sfData.Mnfctr = ManuVec.at(SelectedMan).Name;
        sfData.Universe = patchData.Universe;
        sfData.Quantity = patchData.Quantity;
        vOut.setValue(sfData);
        emit AddFixturesSIGNAL(vOut);
        ui->stackedWidget->setCurrentIndex(0);
    }
}

