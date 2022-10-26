object MainForm: TMainForm
  Left = 268
  Top = 185
  Width = 671
  Height = 437
  BorderWidth = 2
  Caption = 'iBot Platform '#21453#29468#25968#23383' BY YEStudio.cn'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 177
    Top = 0
    Width = 482
    Height = 399
    Align = alClient
    ImeName = #32043#20809#21326#23431#25340#38899'V5'
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 177
    Height = 399
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 1
    object Label1: TLabel
      Left = 7
      Top = 12
      Width = 25
      Height = 13
      Caption = 'SPID'
    end
    object Label2: TLabel
      Left = 7
      Top = 44
      Width = 40
      Height = 13
      Caption = 'SPPWD'
    end
    object Label3: TLabel
      Left = 7
      Top = 76
      Width = 31
      Height = 13
      Caption = 'Server'
    end
    object Label4: TLabel
      Left = 7
      Top = 108
      Width = 19
      Height = 13
      Caption = 'Port'
    end
    object Button1: TButton
      Left = 8
      Top = 136
      Width = 161
      Height = 25
      Caption = 'Login'
      TabOrder = 4
      OnClick = Button1Click
    end
    object Edit1: TEdit
      Left = 48
      Top = 8
      Width = 121
      Height = 21
      ImeName = #32043#20809#21326#23431#25340#38899'V5'
      TabOrder = 0
    end
    object Edit2: TEdit
      Left = 48
      Top = 39
      Width = 121
      Height = 21
      ImeName = #32043#20809#21326#23431#25340#38899'V5'
      TabOrder = 1
    end
    object Edit3: TEdit
      Left = 48
      Top = 72
      Width = 121
      Height = 21
      ImeName = #32043#20809#21326#23431#25340#38899'V5'
      TabOrder = 2
      Text = 'msnbot.incesoft.com'
    end
    object Button2: TButton
      Left = 8
      Top = 169
      Width = 161
      Height = 25
      Caption = 'Logout'
      TabOrder = 5
      OnClick = Button2Click
    end
    object Edit4: TEdit
      Left = 48
      Top = 104
      Width = 121
      Height = 21
      ImeName = #32043#20809#21326#23431#25340#38899'V5'
      TabOrder = 3
      Text = '6602'
    end
    object Button3: TButton
      Left = 32
      Top = 280
      Width = 75
      Height = 25
      Caption = #24320#22987#29468
      TabOrder = 6
      OnClick = Button3Click
    end
    object Edit5: TEdit
      Left = 32
      Top = 216
      Width = 121
      Height = 21
      TabOrder = 7
      Text = '1234'
    end
    object Edit6: TEdit
      Left = 32
      Top = 248
      Width = 121
      Height = 21
      TabOrder = 8
      Text = 'i@xiaoi.com'
    end
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=allUnicode.mdb;Pers' +
      'ist Security Info=False'
    LoginPrompt = False
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 48
    Top = 328
  end
  object ADOQuery1: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 112
    Top = 328
  end
end
