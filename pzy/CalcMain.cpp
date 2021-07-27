#include "CalcMain.h"
#pragma execution_character_set("utf-8");

CalcMain::CalcMain(QWidget *parent) :
	QWidget(parent)
{
	for (int i = 0; i < 4; i++) {
		frame_list[i] = new QFrame();
	}
	QString str_list[5][4] = { {"1","2","3","+"},{"4","5","6","-"},{"7","8","9","*"},{"ac","0","=","/"},{"=/-",".","del","ce"} };
	for (int i = 0; i < 5; ++i)
	{
		//btn_list[i] = new QPushButton*[5];
		for (int j = 0; j < 4; ++j)
		{
			btn_list[i][j] = new QPushButton();
			btn_list[i][j]->setText(str_list[i][j]);
			btn_list[i][j]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
			connect(btn_list[i][j], SIGNAL(clicked()), this, SLOT(onBtnClick()));
			if (i < 3 && j < 3) {
				btn_list[i][j]->setObjectName("btn_1");
				continue;
			}
			else if (j == 3 && i != 4) 
			{
				btn_list[i][j]->setObjectName("btn_11");
			}
		}
	}
	btn_list[3][1]->setObjectName("btn_1");

	btn_list[4][2]->setObjectName("btn_15");
	btn_list[3][0]->setObjectName("btn_16");
	btn_list[3][2]->setObjectName("btn_17");
	btn_list[4][0]->setObjectName("btn_18");
	btn_list[4][1]->setObjectName("btn_19");
	btn_list[4][3]->setObjectName("btn_20");

	for (int i = 0; i < 3; ++i) {
		vLayout_list[i] = new QVBoxLayout();
	}
	for (int i = 0; i < 7; ++i) {
		hLayout_list[i] = new QHBoxLayout();
	}
	this->setLayout(hLayout_list[5]);
	
	frame_his = new History();


	dm = new DataManager();
	ca = new Calculate(frame_his);
	nc = new NumConvert();

	hLayout_list[5]->addWidget(frame_list[0]);
	hLayout_list[5]->setSpacing(20);
	hLayout_list[5]->addWidget(frame_his);
	hLayout_list[5]->setStretchFactor(frame_list[0], 2);
	hLayout_list[5]->setStretchFactor(frame_his, 1);
	frame_his->hide();
	frame_list[0]->setLayout(vLayout_list[0]);

	
	frame_list[2]->setLayout(vLayout_list[2]);
	vLayout_list[0]->addWidget(frame_list[3]);
	vLayout_list[0]->addWidget(frame_list[1]);
	vLayout_list[0]->setSpacing(10);
	vLayout_list[0]->addWidget(frame_list[2]);
	vLayout_list[0]->setStretchFactor(frame_list[1], 2);
	vLayout_list[0]->setStretchFactor(frame_list[2], 5);
	vLayout_list[0]->addWidget(nc->frame_text);
	vLayout_list[0]->setSpacing(10);
	vLayout_list[0]->addWidget(nc->frame_btn);
	vLayout_list[0]->setStretchFactor(nc->frame_text, 2);
	vLayout_list[0]->setStretchFactor(nc->frame_btn, 5);
	nc->frame_text->hide();
	nc->frame_btn->hide();

	frame_list[3]->setLayout(hLayout_list[6]);
	btn_his = new QPushButton(frame_list[3]);
	connect(btn_his, SIGNAL(clicked()), this, SLOT(onBtnClick()));
	cmbBox_conv = new QComboBox();
	cmbBox_conv->addItem("科学");
	cmbBox_conv->addItem("进制转换");
	hLayout_list[6]->addWidget(cmbBox_conv, Qt::AlignLeft);
	hLayout_list[6]->addStretch();
	hLayout_list[6]->addWidget(btn_his, Qt::AlignRight);

	lab_str = new QLabel();
	lab_ans = new QLabel("0");
	lab_str->setAlignment(Qt::AlignRight);
	lab_ans->setAlignment(Qt::AlignRight);

	frame_list[1]->setLayout(vLayout_list[1]);
	vLayout_list[1]->addWidget(lab_str);
	vLayout_list[1]->addWidget(lab_ans);

	frame_list[2]->setLayout(vLayout_list[2]);
	
	vLayout_list[2]->addLayout(hLayout_list[0]);
	vLayout_list[2]->addLayout(hLayout_list[1]);
	vLayout_list[2]->addLayout(hLayout_list[2]);
	vLayout_list[2]->addLayout(hLayout_list[3]);
	vLayout_list[2]->addLayout(hLayout_list[4]);
	
	for (int i = 0; i < 4; i++) {
		hLayout_list[0]->addWidget(btn_list[0][i]);
		hLayout_list[1]->addWidget(btn_list[1][i]);
		hLayout_list[2]->addWidget(btn_list[2][i]);
		hLayout_list[3]->addWidget(btn_list[3][i]);
		hLayout_list[4]->addWidget(btn_list[4][i]);
	}
	
	connect(cmbBox_conv, SIGNAL(currentIndexChanged(const QString)), this, SLOT(onComboxChanged()));
	QString qss;
	QFile qss_main_btn("main_btn.qss");
	qss_main_btn.open(QFile::ReadOnly);
	if (qss_main_btn.isOpen())
	{
		qss = QLatin1String(qss_main_btn.readAll());
		frame_list[2]->setStyleSheet(qss);
		qss_main_btn.close();
	}
	QFile qss_main_label("main_label.qss");
	qss_main_label.open(QFile::ReadOnly);
	if (qss_main_label.isOpen())
	{
		qss = QLatin1String(qss_main_label.readAll());
		frame_list[1]->setStyleSheet(qss);
		qss_main_label.close();
	}
	QFile qss_his_icon("his_icon.qss");
	qss_his_icon.open(QFile::ReadOnly);
	if (qss_his_icon.isOpen())
	{
		qss = QLatin1String(qss_his_icon.readAll());
		frame_list[3]->setStyleSheet(qss);
		qss_his_icon.close();
	}
	QFile qss_his("his.qss");
	qss_his.open(QFile::ReadOnly);
	if (qss_his.isOpen())
	{
		qss = QLatin1String(qss_his.readAll());
		frame_his->setStyleSheet(qss);
		qss_his.close();
	}
	QFile qss_convert_btn("convert_btn.qss");
	qss_convert_btn.open(QFile::ReadOnly);
	if (qss_convert_btn.isOpen())
	{
		qss = QLatin1String(qss_convert_btn.readAll());
		nc->frame_btn->setStyleSheet(qss);
		qss_convert_btn.close();
	}
	QFile qss_convert_text("convert_text.qss");
	qss_convert_text.open(QFile::ReadOnly);
	if (qss_convert_text.isOpen())
	{
		qss = QLatin1String(qss_convert_text.readAll());
		nc->frame_text->setStyleSheet(qss);
		qss_convert_text.close();
	}
}
static bool isFold = true;

