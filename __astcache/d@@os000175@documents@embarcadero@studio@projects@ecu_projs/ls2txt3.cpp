//---------------------------------------------------------------------------

#include <vcl.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#pragma hdrstop

#include "Ls2txt3.h"
#include "ShowTxt.h"
#include "chngpt2sav.h"
#include "check80ptLoc.h"
#include "angle45.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <dir.h> // save function

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1* Form1;

using namespace std;

//color maps ; defined in Tcolor

struct Info
{
    unsigned int id; //ID
    int x1; //起始座標 x
    int y1; //起始座標 y
    int x2; //終點座標 x
    int y2; //終點座標 y
    int ang; //角度
    int length; //長度(LED數量)
    int scan_port; //是否切換 Scan Board 的輸出 port
    int ddu_port; //是否切換 DDU Board 的輸出 port
    int spu_port; //是否切換 SPU Board 的輸出 port
};
Info PointData;

//AnsiString OpenFileName ;//= "ECU_input_fix.csv";

uint32_t TForm1::GetEndPoint(
    int head_x, int head_y, int angle, int length, int* end_x, int* end_y)
{
    //type transferring : (uint32_t head_x, uint32_t head_y, int angle, uint32_t length, uint32_t *end_x, uint32_t *end_y)
    // uint32_t nbuff[9] = {0};
    // int ctrj; //counter_j
    //     for(ctrj = 0; ctrj < 9; ctrj ++){
    //     }
    double temp = 0;
    temp = length / sqrt(2);
    puts("results matters");
    printf("hd_x:%d, hd_y:%d, ang:%d, len:%d\n", head_x, head_y, angle, length);
    printf("tmp:%lf, ed_x:%d, ed_y:%d\n", temp, *end_x, *end_y);
    switch (angle) {
        case 0:
        case 360:
        case -360:
            *end_x = head_x + length;
            *end_y = head_y;
            break;
        case 45:
        case -315:
            *end_x = static_cast<uint32_t>(head_x + temp);
            *end_y = head_y + temp;
            break;
        case 90:
        case -270:
            *end_x = head_x;
            *end_y = head_y + length;
            break;
        case 135:
        case -225:
            *end_x = (head_x - temp);
            *end_y = (head_y + temp);
            break;
        case 180:
        case -180:
            *end_x = head_x - length;
            *end_y = head_y;
            break;
        case 225:
        case -135:
            *end_x = static_cast<uint32_t>(head_x - temp);
            *end_y = static_cast<uint32_t>(head_y - temp);
            break;
        case 270:
        case -90:
            *end_x = head_x;
            *end_y = head_y - length;
            break;
        case 315:
        case -45:
            *end_x = static_cast<uint32_t>(head_x + temp);
            *end_y = static_cast<uint32_t>(head_y - temp);
            break;
        default:
            return 1;
    }

    return 0;
}

