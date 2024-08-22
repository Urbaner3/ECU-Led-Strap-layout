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

}
//---------------------------------------------------------------------------
void TDataFrm::WriteToRows(int rowIndex)
{
    if (rowIndex < 0 || rowIndex >=  LedlengthGrid->RowCount) {
        // Column index out of range
        return;
	}
	//else
    int dataRowCount = 7;
	LedlengthGrid->Cells[0][rowIndex] = port_start1->Text;
	port_end1->Text = IntToStr(port_start1->Text.ToInt() + col_count1->Text.ToInt()) -1;
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


//	//Read one line in strget function
//	Strap xx;
//	std::ofstream wd("east_led.txt");
//	std::ifstream rd("east_port.txt");
//	std::ofstream myout("myout.txt");
//	// Redirect stdout to myout.txt
//	std::streambuf* coutbuf = std::cout.rdbuf();
//	std::cout.rdbuf(myout.rdbuf());
//	AnsiString temp;
//	temp = col_count1->Text;
//	xx.colnum_read((String)temp);
//	temp = dir_strap1->ItemIndex < 1 ? "-1, 1" : "1, -1";
//	xx.vec_read((String)temp.c_str());
//	temp = col_diff1->Text;
//	xx.dir_read((String)temp.c_str());
//	temp =strap_amount1->Text;
//	xx.str_proc((String)temp.c_str());
//	//bfs_on_port
//	std::vector<int> buff = {block_start_x->Text.ToInt(), block_start_y->Text.ToInt()};
//	xx.PLlist.clear();
//	for (int ii = 0; ii < col_count1->Text.ToIntDef(-1); ++ii) {
//		xx.PLlist.push_back(buff);
//		buff = { buff[0] + xx.now_dir[0], buff[1] + xx.now_dir[1] };
//	}
//	//strap_dfs(wt_file, 80, 1);
//	int block_size = 80;
//    for (int jj = 0; jj < xx.port_num; ++jj) {
//		std::vector<int> startup = xx.PLlist[jj];
//		int port_n = xx.Flr_list[jj];
//		int Nled = 76;
//		OutMemo->Lines->Add("----------------");
//		std::vector<int> scl_buff;
//		String linetext = IntToStr(jj) + ",";
//		std::vector<int> buff = startup;
//		std::vector<std::vector<int> > scl_list;
//
//		for (int ii = 0; ii < port_n; ++ii) {
//			scl_buff = { buff[0] * block_size, buff[1] * block_size };
//			OutMemo->Lines->Add(scl_buff[0] + " " + scl_buff[1]);
//			scl_list.push_back(scl_buff);
//			buff = { buff[0] + xx.v_ang[0], buff[1] + xx.v_ang[1] };
//			linetext += IntToStr(Nled);
//			linetext += ",";
//		}
//
//		xx.block_merge(linetext, scl_list, block_size);
//		linetext += "\n";
//		OutMemo->Lines->Add(linetext);
//		wd << linetext;
//	}
	//print the text to string grid
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
	Fmx::Dialogs::TSaveDialog *SaveDialog = new Fmx::Dialogs::TSaveDialog(this);
	SaveDialog->DefaultExt = "xls";
	SaveDialog->Filter = "Excel files (*.xls)|*.xlsx|All files (*.*)|*.*";
    SaveDialog->Title = "Save Excel File As";
	SaveDialog->FileName = fileName;
    if (SaveDialog->Execute())
	{
		wchar_t *cont;
		Book* book = xlCreateBook(); // xlCreateXMLBook() for xlsx
		if(book)
		{
			Sheet* sheet = book->addSheet(L"meta_data");
			if(sheet)
			{
				String data[8] = { "行數範圍起始", "行數結束", "燈管行位移量",
				"燈管行數量", "燈管管數", "燈管區起始座標", "燈管區資料方向",
				"燈管尾位移量" };
				wchar_t *spc;
				//fill in the first row
				for (int col = 0; col < LedlengthGrid->ColumnCount; col++) {
                    spc = data[col].c_str();
					sheet->writeStr(1, col+1, spc);
                    LedlengthGrid->Cells[col][0] = spc;
				}
//                LedlengthGrid->RowCount
				for (int row = 0; row <  10 ; ++row) {

					try {
						for (int col = 0; col < LedlengthGrid->ColumnCount; ++col) {
							cont = String(LedlengthGrid->Cells[col][row+1]).c_str();
							if(!sheet->writeStr(row+2, col+1, cont)){
								sheet->writeNum(row+2, col+1, (double)(col+row));
                            }
						}
					}
					catch (Exception &e)
					{
						Fmx::Dialogs::ShowMessage("Error read file: " + e.Message);
					}
				}

				// Check if the file exists
				if (TFile::Exists(System::Ioutils::TPath::GetDirectoryName(ParamStr(0))))
				{
					// Prompt the user for confirmation to replace the existing file
					if (Vcl::Dialogs::MessageDlg("The file already exists. Do you want to replace it?", TMsgDlgType::mtInformation, mbYesNo, 0) != 0)
					{
						return; // Exit if the user does not want to replace
					}
				}
				//else
				saved = book->save((fileName + String(".xls")).c_str());
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
		"C:\\Users\\Peter\\miniconda3\\envs\\winprog\\python.exe", "C:\\Users\\Peter\\Documents\\Embarcadero\\Studio\\Projects\\python\\hello.py",
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



