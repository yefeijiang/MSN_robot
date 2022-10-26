//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include   <StrUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner)
{
    ADOConnection1->Connected = true;
}
//---------------------------------------------------------------------------

//class CDemoto is declared in Unit1.h

//iErrCode = 0, Login Success,
//iErrCode = 1, Login Fail,
//iErrCode = 2, Login Fail, will reconnect automatically
//lpErrString describs the error details
void WINAPI CDemoBot::OnLogin(int iErrCode, LPCSTR lpErrString)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]Login iBot Platform Server: ("+String(iErrCode)+") "+String(lpErrString));
}

//iErrCode = 0, disconnect from server after the Logout command,
//iErrCode = 1, disconnect form server due to network or server error
void WINAPI CDemoBot::OnLogout(int iErrCode)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]Logout from iBot Platform Server: "+String(iErrCode));
}

void WINAPI CDemoBot::OnUserMsg(LPCSTR lpUserAccount, LPCSTR lpMsg, LPCSTR lpFontName, DWORD dwFontColor, DWORD dwFontStyle)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+": "+String(lpMsg));
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
        MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "message with emotion (xiaoi)", "(xiaoi)=xiaoi.png");
     }
     else if(str == "sig")
     {
        MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, (String("RE: ")+lpMsg).c_str(), "", "老姜机器人");
     }
     else
     {
        AnsiString answer = MainForm->queryhanzi(lpMsg);
        MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, answer.c_str(), "", "老姜机器人", lpFontName, dwFontColor, dwFontStyle);
     }
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnUserNudge(LPCSTR lpUserAccount)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+": <nudge>");
     //MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "a nudge received", "", "Bot Demo");
     AnsiString answer = "输入一个汉字，查询汉字详细信息"+AnsiString('\n')+"输入<teach:问题 答案>就可以教机器人说话"+AnsiString('\n')
     +"比如输入 teach:老储 老储法号觉远 可以教会机器人回答“老储”"+AnsiString('\n')+
     "比如输入 hex:123 就可以把123转成16进制"+AnsiString('\n')+
     "比如输入 gbk:313233 就可以把313233转成gbk"+AnsiString('\n');
     MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, answer.c_str(), "", "老姜机器人");
}

//---------------------------------------------------------------------------
void WINAPI CDemoBot::OnActivityRespond(LPCSTR lpUserAccount, int iRespondCode)
{
    MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+ "..."+String(iRespondCode));
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
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+" add "+String(lpBotAccount));
     MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "hello, nice to meet you!");
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnUserRemove(LPCSTR lpBotAccount, LPCSTR lpUserAccount)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+" remove "+String(lpBotAccount));
     MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, "why delete me?");
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnUserStatusChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, DWORD dwUserStatus, LPCSTR lpUserName)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+" status="+String(dwUserStatus)+" name="+String(lpUserName));
}
//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnUserPersonalMessageChanged(LPCSTR lpBotAccount, LPCSTR lpUserAccount, LPCSTR lpPersonalMessage)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+" personalmessage="+String(lpPersonalMessage));
}
//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnSessionOpen(LPCSTR lpUserAccount, LPCSTR lpUserName, DWORD dwUserStatus, DWORD dwOpenType, DWORD dwClientID)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+" ("+String(lpUserName)+") in ...");
     switch(dwOpenType)
     {
        case 1:
            MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, (String(lpUserName)+", welcome!\r typing \"http://www.YEStudio.cn\" to start a web page").c_str());
            break;
        case 3:
            MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, (String(lpUserName)+", I call you!\r typing \"http://www.YEStudio.cn\" to start a web page").c_str());
            break;
     }
}
//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnSessionClose(LPCSTR lpUserAccount)
{
     MainForm->Memo1->Lines->Add(String(lpUserAccount)+" leaving ...");
}

void WINAPI CDemoBot::OnSendFileRespond(LPCSTR lpUserAccount, int iRespondCode)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+" sendfilecode="+String(iRespondCode));
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnSendBackgroundRespond(LPCSTR lpUserAccount, int iRespondCode)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+" sendbgcode="+String(iRespondCode));
}

//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnSendWebcamRespond(LPCSTR lpUserAccount, int iRespondCode)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]"+String(lpUserAccount)+" sendwebcamecode="+String(iRespondCode));
}
//---------------------------------------------------------------------------

