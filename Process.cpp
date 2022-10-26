//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Process.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProgressForm *ProgressForm;
//---------------------------------------------------------------------------
__fastcall TProgressForm::TProgressForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TProgressForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Action = caNone;
}
//---------------------------------------------------------------------------
