#include "Calculate.h"
Calculate::Calculate(History *his) 
{
	this->his = his;
}

void Calculate::calcOnce() 
{
	if (num.size() <= 1 && op.size() <= 0) 
	{
		return;
	}
	double ans;
	double a;
	double b;
	b = num.top();
	num.pop();
	a = num.top();
	num.pop();
	switch (op.top()) 
	{
	case '+':
		ans = a + b;
		break;
	case '-':
		ans = a - b;
		break;
	case '*':
		ans = a * b;
		break;

	default:
		ans = a / b;
	}
	op.pop();
	num.push(ans);
}
bool Calculate::judgePrior(char c) 
{
	if (!op.empty()) 
	{
		if (op.top() == '*' || op.top() == '/' || c == '+' || c == '-') 
		{
			return true;
		}
	}
	return false;
}
QString Calculate::calcText(QString s)
{
	s = removeComma(s);
	//截取字符串的位置索引
	int cutIndex = 0;
	//i表示的是遍历一次后
	for (int i = 0; i < s.length(); i++) 
	{
		if (s.at(i) == '+' || s.at(i) == '-' || s.at(i) == '*' || s.at(i) == '/') 
		{
			if (i == 0 || s[i - 1] == '(') 
			{
				continue;
			}
			if (s[cutIndex] == '(') 
			{
				num.push(stod(s.mid(cutIndex + 1, i - 1).toStdWString().c_str()));
			}
			else {
				num.push(stod(s.mid(cutIndex, i).toStdWString().c_str()));

			}
			cutIndex = i + 1;
			while (judgePrior(s.at(i).toLatin1()))
			{
				calcOnce();
			}
			op.push(s.at(i).toLatin1());
		}
	}
	QString tempNum = s.mid(cutIndex, s.length());
	if (tempNum[0] == '(') 
	{
		tempNum = tempNum.mid(1, tempNum.length() - 1);
	}
	double m = stod(tempNum.toStdString().c_str());
	num.push(m);
	while (!op.empty())
	{
		calcOnce();
	}
	return deletePoint(QString::number(num.top()));
}
QString Calculate::deletePoint(QString s) 
{
	int index = s.indexOf('.');
	int cutIndex = index;
	for (int i = index + 1; i < s.length(); i++) 
	{
		if (s.at(i) != '0') 
		{
			cutIndex = i + 1;
		}
	}
	return s.mid(0, cutIndex);
}
//暂未实现
QString Calculate::bigNum(QString a, QString b) 
{
	return "";
}
QString Calculate::opp(QString s) 
{
	//文本是0
	if (s == "0") 
	{
		return "0";
	}
	if (s[0] == '-') 
	{
		return s.mid(1, s.length());
	}
	else
	{
		return '-' + s;
	}
}

auto Calculate::removeComma(QString s) -> QString
{
	string str = s.toStdString();
	string str_new = "";
	for (auto c : str)
	{
		if (c != ',')
		{
			str_new += c;
		}
	}
	return QString::fromStdString(str_new);
}

