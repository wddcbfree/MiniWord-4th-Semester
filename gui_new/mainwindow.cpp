#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle(tr("MiniWord"));
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //菜单栏
    createAction = new QAction(tr("New file"), this);
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
    connect(quitAction, &QAction::triggered, this, &MainWindow::close);

    searchAction = new QAction(tr("Search..."), this);
    searchAction->setShortcuts(QKeySequence::Find);
    searchAction->setStatusTip(tr("Search..."));
    connect(searchAction, &QAction::triggered, this, &MainWindow::search);

    replaceAction = new QAction(tr("Replace"), this);
    replaceAction->setShortcuts(QKeySequence::Replace);
    replaceAction->setStatusTip(tr("Replace"));
    connect(replaceAction, &QAction::triggered, this, &MainWindow::search);

    copyAction = new QAction("Block copy", this);
    connect(copyAction, &QAction::triggered, this, &MainWindow::block_copy);
    copyAction->setShortcut(tr("Ctrl+U"));
    copyAction->setDisabled(1);

    pasteAction = new QAction("Block paste", this);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::block_paste);
    pasteAction->setShortcut(tr("Ctrl+I"));
    pasteAction->setDisabled(1);

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

    //菜单栏初始化
    saveAction->setDisabled(1);
    saveasAction->setDisabled(1);

    //输入框部分
    Input.setParent(this);
    Input.setGeometry(INPUT_LEFT_BLANK, WINDOW_HEIGHT - 2 * LINE_HEIGHT, WINDOW_WIDTH - 2 * INPUT_LEFT_BLANK, LINE_HEIGHT);
    Input.show();
    Input.setEchoMode(QLineEdit::Normal);
    Input.setDisabled(1);
    Input.setPlaceholderText("Please open or creat a file");
    Input.setReadOnly(0);
    Input.setAcceptDrops(true);
    Input.setClearButtonEnabled(true);

    //状态栏
    statusBar();
    //工具栏

    //显示
    screen.InitiateScreen(this);
    QTimer *display_timer = new QTimer(this);
    connect(display_timer, SIGNAL(timeout()), this, SLOT(DisplayScreen()));
    display_timer->start(REFLASH_TIME);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!Selected) {
        if (event->key() == Qt::Key_Alt) {
            qDebug() << "SelectTriggered!";
            SelectTriggered = true;
            col_ = Memory->GetCursorCol();
            row_ = Memory->GetCursorRow();
            statusBar()->showMessage("Block choose mode");
            screen.LoadScreen(*Memory);
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (Selected) {
        switch (event->key()) {
        case Qt::Key_Backspace:
            filepart->set_edited(true);
            qDebug() << "Block Deleted! " << row_ << "," << col_ << "  " << Memory->GetCursorRow() << "," << Memory->GetCursorCol();
            int temp_col = Memory->GetCursorCol(), temp_row = Memory->GetCursorRow();
            Memory->BlockDelete(row_, col_, temp_row, temp_col);
            screen.CursorMode();
            break;
        }
        Selected = false;
        copyAction->setDisabled(1);
        pasteAction->setEnabled(1);

        screen.LoadScreen(*Memory);
        return;
    }
    else {
        if (SelectTriggered) {//开始块选择
            switch (event->key()) {
            case Qt::Key_Up:
                qDebug() << "Selected Cursor Up!";
                Memory->MoveUp();
                //高亮
                screen.HighlightMode(row_, col_, Memory->GetCursorRow(), Memory->GetCursorCol());
                screen.LoadScreen(*Memory);
                break;
            case Qt::Key_Down:
                qDebug() << "Selected Cursor Down!";
                Memory->MoveDown();
                //高亮
                screen.HighlightMode(row_, col_, Memory->GetCursorRow(), Memory->GetCursorCol());
                screen.LoadScreen(*Memory);
                break;
            case Qt::Key_Left:
                qDebug() << "Selected Cursor Left!";
                Memory->MoveLeft();
                //高亮
                screen.HighlightMode(row_, col_, Memory->GetCursorRow(), Memory->GetCursorCol());
                screen.LoadScreen(*Memory);
                break;
            case Qt::Key_Right:
                qDebug() << "Selected Cursor Right!";
                Memory->MoveRight();
                screen.HighlightMode(row_, col_, Memory->GetCursorRow(), Memory->GetCursorCol());
                screen.LoadScreen(*Memory);
                break;
            case Qt::Key_Alt://块选择结束
                qDebug() << "Block Selected!";
                screen.HighlightMode(row_, col_, Memory->GetCursorRow(), Memory->GetCursorCol());
                SelectTriggered = false;
                copyAction->setEnabled(1);
                Selected = true;
                break;
            default:
                qDebug() << "Cancel Block Select!";
                screen.CursorMode();
                SelectTriggered = false;
                //取消高亮
                break;
            }
        }
        else {
            if (Input.text() == "") {
                screen.LoadScreen(*Memory);
                switch (event->key()) {
                case Qt::Key_Up:
                    qDebug() << "Cursor Up!";
                    Memory->MoveUp();
                    screen.LoadScreen(*Memory);
                    break;
                case Qt::Key_Down:
                    qDebug() << "Cursor Down!";
                    Memory->MoveDown();
                    screen.LoadScreen(*Memory);
                    break;
                case Qt::Key_Left:
                    qDebug() << "Cursor Left!";
                    Memory->MoveLeft();
                    screen.LoadScreen(*Memory);
                    break;
                case Qt::Key_Right:
                    Memory->MoveRight();
                    qDebug() << "Cursor Right!";
                    screen.LoadScreen(*Memory);
                    break;
                case Qt::Key_Return:
                    qDebug() << "Add blank line!";
                    Memory->InsertString("");
                    filepart->set_edited(true);
                    screen.LoadScreen(*Memory);
                    break;
                case Qt::Key_Delete:
                    qDebug() << "Delete!";
                    Memory->Delete();
                    filepart->set_edited(true);
                    screen.LoadScreen(*Memory);
                    break;
                case Qt::Key_Backspace:
                    qDebug() << "Backspace!";
                    Memory->Backspace();
                    filepart->set_edited(true);
                    screen.LoadScreen(*Memory);
                    break;
                    //default:
                        //break;
                }
            }
            else {
                statusBar()->showMessage("Editing...");
                switch (event->key()) {
                case Qt::Key_Return:
                    qDebug() << "return success!";
                    Memory->InsertString(Input.text());
                    filepart->set_edited(true);
                    Input.clear();
                    statusBar()->showMessage("");
                    screen.LoadScreen(*Memory);
                    break;
                    //default:
                        //break;
                }
            }
        }
    }
}

void MainWindow::search() {
    QDialog SearchDialog(this);
    SearchDialog.setSizeIncrement(410, 4 * LINE_HEIGHT);
    SearchDialog.setWindowTitle("Search");
    SearchDialog.setModal(0);
    QLineEdit SearchInput(&SearchDialog), ReplaceInput(&SearchDialog);
    SearchInput.setGeometry(INPUT_LEFT_BLANK, LINE_GAP, 200 - 2 * INPUT_LEFT_BLANK, LINE_HEIGHT);
    SearchInput.setPlaceholderText("Enter what you're looking...");
    ReplaceInput.setGeometry(210 + INPUT_LEFT_BLANK, LINE_GAP, 200 - 2 * INPUT_LEFT_BLANK, LINE_HEIGHT);
    ReplaceInput.setPlaceholderText("Replace as...");
    QPushButton Search(&SearchDialog), SearchNext(&SearchDialog), Replace(&SearchDialog);
    Search.setGeometry(INPUT_LEFT_BLANK, 2 * LINE_GAP + LINE_HEIGHT, 200 - 2 * INPUT_LEFT_BLANK, LINE_HEIGHT);
    Search.setText("Search");
    Search.setStyleSheet("color:black");
    //connect(&SearchDialog,&Search)
    SearchNext.setGeometry(INPUT_LEFT_BLANK, 3 * LINE_GAP + 2 * LINE_HEIGHT, 200 - 2 * INPUT_LEFT_BLANK, LINE_HEIGHT);
    SearchNext.setText("Next");
    Replace.setGeometry(210 + INPUT_LEFT_BLANK, 2 * LINE_GAP + LINE_HEIGHT, 200 - 2 * INPUT_LEFT_BLANK, LINE_HEIGHT);
    Replace.setText("Replace");
    SearchDialog.exec();
}

void MainWindow::DisplayScreen() {
    screen.DisplayScreen();
}

MainWindow::~MainWindow() {

}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (filepart->is_create()) {
        QMessageBox msgBox;
        msgBox.setText(tr("There are unsaved changes, save?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save, "Save");
        msgBox.setButtonText(QMessageBox::Discard, "Discard");
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
            qDebug() << "Close dialogue!";
            break;
        }
    }
    else if (filepart->is_edited()) {
        QMessageBox msgBox;
        msgBox.setText(tr("There are unsaved changes, save?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save, "Save");
        msgBox.setButtonText(QMessageBox::Discard, "Discard");
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
            qDebug() << "Close dialogue!";
            break;
        }
    }
}

void MainWindow::create() {
    if (filepart->is_edited()) {
        QMessageBox msgBox;
        msgBox.setText(tr("There are unsaved changes, save?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save, "Save");
        msgBox.setButtonText(QMessageBox::Discard, "Discard");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            save();
            qDebug() << "Save!";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard!";
            break;
        }
    }
    emit SendCreateSignal();
    Input.setEnabled(1);
    Input.setFocus();
    Input.setPlaceholderText("typing...");
    saveAction->setEnabled(1);
    saveasAction->setEnabled(1);
    screen.LoadScreen(*Memory);
}

void MainWindow::open() {
    if (filepart->is_edited()) {
        QMessageBox msgBox;
        msgBox.setText(tr("There are unsaved changes, save?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
        msgBox.setButtonText(QMessageBox::Save, "Save");
        msgBox.setButtonText(QMessageBox::Discard, "Discard");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            save();
            qDebug() << "Save!";
            break;
        case QMessageBox::Discard:
            qDebug() << "Discard!";
            break;
        }
    }
    QString FilePath = QFileDialog::getOpenFileName(this, tr("Open..."));
    qDebug() << FilePath << endl;
    emit SendOpenPath(FilePath);
    Input.setEnabled(1);
    Input.setFocus();
    Input.setPlaceholderText("typing...");
    saveAction->setEnabled(1);
    saveasAction->setEnabled(1);
    screen.LoadScreen(*Memory);
    statusBar()->showMessage("Open sucess!");
}

void MainWindow::save() {
    if (filepart->is_open()) {
        QString FilePath;
        if (filepart->is_create()) {
            FilePath = QFileDialog::getSaveFileName(this, tr("Save..."), "新建文档.txt");
        }
        emit SendSavePath(FilePath);
        statusBar()->showMessage("Save sucess!");
    }
}

void MainWindow::save_as() {
    QString FilePath = QFileDialog::getSaveFileName(this, tr("Save as..."), "新建文档.txt");
    emit SendSaveAsPath(FilePath);
    statusBar()->showMessage("Save as sucess!");
}
