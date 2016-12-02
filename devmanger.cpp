#include "devmanger.h"
#include "ui_devmanger.h"

DevManger::DevManger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevManger)
{
    ui->setupUi(this);
    ui->hostComboBox->addItems(getAtmpConfig());
}

DevManger::~DevManger()
{
    delete ui;
}

QStringList DevManger::getAtmpConfig() const
{
    QStringList sAtmpHostList;
    QFile file(sAtmpConfile);
    if(!file.open(QFile::ReadOnly |QFile::Text))
    {
        qDebug()<<"打开文件atmp配置文件出错";
        file.close();
        return QStringList("");
    }
    else
    {
        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString sLine(line);
            qDebug()<<sLine;
            QStringList sAtmpHost = sLine.split(' ');
            qDebug()<<sAtmpHost;
            if(sAtmpHost.at(0) == "[ATMP]")
            {
                sAtmpHostList.append(sAtmpHost.at(1));
            }

        }
        file.close();
        return sAtmpHostList;
    }
}

void DevManger::on_exitBtn_clicked()
{
    this->close();
}

int DevManger::addDev()
{
    QFile file(sDevConfile);
    if (!file.open(QFile::Append | QFile::Text))
    {
        qDebug()<<QString("打开配置文件出错.");
        file.close();
        return false;
    }
    QString sConfig = "\n[DEV] "
                      + ui->hostComboBox->currentText() + " "
                      + ui->devIpEdit->text() + " "
                      + ui->devNoEdit->text();
    QTextStream out(&file);
    out << sConfig;
    file.close();
    return true;
}


void DevManger::on_addDevBtn_clicked()
{
    if(ui->devNoEdit->text().isEmpty() ||
       ui->devNoEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"错误","请填写所有选项",QMessageBox::Yes,QMessageBox::Yes);
        return ;
    }
    if(addDev())
    {
        if(QMessageBox::Yes ==  QMessageBox::question(
                    this,"添加结果",QString("成功添加[%1]信息\n继续添加?").arg(ui->devIpEdit->text()),
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
                    this,"添加结果",QString("添加[%1]信息失败\n继续添加?").arg(ui->devIpEdit->text()),
                    QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes))
        {
            return ;
        }
        else
        {
            this->close();
        }
    }
}
