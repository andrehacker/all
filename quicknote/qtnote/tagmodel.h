#ifndef TAGMODEL_H
#define TAGMODEL_H

#include <string>

class TagModel
{
public:
    TagModel();
    std::string getName();
    std::string getDateCreated();
    std::string getDateUpdated();

private:
    std::string name_;
    std::string dateCreated_;
    std::string dateUpdated_;
};

#endif // TAGMODEL_H
