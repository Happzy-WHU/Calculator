#include "History.h"
#pragma execution_character_set("utf-8");
History::History()
{
	layout_his = new QVBoxLayout();
	this->setLayout(layout_his);
	title = new QLabel("ÀúÊ·¼ÇÂ¼");
	title->setAlignment(Qt::AlignCenter);
	listWgt_his = new QListWidget(this);
	listWgt_his->setViewMode(QListWidget::ListMode);
	layout_his->addWidget(title);
	layout_his->setSpacing(20);
	layout_his->addWidget(listWgt_his);
	layout_his->setStretchFactor(title, 1);
	layout_his->setStretchFactor(listWgt_his, 12);
	initToWidget();
}

void History::initToWidget() const
{
	Thread_read *th = new Thread_read(listWgt_his);
	th->start();
}

void History::addToWidget(QString str, QString ans)
{
	temp_item = new QListWidgetItem(str);
	listWgt_his->insertItem(0, temp_item);
	temp_item->setTextAlignment(Qt::AlignRight);
	temp_item = new QListWidgetItem(ans);
	listWgt_his->insertItem(1, temp_item);
	temp_item->setTextAlignment(Qt::AlignRight);
	while (listWgt_his->count() > 40)
	{
		listWgt_his->removeItemWidget(listWgt_his->item(listWgt_his->count() - 1));
		delete listWgt_his->item(listWgt_his->count() - 1);
		listWgt_his->removeItemWidget(listWgt_his->item(listWgt_his->count() - 1));
		delete listWgt_his->item(listWgt_his->count() - 1);
	}
}