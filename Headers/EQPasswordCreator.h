#pragma once

#include <QMainWindow>
#include <QString>
#include <QThread>
#include "EQPasswordCreatorWorker.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QStringListModel>
#include <QStandardPaths>

class EQPasswordCreator : public QMainWindow
{
	Q_OBJECT

public:
	EQPasswordCreator();
	~EQPasswordCreator();

public slots:
	void addPassword(const QString& newPassword);

private:
	static constexpr std::uint8_t MAX_SAVED_PASSWORDS{ 10 };
	inline static const QString ALPHABETS_DIR{ QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Password-creator" };
	inline static const QString DEFAULT_ALPHABET_PATH{ ALPHABETS_DIR + "/all.txt" };

	void loadAlphabet(const QString& filePath);

	QGroupBox* initParameters();
	QVBoxLayout* initGenerator();

	QThread workerThread;
	EQPasswordCreatorWorker* passwordCreatorWorker{ new EQPasswordCreatorWorker };

	QLabel* characterSetText;
	QStringList realPasswordList;
	QStringListModel* passwordsListModel;
};
