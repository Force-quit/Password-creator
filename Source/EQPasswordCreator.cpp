#include "../Headers/EQPasswordCreator.h"
#include "../Headers/EQPasswordCreatorWorker.h"
#include <QMainWindow>
#include <QBoxLayout>
#include <QGroupBox>
#include <QIcon>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <EQUtilities/EQIntLineEdit.h>
#include <QString>
#include <QFileDialog>
#include <QListView>
#include <QStringListModel>
#include <QThread>
#include <QGUIApplication>
#include <QClipboard>
#include <QDir>
#include <QMessageBox>
#include <QStringList>

EQPasswordCreator::EQPasswordCreator()
{
	auto* centralWidget{ new QWidget };
	setCentralWidget(centralWidget);

	auto* centalLayout{ new QHBoxLayout };
	centralWidget->setLayout(centalLayout);

	centalLayout->addWidget(initParameters());
	centalLayout->addLayout(initGenerator());

	if (QFile::exists(DEFAULT_ALPHABET_PATH))
	{
		loadAlphabet(DEFAULT_ALPHABET_PATH);
	}

	setWindowIcon(QIcon(":/images/appIcon.png"));
}

QGroupBox* EQPasswordCreator::initParameters()
{
	auto* parameters{ new QGroupBox("Parameters") };
	auto* parametersLayout{ new QVBoxLayout };

	auto* characterSetLayout{ new QHBoxLayout };
	auto* characterSetLabel{ new QLabel("Character list :") };
	characterSetText = new QLabel;
	auto* characterSetButton{ new QPushButton("Change") };
	characterSetLayout->addWidget(characterSetLabel);
	characterSetLayout->addWidget(characterSetText);
	characterSetLayout->addWidget(characterSetButton);

	auto* passwordLengthLayout{ new QHBoxLayout };
	auto* passwordLengthLabel{ new QLabel("Password length :") };
	auto* passwordLengthLineEdit{ new EQIntLineEdit(0, EQPasswordCreatorWorker::MAX_PASSWORD_LENGTH, 25) };
	passwordLengthLineEdit->setText(QString::number(EQPasswordCreatorWorker::DEFAULT_PASSWORD_LENGTH));
	passwordLengthLayout->addWidget(passwordLengthLabel);
	passwordLengthLayout->addWidget(passwordLengthLineEdit);

	parametersLayout->addLayout(characterSetLayout);
	parametersLayout->addLayout(passwordLengthLayout);
	parameters->setLayout(parametersLayout);

	connect(characterSetButton, &QPushButton::clicked, this, &EQPasswordCreator::loadAlphabetDialog);
	connect(passwordLengthLineEdit, &EQIntLineEdit::valueChanged, passwordCreatorWorker, &EQPasswordCreatorWorker::setPasswordLength);
	return parameters;
}

QVBoxLayout* EQPasswordCreator::initGenerator()
{
	auto* generatorLayout{ new QVBoxLayout };

	passwordsListView = new QListView;
	passwordsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	passwordsListModel = new QStringListModel;
	passwordsListView->setModel(passwordsListModel);

	auto* generateButton{ new QPushButton("Generate") };
	auto* copyButton{ new QPushButton("Copy") };

	generatorLayout->addWidget(passwordsListView);
	generatorLayout->addWidget(generateButton);
	generatorLayout->addWidget(copyButton);

	connect(generateButton, &QPushButton::clicked, passwordCreatorWorker, &EQPasswordCreatorWorker::generatePassword);
	connect(passwordCreatorWorker, &EQPasswordCreatorWorker::passwordGenerated, this, &EQPasswordCreator::addPassword);
	connect(copyButton, &QPushButton::clicked, this, &EQPasswordCreator::copyPassword);

	connect(&workerThread, &QThread::finished, passwordCreatorWorker, &QObject::deleteLater);
	passwordCreatorWorker->moveToThread(&workerThread);
	workerThread.start();

	return generatorLayout;
}

void EQPasswordCreator::loadAlphabet(const QString& filePath)
{
	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		passwordCreatorWorker->loadAlphabet(file);
		characterSetText->setText(QDir(QDir::homePath()).relativeFilePath(filePath));
	}
	else
	{
		QMessageBox::critical(this, "File error", "Error reading file " + filePath);
	}
}

void EQPasswordCreator::addPassword(QString newPassword)
{
	passwordList.append(newPassword);

	if (newPassword.length() > 30)
	{
		newPassword = newPassword.left(15) + " [...] " + newPassword.right(15);
	}
	displayedPasswordList.append(newPassword);

	if (passwordList.length() > MAX_SAVED_PASSWORDS)
	{
		passwordList.removeFirst();
		displayedPasswordList.removeFirst();
	}

	passwordsListModel->setStringList(displayedPasswordList);
}

void EQPasswordCreator::loadAlphabetDialog()
{
	QFileDialog dialog(this);
	dialog.setWindowTitle("Select character list");
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter("Text files (*.txt)");
	dialog.setDirectory(ALPHABETS_DIR);

	if (dialog.exec())
	{
		loadAlphabet(dialog.selectedFiles().first());
	}
}

void EQPasswordCreator::copyPassword()
{
	int wSelectedRow{ passwordsListView->currentIndex().row() };

	if (wSelectedRow != -1)
	{
		QGuiApplication::clipboard()->setText(passwordList[wSelectedRow]);
	}
	else
	{
		QMessageBox::warning(this, "", "Please select a password to copy");
	}
}

EQPasswordCreator::~EQPasswordCreator()
{
	workerThread.quit();
	workerThread.wait();
}