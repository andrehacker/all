#include <sstream>
#include <QStringListModel>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stringlistmodel.h"
#include "globalhotkey.h"
#include "presenter.h"

Ui::MainWindow *MainWindow::sui = 0;

// TODO: Tray icon: http://qt-project.org/doc/qt-4.8/desktop-systray.html
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    tagsStringList_(),
    tagsUiModel_(tagsStringList_),
    notesUiModel_()
{
    // Attention: pointer to presenter may not be used in constructor. It is set afterwards.
    ui_->setupUi(this);
    sui = ui_;   // static version of ui for globalhotkey eventhandler

    // Layout
    ui_->splitter->setStretchFactor(0, 10);
    ui_->splitter->setStretchFactor(1, 15);
    ui_->splitter->setStretchFactor(2, 30);

    // Set UI-Models
    ui_->listTags->setModel(&tagsUiModel_);
    ui_->listResult->setModel(&notesUiModel_);

    // Event Handler
    connect(ui_->buttonNew, SIGNAL(clicked()),
            this, SLOT(buttonNewClicked()));
    connect(ui_->buttonOptions, SIGNAL(clicked()),
            this, SLOT(buttonOptionsClicked()));
    connect(ui_->lineSearch, SIGNAL(textChanged(const QString&)),
            this, SLOT(lineSearchTextChanged(const QString &)));
    connect(ui_->listResult->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(resultCurrentChanged()));
    connect(ui_->listResult->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(resultSelectionChanged(const QItemSelection &, const QItemSelection &)));
    connect(ui_->lineTitle, SIGNAL(editingFinished()),
            this, SLOT(titleEditingFinished()));
    // Set Event filter to get QFocusEvent for content field and for other events
    // This way we can avoid to subclass QPlainTextEdit
    ui_->textContent->installEventFilter(this);
    ui_->listResult->installEventFilter(this);

    // Register Global Hotkeys
    if (globalHotKey_.Register(this->winId())) {
        qDebug("Registered Hotkeys");
    } else {
        qDebug("Error registering Hotkeys");
    }
    connect(&globalHotKey_, SIGNAL(HotKeyPressed(uint, uint)),
        this, SLOT(HotKeyPressedSlot(uint, uint)));

}

MainWindow::~MainWindow() {
    delete ui_;
}

// Event filter, needed for FocusEvent detection, etc.
bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::FocusOut && object == ui_->textContent) {
        // So inform Presenter about changed content
        if (ui_->textContent->document()->isModified()) {
            NoteModel note = getSelectedNote();
            note.setContent(ui_->textContent->toPlainText().toStdString());

            presenter_->contentEditingFinished(note);

            ui_->textContent->document()->setModified(false);
        }
        return true;
    } else if (event->type() == QEvent::KeyRelease && object == ui_->listResult) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Ate key press %d", keyEvent->key());
        if (keyEvent->key() == Qt::Key_Delete) {
            // Delete selected Note
            NoteModel note = getSelectedNote();
            presenter_->deleteNote(note);
            return true;
        }
    }
    // Standard event processing
    return QObject::eventFilter(object, event);
}

// override QWidgets showEvent
void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    ui_->lineSearch->setFocus();
}

void MainWindow::resultCurrentChanged() {
    // Ignore this, because if there is a current, there is also a selected item
}

void MainWindow::resultSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    if (selected.isEmpty()) {
        // List was cleared (either before adding new items, or because search has no result)
        ui_->lineTitle->setText("");
        ui_->textContent->setPlainText("");
    } else {
        // User selected any item or search result was updated => Update content/title
        // Get selected item
        NoteModel tempNote = notesUiModel_.getNote(selected.indexes().first());
        ui_->textContent->setPlainText(
                    QString::fromStdString(tempNote.getContent()));
        ui_->lineTitle->setText(
                    QString::fromStdString(tempNote.getTitle()));

    }
}

void MainWindow::buttonNewClicked() {
    presenter_->newNoteClicked();
}

void MainWindow::buttonOptionsClicked() {
    presenter_->optionsClicked();
}

void MainWindow::lineSearchTextChanged(const QString & text) {
    presenter_->searchTextChanged(text.toStdString());
}

void MainWindow::titleEditingFinished() {
    if (ui_->lineTitle->isModified()) {

        NoteModel note = getSelectedNote();
        note.setTitle(ui_->lineTitle->text().toStdString());

        presenter_->titleEditingFinished(note);

        ui_->lineTitle->setModified(false);
    }
}

void MainWindow::HotKeyPressedSlot(uint keyId, uint modifiers) {
    std::stringstream s;
    s << "Received WM_HOTKEY. key:" << keyId << " modifiers: " << modifiers;
    //ui->textEditLog->appendPlainText(s.str().c_str());

    ui_->lineSearch->setText("");
    
    // Activate window
    showNormal();
    activateWindow();
    raise();

    // set focus
    ui_->lineSearch->setFocus();
}

void MainWindow::setPresenter(Presenter *presenter) {
    presenter_ = presenter;
}

std::string MainWindow::getSearchFilter() {
    return ui_->lineSearch->text().toStdString();
}

void MainWindow::setSearchFilter(const std::string &text) {
    if (ui_->lineSearch->text().compare(QString::fromStdString(text)) != 0) {
        ui_->lineSearch->setText(QString::fromStdString(text));
    }
}

void MainWindow::addNewNote(NoteModel &newNote) {
    // Add note at beginning
    notesUiModel_.addNoteAt(0, newNote);

    // Select Note
    selectNoteByRow(0);
    ui_->lineTitle->setFocus();
}

void MainWindow::updateNotes(const std::vector<NoteModel> &notes) {
    notesUiModel_.removeRows(0, notesUiModel_.rowCount());

    if (notes.size() > 0) {
        for (auto it = notes.begin(); it != notes.end(); ++it) {
            notesUiModel_.append(*it);
        }

        // Select first note (just select, not focus, so not current)
        selectNoteByRow(0);
    }
}

void MainWindow::updateNote(const NoteModel &note) {
    // Find the index of the note in result list and update list model
    notesUiModel_.updateNoteAt(notesUiModel_.getIndexByNote(note), note);

    // TODO: If the note is selected, update details.
    // Neccesary only if the model is changed from outside the gui (e.g. synchronization)
    // or if the GUI does not update itself properly
}

void MainWindow::deleteNote(const NoteModel &note) {
    // Find the index of the note in result list and update list model
    notesUiModel_.removeRow(notesUiModel_.getIndexByNote(note).row());
}

void MainWindow::showWindow() {
    this->show();
}

void MainWindow::showInfoMessageBox(std::string info) {
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(info));
    msgBox.exec();
}

void MainWindow::selectNoteByRow(int row) {
    QItemSelectionModel *selectionModel = ui_->listResult->selectionModel();
    selectionModel->reset();    // Does not emit any signals (like selectionChanged)
    selectionModel->select(notesUiModel_.index(row,0), QItemSelectionModel::Select);
}

NoteModel MainWindow::getSelectedNote() {
    // TODO: Make this nullptr safe!
    return notesUiModel_.getNote(ui_->listResult->selectionModel()->selectedIndexes().first());
}

