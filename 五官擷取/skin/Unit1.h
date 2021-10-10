//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>

#include "ImgProc.h"
#include "CC.h"
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TDriveComboBox *DriveComboBox1;
	TDirectoryListBox *DirectoryListBox1;
	TFileListBox *FileListBox1;
	TImage *Image1;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Filter1;
	TStatusBar *StatusBar1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TImage *Image2;
	TTabSheet *TabSheet11;
	TImage *Image16;
	TMenuItem *SKIN1;
	TMenuItem *SKINBinary1;
	TMenuItem *H1;
	TImage *Image17;
	TMenuItem *drawline1;
	void __fastcall FileListBox1Click(TObject *Sender);
	void __fastcall Image1DblClick(TObject *Sender);
	void __fastcall Image2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SKIN1Click(TObject *Sender);
	void __fastcall SKINBinary1Click(TObject *Sender);
	void __fastcall H1Click(TObject *Sender);
	void __fastcall drawline1Click(TObject *Sender);



private:	// User declarations
	bool fgImgLoad;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

	Graphics::TBitmap *Bmp;
	int *hProjection;
	int *sProjection;

	};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
