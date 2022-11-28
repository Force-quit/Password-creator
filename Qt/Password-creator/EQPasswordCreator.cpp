#include "EQPasswordCreator.h"
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QGroupBox>
#include "../../Utilities/EQUIRangedLineEdit.h"
#include <QFileDialog>

EQPasswordCreator::EQPasswordCreator(QWidget *parent)
	: QMainWindow(parent), workerThread(), passwordCreatorWorker()
{
	passwordCreatorWorker = new EQPasswordCreatorWorker(this);
	QWidget* centralWidget{ new QWidget };
	QHBoxLayout* centalLayout{ new QHBoxLayout };

	QGroupBox* parameters = initParameters();

	

	centalLayout->addWidget(parameters);
	centralWidget->setLayout(centalLayout);
	setCentralWidget(centralWidget);
	setWindowIcon(QIcon("gears.png"));
}

QGroupBox* EQPasswordCreator::initParameters()
{
	QGroupBox* parameters{ new QGroupBox("Parameters") };
	QVBoxLayout* parametersLayout{ new QVBoxLayout };

	QHBoxLayout* alphabetLayout{ new QHBoxLayout };
	QLabel* alphabetLabel{ new QLabel("Alphabet :") };
	alphabetText = new QLabel;
	QPushButton* changeAlphabetButton{ new QPushButton("Change") };
	alphabetLayout->addWidget(alphabetLabel);
	alphabetLayout->addWidget(alphabetText);
	alphabetLayout->addWidget(changeAlphabetButton);

	QHBoxLayout* passwordLengthLayout{ new QHBoxLayout };
	QLabel* passwordLengthLabel{ new QLabel("Password length :") };
	EQUIRangedLineEdit* passwordLengthLineEdit{ new EQUIRangedLineEdit(0, UINT_MAX) };
	passwordLengthLayout->addWidget(passwordLengthLabel);
	passwordLengthLayout->addWidget(passwordLengthLineEdit);

	parametersLayout->addLayout(alphabetLayout);
	parametersLayout->addLayout(passwordLengthLayout);
	parameters->setLayout(parametersLayout);

	connect(changeAlphabetButton, &QPushButton::clicked, [this]() {
		QString filePath = QFileDialog::getOpenFileName(this, "Select character list", ALPHABETS_DIR, "text files (*.txt)");
		if (!filePath.isEmpty())
			loadAlphabet(filePath);
	});

	return parameters;
}

void EQPasswordCreator::loadAlphabet(const QString& filePath)
{
	passwordCreatorWorker->loadAlphabet(filePath);
	alphabetText->setText(filePath);
}

EQPasswordCreator::~EQPasswordCreator()
{}