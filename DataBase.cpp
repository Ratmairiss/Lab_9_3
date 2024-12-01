
#include "DataBase.h"

DataBase::DataBase(QObject* pt = 0) : QObject(pt)
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("Lab_9_Data_base");
	db.setUserName("user");
	db.setHostName("host");
	db.setPassword("password");
	if (!db.open())
	{
		qDebug() << "Wasnt able to connect to Data base";
		return;
	}

	QSqlQuery query;
	if (!query.exec("CREATE TABLE IF NOT EXISTS figures(\
						     name        VARCHAR(25),\
							 figureType  VARCHAR(25),\
							 connections TEXT, \
							 amount      INTEGER, \
							 figureAmount VARCHAR,\
							 posX        INTEGER, \
							 posY	     INTEGER, \
							 width       INTEGER, \
							 height      INTEGER, \
							 color       INTEGER, \
							 lineColor   INTEGER, \
							 ind         INTEGER, \
							 isHidden    INTEGER);"))
	{
		qDebug() << query.lastError().text();
	}

	model = new QSqlTableModel(this, db);
	model->setTable("figures");
	model->setQuery("SELECT name, figureType, connections, amount, figureType,figureAmount\
					 FROM figures");
	model->setFilter("isHidden = 0");
}

void DataBase::addFigure(QString name, QString figureType, qint32 posX, qint32 posY,
	qint32 width, qint32 height, qint32 color, qint32 lineColor)
{
	QSqlQuery query;

	//—читаем индекс фигуры, которую мы добавл€ем
	qint32 index = size();

	//—колько фигур данного типа уже существует
	query.exec(QString("SELECT COUNT(*) FROM figures WHERE figureType = '%1'").arg(figureType));
	query.next();
	qint32 amount = query.value(0).toInt();

	QString str = QString(
		"INSERT INTO figures (name,figureType, connections, amount, posX, posY, width, height, color, lineColor,ind,isHidden) \
			\VALUES ('%1', '%2', '%3', %4, %5, %6, %7, %8, %9,%10,%11,%12);")
		.arg(name)
		.arg(figureType)
		.arg("No Connections")
		.arg(amount)
		.arg(posX)
		.arg(posY)
		.arg(width)
		.arg(height)
		.arg(color)
		.arg(lineColor)
		.arg(index)
		.arg(0);

	if (!query.exec(str))
		qDebug() << query.lastError().text();

	updateAmounts(figureType);

	model->select();
}


bool DataBase::isFigureExists(QString name)
{
	QSqlQuery query(QString("SELECT COUNT(*)\
							 FROM figures\
						     WHERE name = '%1'")
						     .arg(name));
	query.next();
	return query.value(0).toInt();
}

bool DataBase::isConnected(qint32 ind1, qint32 ind2)
{
	QSqlQuery query;
	query.exec(QString("SELECT connections, name\
						FROM figures\
						WHERE ind = %1")
						.arg(ind1));
	query.next();
	QString connectionText = query.value(0).toString();

	query.exec(QString("SELECT connections, name\
						FROM figures\
						WHERE ind = '%1'")
						.arg(ind2));
	query.next();
	QString name = " " + query.value(1).toString() + " ";

	return connectionText.contains(name);
}

void DataBase::connect(QString name1, QString name2)
{
	QSqlQuery query;
	query.exec(QString("SELECT connections\
						FROM figures\
						WHERE name = '%1'")
					    .arg(name1));
	query.next();
	QString connectionText1 = query.value(0).toString();

	query.exec(QString("SELECT connections\
						FROM figures\
						WHERE name = '%1'")
						.arg(name2));
	query.next();
	QString connectionText2 = query.value(0).toString();

	//”же соеденены
	if (connectionText1.contains(QString(" %1 ").arg(name2)) ||
		connectionText2.contains(QString(" %1 ").arg(name1)))
		return;

	if (connectionText1 == "No Connections")
		connectionText1.clear();
	if (connectionText2 == "No Connections")
		connectionText2.clear();

	connectionText1 = connectionText1 + QString(" %1 ").arg(name2);
	connectionText2 = connectionText2 + QString(" %1 ").arg(name1);

	query.exec(QString("UPDATE figures\
						    SET connections = '%1'\
						    WHERE name = '%2'")
							.arg(connectionText1)
							.arg(name1));
	query.exec(QString("UPDATE figures\
						    SET connections = '%1'\
						    WHERE name = '%2'")
							.arg(connectionText2)
							.arg(name2));
	model->select();
}

