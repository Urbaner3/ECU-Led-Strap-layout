//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Hintfix.h"

#include <System.IOUtils.hpp>
#include <System.SysUtils.hpp>

using namespace System::Ioutils;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
THintFrm* HintFrm;
//---------------------------------------------------------------------------
__fastcall THintFrm::THintFrm(TComponent* Owner) : TForm(Owner) {
	checklist = new TStringList();
}
//---------------------------------------------------------------------------
void __fastcall THintFrm::FormCreate(TObject* Sender)
{
	ImageMemo->WordWrap = true;

    // Specify the file path you want to read
    String FilePath = "MyScript.txt"; // Update this to your file's path
    String steps;
    try {
        // Create a TStreamReader to read the file line by line
        std::vector<String> lines; // A vector to store each line

		// Using TStreamReader for line-by-line reading
		TStreamReader* Reader = new TStreamReader(FilePath);
        try {
            while (!Reader->EndOfStream) // Read until the end of the stream
            {
                String line = Reader->ReadLine(); // Read a line
				lines.push_back(line); // Store the line in the vector
			}
        } __finally
        {
            delete Reader; // Clean up Reader
        }

        // Display lines in TMemo (optional)
		ImageMemo->Lines->Clear();
		int ii = 0;

		for (const String &line : lines) {
			HintMemo->Lines->Add( line); // Add each line to the memo
			//independent task which takes for loop
			if (39 < ii && ii < 54) { //line 41-54 cond ii 40-53
				MystepsMemo->Lines->Add(IntToStr(ii) + line);
			} else if (13 < ii && ii < 39) { //  ii 14-38 ;line 15-39 odds
				if ((ii - 14) % 2 == 0) {
					checklist->Add(line);
				}
				//else
			} else {
				//skipped
			}

			ii++;
		}

	}

    catch (const Exception &e)
    {
        ShowMessage("Error reading file: " + e.Message);
	}

    // Initialize the current image index and load the first image
    currentImageIndex = 0;
	LoadImage(currentImageIndex);
	ImageMemo->Text = checklist->Strings[currentImageIndex];

}
//---------------------------------------------------------------------------

void __fastcall THintFrm::BtnNextPicClick(TObject* Sender)
{
    if (currentImageIndex < ImageList1->Count - 1) {
		currentImageIndex++;
        LoadImage(currentImageIndex);
    } else {
		ImageMemo->Text = L"no next";
	}
		ImageMemo->Text = checklist->Strings[currentImageIndex];
}
//---------------------------------------------------------------------------

void __fastcall THintFrm::BtnPrevPicClick(TObject* Sender)
{
    if (currentImageIndex > 0) {
        currentImageIndex--;
        LoadImage(currentImageIndex);
    } else {
        ImageMemo->Text = L"no prev";
	}
	ImageMemo->Text = checklist->Strings[currentImageIndex];
}
//---------------------------------------------------------------------------

void THintFrm::LoadImage(int index)
{
    if (index >= 0 && index < ImageList1->Count) {
        //		ImageView->Bitmap->Assign(ImageList1->Source[index+1].MultiResBitmap[0]->Bitmap);
        Glyph1->ImageIndex = currentImageIndex;
        BtnPrevPic->Enabled = (index > 0);
		BtnNextPic->Enabled = (index < ImageList1->Source->Count - 1);
	}
}

void __fastcall THintFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
    checklist->Clear();
}
//---------------------------------------------------------------------------


