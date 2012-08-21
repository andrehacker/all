#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include "tagsuimodel.h"
#include "globalhotkey.h"
#include "NoteDTO.h"
#include "abstractview.h"
#include "notesuimodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public AbstractView
{
    Q_OBJECT

public:
    explicit MainWindow(Presenter &presenter, QWidget *parent = 0);
    ~MainWindow();

    virtual void showEvent(QShowEvent *event);  // overwritten
    static Ui::MainWindow *sui; // static version of ui, for globalhotkey

    // Event filter to detect FocusEvents for content
    // TODO: Can this be replaces by overwriting the event in the parent widget? Will events be bubbled up?
    bool eventFilter(QObject* object, QEvent* event);

    // Virtual methods from AbstractView
    virtual void addNewNote(NoteDto &newNote);
    virtual void updateNotes(const std::vector<NoteDto> &notes);
    virtual void updateTags(const std::vector<TagDto> &tags);
    virtual void updateNote(const NoteDto &note);
    virtual void deleteNote(const NoteDto &note);
    virtual std::string getSearchFilter();
    virtual std::vector<TagDto> getSelectedTags();
    virtual void setSearchFilter(const std::string &text);
    virtual void showWindow();
    virtual void showInfoMessageBox(std::string info);

private slots:
	void buttonNewClicked();
    void buttonOptionsClicked();
    void resultCurrentChanged();
    void resultSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void tagsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void titleEditingFinished();
    void tagsEditingFinished();
    void lineSearchTextChanged(const QString & text);
    void HotKeyPressedSlot(uint keyId, uint modifiers);
    
private:
    // Helper methods
    void selectNoteByRow(int row);
    NoteDto getSelectedNote();

    Presenter &presenter_;  // dependency - not our ownership
    Ui::MainWindow *ui_;    // null at beginning, will be initialized in constructor

    GlobalHotKey globalHotKey_;
    QStringList tagsStringList_;
    TagsUiModel tagsUiModel_;
    NotesUiModel notesUiModel_;
};

#endif // MAINWINDOW_H
