//---------------------------------------------------------------------------

#ifndef J_srcH
#define J_srcH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TStringGrid *StringGrid1;
	TMemo *Memo1;
	TButton *Load_Cpbrd;
	TButton *Sav2csv;
	TLabel *Read_place;
	TEdit *Rd_bk;
	TSaveDialog *SaveDialog1;
	TLabel *LblPortA;
	TEdit *PortA;
	TLabel *LblPortB;
	TEdit *PortB;
	void __fastcall Load_CpbrdClick(TObject *Sender);
	void __fastcall Sav2csvClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
    AnsiString SavFileName;
       TStringList *str_rows;
   TStringList *str_cols;
   void split(wchar_t delimiter, UnicodeString str, TStringList *listofstrings);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
