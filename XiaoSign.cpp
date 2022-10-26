//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("Sign.cpp", SignForm);
USEFORM("Process.cpp", ProgressForm);
//---------------------------------------------------------------------------
#include "Process.h"
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         ProgressForm  = new TProgressForm(NULL);
         Application->Initialize();
         Application->Title = "XiaoSign Bot of iBot Platform";
         Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TSignForm), &SignForm);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    delete ProgressForm;
    return 0;
}
//---------------------------------------------------------------------------
