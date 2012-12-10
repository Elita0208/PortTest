#include "mainwindow.h"
#include <QTimer>
#include <QSettings>
#include <QMessageBox>

mainwindow::mainwindow()
: QMainWindow()
{
	setupUi(this);
	init_com();
	readconfig();
}

//����com����Ϣ
void mainwindow::init_com()
{
	QString path="HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM";
	QSettings *settings=new QSettings(path,QSettings::NativeFormat);
	QStringList key=settings->allKeys();
	QStringList comlist ;
	QStringList Baudlist ;
	QStringList Paritylist ;
	QStringList DataBitslist;
	QStringList StopBitslist;
	QStringList ControlFlowlist;

	int kk = key.size();
	int i;
	comlist.clear();
	for(i=0;i<kk;i++)
	{
		comlist << getcomm(i,"value");
	}
	comboBox->addItems(comlist);
	//������
	Baudlist.clear();
	Baudlist<< "300" << "600" << "2400" << "4800" << "9600"<< "19200" << 
			 "56000" << "57600" << "115200"<<"128000"<<"256000"<< "921600";
	baudRateComboBox->addItems(Baudlist);

	//У��λ
	Paritylist.clear();
	Paritylist<<  QString::fromLocal8Bit("NONE") <<  QString::fromLocal8Bit("ODD") << QString::fromLocal8Bit( "EVEN");
	parityComboBox->addItems(Paritylist);

	//����λ
	DataBitslist.clear();
	DataBitslist<< "8" << "7" << "6"<<"5";
	dataBitsComboBox->addItems(DataBitslist);

	//ֹͣλ
	StopBitslist.clear();
	StopBitslist<< "1" << "2";
	stopBitsComboBox->addItems(StopBitslist);

	//����λ
	ControlFlowlist.clear();
	ControlFlowlist<< QString::fromLocal8Bit("NONE") << "XON/XOFF" << QString::fromLocal8Bit("HARDWARE");
	controlComboBox->addItems(ControlFlowlist);	
}

//��ע���
QString mainwindow::getcomm(int index,QString keyorvalue)
{
	QString commresult="";
	QString strkey="HARDWARE\\DEVICEMAP\\SERIALCOMM";//�Ӽ�·��
	int a=strkey.toWCharArray(subkey);//����ת��
	subkey[a]=L'\0';
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,subkey,0,KEY_READ|KEY_QUERY_VALUE,&hKey)!=0)
	{
		QString error="Cannot open regedit!";//�޷���ע���ʱ����error
	}

	QString keymessage="";//����
	QString message="";
	QString valuemessage="";//��ֵ
	indexnum=index;//Ҫ��ȡ��ֵ��������

	keysize=sizeof(keyname);
	valuesize=sizeof(keyvalue);

	if(::RegEnumValue(hKey,indexnum,keyname,&keysize,0,&type,(BYTE*)keyvalue,&valuesize)==0)//�оټ�����ֵ
	{
		//��ȡ����
		for(int i=0;i<keysize;i++)
		{
			message=QString::fromStdWString(keyname);
			keymessage.append(message);
		}
		//��ȡ��ֵ
		for(int j=0;j<valuesize;j++)
		{
			if(keyvalue[j]!=0x00)
			{
				valuemessage.append(keyvalue[j]);
			}
		}

		if(keyorvalue=="key")
		{
			commresult=keymessage;
		}
		if(keyorvalue=="value")
		{
			commresult=valuemessage;
		}
	}
	else
	{
		commresult="nokey";
	}
	::RegCloseKey(hKey);//�ر�ע���
	return commresult;
}

