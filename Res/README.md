============================================================================================================================
[刷新]:如果日志输入框中的日志文件名称为空，则下载所有日志，否则，日志输入框中的日志文件
============================================================================================================================
[分析]：
     :日志文件编码格式识别
     :
============================================================================================================================
[显示]:
     现在的主窗口改成QWidget。用QTabWidget封装，双击QTabWidget可以新建，QTabWidget名称为[设备名称+ATMP服务
     器名称]
============================================================================================================================
[ATMP]
     :libesbsys30.c [esb_Debughex]函数中的[PrintLogConv，toDebitMsgOut_shielded]函数会屏蔽敏感信息，添加日志等级判断，修改为只在生产
     :PrintLogConv函数添加：
     :// [修改]add by lpj 20161129
     :// [说明] 为了调试交易方便，在开发环境中[loglevel = debug]取消敏感字段屏蔽
     :if(igLogLevel>1) //1=ESB_DEBUG
     :  return 0;
     :// add end
============================================================================================================================
[流水日志文件]：
     :流水日志文件需要保存[接出渠道号][批次号] 如果是跟后端的日志还需要保存[后台服务代码]
============================================================================================================================
[20161201]
     :修改[MainFrom.cpp(departLog)函数],采用GB18030的编码解析文本。
     :添加设计,在日志路径下创建[设备IP]文件夹,各个流水日志文件保存在对应的[设备IP]文件夹下边。
============================================================================================================================