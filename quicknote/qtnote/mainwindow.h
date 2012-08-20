#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include "stringlistmodel.h"
#include "globalhotkey.h"
#include "notemodel.h"
#include "abstractview.h"
#include "notesuimodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public AbstractView
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void showEvent(QShowEvent *event);  // overwritten
    static Ui::MainWindow *sui; // static version of ui, for globalhotkey

    // Event filter to detect FocusEvents for content
    // TODO: Can this be replaces by overwriting the event in the parent widget? Will events be bubbled up?
    bool eventFilter(QObject* object, QEvent* event);

    // Virtual methods from AbstractView
    virtual void setPresenter(Presenter *presenter);
    virtual void addNewNote(NoteModel &newNote);
    virtual void updateNotes(const std::vector<NoteModel> &notes);
    virtual void updateNote(const NoteModel &note);
    virtual void deleteNote(const NoteModel &note);
    virtual std::string getSearchFilter();
    virtual void setSearchFilter(const std::string &text);
    virtual void showWindow();
    virtual void showInfoMessageBox(std::string info);

private slots:
	void buttonNewClicked();
    void buttonOptionsClicked();
    void resultCurrentChanged();
    void resultSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void titleEditingFinished();
    void lineSearchTextChanged(const QString & text);
    void HotKeyPressedSlot(uint keyId, uint modifiers);
    
private:
    Ui::MainWindow *ui_;

    // refers to a stack variable, not our ownership, will last longer than own lifetime.
    Presenter *presenter_;

    GlobalHotKey globalHotKey_;
    QStringList tagsStringList_;
    StringListModel tagsUiModel_;
    NotesUiModel notesUiModel_;

    // Helper methods
    void selectNoteByRow(int row);
    NoteModel getSelectedNote();
};

#endif // MAINWINDOW_H
