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
signals:
    void showTypeChanged(bool showSecuMQ,bool showSwitchMQ);

private slots:
    void onNewMainForm(QTreeWidgetItem*,int);
    void onShowTypeChanged();
    void on_mainTab_tabBarDoubleClicked(int index);

private:
    Ui::MainWindow *ui;
    QAction *_mSetConfigAction;
    QAction *_mDevMangerAction;
    QAction *_mShowSecuMQ;
    QAction *_mShowSwitchMQ;
    QMenu *_mSetMenu;
    AtmpConfig *_mConnfig;
    DevManger *_mDevManger;

    void setAction();
};

#endif // MAINWINDOW_H
