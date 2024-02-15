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
	void __fastcall Load_CpbrdClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
