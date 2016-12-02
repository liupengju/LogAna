#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QMainWindow>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QTreeWidgetItem>
#include "atmpconfig.h"
#include "mainform.h"
#include "devmanger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setDevTree();

private slots:
    void newMainForm(QTreeWidgetItem*,int);

private:
    Ui::MainWindow *ui;
    QAction *_mSetConfigAction;
    QAction *_mDevMangerAction;
    QMenu *_mSetMenu;
    AtmpConfig *_mConnfig;
    DevManger *_mDevManger;

    void setAction();
};

#endif // MAINWINDOW_H
