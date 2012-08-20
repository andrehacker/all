/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Mon 20. Aug 13:01:03 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionNewNote;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonOptions;
    QPushButton *buttonNew;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonProfile;
    QSplitter *splitter;
    QListView *listTags;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *lineSearch;
    QListView *listResult;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineTitle;
    QPlainTextEdit *textContent;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(644, 424);
        QIcon icon;
        icon.addFile(QString::fromUtf8("res/glyphicons_027_search.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionNewNote = new QAction(MainWindow);
        actionNewNote->setObjectName(QString::fromUtf8("actionNewNote"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../CODE/github/glyphicons_free/glyphicons_190_circle_plus.png"), QSize(), QIcon::Normal, QIcon::On);
        actionNewNote->setIcon(icon1);
        actionNewNote->setVisible(true);
        actionNewNote->setIconVisibleInMenu(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, -1);
        buttonOptions = new QPushButton(centralWidget);
        buttonOptions->setObjectName(QString::fromUtf8("buttonOptions"));
        buttonOptions->setLayoutDirection(Qt::LeftToRight);
        buttonOptions->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/files/res/glyphicons_023_cogwheels.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOptions->setIcon(icon2);
        buttonOptions->setFlat(false);

        horizontalLayout->addWidget(buttonOptions);

        buttonNew = new QPushButton(centralWidget);
        buttonNew->setObjectName(QString::fromUtf8("buttonNew"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonNew->sizePolicy().hasHeightForWidth());
        buttonNew->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("res/glyphicons_190_circle_plus.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonNew->setIcon(icon3);
        buttonNew->setFlat(false);

        horizontalLayout->addWidget(buttonNew);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonProfile = new QPushButton(centralWidget);
        buttonProfile->setObjectName(QString::fromUtf8("buttonProfile"));
        buttonProfile->setFlat(false);

        horizontalLayout->addWidget(buttonProfile);


        verticalLayout_2->addLayout(horizontalLayout);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        listTags = new QListView(splitter);
        listTags->setObjectName(QString::fromUtf8("listTags"));
        listTags->setFrameShadow(QFrame::Raised);
        listTags->setSelectionMode(QAbstractItemView::ExtendedSelection);
        splitter->addWidget(listTags);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        lineSearch = new QLineEdit(layoutWidget);
        lineSearch->setObjectName(QString::fromUtf8("lineSearch"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineSearch->sizePolicy().hasHeightForWidth());
        lineSearch->setSizePolicy(sizePolicy1);
        lineSearch->setStyleSheet(QString::fromUtf8("padding-right: 20px; padding-left: 2px; background: url(:/files/res/glyphicons_027_search_16px.png); background-position: right; background-repeat: no-repeat; border: 1px solid white;border-radius: 10px"));
        lineSearch->setFrame(false);
        lineSearch->setPlaceholderText(QString::fromUtf8("Search"));

        verticalLayout_3->addWidget(lineSearch);

        listResult = new QListView(layoutWidget);
        listResult->setObjectName(QString::fromUtf8("listResult"));
        listResult->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(listResult);

        splitter->addWidget(layoutWidget);
        layoutWidget1 = new QWidget(splitter);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineTitle = new QLineEdit(layoutWidget1);
        lineTitle->setObjectName(QString::fromUtf8("lineTitle"));
        lineTitle->setFrame(false);

        verticalLayout->addWidget(lineTitle);

        textContent = new QPlainTextEdit(layoutWidget1);
        textContent->setObjectName(QString::fromUtf8("textContent"));
        textContent->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(textContent);

        splitter->addWidget(layoutWidget1);

        verticalLayout_2->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QuickNote", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "&Exit", 0, QApplication::UnicodeUTF8));
        actionNewNote->setText(QApplication::translate("MainWindow", "&New Note", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNewNote->setToolTip(QApplication::translate("MainWindow", "New Note", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNewNote->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        buttonOptions->setText(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        buttonNew->setText(QApplication::translate("MainWindow", "New Note", 0, QApplication::UnicodeUTF8));
        buttonProfile->setText(QApplication::translate("MainWindow", "AndreNotes", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
