// DemoBot.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "stdio.h"
#include "DemoBot.h"
#include "iBotPlatform.h"

#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;								// current instance
HWND g_hwnd;
HWND g_hwndLabel;
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR szServer[MAX_LOADSTRING];					// BOTPLATFORM server address
int iPort;										// BOTPLATFORM server port
TCHAR szUsername[MAX_LOADSTRING];				// Username for login
TCHAR szPassword[MAX_LOADSTRING];				// Password for login

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK LoginDlg(HWND, UINT, WPARAM, LPARAM);


void ShowText(HWND wnd, LPCSTR str)
{
	char* buf = new char[GetWindowTextLength(wnd) + strlen(str) + 10];
	GetWindowText(wnd, buf, GetWindowTextLength(wnd)+1);
	strcat(buf, "\r\n\r\n");
	strcat(buf, str);
	SetWindowText(wnd, buf);
	SendMessage(wnd, EM_SETSEL, GetWindowTextLength(wnd), GetWindowTextLength(wnd));
	SendMessage(wnd,EM_SCROLLCARET,0,0);
	delete[] buf;
}


//DemoBotEvent, inherit from CMsnBotEvent in "MsnBotClient.h"

class CDemoBotEvent: public CBotEvent
{
private:
	char  msg[512];
public:
	CBotCommand BotCommand;
	//constructor
	CDemoBotEvent(){
	};

	//errcode = 0, Login Success,
	//errcode = 1, Login Fail,
	//errcode = 2, Login Fail, will reconnect automatically
	//lpErrString describes the error details
	void WINAPI OnLogin(int errcode, LPCSTR lpErrString)
	{
		if(0 == errcode)
		{
			sprintf(msg, "Login Success: %s", lpErrString); 
			ShowText(g_hwndLabel, msg);
		}
		else
		{
			sprintf(msg, "Login Error:lpErrString=%s",lpErrString);  
			ShowText(g_hwndLabel, msg);
		}
	}
    
	//errcode = 0, disconnect from server after the Logout command,
	//errcode = 1, disconnect form server due to network or server error
	void WINAPI OnLogout(int errcode)
	{
		ShowText(g_hwndLabel, "Server logged out.");
	}
	
	//Bot Receive Message from User
	//lpBuddyAccount:  User's account
	//lpMsg: Message text from user
	void WINAPI OnUserMsg(LPCSTR lpBuddyAccount, LPCSTR lpMsg, LPCSTR lpFontName, DWORD dwFontColor, DWORD dwFontStyle)
	{
		sprintf(msg, "%s: %s", lpBuddyAccount, lpMsg);  
		ShowText(g_hwndLabel, msg);
		sprintf(msg, "From %s: %s", lpBuddyAccount, lpMsg);
		if(strcmp(lpMsg, "?") == 0)
		{
			strcat(msg, "\r");
			strcat(msg, "p4 -------- test msn activity.\r");
			strcat(msg, "nudge ----- test nudge.\r");
			strcat(msg, "sig ----- test msn setSignature.\r");
			this->BotCommand.SendMsg(lpBuddyAccount, msg);			
		}
		else if(strcmp(lpMsg, "p4") == 0)
		{
			strcat(msg, "\r");
			strcat(msg, "Reply a P4 page to you, please accept the invitation!");
			this->BotCommand.SendMsg(lpBuddyAccount, msg);
			this->BotCommand.SendActivity(lpBuddyAccount, "http://www.live.com", "www.live.com");
		}
		else if(strcmp(lpMsg, "nudge") == 0)
		{
			strcat(msg, "\r");
			strcat(msg, "Reply a nudge to you!");
			this->BotCommand.SendMsg(lpBuddyAccount, msg);
			this->BotCommand.SendNudge(lpBuddyAccount);
		}
		else if(strcmp(lpMsg, "sig") == 0)
		{
			strcat(msg, "\r");
			strcat(msg,"Please notice the robot signature");
			this->BotCommand.SendMsg(lpBuddyAccount, msg, "", "Custom Robot Name");
		}
		else
		{
			strcat(msg, "\rRE: ");
			strcat(msg, lpMsg);
			this->BotCommand.SendMsg(lpBuddyAccount, msg, "", "", lpFontName, dwFontColor, dwFontStyle);
		}
	}

	//Bot receive nudge from user
	//lpUserAccount:  User's account
	void WINAPI OnUserNudge(LPCSTR lpBuddyAccount)
	{
		sprintf(msg, "%s sent a nudge2.", lpBuddyAccount);  
		ShowText(g_hwndLabel, msg);
		sprintf(msg, "From2 %s: a nudge2", lpBuddyAccount);
		this->BotCommand.SendMsg(lpBuddyAccount, msg);
	}