//�򿪲����ô���
void mainwindow::on_openBtn_clicked()
{
	myCom = new Win_QextSerialPort(port_name,QextSerialBase::EventDriven);//���崮�ڶ��󣬲����ݲ������ڹ��캯���������г�ʼ��

	//�򿪴���
	port_name = comboBox->currentText(); //��ȡ������
	
	QString m_port = port_name.right(port_name.length()-3);
	if(m_port.toInt()>9)
	{
		QString xx = "\\\\.\\";
		xx.append(port_name);
		myCom->setPortName(xx);
	}
	else
	{
		myCom->setPortName(port_name);
	}
	if(myCom->open(QIODevice::ReadWrite))
	{
		QMessageBox::information(this, tr("���ڼ�� "), tr("�ѳɹ���") + port_name, QMessageBox::Ok);
	
		
		//������
		if(baudRateComboBox->currentText()==tr("300"))
			myCom->setBaudRate(BAUD300);
		else if(baudRateComboBox->currentText()==tr("600"))
			myCom->setBaudRate(BAUD600);
		else if(baudRateComboBox->currentText()==tr("2400"))
			myCom->setBaudRate(BAUD2400);
		else if(baudRateComboBox->currentText()==tr("4800"))
			myCom->setBaudRate(BAUD4800);
		else if(baudRateComboBox->currentText()==tr("9600"))
			myCom->setBaudRate(BAUD9600);
		else if(baudRateComboBox->currentText()==tr("19200"))
			myCom->setBaudRate(BAUD19200);
		else if(baudRateComboBox->currentText()==tr("56000"))
			myCom->setBaudRate(BAUD56000);
		else if(baudRateComboBox->currentText()==tr("57600"))
			myCom->setBaudRate(BAUD57600);
		else if(baudRateComboBox->currentText()==tr("115200"))
			myCom->setBaudRate(BAUD115200);
		else if(baudRateComboBox->currentText()==tr("128000"))
			myCom->setBaudRate(BAUD128000);
		else if(baudRateComboBox->currentText()==tr("256000"))
			myCom->setBaudRate(BAUD256000);
		else if(baudRateComboBox->currentText()==tr("921600"))
			myCom->setBaudRate(BAUD921600);

		//����λ
		if(dataBitsComboBox->currentText()==tr("5"))
			myCom->setDataBits(DATA_5);
		else if(dataBitsComboBox->currentText()==tr("6"))
			myCom->setDataBits(DATA_6);
		if(dataBitsComboBox->currentText()==tr("7"))
			myCom->setDataBits(DATA_7);
		else if(dataBitsComboBox->currentText()==tr("8"))
			myCom->setDataBits(DATA_8);

		//У��λ
		if(parityComboBox->currentText()==tr("NONE"))
			myCom->setParity(PAR_NONE);
		else if(parityComboBox->currentText()==tr("ODD"))
			myCom->setParity(PAR_ODD);
		else if(parityComboBox->currentText()==tr("EVEN"))
			myCom->setParity(PAR_EVEN);

		//ֹͣλ
		if(stopBitsComboBox->currentText()==tr("1"))
			myCom->setStopBits(STOP_1);
		else if(stopBitsComboBox->currentText()==tr("2"))
			myCom->setStopBits(STOP_2);

		//����λ
		if (controlComboBox->currentText()==("NONE"))
			myCom->setFlowControl(FLOW_OFF);
		else if (controlComboBox->currentText()==("HARDWARE"))
			myCom->setFlowControl(FLOW_HARDWARE);
		else if(controlComboBox->currentText()==("XON/XOFF"))
			myCom->setFlowControl(FLOW_XONXOFF);
        	
		connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));//�źźͲۺ��������������ڻ�����������ʱ�����ж����ڲ���
	}
	else
	{
		QMessageBox::information(this, tr("���ڼ�� "), tr("��ʧ�� ") + port_name, QMessageBox::Ok);
	}
	
        m_baudrate=baudRateComboBox->currentText();
	    m_databit=dataBitsComboBox->currentText();
	    m_parity=parityComboBox->currentText();
	    m_stopbit=stopBitsComboBox->currentText();
	    m_control=controlComboBox->currentText();
	
	configini();

}
 
//�رմ���
void mainwindow::on_closeBtn_clicked()
{
	myCom->close();
	delete myCom;
	comboBox->setEnabled(true);
	baudRateComboBox->setEnabled(true);
	parityComboBox->setEnabled(true);
	dataBitsComboBox->setEnabled(true);
	stopBitsComboBox->setEnabled(true);
	controlComboBox->setEnabled(true);

}

//��շ����������������
void mainwindow::on_cleanBtn_clicked()
{
	recEdit->clear();
	sendEdit->clear();
}

