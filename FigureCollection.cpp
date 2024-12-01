
#include "FigureCollection.h"

FigureCollection::FigureCollection(QWidget* pt) : QWidget(pt)
{
	panel			  = new TopPanel;
	view		      = new QTableView;
	hideFigureBtn	  = new QPushButton("Hide");
	hideFigureTypeBtn = new QPushButton("Hide");
	showAllRowsBtn	  = new QPushButton("Show all Figures");
	canv              = new Canvas(dataBase);

	canv                 ->setMinimumHeight(300);
	hideFigureBtn        ->setMinimumHeight(25);
	hideFigureTypeBtn    ->setMinimumHeight(25);
	showAllRowsBtn       ->setMinimumHeight(25);
	panel->creationButton->setMinimumHeight(65);

	view->setMinimumWidth(445);

	QFont font = hideFigureBtn->font();
	font.setPointSize(11);
	hideFigureBtn    ->setFont(font);
	hideFigureTypeBtn->setFont(font);
	showAllRowsBtn   ->setFont(font);

	view->setModel(dataBase.model);
	view->hideColumn(3);
	view->hideColumn(4);
	view->setItemDelegate(new FigureDelegate);
	view->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QGridLayout* mainLayout = new QGridLayout;
	mainLayout->addWidget(panel, 0, 0, 3, 1);
	mainLayout->addWidget(canv, 3, 0);
	mainLayout->addWidget(hideFigureBtn, 0, 1);
	mainLayout->addWidget(hideFigureTypeBtn, 1, 1);
	mainLayout->addWidget(showAllRowsBtn, 2, 1);
	mainLayout->addWidget(view, 3, 1);

	mainLayout->setRowStretch(1, 1);
	mainLayout->setColumnStretch(0, 1);

	this->setLayout(mainLayout);

	connect(panel->creationButton, &QPushButton::clicked,
		this, &FigureCollection::addFigure);

	connect(hideFigureBtn,     &QPushButton::clicked, this, &FigureCollection::hideFigure);
	connect(hideFigureTypeBtn, &QPushButton::clicked, this, &FigureCollection::hideFiguresWithType);
	connect(showAllRowsBtn,    &QPushButton::clicked, this, &FigureCollection::showAllRows);

	connect(canv, &Canvas::figIsSelected, this, &FigureCollection::updateHideFigureBtn);
	connect(canv, &Canvas::figTypeIsSelected, this, &FigureCollection::updateHideFigureTypeBtn);
}