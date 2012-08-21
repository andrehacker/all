#ifndef TAGSUIMODEL_H
#define TAGSUIMODEL_H

#include <QStringListModel>
#include <QString>
#include "tagdto.h"

class TagsUiModel : public QStringListModel
{
public:
    explicit TagsUiModel (const QStringList &strings);

    void append (const QString &string);
    TagDto getTag(const QModelIndex &index);
};


#endif // TAGSUIMODEL_H
