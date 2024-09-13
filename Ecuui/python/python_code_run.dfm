object Form6: TForm6
  Left = 0
  Top = 0
  Caption = 'Demo of python'
  ClientHeight = 458
  ClientWidth = 518
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 8
    Top = 304
    Width = 273
    Height = 15
    Caption = #35201#21360#31243#24335#30340#37679#35492#36664#20986#12290#29376#24907#12290#32380#32396#19979#19968#27493#31243#24335#12290
  end
  object Memo1: TMemo
    Left = -5
    Top = -6
    Width = 86
    Height = 175
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Memo2: TMemo
    Left = 0
    Top = 185
    Width = 81
    Height = 80
    Lines.Strings = (
      'Memo2')
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object Panel1: TPanel
    Left = 0
    Top = 360
    Width = 449
    Height = 81
    Caption = 'Panel1'
    TabOrder = 2
    object Button1: TButton
      Left = 8
      Top = 7
      Width = 115
      Height = 25
      Caption = 'Evaluate script'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 215
      Top = 7
      Width = 106
      Height = 26
      Caption = 'Load script..'
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 336
      Top = 7
      Width = 105
      Height = 25
      Caption = 'Save script..'
      TabOrder = 2
      OnClick = Button3Click
    end
  end
  object Panel2: TPanel
    Left = 112
    Top = 8
    Width = 289
    Height = 273
    Caption = 'Panel2'
    TabOrder = 3
    object Label2: TLabel
      Left = 128
      Top = 36
      Width = 50
      Height = 21
      Caption = 'Label2'
    end
    object Label3: TLabel
      Left = 184
      Top = 36
      Width = 34
      Height = 15
      Caption = 'Label3'
    end
    object ButGenLed: TButton
      Left = 16
      Top = 32
      Width = 75
      Height = 25
      Caption = #29986#29983#29128#40670
      TabOrder = 0
    end
    object ButShowmap: TButton
      Left = 16
      Top = 81
      Width = 75
      Height = 25
      Caption = #22294#24418#39023#31034
      TabOrder = 1
    end
    object Button6: TButton
      Left = 16
      Top = 133
      Width = 75
      Height = 25
      Caption = 'Button6'
      TabOrder = 2
    end
  end
  object OpenDialog1: TOpenDialog
    Left = 368
    Top = 416
  end
  object SaveDialog1: TSaveDialog
    Left = 456
    Top = 392
  end
end