void CalcMain::resizeEvent(QResizeEvent *event)
{
	if (this->width() < 700)
	{
		if (!frame_his->isHidden()) {
			frame_his->hide();
			isFold = true;
		}
		//btn_his->show();
	}
	else {
		if (frame_his->isHidden()) {
			frame_his->show();
			isFold = false;
		}
	}
	QWidget::resizeEvent(event);

}

void CalcMain::processClick(QPushButton* bt)
{
	vector<QString> vec = ca->calcEvent(lab_str->text(), lab_ans->text(), bt->text(), frame_his);
	lab_str->setText(vec[0]);
	lab_ans->setText(vec[1]);
}

void CalcMain::onBtnClick()
{
	auto*bt = static_cast<QPushButton*>(sender());
	processClick(bt);
}

void CalcMain::onComboxChanged() const
{
	QFrame *tempText = nullptr;
	QFrame *tempBtn = nullptr;

	if (cmbBox_conv->currentIndex() == 0)
	{
		nc->frame_btn->hide();
		nc->frame_text->hide();
		frame_list[2]->show();
		frame_list[1]->show();
	}
	else if (cmbBox_conv->currentIndex() == 1)
	{
		frame_list[2]->hide();
		frame_list[1]->hide();
		nc->frame_btn->show();
		nc->frame_text->show();
	}
}
void CalcMain::doPaste()
{
	QString str = lab_str->text();
	QString ans = lab_ans->text();
	QClipboard *clip = QApplication::clipboard();
	QString originalText = clip->text();
	if(originalText=="")
	{
		return;
	}
	else {
		for (auto c : originalText)
		{
			if (!(c == '+' || c == '-' || c == '*' || c == '/' || (c >= 48 && c <= 57) || c == '=')) {
				return;
			}
		}
	}
	QString lastNum = "";
	QString	otherStr = "";
	regex e("[\\W]");
	auto tempStr = originalText.toStdString();
	sregex_iterator pos(tempStr.begin(), tempStr.end(), e);
	sregex_iterator end;
	int maxIndex = -1;

	for (; pos != end; ++pos)
	{
		int maxIndex = max(maxIndex, pos->position());
	}

	if (maxIndex != -1)
	{
		otherStr = originalText.left(maxIndex);
	}
	lastNum = originalText.right(originalText.size() - 1 - maxIndex);

	if (str.size() > 0 && str[str.size() - 1] == '=')
	{
		processClick(btn_list[3][0]);
	}
	if (originalText[originalText.size() - 1] == '=')
	{
		QString str = originalText.left(originalText.size() - 1);
		lab_str->setText(ca->addComma(originalText));
		lab_ans->setText(ca->addComma(ca->calcText(str)));
	}
	else {
		lab_str->setText(ca->addComma(str + otherStr));
		lab_ans->setText(ca->addComma(lastNum));
	}
}
void CalcMain::keyPressEvent(QKeyEvent *ev)
{
	if (ev->key() == '0')
	{
		processClick(btn_list[3][1]);
	}
	else if (ev->key() == '1')
	{
		processClick(btn_list[0][0]);
	}
	else if (ev->key() == '2')
	{
		processClick(btn_list[0][1]);
	}
	else if (ev->key() == '3')
	{
		processClick(btn_list[0][2]);
	}
	else if (ev->key() == '4')
	{
		processClick(btn_list[1][0]);
	}
	else if (ev->key() == '5')
	{
		processClick(btn_list[1][1]);
	}
	else if (ev->key() == '6')
	{
		processClick(btn_list[1][2]);
	}
	else if (ev->key() == '7')
	{
		processClick(btn_list[2][0]);
	}
	else if (ev->key() == '8')
	{
		processClick(btn_list[2][1]);
	}
	else if (ev->key() == '9')
	{
		processClick(btn_list[2][2]);
	}
	else if (ev->key() == '+')
	{
		processClick(btn_list[0][3]);
	}
	else if (ev->key() == '-')
	{
		processClick(btn_list[1][3]);
	}
	else if (ev->key() == '*')
	{
		processClick(btn_list[2][3]);
	}
	else if (ev->key() == '/')
	{
		processClick(btn_list[3][3]);
	}
	else if (ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return)
	{
		processClick(btn_list[3][2]);
	}
	else if (ev->matches(QKeySequence::Paste))
	{
		doPaste();
	}
	else if (ev->key() == Qt::Key_Backspace)
	{
		processClick(btn_list[4][2]);
	}
	else if (ev->key() == Qt::Key_Delete)
	{
		processClick(btn_list[4][3]);
	}
	QWidget::keyPressEvent(ev);
}