void WINAPI CDemoBot::OnException(int iExceptionCode, LPCSTR lpExceptionReason, LPCSTR lpUserAccount, LPCSTR lpBotAccount)
{
     MainForm->Memo1->Lines->Add("["+Now().DateTimeString()+"]Exception - "+String(iExceptionCode)+": "+String(lpExceptionReason)+" (user="+String(lpUserAccount)+", bot="+String(lpBotAccount));
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
    if(Edit1->Text.IsEmpty() || Edit2->Text.IsEmpty())
    {
        MessageBox(Handle, "Please fill up the SPID & SPPWD before Login", "Information", MB_OK);
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
    TIniFile * file=new TIniFile(ExtractFilePath(Application->ExeName)+"DemoBot.ini");

    Edit1->Text=file->ReadString("bot", "1", "");
    Edit2->Text=file->ReadString("bot", "2", "");
    Edit3->Text=file->ReadString("bot", "3", "msnbot.incesoft.com");
    Edit4->Text=file->ReadString("bot", "4", "6602");
    delete file;
}

//---------------------------------------------------------------------------

void TMainForm::SaveIniFile(void)
{
    TIniFile * file=new TIniFile(ExtractFilePath(Application->ExeName)+"DemoBot.ini");

    file->WriteString("bot", "1", Edit1->Text);
    file->WriteString("bot", "2", Edit2->Text);
    file->WriteString("bot", "3", Edit3->Text);
    file->WriteString("bot", "4", Edit4->Text);

    delete file;
}

//---------------------------------------------------------------------------
bool TMainForm::guess(AnsiString GUESS1234,AnsiString BE1357,AnsiString Resule1A2B)
{
    //
    int countA=0,countB=0;
    AnsiString guess_1="",guess_2="",guess_3="",guess_4="";
    AnsiString BE_1="",BE_2="",BE_3="",BE_4="";
    guess_1 =  GUESS1234[1];
    guess_2 =  GUESS1234[2];
    guess_3 =  GUESS1234[3];
    guess_4 =  GUESS1234[4];

    BE_1 =  BE1357[1];
    BE_2 =  BE1357[2];
    BE_3 =  BE1357[3];
    BE_4 =  BE1357[4];

    if((BE_1==BE_2)||(BE_1==BE_3)||(BE_1==BE_4)||(BE_2==BE_3)||(BE_2==BE_4)||(BE_3==BE_4))
        {
        return false;
        }

    if((guess_1==BE_1))
        {
        countA++;
        }
    if((guess_2==BE_2))
        {
        countA++;
        }
    if((guess_3==BE_3))
        {
        countA++;
        }
    if((guess_4==BE_4))
        {
        countA++;
        }

    if((guess_1==BE_2)||(guess_1==BE_3)||(guess_1==BE_4))
        {
        countB++;
        }
    if((guess_2==BE_1)||(guess_2==BE_3)||(guess_2==BE_4))
        {
        countB++;
        }
    if((guess_3==BE_1)||(guess_3==BE_2)||(guess_3==BE_4))
        {
        countB++;
        }
    if((guess_4==BE_1)||(guess_4==BE_2)||(guess_4==BE_3))
        {
        countB++;
        }

    AnsiString REALRESULT = IntToStr(countA)+"A"+IntToStr(countB)+"B";
    if(REALRESULT==UpperCase(Resule1A2B))
        {
        return true;
        }
    else
        {
        return false;
        }
}



void __fastcall TMainForm::Button3Click(TObject *Sender)
{
    MainForm->DemoBot.BotCommand.SendMsg(Edit6->Text.c_str(), Edit5->Text.c_str(), "");
}
//---------------------------------------------------------------------------
AnsiString TMainForm::queryhanzi(AnsiString hanzi)
{
    AnsiString returnstring="";
    AnsiString sqlstring;
    if(UpperCase(hanzi).Pos("TEACH")==1)
        {
        AnsiString question,answer;
        hanzi = AnsiReplaceText(hanzi,"：",":");
        hanzi = AnsiReplaceText(hanzi,"　"," ");
        int pos1 = hanzi.Pos(":");
        int pos2 = hanzi.Pos(" ");
        question = hanzi.SubString(pos1+1,pos2-pos1-1);
        answer = hanzi.SubString(pos2+1,hanzi.Length());
        sqlstring="select * from exception_table where QUESTION=\'"+question+"\'";
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(sqlstring);
        ADOQuery1->Open();
        if(!ADOQuery1->Eof)
            {

            returnstring = "sorry,已经有人教过我了，你教我别的词吧";
            return returnstring;
            }

        sqlstring="INSERT INTO exception_table(QUESTION,ANSWER) VALUES(\'"+question+""+"\',\'"+answer+""+"\')";
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(sqlstring);
        try
            {
            ADOQuery1->ExecSQL();
            }
        catch(...)
            {
            returnstring = "sorry,哦，我好苯，没有学会，你再教我一次吧";
            return returnstring;
            }
        returnstring = "yeah，我学会了，我还要学";
        return returnstring;


        }
    if((UpperCase(hanzi).Pos("HEX")==1)||(UpperCase(hanzi).Pos("GBK")==1))
        {
        AnsiString question,answer;
        hanzi = Trim(hanzi);
        hanzi = AnsiReplaceText(hanzi,"：",":");
        int pos1 = hanzi.Pos(":");
        try
        {
        if(UpperCase(hanzi).Pos("HEX")==1)
            {
            hanzi = hanzi.SubString(pos1+1,hanzi.Length());
            returnstring = BCD_to_AnsiString(hanzi.c_str(),hanzi.Length());
            }
        if(UpperCase(hanzi).Pos("GBK")==1)
            {
            hanzi = hanzi.SubString(pos1+1,hanzi.Length());
            returnstring = AnsiString_to_BCD(hanzi);
            }
        if(returnstring.IsEmpty())
            {
            returnstring = "转换失败！";
            }
        }
        catch(...)
        {
        returnstring = "转换失败！";
        }


        return returnstring;



        }

    if((hanzi.Length()==2)&&(ByteType(hanzi,1 )!= mbSingleByte))
        {
        sqlstring="select * from allunicode where cc=\'"+hanzi+"\'";
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(sqlstring);
        ADOQuery1->Open();
        if(!ADOQuery1->Eof)
            {
            returnstring = hanzi+"："+AnsiString('\n')+
            "全拼："+ADOQuery1->FieldByName("quanpin")->AsString+AnsiString('\n')+
            "五笔："+ADOQuery1->FieldByName("wubi")->AsString+AnsiString('\n')+
            "郑码："+ADOQuery1->FieldByName("zhengma")->AsString+AnsiString('\n')+
            "UNICODE大字节序："+ADOQuery1->FieldByName("unicodeBe")->AsString+AnsiString('\n')+
            "UNICODE小字节序："+ADOQuery1->FieldByName("unicodeLe")->AsString+AnsiString('\n')+
            "utf8编码："+ADOQuery1->FieldByName("utf8")->AsString+AnsiString('\n')+
            "gbk编码："+ADOQuery1->FieldByName("gbk")->AsString+AnsiString('\n')+
            "笔画数："+ADOQuery1->FieldByName("bihuashu")->AsString+AnsiString('\n');
            }
        }
    else
        {
        sqlstring="select * from exception_table where question=\'"+hanzi+"\'";
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(sqlstring);
        ADOQuery1->Open();
        if(!ADOQuery1->Eof)
            {
            returnstring = ADOQuery1->FieldByName("answer")->AsString;
            }
        }
    if(returnstring.Length()==0)
        {
        returnstring = "不知道说些什么好，老姜没教我"+AnsiString('\n')+
        "输入<teach:问题 答案>就可以教我说话";
        }

    return  returnstring;

}
AnsiString TMainForm::BCD_to_AnsiString(char *P_BCD, int length)
{
    //TODO: Add your source code here
    AnsiString returnstring = "";
    char high_char,low_char,temp;
    for(int i=0;i<length;i++)
        {
        temp = *P_BCD++;
        high_char = (temp&0xf0)>>4;
        low_char = temp&0x0f;
        if ((high_char>=0x00)&&(high_char<=0x09))
            high_char+=0x30;
        if ((high_char>=0x0A)&&(high_char<=0x0F))
            high_char+=0x37;

        if ((low_char>=0x00)&&(low_char<=0x09))
            low_char+=0x30;
        if ((low_char>=0x0A)&&(low_char<=0x0F))
            low_char+=0x37;

        returnstring += AnsiString(high_char);
        returnstring += AnsiString(low_char);
        }
    return returnstring;
}
//---------------------------------------------------------------------------
AnsiString TMainForm::AnsiString_to_BCD(AnsiString wait_to_trans)
{
   AnsiString DecodeStr="";
   try
    {
       for(int i=1; i < wait_to_trans.Length()+1; i += 2)
       {
       AnsiString TempStr = "0x" + wait_to_trans.SubString(i,2);
       DecodeStr += AnsiString((char)(TempStr.ToInt()));
       }
    }
   catch(...)
    {
        return "";
    }
   return DecodeStr;
}
