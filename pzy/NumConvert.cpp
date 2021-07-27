#include "NumConvert.h"
NumConvert::NumConvert()
{
	QString str_list_1[4][4] = { {"1","2","3","4"},{"5","6","7","8"},
	{"9","0","A","B"},{"C","D","E","F"} };
	for (int i = 0; i < 30; ++i) {
		btn_list[i] = new QPushButton();
		connect(btn_list[i], SIGNAL(clicked()), this, SLOT(onWidgetClick()));
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			btn_list[i*4+j]->setText(str_list_1[i][j]);
		}
	}
	QString str_list_2[10] = { "ac","del","hex","","dec","","oct","","bin","" };
	for(int i = 0; i < 10; i++) {
		btn_list[i + 16]->setText(str_list_2[i]);
	}
	for (int i = 0; i < 9; i++) {
		hLayout_list[i] = new QHBoxLayout();
		if (i <= 3) {
			hLayout_list[i]->addWidget(btn_list[i * 2 + 18]);
			hLayout_list[i]->setStretchFactor(btn_list[i * 2 + 18], 1);
			hLayout_list[i]->addWidget(btn_list[i * 2 + 19]);
			hLayout_list[i]->setStretchFactor(btn_list[i * 2 + 19], 5);
		}
		else if(i>3&&i<8){
			hLayout_list[i]->addWidget(btn_list[(i - 4) * 4 + 0]);
			hLayout_list[i]->addWidget(btn_list[(i - 4) * 4 + 1]);
			hLayout_list[i]->addWidget(btn_list[(i - 4) * 4 + 2]);
			hLayout_list[i]->addWidget(btn_list[(i - 4) * 4 + 3]);
		}
		else {
			hLayout_list[i]->addWidget(btn_list[16]);
			hLayout_list[i]->addWidget(btn_list[17]);
		}
	}
	ca = new Calculate();
	frame_text = new QFrame();
	frame_btn = new QFrame();

	QVBoxLayout *vLayout_text = new QVBoxLayout();
	QVBoxLayout *vLayout_btn = new QVBoxLayout();

	frame_text->setLayout(vLayout_text);

	vLayout_text->addLayout(hLayout_list[0]);
	vLayout_text->addLayout(hLayout_list[1]);
	vLayout_text->addLayout(hLayout_list[2]);
	vLayout_text->addLayout(hLayout_list[3]);

	frame_btn->setLayout(vLayout_btn);
	vLayout_btn->addLayout(hLayout_list[4]);
	vLayout_btn->addLayout(hLayout_list[5]);
	vLayout_btn->addLayout(hLayout_list[6]);
	vLayout_btn->addLayout(hLayout_list[7]);
	vLayout_btn->addLayout(hLayout_list[8]);

	btn_list[26] = btn_list[28];
	btn_list[27] = btn_list[29];
	btn_list[28] = btn_list[20];
	btn_list[29] = btn_list[21];
	changeColor();
	currentIndex = 2;
}
void NumConvert::processClick(QPushButton* bt)
{
	if (bt == btn_list[18] || bt == btn_list[19])
	{
		currentIndex = 1;
		btn_list[26] = btn_list[28];
		btn_list[27] = btn_list[29];
		btn_list[28] = btn_list[18];
		btn_list[29] = btn_list[19];
		changeColor();
		return;
	}
	else if (bt == btn_list[20] || bt == btn_list[21])
	{
		currentIndex = 2;
		btn_list[26] = btn_list[28];
		btn_list[27] = btn_list[29];
		btn_list[28] = btn_list[20];
		btn_list[29] = btn_list[21];
		changeColor();
		return;

	}
	else if (bt == btn_list[22] || bt == btn_list[23])
	{
		currentIndex = 3;
		btn_list[26] = btn_list[28];
		btn_list[27] = btn_list[29];
		btn_list[28] = btn_list[22];
		btn_list[29] = btn_list[23];
		changeColor();
		return;

	}
	else if (bt == btn_list[24] || bt == btn_list[25])
	{
		currentIndex = 4;
		btn_list[26] = btn_list[28];
		btn_list[27] = btn_list[29];
		btn_list[28] = btn_list[24];
		btn_list[29] = btn_list[25];
		changeColor();
		return;
	}
	char c = -1;
	if (bt == btn_list[0])
	{
		c = 1;
	}
	else if (bt == btn_list[1] || bt == btn_list[2] || bt == btn_list[3] ||
		bt == btn_list[4] || bt == btn_list[5] ||
		bt == btn_list[6])
	{
		if (currentIndex >= 4)
			return;
		c = 1;
	}
	else if (bt == btn_list[7] || bt == btn_list[8])
	{
		if (currentIndex >= 3)
			return;
		c = 1;
	}
	else if (bt == btn_list[9])
	{
		if (btn_list[21]->text() == "0")
			return;
		c = 1;
	}
	else if (bt == btn_list[10] || bt == btn_list[11] ||
		bt == btn_list[12] || bt == btn_list[13] ||
		bt == btn_list[14] || bt == btn_list[15])
	{
		if (currentIndex >= 2)
			return;
		c = 1;
	}
	else if (bt == btn_list[17])
	{
		c = 15;
	}
	else if (bt == btn_list[16])
	{
		c = 16;
	}
	QString str_temp;
	switch (currentIndex)
	{
	case 1:
		str_temp = btn_list[19]->text();
		break;
	case 2:
		str_temp = btn_list[21]->text();
		break;
	case 3:
		str_temp = btn_list[23]->text();
		break;
	case 4:
		str_temp = btn_list[25]->text();
		break;
	default:
		break;
	}
	vector<QString> vec = ca->calcConvertEvent(str_temp, bt->text(), currentIndex, c);
	btn_list[19]->setText(vec[0]);
	btn_list[21]->setText(vec[1]);
	btn_list[23]->setText(vec[2]);
	btn_list[25]->setText(vec[3]);
}
void NumConvert::onWidgetClick()
{
	QPushButton *bt = (QPushButton *)sender();
	processClick(bt);
}

void NumConvert::changeColor()
{
	if (btn_list[26])
	{
		btn_list[26]->setStyleSheet("border: 1px solid black;");
		btn_list[27]->setStyleSheet("border: 1px solid black;");
	}
	btn_list[28]->setStyleSheet("border: 2px solid blue;");
	btn_list[29]->setStyleSheet("border: 2px solid blue;");
}
