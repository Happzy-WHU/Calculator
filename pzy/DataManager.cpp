#include "DataManager.h"
vector<QString> DataManager::readFileJson() const
{
	vector<QString> vec;
	QFile file("history.json");
	if (!file.open(QIODevice::ReadWrite))
	{
		qDebug() << "File open error";
	}
	else {
		qDebug() << "File open!";
	}
	QByteArray allData = file.readAll();

	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

	if (json_error.error != QJsonParseError::NoError)
	{
		qDebug() << "json error!";
		return vec;
	}

	QJsonObject rootObj = jsonDoc.object();

	QJsonArray subArray = rootObj.value("history").toArray();
	QJsonObject temp;
	for (int i = 0; i < subArray.size(); ++i)
	{
		temp = subArray.at(i).toObject();
		vec.push_back(temp["id"].toString());
		vec.push_back(temp["label_ans"].toString());
		vec.push_back(temp["label_str"].toString());
	}
	return vec;
}




void DataManager::writeFileJson(string str, string ans)
{
	QFile file_read("history.json");
	if (!file_read.open(QIODevice::ReadWrite))
	{
		qDebug() << "File open error";
	}
	else {
		qDebug() << "File open!";
	}
	QByteArray allData = file_read.readAll();
	file_read.close();

	QJsonParseError json_error;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));
	QJsonObject rootObj = jsonDoc.object();
	QJsonArray subArray = rootObj.value("history").toArray();

	bool isFull = false;
	if (subArray.size() > 0)
	{
		if (subArray.size() == 20)
		{
			isFull = true;
			subArray.removeAt(0);
			QJsonObject temp;
			for (int i = 0; i < subArray.size(); i++)
			{
				temp = subArray.at(i).toObject();
				temp["id"] = temp["id"].toDouble() - 1;
				subArray[i] = temp;
			}
		}
	}

	QJsonObject jsonObject;
	if (isFull)
	{
		jsonObject.insert("id", 20);
	}
	else
	{
		jsonObject.insert("id", subArray.size() + 1);
	}
	jsonObject.insert("label_str", QString::fromStdString(str));
	jsonObject.insert("label_ans", QString::fromStdString(ans));

	subArray.append(jsonObject);

	//QJsonDocument jsonDoc;
	QJsonObject tempObj;
	tempObj.insert("history", subArray);
	jsonDoc.setObject(tempObj);

	QFile file_write("history.json");
	if (!file_write.open(QIODevice::WriteOnly))
	{
		qDebug() << "File open error";
	}
	file_write.write(jsonDoc.toJson());
	file_write.close();
	qDebug() << "Write to file";
}