//дini�ļ�
void mainwindow::configini()
{	
	strIniDir = QCoreApplication::applicationDirPath() + "/config.ini";
	QSettings *ConfigIni = new QSettings(strIniDir,QSettings::IniFormat,0);

	ConfigIni->setIniCodec(QTextCodec::codecForLocale());
	ConfigIni->setValue("port",port_name);
	ConfigIni->setValue("BaudRate",m_baudrate);
	ConfigIni->setValue("DataBit",m_databit);
	ConfigIni->setValue("Parity",m_parity);
	ConfigIni->setValue("StopBit",m_stopbit);
	ConfigIni->setValue("ControlBit",m_control);	
	delete ConfigIni;
}

//��ini�ļ�
void mainwindow::readconfig()
{
	int index;
	strIniDir = QCoreApplication::applicationDirPath() + "/config.ini";
	QSettings *ConfigIni = new QSettings(strIniDir,QSettings::IniFormat,0);

	index = comboBox->findText(( ConfigIni->value("port",port_name)).toString());
	comboBox->setCurrentIndex(index);
	
	index=baudRateComboBox->findText(( ConfigIni->value("BaudRate",m_baudrate)).toString());
	baudRateComboBox->setCurrentIndex(index);
	
	index=parityComboBox->findText(( ConfigIni->value("Parity",m_parity)).toString());
	parityComboBox->setCurrentIndex(index);
	QString aa= ConfigIni->value("Parity",m_parity).toString();
	
	index=dataBitsComboBox->findText(( ConfigIni->value("DataBit",m_databit)).toString());
	dataBitsComboBox->setCurrentIndex(index);

	index=stopBitsComboBox->findText(( ConfigIni->value("StopBit",m_stopbit)).toString());
	stopBitsComboBox->setCurrentIndex(index);
	
	index=controlComboBox->findText(( ConfigIni->value("ControlBit",m_control)).toString());
	controlComboBox->setCurrentIndex(index);
	QString dd=( ConfigIni->value("ControlBit",m_control)).toString();

	delete ConfigIni;

}

//���ļ��ж�ȡat����
//void mainwindow::readCommand()
//{
//	
//	QString strAtDir = QCoreApplication::applicationDirPath() + "/atCommand.txt";
//	QFile atFile(strAtDir);
//	if (!atFile.open(QIODevice::ReadOnly))
//	{
//		QMessageBox::warning (NULL,tr(""),tr("���ļ�ʧ��"),QMessageBox::Ok);
//	}
//	while (!atFile.atEnd())
//	{
//		QString at_temp=atFile.readLine();
//		m_listCommand.append(at_temp);
//	}
//
//	atFile.close();	
//
//}

//���Ͷ���ָ��
void mainwindow::on_executionBtn_clicked()
{
	/*QTimer *timer2=new QTimer;
	timer2->start(38000);
	connect(timer2,SIGNAL(timeout()),this,SLOT(checkResult()));*/

	m_listCommand=(QStringList() <<"at"/*<<"ati"*/<<"at+cpin?"<<"at+csq"<<"at+creg?"
								<<"at+cgatt?"<<"at+mipcall=1,\"cmnet\""
								<<"at+mipopen=1,5000,\"209.141.56.197\",80,0"
								<<"sleep(1000)"<<"at+mipsets=1,10"<<"at+miptsend=1"
								<<"sleep(50)"<<"1234567890"<<"at+mipclose=1");

	sendMessage();

}

//������
void mainwindow::readMyCom()
{	
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	qint64 temp=myCom->readData(buf,sizeof(buf));//���������ݵ�buf
	buf[temp+1]=0;

#if 0
		if(QString(buf).contains("OK"));
		m_listCommand.pop_front();//�������ok����ִ����һ�������������ǰ����
#endif

		recEdit->insertPlainText(QString::fromLocal8Bit(buf));

		recEdit->moveCursor(QTextCursor::End,QTextCursor::KeepAnchor);
		recEdit->verticalScrollBar()->setValue(recEdit->verticalScrollBar()->maximumHeight());

}

