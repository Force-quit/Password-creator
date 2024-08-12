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
	EQPasswordCreatorWorker();
	~EQPasswordCreatorWorker();
	
	void loadAlphabet(QFile& opennedFile);

	static const int MAX_PASSWORD_LENGTH{ 1000000 };
	static const int DEFAULT_PASSWORD_LENGTH{ 25 };

public slots:
	void generatePassword();
	void setPasswordLength(int passwordLength);

signals:
	void passwordGenerated(QString password);

private:
	QVector<QChar> currentAlphabet;
	int passwordLength;
	int randomIndex;
};
