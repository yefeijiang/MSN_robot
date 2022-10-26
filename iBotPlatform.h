// Copyright (C) 2001-2007 Incesoft Co.,Ltd.
// All rights reserved.

// @author Purple
// This source code is the head file of iBotPlatform.dll (version 2.0.0.0)
// iBotPlatform.dll is a dynamic link library of iBot Platform C++ SDK
// See these sources for detailed information regarding the
// document of SDK.

#ifndef _IBOTPLATFORMCLIENT_H
#define _IBOTPLATFORMCLIENT_H

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef EXPORT
	#define DLL_API extern "C" __declspec(dllexport)
#else
	#define DLL_API __declspec(dllimport)
#endif

//pre defines of initial user status
const DWORD STATUS_UNKNOWN= 0;
const DWORD STATUS_ONLINE = 1;
const DWORD STATUS_OFFLINE= 2;
const DWORD STATUS_HIDDEN = 3;
const DWORD STATUS_BUSY   = 4;
const DWORD STATUS_IDLE   = 5;
const DWORD STATUS_BE_RIGHT_BACK = 6;
const DWORD STATUS_AWAY = 7;
const DWORD STATUS_ON_THE_PHONE = 8;
const DWORD STATUS_OUT_TO_LUNCH = 9;

//pre defines of open type of the conversation
const DWORD OPENTYPE_UNKNOWN = 0;
const DWORD OPENTYPE_USER  = 1;
const DWORD OPENTYPE_RECONNECT = 2;
const DWORD OPENTYPE_BOT   =3;

//pre defines of user's respond to the activity
const int ACTIVITY_ACCEPT  = 0;
const int ACTIVITY_DECLINE = 1;
const int ACTIVITY_LOADED  = 3;
const int ACTIVITY_CLOSED  = 4;
const int ACTIVITY_UNKNOWN = 2;

//pre defines of respond to file sending
const int SENDFILE_ACCEPT  = 0;
const int SENDFILE_DECLINE = 1;
const int SENDFILE_END     = 2;

//pre defines of respond to webcam
const int WEBCAM_ACCEPT  = 0;
const int WEBCAM_DECLINE = 1;

//pre defines of client id of MSN or Windows Live Messenger
const DWORD MOBILE_CLIENT = 0x00000001;      //User is online via Mobile
const DWORD MSN_CLIENT = 0x00000002;         //User online with the MSN client
const DWORD GIF_INK_AWARENESS = 0x00000004;  //User online GIF/ink awareness
const DWORD ISF_INK_AWARENESS = 0x00000008;  //User online ISF/ink awareness
const DWORD WEB_CAMERA = 0x00000010;         //There is a web camera on user's machine
const DWORD MSG_CHUNKING = 0x00000020;       //Support of message chunking (to allow larger messages over SB)
const DWORD MOBILE_IM = 0x00000040;          //Mobile IMs permitted flag
const DWORD DIRECT_WATCH = 0x00000080;       //Direct Watch enabled flag
const DWORD WEB_CLIENT = 0x00000200;         //The user is online via the web client
const DWORD MOBILE_BUDDY = 0x00000400;       //The user is a mobile buddy.
const DWORD FEDERATED_BUDDY = 0x00000800;    //The user is a federated client.
const DWORD MSN_SPACE = 0x00001000;          //The user has its HasSpace bit set
const DWORD P2P_IM = 0x00004000;             //The user supports Peer-to-Peer IM
const DWORD WINKS_SUPPORT = 0x00008000;      //The user supports Winks
const DWORD CLIENT_VERSION_6_0 = 0x10000000; //Client version 6.0
const DWORD CLIENT_VERSION_6_1 = 0x20000000; //Client version 6.1
const DWORD CLIENT_VERSION_6_2 = 0x30000000; //Client version 6.2
const DWORD CLIENT_VERSION_7_0 = 0x40000000; //Client version 7.0

