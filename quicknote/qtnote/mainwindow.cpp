#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sstream>
#include "globalhotkey.h"

Ui::MainWindow *MainWindow::sui = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    globalHotKey()
{
    ui->setupUi(this);
    sui = ui;

    connect(ui->button1, SIGNAL(clicked()), this, SLOT(Press1()));

    // Register Hotkeys
    if (globalHotKey.Register(this->winId())) {
    	ui->textEditLog->appendPlainText("Registered Hotkeys");
    } else {
    	ui->textEditLog->appendPlainText("Error registering Hotkeys");
    }
    connect(&globalHotKey, SIGNAL(HotKeyPressed(uint, uint)),
        this, SLOT(HotKeyPressedSlot(uint, uint)));

    std::stringstream handleString;
    handleString << "Window Handle: " << this->winId();
    ui->textEditLog->appendPlainText(handleString.str().c_str());

}

MainWindow::~MainWindow() {
    delete ui;
}

// override QWidgets showEvent
void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    ui->lineEdit->setFocus();
}

void MainWindow::Press1() {
    ui->textEditLog->appendPlainText("Added: " + ui->lineEdit->text());
    ui->lineEdit->setText("");
    ui->lineEdit->setFocus();
}

void MainWindow::HotKeyPressedSlot(uint keyId, uint modifiers) {
    std::stringstream s;
    s << "Received WM_HOTKEY. key:" << keyId << " modifiers: " << modifiers;
    ui->textEditLog->appendPlainText(s.str().c_str());
    
    // Activate window
    show();
    activateWindow();
    raise();
}