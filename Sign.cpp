//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Sign.h"
#include "Main.h"
#include "Process.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSignForm *SignForm;
//---------------------------------------------------------------------------
__fastcall TSignForm::TSignForm(TComponent* Owner)
    : TForm(Owner)
{
    ADOConnection1->Connected = true;
    BotName = "MSN签名管家";
    pMSN = new TStringList;
    pAllMSg = new TStringList;
    pMSN->Delimiter  = ';';
    ProgressForm->Visible = true;
    LoadNewestSign();
    LoadAllSign();
    ProgressForm->Visible = false;
    helpString = new TStringList;
    helpString->LoadFromFile(ExtractFilePath(Application->ExeName)+"help.txt");
}
bool TSignForm::VoteSign(string msn,int signID)
{
    int votenum=0;
    if((votelimit.find(msn))!= votelimit.end())
        {
        votenum = votelimit[msn];
        }

    if(votenum>=10)
        {
        return false;
        }

    AnsiString sqlstring;
    sqlstring = "update signtable set votecount=votecount+1 where id="+IntToStr(signID);
    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
        ADOQuery1->ExecSQL();
    }
    catch(...)
    {
        return false;
    }
    votenum++;
    votelimit[msn] = votenum;
    return true;
}
//---------------------------------------------------------------------------
AnsiString TSignForm::HotTopn(int page,int pagecount)
{
    AnsiString sqlstring="",returnstring="";
    //查询是否和
    if(page==1)
        {
        sqlstring = "Select top "+IntToStr(pagecount)+" id,sign,msn,votecount from signtable order by votecount desc";
        }
    else
        {
        sqlstring = "Select top "+IntToStr(pagecount)+" id,sign,msn,votecount from signtable"+
        " where id not in (select top "+IntToStr((page-1)*pagecount)+" id from signtable order by votecount desc) "+
        " order by votecount desc";
        }

    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
        ADOQuery1->Open();
    }
    catch(...)
    {
        return 1;
    }
    returnstring = "id      票数    msn签名"+AnsiString('\r')+AnsiString('\n');
    while(!ADOQuery1->Eof)
        {
        returnstring+= fillString(ADOQuery1->FieldByName("id")->AsString,8);
        returnstring+= fillString(ADOQuery1->FieldByName("votecount")->AsString,8);

        returnstring+= Trim(ADOQuery1->FieldByName("sign")->AsString);
        returnstring+= AnsiString('\r')+AnsiString('\n');;
        ADOQuery1->Next();
        }
    return returnstring;
}
AnsiString TSignForm::fillString(AnsiString fill,int maxlength)
{
    int len = fill.Length();
    for(int i=0;i<maxlength-len;i++)
        {
        fill += " ";
        }
    return fill;
}
AnsiString TSignForm::GetHistorySign(AnsiString msn,int page,int pagecount)
{
    AnsiString sqlstring="",returnstring="";
    //查询是否和
    if(page<=0)
    	{
        return "非法页面";
        }
    if(page==1)
        {
        sqlstring = "Select top "+IntToStr(pagecount)+" id,sign,msn,votecount,inserttime from signtable where msn=\'"+msn+"\' order by inserttime desc";
        }
    else
        {
        sqlstring = "Select top "+IntToStr(pagecount)+" id,sign,msn,votecount,inserttime from signtable"+
        " where msn=\'"+msn+"\' and id not in (select top "+IntToStr((page-1)*pagecount)+" id from signtable where msn=\'"+msn+"\' order by inserttime desc) "+
        " order by inserttime desc";
        }

    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
        ADOQuery1->Open();
    }
    catch(...)
    {
        return 1;
    }

    returnstring = "id      时间                 msn签名"+AnsiString('\r')+AnsiString('\n');
    while(!ADOQuery1->Eof)
        {
        returnstring+= fillString(ADOQuery1->FieldByName("id")->AsString,8);
        returnstring+= fillString(ADOQuery1->FieldByName("inserttime")->AsString,21);
        returnstring+= ADOQuery1->FieldByName("sign")->AsString;
        returnstring+= AnsiString('\r')+AnsiString('\n');;
        ADOQuery1->Next();
        }
    return returnstring;
}
AnsiString TSignForm::QuerySameSign(AnsiString msn,AnsiString sign)
{
    int samecount=0;
    AnsiString returnstring="";

    if((sign_map.find(msn.c_str()))!= sign_map.end())
        {
        sign = sign_map[msn.c_str()].begin();
        }

    if((sign_msn_map.find(sign.c_str()))!= sign_msn_map.end())
        {
        AnsiString allmsn = sign_msn_map[sign.c_str()].begin();

        pMSN->DelimitedText = allmsn;
        samecount = pMSN->Count;
        }
    else
        {
        samecount=0;
        }
    if(samecount==1)
        {
        returnstring = "现在用这个签名只有你，有个性，我喜欢";
        }
    else if(samecount!=0)
        {
        returnstring = "现在一共有"+IntToStr(samecount)+"个msn用户和你相同的签名！缘分阿！"+
        AnsiString('\r')+AnsiString('\n')+"想更多了解具体是那些用户和你设的相同签名吗?"+
        AnsiString('\r')+AnsiString('\n')+"发送yuanfen查询有缘之人";
        }

    return returnstring;
}
AnsiString TSignForm::QuerySameSignUser(AnsiString msn,AnsiString sign)
{
    int samecount=0;
    AnsiString returnstring="";

    if((sign_map.find(msn.c_str()))!= sign_map.end())
        {
        sign = sign_map[msn.c_str()].begin();
        }

    if((sign_msn_map.find(sign.c_str()))!= sign_msn_map.end())
        {
        AnsiString allmsn = sign_msn_map[sign.c_str()].begin();
        pMSN->DelimitedText = allmsn;
        pMSN->Delimiter  = ';';
        samecount = pMSN->Count;
        }
    else
        {
        samecount=0;
        }
    if(samecount==1)
        {
        returnstring = "现在用这个签名只有你，有个性，我喜欢";
        }
    else if(samecount!=0)
        {
        returnstring = "现在一共有"+IntToStr(samecount)+"个msn用户和你相同的签名！缘分阿！";
        for(int i=0;i<pMSN->Count;i++)
            {
            returnstring +=  AnsiString('\r')+AnsiString('\n')+pMSN->Strings[i];
            }
        }

    return returnstring;
}
bool TSignForm::UserSignUpdate(string msn,string sign)
{
    if(Trim(AnsiString(sign.begin())).IsEmpty())
        {
        return  false;
        }
    AnsiString allmsn;
    AnsiString currmsn;
    sign = kickspaceial(AnsiString(sign.begin())).c_str();
    //--更新sign
    int index=-1;
    pAllMSg->Find(sign.begin(),index);
    if(index==-1)
        {
        pAllMSg->Add(sign.begin());
        }
    //--存储map  签名，msn集合，分号隔开
    if((sign_msn_map.find(sign))!= sign_msn_map.end())
        {
        allmsn = sign_msn_map[sign].begin();
        currmsn = AnsiString(msn.begin());
        if(allmsn.Pos(currmsn)==0)
            {
            allmsn = allmsn+";"+currmsn;
            }
        sign_msn_map[sign] = allmsn.c_str();
        }
    else
        {
        sign_msn_map[sign] = msn;
        }

    //存储mao  msn，签名
    bool isupdate=false;
    if((sign_map.find(msn))!= sign_map.end())
        {
        if(sign_map[msn]==sign)
            {
            isupdate=false;
            }
        else
            {
            //签名改变
            if((sign_msn_map.find(sign_map[msn]))!= sign_msn_map.end())
                {
                allmsn = sign_msn_map[sign_map[msn]].begin();
                currmsn = AnsiString(msn.begin());
                int pos = allmsn.Pos(currmsn);
                if(pos==1)
                    {
                    allmsn = allmsn.Delete(1,currmsn.Length()+1);
                    }
                else if(pos!=0)
                    {
                    allmsn = allmsn.Delete(pos-1,currmsn.Length()+1);
                    }
                sign_msn_map[sign_map[msn]] = allmsn.c_str();
                }
            else
                {
                //sign_msn_map[sign] = msn;
                }
            isupdate=true;
            }
        }
    else
        {
        isupdate=true;
        }
    sign_map[msn] = sign;
    return isupdate;
}
//---------------------------------------------------------------------------
AnsiString TSignForm::GetRandomSign()
{
    return  pAllMSg->Strings[random(pAllMSg->Count)];
}
//---------------------------------------------------------------------------
int TSignForm::InsertUserSign(AnsiString msn,AnsiString sign)
{
    int returnint=1;
    AnsiString sqlstring="";
    //反注入
    sign = kickspaceial(sign);
    if(sign.IsEmpty())
        {
        return 1;
        }
    if(Trim(msn).IsEmpty())
        {
        return 1;
        }
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
bool TSignForm::DeleteUserSign(AnsiString msn,int id)
{
    int returnint=1;
    AnsiString sqlstring="";
    //查询是否和

    sqlstring = "delete from signtable where msn=\'"+msn+"\' and id="+IntToStr(id);
    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
        ADOQuery1->ExecSQL();
    }
    catch(...)
    {
        return false;
    }
    return true;
}
void TSignForm::LoadNewestSign()
{
    AnsiString sqlstring="",returnstring="";
    string msn,sign;
    AnsiString allmsn;
    AnsiString currmsn;
    sqlstring = " select * from signtable where inserttime in (select a from (Select msn,max(inserttime) as a from signtable  group by msn))";//,sign order by inserttime desc";

    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
        ADOQuery1->Open();
    }
    catch(...)
    {
        return;
    }
    while(!ADOQuery1->Eof)
        {

        if(ProgressForm->ProgressBar1->Position==100)
            {
            ProgressForm->ProgressBar1->Position = 0;
            }
        ProgressForm->ProgressBar1->Position++;
        msn = ADOQuery1->FieldByName("msn")->AsString.c_str();
        sign = ADOQuery1->FieldByName("sign")->AsString.c_str();
        sign_map[msn] = sign;
        Application->ProcessMessages();
        if((sign_msn_map.find(sign))!= sign_msn_map.end())
            {
            allmsn = sign_msn_map[sign].begin();
            currmsn = AnsiString(msn.begin());
            if(allmsn.Pos(currmsn)==0)
                {
                allmsn = allmsn+";"+currmsn;
                }
            sign_msn_map[sign] = allmsn.c_str();
            }
        else
            {
            sign_msn_map[sign] = msn;
            }

        ADOQuery1->Next();
        }


}
void TSignForm::LoadAllSign()
{
    AnsiString sqlstring="",returnstring="";
    pAllMSg->Clear();
    sqlstring = "select distinct sign from signtable";

    ADOQuery1->Close();
    ADOQuery1->SQL->Clear();
    ADOQuery1->SQL->Add(sqlstring);
    try
    {
        ADOQuery1->Open();
    }
    catch(...)
    {
        return;
    }
    while(!ADOQuery1->Eof)
        {
        if(ProgressForm->ProgressBar1->Position==100)
            {
            ProgressForm->ProgressBar1->Position = 0;
            }
        ProgressForm->ProgressBar1->Position++;
        Application->ProcessMessages();
        pAllMSg->Add(ADOQuery1->FieldByName("sign")->AsString);
        ADOQuery1->Next();
        }
}