//����
void mainwindow::sendMessage()
{	
	gettime();

	if (auto_sendBox->isChecked())
	{	
		if(m_listCommand.size()>0)
		{
			QByteArray ba=QString(m_listCommand.at(0)+"\r\n").toAscii();
			sendEdit->setText(ba);
			const char * data=ba.data();
			myCom->writeData(data,qstrlen(data));//��data����д�뵽������
			myCom->flush();

			recEdit->append("------------------------------");
			recEdit->append("<font size=3>"+stime+"<br/>"+tr("����:")+data+"</font>");
			recEdit->append(tr("<font size=3>����:</font>"));

			//��
			char buf[512];
			memset(buf, 0, sizeof(buf));
			qint64 temp=myCom->readData(buf,sizeof(buf));
			buf[temp+1]=0;
			//recEdit->insertPlainText(QString::fromLocal8Bit(buf));
			recEdit->append("<p>"+QString(buf)+"</p>");
		
			//������������׶�
			recEdit->moveCursor(QTextCursor::End,QTextCursor::KeepAnchor);
			recEdit->verticalScrollBar()->setValue(recEdit->verticalScrollBar()->maximumHeight());

			//�жϷ���ֵ
			char *str1="OK";
			char *str2="ERROR";
			char *ptr1,*ptr2;
			ptr1=strstr(buf,str1);
			ptr2=strstr(buf,str2);

			if (!ptr1==NULL)//����OK
			{		
				m_listCommand.pop_front();

				QTimer *timer=new QTimer;
				timer->setSingleShot(true);
				timer->start(2000);
				connect(timer,SIGNAL(timeout()),this,SLOT(sendMessage()));

				if (m_listCommand.isEmpty())
				{
					recEdit->append(tr("<font color=\"#000000\" size=10><b> �����:</b></font>"));
					recEdit->append("<font color=\"#00ff00\" size=16> <b>Pass!</b></font>");
				}
			}
			else if((!ptr2==NULL)||(*buf==NULL))//����ERROR���
			{
				recEdit->append(tr("<font color=\"#000000\" size=10><b> �����:</b></font>"));
				recEdit->append("<font color=\"#ff0000\" size=16> <b>Failed!</b></font>");
			}
		}
	}
	
	else 
	{
		QString str=sendEdit->toPlainText();
		str.append("\r\n");
		QByteArray aa=str.toAscii();
		const char * strdata=aa.data();
		int rec=myCom->writeData(strdata,qstrlen(strdata));
		myCom->flush();
		
	
		recEdit->append("------------------------------");
		
		recEdit->append(stime+"\r\n"+tr("����:")+strdata);		
		recEdit->append(tr("����:")+"\r\n");
	}

	QString qq = recEdit->toHtml();

}

//��ȡ��ǰʱ��
void mainwindow::gettime()
{
	QDateTime dateTime = QDateTime::currentDateTime();
	int y=dateTime.date().year();
	int m=dateTime.date().month();
	int d=dateTime.date().day();
	QString strTime=dateTime.time().toString();
	stime=(strTime+"   "+QString::number(y)+"/"+QString::number(m)+"/"+QString::number(d));
}

//�������������ݱ�����save.txt��
void mainwindow::on_saveBtn_clicked()
{
	
	strSaveDir = QCoreApplication::applicationDirPath() + "/save.txt";
	QString temp=recEdit->toPlainText();
	
	QByteArray bb=temp.toAscii();
	const char *str_temp=bb.data();

	QFile myFile(strSaveDir);
	if (!myFile.open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(this,tr("warning"),tr("Open Error!"),QMessageBox::Ok);
	}

	myFile.write(str_temp);
	myFile.close();
	QMessageBox::information(this,tr("���ڼ��"),tr("����ɹ�!"),QMessageBox::Ok);

}

void mainwindow::checkResult()
{

	QString temp=recEdit->toPlainText();

	if ((temp.contains("ERROR"))||temp.isEmpty())
	{
		recEdit->append(tr("<font color=\"#000000\" size=10><b> �����:</b></font>"));
		recEdit->append("<font color=\"#ff0000\" size=16> <b>Failed!</b></font>");
	}
	else
	{
		recEdit->append(tr("<font color=\"#000000\" size=10><b> �����:</b></font>"));
		recEdit->append("<font color=\"#00ff00\" size=16> <b>Pass!</b></font>");

	}

}