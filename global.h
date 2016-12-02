#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>

extern const QString sAtmpConfile;
extern const QString sDevConfile;
extern const QString gSeqLogDir;
extern const QString gDownLoadDir;

#define debuger(message) (qDebug()<<"[Debug]"<<MsgDeal1(message)<<"[ 文件："<<__FILE__<<':'<<__LINE__<<" ]")
#define debuger2(M1,M2) (qDebug()<<"[Debug]"<<MsgDeal2(M1,M2)<<"[ 文件："<<__FILE__<<':'<<__LINE__<<" ]")
#define SUCCESS 0;
#define FAILED -1;

QString MsgDeal1(QString message);
QString MsgDeal2(QString M1,QString M2);


#endif // GLOBAL_H


