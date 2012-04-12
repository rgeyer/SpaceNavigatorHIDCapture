// SpaceNavigatorAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpaceNavigatorApp.h"
#include "SpaceNavigatorAppDlg.h"

#include <dbt.h>

#include "CConfigParser.h"
#include "CMouseDeviceContext.h"
#include "CAxis.h"
#include "CTimeFrame.h"
#include "CActionButton.h"

#include "CExecuteAction.h"
#include "CKeyboardAction.h"
#include "CLeftMouseButtonAction.h"
#include "CRightMouseButtonAction.h"
#include "CSendWindowMessageAction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpaceNavigatorAppDlg dialog


CSpaceNavigatorAppDlg::CSpaceNavigatorAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpaceNavigatorAppDlg::IDD, pParent)
{
	_blueIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	_redIcon = AfxGetApp()->LoadIcon(IDI_ICON2);
}

void CSpaceNavigatorAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSpaceNavigatorAppDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_QUIT, &CSpaceNavigatorAppDlg::OnMenuQuit)
	ON_MESSAGE(WM_TRAY_NOTIFY, &CSpaceNavigatorAppDlg::OnTrayNotify)
	ON_WM_WINDOWPOSCHANGING()
	ON_MESSAGE(WM_DEVICECHANGE, &CSpaceNavigatorAppDlg::OnDeviceChange)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CSpaceNavigatorAppDlg message handlers

BOOL CSpaceNavigatorAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(_blueIcon, TRUE);			// Set big icon
	SetIcon(_blueIcon, FALSE);		// Set small icon
	
	ShowWindow(SW_MINIMIZE);

	_smallBlue = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, NULL);
	_smallRed = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, NULL);

	char currentDir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, (LPSTR)&currentDir);

	string configFile = currentDir;
	configFile += "\\config.xml";
	CConfigParser::ParseConfig(configFile, *this);

	StartCapturing();

	_tray = new CSystemTray(GetSafeHwnd(), WM_TRAY_NOTIFY, "SpaceNavigator", NULL);

	_tray->Notify(_smallBlue);

	_menu.LoadMenuA(IDR_MENU1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSpaceNavigatorAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, _blueIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSpaceNavigatorAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(_blueIcon);
}


void CSpaceNavigatorAppDlg::OnMenuQuit()
{
	OnOK();
}

LRESULT CSpaceNavigatorAppDlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
		case WM_RBUTTONDOWN:
		{
			/////////////////////////////////////
			// Load and Verify Menu
			CMenu* pPopup = _menu.GetSubMenu (0) ;
			ASSERT(pPopup != NULL);

			// Get the cursor position
			POINT pt ;
			GetCursorPos (&pt) ;

			// Fix Microsofts' BUG!!!!
			SetForegroundWindow();

			///////////////////////////////////
			// Display The Menu
			pPopup->TrackPopupMenu(TPM_LEFTALIGN |
			TPM_RIGHTBUTTON,pt.x, pt.y, this);
				break ;
		}
	}
	return (0);
}
void CSpaceNavigatorAppDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	lpwndpos->flags &= ~SWP_SHOWWINDOW;
	CDialog::OnWindowPosChanging(lpwndpos);
}

/*virtual*/ void CSpaceNavigatorAppDlg::PostNcDestroy()
{
	delete _tray;
	DestroyIcon(_smallBlue);
	DestroyIcon(_smallRed);
}

LRESULT CSpaceNavigatorAppDlg::OnDeviceChange(WPARAM wParam, LPARAM lParam)
{
	// TODO: Add a method to ADeviceListener to re-scan all devices
	return 0;
}

BOOL CSpaceNavigatorAppDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	USES_CONVERSION;
	char* cPtr = (char*)pCopyDataStruct->lpData;
	//cPtr[pCopyDataStruct->cbData] = 0;
	TRACE("Received Window Message %s\r\n", cPtr);
	wstring message = T2OLE(cPtr);
	message = message.substr(0, pCopyDataStruct->cbData);
	// check if this is a context switch request
	if(wstring::npos != message.find(L"CONTEXT;", 0))
	{
		// check if we're going up or down the context list
		if(wstring::npos != message.find(L"Up", 7))
		{
			IncrementContext();
		}
		else if(wstring::npos != message.find(L"Down", 7))
		{
			DecrementContext();
		}
		else
		{
			wstring contextName = message.substr(8);
			SetContext(contextName);
		}
	}
	if(wstring::npos != message.find(L"HID;", 0))
	{
		wstring deviceAndCommand = message.substr(4);
		wstring::size_type commSeperator = message.find(L";", 5);

		wstring deviceName = message.substr(4, commSeperator-4);
		wstring command = message.substr(commSeperator+1);
		CWin32SpaceNavigatorHIDCapture* hidDevice = dynamic_cast<CWin32SpaceNavigatorHIDCapture*>(_devicesByName[deviceName]);
		if(hidDevice != NULL)
			hidDevice->RunCommand(command);
	}
	return true;
}