QString  Calculate::addComma(QString s)
{
	string str = s.toStdString();
	char temp = 0;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (isalnum(str[i]))
		{
			if (++temp == 3)
			{
				temp = 0;
				if (i != 0 && isalnum(str[i - 1]))
				{
					str.insert(i, ",");
				}
			}
		}
		else {
			temp = 0;
		}
	}
	return QString::fromStdString(str);
}
long long Calculate::otherToLong(QString str, int radix) 
{
	string s = str.toStdString();
	long long ans = 0;
	for (int i = 0; i < s.size(); i++)
	{
		char t = s.at(i);
		if (t >= '0'&&t <= '9') ans = ans * radix + t - '0';
		else ans = ans * radix + t - 'a' + 10;
	}
	return ans;
}
vector<QString> Calculate::longToOther(long long num) const
{
	vector<QString> vec(4);
	QString a= QString::number(num, 16);
	QString b = QString::number(num, 8);
	QString c = QString::number(num, 2);
	vec[0] = a;
	vec[1] = QString::number(num, 10);
	vec[2] = b;
	vec[3] = c;
	return vec;
}
vector<QString> Calculate::calcConvertEvent(QString str, QString btn_text, char currentIndex, char c) const
{
	vector<QString>vec{4,"0"};
	if (c == 1 || c == 15) 
	{
		if (c == 1) 
		{
			str += btn_text;
		}
		if (c == 15) 
		{
			str = str.left(str.size() - 1);
		}
		long long temp = 0;
		if (currentIndex == 1) 
		{
			temp = otherToLong(str, 16);
			vec = longToOther(temp);
		}
		else if (currentIndex == 2) 
		{
			temp = str.toLongLong();
			vec = longToOther(temp);
			vec[1] = QString::number(temp, 10);
		}
		else if (currentIndex == 3) 
		{
			temp = otherToLong(str, 8);
			vec = longToOther(temp);
		}
		else if (currentIndex == 4) 
		{
			temp = otherToLong(str, 2);
			vec = longToOther(temp);
		}
		return vec;
	}
	return vec;
	
}
vector<QString> Calculate::calcEvent(QString str, QString ans,QString btn_text, History *frame_his)
{
	vector<QString> vec{str, ans};
	if (btn_text=="1"|| btn_text == "2"|| btn_text == "3"|| btn_text == "4"|| btn_text == "5"||
		btn_text == "6" || btn_text == "7" || btn_text == "8" || btn_text == "9" || btn_text == "0")
	{
		if (ans == "0") 
		{
			ans = "";
		}
		
		vec[1] = ans + btn_text;
	}
	if (btn_text == "+" || btn_text == "-" || btn_text == "*" || btn_text == "/")
	{
		//这是一个判断是否将运算符替换掉的变量
		bool should_replace = false;
		if (str.size() > 0) 
		{
			QChar c = str[str.size() - 1];
			if (c == '+' || c == '-' || c == '*' || c == '/') 
			{
				should_replace = true;
				vec[0] = str.left(str.length() - 1) + btn_text;
			}
			if (c == '=') 
			{
				str = "";
			}
		}
		if (ans[0] == '-') 
		{
			ans = '(' + ans + ')';
		}
		if(!should_replace)
			vec[0] = str + ans + btn_text;
		vec[1] = "0";
	}
	if (btn_text == "del")
	{
		if (ans == "0") 
		{
			vec[0] = addComma(removeComma(vec[0]));
			vec[1] = addComma(removeComma(vec[1]));
			return vec;
		}
		if (ans.length() == 1) 
		{
			vec[1] = "0";
		}
		else {
			vec[1] = ans.mid(0, ans.length() - 1);
		}
	}
	if (btn_text=="del" || (btn_text == "ce" && ans == "0"))
	{
		vec[0] = "";
		vec[1] = "0";
	}
	if (btn_text == "=")
	{
		if (str.size()>0 && str[str.size() - 1] == '=') 
		{
			int index = -1;
			for (int i = 0; i < str.length(); i++) 
			{
				if (str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '*' || str.at(i) == '/') 
				{
					index = i;
				}
			}
			if (index == -1) 
			{
				Thread_write *th = new Thread_write();
				vec[0] = addComma(vec[1]+'=');
				vec[1] = addComma(vec[1]);
				th->str = vec[0].toStdString();
				th->ans = vec[1].toStdString();
				th->start();
				his->addToWidget(vec[0], vec[1]);
				vec[0] = addComma(removeComma(vec[0]));
				vec[1] = addComma(removeComma(vec[1]));
				return vec;

			}
			else {
				str = ans.append(str.mid(index));
				vec[0] = str;
				vec[1] = calcText(str);
				Thread_write *th = new Thread_write();
				vec[0] = addComma(vec[0]);
				vec[1] = addComma(vec[1]);
				th->str = vec[0].toStdString();
				th->ans = vec[1].toStdString();
				th->start();
				his->addToWidget(vec[0], vec[1]);
				vec[0] = addComma(removeComma(vec[0]));
				vec[1] = addComma(removeComma(vec[1]));
				return vec;
			}
		}
		if (ans[0] == '-') 
		{
			ans = '(' + ans + ')';
		}
		vec[0] = str + ans + '=';
		vec[1] = calcText((str + ans));
		Thread_write *th = new Thread_write();
		vec[0] = addComma(vec[0]);
		vec[1] = addComma(vec[1]);
		th->str = vec[0].toStdString();
		th->ans = vec[1].toStdString();
		th->start();
		his->addToWidget(vec[0],vec[1]);
	}
	if (btn_text == "+/-")
	{
		if (str[str.size() - 1] == '=') 
		{
			vec[0] = "";
		}
		vec[1] = opp(ans);
	}
	if (btn_text == ".")
	{
		if (ans.indexOf(".") == -1)
			vec[1] = ans + ".";
	}
	if (btn_text == "ce" && ans != "0")
	{
		vec[1] = "0";
	}
	vec[0] = addComma(removeComma(vec[0]));
	vec[1] = addComma(removeComma(vec[1]));
	return vec;
}