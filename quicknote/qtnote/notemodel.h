#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <vector>
#include <string>
#include <QMetaType>
#include "tagmodel.h"

class NoteModel
{
public:
    NoteModel();
    NoteModel(int id, std::string title, std::string content);
    int getId() const;
    std::string getTitle() const;
    std::string getContent() const;
    std::vector<TagModel> getTags() const;
    std::string getDateCreated() const;
    std::string getDateModified() const;
    void setId(const long long int);
    void setTitle(const std::string &);
    void setContent(const std::string &);
    bool isDeleted();

private:
    int id_;
    std::string title_;
    std::string content_;
    std::vector<TagModel> tags_;
    std::string dateCreated_;
    std::string dateModified_;
    bool isDeleted_;
};

// Needed to store NoteModel in QVariant
Q_DECLARE_METATYPE(NoteModel)

#endif // NOTEMODEL_H
