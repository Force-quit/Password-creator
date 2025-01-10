#include "EQPasswordCreator.hpp"
#include "EQPasswordCreatorWorker.hpp"
#include <EQIntLineEdit.hpp>
#include <QBoxLayout>
#include <QClipboard>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QGroupBox>
#include <QGUIApplication>
#include <QIcon>
#include <QLabel>
#include <QListView>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QStringListModel>
#include <QThread>

EQPasswordCreator::EQPasswordCreator()
{
	auto* wCentralWidget{ new QWidget };
	setCentralWidget(wCentralWidget);

	auto* wCentalLayout{ new QVBoxLayout };
	wCentralWidget->setLayout(wCentalLayout);

	wCentalLayout->addWidget(initParameters());
	wCentalLayout->addLayout(initGenerator());

	if (QFile::exists(DEFAULT_ALPHABET_PATH))
	{
		loadAlphabet(DEFAULT_ALPHABET_PATH);
	}

	setWindowIcon(QIcon(":/images/icon.png"));
}

QGroupBox* EQPasswordCreator::initParameters()
{
	auto* wParametersGroupBox{ new QGroupBox(tr("Parameters")) };

	auto* wParametersLayout{ new QVBoxLayout };
	wParametersGroupBox->setLayout(wParametersLayout);

	wParametersLayout->addLayout(initCharacterListLayout());
	wParametersLayout->addLayout(initPasswordLengthLayout());

	return wParametersGroupBox;
}

QHBoxLayout* EQPasswordCreator::initCharacterListLayout()
{
	auto* wCharacterSetLayout{ new QHBoxLayout };
	
	auto* wCharacterSetLabel{ new QLabel(tr("Character set :")) };
	wCharacterSetLayout->addWidget(wCharacterSetLabel);
	
	mCharacterSetLabel = new QLabel;
	wCharacterSetLayout->addWidget(mCharacterSetLabel);
	
	auto* wCharacterSetButton{ new QPushButton(tr("Change")) };
	wCharacterSetLayout->addWidget(wCharacterSetButton);

	connect(wCharacterSetButton, &QPushButton::clicked, this, &EQPasswordCreator::loadAlphabetDialog);

	return wCharacterSetLayout;
}

QHBoxLayout* EQPasswordCreator::initPasswordLengthLayout()
{
	auto* wPasswordLengthLayout{ new QHBoxLayout };

	auto* wPasswordLengthLabel{ new QLabel(tr("Password length :")) };
	wPasswordLengthLayout->addWidget(wPasswordLengthLabel);

	auto* wPasswordLengthLineEdit{ new EQIntLineEdit(0, EQPasswordCreatorWorker::MAX_PASSWORD_LENGTH, EQPasswordCreatorWorker::DEFAULT_PASSWORD_LENGTH) };
	wPasswordLengthLayout->addWidget(wPasswordLengthLineEdit);

	connect(wPasswordLengthLineEdit, &EQIntLineEdit::valueChanged, mPasswordCreatorWorker, &EQPasswordCreatorWorker::setPasswordLength);

	return wPasswordLengthLayout;
}

QVBoxLayout* EQPasswordCreator::initGenerator()
{
	auto* wGeneratorLayout{ new QVBoxLayout };

	auto* wGenerateButton{ new QPushButton(tr("Generate")) };
	wGeneratorLayout->addWidget(wGenerateButton);

	auto* wCopyButton{ new QPushButton(tr("Copy")) };
	wGeneratorLayout->addWidget(wCopyButton);

	mPasswordsListView = new QListView;
	mPasswordsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	wGeneratorLayout->addWidget(mPasswordsListView);
	
	mPasswordListModel = new QStringListModel;
	mPasswordsListView->setModel(mPasswordListModel);


	connect(wGenerateButton, &QPushButton::clicked, mPasswordCreatorWorker, &EQPasswordCreatorWorker::generatePassword);
	connect(mPasswordCreatorWorker, &EQPasswordCreatorWorker::passwordGenerated, this, &EQPasswordCreator::addPassword);
	connect(wCopyButton, &QPushButton::clicked, this, &EQPasswordCreator::copyPassword);

	connect(&mWorkerThread, &QThread::finished, mPasswordCreatorWorker, &QObject::deleteLater);
	mPasswordCreatorWorker->moveToThread(&mWorkerThread);
	mWorkerThread.start();

	return wGeneratorLayout;
}

void EQPasswordCreator::loadAlphabet(const QString& iFilePath)
{
	QFile wFile(iFilePath);
	if (wFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		mPasswordCreatorWorker->loadAlphabet(wFile);
		mCharacterSetLabel->setText(QDir(QDir::homePath()).relativeFilePath(iFilePath));
	}
	else
	{
		QMessageBox::critical(this, tr("File error"), tr("Error reading file ") + iFilePath);
	}
}

void EQPasswordCreator::addPassword(QString iNewPassword)
{
	mPasswordList.append(iNewPassword);

	if (iNewPassword.length() > 30)
	{
		iNewPassword = iNewPassword.left(15) + " [...] " + iNewPassword.right(15);
	}
	mDisplayedPasswordList.append(iNewPassword);

	if (mPasswordList.length() > MAX_SAVED_PASSWORDS)
	{
		mPasswordList.removeFirst();
		mDisplayedPasswordList.removeFirst();
	}

	mPasswordListModel->setStringList(mDisplayedPasswordList);
}

void EQPasswordCreator::loadAlphabetDialog()
{
	QFileDialog wDialog(this);
	wDialog.setWindowTitle(tr("Select character list"));
	wDialog.setFileMode(QFileDialog::ExistingFile);
	wDialog.setNameFilter(tr("Text files (*.txt)"));
	wDialog.setDirectory(ALPHABETS_DIR);

	if (wDialog.exec())
	{
		loadAlphabet(wDialog.selectedFiles().first());
	}
}

void EQPasswordCreator::copyPassword()
{
	int wSelectedRow{ mPasswordsListView->currentIndex().row() };

	if (wSelectedRow != -1)
	{
		QGuiApplication::clipboard()->setText(mPasswordList[wSelectedRow]);
	}
	else
	{
		QMessageBox::warning(this, "", tr("Please select a password to copy"));
	}
}

EQPasswordCreator::~EQPasswordCreator()
{
	mWorkerThread.quit();
	mWorkerThread.wait();
}