//---------------------------------------------------------------------------

#ifndef ProcessH
#define ProcessH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TProgressForm : public TForm
{
__published:	// IDE-managed Components
    TProgressBar *ProgressBar1;
    TLabel *Label1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TProgressForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProgressForm *ProgressForm;
//---------------------------------------------------------------------------
#endif