	//responding to activity invitation
	//lpUserAccount:  User's account
    //iRespondCode: Responding event after user receive an activity invitation
    //              ACTIVITY_ACCEPT  (0): User acccept the invitation
    //              ACTIVITY_DECLINE (1): User decline the invitation
    //              ACTIVITY_LOADED  (3): the activity load complete
    //              ACTIVITY_CLOSED  (4): User close the activity window
    //              ACTIVITY_UNKNOWN (2): Unknown event
	void WINAPI OnActivityRespond(LPCSTR lpUserAccount,int iRespondCode)
	{
		sprintf(msg, "%s accept activity.", lpUserAccount);
		ShowText(g_hwndLabel, msg);
		switch(iRespondCode)
		{
        case ACTIVITY_ACCEPT://  (0): User Acccept the invitation
            this->BotCommand.SendMsg(lpUserAccount, "you accept the activity, please waiting...");
            break;
        case ACTIVITY_DECLINE:// (1): User Decline the invitation
            this->BotCommand.SendMsg(lpUserAccount, "you decline the activity, why?");
            break;
        case ACTIVITY_LOADED://  (3): the activity load complete
            this->BotCommand.SendMsg(lpUserAccount, "the activity window loaded, please look right side!");
            break;
        case ACTIVITY_CLOSED://  (4): User close the activity window
            this->BotCommand.SendMsg(lpUserAccount, "you close the activity window!");
            break;
		}
	}



	//User add the robot to his/her friend list
	//lpBotAccount: Bot's account
	//lpBuddyAccount: User's account
	void WINAPI OnUserAdd(LPCSTR lpBotAccount, LPCSTR lpBuddyAccount)
	{
		sprintf(msg, "%s adds %s", lpBuddyAccount, lpBotAccount);  
		ShowText(g_hwndLabel, msg);
	}

	//User remove the robot to his/her friend list
	//lpBotAccount: Bot's account
	//lpBuddyAccount: User's account
	void WINAPI OnUserRemove(LPCSTR lpBotAccount, LPCSTR lpBuddyAccount)
	{
		sprintf(msg, "%s removes %s", lpBuddyAccount, lpBotAccount);  
		ShowText(g_hwndLabel, msg);
	}

	//On Session Started by the user
	//lpUserAccount: user's account;
	//lpUserName:    user's nickname;
    //dwUserStatus:  user's initial status when he/she start the session with robot
    //dwType:         session open type
    //                OPENTYPE_UNKNOWN (0) - Unknown
	//                OPENTYPE_USER  (1) - User Open the conversation, bot can send welcome message to user
	//                OPENTYPE_RECONNECT (2) - Conversation is timeout, and reconnect automatically, bot no need to send welcome message to user
	//                OPENTYPE_BOT (3) - Bot Open the conversation, occurs after function CreateSession called
    //dwClientID:     user's MSN or Windows Live Messenger Client ID;
    //                This value can be a combination. You may check if the user's messesnger client supports wink:
    //                if (dwClientID & WINKS_SUPPORT) {//supports wink;} else {//not supports wink;}
	void WINAPI OnSessionOpen(LPCSTR lpBuddyAccount, LPCSTR lpBuddyName, DWORD dwBuddyStatus, DWORD dwType, DWORD dwClientID)
	{
		// if the conversation is opened by user, bot sends him/her welcome message
		sprintf(msg, "%s coming ...", lpBuddyAccount);  
		ShowText(g_hwndLabel, msg);
		if(1 == dwType)
		{
			sprintf(msg, "%s, Welcome!", lpBuddyName);
			BotCommand.SendMsg(lpBuddyAccount, msg);
		}
		if(3 == dwType)
		{
			sprintf(msg, "%s, I call you!", lpBuddyName);
			BotCommand.SendMsg(lpBuddyAccount, msg);
		}
	}
	
	//On conversation window closed by the user or the conversation timeout (after 1 minute idle)
	//lpBuddyAccount: user's account;
	void WINAPI OnSessionClose(LPCSTR lpBuddyAccount)
	{
		sprintf(msg, "%s leaving ...", lpBuddyAccount);  
		ShowText(g_hwndLabel, msg);
	}
	
