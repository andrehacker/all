#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QStringListModel>
#include <QString>

class StringListModel : public QStringListModel
{
public:
	explicit StringListModel (const QStringList & strings);
    void append (const QString& string);
};


#endif // STRINGLISTMODEL_H
