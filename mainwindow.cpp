#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
setConnection();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setConnection(){
    buffer = new Car;
    t_model = new QCarModel;
    ui->setupUi(this);
    ui->tableView->setModel(t_model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setColumnWidth(2, 250);
    ui->tableView->setColumnWidth(4, 150);
    DAddCar *daddcar = new DAddCar();
    findDialog *fndD = new findDialog();
    setStatusBar();
    QString path("/buffer");
    QDir dir;
    if (!dir.exists(path))
        dir.mkpath(path);
    QFile file("c://buffer//buffer.xlsx");
    file.open(QIODevice::ReadWrite); // Or QIODevice::ReadWrite
    file.close();
    connect(ui->about,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->aboutQt,SIGNAL(triggered()),this,SLOT(aboutQt()));
    connect(ui->FAQ,SIGNAL(triggered()),this,SLOT(faq()));
    connect(ui->add,SIGNAL(triggered()),daddcar,SLOT(show()));
    connect(ui->copy,SIGNAL(triggered()),this,SLOT(copy()));
    connect(ui->cut,SIGNAL(triggered()),this,SLOT(cut()));
    connect(ui->find,SIGNAL(triggered()),fndD,SLOT(show()));
    connect(ui->open,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->paste,SIGNAL(triggered()),this,SLOT(paste()));
    connect(ui->save,SIGNAL(triggered()),this,SLOT(save()));
    connect(daddcar,SIGNAL(sendData(QString,QString,QString,QString,QString,QString)),this,SLOT(receiveData(QString,QString,QString,QString,QString,QString)));
    connect(fndD,SIGNAL(SfindData(int,QString)),this,SLOT(getFind(int,QString)));
    connect(ui->findNext,SIGNAL(triggered()),this,SLOT(nfindpush()));
    connect(ui->findPrev,SIGNAL(triggered()),this,SLOT(pfindpush()));
    connect(ui->new1,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->append,SIGNAL(triggered()),this,SLOT(append()));
    connect(ui->saveAs,SIGNAL(triggered()),this,SLOT(saveAs()));
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));
    setCurrentFile("");
    Excel();
}
void MainWindow::Excel(){ // Данная функция нужна, чтобы оптимизировать открытие файла, вместо того, чтобы использовать поток, мы открываем эксель при создании главного окна
    excel = new QAxWidget("Excel.Application");
    excel->setProperty("DisplayAlerts", "0");
    workbooks = excel->querySubObject("WorkBooks");

    workbooks->dynamicCall("Add");
    workbook=excel->querySubObject("ActiveWorkBook");
    workbook->dynamicCall("SaveAs (const QString&)", "c:\\buffer\\buffer.xlsx");
    workbook->dynamicCall("Close (Boolean)", false);
    workbook->clear();
    delete workbook;
    workbook = NULL;
     workbook = workbooks->querySubObject("Open (const QString&)","c:\\buffer\\buffer.xlsx");
}
void MainWindow::receiveData(QString make,QString model, QString power, QString engine, QString year, QString plat ){
    t_model->addCar(make,model,power,engine,year,plat);
}
void MainWindow::nfindpush(){
    emit getFind(1,findBuffer);
}
void MainWindow::pfindpush(){
    emit getFind(2,findBuffer);
}
void MainWindow::removeRows(){
    QModelIndexList indexes =  ui->tableView->selectionModel()->selectedRows();
    int countRow = indexes.count();
    if(countRow!=0){
    QModelIndex deleteindex = ui->tableView->selectionModel()->selectedRows().first();
    QModelIndex deleteindex2 = ui->tableView->selectionModel()->selectedRows().last();
    if(deleteindex.row() > deleteindex2.row()) deleteindex = deleteindex2;
    while(countRow>0){
        t_model->remove( deleteindex.row());
        countRow--;
    }
    }
}
void MainWindow::copy(){
    QModelIndexList indexes=ui->tableView->selectionModel()->selectedRows();
    sizeBuffer = indexes.count();
    if(sizeBuffer!=0){
            delete buffer;
        buffer = new Car[sizeBuffer];
        for(int i = 0;i<sizeBuffer;i++){
            buffer[i] = t_model->value[indexes.at(i).row()];
        }
        statusBar()->showMessage("Данные занесены в буффер");
    }
}
void MainWindow::paste(){
    for(int i = 0; i<sizeBuffer;i++){
        t_model->addExcelCar(buffer[i]);
    }
    statusBar()->showMessage("Данные успешно добавлены");
}
void MainWindow::cut(){
    copy();
    removeRows();
    statusBar()->showMessage("Данные занесены в буффер");
}
void MainWindow::getFind(int row, QString str){ // row == 0(findAll), 1(findNext), 2(findPrev) ; str(text,which should will be has find);
    findBuffer = str;
    bool isFind = false;
    int k;
   if(ui->tableView->selectionModel()->hasSelection())
       k = ui->tableView->selectionModel()->selectedRows().last().row();
   else k = -1;
    if(row == 0){

            for(int i=0;i<5;i++){
                for(int x=0;x<=t_model->rowCount(QModelIndex());x++){
                    QModelIndex ind = t_model->index(x,i);
                    if(ind.data().toString()==findBuffer){
                        isFind = true;
                        ui->tableView->scrollTo(ind);
                        ui->tableView->selectRow(ind.row());
                        break;
                    }
                }
            }

    }
    else if(row == 1){
        for(int x=k+1;x<=t_model->rowCount(QModelIndex());x++){
            if(isFind == true) break;
            for(int i=0;i<5;i++){
                QModelIndex ind = t_model->index(x,i);
                if(ind.data().toString()==findBuffer){
                    isFind = true;
                    ui->tableView->scrollTo(ind);
                    ui->tableView->selectRow(ind.row());
                    break;
                }
            }
        }
    }
    else{
        for(int x=k-1;x>=0;x--){
            if(isFind == true) break;
            for(int i=0;i<5;i++){
                QModelIndex ind = t_model->index(x,i);
                if(ind.data().toString()==findBuffer){
                    isFind = true;
                    ui->tableView->scrollTo(ind);
                    ui->tableView->selectRow(ind.row());
                    break;
                }
            }
        }
    }
    if(isFind == false){
        QMessageBox::information(this,"Информация","'"+str+"' не найдено");

    }


}
void MainWindow::newFile(){
    if(t_model->isChanged == true) {
        maybeSave();
    }
    fileBuffer="";
    t_model->clearTable();
    t_model->isChanged=false;
    statusBar()->showMessage("Новый файл успешно создан");
}
void MainWindow::open(){
    fileName = QFileDialog::getOpenFileName( this,QString("Открыть файл"), QString(),QString("MS Excel (*.xlsx)"));
    if(!fileName.isEmpty()){
        if(t_model->isChanged == true) {
            bool s = maybeSave();
            if(s==false) return;
        }
        if(isOpen==false){
    setCurrentFile(fileName);
    fileBuffer=fileName;
    t_model->clearTable();
    workbook = workbooks->querySubObject("Open (const QString&)", fileName);
    sheet = workbook->querySubObject("Worksheets(int)", 1);
    QAxObject *usedRange = sheet->querySubObject("UsedRange");
    QAxObject *usedRows = usedRange->querySubObject("Rows");
    QAxObject *usedCols = usedRange->querySubObject("Columns");
    mRows = usedRows->property("Count").toInt();
    if(mRows != 0)  {// Если файл не пуст, то считать данные
    for(int i = 2;i<=mRows+1;i++){ // Начинаем с 2 индекса, так как 1 строка отвечает за хедер
        for(int j = 1; j<6; j++){
            cell = sheet->querySubObject("Cells(QVariant,QVariant)", i, j);
            data = cell->property("Value").toString();
            switch(j){
            case 1: temp.SetMake(data);
            case 2: temp.SetModel(data);
            case 3: temp.SetPower(data);
            case 4: temp.SetEngine(data);
            case 5: temp.SetYear(data);
            case 6: temp.SetPlay(data); break;
            }
        }
        t_model->addExcelCar(temp);
    }
    cell->clear();
    delete cell;
    cell = NULL;
 }
    delete usedCols;
    delete usedRows;
    delete usedRange;
    isOpen = true;
    statusBar()->showMessage("Файл успешно открыт");
    }
    else{
        fileBuffer=fileName;
        setCurrentFile(fileName);
        t_model->clearTable();
        sheet->clear();
         delete sheet;
        sheet = NULL;
        workbook->clear();
         delete workbook;
        workbook = NULL;
        workbook = workbooks->querySubObject("Open (const QString&)", fileName);
        sheet = workbook->querySubObject("Worksheets(int)", 1);
        QAxObject *usedRange = sheet->querySubObject("UsedRange");
        QAxObject *usedRows = usedRange->querySubObject("Rows");
        QAxObject *usedCols = usedRange->querySubObject("Columns");
        mRows = usedRows->property("Count").toInt();
        if(mRows != 0)  {// Если файл не пуст, то считать данные
        for(int i = 2;i<=mRows+1;i++){ // Начинаем с 2 индекса, так как 1 строка отвечает за хедер
            for(int j = 1; j<6; j++){
                cell = sheet->querySubObject("Cells(QVariant,QVariant)", i, j);
                data = cell->property("Value").toString();
                switch(j){
                case 1: temp.SetMake(data);
                case 2: temp.SetModel(data);
                case 3: temp.SetPower(data);
                case 4: temp.SetEngine(data);
                case 5: temp.SetYear(data);
                case 6: temp.SetPlay(data); break;
                }
            }
            t_model->addExcelCar(temp);
        }
        cell->clear();
        delete cell;
        cell = NULL;
     }
        delete usedCols;
        delete usedRows;
        delete usedRange;
        t_model->isChanged=false;
        statusBar()->showMessage("Файл успешно открыт");

    }
}
    else{
        statusBar()->showMessage("Ошибка в открытии файла");
    }
}
void MainWindow::append(){
    fileName = QFileDialog::getOpenFileName( this,QString("Открыть файл"), QString(),QString("MS Excel (*.xlsx)"));
    if(!fileName.isEmpty()){
        if(fileBuffer!=nullptr){
            sheet->clear();
             delete sheet;
            sheet = NULL;
            workbook->clear();
             delete workbook;
            workbook = NULL;
        }
    workbook = workbooks->querySubObject("Open (const QString&)", fileName);
    sheet = workbook->querySubObject("Worksheets(int)", 1);
    QAxObject *usedRange = sheet->querySubObject("UsedRange");
    QAxObject *usedRows = usedRange->querySubObject("Rows");
    QAxObject *usedCols = usedRange->querySubObject("Columns");
    mRows = usedRows->property("Count").toInt();
    if(mRows != 0)  {// Если файл не пуст, то считать данные
    for(int i = 2;i<=mRows+1;i++){ // Начинаем с 2 индекса, так как 1 строка отвечает за хедер
        for(int j = 1; j<6; j++){
            cell = sheet->querySubObject("Cells(QVariant,QVariant)", i, j);
            data = cell->property("Value").toString();
            switch(j){
            case 1: temp.SetMake(data);
            case 2: temp.SetModel(data);
            case 3: temp.SetPower(data);
            case 4: temp.SetEngine(data);
            case 5: temp.SetYear(data);
            case 6: temp.SetPlay(data); break;
            }
        }
        t_model->addExcelCar(temp);
    }
    cell->clear();
    delete cell;
    cell = NULL;
 }
    delete usedCols;
    delete usedRows;
    delete usedRange;
    t_model->isChanged=true;
    statusBar()->showMessage("Таблицы успешно объединены");
    sheet->clear();
     delete sheet;
    sheet = NULL;
    workbook->clear();
     delete workbook;
    workbook = NULL;
    fileName=fileBuffer;
    if(fileBuffer!=nullptr){
 // восстанавливаем работу с прошлым файлом, если она была
    workbook = workbooks->querySubObject("Open (const QString&)", fileName);
    sheet = workbook->querySubObject("Worksheets(int)", 1);
    }
    }
    else
    {
         fileName=fileBuffer;
        statusBar()->showMessage("Ошибка в открытии файла");
    }
}
void MainWindow::closeEvent(QCloseEvent *event){
    if(maybeSave()){
        event->accept();
    }
    else{
        event->ignore();
        return;
    }
    if(fileName!=nullptr){
    sheet->clear();
     delete sheet;
    sheet = NULL;
    workbook->dynamicCall("Save");
    workbook->clear();
     delete workbook;
    workbook = NULL;
     workbooks->dynamicCall( "Close" );
     workbooks->clear();
    delete workbooks;
     workbooks = NULL;
     excel->dynamicCall( "Quit" );
     delete excel;
     excel = NULL;
     }
}
bool MainWindow::saveFile(){
    if(!fileName.isEmpty()){
        if(isSaveAs == true){
            if(isOpen==false){
              //  excel = new QAxWidget("Excel.Application",this);
             //   excel->setProperty("Visible", false);
              //  excel->setProperty("DisplayAlerts", "0");
            }
            else{
                sheet->clear();
                 delete sheet;
                sheet = NULL;
                workbook->clear();
                 delete workbook;
                workbook = NULL;
                workbooks->dynamicCall( "Close" );
                workbooks->clear();
               delete workbooks;
                workbooks = NULL;
            }
            fileBuffer=fileName;
            fileName.replace(QRegExp("/"), "\\");
           // workbooks = excel->querySubObject("WorkBooks");
            workbooks->dynamicCall("Add");
            workbook=excel->querySubObject("ActiveWorkBook");
            sheet = workbook->querySubObject("WorkSheets");
            workbook->dynamicCall("SaveAs (const QString&)", fileName);
           workbook->dynamicCall("Close (Boolean)", false);
         //   excel->setProperty("DisplayAlerts",1);
        //   excel->dynamicCall("Quit(void)");
           workbook = workbooks->querySubObject("Open (const QString&)", fileName);
           sheet = workbook->querySubObject("Worksheets(int)", 1);
           isSaveAs=false;
           t_model->isChanged=false;

        }
    List::Iterator it = t_model->value.begin();

    if( it.GetHead()!=nullptr ){ // делаем проверку, если были добавлены элементы в лист, то заносим данные в файл
        if(mRows>t_model->value.GetSize()){ // Данная проверка нужна для того, чтобы проверить удалили ли мы что-то из таблицы, которую использовали
                                            // Если да, то сначала мы заносим новые данные, а затем стираем старые вторым циклом
            for(int i = 2; i<t_model->value.GetSize()+2;i++){
                for(int j = 1; j<7; j++){
                    cell = sheet->querySubObject("Cells(QVariant,QVariant)", i, j);
                    cell->setProperty("Value",t_model->value[i-2][j-1]);
        }
            }
            for(int i = t_model->value.GetSize()+2;i<mRows+2;i++){
                for(int j =1; j<7; j++){
                    cell = sheet->querySubObject("Cells(QVariant,QVariant)", i, j);
                    cell->setProperty("Value"," ");
                }
            }
        }
                else{
                    for(int i = 2; i<t_model->value.GetSize()+2;i++){
                        for(int j = 1; j<7; j++){
                            cell = sheet->querySubObject("Cells(QVariant,QVariant)", i, j);
                            cell->setProperty("Value",t_model->value[i-2][j-1]);
                        }
                    }
                }
    cell->clear();
    delete cell;
    cell = NULL;

        }
    t_model->isChanged=false;
    statusBar()->showMessage("Файл успешно сохранён");
    return true;
    }
    else{
        return false;
    }
}
bool MainWindow::saveAs(){
    fileName = QFileDialog::getSaveFileName(this,QString("Открыть файл"), QString(),QString("MS Excel (*.xlsx)") );
    fileBuffer=fileName;
    setCurrentFile(fileName);
    if(fileName.isEmpty())
        return false;
    isSaveAs=true;
    return saveFile();
}
void MainWindow::setStatusBar()
{
#ifndef QT_NO_STATUSBAR
    ( void )statusBar();
#endif
}
bool MainWindow::maybeSave(){
    if (t_model->isChanged==true) {
        int ret = QMessageBox::warning(this, tr("CarBase"),
                      tr("The document has been modified.\n"
                         "Do you want to save your changes?"),
                      QMessageBox::Yes | QMessageBox::Default,
                      QMessageBox::No,
                      QMessageBox::Cancel | QMessageBox::Escape);
        if (ret == QMessageBox::Yes)
          return save();
        else if (ret == QMessageBox::Cancel)
          return false;
      } return true;
}
bool MainWindow::save(){
    if( fileName == nullptr){
        return saveAs();
    }
    else{
        saveFile();
    }
}
void MainWindow::setCurrentFile(const QString &Name){
    fileName=Name;
   // t_model->isChanged=false;
    QString shownName;
    if(fileName==nullptr){
        shownName = tr("untitled.xlsx");}
    else{
        shownName = QFileInfo(fileName).fileName();
    }
    setWindowTitle(tr("%1[*]--%2").arg(shownName).arg(tr("CarBase")));
}
void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    QMenu menu(this);
    menu.addAction("Вырезать",this,SLOT(cut()));
    menu.addAction("Копировать",this,SLOT(copy()));
    menu.addSeparator();
    menu.addAction("Вставить",this,SLOT(paste()));
    menu.addAction("Удалить", this, SLOT(removeRows()));
    menu.addSeparator();
    menu.addAction("Exit", qApp, SLOT(qApp->exit()));
    menu.exec(event->globalPos());
}
void MainWindow::about(){
    QMessageBox::about(this,"О программе","Данная программа создана по заданию курсового проекта.\nСоздать базу данных, работающую на основе контейнера, который следует разработать в процессе выполнения курсовой работы. В качестве прототипа контейнера можно использовать контейнеры vector или list из библиотеки STL. Для работы с контейнером следует предусмотреть итератор. Остальные требования к контейнеру определяются студентом самостоятельно.Разрабатываемая база данных должна быть создана использованием C++ и библиотеки Qt4. Среда программировании Qt Creater.");
}
void MainWindow::aboutQt(){
    QMessageBox::aboutQt(this,"О Qt");

}
void MainWindow::faq(){
    QMessageBox::information(this,"FAQ","Данная программа выполняет функцию базы данных.\n База может работать с программой MS Excel(начиная от 2007).\n Во время работы с программой желательно закрыть Excel, в избежании критических ошибок.\n Программа создаёт дополнительный файл для работы на диске C в папке 'buffer'.\n Если нашли ошибки в работе программы отправляйте их на почту kolen322@yandex.ru");
}
