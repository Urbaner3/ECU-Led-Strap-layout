//---------------------------------------------------------------------------

#ifndef HintfixH
#define HintfixH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Types.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <System.Rtti.hpp>
#include <vector>
//---------------------------------------------------------------------------
class THintFrm : public TForm
{
  __published: // IDE-managed Components
    TTabControl* TabControl2;
    TTabItem* blockIntro;
    TImageViewer* HintImage;
    TTabItem* Guide;
    TImageList* ImageList1;
    TGroupBox* GroupBtn;
    TCornerButton* BtnPrevPic;
    TCornerButton* BtnNextPic;
    TMemo* ImageMemo;
    TGlyph* Glyph1;
    TScaledLayout* ScaledLayout1;
    TMemo* MystepsMemo;
    TMemo* HintMemo;
    void __fastcall FormCreate(TObject* Sender);
    void __fastcall BtnNextPicClick(TObject* Sender);
	void __fastcall BtnPrevPicClick(TObject* Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  private: // User declarations
	int currentImageIndex;
	TStringList *checklist;
    void LoadImage(int index);
  public: // User declarations
    __fastcall THintFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THintFrm* HintFrm;
//---------------------------------------------------------------------------
#endif

