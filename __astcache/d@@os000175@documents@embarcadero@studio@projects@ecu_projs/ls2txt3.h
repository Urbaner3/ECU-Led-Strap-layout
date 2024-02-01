//---------------------------------------------------------------------------

#ifndef Ls2txt3H
#define Ls2txt3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ComCtrls.hpp>

#include <vector> //   split

//---------------------------------------------------------------------------
//Trsfr.cpp = Transfer file
//Filename:Ls2txt : Excel to text
//Editor: Peter Chen
//Time: 010424 13:30

using namespace std;

class TForm1 : public TForm
{
  __published: // IDE-managed Components
    TLabel* Label1;
    TLabel* Label2;
    TButton* btnSrc;
    TButton* BtnSavTxt1;
    TButton* btnExit;
    TButton* BtnShow;
    TButton* BtnF2Show;
    TButton* BtnClear;
    TButton* Btnchg;
    TCheckBox* PortLockBox;
    TSpinEdit* SBUptNum;
    TSpinEdit* DDUptNum;
    TOpenDialog* srcOpDlg1;
    TSaveTextFileDialog* SavTxtDlg1;
    TPaintBox* PaintEq;
    TRichEdit* RichEdit;
    TLabel* SavFilLabl;
    TLabel* OpnFilLabl;
	TSpinEdit *WidthSet;
	TSpinEdit *HeightSet;
	TLabel *Label3;
	TLabel *Label4;

    //  make excel files

    void __fastcall BtnSavTxt1Click(TObject* Sender);
    void __fastcall btnExitClick(TObject* Sender);
    void __fastcall btnSrcClick(TObject* Sender);
    void __fastcall BtnClearClick(TObject* Sender);
    void __fastcall BtnShowClick(TObject* Sender);
    void __fastcall BtnF2ShowClick(TObject* Sender);
    void __fastcall BtnchgClick(TObject* Sender);
    void __fastcall PaintEqPaint(TObject* Sender);
    void __fastcall PortLockBoxClick(TObject* Sender);
	void __fastcall WidthSetChange(TObject *Sender);
	void __fastcall HeightSetChange(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
  private: // User declarations
  public: // User declarations
    __fastcall TForm1(TComponent* Owner);
    AnsiString OpenFileName, OpenFilePath, SaveFileName, SaveFilePath;
    int FileNumber;
    uint32_t GetEndPoint(
        int head_x, int head_y, int angle, int length, int* end_x, int* end_y);
    uint32_t GetEndPoint6(
        int head_x, int head_y, int angle, int length, int* end_x, int* end_y);

    void Read_File2(int sselect);
    int mystoi(const std::string &pat);
    const std::vector<std::string> split(
        const std::string &str, const std::string &pattern);
    void ChangePointToSave(AnsiString file_path);
    void Check80x80PointLocation(int ang, int &x1, int &y1, int &x2, int &y2);
    int Angle_45(int angle, int length, unsigned int x1, unsigned int y1,
        unsigned int x2, unsigned int y2, int point_buff[][100]);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1* Form1;
//---------------------------------------------------------------------------
#endif

