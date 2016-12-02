#ifndef DEVMANGER_H
#define DEVMANGER_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include <QCompleter>
#include "global.h"

namespace Ui {
class DevManger;
}

class DevManger : public QWidget
{
    Q_OBJECT

public:
    explicit DevManger(QWidget *parent = 0);
    ~DevManger();
    int addDev();
    QStringList getAtmpConfig() const;

private slots:

    void on_exitBtn_clicked();
    void on_addDevBtn_clicked();

private:
    Ui::DevManger *ui;
};

#endif // DEVMANGER_H
