//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <INIFILES.hpp>
#include <ScktComp.hpp>


#include "iBotPlatform.h"
#include <ADODB.hpp>
#include <DB.hpp>
class CDemoBot: public CBotEvent
{
public:
	void WINAPI OnLogin(int iErrCode, LPCSTR lpErrString);
        void WINAPI OnLogout(int iErrCode);
	void WINAPI OnSessionOpen(LPCSTR lpUserAccount, LPCSTR lpUserName, DWORD dwUserStatus, DWORD dwOpenType, DWORD dwClientID);
	void WINAPI OnSessionClose(LPCSTR lpUserAccount);
	void WINAPI OnUserMsg(LPCSTR lpUserAccount, LPCSTR lpMsg, LPCSTR lpFontName, DWORD dwFontColor, DWORD dwFontStyle);
	void WINAPI OnUserNudge(LPCSTR lpUserAccount);
        void WINAPI OnActivityRespond(LPCSTR lpUserAccount, int iRespondCode);
        void WINAPI OnUserAdd(LPCSTR lpBotAccount, LPCSTR lpUserAccount);
	void WINAPI OnUserRemove(LPCSTR lpBotAccount, LPCSTR lpUserAccount);
        void WINAPI OnUserStatusChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, DWORD dwUserStatus, LPCSTR lpUserName);
        void WINAPI OnUserPersonalMessageChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, LPCSTR lpPersonalMessage);
	void WINAPI OnSendFileRespond(LPCSTR lpUserAccount, int iRespondCode);
	void WINAPI OnSendBackgroundRespond(LPCSTR lpUserAccount, int iRespondCode);
	void WINAPI OnSendWebcamRespond(LPCSTR lpUserAccount, int iRespondCode);
        void WINAPI OnException(int iExceptionCode, LPCSTR lpExceptionReason, LPCSTR lpUserAccount, LPCSTR lpBotAccount);
        CBotCommand BotCommand;
};


//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
    TPanel *Panel1;
    TButton *Button1;
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TButton *Button2;
    TEdit *Edit4;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TButton *Button3;
    TEdit *Edit5;
    TEdit *Edit6;
    TADOConnection *ADOConnection1;
    TADOQuery *ADOQuery1;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
    void LoadIniFile(void);
    void SaveIniFile(void);
public:		// User declarations
    __fastcall TMainForm(TComponent* Owner);
    bool guess(AnsiString GUESS1234,AnsiString BE1357,AnsiString Resule1A2B);
    CDemoBot DemoBot;
    AnsiString queryhanzi(AnsiString hanzi);
    AnsiString BCD_to_AnsiString(char *P_BCD, int length);
    AnsiString AnsiString_to_BCD(AnsiString wait_to_trans);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
