#pragma once

#include <QtWidgets>
#include <QtSql>
#include "TopPanel.h"
#include "Canvas.h"
#include "DataBase.h"
#include "Delegate.h"

class FigureCollection : public QWidget
{
	Q_OBJECT

	TopPanel*		panel;
	Canvas*			canv;
	QTableView*     view;
	QPushButton*    hideFigureBtn;
	QPushButton*	hideFigureTypeBtn;
	QPushButton*    showAllRowsBtn;

	DataBase& dataBase = *(new DataBase(this));

public:

	FigureCollection(QWidget* pt = 0);

protected slots:

	void addFigure()
	{
		QString newFigureName = panel->nameLineEdit->text();
		newFigureName.remove(" ");

		if (dataBase.isFigureExists(newFigureName))
		{
			QMessageBox::warning(this, "Cant create figure", QString("Figure with name %1 alredy exists").arg(newFigureName));
			return;
		}

		dataBase.addFigure(newFigureName,panel->figureComboBox->currentText(), 150, 100, 100, 50,
							panel->redSpinBox->value() * 1000000 + panel->greenSpinBox->value() * 1000 + panel->blueSpinBox->value(),
							0);

		panel->autoChangeNameEdit();
		canv->update();
	}

	void showAllRows()
	{
		qint32 amount = dataBase.size();
		for (qint32 i = 0; i < amount; i++)
		{
			dataBase(DataBase::Ind, i).setVal(DataBase::IsHidden, 0);
		}
	}

	void updateHideFigureBtn(QString name)
	{
		hideFigureBtn->setText("Hide " + name);
	}

	void updateHideFigureTypeBtn(QString figType)
	{
		hideFigureTypeBtn->setText("Hide " + figType);
	}

	void hideFigure()
	{
		QString name = hideFigureBtn->text().remove("Hide ");
		if (name.isEmpty())
			return;
		
		dataBase(DataBase::Name, name).setVal(DataBase::IsHidden, 1);
	}

	void hideFiguresWithType()
	{
		QString figType = hideFigureTypeBtn->text().remove("Hide ");
		if (figType.isEmpty())
			return;

		qint32 amount = dataBase.size();
		for (qint32 i = 0; i < amount; i++)
		{
			if (dataBase(DataBase::Ind,i).getVal<QString>(DataBase::FigureType) == figType)
				dataBase(DataBase::Ind, i).setVal(DataBase::IsHidden, 1);
		}
	}

};
