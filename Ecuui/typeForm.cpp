//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "typeForm.h"
#include "Hintfix.h"
//#include "Strap.h"
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include "libxl.h"
#include <Vcl.Dialogs.hpp> //use vcl instead
#include <string.h>
#include <wchar.h>
#include <wstring.h>
#include <string>

#include <FMX.Clipboard.hpp>

//---------------------------------------------------------------------------
#pragma execution_character_set("utf-8")
#pragma package(smart_init)
#pragma resource "*.fmx"
TDataFrm* DataFrm;

#include <System.IOUtils.hpp> //string writer
using namespace std;
using namespace libxl;
//---------------------------------------------------------------------------
__fastcall TDataFrm::TDataFrm(TComponent* Owner) : TForm(Owner)
{
    this->Image1->Bitmap->LoadFromFile("eqblock.png");
    this->Text1->Text =
        L"區頭座標·行位移量·行頭座標·燈管行數量 \
		燈管行之燈管管數·燈管行之燈管頭座標·燈管                \
		行之燈管位移量·燈管行之燈管之燈點數量·燈                 \
		管行之燈管之燈點座標";
    LedlengthGrid->RowCount = 35;
}
//---------------------------------------------------------------------------
void __fastcall TDataFrm::FormCreate(TObject* Sender)
{
    this->datacount = 1; //leave the first line blank
    port_start1->ImeMode = Fmx::Types::TImeMode::imOnHalf;
    port_end1->ImeMode = Fmx::Types::TImeMode::imOnHalf;
    col_diff1->ImeMode = Fmx::Types::TImeMode::imOnHalf;
    strap_amount1->ImeMode = Fmx::Types::TImeMode::imOnHalf;
    block_start_x->ImeMode = Fmx::Types::TImeMode::imOnHalf;
    block_start_y->ImeMode = Fmx::Types::TImeMode::imOnHalf;
    // dir_strap1->ImeMode = TImeMode::imOnHalf;
    strap_amount1->Items->Clear();
    col_diff1->Items->Clear();
    end_diff1->Items->Clear();

    StrapInColStringGrid->Canvas->Font->Size = 20;
    LedlengthGrid->Canvas->Font->Size = 20;

    // Set up the ADO connection

    //		UnicodeString Connection = String("Provider=MSDAOSP;Data Source=")
    //		+ System::Ioutils::TPath::GetDirectoryName(ParamStr(0))
    //		+ String("portfolio.xml;");
    //
    //		ADOConnection1->ConnectionString = Connection;
    //
    //		ADOConnection1->LoginPrompt = false; // Disable login prompt
    //		ADOConnection1->Connected = true; // Connect to the Excel file
    //
    //		// Set the query to select data from your Excel sheet
    //		ADOQuery1->SQL->Clear();
    //		ADOQuery1->SQL->Add("SELECT * FROM ["+ SheetComboBox->Items->Strings[
    //		SheetComboBox->ItemIndex ] +"]");// Adjust the sheet name as necessary
    //		ADOQuery1->Open(); // Execute the query

    OutMemo->Lines->Add("cd ../../python");
	OutMemo->Lines->Add("python showmap.py");

    //    for (int col = 0; col < 26; col++) {
    //		((TStringColumn*)FindComponent("StringColumn" + String(col)))
	//			->SetHeader = IntToStr(col + 1);
    //    }
}
//---------------------------------------------------------------------------
void TDataFrm::WriteToRows(int rowIndex)
{
    if (rowIndex < 0 || rowIndex >= LedlengthGrid->RowCount) {
        // Column index out of range
		return;
    }
    //else
    int dataRowCount = 7;
    LedlengthGrid->Cells[0][rowIndex] = port_start1->Text;
    port_end1->Text =
        IntToStr(port_start1->Text.ToInt() + col_count1->Text.ToInt()) - 1;
	LedlengthGrid->Cells[1][rowIndex] = port_end1->Text;
	LedlengthGrid->Cells[2][rowIndex] = col_diff1->Text;
    LedlengthGrid->Cells[3][rowIndex] = col_count1->Text;
    LedlengthGrid->Cells[4][rowIndex] = strap_amount1->Text;
    String cord;
    cord = block_start_x->Text + ", " + block_start_y->Text;
    LedlengthGrid->Cells[5][rowIndex] = cord;
    LedlengthGrid->Cells[6][rowIndex] =
        dir_strap1->ItemIndex < 1 ? "-1, 1" : "1, -1";
}

