//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Sign.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------

//class CDemoto is declared in Unit1.h

//iErrCode = 0, Login Success,
//iErrCode = 1, Login Fail,
//iErrCode = 2, Login Fail, will reconnect automatically
//lpErrString describs the error details
void WINAPI CDemoBot::OnLogin(int iErrCode, LPCSTR lpErrString)
{
    AnsiString info = "["+Now().DateTimeString()+"]Login iBot Platform Server: ("+String(iErrCode)+") "+String(lpErrString);
    MainForm->addlog(info);
}

//iErrCode = 0, disconnect from server after the Logout command,
//iErrCode = 1, disconnect form server due to network or server error
void WINAPI CDemoBot::OnLogout(int iErrCode)
{
    AnsiString info = "["+Now().DateTimeString()+"]Logout from iBot Platform Server: "+String(iErrCode);
    MainForm->addlog(info);
}

void WINAPI CDemoBot::OnUserMsg(LPCSTR lpUserAccount, LPCSTR lpMsg, LPCSTR lpFontName, DWORD dwFontColor, DWORD dwFontStyle)
{
     AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+": "+String(lpMsg);
     MainForm->addlog(info);
     AnsiString str=lpMsg;
     str=str.Trim().LowerCase();
     if(str.AnsiPos("http://") == 1)
     {
        MainForm->DemoBot.BotCommand.SendActivity(lpUserAccount, str.c_str(), "活动窗口1");
     }
     else if(str.AnsiPos("www.") == 1)
     {
        str="http://"+str;
        MainForm->DemoBot.BotCommand.SendActivity(lpUserAccount, str.c_str(), "活动窗口2");
     }
     else if(str == "nudge")
     {
        MainForm->DemoBot.BotCommand.SendNudge(lpUserAccount);
     }
     else if(str == "emo")
     {
        MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "message with emotion (xiaosign)", "(xiaosign)=xiaosign.png");
     }
     else if(str == "sig")
     {
        MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, (String("RE: ")+lpMsg).c_str(), "", SignForm->BotName.c_str());
     }
     else
     {
        SignForm->answerMSG(lpUserAccount, lpMsg);
        //MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, (String("RE: ")+lpMsg).c_str(), "", "", lpFontName, dwFontColor, dwFontStyle);
     }
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnUserNudge(LPCSTR lpUserAccount)
{
     AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+": <nudge>";
     MainForm->addlog(info);
     SignForm->answerMSG(lpUserAccount, "HELP");
     //MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "a nudge received", "", "Bot Demo");
}

//---------------------------------------------------------------------------
void WINAPI CDemoBot::OnActivityRespond(LPCSTR lpUserAccount, int iRespondCode)
{
    AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+ "..."+String(iRespondCode);
    MainForm->addlog(info);
    switch(iRespondCode)
    {
        case ACTIVITY_ACCEPT://  (0): User Acccept the invitation
            MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "you accept the activity, please waiting...");
            break;
        case ACTIVITY_DECLINE:// (1): User Decline the invitation
            MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "you decline the activity, why?");
            break;
        case ACTIVITY_LOADED://  (3): the activity load complete
            MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "the activity window loaded, please look right side!");
            break;
        case ACTIVITY_CLOSED://  (4): User close the activity window
            MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "you close the activity window!");
            break;
    }

}
//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnUserAdd(LPCSTR lpBotAccount, LPCSTR lpUserAccount)
{
    AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+" add "+String(lpBotAccount);
    MainForm->addlog(info);
    MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "你好，欢迎您将MSN签名管家加为好友，我会好好的保管您的签名的");
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnUserRemove(LPCSTR lpBotAccount, LPCSTR lpUserAccount)
{
    AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+" remove "+String(lpBotAccount);
    MainForm->addlog(info);
    MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "好可惜哦，真的要删掉MSN签名管家吗?");
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnUserStatusChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, DWORD dwUserStatus, LPCSTR lpUserName)
{
    AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+" status="+String(dwUserStatus)+" name="+String(lpUserName);
    MainForm->addlog(info);
}
//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnUserPersonalMessageChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, LPCSTR lpPersonalMessage)
{
    if(SignForm->UserSignUpdate(lpUserAccount,Trim(AnsiString(lpPersonalMessage)).c_str()))
        {
        SignForm->InsertUserSign(lpUserAccount,lpPersonalMessage);
        }
    AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+" personalmessage="+String(lpPersonalMessage);
    MainForm->addlog(info);
}
//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnSessionOpen(LPCSTR lpUserAccount, LPCSTR lpUserName, DWORD dwUserStatus, DWORD dwOpenType, DWORD dwClientID)
{
    AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+" ("+String(lpUserName)+") in ...";
    MainForm->addlog(info);
     switch(dwOpenType)
     {
        case 1:
            MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, (String(lpUserName)+", 欢迎您!我是你的MSN签名管家\r 输入 \"http://www.YEStudio.cn\" 参观我的老家").c_str());
            break;
        case 3:
            MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, (String(lpUserName)+", I call you!\r 输入 \"http://www.YEStudio.cn\" 参观我的老家").c_str());
            break;
     }
}
//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnSessionClose(LPCSTR lpUserAccount)
{
    AnsiString info = String(lpUserAccount)+" leaving ...";
    MainForm->addlog(info);
}

