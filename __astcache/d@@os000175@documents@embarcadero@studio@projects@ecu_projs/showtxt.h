//---------------------------------------------------------------------------

#ifndef ShowTxtH
#define ShowTxtH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TButton *BtnOpnSrc;
	TButton *Btn_Clear;
	TButton *Btn_Show;
	TButton *Btn_Exit;
	TRichEdit *RichEdit1;
	TOpenTextFileDialog *OpnTxtFlDiag;
	TLabel *TxtLoadLbl;
	TImage *Work;
	TSpeedButton *SavPicBtn;
	TSpeedButton *PdfGenBtn;
	TSaveDialog *SavePicDialog1;
	void __fastcall BtnOpnSrcClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Btn_ShowClick(TObject *Sender);
	void __fastcall Btn_ExitClick(TObject *Sender);
	void __fastcall Btn_ClearClick(TObject *Sender);
	void __fastcall SavPicBtnClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
    const int show_time = 10;
	__fastcall TForm2(TComponent* Owner);
    AnsiString OpenFileName, OpenFilePath, SavPicName;
    //frame image bitmap : picture_show
    Graphics::TBitmap *bitmap;
    void Show_picture(void);


};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
