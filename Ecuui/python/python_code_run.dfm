object Form6: TForm6
  Left = 0
  Top = 0
  Caption = 'Demo of python'
  ClientHeight = 442
  ClientWidth = 628
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 104
    Top = 280
    Width = 289
    Height = 33
    Caption = #35201#21360#31243#24335#30340#37679#35492#36664#20986#12290#29376#24907#12290#32380#32396#19979#19968#27493#31243#24335#12290
  end
  object Memo1: TMemo
    Left = -5
    Top = -6
    Width = 625
    Height = 185
    Lines.Strings = (
      'Memo1')
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Memo2: TMemo
    Left = 0
    Top = 185
    Width = 620
    Height = 64
    Lines.Strings = (
      'Memo2')
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object Panel1: TPanel
    Left = 0
    Top = 392
    Width = 625
    Height = 49
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
  object OpenDialog1: TOpenDialog
    Left = 512
    Top = 392
  end
  object SaveDialog1: TSaveDialog
    Left = 456
    Top = 392
  end
end