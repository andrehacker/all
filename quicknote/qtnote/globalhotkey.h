#ifndef _HOTKEY_H_
#define _HOTKEY_H_

#include <QMainWindow>
#include <QAbstractEventDispatcher>

class GlobalHotKey : public QObject {
	
	Q_OBJECT

public:
	explicit GlobalHotKey();
    GlobalHotKey& operator=(const GlobalHotKey&) = delete;    // disallow copy assignment
    GlobalHotKey(const GlobalHotKey&) = delete;    // disallow copy
    bool registerHotkeys(WId handle);
    static bool eventFilter(void *message);

signals:
    void hotKeyPressed(uint keyId, uint modifiers);

private:
    static QAbstractEventDispatcher::EventFilter prevEventFilter_;	// what is this good for?
    static GlobalHotKey *instance_;

};

#endif
