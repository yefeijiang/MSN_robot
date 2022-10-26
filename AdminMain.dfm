object Admin: TAdmin
  Left = 231
  Top = 190
  Width = 870
  Height = 640
  Caption = 'Admin'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 584
    Width = 65
    Height = 13
    AutoSize = False
    Caption = #20849#26377#29992#25143#65306
  end
  object Label2: TLabel
    Left = 88
    Top = 584
    Width = 6
    Height = 13
    Caption = '0'
  end
  object UserListBox: TListBox
    Left = 8
    Top = 8
    Width = 193
    Height = 569
    ImeName = #20013#25991' ('#31616#20307') - '#35895#27468#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
    OnClick = UserListBoxClick
  end
  object ListBox2: TListBox
    Left = 208
    Top = 8
    Width = 641
    Height = 473
    ImeName = #20013#25991' ('#31616#20307') - '#35895#27468#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 1
    OnDblClick = ListBox2DblClick
  end
  object Memo1: TMemo
    Left = 208
    Top = 488
    Width = 641
    Height = 81
    ImeName = #20013#25991' ('#31616#20307') - '#35895#27468#25340#38899#36755#20837#27861
    TabOrder = 2
  end
  object Button1: TButton
    Left = 208
    Top = 576
    Width = 641
    Height = 25
    Caption = #28155#21152
    TabOrder = 3
    OnClick = Button1Click
  end
  object ADOQuery1: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 160
    Top = 56
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=YEStudioBot.mdb;Per' +
      'sist Security Info=False'
    LoginPrompt = False
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 128
    Top = 40
  end
end
