//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <clipbrd.hpp>

#include "J_src.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void split(wchar_t delimiter, UnicodeString str, TStringList *listofstrings)
{
   listofstrings->Clear();
   listofstrings->Delimiter = delimiter;
   listofstrings->StrictDelimiter = True; // Requires D2006 or newer.
   listofstrings->DelimitedText = str;
}

//---------------------------------------------------------------------------
void __fastcall TForm3::Button1Click(TObject *Sender)
{
        UnicodeString us;
   TStringList *str_rows= new TStringList();
   TStringList *str_cols= new TStringList();

   split( L'\n', Clipboard()->AsText, str_rows); //Delimit lines with return char

   StringGrid1->RowCount=str_rows->Count;
   for(int j=0; j<str_rows->Count; j++)
   {
    if( str_cols->Count > StringGrid1->ColCount ) StringGrid1->ColCount=str_cols->Count;

    split( L'\t', str_rows->Strings[j], str_cols); //Delimit line with tab char
    for(int i=0; i<str_cols->Count; i++)
    {
    Memo1->Lines->Add(IntToStr(i)+","+IntToStr(j)+"="+str_cols->Strings[i]);
    StringGrid1->Cells[i][j]=str_cols->Strings[i];
    }
   }
}
//---------------------------------------------------------------------------

