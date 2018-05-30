#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("MiniWord"));
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);

    //菜单栏
    createAction = new QAction(tr("新文件"), this);
    createAction->setShortcuts(QKeySequence::New);
    createAction->setStatusTip(tr("Create a file"));
    connect(createAction, &QAction::triggered, this, &MainWindow::create);

    openAction = new QAction(tr("打开..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(tr("保存"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save current file"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    saveasAction = new QAction(tr("另存为..."), this);
    saveasAction->setShortcuts(QKeySequence::SaveAs);
    saveasAction->setStatusTip(tr("Save as..."));
    connect(saveasAction, &QAction::triggered, this, &MainWindow::save_as);

    quitAction = new QAction(tr("退出"),this);
    quitAction->setShortcuts(QKeySequence::Close);
    quitAction->setStatusTip(tr("Quit"));
    connect(quitAction,&QAction::triggered,this,&MainWindow::close);

    searchAction = new QAction(tr("查找..."),this);
    searchAction->setShortcuts(QKeySequence::Find);
    searchAction->setStatusTip(tr("Search..."));
    connect(searchAction,&QAction::triggered,this,&MainWindow::search);

    replaceAction = new QAction(tr("替换"),this);
    replaceAction->setShortcuts(QKeySequence::Replace);
    replaceAction->setStatusTip(tr("Replace"));
    connect(replaceAction,&QAction::triggered,this,&MainWindow::search);

    copyAction = new QAction("块拷贝",this);
    connect(copyAction,&QAction::triggered,this,&MainWindow::block_copy);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setDisabled(1);

    pasteAction = new QAction("块粘贴",this);
    connect(pasteAction,&QAction::triggered,this,&MainWindow::block_paste);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setDisabled(1);

    QMenu *file = menuBar()->addMenu(tr("&文件"));
    file->addAction(createAction);
    file->addSection("");
    file->addAction(openAction);
    file->addAction(saveAction);
    file->addAction(saveasAction);
    file->addSection("");
    file->addAction(quitAction);
    QMenu *edit = menuBar()->addMenu(tr("&编辑"));
    edit->addAction(searchAction);
    edit->addAction(replaceAction);
    edit->addSection("");
    edit->addAction(copyAction);
    edit->addAction(pasteAction);
    QMenu *info = menuBar()->addMenu(tr("&关于"));
    //info->addAction(aboutRole);

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
}


void MainWindow::keyPressEvent(QKeyEvent *event){
    if(!Selected){
        switch (event->key()) {
        case Qt::Key_Alt:
            qDebug()<<"SelectTriggered!";
            SelectTriggered = true;
            col_ = Memory->GetCursorCol();
            row_ = Memory->GetCursorRow();
            statusBar()->showMessage("进入块选择模式");
            screen.LoadScreen(*Memory);
            break;
        default:
            if(event->text() != ""){
                Memory->InsertString(event->text());
                qDebug()<<"Input English:"<<event->text();
            }
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
            screen.HighlightMode(row_,col_,Memory->GetCursorRow(),Memory->GetCursorCol());
        }else{
            qDebug()<<"Cursor Up!";
            screen.CursorMode();
        }
        if(Selected)
            Selected = false;
        Memory->MoveUp();

        screen.LoadScreen(*Memory);
        break;
    case Qt::Key_Down:
        if(SelectTriggered){
            qDebug()<<"Selected Cursor Down!";
            screen.HighlightMode(row_,col_,Memory->GetCursorRow(),Memory->GetCursorCol());
        }else{
            qDebug()<<"Cursor Down!";
            screen.CursorMode();
        }
        if(Selected)
            Selected = false;
        Memory->MoveDown();
        screen.LoadScreen(*Memory);
        break;
    case Qt::Key_Left:
        if(SelectTriggered){
            qDebug()<<"Selected Cursor Left!";
            screen.HighlightMode(row_,col_,Memory->GetCursorRow(),Memory->GetCursorCol());
        }else{
            qDebug()<<"Cursor Left!";
            screen.CursorMode();
        }
        if(Selected)
            Selected = false;
        Memory->MoveLeft();
        screen.LoadScreen(*Memory);
        break;
    case Qt::Key_Right:
        if(SelectTriggered){
            qDebug()<<"Selected Cursor Right!";
            //高亮
            screen.HighlightMode(row_,col_,Memory->GetCursorRow(),Memory->GetCursorCol());
        }else{
            qDebug()<<"Cursor Right!";
            screen.CursorMode();
        }
        if(Selected)
            Selected = false;
        Memory->MoveRight();
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

void MainWindow::search(){
    QDialog SearchDialog(this);
    SearchDialog.setSizeIncrement(410,4*LINE_HEIGHT);
    SearchDialog.setWindowTitle("查找");
    SearchDialog.setModal(0);
    QLineEdit SearchInput(&SearchDialog),ReplaceInput(&SearchDialog);
    SearchInput.setGeometry(INPUT_LEFT_BLANK,LINE_GAP,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    SearchInput.setPlaceholderText("输入要查找的内容...");
    ReplaceInput.setGeometry(210+INPUT_LEFT_BLANK,LINE_GAP,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    ReplaceInput.setPlaceholderText("替换为...");
    QPushButton Search(&SearchDialog),SearchNext(&SearchDialog),Replace(&SearchDialog);
    Search.setGeometry(INPUT_LEFT_BLANK,2*LINE_GAP+LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    Search.setText("查找");
    Search.setStyleSheet("color:black");
    //connect(&SearchDialog,&Search)
    SearchNext.setGeometry(INPUT_LEFT_BLANK,3*LINE_GAP+2*LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    SearchNext.setText("下一个");
    Replace.setGeometry(210+INPUT_LEFT_BLANK,2*LINE_GAP+LINE_HEIGHT,200-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    Replace.setText("替换");
    SearchDialog.exec();
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
        msgBox.setText(tr("还有未保存的修改，是否保存？"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save,"保存");
        msgBox.setButtonText(QMessageBox::Discard,"不保存");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            qDebug() << "保存！";
            save_as();
            break;
        case QMessageBox::Discard:
            qDebug() << "不保存!";
            break;
        default:
            qDebug() << "关闭对话框！";
            break;
        }
    }
    else if(filepart->is_edited()){
        QMessageBox msgBox;
        msgBox.setText(tr("还有未保存的修改，是否保存？"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save,"保存");
        msgBox.setButtonText(QMessageBox::Discard,"不保存");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            qDebug() << "保存！";
            save();
            break;
        case QMessageBox::Discard:
            qDebug() << "不保存!";
            break;
        default:
            qDebug() << "关闭对话框！";
            break;
        }
    }
}

void MainWindow::create(){
    if(filepart->is_edited()){
        QMessageBox msgBox;
        msgBox.setText(tr("还有未保存的修改，是否保存？"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save,"保存");
        msgBox.setButtonText(QMessageBox::Discard,"不保存");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            save();
            qDebug() << "保存！";
            break;
        case QMessageBox::Discard:
            qDebug() << "不保存!";
            break;
        }
    }
    emit SendCreateSignal();
    saveAction->setEnabled(1);
    saveasAction->setEnabled(1);
    screen.LoadScreen(*Memory);
}

void MainWindow::open(){
    if(filepart->is_edited()){
        QMessageBox msgBox;
        msgBox.setText(tr("还有未保存的修改，是否保存？"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save,"保存");
        msgBox.setButtonText(QMessageBox::Discard,"不保存");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            save();
            qDebug() << "保存！";
            break;
        case QMessageBox::Discard:
            qDebug() << "不保存!";
            break;
        }
    }
    QString FilePath = QFileDialog::getOpenFileName(this,tr("打开..."));
    qDebug()<<FilePath<<endl;
    emit SendOpenPath(FilePath);
    saveAction->setEnabled(1);
    saveasAction->setEnabled(1);
    screen.LoadScreen(*Memory);
    statusBar()->showMessage("打开成功！");
}

void MainWindow::save(){
    if(filepart->is_open()){
        QString FilePath;
        if(filepart->is_create()){
            FilePath = QFileDialog::getSaveFileName(this,tr("保存为..."),"新建文档.txt");
        }
        emit SendSavePath(FilePath);
        statusBar()->showMessage("保存成功！");
    }
}

void MainWindow::save_as(){
    QString FilePath = QFileDialog::getSaveFileName(this,tr("另存为..."),"新建文档.txt");
    emit SendSaveAsPath(FilePath);
    statusBar()->showMessage("另存为成功！");
}
