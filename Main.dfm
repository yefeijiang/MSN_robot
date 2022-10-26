object MainForm: TMainForm
  Left = 268
  Top = 185
  Width = 671
  Height = 469
  BorderWidth = 2
  Caption = 'iBot Platform YEStudioBot   http://www.YEStudio.cn  MSN'#31614#21517#31649#23478
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 177
    Top = 0
    Width = 482
    Height = 438
    Align = alClient
    ImeName = #32043#20809#21326#23431#25340#38899'V5'
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 177
    Height = 438
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
    object Label5: TLabel
      Left = 8
      Top = 208
      Width = 24
      Height = 13
      Caption = 'MSN'
    end
    object Label6: TLabel
      Left = 8
      Top = 256
      Width = 24
      Height = 13
      Caption = #20869#23481
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
    object Edit5: TEdit
      Left = 8
      Top = 224
      Width = 161
      Height = 21
      ImeName = #20013#25991' ('#31616#20307') - '#35895#27468#25340#38899#36755#20837#27861
      TabOrder = 6
      Text = 'fjye525@hotmail.com'
    end
    object Button3: TButton
      Left = 8
      Top = 376
      Width = 161
      Height = 25
      Caption = #21457#28040#24687
      TabOrder = 7
      OnClick = Button3Click
    end
    object Memo2: TMemo
      Left = 8
      Top = 272
      Width = 161
      Height = 89
      ImeName = #20013#25991' ('#31616#20307') - '#35895#27468#25340#38899#36755#20837#27861
      Lines.Strings = (
        #26412#28040#24687#26469#33258#20110#32769#23004#26426#22120#20154
        'xiaosign@hotmail.com')
      TabOrder = 8
    end
    object Button4: TButton
      Left = 64
      Top = 200
      Width = 91
      Height = 25
      Caption = #20449#24687#25509#25910#27979#35797
      TabOrder = 9
      Visible = False
      OnClick = Button4Click
    end
    object CheckBox1: TCheckBox
      Left = 8
      Top = 408
      Width = 97
      Height = 17
      Caption = #25171#21360#26085#24535
      Checked = True
      State = cbChecked
      TabOrder = 10
    end
  end
end
