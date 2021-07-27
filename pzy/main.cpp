#include "CalcMain.h"
#include <QApplication>
#pragma execution_character_set("utf-8");
#include <QFile>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
	CalcMain w;
	w.setWindowTitle("¼ÆËãÆ÷");
	w.setWindowIcon(QIcon("icon.png"));
	w.show();
	return a.exec();
}