void WINAPI CDemoBot::OnSendFileRespond(LPCSTR lpUserAccount, int iRespondCode)
{
    AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+" sendfilecode="+String(iRespondCode);
    MainForm->addlog(info);
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnSendBackgroundRespond(LPCSTR lpUserAccount, int iRespondCode)
{
    AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+" sendbgcode="+String(iRespondCode);
    MainForm->addlog(info);
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnSendWebcamRespond(LPCSTR lpUserAccount, int iRespondCode)
{
    AnsiString info = "["+Now().DateTimeString()+"]"+String(lpUserAccount)+" sendwebcamecode="+String(iRespondCode);
    MainForm->addlog(info);
}
//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnException(int iExceptionCode, LPCSTR lpExceptionReason, LPCSTR lpUserAccount, LPCSTR lpBotAccount)
{
    AnsiString info = "["+Now().DateTimeString()+"]Exception - "+String(iExceptionCode)+": "+String(lpExceptionReason)+" (user="+String(lpUserAccount)+", bot="+String(lpBotAccount);
    MainForm->addlog(info);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
    if(Edit1->Text.IsEmpty() || Edit2->Text.IsEmpty())
    {
    AnsiString info = "Please fill up the SPID & SPPWD before Login";
    MainForm->addlog(info);
        //MessageBox(Handle, "Please fill up the SPID & SPPWD before Login", "Information", MB_OK);
        return;
    }
    MainForm->DemoBot.BotCommand.Login(Edit1->Text.c_str(), Edit2->Text.c_str(), Edit3->Text.c_str(), Edit4->Text.ToIntDef(6602));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
    if(DemoBot.BotCommand.Init(&DemoBot))
    {
        Memo1->Lines->Add("Init iBot Platform C++ SDK OK");
    }
    else
    {
        Memo1->Lines->Add("Init iBot Platform C++ SDK Error");
    }
    LoadIniFile();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    SaveIniFile();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Button2Click(TObject *Sender)
{
    DemoBot.BotCommand.Logout();
}
//---------------------------------------------------------------------------

void TMainForm::LoadIniFile(void)
{
    TIniFile * file=new TIniFile(ExtractFilePath(Application->ExeName)+"YEStudioBot.ini");

    Edit1->Text=file->ReadString("bot", "1", "");
    Edit2->Text=file->ReadString("bot", "2", "");
    Edit3->Text=file->ReadString("bot", "3", "http://www.YEStudio.cn");
    Edit4->Text=file->ReadString("bot", "4", "6602");
    delete file;
}

//---------------------------------------------------------------------------

void TMainForm::SaveIniFile(void)
{
    TIniFile * file=new TIniFile(ExtractFilePath(Application->ExeName)+"YEStudioBot.ini");

    file->WriteString("bot", "1", Edit1->Text);
    file->WriteString("bot", "2", Edit2->Text);
    file->WriteString("bot", "3", Edit3->Text);
    file->WriteString("bot", "4", Edit4->Text);

    delete file;
}
void __fastcall TMainForm::Button3Click(TObject *Sender)
{
    MainForm->DemoBot.BotCommand.SendMsg(Edit5->Text.c_str(), Memo2->Text.c_str(), "", SignForm->BotName.c_str());
    //MainForm->DemoBot.OnUserPersonalMessageChanged("",Edit5->Text.c_str(), Memo2->Text.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button4Click(TObject *Sender)
{
//    Memo1->Lines->Add(GetHistorySign("fjye@hotmail.com",2));
    //Memo1->Lines->Add(SignForm->HotTopn());
    //Memo1->Lines->Add(SignForm->GetHistorySign(Edit5->Text,4,5));
    SignForm->answerMSG(Edit5->Text.c_str(),Memo2->Text.c_str()) ;
    //Memo1->Lines->Add(SignForm->QuerySameSign(Edit5->Text,Memo2->Text));
}
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    Button1Click(NULL);    
}
//---------------------------------------------------------------------------
void TMainForm::addlog(AnsiString inf)
{
    //TODO: Add your source code here
    if(CheckBox1->Checked)
        {
        MainForm->Memo1->Lines->Add(inf);
        }
    TDateTime now;
    now = now.CurrentDateTime();
    AnsiString date;
    date = now.FormatString("yyyy-mm-dd");
    //Memo2->Lines->Add("["+date+"] "+inf);
    //fstream fp;
    AnsiString path;
    path = ExtractFilePath(Application->ExeName);
    path = path+"log\\"+date+".txt";
    char *p;
    p = path.c_str();
    FILE *fp;
    if(FileExists(path))
        {
        fp=fopen(p,"a");
        if(fp)
            {
            p = inf.c_str();
            fputc(0x0a,fp);
            fputs(p,fp);
            }
        }
    else
        {
        fp=fopen(p,"wt+");
        if(fp)
            {
            p = inf.c_str();
            fputs(p,fp);
            }
        }
    fclose(fp);
}
