#ifndef CONFIG_H
#define CONFIG_H

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include "global.h"

namespace Ui {
class AtmpConfig;
}

class AtmpConfig : public QWidget
{
    Q_OBJECT

public:
    explicit AtmpConfig(QWidget *parent = 0);
    ~AtmpConfig();
    bool addFtpConfig();

private slots:
    void on_ftpQuitBtn_clicked();
    void on_addFtpBtn_clicked();

private:
    Ui::AtmpConfig *ui;
};

#endif // CONFIG_H
