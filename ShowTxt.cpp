//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ShowTxt.h"
#include "Ls2txt3.h"
#include <string> // RightStr
#include <typeinfo> //typeid
#include <dir.h> // save function MAXFILE

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2* Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------
AnsiString OpenFileName, OpenFilePath;
void TForm2::Show_picture(void)
{
    unsigned int start_flag = 0, count = 0, err;
    int ii, jj;
    int point_buff[3];
    TStreamReader* read_file = new TStreamReader(OpenFilePath);
    AnsiString str, str1, str2;
    Graphics::TBitmap* bit;
    UnicodeString myword;
    std::string goodword;

    //    try {
    if (OpenFilePath == "") {
        ShowMessage("Please select 'Open' file.");
        return;
    }

    //clear code
    //        Work->Canvas->Brush->Color = clBlack;
    //        Work->Canvas->FillRect(Work->ClientRect);
    //¹Ï§Îªº®Ø¬[
    //horizon lines drawing
    std::auto_ptr<Graphics::TBitmap> Bitmap(new Graphics::TBitmap);
    TRGBTriple* ptr;
    TPixelFormat pixForm;
    Bitmap->LoadFromFile(
        ".\\black.bmp"); //. is set somme how in Ls2txt3.cpp, is it Path var
    pixForm = Bitmap->PixelFormat;
    Bitmap->PixelFormat = pf24bit;
    for (jj = 0; 99 + (80 * jj) < Work->Height; jj++) {
        for (ii = 99; ii < Bitmap->Width - 2; ii++) {
            //            set blue
            ptr = reinterpret_cast<TRGBTriple*>(
                Bitmap->ScanLine[99 + (80 * jj)]); // certain 4 rows
            ptr[ii].rgbtRed = 0;
            ptr[ii].rgbtGreen = 0;
            ptr[ii].rgbtBlue = 255;
        }
    }

    //veritical lines drawing
    for (ii = 99; ii < Bitmap->Height - 2; ii++) {
        for (jj = 0; 99 + (80 * jj) < Work->Width; jj++) {
            //set blue
            ptr = reinterpret_cast<TRGBTriple*>(
                Bitmap->ScanLine[ii]); // all rows makes vertical line.
            ptr[99 + (80 * jj)].rgbtRed = 0;
            ptr[99 + (80 * jj)].rgbtGreen = 0;
            ptr[99 + (80 * jj)].rgbtBlue = 255;
        }
    }
    //    jj -= 1;
    //    for (ii = 99; ii < Bitmap->Height - 2; ii++) {
    //        //set blue
    //        ptr = reinterpret_cast<TRGBTriple*>(
    //            Bitmap->ScanLine[ii]); // all rows makes vertical line.
    //        ptr[99 + (80 * jj) + 50].rgbtRed = 0;
    //        ptr[99 + (80 * jj) + 50].rgbtGreen = 0;
    //        ptr[99 + (80 * jj) + 50].rgbtBlue = 255;
    //    }
    //
    //    for (ii = 99; ii < Bitmap->Height - 2; ii++) {
    //        //set blue
    //        ptr = reinterpret_cast<TRGBTriple*>(
    //            Bitmap->ScanLine[ii]); // all rows makes vertical line.
    //        ptr[99 + (80 * jj) + 130].rgbtRed = 0;
    //        ptr[99 + (80 * jj) + 130].rgbtGreen = 0;
    //        ptr[99 + (80 * jj) + 130].rgbtBlue = 255;
    //    }

    struct Tmap
    {
        TColor col;
    };
    struct Tmap mmp[5]; // my color map

    enum clmp
    {
        red = 0,
        green,
        blue,
        cyan,
        yellow
    };
    int Size_clmp = 5;
    int mpen = red; //variable
    mmp[red].col = clRed, mmp[green].col = clLime, mmp[blue].col = clBlue;
    mmp[cyan].col = clFuchsia, mmp[yellow].col = clYellow;

    int ps_count = 0;
    //str: cut the strings
    while (!read_file->EndOfStream) {
        str = read_file->ReadLine();
        str = Trim(str);

        str2 = str;
        str1 = str.SetLength(str.Pos(" ")); // including space
        str1 = TrimRight(str1);
        str2 = str2.SubString(str1.Length() + 2, str1.Length());

        myword = str1 + "," + str2;

        if (str1.SubString(1, 2) == "**") {
            myword = "";
            continue;

        } else if ((str1.SubString(1, 6) == "333333" &&
                       str2.SubString(1, 6) == "333333") ||
                   (str1.SubString(1, 6) == "555555" &&
                       str2.SubString(1, 6) == "555555"))
        {
            ps_count++;
            if (ps_count == br_line->Value) {
                break;
            }
            //            break;
        } else if (str1.SubString(1, 1) == "0" && str2.SubString(1, 1) == "0") {
            myword = "";
            continue;
        }

        //        else if (Form1->mystoi(str1.c_str()) > Form2->Work->Width ||
        //                 Form1->mystoi(str2.c_str()) > Form2->Work->Height)
        //        {
        //            RichEdit1->Lines->Add(str1 + "," + str2);
        //            ShowMessage("coordernate exceeding box size!!");
        //            return;
        //}
        else
        {
            point_buff[0] = Form1->mystoi(str1.c_str());
            point_buff[1] = Form1->mystoi(str2.c_str());
            //set red

            int nwcl = (int)mmp[mpen].col;
            ptr = reinterpret_cast<TRGBTriple*>(
                Bitmap->ScanLine[point_buff[1]]); // certain 4 rows
            ptr[point_buff[0]].rgbtBlue = nwcl % 256;
            nwcl /= 256;
            ptr[point_buff[0]].rgbtGreen = nwcl % 256;
            nwcl /= 256;
            ptr[point_buff[0]].rgbtRed = nwcl % 256;
            mpen++; //looping with while
            if (mpen == Size_clmp) {
                mpen = red;
            }

            //            ptr = reinterpret_cast<TRGBTriple*>(
            //                Bitmap
            //                    ->ScanLine[point_buff[1]]); // all rows makes vertical line.
            //            ptr[point_buff[0]].rgbtRed = 255;
            //            ptr[point_buff[0]].rgbtGreen = 0;
            //            ptr[point_buff[0]].rgbtBlue = 0;
        }
        RichEdit->Lines->Add(myword);
    }

    Work->Canvas->Draw(0, 0, Bitmap.get());
    delete read_file;

    //    } catch (Exception &ex) { //FileIO.MalformedLineException
    //        ShowMessage("Line" + ex.Message + "is not valid and will be skipped.");
    //		delete read_file;
    //    }
}

