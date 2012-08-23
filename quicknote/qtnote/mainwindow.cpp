#include <sstream>
#include <vector>
#include <QStringListModel>
#include <QStringList>
#include <QDebug>
#include <QMenu>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tagsuimodel.h"
#include "globalhotkey.h"
#include "presenter.h"
#include "settingsui.h"

Ui::MainWindow *MainWindow::sui = 0;

// TODO: Tray icon: http://qt-project.org/doc/qt-4.8/desktop-systray.html
MainWindow::MainWindow(Presenter &presenter, QWidget *parent) :
    QMainWindow(parent),
    presenter_(presenter),
    ui_(new Ui::MainWindow),
    tagsStringList_(),
    tagsUiModel_(tagsStringList_),
    notesUiModel_()
{
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
    connect(ui_->listTags->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(tagsSelectionChanged(const QItemSelection &, const QItemSelection &)));
    connect(ui_->lineTitle, SIGNAL(editingFinished()),
            this, SLOT(titleEditingFinished()));
    connect(ui_->lineTags, SIGNAL(editingFinished()),
            this, SLOT(tagsEditingFinished()));

    initTrayIcon();

    // Set Event filter to get QFocusEvent for content field and for other events
    // This way we can avoid to subclass QPlainTextEdit
    ui_->textContent->installEventFilter(this);
    ui_->listResult->installEventFilter(this);

    // Register Global Hotkeys
    if (globalHotKey_.registerHotkeys(this->winId())) {
        qDebug("Registered Hotkeys");
    } else {
        qDebug("Error registering Hotkeys");
    }
    connect(&globalHotKey_, SIGNAL(hotKeyPressed(uint, uint)),
        this, SLOT(hotKeyPressed(uint, uint)));
}

void MainWindow::initTrayIcon() {
    //connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(&trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon.setIcon(QIcon(":/files/res/glyphicons_027_search.png"));

    restoreAction = std::unique_ptr<QAction> (new QAction(tr("&Open Note"), this));
    connect(restoreAction.get(), SIGNAL(triggered()), this, SLOT(showNormal()));
    quitAction = std::unique_ptr<QAction> (new QAction(tr("&Quit"), this));
    connect(quitAction.get(), SIGNAL(triggered()), qApp, SLOT(quit()));

    trayIconMenu = std::unique_ptr<QMenu>(new QMenu(this));
    trayIconMenu->addAction(restoreAction.get());
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction.get());
    trayIcon.setContextMenu(trayIconMenu.get());

    trayIcon.show();
}

MainWindow::~MainWindow() {
    qDebug() << "MainWindow Destructor";
    trayIcon.hide();
    delete ui_;
}

// Event filter, needed for FocusEvent detection, etc.
bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::FocusOut && object == ui_->textContent) {
        // So inform Presenter about changed content
        if (ui_->textContent->document()->isModified()) {
            NoteDto note = getSelectedNote();
            note.setContent(ui_->textContent->toPlainText().toStdString());

            presenter_.contentEditingFinished(note);

            ui_->textContent->document()->setModified(false);
        }
        return true;
    } else if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("Key pressed: %d", keyEvent->key());
        if (object == ui_->listResult && keyEvent->key() == Qt::Key_Delete) {
            // Delete selected Note
            NoteDto note = getSelectedNote();
            presenter_.deleteNote(note);
            return true;
        }
    }
    // Standard event processing
    return QObject::eventFilter(object, event);
}

// overwrite QWidgets showEvent
void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);

    ui_->lineSearch->setFocus();
}

// overwrite
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon.isVisible()) {
        if (SettingsUi::minimizedInfoAllowed()) {
            trayIcon.showMessage("QNote", "QNote will keep running in background. "
                                 "Click here to restore it, or choose Quit"
                                 " in the context menu of the tray icon.");
        }
        hide();
        event->ignore();
    }
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        qDebug() << "Regular click/Trigger";
        restoreWindowFromTray();
        break;
    case QSystemTrayIcon::DoubleClick:
        // Trigger event was handled before. Ignore this second click.
        break;
    default:
    ;
    }
}

void MainWindow::resultCurrentChanged() {
    // Ignore this, because if there is a current, there is also a selected item
}

