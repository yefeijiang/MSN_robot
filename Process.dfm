object ProgressForm: TProgressForm
  Left = 295
  Top = 395
  BorderStyle = bsNone
  Caption = #31243#24207#21021#22987#21270'...'
  ClientHeight = 32
  ClientWidth = 427
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 0
    Width = 427
    Height = 13
    Align = alTop
    AutoSize = False
    Caption = #31243#24207#21152#36733#20013#35831#31245#20505
  end
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 13
    Width = 427
    Height = 17
    Align = alTop
    Min = 0
    Max = 100
    TabOrder = 0
  end
end