//pre defines of Font Color
const DWORD FONT_COLOR_RANDOM   = 0xFFFFFFFF;
const DWORD FONT_COLOR_RED      = 0xFF0000;
const DWORD FONT_COLOR_GREEN    = 0x00FF00;
const DWORD FONT_COLOR_BLUE     = 0x0000FF;
const DWORD FONT_COLOR_YELLOW   = 0xFFFF00;
const DWORD FONT_COLOR_PURPLE   = 0xFF00FF;
const DWORD FONT_COLOR_BLACK    = 0x000000;
const DWORD FONT_COLOR_WHILE    = 0xFFFFFF;

//pre defines of Font Style
const DWORD FONT_STYLE_NONE = 0x0;
const DWORD FONT_STYLE_BOLD = 0x00000001;
const DWORD FONT_STYLE_ITALIC = 0x00000002;
const DWORD FONT_STYLE_UNDERLINE = 0x00000004;
const DWORD FONT_STYLE_STRIKE = 0x00000008;
const DWORD FONT_STYLE_BOLD_ITALIC = FONT_STYLE_BOLD | FONT_STYLE_ITALIC;
const DWORD FONT_STYLE_ALL = FONT_STYLE_BOLD | FONT_STYLE_ITALIC | FONT_STYLE_UNDERLINE | FONT_STYLE_STRIKE;


class  CBotEvent
{
public:
    CBotEvent(){};
    virtual ~CBotEvent(){};

	//Login Result Event
	//iErrCode: 0 - Login Success
    //          1 - Login Error
  	//lpErrString:  Login error description
	virtual void WINAPI OnLogin(int iErrCode, LPCSTR lpErrString){};

    //Logout Result Event
    //Bot Client disconnected from the iBot Platform
    //iErrCode: 0 - normally logout, occurs after CBotCommand::Logout called
    //          1 - error occurs
    virtual void WINAPI OnLogout(int iErrCode){};

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
    virtual void WINAPI OnSessionOpen(LPCSTR lpUserAccount, LPCSTR lpUserName, DWORD dwUserStatus, DWORD dwOpenType, DWORD dwClientID){};

	//On conversation window closed by the user or the conversation timeout (after 1 minute idle)
	//lpUserAccount: user's account;
	virtual void WINAPI OnSessionClose(LPCSTR lpUserAccount){};

	//Bot receive messages from rser
	//lpUserAccount:  User's account
	//lpMsg: Message from user
    //lpFontName: Message Font Name form user, for example: Times New Roman
    //dwFontColor: Message Font Color from user, the RGB value the color, for example: 0xFF0000 - Red
    //dwFontStyle: Message Font Style from user, the combination of pre defined font style value
	virtual void WINAPI OnUserMsg(LPCSTR lpUserAccount, LPCSTR lpMsg, LPCSTR lpFontName, DWORD dwFontColor, DWORD dwFontStyle){};

	//Bot receive nudge from user
	//lpUserAccount:  User's account
	virtual void WINAPI OnUserNudge(LPCSTR lpUserAccount){};

	//responding to activity invitation
	//lpUserAccount:  User's account
    //iRespondCode: Responding event after user receive an activity invitation
    //              ACTIVITY_ACCEPT  (0): User acccept the invitation
    //              ACTIVITY_DECLINE (1): User decline the invitation
    //              ACTIVITY_LOADED  (3): the activity load complete
    //              ACTIVITY_CLOSED  (4): User close the activity window
    //              ACTIVITY_UNKNOWN (2): Unknown event
	virtual void WINAPI OnActivityRespond(LPCSTR lpUserAccount, int iRespondCode){};

	//user add the bot to his friend list
    //lpBotAccount: Bot's account
	//lpUserAccount:  User's account
	virtual void WINAPI OnUserAdd(LPCSTR lpBotAccount, LPCSTR lpUserAccount){};

	//user remove the bot from his friend list
    //lpBotAccount: Bot's account
	//lpUserAccount:  User's account
	virtual void WINAPI OnUserRemove(LPCSTR lpBotAccount, LPCSTR lpUserAccount){};

