object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'Form3'
  ClientHeight = 592
  ClientWidth = 859
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Panel1: TPanel
    Left = 8
    Top = 16
    Width = 745
    Height = 569
    Caption = 'Panel1'
    TabOrder = 0
    object Read_place: TLabel
      Left = 536
      Top = 436
      Width = 39
      Height = 15
      Caption = 'Read at'
    end
    object LblPortA: TLabel
      Left = 524
      Top = 476
      Width = 51
      Height = 15
      Caption = 'Port from'
    end
    object LblPortB: TLabel
      Left = 631
      Top = 476
      Width = 11
      Height = 15
      Caption = 'to'
    end
    object StringGrid1: TStringGrid
      Left = 32
      Top = 24
      Width = 369
      Height = 473
      TabOrder = 0
    end
    object Memo1: TMemo
      Left = 432
      Top = 24
      Width = 225
      Height = 385
      Lines.Strings = (
        'Memo1')
      ScrollBars = ssVertical
      TabOrder = 1
    end
    object Load_Cpbrd: TButton
      Left = 432
      Top = 432
      Width = 75
      Height = 25
      Caption = 'Load'
      TabOrder = 2
      OnClick = Load_CpbrdClick
    end
    object Sav2csv: TButton
      Left = 432
      Top = 472
      Width = 75
      Height = 25
      Caption = 'Export'
      TabOrder = 3
      OnClick = Sav2csvClick
    end
    object Rd_bk: TEdit
      Left = 592
      Top = 433
      Width = 65
      Height = 23
      TabOrder = 4
      Text = 'N5'
    end
    object PortA: TEdit
      Left = 581
      Top = 473
      Width = 44
      Height = 23
      TabOrder = 5
      Text = '1'
    end
    object PortB: TEdit
      Left = 648
      Top = 473
      Width = 41
      Height = 23
      TabOrder = 6
      Text = '8'
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 384
    Top = 528
  end
end
