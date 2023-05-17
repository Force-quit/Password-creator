#pragma once

#include <QMainWindow>
#include <QString>
#include <QThread>
#include "EQPasswordCreatorWorker.h"
#include <QStringList>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QStringListModel>

class EQPasswordCreator : public QMainWindow
{
	Q_OBJECT

public:
	EQPasswordCreator(QWidget *parent = nullptr);
	~EQPasswordCreator();

public slots:
	void updatePasswordList(const QString& newPassword);

private:
	const ushort MAX_SAVED_PASSWORDS;
	const QString APP_PATH;
	const QString ALPHABETS_DIR;
	const QString DEFAULT_ALPHABET_PATH;

	QThread workerThread;
	EQPasswordCreatorWorker* passwordCreatorWorker;
	QStringList realPasswordList;
	QLabel* characterSetText;
	QStringListModel* passwordsListModel;

	QGroupBox* initParameters();
	QVBoxLayout* initGenerator();
	
	void loadAlphabet(const QString& filePath);
};
