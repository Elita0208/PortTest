#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "ui_mainwindow.h"
#include "win_qextserialport.h"


class mainwindow : public QMainWindow,public Ui_mainwindowClass
{
	Q_OBJECT

	public:
		mainwindow();
		~mainwindow(){};

	public:
		QString getcomm(int index,QString keyorvalue); //��ȡ����

	private:
		void init_com();
		Win_QextSerialPort *myCom;//��������
        QTimer *timer;
		QStringList m_listCommand;	//�����͵�����
		wchar_t subkey[80];
		wchar_t keyname[256]; //��������
		char keyvalue[256];  //��ֵ����
		int indexnum;
		DWORD keysize,type,valuesize;
		HKEY hKey;
		QString port_name;
		QString baud_rate;
		QString m_baudrate;
		QString m_databit;
		QString m_parity;
		QString m_stopbit;
		QString m_control;
		QString strIniDir;
		QString stime;
		QString strSaveDir;


	private slots:
	
		void readMyCom();
		void on_openBtn_clicked();
		void on_executionBtn_clicked();
		void on_closeBtn_clicked();
		void on_cleanBtn_clicked();
		void on_saveBtn_clicked();
		//void saveBtn();

		void sendMessage();
		void configini();
		void readconfig();
		void gettime();
		void checkResult();

};

#endif
