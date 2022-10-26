//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AdminMain.h"
#include "Sign.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAdmin *Admin;
//---------------------------------------------------------------------------
__fastcall TAdmin::TAdmin(TComponent* Owner)
    : TForm(Owner)
{
    LoadMsnUser();
}
//---------------------------------------------------------------------------
void TAdmin::LoadMsnUser()
{
    UserListBox->Clear();
    AnsiString sqlstring = "select distinct msn from signtable";
    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
      ADOQuery1->Open();
    }
    catch(...)
    {
    }
    while(!ADOQuery1->Eof)
        {
        UserListBox->Items->Add(ADOQuery1->FieldByName("msn")->AsString);
        ADOQuery1->Next();
        }
    Label2->Caption = UserListBox->Count;
}

void TAdmin::LoadUserList(AnsiString msn)
{
    ListBox2->Clear();
    AnsiString sqlstring = "select sign from signtable where msn=\'"+msn+"\' order by inserttime";
    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
      ADOQuery1->Open();
    }
    catch(...)
    {
    }
    while(!ADOQuery1->Eof)
        {
        ListBox2->Items->Add(ADOQuery1->FieldByName("sign")->AsString);
        ADOQuery1->Next();
        }

}
void __fastcall TAdmin::UserListBoxClick(TObject *Sender)
{
    LoadUserList(UserListBox->Items->operator [](UserListBox->ItemIndex));
}
//---------------------------------------------------------------------------

void __fastcall TAdmin::Button1Click(TObject *Sender)
{
    if(Memo1->Text.IsEmpty()) return;
    InsertUserSign("fjye525@hotmail.com",Memo1->Text);
}
//---------------------------------------------------------------------------
int TAdmin::InsertUserSign(AnsiString msn,AnsiString sign)
{
    int returnint=1;
    AnsiString sqlstring="";
    //查询是否和
    AnsiString timestring = Now().FormatString("YYYY-MM-DD HH:MM:SS");
    sqlstring = "insert into signtable(msn,sign,inserttime) values(\'"+msn+"\',\'"+sign+"\',\'"+timestring+"\')";
    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
        ADOQuery1->ExecSQL();
    }
    catch(...)
    {
        return 1;
    }
    return 0;
}
int TAdmin::deleteUserSign(AnsiString msn,AnsiString sign)
{
    int returnint=1;
    AnsiString sqlstring="";
    //查询是否和

    sqlstring = "delete from signtable where msn=\'"+msn+"\' and sign=\'"+sign+"\'";
    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
        ADOQuery1->ExecSQL();
    }
    catch(...)
    {
        return 1;
    }
    return 0;
}
void __fastcall TAdmin::ListBox2DblClick(TObject *Sender)
{
    deleteUserSign(UserListBox->Items->operator [](UserListBox->ItemIndex),
                   ListBox2->Items->operator [](ListBox2->ItemIndex));
    ListBox2->DeleteSelected();
}
//---------------------------------------------------------------------------

