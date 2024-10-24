//---------------------------------------------------------------------------

#ifndef typeFormH
#define typeFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ComboEdit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.NumberBox.hpp>
#include <Data.Bind.Controls.hpp>
#include <Fmx.Bind.Navigator.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.TabControl.hpp>
#include <System.Rtti.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Objects.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <FMX.ImgList.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>

#include <System.ImageList.hpp>

//---------------------------------------------------------------------------
class TDataFrm : public TForm
{
  __published: // IDE-managed Components
	TExpander* Expander1;
	TExpander *Blockhead;
    TLabel* Label1;
	TLabel* Label2;
    TLabel* Label3;
    TLabel* Label4;
	TExpander *portN;
    TLabel* Label5;
	TExpander *Strip_length;
    TLabel* Label6;
    TButton* BtnReadFromSheet;
	TNumberBox *col_count1;
    TPanel* Panel1;
    TTabControl* TabControl1;
	TTabItem *TabLength;
	TTabItem *TabMeta;
	TTabItem *SqlFunc;
    TGrid* Grid2;
    TBindNavigator* BindNavigator1;
    TImage* Image1;
    TCornerButton* HintCorButton1;
	TButton *ButtonSave;
    TLabel* Label9;
    TLabel* Label10;
    TLabel* Label11;
	TComboEdit *col_diff1;
	TComboEdit *strap_amount1;
    TText* Text1;
    TLabel* Label8;
    TLabel* Label7;
	TComboEdit *end_diff1;
    TLabel* Label12;
    TLabel* Label13;
	TComboBox *dir_strap1;
	TListBoxItem* Leftup;
    TListBoxItem* Rightdown;
    TStringGrid* LedlengthGrid;
    TIntegerColumn* port_start;
    TIntegerColumn* port_end;
	TIntegerColumn *col_count;
	TIntegerColumn *int_col;
	TButton *ButtonLoad;
	TEdit *block_start_x;
	TEdit *block_start_y;
	TEdit *port_start1;
	TEdit *port_end1;
	TButton *ButtonLoadXls;
	TStringGrid *StrapInColStringGrid;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn6;
	TStringColumn *StringColumn7;
	TStringColumn *StringColumn8;
	TStringColumn *StringColumn9;
	TStringColumn *StringColumn10;
	TStringColumn *StringColumn11;
	TStringColumn *StringColumn12;
	TStringColumn *StringColumn13;
	TStringColumn *StringColumn14;
	TTabItem *VisualCheckTab;
	TStringColumn *strap_amount;
	TStringColumn *block_start;
	TPopupColumn *PopupColumn1;
	TStringColumn *dir_strap;
	TButton *ButtonExtProg;
	TImageList *ImageList1;
	TStringColumn *col_diff;
	TPaintBox *PaintBox1;
	TMemo *OutMemo;
	TComboBox *SheetComboBox;
	TButton *BtnWriteLen;
	TStringColumn *StringColumn15;
	TStringColumn *StringColumn16;
	TStringColumn *StringColumn17;
	TStringColumn *StringColumn18;
	TStringColumn *StringColumn19;
	TStringColumn *StringColumn20;
	TStringColumn *StringColumn21;
	TStringColumn *StringColumn22;
	TStringColumn *StringColumn23;
	TStringColumn *StringColumn24;
	TStringColumn *StringColumn25;
	TStringColumn *StringColumn26;
	TButton *ButGenLed;
	TButton *ButShowmap;
	TLabel *Label14;
	TLabel *Label15;
	TButton *ButPdfRead;
	TStringColumn *end_diff;
    void __fastcall HintCorButton1Click(TObject* Sender);
    void __fastcall BtnReadFromSheetClick(TObject* Sender);
    void __fastcall FormCreate(TObject* Sender);
	void __fastcall ButtonLoadClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonExtProgClick(TObject *Sender);
	void __fastcall col_diff1Change(TObject *Sender);
	void __fastcall strap_amount1Change(TObject *Sender);
	void __fastcall end_diff1Change(TObject *Sender);

	void __fastcall BtnWriteLenClick(TObject *Sender);

	void __fastcall ButGenLedClick(TObject *Sender);
	void __fastcall ButShowmapClick(TObject *Sender);
	void __fastcall ButtonLoadXlsClick(TObject *Sender);
	void __fastcall ButPdfReadClick(TObject *Sender);

  private: // User declarations
	void split(
		wchar_t delimiter, UnicodeString str, TStringList* listofstrings);
	void WriteToRows(int columnIndex);
	int datacount;
	void LoadCSV(const String &FileName);
	void SaveLenGridToCSV(const String &FileName);
	void SaveGridToCSV(const String& fileName);
	void LoadGridToCSV(void);
    String EscapeCSV(const String& str);
  public: // User declarations
    __fastcall TDataFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDataFrm* DataFrm;
//---------------------------------------------------------------------------
#endif