uint32_t TForm1::GetEndPoint6(
    int head_x, int head_y, int angle, int length, int* end_x, int* end_y)
{
    // (uint32_t head_x, uint32_t head_y, int angle, uint32_t length, uint32_t end_x, uint32_t end_y)
    double x_add, y_add, len_x, len_y;
    int ang = 0;
    // Calculate Sin and Cos needs angle adjustment
    if (angle > 270) {
        ang = 360 - angle;
    } else if (angle > 180) {
        ang = angle - 180;
    } else if (angle > 90) {
        ang = 180 - angle;
    } else if (angle > 0) {
        ang = angle;
    } else if (angle > -90) {
        ang = abs(angle);
    } else if (angle > -180) {
        ang = 180 - abs(angle);
    } else if (angle > -270) {
        ang = abs(angle) - 180;
    } else if (angle > -360) {
        ang = 360 - abs(angle);
    }
    // Convert to corresponding x, y lengths to be added or subtracted
    x_add = round(length * round(cos((M_PI / 180) * (ang)))) - 1;
    y_add = round(length * round(sin((M_PI / 180) * (ang)))) - 1;
    len_x = x_add;
    len_y = y_add;
    // Calculate endpoint coordinates
    if (angle == 0 || angle == 360) {
        *end_x = head_x - len_x;
        *end_y = head_y;
    } else if (angle == 45) {
        *end_x = head_x - len_x;
        *end_y = head_y + len_y;
    } else if (angle > 0 && angle < 90) {
        *end_x = head_x - x_add;
        *end_y = head_y + y_add;
    } else if (angle == 90) {
        *end_x = head_x;
        *end_y = head_y + len_y;
    } else if (angle == 135) {
        *end_x = head_x + len_x;
        *end_y = head_y + len_y;
    } else if (angle > 90 && angle < 180) {
        *end_x = head_x + x_add;
        *end_y = head_y + y_add;
    } else if (angle == 180) {
        *end_x = head_x + len_x;
        *end_y = head_y;
    } else if (angle == 225) {
        *end_x = head_x + len_x;
        *end_y = head_y - len_y;
    } else if (angle > 180 && angle < 270) {
        *end_x = head_x + x_add;
        *end_y = head_y - y_add;
    } else if (angle == 270) {
        *end_x = head_x;
        *end_y = head_y - len_y;
    } else if (angle == 315) {
        *end_x = head_x - len_x;
        *end_y = head_y - len_y;
    } else if (angle > 270 && angle < 360) {
        *end_x = head_x - x_add;
        *end_y = head_y - y_add;
    } else if (angle == -360) {
        *end_x = head_x + len_x;
        *end_y = head_y;
    } else if (angle == -315) {
        *end_x = head_x + len_x;
        *end_y = head_y - len_y;
    } else if (angle > -360 && angle < -270) {
        *end_x = head_x + x_add;
        *end_y = head_y - y_add;
    } else if (angle == -270) {
        *end_x = head_x;
        *end_y = head_y - len_y;
    } else if (angle == -225) {
        *end_x = head_x - len_y;
        *end_y = head_y - len_x;
    } else if (angle > -270 && angle < -180) {
        *end_x = head_x - x_add;
        *end_y = head_y - y_add;
    } else if (angle == -180) {
        *end_x = head_x - len_x;
        *end_y = head_y;
    } else if (angle == -135) {
        *end_x = head_x - len_x;
        *end_y = head_y + len_y;
    } else if (angle > -180 && angle < -90) {
        *end_x = head_x - x_add;
        *end_y = head_y + y_add;
    } else if (angle == -90) {
        *end_x = head_x;
        *end_y = head_y + len_y;
    } else if (angle == -45) {
        *end_x = head_x + len_x;
        *end_y = head_y + len_y;
    } else if (angle > -90 && angle < 0) {
        *end_x = head_x + x_add;
        *end_y = head_y + y_add;
    } else {
        return 1;
    }
    return 0;
}

const std::vector<std::string> TForm1::split(
    const std::string &str, const std::string &pattern)
{
    std::vector<std::string> result;
    std::string::size_type begin, end;
    end = str.find(pattern);
    begin = 0;
    while (end != std::string::npos) {
        if (end - begin != 0) {
            result.push_back(str.substr(begin, end - begin));
        }
        begin = end + pattern.size();
        end = str.find(pattern, begin);
    }
    if (begin != str.length()) {
        result.push_back(str.substr(begin));
    }
    return result;
}

int TForm1::mystoi(const string &pat)
{
    int ii, sum, pos = 0;
    char tmp;
    sum = 0;
    for (ii = 0; ii < pat.size(); ii++) {
        tmp = (char)pat[ii];
        if (tmp == '-') {
            pos = 1;
            continue;
        }
        sum *= 10;
        sum += (tmp - '0');
    }
    if (pos == 1)
        sum *= (-1);
    return sum;
}

