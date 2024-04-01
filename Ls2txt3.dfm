object Form1: TForm1
  Left = 1083
  Top = 104
  Width = 959
  Height = 982
  AutoScroll = True
  Caption = 'Mapping Tool'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poDesigned
  OnCreate = FormCreate
  TextHeight = 15
  object Label1: TLabel
    Left = 258
    Top = 858
    Width = 84
    Height = 15
    Caption = 'Scan Board port'
  end
  object Label2: TLabel
    Left = 356
    Top = 858
    Width = 83
    Height = 15
    Caption = 'DDU Board port'
  end
  object PaintEq: TPaintBox
    Left = 210
    Top = 8
    Width = 716
    Height = 833
    OnPaint = PaintEqPaint
  end
  object SavFilLabl: TLabel
    Left = 37
    Top = 876
    Width = 44
    Height = 15
    Caption = 'SavLoad'
    FocusControl = BtnSavTxt1
    Visible = False
  end
  object OpnFilLabl: TLabel
    Left = 104
    Top = 876
    Width = 55
    Height = 15
    Caption = 'OpenLoad'
    FocusControl = btnSrc
    Visible = False
  end
  object Label3: TLabel
    Left = 104
    Top = 392
    Width = 32
    Height = 15
    Caption = 'Width'
  end
  object Label4: TLabel
    Left = 118
    Top = 454
    Width = 36
    Height = 15
    Caption = 'Height'
  end
  object CsvSavLabl: TLabel
    Left = 115
    Top = 612
    Width = 44
    Height = 15
    Caption = 'SavLoad'
    FocusControl = BtnSavTxt1
    Visible = False
  end
  object BtnSavTxt1: TButton
    Left = 16
    Top = 904
    Width = 65
    Height = 25
    Caption = 'Save File'
    DisabledImageName = 'BtnSavTxt1'
    TabOrder = 0
    OnClick = BtnSavTxt1Click
  end
  object btnSrc: TButton
    Left = 87
    Top = 904
    Width = 83
    Height = 25
    Caption = 'Open(Source)'
    TabOrder = 1
    OnClick = btnSrcClick
  end
  object btnExit: TButton
    Left = 176
    Top = 904
    Width = 75
    Height = 25
    Caption = 'EXIT'
    TabOrder = 2
    OnClick = btnExitClick
  end
  object BtnShow: TButton
    Left = 272
    Top = 903
    Width = 75
    Height = 25
    Caption = 'Show'
    TabOrder = 3
    OnClick = BtnShowClick
  end
  object BtnF2Show: TButton
    Left = 387
    Top = 903
    Width = 75
    Height = 25
    Caption = 'form2'
    DisabledImageName = 'Button7'
    TabOrder = 4
    OnClick = BtnF2ShowClick
  end
  object BtnClear: TButton
    Left = 507
    Top = 873
    Width = 75
    Height = 25
    Caption = 'clear'
    DisabledImageName = 'BtnClear'
    TabOrder = 5
    OnClick = BtnClearClick
  end
  object Btnchg: TButton
    Left = 507
    Top = 904
    Width = 75
    Height = 25
    Caption = 'changeButton'
    DisabledImageName = 'Button9'
    TabOrder = 6
    OnClick = BtnchgClick
  end
  object PortLockBox: TCheckBox
    Left = 194
    Top = 876
    Width = 58
    Height = 17
    Caption = 'Lock'
    Checked = True
    State = cbChecked
    TabOrder = 7
    OnClick = PortLockBoxClick
  end
  object SBUptNum: TSpinEdit
    Left = 258
    Top = 873
    Width = 57
    Height = 24
    Enabled = False
    MaxValue = 16
    MinValue = 0
    TabOrder = 8
    Value = 8
  end
  object DDUptNum: TSpinEdit
    Left = 348
    Top = 873
    Width = 59
    Height = 24
    Enabled = False
    MaxValue = 10
    MinValue = 0
    TabOrder = 9
    Value = 6
  end
  object RichEdit: TRichEdit
    Left = 8
    Top = 8
    Width = 196
    Height = 364
    Font.Charset = CHINESEBIG5_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    ImeName = 'Chinese (Traditional) - US Keyboard'
    Lines.Strings = (
      'Result~')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 10
  end
  object WidthSet: TSpinEdit
    Left = 47
    Top = 424
    Width = 121
    Height = 24
    MaxValue = 0
    MinValue = 0
    TabOrder = 11
    Value = 720
  end
  object HeightSet: TSpinEdit
    Left = 74
    Top = 483
    Width = 121
    Height = 24
    MaxValue = 1000
    MinValue = 0
    TabOrder = 12
    Value = 831
  end
  object BtmF3show: TButton
    Left = 16
    Top = 542
    Width = 75
    Height = 25
    Caption = 'form3'
    TabOrder = 13
    OnClick = BtmF3showClick
  end
  object TestJSrc: TButton
    Left = 12
    Top = 589
    Width = 75
    Height = 25
    Caption = 'J_Src'
    TabOrder = 14
    OnClick = TestJSrcClick
  end
  object JSavToCsv: TButton
    Left = 104
    Top = 568
    Width = 75
    Height = 25
    Caption = 'J_save'
    TabOrder = 15
    OnClick = JSavToCsvClick
  end
  object srcOpDlg1: TOpenDialog
    Filter = '*.csv|*.csv|*.xlsx|*.xlsx'
    Left = 24
    Top = 784
  end
  object SavTxtDlg1: TSaveDialog
    DefaultExt = 'txt'
    Filter = 'Txt file |*.txt'
    Left = 40
    Top = 720
  end
  object JSavCsvDlg: TSaveDialog
    DefaultExt = 'csv'
    Filter = 'csv file |*.csv'
    Left = 104
    Top = 768
  end
end
