#include "Ls2txt3.h"
#include "IOUtils.hpp"
#include <dir.h> //MAXFILE

void __fastcall TForm1::JSavToCsvClick(TObject *Sender)
{
     //save to excel
//    if (Form1->JSavCsvDlg->Execute()) {
//        SaveFileName = Form1->JSavCsvDlg->FileName;
//        //check if extensoin is correct
//        int ptplace;
//        ptplace = LastDelimiter(".", Form3->SavFileName);
//        if (ptplace == 0) {
//            SaveFileName = Form1->JSavCsvDlg->FileName + ".";
//        } else if (SaveFileName.SubString(
//                       SaveFileName.Length() - ptplace + 2, 4) == "xlsx")
//        {
//            ShowMessage("ª`·N°ÆÀÉ¦W");
//        }
//
//        else
//        {
//            ShowMessage("FileName Exception");
//            SaveFileName.Delete(SaveFileName.Length() - ptplace + 2, 10);
//            SaveFileName = Form1->SaveFileName + ".xlsx";
//        }
//    }

    //set the name to variable
    wchar_t szFileName[MAXFILE + 4];
    int FileHandle;
    int theLen;
    int count;

    if (JSavCsvDlg->Execute()) {
        //backup existing files
        if (FileExists(Form1->JSavCsvDlg->FileName)) {
            _wfnsplit(Form1->JSavCsvDlg->FileName.w_str(), 0, 0, szFileName, 0);
            wcscat(szFileName, L".BAK");

            RenameFile(JSavCsvDlg->FileName, szFileName);
        }
        //creating file
        FileHandle = FileCreate(JSavCsvDlg->FileName);

        FileClose(FileHandle);

        SaveFileName = JSavCsvDlg->FileName;
        RichEdit->Lines->Add("prt name:" + SaveFileName);
        SaveFilePath = TPath::GetDirectoryName(SaveFileName);
    }
    if (!Form1->SaveFileName.IsEmpty()) {
        Form1->CsvSavLabl->Show();
    }


        //------------- WRTING TO AN OUTPUT FILE STREAM -----------------------------------
    std::ofstream ofs1;

    ofs1.open(
        "D:\\OS000175\\Documents\\Embarcadero\\Studio\\Projects\\ECU_projs\\supply\\my_stream_test.txt",
        std::ios::out | // output file stream
            std::ios::app | // can append to a existing file
            std::ios::ate); // set file cursor at the end

    if (ofs1) {
        RichEdit->Lines->Add("my first");
        RichEdit->Lines->Add("my second");
        RichEdit->Lines->Add("my third");
        ofs1 << "This is my first record" << std::endl;
        ofs1 << "This is my second record" << std::endl;
        ofs1 << "This is my third record" << std::endl;

        ofs1.close();
    } else
        std::cout << "Unable to open file to write" << std::endl;

    //------------- READING FROM AN INPUT FILE STREAM -----------------------------------
    std::ifstream ifs1 ;
    std::string str;
    ifs1.open(
        "D:\\OS000175\\Documents\\Embarcadero\\Studio\\Projects\\ECU_projs\\supply\\my_stream_out.txt",
        std::ios::in); // input file stream

    if (ifs1) {
        while (!ifs1.eof()) {
            std::getline(ifs1, str);
//            std::cout << str << std::endl;
            RichEdit->Lines->Add((UnicodeString)str.c_str());
        }
        ifs1.close();
    } else
        std::cout << "Unable to open file to read" << std::endl;

    getchar();

     // test if the data is reachable from different forms

    

}


//---------------------------------------------------------------------------

