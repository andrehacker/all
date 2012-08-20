#include "stringlistmodel.h"

StringListModel::StringListModel (const QStringList &strings)
	: QStringListModel(strings)
{}

void StringListModel::append (const QString &string) {
	insertRows(rowCount(), 1);
	setData(index(rowCount()-1), string);
}
