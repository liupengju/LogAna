#include "mainform.h"
#include "ui_mainform.h"

MainForm::MainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::MainForm(QString devIp,QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);
    _mEpSeqEditCompleter = new QCompleter(this);
    _mEpSeqStringListModel = new QStringListModel(this);
    this->_mDevIp = devIp;
    this->_mLogName = gDownLoadDir + devIp.replace('.','_');
    //实例化FTP对象
    ftp  = new QFtp(this);
    connect(ftp,SIGNAL(commandStarted(int)),this,SLOT(ftpCommandStarted(int)));
    connect(ftp,SIGNAL(commandFinished(int,bool)),this,SLOT(ftpCommandFinished(int,bool)));
    debuger(this->_mLogName);
}

MainForm::~MainForm()
{
    delete ui;
}

int MainForm::downloadLogFile()
{
    qDebug()<<"开始下载日志文件["<<_mLogName<<"]";
    return 0;
}

int MainForm::getfileByCpSeq(const QString &sCpSeq)
{
    //获取EP流水
    QString sEpSeq;
    //分析EP流水文件
    this->getfileByEpSeq(sEpSeq);

    return 0;
}

int MainForm::analysisSeqLog()
{

}

int MainForm::getfileByEpSeq(const QString &sEpSeq)
{
    //要使用的正则表达式
    const QString PATTERN_STRING = "a.*a";
    //QRegExp::cap的参数
    const int NTH = 0;
    QTextStream cout(stdout);

    //输入文件：存储要查找的文本
    QFile inputFile("input.txt");
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);
    //输出文件：存储查找结果
    QFile outputFile("output.txt");
    outputFile.open(QIODevice::WriteOnly);
    QTextStream out(&outputFile);

    QString txtStr = in.readAll();
    //如果要区分大小写，就把下面这句话删掉
    txtStr.toLower();

    QRegExp regExp;
    int pos, result;
    pos = result = 0;
    regExp.setPattern(PATTERN_STRING);
    //将匹配设置为最小（短）匹配
    regExp.setMinimal(true);

    //开始匹配
    while ((pos = regExp.indexIn(txtStr, pos)) != -1)
    {
        QString str = regExp.cap(NTH);
        out << str << endl;
        pos += regExp.matchedLength();
        result++;
    }

    cout << result << " results" << endl;
    inputFile.close();
    outputFile.close();
    return 0;
}

void MainForm::slotError(QNetworkReply::NetworkError code)
{
    debuger(reply->errorString());
}

void MainForm::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QString all = codec->toUnicode(reply->readAll());
    debuger(QString("收到的数据[%1]").arg(all));
    reply->deleteLater();
}

void MainForm::ftpCommandStarted(int)
{
    if(ftp->currentCommand()==QFtp::ConnectToHost)
    {
        debuger("正在连接到服务器...");
    }
    else if(ftp->currentCommand()==QFtp::Login)
    {
        debuger("正在登陆...");
    }
    else if(ftp->currentCommand()==QFtp::Get)
    {
        debuger("正在下载...");
    }
    else if (ftp->currentCommand() == QFtp::Close)
    {
        debuger("正在关闭连接...");
    }
}

void MainForm::ftpCommandFinished(int, bool)
{
    if(ftp->currentCommand() == QFtp::ConnectToHost)
    {
        if(errno)
            debuger(QString("连接服务器错误[%1]").arg(ftp->errorString()));
        else
            debuger(QString("连接服务器成功"));
    }
    if(ftp->currentCommand() == QFtp::Login)
    {
        if(errno)
            debuger(QString("登录服务器失败[%1]").arg(ftp->errorString()));
        else
            debuger("登录服务器成功");
    }
    if(ftp->currentCommand()==QFtp::Get)
    {
        if(errno)
            debuger(QString("下载日志文件失败[%1]").arg(ftp->errorString()));
        else
            debuger("下载日志文件成功");
    }
    if(ftp->currentCommand()==QFtp::Close)
    {
        if(errno)
            debuger(QString("关闭FTP连接失败[%1]").arg(ftp->errorString()));
        else
            debuger("已成功关闭Ftp连接");
    }

}

