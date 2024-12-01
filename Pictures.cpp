
#include <QtWidgets>

QMap <QString, QPicture(*)(qint32, qint32)> pictures{
{"Rectangle",
[](qint32 width,qint32 height)
{ QPicture pict;
  QPainter painter(&pict);
  painter.drawRect(0, 0, width, height);
  return pict; }},
{"Ellipse",
[](qint32 width,qint32 height)
{ QPicture pict;
  QPainter painter(&pict);
  painter.drawEllipse(0, 0, width, height);
  return pict; }},
{"Triangle",
[](qint32 width,qint32 height)
{ QPicture pict;
  QPainter painter(&pict);
  QPolygon pol;
  pol << QPoint(0,height) << QPoint(width / 2,0) << QPoint(width,height);
  painter.drawPolygon(pol);
  return pict; }},
{"Pentagon",
[](qint32 width,qint32 height)
{ QPicture pict;
  QPainter painter(&pict);
  QPolygon pol;
  pol << QPoint(0,         height / 2) << QPoint(width / 2,       0) 
	  << QPoint(width,     height / 2) << QPoint((width / 4) * 3, height) 
	  << QPoint(width / 4, height);
  painter.drawPolygon(pol);
  return pict; }},
{"Hexagon",
[](qint32 width,qint32 height)
{ QPicture pict;
  QPainter painter(&pict);
  QPolygon pol;
  pol << QPoint(0,               height / 2) << QPoint(width / 4, 0) 
	  << QPoint((width / 4) * 3, 0)          << QPoint(width,     height / 2) 
	  << QPoint((width / 4) * 3, height)     << QPoint(width / 4, height);
  painter.drawPolygon(pol);
  return pict; }},
};

									    