#pragma once

#include <QtWidgets>
#include "DataBase.h"

class Canvas : public QWidget
{
	Q_OBJECT

	QPoint prevMousePos;
    bool   isHolding = 0;

public:

    QString   selectedFigureName;
    DataBase& dataBase;

    Canvas(DataBase& dataBase0, QWidget* pt = 0);
    ~Canvas();

protected:

    virtual void paintEvent        (QPaintEvent* eventPt) override;
    virtual void keyPressEvent     (QKeyEvent* eventPt)   override;
    virtual void mousePressEvent   (QMouseEvent* eventPt) override;
    virtual void mouseMoveEvent    (QMouseEvent* eventPt) override;
    virtual void mouseReleaseEvent (QMouseEvent* eventPt) override;
    virtual void wheelEvent        (QWheelEvent* eventPt) override;

    signals:

    void figIsSelected    (QString name = "");
    void figTypeIsSelected(QString figType = "");

};
