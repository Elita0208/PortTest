#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));

	mainwindow mycom;
	mycom.show();
	return a.exec();
}
