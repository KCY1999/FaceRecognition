//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CC.cpp"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FileListBox1Click(TObject *Sender)
{
	Image1->Picture->LoadFromFile(FileListBox1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image1DblClick(TObject *Sender)
{
	Bmp=LoadImage(FileListBox1->FileName);
	Image2->Picture->Assign(Bmp);
	Image2->Width=Bmp->Width;
	Image2->Height=Bmp->Height;

	Image16->Picture->Bitmap=new Graphics::TBitmap();
	Image16->Width=Bmp->Width;
	Image16->Height=Bmp->Height;
	Image16->Picture->Bitmap->Width=Bmp->Width;
	Image16->Picture->Bitmap->Height=Bmp->Height;
	Image16->Picture->Bitmap->PixelFormat=pf24bit;

	Image17->Picture->Bitmap=new Graphics::TBitmap();
	Image17->Width=100;
	Image17->Height=Bmp->Height;
	Image17->Picture->Bitmap->Width=100;
	Image17->Picture->Bitmap->Height=Bmp->Height;
	Image17->Picture->Bitmap->PixelFormat=pf24bit;
	Image17->Left=Image16->Left+Image16->Width+50;

	fgImgLoad=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image2MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	int r,g,b;
	int h,s,v;
	AnsiString str;

	if(!(fgImgLoad))
        return;
	GetRGB(Image2->Picture->Bitmap,X,Y,&r,&g,&b);

	str="R="+IntToStr(r)+",G="+IntToStr(g)+",B="+IntToStr(b);
	StatusBar1->Panels->Items[0]->Text=str;
//----------------------------
	RGBToHSV(r,g,b,&h,&s,&v);
	str="H="+IntToStr(h)+",S="+IntToStr(s)+",V="+IntToStr(v);

	StatusBar1->Panels->Items[1]->Text=str;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	fgImgLoad=false;
	hProjection=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SKIN1Click(TObject *Sender)
{
   Skin(Image2->Picture->Bitmap,Image16->Picture->Bitmap);
   TabSheet11->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SKINBinary1Click(TObject *Sender)
{
   ToBinary_B(Image16->Picture->Bitmap,Image16->Picture->Bitmap,200);
   TabSheet11->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::H1Click(TObject *Sender)
{
   float scale;

   if(hProjection!=NULL)
   {
	   delete []hProjection;
	   hProjection=NULL;
   }
   else
   {
	   try
	   {
			hProjection=new int [Image16->Height];

			for(int i=0;i<Image16->Height;i++)
			   hProjection[i]=0;
	   }
	   catch(...)
	   {
			ShowMessage("Allocate memory error");
			return;
	   }
   }
	H_projection(Image16->Picture->Bitmap,&hProjection[0]);
																			   //畫筆是白的
	Image17->Canvas->Brush->Color=clWhite;
	Image17->Canvas->FillRect(TRect(0,0,Image17->Width,Image17->Height));      //TRect給座標

	scale=(float)Image16->Width/(float)Image17->Width;
	DrawHProjection(&hProjection[0],Image17,Image17->Height,scale);

	TabSheet11->Repaint();
	if(hProjection!=NULL)
	{
		delete hProjection;
		hProjection=NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::drawline1Click(TObject *Sender)
{
	int c,width;
	Image2->Canvas->Brush->Style=bsClear;
	Image2->Canvas->Pen->Color=clRed;
	width=Image2->Width;

	c=Image2->Height/10;
	Image2->Canvas->Rectangle(40,50,170,230);
}
//--------------------------------------------------------------------------

