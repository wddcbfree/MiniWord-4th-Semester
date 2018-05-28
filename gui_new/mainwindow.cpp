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

    selectAction = new QAction(tr("选中块"),this);
    selectAction->setStatusTip(tr("Select"));

    connect(selectAction,&QAction::triggered,this,&MainWindow::select);

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
    edit->addAction(selectAction);
    QMenu *info = menuBar()->addMenu(tr("&关于"));
    //info->addAction(aboutRole);

    //菜单栏初始化
    saveAction->setDisabled(1);
    saveasAction->setDisabled(1);
    selectAction->setDisabled(1);

    //输入框部分
    Input.setParent(this);
    Input.setGeometry(INPUT_LEFT_BLANK,WINDOW_HEIGHT-2*LINE_HEIGHT,WINDOW_WIDTH-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    Input.show();
    Input.setEchoMode(QLineEdit::Normal);
    Input.setPlaceholderText("typing...");
    Input.setReadOnly(0);
    Input.setAcceptDrops(true);
    Input.setClearButtonEnabled(true);

    //输入提示
    InputTips.setParent(this);
    InputTips.setGeometry(INPUT_LEFT_BLANK,WINDOW_HEIGHT-3*LINE_HEIGHT,WINDOW_WIDTH-2*INPUT_LEFT_BLANK,LINE_HEIGHT);
    InputTips.show();
    InputTips.setText("test");

    //状态栏
    statusBar();
    //工具栏

    //显示
    screen.InitiateScreen(this);
    QTimer *display_timer = new QTimer(this);
    connect(display_timer, SIGNAL(timeout()), this, SLOT(DisplayScreen()));
    display_timer->start(REFLASH_TIME);
}

void MainWindow::select(){
    qDebug()<<"Select triggered!";
    selectAction->setDisabled(1);
    Input.setReadOnly(1);
    Input.setPlaceholderText(tr("请移动光标选择块的开头，按 Enter 键确认"));
    SelectTriggered = true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if(Select2){
        if(event->key() == Qt::Key_Backspace){
            qDebug()<<"Block Deleted!";
            //Memory->BlockDelete(row1,col1,row2,col2);
        }else if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_C){
            qDebug()<<"Block Copied!";
            Selected = true;
            statusBar()->showMessage(tr("块复制成功！"));
        }
        Input.setReadOnly(0);
        Input.setPlaceholderText("typing...");
        Select2 = false;
        screen.LoadScreen(*Memory);
    }
    if(Input.text() == ""){
        screen.LoadScreen(*Memory);
        selectAction->setDisabled(0);
        switch (event->key()) {
        case Qt::Key_Up:
            qDebug()<<"Cursor Up!";
            Memory->MoveUp();
            screen.LoadScreen(*Memory);
            break;
        case Qt::Key_Down:
            qDebug()<<"Cursor Down!";
            Memory->MoveDown();
            screen.LoadScreen(*Memory);
            break;
        case Qt::Key_Left:
            qDebug()<<"Cursor Left!";
            Memory->MoveLeft();
            screen.LoadScreen(*Memory);
            break;
        case Qt::Key_Right:
            Memory->MoveRight();
            qDebug()<<"Cursor Right!";
            screen.LoadScreen(*Memory);
            break;
        case Qt::Key_Return:
            if(SelectTriggered){
                if(Select1){
                    qDebug()<<"End of Blcok Entered!";
                    Input.setPlaceholderText(tr("请完成对选中块的操作(删除、拷贝)"));
                    //row2 = Memory->GetCursorRow();
                    //col2 = Memory->GetCursorCol();
                    //调用块操作接口
                    SelectTriggered = false;
                    Select1 = false;
                    Select2 = true;
                    screen.LoadScreen(*Memory);
                    filepart->set_edited(true);
                    break;
                }else{
                    qDebug()<<"Start of Block Entered!";
                    Input.setPlaceholderText(tr("请移动光标选择块的结尾，按 Enter 键确认"));
                    Select1 = true;
                    //row1 = Memory->GetCursorRow();
                    //col1 = Memory->GetCursorCol();
                    screen.LoadScreen(*Memory);
                    break;
                }
            }
            qDebug()<<"Add blank line!";
            Memory->InsertString("");
            filepart->set_edited(true);
            screen.LoadScreen(*Memory);
            break;
        case Qt::Key_Backspace:
            qDebug()<<"Backspace!";
            Memory->Backspace();
            filepart->set_edited(true);
            screen.LoadScreen(*Memory);
            break;
        case Qt::Key_Delete:
            qDebug()<<"Delete!";
            Memory->Delete();
            filepart->set_edited(true);
            screen.LoadScreen(*Memory);
            break;
        //default:
            //break;
        }
    }else{
        selectAction->setDisabled(1);
        switch (event->key()) {
        case Qt::Key_Return:
            qDebug()<<"return success!";
            Memory->InsertString(Input.text());
            filepart->set_edited(true);
            selectAction->setDisabled(0);
            Input.clear();
            screen.LoadScreen(*Memory);
            break;
        //default:
            //break;
        }
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
    selectAction->setEnabled(1);
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
