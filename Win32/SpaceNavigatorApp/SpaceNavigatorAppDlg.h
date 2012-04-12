// SpaceNavigatorAppDlg.h : header file
//

#pragma once
#include "CSystemTray.h"
#include "CWin32SpaceNavigatorHIDCapture.h"
#include "CMouseProc.h"
#include "CContext.h"
#include "IAction.h"

#include <vector>

#include "ADeviceListener.h"

using namespace std;

// CSpaceNavigatorAppDlg dialog
class CSpaceNavigatorAppDlg : public CDialog, public ADeviceListener
{
// Internal data
private:
	HICON _blueIcon, _redIcon, _smallBlue, _smallRed, _bigBlue, _bigRed;
	CMenu _menu;
	CSystemTray* _tray;
	LRESULT OnTrayNotify(WPARAM, LPARAM);

// Construction
public:
	CSpaceNavigatorAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SPACENAVIGATORAPP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//New message handlers
public:
	virtual void PostNcDestroy();
	afx_msg void OnMenuQuit();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnSwapIcon();
	afx_msg LRESULT OnDeviceChange(WPARAM, LPARAM);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);

private:
	bool _button1;
	bool _button2;
};