//---------------------------------------------------------------------------
void __fastcall TForm2::BtnOpnSrcClick(TObject* Sender)
{
    if (Form2->OpnTxtFlDiag->Execute()) {
        //Form2->OpSTFilePath = g_current_path;
        Form2->OpenFileName = Form2->OpnTxtFlDiag->FileName;
        Form2->OpenFilePath = Form2->OpenFileName;
        //Form2->OpenFileName = //cut the latter half of
    }
    if (!Form2->OpenFileName.IsEmpty()) {
        Form2->TxtLoadLbl->Show();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject* Sender)
{
    //    Form2->PaintBox1->Canvas->Brush->Color = clBlack;
    //    Form2->Work->Height = Form1->PaintEq->Height;
    //    Form2->Work->Width = Form1->PaintEq->Width;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Btn_ShowClick(TObject* Sender)
{
    //    TCanvas* mycanvas = Work->Canvas;
    //
    //    // Draw a circle at position (50, 50) with a radius of 30
    //    mycanvas->Ellipse(50, 50, 80, 80);
    Form2->RichEdit->Lines->Clear();
    Form2->RichEdit->Lines->Add("my data");

    //do Show_picture();
    TForm2::Show_picture();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Btn_ExitClick(TObject* Sender)
{
    Form2->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Btn_ClearClick(TObject* Sender)
{
    // Clear the entire paint area by filling it with a white color
    Work->Canvas->Brush->Color = clBlack;
    Work->Canvas->FillRect(Work->ClientRect);
    // show the object, picture_show
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SavPicBtnClick(TObject* Sender)
{
    wchar_t szFileName[MAXFILE + 4];
    int FileHandle;
    int theLen;
    int count;

    if (SavePicDialog1->Execute()) {
        //backup existing files
        if (FileExists(Form2->SavePicDialog1->FileName)) {
            _wfnsplit(
                Form2->SavePicDialog1->FileName.w_str(), 0, 0, szFileName, 0);
            wcscat(szFileName, L".BAK");

            RenameFile(SavePicDialog1->FileName, szFileName);
        }
        //creating file
        FileHandle = FileCreate(SavePicDialog1->FileName);

        FileClose(FileHandle);

        SavPicName = SavePicDialog1->FileName;
        RichEdit->Lines->Add("prt name:" + SavPicName);
        //        SaveFilePath = SavPicName;
        Work->Picture->SaveToFile(SavPicName);
    }
    if (!Form2->SavPicName.IsEmpty()) {
        Form2->SavPicLabl->Show();
    }
}
//---------------------------------------------------------------------------

