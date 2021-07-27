#ifndef CALCMAIN_H
#define CALCMAIN_H

#include <QMainWindow>
#include<QPushButton>
#include "History.h"
#include "DataManager.h"
#include "Calculate.h"
#include <QApplication>
#include "NumConvert.h"
#include <QComboBox>
#include <QKeyEvent>
#include <QClipboard>
#include <regex>

class DataManager;
class ErrorManager;
class Calculate;
class NumConvert;

class CalcMain : public QWidget
{
	Q_OBJECT

public:
	explicit CalcMain(QWidget *parent = nullptr);
public slots:
	void onBtnClick();
	void onComboxChanged() const;

protected:
	void resizeEvent(QResizeEvent *event) override;
private:
	QFrame *frame_list[4];
	History *frame_his;
	NumConvert *nc = nullptr;
	DataManager *dm;
	Calculate *ca;
	QPushButton *btn_list[5][4];
	QPushButton *btn_his;
	QComboBox *cmbBox_conv;
	QLabel *lab_str;
	QLabel *lab_ans;
	QVBoxLayout *vLayout_list[3];
	QHBoxLayout *hLayout_list[7];
	void keyPressEvent(QKeyEvent *ev) override;
	void processClick(QPushButton* bt);
	void doPaste();
};

#endif // CALCMAIN_H