//---------------------------------------------------------------------------
AnsiString TSignForm::helpinfo()
{
    /*AnsiString returnstring;
    returnstring =
    "每个签名都是一段心情，每个签名也许都会有一个小故事"+AnsiString('\r')+AnsiString('\n')+
    "可以输入top查询最受欢迎的签名还可输入top1、top2..."+AnsiString('\r')+AnsiString('\n')+
    "可以输入same或者yuanfen查询系统内和自己当前签名相同的个数"+AnsiString('\r')+AnsiString('\n')+
    "可以输入history查询自己的历史签名,还可输入history1、history2..."+AnsiString('\r')+AnsiString('\n')+
    "可以输入vote[id]给自己喜欢的签名投票,比如输入vote88，就是给id为88的签名投票，每天可投10票"+AnsiString('\r')+AnsiString('\n')+
    "可以输入random获取系统随机签名"+AnsiString('\r')+AnsiString('\n')+
    "http://www.YEStudio.cn";     */

    return  helpString->Text;
}
//---------------------------------------------------------------------------
void TSignForm::answerMSG(LPCSTR lpUserAccount, LPCSTR lpMsg)
{
    AnsiString msnaccount =  AnsiString(lpUserAccount);
    AnsiString question = UpperCase(AnsiString(lpMsg));
    AnsiString answer="";

    if((question=="HELP")||(question=="?"))
        {
        answer = helpinfo();
        }
    if(question.Pos("HISTORY")==1)
        {
        answer = GetHistorySign(msnaccount,getint(question.SubString(8,question.Length())));
        }
    if(question.Pos("TOP")==1)
        {
        answer = HotTopn(getint(question.SubString(4,question.Length())));
        }
    if(question.Pos("SAME")==1)
        {
        answer = QuerySameSign(msnaccount,question);
        }
    if(question.Pos("YUANFEN")==1)
        {
        answer = QuerySameSignUser(msnaccount,question);
        }
    if(question.Pos("VOTE")==1)
        {
        if(VoteSign(lpUserAccount,getint(question.SubString(5,question.Length()))))
            {
            answer = "投票成功";
            }
        else
            {
            answer = "对不起，您今天的投票次数已经到10次，请明天再投";
            }
        }
    if(question.Pos("RANDOM")==1)
        {
        answer = GetRandomSign();
        }
    if(question.Pos("DELETE")==1)
        {
        int id= getint(question.SubString(7,question.Length()));
        if(DeleteUserSign(msnaccount,id))
            {
            answer = "你已成功删除id号为"+IntToStr(id)+"的历史签名";
            }
        else
            {
            answer = "删除历史签名失败！";
            }
        }
    //MainForm->Memo1->Lines->Add(answer);
    if(answer.IsEmpty())
        {
        answer = GetRandomSign();
        answer += AnsiString('\r')+AnsiString('\n')+"请输入help或者?查询帮助";
        }
    MainForm->DemoBot.BotCommand.SendMsg(lpUserAccount, answer.c_str(), "", SignForm->BotName.c_str());

}

int TSignForm::getint(AnsiString str)
{
    try
    {
    str = kickspaceial(str);
      if(str.Length()==0)
        {
        return 1;
        }
      return StrToInt(str);

    }
    catch(...)
    {
        return 1;
    }

}
AnsiString TSignForm::kickspaceial(AnsiString str)
{
    str = Trim(str);
    str = AnsiReplaceText(str,"'","''");
    str = AnsiReplaceText(str," ","");
    str = AnsiReplaceText(str,"　","");
    str = AnsiReplaceText(str,AnsiString('\r'),"");
    str = AnsiReplaceText(str,AnsiString('\n'),"");
    return str;
}
void __fastcall TSignForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    delete pMSN;
    delete pAllMSg;
    delete helpString;
}
//---------------------------------------------------------------------------

void __fastcall TSignForm::Timer1Timer(TObject *Sender)
{
   //
    static day=0;
    if(day!=Now().DayOfWeek())
    {
    votelimit.clear();
    }
    day = Now().DayOfWeek();

}
//---------------------------------------------------------------------------

