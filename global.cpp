#include "global.h"

//东莞农商银行配置文件位置
extern const QString sDevConfile = "D:\\nantian\\Project\\LogAna\\Res\\dev.ini";
extern const QString sAtmpConfile = "D:\\nantian\\Project\\LogAna\\Res\\atmp.ini";
extern const QString gSeqLogDir =  "D:\\nantian\\Project\\LogAna\\SeqLog\\"; //用来保存处理后设备流水日志
extern const QString gDownLoadDir = "D:\\nantian\\Project\\LogAna\\DownLoad\\"; //日志下载后会把保存在这个文件夹里。
//本机开发环境配置文件位置
//extern const QString sDevConfile =  "G:\\SystemFile\\Documents\\GitHub\\LogAna\\Res\\dev.ini";
//extern const QString sAtmpConfile = "G:\\SystemFile\\Documents\\GitHub\\LogAna\\Res\\atmp.ini";
//extern const QString gLogFiledir =  "G:\\SystemFile\\Documents\\GitHub\\LogAna\\tmp\\";

QString MsgDeal1(QString message)
{
    QString tmp;
    tmp.clear();
    tmp.append(message);
    if(tmp.length() < 50)
    {
        tmp = tmp.leftJustified(50,'_');
    }
    return tmp;
}

QString MsgDeal2(QString M1,QString M2)
{
    QString tmp;
    tmp.clear();
    tmp.append(M1);
    tmp.append(": ");
    tmp.append(M2);
    if(tmp.length() < 93)
    {
        tmp = tmp.leftJustified(93,'_');
    }
    return tmp;
}
