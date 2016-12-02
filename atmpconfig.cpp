#include "atmpconfig.h"
#include "ui_atmpconfig.h"

AtmpConfig::AtmpConfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AtmpConfig)
{
    ui->setupUi(this);
}

AtmpConfig::~AtmpConfig()
{
    delete ui;
}

void AtmpConfig::on_ftpQuitBtn_clicked()
{
    this->close();
}

bool AtmpConfig::addFtpConfig()
{
    QFile file(sAtmpConfile);
    if (!file.open(QFile::Append | QFile::Text))
    {
        qDebug()<<QString("打开配置文件出错.");
        file.close();
        return false;
    }
    QString sConfig = "\n[ATMP] "
                      + ui->ftpNameEdit->text() + " "
                      + ui->ftpIpEdit->text() + " "
                      + ui->ftpUserEdit->text() + " "
                      + ui->ftpPswdEdit->text();
    QTextStream out(&file);
    out << sConfig;
    file.close();
    return true;
}

void AtmpConfig::on_addFtpBtn_clicked()
{
    if(ui->ftpNameEdit->text().isEmpty() ||
       ui->ftpIpEdit->text().isEmpty() ||
       ui->ftpUserEdit->text().isEmpty() ||
       ui->ftpPswdEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","请填写所有选项",QMessageBox::Yes,QMessageBox::Yes);
        return ;
    }
    if(addFtpConfig())
    {
        if(QMessageBox::Yes ==  QMessageBox::question(
                    this,"添加结果",QString("成功添加[%1]信息\n继续添加?").arg(ui->ftpNameEdit->text()),
                    QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes))
        {
            return ;
        }
        else
        {
            this->close();
        }
    }
    else
    {
        if(QMessageBox::Yes ==  QMessageBox::critical(
                    this,"添加结果",QString("添加[%1]信息失败\n继续添加?").arg(ui->ftpNameEdit->text()),
                    QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes))
        {
            return ;
        }
        else
        {
            this->close();
        }
    }
};
