#ifndef MAINFORM_H
#define MAINFORM_H

//#if _MSC_VER >= 1600
//#pragma execution_character_set("utf-8")
//#endif

//#pragma execution_character_set("utf-8")
#pragma execution_character_set("GBK")

#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QTextCodec>
#include <Qtimer>
#include <QtFtp/QFtp>
#include <QDir>
#include <QDateTime>
#include <QCompleter>
#include <QStringListModel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDomDocument>
#include "ftpdownloard.h"
#include "global.h"


namespace Ui {
class MainForm;
}
typedef struct sTranInfo
{
    QString sCpSeqNo;
    QString sEpSeqNo;
    QString sTrnCode;
    QString sStartTime;
}sTranInfo;

class MainForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    //explicit MainForm(QString devIp,QWidget *parent = 0);
    MainForm(QString devIp,bool showSecuMQ,bool showSwitchMQ,QWidget *parent = 0);
    ~MainForm();
private:
    Ui::MainForm *ui;
    QString _mDevIp;
    QString _mLogName;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QStringListModel *_mEpSeqStringListModel;
    QStringList _mEpSeqNoList;
    QCompleter *_mEpSeqEditCompleter;
    QVector <sTranInfo> _mTranInfoVector;
    bool _mShowSecuMq;
    bool _mShowSwitchMq;

    //FTP新增对象
    QFtp *ftp;
    //下载日志文件
    int downloadLogFile();
    //根据CP流水号获取流水日志文件
    int getfileByCpSeq(const QString &sCpSeq);
    //根据EP流水号获取流水日志文件
    int getfileByEpSeq(const QString &sEpSeq);
    //将日志文件按照ESB流水分解成独立的流水文件。并且按照EP流水+CP流水的方式命名。
    int departLog();
    //分析流水文件，并将交易报文，交易流水，交易结果映射到TableWidget中。
    int analysisSeqLog();
    //分析获取到的交易报文，并映射到[tableWidget]中
    int analysisMessage(QString sMsg,QString sSrcMQ,QString sDestMQ);

private slots:
    void on_updateBtn_clicked();
    void on_anaBtn_clicked();

    void slotError(QNetworkReply::NetworkError code);
    void replyFinished(QNetworkReply *reply);

    //FTP新增SLOT
    void ftpCommandStarted(int);
    void ftpCommandFinished(int,bool);
    //
    void onChangeShowType(bool showSecuMQ,bool showSwitchMq);
};

#endif // MAINFORM_H
