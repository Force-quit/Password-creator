#pragma once

#include <QObject>
#include <QString>
#include <QVector>
#include <QChar>
#include <QFile>

class EQPasswordCreatorWorker : public QObject
{
	Q_OBJECT

public:
	void loadAlphabet(QFile& iOpennedFile);

	static constexpr std::uint16_t MAX_PASSWORD_LENGTH{ 0xFFFF };
	static constexpr std::uint16_t DEFAULT_PASSWORD_LENGTH{ 25 };

public slots:
	void generatePassword();
	void setPasswordLength(int iPasswordLength);

signals:
	void passwordGenerated(QString iPassword);

private:
	int mPasswordLength{ DEFAULT_PASSWORD_LENGTH };
	QVector<QChar> mCurrentAlphabet;
};