void DataBase::disConnect(qint32 ind1, qint32 ind2)
{
	QSqlQuery query;
	query.exec(QString("SELECT connections, name\
						FROM figures\
						WHERE ind = %1")
						.arg(ind1));
	query.next();
	QString connectionText1 = query.value(0).toString();
	QString name1 = query.value(1).toString();

	query.exec(QString("SELECT connections, name\
						FROM figures\
						WHERE ind = %1")
						.arg(ind2));
	query.next();
	QString connectionText2 = query.value(0).toString();
	QString name2 = query.value(1).toString();

	connectionText1.remove(" " + name2 + " ");
	connectionText2.remove(" " + name1 + " ");

	if (connectionText1.isEmpty())
		connectionText1 = "No Connections";
	if (connectionText2.isEmpty())
		connectionText2 = "No Connections";

	query.exec(QString("UPDATE figures\
						SET connections = '%1'\
						WHERE name = '%2'")
						.arg(connectionText1)
						.arg(name1));
	query.exec(QString("UPDATE figures\
						SET connections = '%1'\
						WHERE name = '%2'")
						.arg(connectionText2)
						.arg(name2));
	model->select();
}

void DataBase::deleteFigure(QString name)
{
	QSqlQuery query(QString("SELECT ind, figureType\
							 FROM figures\
						     WHERE name = '%1'")
							 .arg(name));
	query.next();
	qint32  ind = query.value(0).toInt();
	QString figureType = query.value(1).toString();

	qint32 amount = size();
	for (int i = 0; i < amount; i++)
	{
		if (i == ind)
			continue;
		if (isConnected(i, ind))
			disConnect(i, ind);
	}

	query.exec(QString("DELETE FROM figures\
						WHERE name = '%1';")
					    .arg(name));
	decrementIndexesFrom(ind);
	updateAmounts(figureType);

	model->select();
}

qint32 DataBase::size()
{
	QSqlQuery query(QString("SELECT COUNT(*) FROM figures"));
	query.next();
	return query.value(0).toInt();
}

void DataBase::pushBackFigure(qint32 index)
{
	QSqlQuery quary;
	quary.exec(QString("UPDATE figures\
						SET ind = -1\
					    WHERE ind = %1;")
						.arg(index));
	// “ак как изменили индекс одной фигуры, нужно изменить индексы остальных
	for (qint32 i = index - 1; i > -1; i--)
	{
		quary.exec(QString("UPDATE figures\
							SET ind = %1\
							WHERE ind = %2;")
					        .arg(i + 1)
						    .arg(i));
	}

	quary.exec(QString("UPDATE figures\
						SET ind = 0\
						WHERE ind = -1;"));
	model->select();
}


void DataBase::decrementIndexesFrom(qint32 index)
{
	QSqlQuery quary;
	qint32 amount = size();
	for (qint32 i = index + 1; i < amount + 1; i++)
		{
			quary.exec(QString("UPDATE figures\
								SET ind = '%1'\
								WHERE ind = '%2'")
								.arg(i - 1)
								.arg(i));
		}
}

void DataBase::updateAmounts(QString figureType)
{
	QSqlQuery query(QString("SELECT COUNT(*)\
							 FROM figures\
							 WHERE figureType = '%1'")
							 .arg(figureType));
	query.next();
	qint32 newAmount = query.value(0).toInt();
	query.exec(QString("UPDATE figures\
						SET amount = '%1'\
						WHERE figureType = '%2'")
						.arg(newAmount)
						.arg(figureType));
	model->select();
}
