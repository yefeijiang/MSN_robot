//---------------------------------------------------------------------------

#ifndef AdminMainH
#define AdminMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TAdmin : public TForm
{
__published:	// IDE-managed Components
    TListBox *UserListBox;
    TListBox *ListBox2;
    TADOQuery *ADOQuery1;
    TMemo *Memo1;
    TButton *Button1;
    TADOConnection *ADOConnection1;
    TLabel *Label1;
    TLabel *Label2;
    void __fastcall UserListBoxClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall ListBox2DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TAdmin(TComponent* Owner);
    void LoadMsnUser();
    void LoadUserList(AnsiString msn);
    int InsertUserSign(AnsiString msn,AnsiString sign);
    int deleteUserSign(AnsiString msn,AnsiString sign);
};
//---------------------------------------------------------------------------
extern PACKAGE TAdmin *Admin;
//---------------------------------------------------------------------------
#endif
