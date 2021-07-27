#pragma once
#include"Calculate.h"
class Calculate;
class NumConvert :
	public QFrame
{
	Q_OBJECT
public:
	NumConvert();
	QFrame *frame_text;
	QFrame *frame_btn;
	void processClick(QPushButton* bt);
	Calculate *ca = nullptr;
public slots:
	void onWidgetClick();
private:
	QPushButton *btn_list[30];
	QHBoxLayout *hLayout_list[9];
	
	char currentIndex;
	
	void changeColor();
};

