#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("MiniWord"));
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);

    //菜单栏
    createAction = new QAction(tr("New"), this);
    createAction->setShortcuts(QKeySequence::New);
    createAction->setStatusTip(tr("Create a file"));
    connect(createAction, &QAction::triggered, this, &MainWindow::create);

    openAction = new QAction(tr("Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(tr("Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save current file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    saveasAction = new QAction(tr("Save as..."), this);
    saveasAction->setShortcuts(QKeySequence::SaveAs);
    saveasAction->setStatusTip(tr("Save as..."));
    connect(saveasAction, &QAction::triggered, this, &MainWindow::save_as);

    quitAction = new QAction(tr("Quit"), this);
    quitAction->setShortcuts(QKeySequence::Close);
    quitAction->setStatusTip(tr("Quit"));
    connect(quitAction,&QAction::triggered,this,&MainWindow::close);

    searchAction = new QAction(tr("Search..."), this);
    searchAction->setShortcuts(QKeySequence::Find);
    searchAction->setStatusTip(tr("Search..."));
    connect(searchAction,&QAction::triggered,this,&MainWindow::search_init);

    replaceAction = new QAction(tr("Replace"), this);
    replaceAction->setShortcuts(QKeySequence::Replace);
    replaceAction->setStatusTip(tr("Replace"));
    connect(replaceAction,&QAction::triggered,this,&MainWindow::search_init);

    copyAction = new QAction("Block Copy", this);
    connect(copyAction,&QAction::triggered,this,&MainWindow::block_copy);
    copyAction->setShortcut(QKeySequence::Copy);

    pasteAction = new QAction("Block Paste", this);
    connect(pasteAction,&QAction::triggered,this,&MainWindow::block_paste);
    pasteAction->setShortcut(QKeySequence::Paste);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(createAction);
    file->addSection("");
    file->addAction(openAction);
    file->addAction(saveAction);
    file->addAction(saveasAction);
    file->addSection("");
    file->addAction(quitAction);
    QMenu *edit = menuBar()->addMenu(tr("&Edit"));
    edit->addAction(searchAction);
    edit->addAction(replaceAction);
    edit->addSection("");
    edit->addAction(copyAction);
    edit->addAction(pasteAction);
    QMenu *info = menuBar()->addMenu(tr("&Info"));
    //info->addAction(aboutRole);

    SearchInput.setParent(&SearchDialog);
    ReplaceInput.setParent(&SearchDialog);
    Replace.setParent(&SearchDialog);
    Search.setParent(&SearchDialog);
    SearchNext.setParent(&SearchDialog);
    SearchTips.setParent(&SearchDialog);
    SearchDialog.setSizeIncrement(410,6*LINE_HEIGHT);
    SearchDialog.setWindowTitle("Search");
    SearchDialog.setModal(0);
    SearchInput.setGeometry(INPUT_LEFT_BLANK,LINE_GAP,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    SearchInput.setPlaceholderText("typing...");
    ReplaceInput.setGeometry(210+INPUT_LEFT_BLANK,LINE_GAP,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    ReplaceInput.setPlaceholderText("to...");
    Search.setGeometry(INPUT_LEFT_BLANK,2*LINE_GAP+LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    Search.setText("Search");
    Search.setStyleSheet("color:black");
    connect(&Search,&QPushButton::clicked,this,&MainWindow::search);
    SearchNext.setGeometry(INPUT_LEFT_BLANK,3*LINE_GAP+2*LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    SearchNext.setText("Next");
    connect(&SearchNext,&QPushButton::clicked,this,&MainWindow::search_next);
    Replace.setGeometry(210+INPUT_LEFT_BLANK,2*LINE_GAP+LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    Replace.setText("Replace");
    SearchTips.setGeometry(210+INPUT_LEFT_BLANK,3*LINE_GAP+2*LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);


    //菜单栏初始化
    saveAction->setDisabled(1);
    saveasAction->setDisabled(1);

    QWidget::setAttribute(Qt::WA_InputMethodEnabled,true);

    //状态栏
    statusBar();
    //显示
    screen.InitiateScreen(this);
    QTimer *display_timer = new QTimer(this);
    connect(display_timer, SIGNAL(timeout()), this, SLOT(DisplayScreen()));
    display_timer->start(REFLASH_TIME);

    QTimer::singleShot(3,this,SLOT(create()));
}

void MainWindow::wheelEvent(QWheelEvent *event){
    if(event->delta() >0){
        //up
        Memory->MoveUp();
        screen.LoadScreen(*Memory);
    }else{
        //down
        Memory->MoveDown();
        screen.LoadScreen(*Memory);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(!Selected){
        switch (event->key()) {
        case Qt::Key_Alt:
            qDebug()<<"SelectTriggered!";
            SelectTriggered = true;
            col_ = Memory->GetCursorCol();
            row_ = Memory->GetCursorRow();
            statusBar()->showMessage("Block Selecting");
            screen.LoadScreen(*Memory);
            break;
        default:
            if(event->text() != "" && event->text() != "\u007F" && event->text() != "\r" && event->text() != "\b"){
                Memory->InsertString(event->text());
                statusBar()->showMessage("Typing...");
                qDebug()<<"Input English:"<<event->text();
            }
            screen.LoadScreen(*Memory);
            break;
        }
    }else{
        switch (event->key()) {
        case Qt::Key_Alt:
            qDebug()<<"SelectContinueTriggered!";
            SelectTriggered = true;
            Selected = false;
            statusBar()->showMessage("Block Selecting");
            screen.LoadScreen(*Memory);
            break;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {

    switch (event->key()) {
    case Qt::Key_Up:
        if(SelectTriggered){
            qDebug()<<"Selected Cursor Up!";
            Memory->MoveUp();
            screen.HighlightMode(row_,col_,Memory->GetCursorRow(),Memory->GetCursorCol());
        }else{
            qDebug()<<"Cursor Up!";
            Memory->MoveUp();
            screen.CursorMode();
        }
        if(Selected)
            Selected = false;
        screen.LoadScreen(*Memory);
        break;
    case Qt::Key_Down:
        if(SelectTriggered){
            qDebug()<<"Selected Cursor Down!";
            Memory->MoveDown();
            screen.HighlightMode(row_,col_,Memory->GetCursorRow(),Memory->GetCursorCol());
        }else{
            qDebug()<<"Cursor Down!";
            Memory->MoveDown();
            screen.CursorMode();
        }
        if(Selected)
            Selected = false;
        screen.LoadScreen(*Memory);
        break;
    case Qt::Key_Left:
        if(SelectTriggered){
            qDebug()<<"Selected Cursor Left!";
            Memory->MoveLeft();
            screen.HighlightMode(row_,col_,Memory->GetCursorRow(),Memory->GetCursorCol());
        }else{
            qDebug()<<"Cursor Left!";
            Memory->MoveLeft();
            screen.CursorMode();
        }
        if(Selected)
            Selected = false;

        screen.LoadScreen(*Memory);
        break;
    case Qt::Key_Right:
        if(SelectTriggered){
            qDebug()<<"Selected Cursor Right!";
            Memory->MoveRight();
            screen.HighlightMode(row_,col_,Memory->GetCursorRow(),Memory->GetCursorCol());
        }else{
            qDebug()<<"Cursor Right!";
            Memory->MoveRight();
            screen.CursorMode();
        }
        if(Selected)
            Selected = false;
        screen.LoadScreen(*Memory);
        break;
    case Qt::Key_Return:
        if(Selected)
            Selected = false;
        else{
            qDebug()<<"Add blank line!";
            Memory->InsertString("");
            filepart->set_edited(true);
            screen.CursorMode();
            screen.LoadScreen(*Memory);
        }
        break;
    case Qt::Key_Delete:
        if(Selected){
            filepart->set_edited(true);
            qDebug()<<"Block Deleted! "<< row_<< ","<< col_<<"  "<< Memory->GetCursorRow()<<","<<Memory->GetCursorCol();
            int temp_col = Memory->GetCursorCol(),temp_row = Memory->GetCursorRow();
            Memory->BlockDelete(row_,col_,temp_row,temp_col);
            Selected = false;
            copyAction->setDisabled(1);
            pasteAction->setEnabled(1);
            screen.CursorMode();
            screen.LoadScreen(*Memory);
            break;
        }else{
            qDebug()<<"Delete!";
            Memory->Delete();
            filepart->set_edited(true);
            screen.LoadScreen(*Memory);
        }
        break;
    case Qt::Key_Backspace:
        if(Selected){
            filepart->set_edited(true);
            qDebug()<<"Block Deleted! "<< row_<< ","<< col_<<"  "<< Memory->GetCursorRow()<<","<<Memory->GetCursorCol();
            int temp_col = Memory->GetCursorCol(),temp_row = Memory->GetCursorRow();
            Memory->BlockDelete(row_,col_,temp_row,temp_col);
            Selected = false;
            copyAction->setDisabled(1);
            pasteAction->setEnabled(1);
            screen.CursorMode();
            screen.LoadScreen(*Memory);
            break;
        }else{
            qDebug()<<"Backspace!";
            Memory->Backspace();
            filepart->set_edited(true);
            screen.LoadScreen(*Memory);
            break;
        }
    case Qt::Key_Alt:
        qDebug()<<"Block Selected!";
        screen.HighlightMode(row_,col_,Memory->GetCursorRow(),Memory->GetCursorCol());
        screen.LoadScreen(*Memory);
        SelectTriggered = false;
        copyAction->setEnabled(1);
        Selected = true;

    //default:

        //break;
    }
}

void MainWindow::inputMethodEvent(QInputMethodEvent *e){
    if(e->commitString() != ""){
        qDebug()<<"from InputMethod:"<<e->commitString();
        Memory->InsertString(e->commitString());
        screen.LoadScreen(*Memory);
    }
}

void MainWindow::search_init(){
    SearchDialog.exec();
}

void MainWindow::search(){
    bool result = Memory->SearchWord(SearchInput.text());
    screen.LoadScreen(*Memory);
    qDebug()<<"Seached: "<<SearchInput.text();
    screen.LoadScreen(*Memory);
    if(result){
        qDebug()<<"Search Success!";
        QString temp = "Row: "+QString::number(Memory->GetCursorRow())+",Col: "+QString::number(Memory->GetCursorCol());
        SearchTips.setText(temp);
    }else{
        qDebug()<<"Not Found!";
        SearchTips.setText("Not Found!");
    }
}

void MainWindow::search_next(){
    Memory->MoveRight();
    bool result = Memory->SearchWord(SearchInput.text());
    screen.LoadScreen(*Memory);
    qDebug()<<"Seached: "<<SearchInput.text();
    screen.LoadScreen(*Memory);
    if(result){
        qDebug()<<"Search Success!";
        QString temp = "Row: "+QString::number(Memory->GetCursorRow())+",Col: "+QString::number(Memory->GetCursorCol());
        SearchTips.setText(temp);
    }else{
        qDebug()<<"Not Found!";
        Memory->MoveLeft();
        SearchTips.setText("Not Found!");
    }
}

void MainWindow::DisplayScreen() {
    screen.DisplayScreen();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(filepart->is_create()){
        QMessageBox msgBox;
        msgBox.setText(tr("File not saved, save?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save,"Save");
        msgBox.setButtonText(QMessageBox::Discard,"Discard");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            qDebug() << "Save!";
            save_as();
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard!";
            break;
        default:
            qDebug() << "Close!";
            break;
        }
    }
    else if(filepart->is_edited()){
        QMessageBox msgBox;
        msgBox.setText(tr("File not saved, save?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save,"Save");
        msgBox.setButtonText(QMessageBox::Discard,"Discard");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            qDebug() << "Save!";
            save_as();
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard!";
            break;
        default:
            qDebug() << "Close!";
            break;
        }
    }
}

void MainWindow::create(){
    if(filepart->is_edited()){
        QMessageBox msgBox;
        msgBox.setText(tr("File not saved, save?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save,"Save");
        msgBox.setButtonText(QMessageBox::Discard,"Discard");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            qDebug() << "Save!";
            save_as();
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard!";
            break;
        default:
            qDebug() << "Close!";
            break;
        }
    }
    emit SendCreateSignal();
    statusBar()->showMessage("New File");
    saveAction->setEnabled(1);
    saveasAction->setEnabled(1);
    screen.LoadScreen(*Memory);
}

void MainWindow::open(){
    if(filepart->is_edited()){
        QMessageBox msgBox;
        msgBox.setText(tr("File not saved, save?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save,"Save");
        msgBox.setButtonText(QMessageBox::Discard,"Discard");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            qDebug() << "Save!";
            save();
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard!";
            break;
        default:
            qDebug() << "Close!";
            break;
        }
    }
    QString FilePath = QFileDialog::getOpenFileName(this,tr("Open..."));
    qDebug()<<FilePath<<endl;
    emit SendOpenPath(FilePath);
    saveAction->setEnabled(1);
    saveasAction->setEnabled(1);
    statusBar()->showMessage("Open Success!");
    screen.LoadScreen(*Memory);    
}

void MainWindow::save(){
    if(filepart->is_open()){
        QString FilePath;
        if(filepart->is_create()){
            FilePath = QFileDialog::getSaveFileName(this,tr("Save..."),"new_file.txt");
        }
        emit SendSavePath(FilePath);
        statusBar()->showMessage("Save Success!");
    }
}

void MainWindow::save_as(){
    QString FilePath = QFileDialog::getSaveFileName(this,tr("Save as..."),"new_file.txt");
    emit SendSaveAsPath(FilePath);
    statusBar()->showMessage("Save as Success!");
}
