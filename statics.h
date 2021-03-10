#ifndef STATICS_H
#define STATICS_H

#include <QString>

#include "EnumSex.h"
#include "EnumFirm.h"
#include "EnumMaritalStatus.h"

QString getErrorStyle();
bool isANumber(const class QString &String);
bool isValidText(class QLineEdit *Text);
bool isValidDate(class QLineEdit *YEAR, class QLineEdit *MONTH, class QLineEdit *DAY);

bool isValidEnum(const Sex Sex);
bool isValidEnum(const Firm Firm);
bool isValidEnum(const MaritalStatus MaritalStatus);

bool isValidNumber(class QLineEdit *Number);

void setDayValidator(class QLineEdit *Date);
void setMonthValidator(class QLineEdit *Date);
void setYearValidator(class QLineEdit *Date);
void setNumberValidator(class QLineEdit *Number);

void createDirectory(const class QString &Path);

void Whiten(QList<class EditableWidget*> list);
void deWhiten(QList<class EditableWidget*> list);

void printWidget(class QWidget* widget, QWidget* parent);

QString formatDate(int date);

#endif // STATICS_H