void MainWindow::resultSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    if (selected.isEmpty()) {
        // List was cleared (either before adding new items, or because search has no result)
        ui_->lineTitle->setText("");
        ui_->lineTags->setText("");
        ui_->textContent->setPlainText("");
    } else {
        // User selected any item or search result was updated => Update content/title
        NoteDto tempNote = notesUiModel_.getNote(selected.indexes().first());
        ui_->textContent->setPlainText(
                    QString::fromStdString(tempNote.getContent()));
        ui_->lineTitle->setText(
                    QString::fromStdString(tempNote.getTitle()));
        ui_->lineTags->setText(
                    QString::fromStdString(tempNote.getTags()));
    }
}

void MainWindow::tagsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {

    // TODO: This is not called when a user has two tags selected, and then selects the last of the two tags only
    // (because the currently selected tag does not change)
    // Inform Presenter. He must load the notes according to the users selection
    presenter_.tagSelectionChanged();
}

std::vector<TagDto> MainWindow::getSelectedTags() {
    std::vector<TagDto> tags;
    for (int i=0; i<ui_->listTags->selectionModel()->selectedIndexes().size(); ++i) {
        tags.push_back(tagsUiModel_.getTag(ui_->listTags->selectionModel()->selectedIndexes().at(i)));
    }
    return tags;
}

void MainWindow::buttonNewClicked() {
    presenter_.newNoteClicked();
}

void MainWindow::buttonOptionsClicked() {
    presenter_.optionsClicked();
}

void MainWindow::lineSearchTextChanged(const QString & text) {
    presenter_.searchTextChanged(text.toStdString());
}

void MainWindow::titleEditingFinished() {
    if (ui_->lineTitle->isModified()) {
        NoteDto note = getSelectedNote();
        note.setTitle(ui_->lineTitle->text().toStdString());

        presenter_.titleEditingFinished(note);

        ui_->lineTitle->setModified(false);
    }
}

void MainWindow::tagsEditingFinished() {
    if (ui_->lineTags->isModified()) {
        NoteDto note = getSelectedNote();
        note.setTags(ui_->lineTags->text().toStdString());

        presenter_.tagsEditingFinished(note);

        ui_->lineTags->setModified(false);
    }
}

void MainWindow::hotKeyPressed(uint keyId, uint modifiers) {
    std::stringstream s;
    s << "Received WM_HOTKEY. key:" << keyId << " modifiers: " << modifiers;
    //ui->textEditLog->appendPlainText(s.str().c_str());

    restoreWindowFromTray();
}

void MainWindow::restoreWindowFromTray() {
    ui_->lineSearch->setText("");

    // Activate window
    showNormal();
    activateWindow();
    raise();

    // set focus
    ui_->lineSearch->setFocus();
}

std::string MainWindow::getSearchFilter() {
    return ui_->lineSearch->text().toStdString();
}

void MainWindow::setSearchFilter(const std::string &text) {
    if (ui_->lineSearch->text().compare(QString::fromStdString(text)) != 0) {
        ui_->lineSearch->setText(QString::fromStdString(text));
    }
}

void MainWindow::addNewNote(NoteDto &newNote) {
    // Add note at beginning
    notesUiModel_.addNoteAt(0, newNote);

    // Select Note
    selectNoteByRow(0);
    ui_->lineTitle->setFocus();
}

void MainWindow::updateNotes(const std::vector<NoteDto> &notes) {
    notesUiModel_.removeRows(0, notesUiModel_.rowCount());

    if (notes.size() > 0) {
        for (auto it = notes.begin(); it != notes.end(); ++it) {
            notesUiModel_.append(*it);
        }

        // Select first note (just select, not focus, so not current)
        selectNoteByRow(0);
    }
}

void MainWindow::updateTags(const std::vector<TagDto> &tags) {
    tagsUiModel_.removeRows(0, tagsUiModel_.rowCount());

    if (tags.size() > 0) {
        for (auto it = tags.begin(); it != tags.end(); ++it) {
            tagsUiModel_.append(it->getName().c_str());
        }
    }
}

void MainWindow::updateNote(const NoteDto &note) {
    // Find the index of the note in result list and update list model
    notesUiModel_.updateNoteAt(notesUiModel_.getIndexByNote(note), note);

    // TODO: If the note is selected, update details.
    // Neccesary only if the model is changed from outside the gui (e.g. synchronization)
    // or if the GUI does not update itself properly
}

void MainWindow::deleteNote(const NoteDto &note) {
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

NoteDto MainWindow::getSelectedNote() {
    // TODO: Make this nullptr safe!
    return notesUiModel_.getNote(ui_->listResult->selectionModel()->selectedIndexes().first());
}