void MainForm::on_updateBtn_clicked()
{
    //下载日志文件
    debuger("enter into LogDownLoard");
    //下载日志，方式1：
    {
        //    QNetworkAccessManager *nam = new QNetworkAccessManager();
        //    QUrl url2("ftp://10.8.6.33/log/debug/err.debug");
        //    url2.setUserName("tsp30cz");
        //    url2.setPassword("123456");
        //    url2.setPort(21);
        //    QNetworkRequest req(url2);
        //    QNetworkReply *reply = nam->get(req);
        //    QByteArray data = reply->readAll();
        //    QString sData = QString(data);
        //下载日志，方式2：
        //在该方式的实现时,新增了两个成员变量manager和reply
        //    QUrl url;
        //    url.setScheme("ftp");
        //    debuger(QString("URL: %1").arg(url.errorString()));
        //    url.setHost("10.8.6.33");
        //    debuger(QString("URL: %1").arg(url.errorString()));
        //    url.setPath("/err.txt");
        //    debuger(QString("URL: %1").arg(url.errorString()));
        //    url.setPort(21);
        //    debuger(QString("URL: %1").arg(url.errorString()));
        //    url.setUserName("tsp30cz");
        //    debuger(QString("URL: %1").arg(url.errorString()));
        //    url.setPassword("123456");
        //    debuger(QString("URL: %1").arg(url.errorString()));
        //    QNetworkRequest request;
        //    request.setUrl(url);
        //    manager = new QNetworkAccessManager;
        //    reply = manager->get(request);
        //    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(slotError(QNetworkReply::NetworkError)));
        //    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply*)));
        //下载日志
        //使用编译的QFtp类来实现日志下载
        //    ftp->connectToHost("10.8.6.33");
        //    ftp->login("tsp30cz","123456");
        //    ftp->cd("log/debug");
        //    ftp->get("lpjerrdebug.txt");
        //    ftp->close();
    }

    //分解日志文件
    //QtFtp下载日志是异步的，所以需要在QFtp发出[ftpCommandFinished(close)]信号之后才进行日志处理
    departLog();
    //更新cpSeqEdit,epSeqEdit的QCompleter;
    if(!ui->cpSeqNoEdit->text().isEmpty())
    {
        int ret = getfileByCpSeq(ui->cpSeqNoEdit->text());
        if(!ret)
            qDebug()<<"获取日志流水文件失败";
    }
    else
    {
        if(!ui->epSeqNoEdit->text().isEmpty())
        {
            int ret = this->getfileByEpSeq(ui->epSeqNoEdit->text());
            if(!ret)
                qDebug()<<"获取流水日志文件失败";
        }
    }

}

