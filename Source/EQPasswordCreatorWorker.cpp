#include "../Headers/EQPasswordCreatorWorker.h"
#include <QString>
#include <QRandomGenerator>
#include <QThread>
#include <QTextStream>
#include <QFile>

void EQPasswordCreatorWorker::loadAlphabet(QFile& iOpennedFile)
{
	mCurrentAlphabet.clear();
	QTextStream wTextStream(&iOpennedFile);
	QString wLine(wTextStream.readLine());
	mCurrentAlphabet.assign(wLine.begin(), wLine.end());
}

void EQPasswordCreatorWorker::setPasswordLength(int iPasswordLength)
{
	mPasswordLength = iPasswordLength;
}

void EQPasswordCreatorWorker::generatePassword()
{
	QString wPassword;
	wPassword.resize(mPasswordLength);

	for (int i{}; i < mPasswordLength; ++i)
	{
		wPassword[i] = mCurrentAlphabet[QRandomGenerator::global()->bounded(0, mCurrentAlphabet.length())];
	}

	emit passwordGenerated(wPassword);
}