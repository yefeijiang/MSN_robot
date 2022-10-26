//---------------------------------------------------------------------------

#ifndef SignH
#define SignH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <StrUtils.hpp>
using namespace std;
//---------------------------------------------------------------------------
class TSignForm : public TForm
{
__published:	// IDE-managed Components
    TADOQuery *ADOQuery1;
    TADOConnection *ADOConnection1;
    TTimer *Timer1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TSignForm(TComponent* Owner);
    //---------------------------------------------------------------------------
    int InsertUserSign(AnsiString msn,AnsiString sign);
    bool DeleteUserSign(AnsiString msn,int id);
    bool UserSignUpdate(string msn,string sign);
    map<string, string> sign_map;     //'fjye@hotmail.com','蚕食桑，所吐丝也，非桑也'
    map<string, string> sign_msn_map;     //'蚕食桑，所吐丝也，非桑也','fjye@hotmail.com'
    map<string,int>  votelimit;
    AnsiString HotTopn(int page=1,int pagecount=10);
    AnsiString GetHistorySign(AnsiString msn,int page=1,int pagecount=10);
    AnsiString QuerySameSign(AnsiString msn,AnsiString sign);
    AnsiString QuerySameSignUser(AnsiString msn,AnsiString sign);
    AnsiString GetRandomSign();
    bool VoteSign(string msn,int signID);
    AnsiString fillString(AnsiString fill,int maxlength);
    void LoadNewestSign();
    void LoadAllSign();
    AnsiString helpinfo();
    void answerMSG(LPCSTR lpUserAccount, LPCSTR lpMsg);
    AnsiString BotName;
    int getint(AnsiString str);
    AnsiString kickspaceial(AnsiString str);
    TStringList *pMSN;
    TStringList *pAllMSg;
    TStringList *helpString;
    //---------------------------------------------------------------------------
};
//---------------------------------------------------------------------------
extern PACKAGE TSignForm *SignForm;
//---------------------------------------------------------------------------
#endif