	//responding to send file
	void WINAPI OnSendFileRespond(LPCSTR lpUserAccount, int iRespondCode)
	{
		sprintf(msg, "%s ::: %d", lpUserAccount, iRespondCode);  
		ShowText(g_hwndLabel, msg);
	}
	//responding to send background file
	void WINAPI OnSendBackgroundRespond(LPCSTR lpUserAccount, int iRespondCode)
	{
		sprintf(msg, "%s ::: %d", lpUserAccount, iRespondCode);  
		ShowText(g_hwndLabel, msg);
	}
	//responding to use webcam
	void WINAPI OnSendWebcamRespond(LPCSTR lpUserAccount, int iRespondCode)
	{
		sprintf(msg, "%s ::: %d", lpUserAccount, iRespondCode);  
		ShowText(g_hwndLabel, msg);
	}
	//user change his displayname or status
	void WINAPI OnUserStatusChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, DWORD dwUserStatus, LPCSTR lpUserName)
	{
		sprintf(msg, "%s ::: %s:::%d:::%s", lpBotAccount, lpUserAccount,dwUserStatus,lpUserName);  
		ShowText(g_hwndLabel, msg);
	}
	//user change his personal message
	void WINAPI OnUserPersonalMessageChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, LPCSTR lpPersonalMessage)
	{
		sprintf(msg, "%s ::: %s ::: %s", lpBotAccount, lpUserAccount,lpPersonalMessage);  
		ShowText(g_hwndLabel, msg);
	}
	
	//Exception occurs
	void WINAPI OnException(int iExceptionCode, LPCSTR lpExceptionReason, LPCSTR lpUserAccount, LPCSTR lpBotAccount)
	{
		sprintf(msg, "%d,: %s ...%s...,%s...", iExceptionCode,lpExceptionReason,lpUserAccount,lpBotAccount);  
		ShowText(g_hwndLabel, msg);
	}


} BotClient;


int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	
	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DEMOBOT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMOBOT));
	
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMOBOT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DEMOBOT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	//Set default BOTPLATFORM server address and port
	strcpy(szServer ,"msnbot.incesoft.com");
	iPort = 6602;

	HWND hWnd;
	
	hInst = hInstance; // Store instance handle in our global variable
	
	hWnd = CreateWindow(szWindowClass, szTitle, WS_TILEDWINDOW|DS_SETFONT,
		300, 200, 300, 240, NULL, NULL, hInstance, NULL);
	
	if (!hWnd)
	{
		return FALSE;
	}
	
	g_hwnd=hWnd;	
	
	RECT rect;
	GetClientRect(hWnd, &rect);
	
	g_hwndLabel = CreateWindowEx(WS_EX_STATICEDGE, "EDIT", "", WS_VISIBLE|WS_CHILD|ES_LEFT|ES_MULTILINE|ES_AUTOVSCROLL|WS_VSCROLL|ES_READONLY|ES_WANTRETURN, rect.left, rect.top,rect.right-rect.left, rect.bottom-rect.top, hWnd, NULL, hInstance, NULL);


	// Set font of g_hwndLabel to default GUI font
	
	SendMessage(g_hwndLabel, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), FALSE); 
	
	SetWindowText(g_hwndLabel, "Please click File, Login!");
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	return TRUE;
}



//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_Login:
			if(!BotClient.BotCommand.Init(&BotClient))
			{
				MessageBox(hWnd, "Incesoft Bot Platform SDK Init Error", "Init", MB_OK);
				break;
			}
			if (DialogBox(hInst, MAKEINTRESOURCE(IDD_LOGIN), hWnd, LoginDlg))
			{
				BotClient.BotCommand.Login(szUsername,szPassword, szServer, iPort);
			}
			break;
		case IDM_Logout:
			BotClient.BotCommand.Logout();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_SIZE:
		RECT rect;
		GetClientRect(hWnd, &rect);
		MoveWindow(g_hwndLabel, rect.left, rect.top,rect.right-rect.left, rect.bottom-rect.top, TRUE);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
BOOL CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
		
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

// Message handler for login dialog.
BOOL CALLBACK LoginDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	HWND hItem = NULL;
	switch (message)
	{
	case WM_INITDIALOG:
		hItem = GetDlgItem(hDlg, IDC_EDITSERVER);
		SetWindowText(hItem, szServer);
		hItem = GetDlgItem(hDlg, IDC_EDITPORT);
		TCHAR szPort[5];
		itoa(iPort, szPort, 10);
		SetWindowText(hItem, szPort );
		hItem = GetDlgItem(hDlg, IDC_EDITUSERNAME);
		SetWindowText(hItem, szUsername);
		hItem = GetDlgItem(hDlg, IDC_EDITPASSWORD);
		SetWindowText(hItem, szPassword);
		return TRUE;

	case WM_SHOWWINDOW:
		hItem = GetDlgItem(hDlg, IDC_EDITUSERNAME);
		SetFocus(hItem);
		return TRUE;
		
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			hItem = GetDlgItem(hDlg, IDC_EDITSERVER);
			GetWindowText(hItem, szServer, MAX_LOADSTRING);
			hItem = GetDlgItem(hDlg, IDC_EDITPORT);
			TCHAR szPort[5];
			GetWindowText(hItem, szPort, 5);
			iPort = atoi(szPort);
			if (iPort == 0)
				iPort = 6602;
			hItem = GetDlgItem(hDlg, IDC_EDITUSERNAME);
			GetWindowText(hItem, szUsername, MAX_LOADSTRING);
			hItem = GetDlgItem(hDlg, IDC_EDITPASSWORD);
			GetWindowText(hItem, szPassword, MAX_LOADSTRING);			
			EndDialog(hDlg, TRUE);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, FALSE);
			return TRUE;
		}
		break;
	}
	return FALSE;
}


