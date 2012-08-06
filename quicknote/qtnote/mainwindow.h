#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "globalhotkey.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void showEvent(QShowEvent *event);
    static Ui::MainWindow *sui;

private slots:
	void Press1();
	void HotKeyPressedSlot(uint keyId, uint modifiers);
    
private:
    Ui::MainWindow *ui;
	GlobalHotKey globalHotKey;
};

#endif // MAINWINDOW_H
