#ifndef NOTESUIMODEL_H
#define NOTESUIMODEL_H
#include <vector>
#include <QAbstractListModel>
#include "notemodel.h"

class NotesUiModel : public QAbstractListModel
{
public:
    NotesUiModel(QObject *parent = 0);

    // overwritten
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(const int position, const int rows, const QModelIndex &index = QModelIndex());

    // custom methods
    void updateNoteAt (const QModelIndex &noteIndex, const NoteModel &note);
    void addNoteAt (const int position, const NoteModel &note);
    void append (const NoteModel &note);
    NoteModel getNote(const QModelIndex &index);
    QModelIndex getIndexByNote(const NoteModel &note);

private:
    std::vector<NoteModel> notes_;
};

#endif // NOTESUIMODEL_H