int MainForm::departLog()
{
    debuger("Enter Into departLog");
    QFile file(_mLogName);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        debuger(QString("打开日志文件[%1]出错\n").arg(_mLogName));
        QString sErrString = QString("打开日志文件出错\n[%1]\n\n").arg(_mLogName) + file.errorString();
        QMessageBox::critical(this,"打开文件失败",sErrString,QMessageBox::Yes,QMessageBox::Yes);
        file.close();
        return FAILED;
    }
    QString sDate = QDateTime::currentDateTime().date().toString("yyyyMMdd");
    QString sSeqLogPath = gSeqLogDir+this->_mDevIp+"\\"+sDate;
    QDir seqLogDir(sSeqLogPath);
    if (!seqLogDir.exists())
    {
        debuger(QString("文件路径[%1]不存在").arg(sSeqLogPath));
        seqLogDir.mkpath(sSeqLogPath);
    }
    debuger(QString("打开文件[%1]成功").arg(_mLogName));
    //日志文件编码格式测试

    //test end.......

    //按照日志开始，结束标志来分解日志
    //需要处理日志文件编码格式
    //日志开始[接收到设备]
    //日志结束[交易正常结束]
    int i = 0;
    int sSeqNum = 0;
    debuger("开始读取日志文件...");
    //QTextCodec *codec = QTextCodec::codecForName("GB18030");
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    //添加该标志位用来标示当前正在获取该流水日志中。在读到[接受到设备]时记录流水日志信息[开始时间，EP流水],并将该位设置为true，标示
    //已经成功获取流水起始位置;在读到[交易正常结束]时记录日志信息[交易结束时间],并将该标志位设置为false，标示该笔流水日志已经获取成
    //功，可以开始进行下边流水交易的获取。
    bool isEpSeqGot = false;
    bool isNotSeqLogFileCreated = true;
    bool isCpSeqNoGot = false;
    bool isTrnCodeGot = false;
    sTranInfo tranInfo;
    QTextStream seqFileStream;
    QString sEpSeq;
    QString sStartTime;
    QFile seqFile;
    while(!file.atEnd())
    {
        QByteArray line =  file.readLine();
        //QString sLine(line);
        QString  sLine = codec->toUnicode(line);
        //如果获取到了流水，并且流水文件还没有创建,就创建流水文件
        if(isEpSeqGot && isNotSeqLogFileCreated)
        {
            seqFile.setFileName( gSeqLogDir + _mDevIp+ "\\" + sDate +"\\" + sEpSeq );
            _mEpSeqNoList.append(sEpSeq);
            seqFileStream.setDevice(&seqFile);
            if(!seqFile.open(QFile::WriteOnly|QFile::Text))
            {
                QMessageBox::critical(this,"创建流水文件失败",QString("创建流水日志文件失败\n%1\n%2").arg(sEpSeq)
                                      .arg(seqFile.errorString()),QMessageBox::Yes,QMessageBox::Yes);
            }
            else
            {
                isNotSeqLogFileCreated = false;
            }
        }
        //流水日志开始
        if(!isEpSeqGot)
        {
            if(sLine.contains(QString("接收到设备")))
            {
                //debuger(QString("+++++%1").arg(sLine));
                //seqFileStream<<sLine;
                sSeqNum++;
                sEpSeq = sLine.mid(1,9);                //esb-->p流水;
                sStartTime = sLine.mid(12,21);          //交易起始时间
                tranInfo.sStartTime = sStartTime;
                tranInfo.sEpSeqNo = sEpSeq;
                isEpSeqGot = true;
            }
        }
        else
        {
            //流水日志结束
            //qDebug()<<"isCpSeqNoGot"<<isCpSeqNoGot;
            if(!isTrnCodeGot)
            {
                if(sLine.contains(QString("算出交易码为")))
                {
                    QString sTrnCode = sLine.mid(54,6);
                    debuger(QString("====CP交易码[%1]").arg(sTrnCode));
                    isTrnCodeGot = true;
                }
                tranInfo.sTrnCode = sLine.mid(54,6);

            }
            seqFileStream << sLine;
            if(sLine.contains(QString("交易正常结束")))
            {
                //debuger(QString("====%1").arg(sLine));
                QString sEndTime = sLine.mid(12,21);
                isEpSeqGot = false;
                isTrnCodeGot = false;
                seqFile.close();
                isNotSeqLogFileCreated = true;
            }
        }
        i++;
    }
    debuger(QString("读取文件结束,总共读取[%1]行 [%2]条流水").arg(i).arg(sSeqNum));
    _mEpSeqStringListModel->setStringList(_mEpSeqNoList);
    this->_mEpSeqEditCompleter->setModel(_mEpSeqStringListModel);
    this->ui->epSeqNoEdit->setCompleter(_mEpSeqEditCompleter);
    qDebug()<<"_mEpSeqNoList:\n"<<_mEpSeqNoList;
    return 0;
}