    //user change his displayname or status
    //lpBotAccount: Bot's account
    //lpUserAccount: User's account
    //dwUserStatus:  User's new status
    //lpUserName:    User's new display name
    virtual void WINAPI OnUserStatusChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, DWORD dwUserStatus, LPCSTR lpUserName){};


    //user change his personal message
    //lpBotAccount: Bot's account
    //lpUserAccount: User's account
    //lpUserPersonalMessage: User's personal message
    virtual void WINAPI OnUserPersonalMessageChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, LPCSTR lpPersonalMessage){};

	//responding to send file
	//lpUserAccount:  User's account
    //iRespondCode:
    //              SENDFILE_ACCEPT  (0): User acccept the file
    //              SENDFILE_DECLINE (1): User decline the file
    //              SENDFILE_END     (2): File send finished
	virtual void WINAPI OnSendFileRespond(LPCSTR lpUserAccount, int iRespondCode){};

	//responding to send background file
	//lpUserAccount:  User's account
    //iRespondCode:
    //              SENDFILE_ACCEPT  (0): User acccept the background file
    //              SENDFILE_DECLINE (1): User decline the background file
    //              SENDFILE_END     (2): Background file send finished
	virtual void WINAPI OnSendBackgroundRespond(LPCSTR lpUserAccount, int iRespondCode){};

	//responding to use webcam
	//lpUserAccount:  User's account
    //iRespondCode:
    //              WEBCAM_ACCEPT  (0): User acccept the file
    //              WEBCAM_DECLINE (1): User decline the file
	virtual void WINAPI OnSendWebcamRespond(LPCSTR lpUserAccount, int iRespondCode){};

    //Exception occurs
    //iExceptionCode: Exception Code
    //lpExceptionReason: Description of the Exception
    //lpUserAccount: Corresponding user's account
    //lpBotAccount:  Corresponding bot's account
	virtual void WINAPI OnException(int iExceptionCode, LPCSTR lpExceptionReason, LPCSTR lpUserAccount, LPCSTR lpBotAccount){};

};


//Dll functions exported from "BotClient.dll"
typedef BOOL (WINAPI* fpInit)(CBotEvent *pEvent);
typedef	BOOL (WINAPI* fpLogin)(LPCSTR lpSPID, LPCSTR lpSPPWD, LPCSTR lpSPPS, int SPPSPort);
typedef	BOOL (WINAPI* fpLogout)(void);
typedef	BOOL (WINAPI* fpSendMsg)(LPCSTR lpUserAccount, LPCSTR lpMsg, LPCSTR lpEmotion, LPCSTR lpBotName, LPCSTR lpFontName, DWORD dwFontColor, DWORD dwFontStyle);
typedef	BOOL (WINAPI* fpSendTyping)(LPCSTR lpUserAccount);
typedef	BOOL (WINAPI* fpSendNudge)(LPCSTR lpUserAccount);
typedef	BOOL (WINAPI* fpSendActivity)(LPCSTR lpUserAccount, LPCSTR lpUrl, LPCSTR lpAppName);
typedef BOOL (WINAPI* fpChangeDisplayName)(LPCSTR lpDisplayName);
typedef BOOL (WINAPI* fpChangePersonalMessage)(LPCSTR lpMessage);
typedef BOOL (WINAPI* fpChangeDisplayPicture)(LPCSTR lpUri);

