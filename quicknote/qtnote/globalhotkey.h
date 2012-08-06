#ifndef _HOTKEY_H_
#define _HOTKEY_H_

#include <QMainWindow>
#include <QAbstractEventDispatcher>

class GlobalHotKey : public QObject {
	
	Q_OBJECT

public:
	explicit GlobalHotKey();
	bool Register(WId handle);
	static bool EventFilter(void *message);

signals:
	void HotKeyPressed(uint keyId, uint modifiers);

private:
    static QAbstractEventDispatcher::EventFilter prevEventFilter;	// what is this good for?
    static GlobalHotKey* instance;

};

#endif
