#ifndef __CSYSTEMTRAY_H__
#define __CSYSTEMTRAY_H__

#include <string>
#include <shellapi.h>

using namespace std;

#define WM_TRAY_NOTIFY WM_APP + 1000

class CSystemTray
{
public:
	CSystemTray(HWND hWnd, UINT uCallbackMessage, string szTip, HICON icon);
	~CSystemTray() { UnNotify(); }

	void Notify();
	void Notify(HICON icon);
	void UnNotify();

	HICON GetIcon();

private:
	bool _enabled, _shown;
	NOTIFYICONDATA _tnd;
};

#endif