//functions below only for enterprise or professional developers
typedef BOOL (WINAPI* fpCreateSession)(LPCSTR lpUserAccount, LPCSTR lpBotAccount);
typedef BOOL (WINAPI* fpInviteUserToSession)(LPCSTR lpUserAccount, LPCSTR lpNewUserAccount);
typedef BOOL (WINAPI* fpPushMsg)(LPCSTR lpUserAccount, LPCSTR lpBotAccount, LPCSTR lpMsg);
typedef BOOL (WINAPI* fpSendFile)(LPCSTR lpUserAccount, LPCSTR lpUri, LPCSTR lpResourceName);
typedef BOOL (WINAPI* fpSendBackground)(LPCSTR lpUserAccount, LPCSTR lpUri, LPCSTR lpResourceName);
typedef BOOL (WINAPI* fpSendInk)(LPCSTR lpUserAccount, LPCSTR lpUri);
typedef BOOL (WINAPI* fpSendWink)(LPCSTR lpUserAccount, LPCSTR lpUri, LPCSTR lpStamp);
typedef BOOL (WINAPI* fpSendVoiceclip)(LPCSTR lpUserAccount, LPCSTR lpUri);
typedef BOOL (WINAPI* fpSendWebcam)(LPCSTR lpUserAccount, LPCSTR lpServerIP, int iServerPort, int iRecipientId, int iSessionId);



class  CBotCommand
{

private:
	fpInit		   m_fpInit;
	fpLogin		   m_fpLogin;
	fpLogout	   m_fpLogout;
	fpSendMsg	   m_fpSendMsg;
    fpSendTyping   m_fpSendTyping;
	fpSendNudge	   m_fpSendNudge;
	fpSendActivity	   m_fpSendActivity;
    fpChangeDisplayName m_fpChangeDisplayName;
    fpChangePersonalMessage m_fpChangePersonalMessage;
    fpChangeDisplayPicture m_fpChangeDisplayPicture;
	fpInviteUserToSession	   m_fpInviteUser;
	fpCreateSession	    m_fpCreateSession;
	fpPushMsg	        m_fpPushMsg;
    fpSendFile          m_fpSendFile;
    fpSendBackground    m_fpSendBackground;
    fpSendInk           m_fpSendInk;
    fpSendWink          m_fpSendWink;
    fpSendVoiceclip     m_fpSendVoiceclip;
    fpSendWebcam        m_fpSendWebcam;

	HINSTANCE 	   m_hInstance;

public:
	CBotCommand()
	{
		m_hInstance	  = NULL;
		m_fpInit   = NULL;
		m_fpLogin	= NULL;
		m_fpLogout	= NULL;
		m_fpSendMsg   = NULL;
        m_fpSendTyping   = NULL;
		m_fpSendNudge   = NULL;
		m_fpSendActivity   = NULL;
        m_fpChangeDisplayName = NULL;
        m_fpChangePersonalMessage = NULL;
        m_fpChangeDisplayPicture = NULL;
        m_fpInviteUser = NULL;
        m_fpCreateSession = NULL;
        m_fpPushMsg = NULL;
	}

	virtual ~CBotCommand()
	{
		if (NULL != m_hInstance)
		{
			FreeLibrary(m_hInstance);
			m_hInstance = NULL;
		}
	}

