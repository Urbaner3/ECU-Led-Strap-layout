object Form2: TForm2
  Left = 0
  Top = 0
  Width = 1073
  Height = 970
  AutoScroll = True
  Caption = 'Form2'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 15
  object TxtLoadLbl: TLabel
    Left = 32
    Top = 867
    Width = 41
    Height = 15
    Caption = 'Txt load'
    Visible = False
  end
  object Work: TImage
    Left = 8
    Top = 8
    Width = 761
    Height = 833
    Proportional = True
    Stretch = True
  end
  object SavPicBtn: TSpeedButton
    Left = 672
    Top = 876
    Width = 57
    Height = 36
    Caption = 'Save To pic'
    OnClick = SavPicBtnClick
  end
  object PdfGenBtn: TSpeedButton
    Left = 664
    Top = 848
    Width = 55
    Height = 22
    Caption = 'Go Pdf'
  end
  object SavPicLabl: TLabel
    Left = 791
    Top = 891
    Width = 43
    Height = 15
    Caption = 'Pic Save'
    Visible = False
  end
  object bk_labl: TLabel
    Left = 800
    Top = 651
    Width = 42
    Height = 15
    Caption = 'break at'
  end
  object pt_break: TLabel
    Left = 797
    Top = 688
    Width = 45
    Height = 15
    Caption = 'at LED N'
  end
  object BtnOpnSrc: TButton
    Left = 16
    Top = 895
    Width = 75
    Height = 25
    Caption = 'Open File'
    TabOrder = 1
    OnClick = BtnOpnSrcClick
  end
  object Btn_Clear: TButton
    Left = 112
    Top = 895
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 2
    OnClick = Btn_ClearClick
  end
  object Btn_Show: TButton
    Left = 270
    Top = 887
    Width = 75
    Height = 25
    Caption = 'Show'
    TabOrder = 3
    OnClick = Btn_ShowClick
  end
  object Btn_Exit: TButton
    Left = 430
    Top = 887
    Width = 75
    Height = 25
    Caption = 'EXIT'
    TabOrder = 0
    OnClick = Btn_ExitClick
  end
  object RichEdit: TRichEdit
    Left = 791
    Top = 128
    Width = 256
    Height = 425
    Font.Charset = CHINESEBIG5_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Lines.Strings = (
      'RichEdit1')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 4
  end
  object br_line: TSpinEdit
    Left = 848
    Top = 648
    Width = 121
    Height = 24
    MaxValue = 0
    MinValue = 0
    TabOrder = 5
    Value = 1
  end
  object br_led: TSpinEdit
    Left = 848
    Top = 685
    Width = 121
    Height = 24
    MaxValue = 78
    MinValue = 0
    TabOrder = 6
    Value = 1
  end
  object OpnTxtFlDiag: TOpenTextFileDialog
    Filter = 'txt files | *.txt'
    Left = 904
    Top = 752
  end
  object SavePicDialog1: TSaveDialog
    Filter = 'bmp|*.bmp|jpeg|*.jpg|PNG|*.png'
    Left = 800
    Top = 824
  end
end
