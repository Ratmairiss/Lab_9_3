#pragma once

#include <QtWidgets>
#include <QtSql>
#include <qdebug.h>

extern QMap <QString, QPicture(*)(qint32, qint32)> pictures;

class DataBase: public QObject {

	template <typename T>
	class Cell
	{
		qint32 columnIndToFind;   //Поле, по которому ищем
		T valToFind;              //Значение, по которому ищем
		QSqlTableModel* model;

		QString columnNames[8]{ "name",         "ind",   "figureType", 
							   "amount", "color", "lineColor", 
							   "isHidden", "connections"};

	public:

		Cell(qint32 columnIndToFind0,T valToFind0, 
			 QSqlTableModel* model0) :
			 columnIndToFind(columnIndToFind0), valToFind(valToFind0),
		     model(model0)
		{}

		template<typename U>
		U getVal(qint32 columnIndToGet)
		{
			return U();
		}

		template<>
		qint32 getVal<qint32>(qint32 columnIndToGet)
		{
			QSqlQuery query(QString("SELECT \"%1\" FROM figures WHERE \"%2\" = '%3';")
				.arg(columnNames[columnIndToGet])
				.arg(columnNames[columnIndToFind])
				.arg(valToFind));
			query.next();
			return query.value(0).toInt();
		}

		template<>
		QString getVal<QString>(qint32 columnIndToGet)
		{
			QSqlQuery query(QString("SELECT \"%1\" FROM figures WHERE \"%2\" = '%3';")
				.arg(columnNames[columnIndToGet])
				.arg(columnNames[columnIndToFind])
				.arg(valToFind));
			query.next();
			return query.value(0).toString();
		}

		template<>
		QColor getVal<QColor>(qint32 columnIndToGet)
		{
			QSqlQuery query(QString("SELECT \"%1\" FROM figures WHERE \"%2\" = '%3';")
				.arg(columnNames[columnIndToGet])
				.arg(columnNames[columnIndToFind])
				.arg(valToFind));
			query.next();
			qint32 colorCode = query.value(0).toInt();
			return QColor(colorCode / 1000000, (colorCode % 1000000) / 1000, colorCode % 1000);
		}

		template<typename U>
		U getVal()
		{
			return U();
		}

		template<>
		QPoint getVal<QPoint>()
		{
			QSqlQuery query(QString("SELECT posX, posY\
								    FROM figures\
								    WHERE \"%1\" = '%2'")
									.arg(columnNames[columnIndToFind])
									.arg(valToFind));
			query.next();
			return QPoint(query.value(0).toInt(), query.value(1).toInt());
		}

		template<>
		QPicture getVal<QPicture>()
		{
			QSqlQuery query(QString("SELECT figureType,width, height\
								    FROM figures\
								    WHERE \"%1\" = '%2'")
									.arg(columnNames[columnIndToFind])
									.arg(valToFind));
			query.next();
			return pictures[query.value(0).toString()](query.value(1).toInt(), query.value(2).toInt());
		}

		template<>
		QRect getVal<QRect>()
		{
			QSqlQuery query(QString("SELECT posX, posY, width, height\
								    FROM figures\
								    WHERE \"%1\" = '%2'")
									.arg(columnNames[columnIndToFind])
									.arg(valToFind));
			query.next();
			return QRect(query.value(0).toInt(), query.value(1).toInt(), 
						 query.value(2).toInt(), query.value(3).toInt());
		}

		template <typename U>
		void setVal(qint32 columnIndToSet, U val)
		{
			QSqlQuery query(QString("UPDATE figures\
									 SET \"%1\" = '%2'\
									 WHERE \"%3\" = '%4';")
									 .arg(columnNames[columnIndToSet])
									 .arg(QVariant(val).toString())
									 .arg(columnNames[columnIndToFind])
									 .arg(valToFind));
			model->select();
		}

		template<>
		void setVal<QColor>(qint32 columnIndToSet, QColor val)
		{
			QSqlQuery query(QString("UPDATE figures\
									 SET \"%1\" = '%2'\
									 WHERE \"%3\" = '%4';")
				.arg(columnNames[columnIndToSet])
				.arg(val.red() * 1000000 + val.green() * 1000 + val.blue())
				.arg(columnNames[columnIndToFind])
				.arg(valToFind));
			model->select();
		}
		
		QPoint getMiddlePos()
		{
			QSqlQuery query(QString("SELECT posX, posY, width, height\
									 FROM figures\
									 WHERE \"%1\" = '%2'")
									 .arg(columnNames[columnIndToFind])
									 .arg(valToFind));
			query.next();
			return QPoint(query.value(0).toInt() + (query.value(2).toInt() / 2),
				query.value(1).toInt() + (query.value(3).toInt() / 2));
		}

		void operator+= (qint32 val)
		{
			QString columnNameToFind = columnNames[columnIndToFind];
			QSqlQuery query(QString("SELECT width, height\
								 FROM figures\
								    WHERE \"%1\" = '%2'")
				.arg(columnNameToFind)
				.arg(valToFind));
			query.next();
			qint32 newWidth = query.value(0).toInt() + val;
			qint32 newHeight = query.value(1).toInt() + val;

			query.exec(QString("UPDATE figures\
					        SET width = %1\
                            WHERE \"%2\" = '%3'")
				.arg(newWidth)
				.arg(columnNameToFind)
				.arg(valToFind));

			query.exec(QString("UPDATE figures\
					        SET height = %1\
                            WHERE \"%2\" = '%3'")
				.arg(newHeight)
				.arg(columnNameToFind)
				.arg(valToFind));
		}

		void operator+= (QPoint point)
		{
			QString columnNameToFind = columnNames[columnIndToFind];
			QSqlQuery query(QString("SELECT posX, posY\
								 FROM figures\
								WHERE \"%1\" = '%2'")
				.arg(columnNameToFind)
				.arg(valToFind));
			query.next();
			qint32 currentPosX = query.value(0).toInt();
			qint32 currentPosY = query.value(1).toInt();

			query.exec(QString("UPDATE figures\
						    SET posX = '%1'\
						    WHERE \"%2\" = '%3'")
				.arg(currentPosX + point.x())
				.arg(columnNameToFind)
				.arg(valToFind));
			query.exec(QString("UPDATE figures\
						    SET posY = '%1'\
						    WHERE \"%2\" = '%3'")
				.arg(currentPosY + point.y())
				.arg(columnNameToFind)
				.arg(valToFind));
			model->select();
		}

	};

public:

	QSqlTableModel* model;
	QSqlDatabase    db;

	enum { Name, Ind, FigureType, FigureAmount, Color, LineColor, IsHidden, Connections };

	DataBase(QObject* pt);

	void addFigure(QString name, QString figureType, qint32 posX,  qint32 posY, 
				   qint32  width, qint32 height,     qint32 color, qint32 lineColor);
	void deleteFigure(QString name);
	void pushBackFigure(qint32 index);
	  
	template<typename T>
	Cell<T> operator() (qint32 columnIndToFind0, T valToFind0)
	{
		return Cell(columnIndToFind0, valToFind0, model);
	}

	bool isFigureExists(QString name);
	bool isConnected(qint32 ind1, qint32 ind2);

	void connect(QString name1, QString name2);
	void disConnect(qint32 ind1, qint32 ind2);

	qint32 size();

private:

	void decrementIndexesFrom(qint32 ind);

	void updateAmounts(QString figureType);

};
