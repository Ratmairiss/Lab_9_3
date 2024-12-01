#pragma once

#include <QStyledItemDelegate>
#include <QPainter>

extern QMap <QString, QPicture(*)(qint32, qint32)> pictures;

class FigureDelegate : public QStyledItemDelegate {

    Q_OBJECT

public:
    explicit FigureDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override {
        if (index.column() == 5) { 
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing, true);

            QPen pen(Qt::black);
            pen.setWidth(1);
            painter->setPen(pen);
            painter->setBrush(Qt::red);

            qint32 posX = option.rect.x() + 5;
            qint32 posY = option.rect.y() + 5;
            qint32 amount   = index.siblingAtColumn(3).data().toInt();
            QString figType = index.siblingAtColumn(4).data().toString();
            if (amount <= 3)
            {
                painter->drawPicture(QPoint(posX, posY), pictures[figType](30, 20));
            }
            else if ((4 <= amount) && (amount <= 10))
            {
                painter->drawPicture(QPoint(posX, posY), pictures[figType](30, 20));
                painter->drawPicture(QPoint(posX + 35, posY), pictures[figType](30, 20));
            }
            else
            {
                painter->drawPicture(QPoint(posX, posY), pictures[figType](30, 20));
                painter->drawPicture(QPoint(posX + 35, posY), pictures[figType](30, 20));
                painter->drawPicture(QPoint(posX + 70, posY), pictures[figType](30, 20));
            }

            painter->restore();
        }
        else {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
};
