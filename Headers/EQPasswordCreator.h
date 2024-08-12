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
#include <QListView>

class EQPasswordCreator : public QMainWindow
{
	Q_OBJECT

public:
	EQPasswordCreator();
	~EQPasswordCreator();

private slots:
	void addPassword(QString newPassword);
	void loadAlphabetDialog();
	void copyPassword();

private:
	static constexpr std::uint8_t MAX_SAVED_PASSWORDS{ 150 };
	inline static const QString ALPHABETS_DIR{ QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/Password-creator" };
	inline static const QString DEFAULT_ALPHABET_PATH{ ALPHABETS_DIR + "/all.txt" };

	void loadAlphabet(const QString& filePath);

	QGroupBox* initParameters();
	QHBoxLayout* initCharacterListLayout();
	QHBoxLayout* initPasswordLengthLayout();

	QVBoxLayout* initGenerator();

	

	QThread mWorkerThread;
	EQPasswordCreatorWorker* mPasswordCreatorWorker{ new EQPasswordCreatorWorker };

	QStringList mPasswordList;
	QStringList mDisplayedPasswordList;

	QLabel* mCharacterSetLabel;
	QStringListModel* mPasswordListModel;
	QListView* mPasswordsListView;
};