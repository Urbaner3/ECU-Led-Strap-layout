//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <clipbrd.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "J_src.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3* Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
void TForm3::split(
    wchar_t delimiter, UnicodeString str, TStringList* listofstrings)
{
    listofstrings->Clear();
    listofstrings->Delimiter = delimiter;
    listofstrings->StrictDelimiter = True; // Requires D2006 or newer.
    listofstrings->DelimitedText = str;
}

//---------------------------------------------------------------------------
void __fastcall TForm3::Load_CpbrdClick(TObject* Sender)
{
    UnicodeString us;
    TStringList* str_rows = new TStringList();
    TStringList* str_cols = new TStringList();

    split(
        L'\n', Clipboard()->AsText, str_rows); //Delimit lines with return char

    StringGrid1->RowCount = str_rows->Count;
    for (int j = 0; j < str_rows->Count; j++) {
        if (str_cols->Count > StringGrid1->ColCount)
            StringGrid1->ColCount = str_cols->Count;

        split(
            L'\t', str_rows->Strings[j], str_cols); //Delimit line with tab char
        for (int i = 0; i < str_cols->Count; i++) {
            Memo1->Lines->Add(
                IntToStr(i) + "," + IntToStr(j) + "=" + str_cols->Strings[i]);
            StringGrid1->Cells[i][j] = str_cols->Strings[i];
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Sav2csvClick(TObject* Sender)
{
    //data modifying

    //save to excel
    if (Form3->SaveDialog1->Execute()) {
        SavFileName = Form3->SaveDialog1->FileName;
        //check if extensoin is correct
        int ptplace;
        ptplace = LastDelimiter(".", Form3->SavFileName);
        if (ptplace == 0) {
            SavFileName = Form3->SavFileName + ".";
        } else if (SavFileName.SubString(
                       SavFileName.Length() - ptplace + 2, 4) == "xlsx")
        {
            ShowMessage("ª`·N°ÆÀÉ¦W");
        }

        else
        {
            ShowMessage("FileName Exception");
            SavFileName.Delete(SavFileName.Length() - ptplace + 2, 10);
            SavFileName = Form3->SavFileName + ".xlsx";
        }
        // SaveToFile failed
    }

    //------------- WRTING TO AN OUTPUT FILE STREAM -----------------------------------
    std::ofstream ofs;

    ofs.open(
        "D:\\OS000175\\Documents\\Embarcadero\\Studio\\Projects\\ECU_projs\\supply\\my_stream_test.txt",
        std::ios::out | // output file stream
            std::ios::app | // can append to a existing file
            std::ios::ate); // set file cursor at the end

    if (ofs) {
        Memo1->Lines->Add("my first");
        Memo1->Lines->Add("my second");
        Memo1->Lines->Add("my third");
        ofs << "This is my first record" << std::endl;
        ofs << "This is my second record" << std::endl;
        ofs << "This is my third record" << std::endl;

        ofs.close();
    } else
        std::cout << "Unable to open file to write" << std::endl;

    //------------- READING FROM AN INPUT FILE STREAM -----------------------------------
    std::ifstream ifs;
    std::string str;
    ifs.open(
        "D:\\OS000175\\Documents\\Embarcadero\\Studio\\Projects\\ECU_projs\\supply\\my_stream_out.txt",
        std::ios::in); // input file stream

    if (ifs) {
        while (!ifs.eof()) {
            std::getline(ifs, str);
//            std::cout << str << std::endl;
            Memo1->Lines->Add((UnicodeString)str.c_str());
        }
        ifs.close();
    } else
        std::cout << "Unable to open file to read" << std::endl;

    getchar();
}
//---------------------------------------------------------------------------

