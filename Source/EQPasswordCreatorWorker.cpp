#include "../Headers/EQPasswordCreatorWorker.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QThread>

EQPasswordCreatorWorker::EQPasswordCreatorWorker()
	: currentAlphabet(), passwordLength{ DEFAULT_PASSWORD_LENGTH },
	randomIndex{ static_cast<int>(time(0)) }
{}

void EQPasswordCreatorWorker::loadAlphabet(QFile& opennedFile)
{
	currentAlphabet.clear();
	QTextStream in{ &opennedFile };
	QString line{ in.readLine() };
	for (QChar& i : line)
		currentAlphabet.append(i);
}

void EQPasswordCreatorWorker::setPasswordLength(int passwordLength)
{
	this->passwordLength = passwordLength;
}

void EQPasswordCreatorWorker::generatePassword()
{
	++randomIndex;
	QRandomGenerator rand(randomIndex);
	qsizetype alphabetLength{ currentAlphabet.length() };
	QString password;
	password.resize(passwordLength);
	for (int i{}; i < passwordLength; ++i)
		password[i] = currentAlphabet[rand.generateDouble() * alphabetLength];
	emit passwordGenerated(password);
}

EQPasswordCreatorWorker::~EQPasswordCreatorWorker()
{}