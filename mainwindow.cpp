#include "mainwindow.h"
#include "ui_mainwindow.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    ui->mainTab->hide();
    setAction();
    this->setDevTree();
    connect(ui->devTreeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(newMainForm(QTreeWidgetItem*,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAction()
{
    _mConnfig = new AtmpConfig();
    _mDevManger = new DevManger();
    _mSetConfigAction = new QAction("ATMP网络设置",this);
    _mDevMangerAction = new QAction("设备管理",this);
    connect(_mSetConfigAction,SIGNAL(triggered(bool)),this->_mConnfig,SLOT(show()));
    connect(_mDevMangerAction,SIGNAL(triggered(bool)),this->_mDevManger,SLOT(show()));

    _mSetMenu = this->menuBar()->addMenu("设置");
    _mSetMenu->addAction(_mSetConfigAction);
    _mSetMenu->addAction(_mDevMangerAction);
}

void MainWindow::setDevTree()
{
    //sDevListMap[AtmpHost,devIpList]
    QMap <QString,QStringList> sDevListMap;
    QFile file(sDevConfile);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        debuger(QString("打开文件[%1]失败").arg(sDevConfile));
        return ;
    }
    else
    {
        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString sLine = QString(line);
            QStringList sLineList = sLine.split(' ');
            if(sLineList.at(0) == "[DEV]")
            {
                //[DEV] DEV 10.8.202.151 DL00001
                //如果MAP中已经存在当前与当前AtmpHost相同的KEY值，在再该key值下的QStringList中添加devIP
                QString sKey = sLineList.at(1);
                QString sValue = sLineList.at(2);
                if(sDevListMap.contains(sKey))
                {
                    QStringList value = sDevListMap.take(sKey);
                    value.append(sValue);
                    sDevListMap.insert(sKey,value);
                }
                else
                {
                    sDevListMap.insert(sKey,QStringList(sValue));
                }
            }
        }
        QMapIterator<QString, QStringList> devMapIter(sDevListMap);

        int currentClass = 0;
        while (devMapIter.hasNext())
        {
            devMapIter.next();
            QStringList devList = devMapIter.value();
            QList <QTreeWidgetItem *> itemList;
            for(int index = 0;index < devList.size();index++)
            {
                QTreeWidgetItem *item = new QTreeWidgetItem();
                item->setText(0,devList.at(index));
                itemList.append(item);
            }
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0,devMapIter.key());
            item->addChildren(itemList);
            ui->devTreeWidget->addTopLevelItem(item);
            currentClass++;
        }
    }
}

void MainWindow::newMainForm(QTreeWidgetItem * item, int)
{
    QTreeWidgetItem *parent=item->parent();//获得父节点
    if(NULL==parent)
        return;
    QString devIp = item->text(0);
    if(ui->mainTab->isHidden())
    {
        ui->mainTab->show();
        ui->mainTab->clear();
        MainForm *form = new MainForm(devIp,this);
        ui->mainTab->addTab(form,devIp);
    }
    else
    {
        for(int i = 0; i < ui->mainTab->count(); i++)
        {
            if(ui->mainTab->tabText(i) == devIp)
            {
                ui->mainTab->setCurrentIndex(i);
                return;
            }
        }
        ui->mainTab->addTab(new MainForm(devIp,this),devIp);
        ui->mainTab->setCurrentIndex(ui->mainTab->count()-1);
    }
}
