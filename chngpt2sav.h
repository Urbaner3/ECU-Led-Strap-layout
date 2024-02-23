
#include <Math.hpp>
#include "Ls2txt3.h"

// Declare your global variables here
int Center_x = 100; // Example value, replace with your actual value
int Center_y = 100; // Example value, replace with your actual value
int ScanBoard_Portlocation = 0; // Example value, replace with your actual value
int DDUBoard_Portlocation = 0; // Example value, replace with your actual value
int SPUBoard_Portlocation = 0; // Example value, replace with your actual value

struct PointData
{
    int id, x1, y1, ang, length, scan_port, ddu_port, x2, y2, spu_port;
};

PointData myPoint;

AnsiString OpenFileName, OpenFilePath, SaveFileName, SaveFilePath;

using namespace std;

void TForm1::ChangePointToSave(AnsiString file_path)
{
    unsigned int start_flag = 0;
    int buff[10] = { 3 }, count = 0;
    unsigned int err;
    AnsiString str = "aaa";
    UnicodeString Ustr;
    std::string myword = "";
//    int point_buff[101][101] = { 0 };
    int point_buff[2][100] = { 0 };
    int i = 0;
    int scan_board_add_zero_data = 0;

    int ScanBoard_Port = Form1->SBUptNum->Value;
    int DDUBoard_Port = Form1->DDUptNum->Value;

    myPoint.spu_port = 0; // Example value, replace with your actual value

    try {
        if (OpenFilePath == "") {
            ShowMessage("Please select 'Open' file.");
            return;
        } else if (SaveFilePath == "") {
            ShowMessage("Please select 'Save' file.");
            return;
        }

        DeleteFile(SaveFilePath);
        str =
            "**This coordinate file Is created specifically for D3 Mapping System**\r\n";
        TFileStream* fs = new TFileStream(SaveFilePath, fmCreate);
        fs->Write(str.c_str(), str.Length());
        delete fs;

        TStreamReader* sr = new TStreamReader(OpenFilePath);
        while (!sr->EndOfStream) {
            TStringList* currentRow = new TStringList();
            currentRow->Delimiter = ',';
            currentRow->DelimitedText = sr->ReadLine();

            try {
                for (int j = 0; j < currentRow->Count; j++) {
                    AnsiString currentField = currentRow->Strings[j];
                    //myword = (UnicodeString) currentField.c_str();
                    Form1->RichEdit->Lines->Add(currentField);

                    if (start_flag == 2) { // tree A
                        //buff[count] = currentField.ToInt();
                        buff[count] = mystoi(currentField.c_str());
                        count++;
                    } else if (currentField == "Dend" && start_flag == 0) {
                        start_flag = 1;
                    }
                }
                Form1->RichEdit->Lines->Add("treeB");
                if (start_flag == 1) { //tree B
                    Form1->RichEdit->Lines->Add("treeB if branch");
                    start_flag = 2;

                } else if (start_flag == 2) {
                    // not enter here
                    Form1->RichEdit->Lines->Add("treeB else branch");
                    count = 0;
                    if (ScanBoard_Portlocation == 0) {
                        ScanBoard_Portlocation++;
                    }
                    if (DDUBoard_Portlocation == 0) {
                        DDUBoard_Portlocation++;
                    }

                    buff[7] = 0, buff[8] = 0;

                    err = GetEndPoint6(
                        buff[1], buff[2], buff[3], buff[4], &buff[7], &buff[8]);
                    Form1->RichEdit->Lines->Add("before 80");
                    myword = "";
                    int kk;
                    for (kk = 0; kk < 9; kk++) {
                        myword = myword + to_string(buff[kk]) + " ";
                    }
                    Ustr = (UnicodeString)myword.c_str();
                    Form1->RichEdit->Lines->Add(Ustr);

                    Check80x80PointLocation(
                        buff[3], buff[1], buff[2], buff[7], buff[8]);
                    Form1->RichEdit->Lines->Add("after 80");
                    myword = "";
                    for (kk = 0; kk < 9; kk++) {
                        myword = myword + to_string(buff[kk]) + " ";
                    }
                    Ustr = (UnicodeString)myword.c_str();
                    Form1->RichEdit->Lines->Add(Ustr);

                    myPoint.id = buff[0];
                    myPoint.x1 = buff[1];
                    myPoint.y1 = buff[2];
                    myPoint.ang = buff[3];
                    myPoint.length = buff[4];
                    myPoint.scan_port = buff[5];  //
                    //myPoint.spu_port??
                    myPoint.ddu_port = buff[6];
                    myPoint.x2 = buff[7];
                    myPoint.y2 = buff[8];

                    Angle_45(myPoint.ang, myPoint.length, myPoint.x1 + Center_x,
                        myPoint.y1 + Center_y, myPoint.x2 + Center_x,
                        myPoint.y2 + Center_y, point_buff);

                    for (kk = 0; kk < myPoint.length; kk++) {
                        str = Format("%-5d (%3d , %3d)", kk, point_buff[0][kk],
                            point_buff[1][kk]);
                        Form1->RichEdit->Lines->Add(str);
                    }

                    Form1->RichEdit->Lines->Add("mid pass"); //換行

                    //座標寫入
                    for (i = 0; i < myPoint.length; i++) {
                        str = Format(
                            " %09d %1d\r\n", point_buff[0][i], point_buff[1][i]);
                        TFileStream* fs =
                            new TFileStream(SaveFilePath, fmOpenWrite);
                        fs->Seek(0, soFromEnd);
                        fs->Write(str.c_str(), str.Length());
                        delete fs;
                    }
                    scan_board_add_zero_data = 0;

                    //是否切換 Scan port 輸出線路     uno
                    if (myPoint.scan_port) { //是否切換 Scan port 輸出線路
                        ScanBoard_Portlocation++; //Scan Board輸出位置累加
                        str = "  333333 333333 uno\r\n";
                        if (scan_board_add_zero_data == 0) {
                            scan_board_add_zero_data = 1;
                        }
                        TFileStream* fs =
                            new TFileStream(SaveFilePath, fmOpenWrite);
                        fs->Seek(0, soFromEnd);
                        fs->Write(str.c_str(), str.Length());
                        delete fs;
                    }
                    //是否切換 DDU 的輸出         dos
                    if (myPoint.ddu_port) {
                        DDUBoard_Portlocation++;
                        //檢查 Scan Board 的 Port 是否完整
                        if (ScanBoard_Portlocation < ScanBoard_Port) {
                            while (ScanBoard_Portlocation < ScanBoard_Port) {
                                if (scan_board_add_zero_data == 0) {
                                    scan_board_add_zero_data = 1;
                                }
                                str = "  0 0 dos\r\n";
                                TFileStream* fs =
                                    new TFileStream(SaveFilePath, fmOpenWrite);
                                fs->Seek(0, soFromEnd);
                                fs->Write(str.c_str(), str.Length());
                                ScanBoard_Portlocation++;
                                delete fs;

                                str = "  333333 333333 dos\r\n";
                                TFileStream* fs2 =
                                    new TFileStream(SaveFilePath, fmOpenWrite);
                                fs2->Seek(0, soFromEnd);
                                fs2->Write(str.c_str(), str.Length());
                                delete fs2;
                            }
                        }
                        str = "  555555 555555 dos\r\n";
                        TFileStream* fs3 =
                            new TFileStream(SaveFilePath, fmOpenWrite);
                        fs3->Seek(0, soFromEnd);
                        fs3->Write(str.c_str(), str.Length());
                        delete fs3;

                        ScanBoard_Portlocation = 0;
                        DDUBoard_Portlocation = 0;
                    }
                    //是否切換 SPU 的輸出 port       tres
                    if (myPoint.spu_port) {
                        SPUBoard_Portlocation++;

                        if (ScanBoard_Portlocation == 0) {
                        } else if (ScanBoard_Portlocation < ScanBoard_Port) {
                            while (ScanBoard_Portlocation < ScanBoard_Port) {
                                if (scan_board_add_zero_data == 0) {
                                    scan_board_add_zero_data = 1;
                                }
                                str = "  0 0 tres\r\n";
                                TFileStream* fs =
                                    new TFileStream(SaveFilePath, fmOpenWrite);
                                fs->Seek(0, soFromEnd);
                                fs->Write(str.c_str(), str.Length());
                                ScanBoard_Portlocation++;
                                delete fs;

                                str = "  333333 333333 tres\r\n";
                                TFileStream* fs2 =
                                    new TFileStream(SaveFilePath, fmOpenWrite);
                                fs2->Seek(0, soFromEnd);
                                fs2->Write(str.c_str(), str.Length());
                                delete fs2;
                            }
                        }

                        if (DDUBoard_Portlocation < DDUBoard_Port) {
                            while (DDUBoard_Portlocation < DDUBoard_Port) {
                                str = "  555555 555555 tres\r\n";
                                TFileStream* fs3 =
                                    new TFileStream(SaveFilePath, fmOpenWrite);
                                fs3->Seek(0, soFromEnd);
                                fs3->Write(str.c_str(), str.Length());
                                DDUBoard_Portlocation++;
                                delete fs3;
                            }
                        }

                        str = "  777777 777777 tres\r\n";
                        TFileStream* fs4 =
                            new TFileStream(SaveFilePath, fmOpenWrite);
                        fs4->Seek(0, soFromEnd);
                        fs4->Write(str.c_str(), str.Length());
                        delete fs4;

                        ScanBoard_Portlocation = 0;
                        DDUBoard_Portlocation = 0;
                    }
                }
            } catch (EConvertError &e) {
                ShowMessage("Line " + IntToStr(i) +
                            " is not valid and will be skipped.");
            }
        }

        //if (ScanBoard_Portlocation == 0) {        // tres_below
        //} else
        if (ScanBoard_Portlocation < ScanBoard_Port) {
            while (ScanBoard_Portlocation < ScanBoard_Port) {
                if (scan_board_add_zero_data == 0) {
                    scan_board_add_zero_data = 1;
                }
                str = "  0 0 tres_b\r\n";
                TFileStream* fs = new TFileStream(SaveFilePath, fmOpenWrite);
                fs->Seek(0, soFromEnd);
                fs->Write(str.c_str(), str.Length());
                ScanBoard_Portlocation++;
                delete fs;

                str = "  333333 333333 tres_b\r\n";
                TFileStream* fs2 = new TFileStream(SaveFilePath, fmOpenWrite);
                fs2->Seek(0, soFromEnd);
                fs2->Write(str.c_str(), str.Length());
                delete fs2;
            }
        } else {
            Form1->RichEdit->Lines->Add("ScanBd pass");
        }

        ScanBoard_Portlocation = 0;

//        if (DDUBoard_Portlocation == 0) {
//        } else
        if (DDUBoard_Portlocation < DDUBoard_Port) {
            while (DDUBoard_Portlocation < DDUBoard_Port) {
                str = "  555555 555555 ddus \r\n";
                TFileStream* fs3 = new TFileStream(SaveFilePath, fmOpenWrite);
                fs3->Seek(0, soFromEnd);
                fs3->Write(str.c_str(), str.Length());
                DDUBoard_Portlocation++;
                delete fs3;
            }
        } else {
            Form1->RichEdit->Lines->Add("DDU pass");
        }

        DDUBoard_Portlocation = 0;
        delete sr;
    } catch (Exception &e) {
        ShowMessage("ERROR !!");
    }
}

