//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>

#include "cc.h"
#include "Morphology.h"

#define BINARY_FOREGROUND 0
#define BINARY_BACKGROUND 255
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button3;
	TButton *Button1;
	TButton *Button2;
	TImage *Image1;
	TOpenPictureDialog *OpenPictureDialog1;
	TImage *Image2;
	TImage *Image3;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button8;
	TButton *Button10;
	TImage *Image4;
	TImage *Image5;
	TImage *Image6;
	TButton *Button7;
	TButton *Button9;
	TMemo *Memo2;
	TMemo *Memo1;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button11;
	TScrollBar *ScrollBar1;
	TScrollBar *ScrollBar2;
	TScrollBar *ScrollBar3;
	TScrollBar *ScrollBar4;
	TScrollBar *ScrollBar5;
	TScrollBar *ScrollBar6;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall ScrollBar1Change(TObject *Sender);
	void __fastcall ScrollBar2Change(TObject *Sender);
	void __fastcall ScrollBar3Change(TObject *Sender);
	void __fastcall ScrollBar4Change(TObject *Sender);
	void __fastcall ScrollBar5Change(TObject *Sender);
	void __fastcall ScrollBar6Change(TObject *Sender);

private:	// User declarations
public:		// User declarations

	Graphics::TBitmap *bmp1,*bmp2,*bmp3,*bmp4;
	Graphics::TBitmap *Bmp;
	int *hProjection;
	int *vProjection;

	__fastcall TForm1(TComponent* Owner);
	void __fastcall ToGray(Graphics::TBitmap *,Graphics::TBitmap *);
	void __fastcall RGBToHSV(int , int , int , int *, int *, int *);
	void __fastcall Colorr(Graphics::TBitmap *, Graphics::TBitmap *);
	void __fastcall ToBinary_S(Graphics::TBitmap *,Graphics::TBitmap *,int );
	void __fastcall H_Projection(Graphics::TBitmap *,int *);
	void __fastcall DrawHProjection(int *,TImage *,int ,float );
	void __fastcall V_Projection(Graphics::TBitmap *,int *);
	void __fastcall DrawVProjection(int *,TImage *,int ,float );
	void __fastcall re(Graphics::TBitmap *,Graphics::TBitmap *,int ); //?h?????n??????
	void __fastcall ee(Graphics::TBitmap *,Graphics::TBitmap *);
	void __fastcall HSV(Graphics::TBitmap *,Graphics::TBitmap *);

	ConntdCompnt CC;
	MorphyObj Morphy;

	void MorphoInitial();
	void InitCC();
	void FillBlack(Graphics::TBitmap *);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