	BOOL Init(CBotEvent* pBotEvent)
	{
		m_hInstance = LoadLibrary("iBotPlatform.dll");
 	    if(NULL == m_hInstance) return FALSE;

		if(
			   (NULL == (m_fpInit  = (fpInit)GetProcAddress(m_hInstance, "Init")))
			|| (NULL == (m_fpLogin = (fpLogin)GetProcAddress(m_hInstance, "Login")))
			|| (NULL == (m_fpLogout= (fpLogout)GetProcAddress(m_hInstance, "Logout")))
			|| (NULL == (m_fpSendNudge= (fpSendNudge)GetProcAddress(m_hInstance, "SendNudge")))
			|| (NULL == (m_fpSendMsg  = (fpSendMsg)GetProcAddress(m_hInstance, "SendMsg")))
			|| (NULL == (m_fpSendTyping  = (fpSendTyping)GetProcAddress(m_hInstance, "SendTyping")))
			|| (NULL == (m_fpSendActivity = (fpSendActivity)GetProcAddress(m_hInstance, "SendActivity")))
			|| (NULL == (m_fpChangeDisplayName  = (fpChangeDisplayName)GetProcAddress(m_hInstance, "ChangeDisplayName")))
			|| (NULL == (m_fpChangePersonalMessage  = (fpChangePersonalMessage)GetProcAddress(m_hInstance, "ChangePersonalMessage")))
			|| (NULL == (m_fpChangeDisplayPicture  = (fpChangeDisplayPicture)GetProcAddress(m_hInstance, "ChangeDisplayPicture")))
			|| (NULL == (m_fpInviteUser  = (fpInviteUserToSession)GetProcAddress(m_hInstance, "InviteUser")))
			|| (NULL == (m_fpCreateSession  = (fpCreateSession)GetProcAddress(m_hInstance, "CreateSession")))
			|| (NULL == (m_fpPushMsg  = (fpPushMsg)GetProcAddress(m_hInstance, "PushMsg")))
			|| (NULL == (m_fpSendFile  = (fpSendFile)GetProcAddress(m_hInstance, "SendFile")))
			|| (NULL == (m_fpSendBackground  = (fpSendBackground)GetProcAddress(m_hInstance, "SendBackground")))
			|| (NULL == (m_fpSendInk  = (fpSendInk)GetProcAddress(m_hInstance, "SendInk")))
			|| (NULL == (m_fpSendWink  = (fpSendWink)GetProcAddress(m_hInstance, "SendWink")))
			|| (NULL == (m_fpSendVoiceclip  = (fpSendVoiceclip)GetProcAddress(m_hInstance, "SendVoiceclip")))
			|| (NULL == (m_fpSendWebcam  = (fpSendWebcam)GetProcAddress(m_hInstance, "SendWebcam")))
			)
		{
			return FALSE;
		}

		return m_fpInit(pBotEvent);
	}

    //Connect to Incesoft Bot Platform Cloud
    //lpSPID  : Service Provider ID, assigned by Incesoft
    //lpSPPWD : Service Provider ID Password, assigned by Incesoft
    //lpSPPS  : Service Provider Proxy Server Address, like msnbot.incesoft.com
    //SPPSPort: Service Provider Proxy Server Port, default is 6602
    //Event OnLogin will occurs after this function called
	BOOL Login(LPCSTR lpSPID, LPCSTR lpSPPWD, LPCSTR lpSPPS, int SPPSPort=6602)
	{
		return m_fpLogin(lpSPID, lpSPPWD, lpSPPS, SPPSPort);
	}

    //Disconnect from Incesoft Bot Platform Cloud
    //Event OnLogout will occurs with errcode=0 after this function called successfully
	BOOL Logout(void)
	{
		return m_fpLogout();
	}

    //Send Message to user in conversation
    //return non-zero means success
    //return zero means fail, such as user has left the conversation or other exceptions
    //lpUserAccount:  user's account
    //lpMsg:           text message, such as "I'm xiaoi"
    //lpEmotion:       custom emotion, such as "xiaoi=emoticon.gif", emotion.gif must be registered to Incesoft Bot Platform
    //lpBotName:       custom signature of Bot Name
    //lpFontName:      set the font name of the message, for example: "Times New Roman"
    //dwFontColor:     set the font color (RGB value) of the message, for example: FF0000 (RED)
    //dwFontStyle:     set the font style of the message, for example: FONT_STYLE_BOLD | FONT_STYLE_ITALIC
	BOOL SendMsg(LPCSTR lpUserAccount,
                 LPCSTR lpMsg,
                 LPCSTR lpEmotion="",
                 LPCSTR lpBotName="",
                 LPCSTR lpFontName="",
                 DWORD dwFontColor=FONT_COLOR_RANDOM,
                 DWORD dwFontStyle=FONT_STYLE_NONE )
	{
		return m_fpSendMsg(lpUserAccount,lpMsg, lpEmotion, lpBotName, lpFontName, dwFontColor, dwFontStyle);
	}

    //Send a nudge to user in conversation
    //return non-zero means success
    //return zero means fail, such as user has left the conversation or other exceptions
    //lpUserAccount:  user's account
	BOOL SendNudge(LPCSTR lpUserAccount)
	{
		return m_fpSendNudge(lpUserAccount);
	}

