
#include "Canvas.h"

Canvas::Canvas(DataBase& dataBase0, QWidget* pt) : dataBase(dataBase0), QWidget(pt)
{
    setObjectName("Canvas");
    this->setFocusPolicy(Qt::StrongFocus);
}

Canvas::~Canvas()
{
    if (!selectedFigureName.isEmpty())
    {
        dataBase(DataBase::Name, selectedFigureName).setVal(DataBase::LineColor, 0);
    }
}	

//////////////////////////////////////////////////////////////////////////////////////////

void Canvas::paintEvent(QPaintEvent* eventPt)
{
    QPainter painter(this);
    painter.fillRect(rect(), palette().window().color());
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen;
    pen.setWidth(2);

    //Отрисовка связей (линий) между фигурами
    pen.setColor(Qt::blue);
    painter.setPen(pen);

    qint32 amount = dataBase.size();

    //Собираем все соединения
    QMap<QString, QStringList> connections;
    for (int i1 = amount - 1; i1 > -1; i1--)
    {
        QString connectionText = dataBase(DataBase::Ind, i1).getVal<QString>(DataBase::Connections);
        if (connectionText == "No Connections")
            continue;
        connections.insert(dataBase(DataBase::Ind, i1).getVal<QString>(DataBase::Name),
            connectionText.split(" ", Qt::SkipEmptyParts));
    }

    //Рисуем линии попутно удаляя уже нарисованные соединения
    for (auto it = connections.begin(); it != connections.end(); it++)
    {
        for (int i = 0; i < it.value().size(); i++)
        {
            //Удаление
            QStringList& tmp = connections[it.value()[i]];
            tmp.removeAt(tmp.indexOf(it.key()));

            //Отрисовка
            painter.drawLine(dataBase(DataBase::Name, it.key()).getMiddlePos(),
                dataBase(DataBase::Name, it.value()[i]).getMiddlePos());
        }
    }

    //Отрисовка фигур
    for (int i = amount - 1; i > -1; i--)
    {
        pen.setColor(dataBase(DataBase::Ind, i).getVal<QColor>(DataBase::LineColor));
        painter.setPen(pen);
        painter.setBrush(QBrush(dataBase(DataBase::Ind, i).getVal<QColor>(DataBase::Color), Qt::SolidPattern));
        painter.drawPicture(dataBase(DataBase::Ind, i).getVal<QPoint>(),
            dataBase(DataBase::Ind, i).getVal<QPicture>());
    }

    QWidget::paintEvent(eventPt);
}


void Canvas::keyPressEvent(QKeyEvent* eventPt) 
{
    if ((eventPt->key() == Qt::Key_Delete) && (!selectedFigureName.isEmpty()))
    {
        dataBase.deleteFigure(selectedFigureName);
        selectedFigureName.clear();
        update();

        emit figIsSelected();
        emit figTypeIsSelected();
    }
}


void Canvas::mousePressEvent(QMouseEvent* eventPt)
{
    prevMousePos = eventPt->pos();

    qint32 amount = dataBase.size();
    for (int i = amount - 1; i > -1; i--)
    {
        if (dataBase(DataBase::Ind, i).getVal<QRect>().contains(prevMousePos))
        {
            if (eventPt->modifiers() & Qt::ShiftModifier)
            {
                // Никакая фигура не выбрана
                if (selectedFigureName.isEmpty())
                {
                    selectedFigureName = dataBase(DataBase::Ind, i).getVal<QString>(DataBase::Name);
                    dataBase(DataBase::Name, selectedFigureName).setVal(DataBase::LineColor, QColor(255, 0, 0));

                    emit figIsSelected(selectedFigureName);
                    emit figTypeIsSelected(dataBase(DataBase::Ind, i).getVal<QString>(DataBase::FigureType));
                }
                // Другая фигура выбрана и нужно соединить с новой
                else if (selectedFigureName != dataBase(DataBase::Ind, i).getVal<QString>(DataBase::Name))
                {
                    dataBase.connect(selectedFigureName, 
                                     dataBase(DataBase::Ind, i).getVal<QString>(DataBase::Name));
                    dataBase(DataBase::Name, selectedFigureName).setVal(DataBase::LineColor, 0);
                    selectedFigureName.clear();

                    emit figIsSelected();
                    emit figTypeIsSelected();
                }
            }

            isHolding = 1;
            dataBase.pushBackFigure(i);

            update();
            return;
        }
    }

    // Нажали на фон => Если до этого была выбрана фигура нужно сделать её не выбранной
    if (!selectedFigureName.isEmpty())
    {
        dataBase(DataBase::Name, selectedFigureName).setVal(DataBase::LineColor, 0);
        selectedFigureName.clear();

        emit figIsSelected();
        emit figTypeIsSelected();
    }

    update();
}


void Canvas::mouseMoveEvent(QMouseEvent* eventPt)
{
    if (isHolding && (QRect(QPoint(0, 0), this->size()).contains(eventPt->pos())))
    {
        dataBase(DataBase::Ind, 0) += eventPt->pos() - prevMousePos;
        prevMousePos = eventPt->pos();
        update();
    }
}


void Canvas::mouseReleaseEvent(QMouseEvent* eventPt)
{
    isHolding = 0;
}


void Canvas::wheelEvent(QWheelEvent* eventPt)
{
    if (isHolding)
        dataBase(DataBase::Ind, 0) += -(eventPt->angleDelta().y() / 120);
}