int MainForm::analysisMessage(QString sMsg,QString sSrcMQ,QString sDestMQ)
{
    //处理xml报文,将xml报文中的'.'转换成空格
    sMsg.replace('.',' ');
    debuger(QString("======sMsg[%1]").arg(sMsg));
    //映射xml报文到QTableWidget中
    QDomDocument doc;
    doc.setContent(sMsg);
    QDomElement root = doc.documentElement();
    int index = 1;
    QString tagName;

    //处理200的xml报文
    if(sSrcMQ == "200" || sDestMQ == "200")
    {
        QTableWidget *tabWidget =  new QTableWidget(this);
        QStringList headList;
        headList<<"节点"<<"数据";
        //tabWidget->setRowCount(100);
        tabWidget->setColumnCount(2);
        tabWidget->setHorizontalHeaderLabels(headList);
        for(int i = 0;i<root.childNodes().count();i++)
        {
            QString sName = root.childNodes().at(i).toElement().tagName();
            QString sText = root.childNodes().at(i).toElement().text();
            tabWidget->insertRow(i);
            tabWidget->setItem(i,0,new QTableWidgetItem(sName));
            tabWidget->setItem(i,1,new QTableWidgetItem(sText));
            //debuger(QString("Name[%1]---->Text[%2]").arg(sName).arg(sText));
        }
        this->ui->msgTabWidget->addTab(tabWidget,QString("%1-->%2").arg(sSrcMQ).arg(sDestMQ));
    }
    //处理410的xml报文
    if(sSrcMQ == "410" || sDestMQ == "410")
    {
        QTableWidget *tabWidget =  new QTableWidget(this);
        QStringList headList;
        //节点用'/'组织，类型为"String(length)","Double(20,2)"...
        headList<<"节点"<<"类型"<<"数据";
        //tabWidget->setRowCount(100);
        tabWidget->setColumnCount(3);
        tabWidget->setHorizontalHeaderLabels(headList);
        QDomElement cursorElement;
        for(int i = 0;i<root.childNodes().count();i++)
        {
            QString sName = root.tagName() + '/';
            cursorElement = root.childNodes().at(i).toElement();
            sName = sName + cursorElement.tagName() + "/";
            while(cursorElement.hasChildNodes())
            {

            }

            QString sName = root.childNodes().at(i).toElement().tagName();
            QString sText = root.childNodes().at(i).toElement().text();
            tabWidget->insertRow(i);
            tabWidget->setItem(i,0,new QTableWidgetItem(sName));
            tabWidget->setItem(i,1,new QTableWidgetItem(sText));
            //debuger(QString("Name[%1]---->Text[%2]").arg(sName).arg(sText));
        }
        this->ui->msgTabWidget->addTab(tabWidget,QString("%1-->%2").arg(sSrcMQ).arg(sDestMQ));
    }
    return 0;
}

void MainForm::on_anaBtn_clicked()
{
    //清楚msgTable
    this->ui->msgTabWidget->clear();
    //获取文件名称
    QString sDate = QDateTime::currentDateTime().date().toString("yyyyMMdd");
    QString sFileName = gSeqLogDir + _mDevIp+ "\\" + sDate +"\\" +ui->epSeqNoEdit->text();
    //打开并分析文件
    QFile file(sFileName);
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        debuger("打开日志文件失败");
        return;
    }
    bool isMsgStartGot = false;
    bool isMQGot = false;
    QString sMsg;
    QString sSrcMQ;
    QString sDestMQ;
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString sLine = codec->toUnicode(line);
        if(!isMQGot)
        {
            if(sLine.contains(QString("iSrcMQ")))
                sSrcMQ = sLine.mid(48,3);
            if(sLine.contains(QString("iDestMQ")))
            {
                sDestMQ = sLine.mid(48,3);
                isMQGot = true;
            }
        }
        else
        {
            if(!isMsgStartGot)
            {
                if(sLine.contains(QString("--- 报文(开始) ---")))
                {
                    isMsgStartGot = true;
                    sMsg.clear();
                }
            }
            else
            {
                if(sLine.contains(QString("~~~ 报文(结束) ~~~")))
                {
                    isMsgStartGot = false;
                    isMQGot = false;
                    //交易报文分析
                    debuger(QString("%1-->%2").arg(sSrcMQ).arg(sDestMQ));
                    debuger(QString("==sMsg\n[%1]").arg(sMsg));
                    analysisMessage(sMsg,sSrcMQ,sDestMQ);
                }
                else
                {
                    sMsg.append(sLine.mid(46,64));
                }
            }
        }
    }
}