    //Send a web page in activity window to user in conversation
    //return non-zero means success
    //return zero means fail, such as user has left the conversation or other exceptions
    //lpUserAccount:  user's account
    //lpUrl:       URL of the web page, such as "http://www.live.com" (must started with http://)
    //lpAppName:       the application name of the activity invitation, null will be replaced with the default name
	BOOL SendActivity(LPCSTR lpUserAccount, LPCSTR lpUrl, LPCSTR lpAppName="")
	{
		return m_fpSendActivity(lpUserAccount,lpUrl, lpAppName);
	}

    //Send typing message to user in conversation
    //return non-zero means success
    //return zero means fail, such as user has left the conversation or other exceptions
    //lpUserAccount:  user's account
	BOOL SendTyping(LPCSTR lpUserAccount)
	{
		return m_fpSendTyping(lpUserAccount);
	}

    //Change the display name of robot
    //return non-zero means success
    //return zero means fail
    //lpDisplayName:  display name of the robot, max length is 40 Characters
    BOOL ChangeDisplayName(LPCSTR lpDisplayName)
    {
        return m_fpChangeDisplayName(lpDisplayName);
    }

    //Change the personal message of robot
    //return non-zero means success
    //return zero means fail
    //lpMessage:  personal message of the robot, max length is 80 Characters
    BOOL ChangePersonalMessage(LPCSTR lpMessage)
    {
        return m_fpChangePersonalMessage(lpMessage);
    }

    //Change the display picture of robot
    //return non-zero means success
    //return zero means fail
    //lpUri:  the resource name of display pictures, which has uploaded to Incesoft Bot Platform and has been validated
    //        if the lpUri is invalid, the display picture of the robot will be changed to a default one
    BOOL ChangeDisplayPicture(LPCSTR lpUri)
    {
        return m_fpChangeDisplayPicture(lpUri);
    }

    BOOL InviteUserToSession(LPCSTR lpUserAccount, LPCSTR lpNewUserAccount)
    {
        return m_fpInviteUser(lpUserAccount, lpNewUserAccount);
    }

    BOOL CreateSession(LPCSTR lpUserAccount, LPCSTR lpBotAccount)
    {
        return m_fpCreateSession(lpUserAccount, lpBotAccount);
    }

    BOOL PushMsg(LPCSTR lpUserAccount, LPCSTR lpBotAccount, LPCSTR lpMsg)
    {
        return m_fpPushMsg(lpUserAccount, lpBotAccount, lpMsg);
    }

    BOOL SendFile(LPCSTR lpUserAccount, LPCSTR lpUri, LPCSTR lpResourceName)
    {
        return m_fpSendFile(lpUserAccount, lpUri, lpResourceName);
    }

    BOOL SendBackground(LPCSTR lpUserAccount, LPCSTR lpUri, LPCSTR lpResourceName)
    {
        return m_fpSendBackground(lpUserAccount, lpUri, lpResourceName);
    }

    BOOL SendInk(LPCSTR lpUserAccount, LPCSTR lpUri)
    {
        return m_fpSendInk(lpUserAccount, lpUri);
    }

    BOOL SendWink(LPCSTR lpUserAccount, LPCSTR lpUri, LPCSTR lpStamp)
    {
        return m_fpSendWink(lpUserAccount, lpUri, lpStamp);
    }

    BOOL SendVoiceclip(LPCSTR lpUserAccount, LPCSTR lpUri)
    {
        return m_fpSendVoiceclip(lpUserAccount, lpUri);
    }

    BOOL SendWebcam(LPCSTR lpUserAccount, LPCSTR lpServerIP, int iServerPort, int iRecipientId, int iSessionId)
    {
        return m_fpSendWebcam(lpUserAccount, lpServerIP, iServerPort, iRecipientId, iSessionId);
    }

};//end class define

#endif