void __fastcall TDataFrm::HintCorButton1Click(TObject* Sender)
{
    HintFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TDataFrm::BtnReadFromSheetClick(TObject* Sender)
{
    UnicodeString us;
    TStringList* str_rows = new TStringList();
    TStringList* str_cols = new TStringList();

    // Assuming you have a TStringGrid named StrapInColStringGrid and a Button named LoadButton on your form
    Fmx::Dialogs::TOpenDialog* OpenDialog = new Fmx::Dialogs::TOpenDialog(this);
    OpenDialog->Filter = "CSV files (*.csv)|*.csv|All files (*.*)|*.*";
	OpenDialog->DefaultExt = "csv";

    if (OpenDialog->Execute()) {
        LoadCSV(OpenDialog->FileName);
    }

    delete OpenDialog;
}

//---------------------------------------------------------------------------

void TDataFrm::LoadCSV(const String &FileName)
{
    TStringList* CSVContent = new TStringList();

    try {
        CSVContent->LoadFromFile(FileName);

        // Clear previous data
        StrapInColStringGrid->RowCount = 215; // Keep header row
        //		StrapInColStringGrid->ColumnCount = 0;  // Clear existing columns
        //		StrapInColStringGrid->ClearColumns();

        if (CSVContent->Count > 0) {
            // Process header row
            TStringList* Headers = new TStringList();
            Headers->CommaText =
                CSVContent->Strings[0]; // Assuming first line is header
            //			StrapInColStringGrid->ColumnCount = Headers->Count;

            //			for (int col = 0; col < Headers->Count; col++)
            //			{
            //				StrapInColStringGrid->Cells[col][0] = Headers->Strings[col];
            //            }

            // Process data rows
            for (int row = 0; row < CSVContent->Count; row++) {
                TStringList* RowValues = new TStringList();
                RowValues->CommaText = CSVContent->Strings[row];

                StrapInColStringGrid->RowCount++;

                for (int col = 0; col < RowValues->Count; col++) {
                    StrapInColStringGrid->Cells[col][row] =
                        RowValues->Strings[col];
                }

                delete RowValues;
            }

            delete Headers;
        }
    } __finally
    {
        delete CSVContent;
    }
}
//---------------------------------------------------------------------------

void TDataFrm::split(
	wchar_t delimiter, UnicodeString str, TStringList* listofstrings)
{
    listofstrings->Clear();
    listofstrings->Delimiter = delimiter;
    listofstrings->StrictDelimiter = True; // Requires D2006 or newer.
    listofstrings->DelimitedText = str;
}
//---------------------------------------------------------------------------

void __fastcall TDataFrm::ButtonLoadClick(TObject* Sender)
{
    WriteToRows(this->datacount);
    datacount++;
}
//---------------------------------------------------------------------------

void __fastcall TDataFrm::ButtonSaveClick(TObject* Sender)
{
    SaveGridToCSV("output");
}
//---------------------------------------------------------------------------

void TDataFrm::SaveGridToCSV(const String &fileName)
{
    int BufferSize = 7;
    bool saved = false;
    Fmx::Dialogs::TSaveDialog* SaveDialog = new Fmx::Dialogs::TSaveDialog(this);
    SaveDialog->DefaultExt = "xls";
    SaveDialog->Filter = "Excel files (*.xls)|*.xls|All files (*.*)|*.*";
    SaveDialog->Title = "Save Excel File As";
    SaveDialog->FileName = fileName;
    if (SaveDialog->Execute()) {
        wchar_t* cont;
        Book* book = xlCreateBook(); // xlCreateXMLBook() for xlsx
        if (book) {
            Sheet* sheet = book->addSheet(L"meta_data");
            if (sheet) {
                String data[8] = { "行數範圍起始", "行數結束", "燈管行位移量",
                    "燈管行數量", "燈管管數", "燈管區起始座標",
                    "燈管區資料方向", "燈管尾位移量" };
                wchar_t* spc;
                //fill in the first row
                for (int col = 0; col < LedlengthGrid->ColumnCount; col++) {
                    spc = data[col].c_str();
                    sheet->writeStr(1, col + 1, spc);
                    LedlengthGrid->Cells[col][0] = spc;
                }
                //                LedlengthGrid->RowCount
                for (int row = 0; row < 10; ++row) {
                    try {
                        for (int col = 0; col < LedlengthGrid->ColumnCount;
                             ++col) {
							cont = String(LedlengthGrid->Cells[col][row + 1])
									   .c_str();
                            if (!sheet->writeStr(row + 2, col + 1, cont)) {
                                sheet->writeNum(
                                    row + 2, col + 1, (double)(col + row));
                            }
                        }
                    } catch (Exception &e) {
                        Fmx::Dialogs::ShowMessage(
                            "Error read file: " + e.Message);
                    }
                }

                // Check if the file exists
                if (TFile::Exists(
                        System::Ioutils::TPath::GetDirectoryName(ParamStr(0))))
                {
                    // Prompt the user for confirmation to replace the existing file
                    if (Vcl::Dialogs::MessageDlg(
                            "The file already exists. Do you want to replace it?",
                            TMsgDlgType::mtInformation, mbYesNo, 0) != 0)
                    {
                        return; // Exit if the user does not want to replace
                    }
                }
                //else
                saved = book->save((SaveDialog->FileName).c_str(), 0);
                if (!saved)
                    Fmx::Dialogs::ShowMessage("XLS file saved failed!");
                //else
            }
            //else sheet
        }
        //else book

        book->release();
    }
    //else
    //	delete SaveDialog;
}

//---------------------------------------------------------------------------

String TDataFrm::EscapeCSV(const String &str)
{
    String result = str;
    if (result.Pos(",") > 0 || result.Pos("\"") > 0 || result.Pos("\n") > 0) {
        result = "\"" +
                 StringReplace(
                     result, "\"", "\"\"", TReplaceFlags() << rfReplaceAll) +
                 "\"";
    }
    return result;
}

//---------------------------------------------------------------------------

void __fastcall TDataFrm::ButtonExtProgClick(TObject* Sender)
{
    ShellExecuteA(NULL, "open",
        "C:\\Users\\Peter\\miniconda3\\envs\\winprog\\python.exe",
        "C:\\Users\\Peter\\Documents\\Embarcadero\\Studio\\Projects\\python\\hello.py",
        NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TDataFrm::col_diff1Change(TObject* Sender)
{
    col_diff1->Items->Add(col_diff1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TDataFrm::strap_amount1Change(TObject* Sender)
{
    strap_amount1->Items->Add(strap_amount1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TDataFrm::end_diff1Change(TObject* Sender)
{
    end_diff1->Items->Add(end_diff1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TDataFrm::BtnWriteLenClick(TObject* Sender)
{
    Fmx::Dialogs::TSaveDialog* SaveDialog = new Fmx::Dialogs::TSaveDialog(this);
    SaveDialog->Filter = "CSV files (*.csv)|*.csv|All files (*.*)|*.*";
    SaveDialog->DefaultExt = "csv";

    if (SaveDialog->Execute()) {
        SaveLenGridToCSV(SaveDialog->FileName);
    }

    delete SaveDialog;
}
//---------------------------------------------------------------------------

void TDataFrm::SaveLenGridToCSV(const String &FileName)
{
    TStringList* CSVContent = new TStringList();

    try {
        // Loop through the grid to create CSV lines
        String line;
        // First, get the headers
        for (int col = 0; col < StrapInColStringGrid->ColumnCount; col++) {
            if (col > 0)
                line += ","; // Add a comma before next column
            line += StrapInColStringGrid->Cells[col][0]; // Get header
        }
        CSVContent->Add(line); // Add header row to CSV

        // Now process data rows
        for (int row = 1; row < StrapInColStringGrid->RowCount;
             row++) // Start from 1 to skip header
        {
            line = "";
            for (int col = 0; col < StrapInColStringGrid->ColumnCount; col++) {
                if (col > 0)
                    line += ","; // Add a comma before next column
                line += StrapInColStringGrid->Cells[col][row]; // Get cell data
            }
            CSVContent->Add(line); // Add data row to CSV
        }

        // Save to the specified file
        CSVContent->SaveToFile(FileName);
    } __finally
    {
        delete CSVContent; // Clean up
    }
}

void __fastcall TDataFrm::ButGenLedClick(TObject* Sender)
{
    ShellExecuteA(NULL, "open",
        "C:\\Users\\Peter\\miniconda3\\envs\\winprog\\python.exe",
        "C:\\Users\\Peter\\Documents\\ECU_projs\\Ecuui\\python\\gen_led.py",
        NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TDataFrm::ButShowmapClick(TObject* Sender)
{
    ShellExecuteA(NULL, "", "cmd",
        "cd C:\\Users\\Peter\\Documents\\ECU_projs\\Ecuui\\python", NULL,
        SW_SHOWDEFAULT);
    //		ShellExecuteA(NULL, "",
    //		"C:\\Users\\Peter\\miniconda3\\envs\\winprog\\python.exe", "C:\\Users\\Peter\\Documents\\ECU_projs\\Ecuui\\python\\showmap.py",
    //		NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

void __fastcall TDataFrm::ButtonLoadXlsClick(TObject* Sender)
{
    LoadGridToCSV("Output");
}
//---------------------------------------------------------------------------
void TDataFrm::LoadGridToCSV(const String &fileName)
{
    int BufferSize = 7;
    bool saved = false;
    Fmx::Dialogs::TOpenDialog* OpenDialog = new Fmx::Dialogs::TOpenDialog(this);
    OpenDialog->DefaultExt = "xls";
    OpenDialog->Filter = "Excel files (*.xls)|*.xls|All files (*.*)|*.*";
    OpenDialog->Title = "Save Excel File As";
    OpenDialog->FileName = fileName;
    String locname = fileName;
	if (OpenDialog->Execute()) {
		Book* book = xlCreateBook(); // xlCreateXMLBook() for xlsx
        if (book->load((fileName + String(".xls")).c_str(), 0)) {
            Sheet* sheet = book->getSheet(0);
            if (sheet) {
                //				String data[8] = { "行數範圍起始", "行數結束", "燈管行位移量",
                //					"燈管行數量", "燈管管數", "燈管區起始座標",
				//					"燈管區資料方向", "燈管尾位移量" };     wchar_t
				String spc;
                //                LedlengthGrid->RowCount
                int colint[4] = { 1, 2, 4, 8 }, colstr[4] = { 3, 5, 6, 7 }; //col 0 is empty
                int size_ci = sizeof(colint) / sizeof(colint[0]),
                    size_cs = sizeof(colstr) / sizeof(colstr[0]);
                for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
				{

						//integer columns
						for (int colind = 0; colind < size_ci; ++colind) {
							const wchar_t *s = sheet->readStr(row, colint[colind]);
							if (!s) {
								continue;
							}
							else {
								spc = spc + s;
								LedlengthGrid->Cells[colint[colind]-1][row-1] =
									StrToInt(spc);
								spc = "";
							}
						}

//						//string columns
						for (int colind = 0; colind < size_cs; ++colind) {
                            const wchar_t *s = sheet->readStr(row, colstr[colind]);
							if (!s) {
								continue;
							}
							else {
								spc = spc + s;
								LedlengthGrid->Cells[colstr[colind]-1][row-1] = spc;
                                spc = "";
							}
						}
//

				}

				//				saved = book->save((fileName + String(".xls")).c_str());
				//				if (!saved)
				//					Fmx::Dialogs::ShowMessage("XLS file saved failed!");
				//else
			}
            //else sheet
        }
        //else book


        book->release();
    }
    //else
    //	delete OpenDialog;
}

//---------------------------------------------------------------------------

void __fastcall TDataFrm::ButPdfReadClick(TObject *Sender)
{
	ShellExecuteA(NULL, "open",
		"..\\..\\viewpdf\\Win32\\Release\\PdfView.exe","",
		NULL, SW_SHOWDEFAULT);
}
//---------------------------------------------------------------------------