void TForm1::Read_File2(int sselect)
{
    unsigned char start_flag = 0;

    int buff[9] = { 0 };
    int count = 0;
    uint32_t err = 0;
    int jj = 0;
    vector<string> currentRow;
    Form1->RichEdit->Lines->Add("ReadFile2 head!");
    UnicodeString myword;
    std::string sent = "";
    //  UnicodeString myword = (UnicodeString) TForm1::OpenFileName;
    //  Form1->RichEdit->Lines->Add(myword);
    try {
        if (OpenFileName.IsEmpty()) {
            ShowMessage("Please select 'Open' file.");
            return;
        }
        std::ifstream inputFile;
        inputFile.open((std::string)OpenFilePath, std::ifstream::in);
        if (!inputFile.is_open()) {
            ShowMessage("Failed to open the file.");
            return;
        }
        //    Form1->RichEdit->Lines->Add("if checks!!");
        string line;
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

        while (getline(inputFile, line)) {
            line = "," + line; // balance the difference in c
            currentRow = split(line, ",");
            // // test output string
            // for (auto &s : currentRow) {
            //   cout << s << "\n";
            //   if (s == "\r") {
            //     puts("*");
            //   }
            // }
            for (const auto &currentField : currentRow) {
                if (start_flag == 2) {
                    buff[count] = mystoi(currentField);
                    count++;
                } else if (currentField == "Dend" && start_flag == 0) {
                    start_flag = 1;
                    //          cout << "@@";
                } else {
                    //          cout << currentField << " ";
                }
            }
            //      Form1->RichEdit->Lines->Add("Try get data");

            if (start_flag == 1) { // A tree
                start_flag = 2;
            } else if (start_flag == 2) {
                count = 0;
                // initialize buff[7], buff[8]
                buff[7] = 0, buff[8] = 0;
                if (sselect == 0) { // A-B branch tree
                    err = GetEndPoint(
                        buff[1], buff[2], buff[3], buff[4], &buff[7], &buff[8]);
                } else {
                    err = GetEndPoint6(
                        buff[1], buff[2], buff[3], buff[4], &buff[7], &buff[8]);
                }

                sent = "";
                for (jj = 0; jj < 9; jj++) {
                    sent = sent + to_string(buff[jj]) + " ";
                }
                myword = (UnicodeString)sent.c_str();
                Form1->RichEdit->Lines->Add(myword);

                // colors in circle take turns.
                Form1->PaintEq->Canvas->Pen->Color =
                    mmp[mpen].col; //my map color of mpen color
                // mpen color name is chosen

                mpen++; //looping with while
                if (mpen == Size_clmp) { // mpen reached liimit
                    mpen = red;
                }

                //   // g.DrawLine(pen, buff[1], buff[2], buff[7], buff[8]);
                Form1->PaintEq->Canvas->MoveTo(buff[1], buff[2]);
                Form1->PaintEq->Canvas->LineTo(buff[7], buff[8]);
                PointData.id = buff[0];
                PointData.x1 = buff[1];
                PointData.y1 = buff[2];
                PointData.ang = buff[3];
                PointData.length = buff[4];
                PointData.scan_port = buff[5];
                PointData.ddu_port = buff[6];
                PointData.x2 = buff[7];
                PointData.y2 = buff[8];

                // Output PointData as needed
            } // else if - line of A tree
        }
        inputFile.close();
        Form1->RichEdit->Lines->Add("end Reading.");
    } catch (const exception &ex) {
        //    cout <<  << endl;   = "ERROR: " + ex.what();
    }
    return;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {

StringGrid1->Cells[1][0] = L"Column 1";
  StringGrid1->Cells[2][0] = L"Column 2";
  StringGrid1->Cells[3][0] = L"Column 3";
  StringGrid1->Cells[4][0] = L"Column 4";
  StringGrid1->Cells[0][1] = L"Row 1";
  StringGrid1->Cells[1][1] = L"Object";
  StringGrid1->Cells[2][1] = L"Pascal";
  StringGrid1->Cells[3][1] = L"is";
  StringGrid1->Cells[4][1] = L"excellent";
  StringGrid1->Cells[0][2] = L"Row 2";
  StringGrid1->Cells[1][2] = L"Delphi";
  StringGrid1->Cells[2][2] = L"is";
  StringGrid1->Cells[4][2] = L"RAD well";

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnSavTxt1Click(TObject* Sender)
{
    //set the name to variable
    wchar_t szFileName[MAXFILE + 4];
    int FileHandle;
    int theLen;
    int count;

    if (SavTxtDlg1->Execute()) {
        //backup existing files
        if (FileExists(Form1->SavTxtDlg1->FileName)) {
            _wfnsplit(Form1->SavTxtDlg1->FileName.w_str(), 0, 0, szFileName, 0);
            wcscat(szFileName, L".BAK");

            RenameFile(SavTxtDlg1->FileName, szFileName);
        }
        //creating file
        FileHandle = FileCreate(SavTxtDlg1->FileName);
        // Write out the number of rows and columns in the grid.
        count = StringGrid1->ColCount;
        FileWrite(FileHandle, &count, sizeof(count));
        count = StringGrid1->RowCount;
        FileWrite(FileHandle, &count, sizeof(count));
        for (int x = 0; x < StringGrid1->ColCount; x++) {
            for (int y = 0; y < StringGrid1->RowCount; y++) {
                // Write out the length of each string, followed by the string itself.
                theLen = StringGrid1->Cells[x][y].Length() * sizeof(wchar_t);
                FileWrite(FileHandle, (wchar_t*)&theLen, sizeof(theLen));
                FileWrite(
                    FileHandle, StringGrid1->Cells[x][y].w_str(), theLen);
            }
        }

        FileClose(FileHandle);

        //        SaveFileName = SavTxtDlg1->FileName;
        //        SaveFilePath = SaveFileName;
    }
    if (!Form1->SaveFileName.IsEmpty()) {
        Form1->SavFilLabl->Show();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnExitClick(TObject* Sender)
{
    Form1->Close(); // Close the form and exit the Application.
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnSrcClick(TObject* Sender)
{
    if (srcOpDlg1->Execute()) {
        OpenFileName = srcOpDlg1->FileName;
        OpenFilePath = OpenFileName;
    }

    if (!Form1->OpenFileName.IsEmpty()) {
        Form1->OpnFilLabl->Show();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnClearClick(TObject* Sender)
{
    // Clear the entire paint area by filling it with a white color
    PaintEq->Canvas->Brush->Color = clWhite;
    PaintEq->Canvas->FillRect(PaintEq->ClientRect);
    Form1->RichEdit->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnShowClick(TObject* Sender)
{
    //ReadFile();

    Form1->RichEdit->Lines->Clear();
    Form1->RichEdit->Lines->Add("my data");
    Form1->Read_File2(1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnF2ShowClick(TObject* Sender)
{
    Form2->Show();
    //    Form1->Enabled = False;      //focus on TxtCheck Window
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnchgClick(TObject* Sender)
{
    Form1->ChangePointToSave(SaveFilePath);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PaintEqPaint(TObject* Sender)
{
    //        Canvas->Rectangle( 10, 15, ClientWidth / 2, ClientHeight / 2 );
    //	Canvas->Ellipse( 0, 0, ClientWidth / 2, ClientHeight / 2 );

    //        Form1->PaintEq->Canvas->MoveTo( 3, 3 );
    //	Form1->PaintEq->Canvas->LineTo( 3, ClientHeight-3 );
    //	Form1->PaintEq->Canvas->MoveTo( 3, ClientHeight-3 );
    //	Form1->PaintEq->Canvas->LineTo( ClientWidth-3, ClientHeight-3);
    //        Form1->PaintEq->Canvas->MoveTo( ClientWidth-3, ClientHeight-3);
    //        Form1->PaintEq->Canvas->LineTo( 3, 3);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PortLockBoxClick(TObject* Sender)
{
    Form1->RichEdit->Lines->Add("box clicked");
    if (Form1->PortLockBox->Checked == true) {
        Form1->SBUptNum->Enabled = false;
        Form1->DDUptNum->Enabled = false;
    } else {
        Form1->SBUptNum->Enabled = true;
        Form1->DDUptNum->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::WidthSetChange(TObject* Sender)
{
    Form1->PaintEq->Width = Form1->WidthSet->Value;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::HeightSetChange(TObject* Sender)
{
    Form1->PaintEq->Height = Form1->HeightSet->Value;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject* Sender)
{
    Form1->WidthSet->Value = Form1->PaintEq->Width;
    Form1->HeightSet->Value = Form1->PaintEq->Height;
}
//---------------------------------------------------------------------------

