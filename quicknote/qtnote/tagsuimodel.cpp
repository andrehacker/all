#include "tagsuimodel.h"

TagsUiModel::TagsUiModel (const QStringList &strings)
	: QStringListModel(strings)
{}

void TagsUiModel::append (const QString &string) {
	insertRows(rowCount(), 1);
	setData(index(rowCount()-1), string);
}

TagDto TagsUiModel::getTag(const QModelIndex &index) {
    // TODO: Remove this dirty hack!
    // Make this class store the Tags (similar to NotesUiModel)
    return TagDto(-1, data(index, Qt::DisplayRole).toString().toStdString(), 0);
}
