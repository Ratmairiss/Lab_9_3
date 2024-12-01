
#include "TopPanel.h"

TopPanel::TopPanel(QWidget* pt) : QWidget(pt)
{
	creationButton = new QPushButton;
	figureComboBox = new QComboBox;
	miniCanvas     = new MiniCanvas;
	redSpinBox     = new QSpinBox;
	greenSpinBox   = new QSpinBox;
	blueSpinBox    = new QSpinBox;
	nameLineEdit   = new QLineEdit("Figure0");

	creationButton ->setMinimumSize(100, 50);
	figureComboBox ->setMinimumSize(100, 35);
	miniCanvas	   ->setMinimumSize(70, 50);
	redSpinBox	   ->setMinimumSize(50, 30);
	greenSpinBox   ->setMinimumSize(50, 30);
	blueSpinBox    ->setMinimumSize(50, 30);
	figureComboBox ->setMaximumHeight(35);
	nameLineEdit   ->setMinimumHeight(20);

	creationButton->setText("Create\nFigure");
	figureComboBox->addItems(QStringList{ "Rectangle","Ellipse","Triangle","Pentagon","Hexagon" });
	redSpinBox  ->setRange(0, 255);
	greenSpinBox->setRange(0, 255);
	blueSpinBox ->setRange(0, 255);

	QHBoxLayout* mainLayout   = new QHBoxLayout;
	QVBoxLayout* vColorLayout = new QVBoxLayout;
	QHBoxLayout* hColorLayout = new QHBoxLayout;
	QVBoxLayout* figureLayout = new QVBoxLayout;

	mainLayout->addWidget(creationButton);
	mainLayout->addLayout(figureLayout);
	mainLayout->addWidget(miniCanvas);
	mainLayout->addLayout(vColorLayout);
	mainLayout->addStretch(1);

	figureLayout->addWidget(nameLineEdit);
	figureLayout->addWidget(figureComboBox);

	QLabel* rgbText = new QLabel("  R         G         B   ");

	QFont font = creationButton->font();
	font.setPointSize(16);
	creationButton->setFont(font);
	rgbText->setFont(font);
	font.setPointSize(11);
	redSpinBox->setFont(font);
	greenSpinBox->setFont(font);
	blueSpinBox->setFont(font);
	figureComboBox->setFont(font);

	vColorLayout->addWidget(rgbText);
	vColorLayout->addLayout(hColorLayout);

	hColorLayout->addWidget(redSpinBox);
	hColorLayout->addWidget(greenSpinBox);
	hColorLayout->addWidget(blueSpinBox);

	updateMiniCanvas();

	this->setLayout(mainLayout);

	connect(redSpinBox,     &QSpinBox::valueChanged,        this, &TopPanel::updateMiniCanvas);
	connect(greenSpinBox,   &QSpinBox::valueChanged,        this, &TopPanel::updateMiniCanvas);
	connect(blueSpinBox,    &QSpinBox::valueChanged,        this, &TopPanel::updateMiniCanvas);
	connect(figureComboBox, &QComboBox::currentTextChanged, this, &TopPanel::updateMiniCanvas);
}

void TopPanel::autoChangeNameEdit()
{
	QString name = nameLineEdit->text();
	if (QRegularExpression("^Figure\\d+$").match(name).hasMatch())
	{
		qint32 num = name.remove("Figure").toInt();
		nameLineEdit->setText("Figure" + QString::number(num + 1));
	}
	else
		nameLineEdit->setText(name + "0");
}