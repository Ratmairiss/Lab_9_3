#pragma once

#include <QtWidgets>

extern QMap <QString, QPicture(*)(qint32, qint32)> pictures;


class MiniCanvas : public QWidget
{
	Q_OBJECT

public:

	QColor   color;
	QPicture pict;

	MiniCanvas(QWidget* pt = 0) : QWidget(pt)
	{
		setObjectName("MiniCanvas");
	}

protected:

	virtual void paintEvent(QPaintEvent* eventPt) override
	{
		QPainter painter(this);
		
		painter.fillRect(rect(), palette().window().color());

		painter.setPen(Qt::black);
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setBrush(QBrush(color, Qt::SolidPattern));

		painter.drawPicture(10, 20, pict);
	}
};


////////////////////////////////////////////////////////////////////////////////////


class TopPanel : public QWidget
{
	Q_OBJECT

	MiniCanvas*     miniCanvas;

public:

	QPushButton* creationButton;
	QSpinBox*	 redSpinBox;
	QSpinBox*	 greenSpinBox;
	QSpinBox*	 blueSpinBox;
	QComboBox*	 figureComboBox;
	QLineEdit*   nameLineEdit;

	TopPanel(QWidget* pt = 0);

	void autoChangeNameEdit();

public slots:

	void updateMiniCanvas()
	{
		miniCanvas->color = QColor(redSpinBox->value(), 
			                           greenSpinBox->value(),
			                           blueSpinBox->value());
		miniCanvas->pict = pictures[figureComboBox->currentText()](50, 30);

		miniCanvas->update();
	}

};

