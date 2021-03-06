//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int mx_x=0,mx_y=0,mi_x=999,mi_y=999;
int mxh=360,mih=0,mxs=255,mis=0,mxv=255,miv=0;

int m1=999,m2=999,y1,y2;
int m3=999,m4=999,m5=999,x1,x2,x3;

int ex=25,ey=15;
int cox=30,coy=15;
//---------------------------------------------------------------------------
int min(int a,int b)
{
	if(a>=b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

int max(int a,int b)
{
	if(a>=b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

int compare(const void *a,const void *b)
{
	int aa=*(int *)a;
	int bb=*(int *)b;

	if(aa<bb) return -1;
	if(aa>bb) return 1;
	else
	return 0;
}

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if(OpenPictureDialog1->Execute())
	{
		Bmp=new Graphics::TBitmap();
		Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
		Bmp->LoadFromFile(OpenPictureDialog1->FileName);

		bmp1=new Graphics::TBitmap();
		bmp1->Width=Bmp->Width;
		bmp1->Height=Bmp->Height;
		bmp1->PixelFormat=pf24bit;

		bmp2=new Graphics::TBitmap();
		bmp2->Width=Bmp->Width;
		bmp2->Height=Bmp->Height;
		bmp2->PixelFormat=pf24bit;

		bmp3=new Graphics::TBitmap();
		bmp3->Width=Bmp->Width;
		bmp3->Height=Bmp->Height;
		bmp3->PixelFormat=pf24bit;

		bmp4=new Graphics::TBitmap();
		bmp4->Width=Bmp->Width;
		bmp4->Height=Bmp->Height;
		bmp4->PixelFormat=pf24bit;

		Image2->Left=Image1->Left+Image1->Width+50;
		Image2->Width=Image1->Picture->Bitmap->Width;
		Image2->Height=Image1->Picture->Bitmap->Height;
		Image2->Picture->Bitmap=new Graphics::TBitmap();
		Image2->Picture->Bitmap->Width=Image1->Picture->Bitmap->Width;
		Image2->Picture->Bitmap->Height=Image1->Picture->Bitmap->Height;
		Image2->Picture->Bitmap->PixelFormat=pf24bit;

		Image3->Top=Image1->Top+Image1->Height+20;
		Image3->Height=Image1->Picture->Bitmap->Height;
		Image3->Width=Image1->Picture->Bitmap->Width;
		Image3->Picture->Bitmap=new Graphics::TBitmap();
		Image3->Picture->Bitmap->Width=Image1->Picture->Bitmap->Width;
		Image3->Picture->Bitmap->Height=Image1->Picture->Bitmap->Height;
		Image3->Picture->Bitmap->PixelFormat=pf24bit;
	 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Colorr(Image1->Picture->Bitmap,Image1->Picture->Bitmap);
	Image1->Repaint();
}
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	ToBinary_S(Image1->Picture->Bitmap,Image1->Picture->Bitmap,220);
	Image1->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  	Bmp=NULL;
	hProjection=NULL;
	vProjection=NULL;
  	Form1->Width=1350;
	Form1->Height=855;
}
//----------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	float scale;

	if(hProjection!=NULL)
	{
		delete [] hProjection;
		hProjection=NULL;
	}
	else
	{
		try
		{
			hProjection=new int [Image1->Height];

			for(int i=0;i<Image1->Height;i++)
				hProjection[i]=0;
		}
		catch (...)
		{
			ShowMessage("error");
			return;
		}
	}

	H_Projection(Image1->Picture->Bitmap,&hProjection[0]);

	Image2->Canvas->Brush->Color=clWhite;
	Image2->Canvas->FillRect(TRect(0,0,Image2->Width,Image2->Height));

	scale=(float)Image1->Width/(float)Image2->Width;

	DrawHProjection(&hProjection[0],Image2,Image2->Height,scale);
	Image2->Repaint();

    for(int i=0;i<Image2->Width;i++)
        Memo1->Lines->Add(hProjection[i]);

	if(vProjection!=NULL)
	{
		delete [] vProjection;
		vProjection=NULL;
	}
	else
	{
		try
		{
			vProjection=new int [Image1->Width];

			for(int i=0;i<Image1->Width;i++)
				vProjection[i]=0;
		}
		catch (...)
		{
			ShowMessage("error");
			return;
		}
	}

	V_Projection(Image1->Picture->Bitmap,&vProjection[0]);

	Image3->Canvas->Brush->Color=clWhite;
	Image3->Canvas->FillRect(TRect(0,0,Image3->Width,Image3->Height));

	scale=(float)Image1->Height/(float)Image3->Height;

	DrawVProjection(&vProjection[0],Image3,Image3->Width,scale);
	Image3->Repaint();
	for(int i=0;i<Image3->Width;i++)
		Memo2->Lines->Add(vProjection[i]);
	/*if(vProjection!=NULL)
	{
		delete vProjection;
		vProjection=NULL;
	}*/
}
//--------------------------????----------------------------------------------
void __fastcall TForm1::ToGray(Graphics::TBitmap *sbmp,Graphics::TBitmap *tbmp)
{
	Byte *s_ptr,*t_ptr;
	int r,g,b;
	int w,h;
	int gray;

	w=(sbmp->Width)*3;
	h=sbmp->Height;

	for (int y = 0; y < h; y++)
	{
		s_ptr=(Byte *)sbmp->ScanLine[y];
		t_ptr=(Byte *)tbmp->ScanLine[y];

		for(int x=0;x < w ; x+=3)
		{
			r=s_ptr[x+2];
			g=s_ptr[x+1];
			b=s_ptr[x];

			gray=b*0.114+g*0.587+r*0.299;
			//gray=(b+g+r)/3;

			t_ptr[x+2]=gray;
			t_ptr[x+1]=gray;
			t_ptr[x]=gray;
		}
	}
}
//-------------------------??HSV----------------------------------------------
void __fastcall TForm1::RGBToHSV(int r, int g, int b, int *ch, int *cs, int *cv)
{
	BYTE *ptr;
	float temp,mi,delta;
	int inter,c;
	float h,s,v;

	mi=min(min(r,g),b);
	v=max(max(r,g),b);
	delta=v-mi;

	if(delta==0)
		h=0;
	else
    {
		if(r==v)
			h = 60.0 * (g - b) / delta;
		if(g==v)
			h = 120.0 + 60.0 * (b - r) / delta;
		if(b==v)
			h = 240.0 + 60.0 * (r - g) / delta;
		if(h<0.0)
			h = h + 360.0;
    }

	if(v==0.0)
		s=0;
	else
		s=delta/v;

	s*=255.0;

	*ch=h;
	*cs=s;
	*cv=v;
}
//------------------------?????^??--------------------------------------------
void __fastcall TForm1::Colorr(Graphics::TBitmap *sbmp, Graphics::TBitmap *tbmp)
{
	Byte *sptr,*tptr;
	int w,h;
	int r,g,b;
	int hh,ss,vv;

	w=(sbmp->Width)*3;
	h=sbmp->Height;

	for(int y=0;y<h;y++)
	{
		sptr=(Byte *)sbmp->ScanLine[y];
		tptr=(Byte *)tbmp->ScanLine[y];
		for(int x=0;x<w;x+=3)
		{
			RGBToHSV(sptr[x+2], sptr[x+1], sptr[x], &hh,&ss,&vv);

			if(hh>=0 && hh<=60 && ss>=0 && ss<=255 && vv>=0 && vv<=255)
			{
				tptr[x]=sptr[x];
				tptr[x+1]=sptr[x+1];
				tptr[x+2]=sptr[x+2];
			}
			else
			{
				tptr[x]=BINARY_BACKGROUND;
				tptr[x+1]=BINARY_BACKGROUND;
				tptr[x+2]=BINARY_BACKGROUND;
			}
		}
	}
}
//------------------------?G???????p--------------------------------------------
void __fastcall TForm1::ToBinary_S(Graphics::TBitmap *sbmp,Graphics::TBitmap *tbmp,int th)
{
	Byte *s_ptr,*t_ptr;
	int r,g,b;
	int w,h;
	int gray;

	w=(sbmp->Width)*3;
	h=sbmp->Height;


	for (int y = 0; y < h; y++)
	{
		s_ptr=(Byte *)sbmp->ScanLine[y];
		t_ptr=(Byte *)tbmp->ScanLine[y];

		for(int x=0;x < w ; x+=3)
		{
			b=s_ptr[x];

			if(b<th)
			{
				t_ptr[x+2]=BINARY_FOREGROUND;
				t_ptr[x+1]=BINARY_FOREGROUND;
				t_ptr[x]=BINARY_FOREGROUND;
			}
			else
			{
				t_ptr[x+2]=BINARY_BACKGROUND;
				t_ptr[x+1]=BINARY_BACKGROUND;
				t_ptr[x]=BINARY_BACKGROUND;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::H_Projection(Graphics::TBitmap *bmp,int H[])
{
	 Byte *ptr;
	 int w;
	w=bmp->Width*3;

	for(int y=0;y<bmp->Height;y++)
	{
		ptr=(Byte *)bmp->ScanLine[y];

		for(int x=0;x<w;x+=3)
		{
			if(ptr[x]==0)
			H[y]++;
		}
	}
}
//--------------------------------------------------------------------
void __fastcall TForm1::DrawHProjection(int H[],TImage *img,int h,float scale)
{
	int c;
	img->Canvas->Pen->Color=clBlack;

	for(int i=0;i<h;i++)
	{
	c=(float)H[i]/scale;
	img->Canvas->MoveTo(img->Width-c,i);
	img->Canvas->LineTo(img->Width,i);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForm1::V_Projection(Graphics::TBitmap *bmp,int V[])
{
	Byte *ptr;
	int w,h;
	w=bmp->Width*3;
	h=bmp->Height;
	for(int y=0;y<h;y++)
	{
		ptr=(Byte *)bmp->ScanLine[y];

		for(int x=0;x<w;x+=3)
		{
			if(ptr[x]==0)
				V[x/3]++;
		}
	}
}
//--------------------------------------------------------------------
void __fastcall TForm1::DrawVProjection(int V[],TImage *img,int v,float scale)
{
	int c;
	img->Canvas->Pen->Color=clBlack;

	for(int i=0;i<v;i++)
	{
		c=(float)V[i]/scale;
		img->Canvas->MoveTo(i,img->Height-c);
		img->Canvas->LineTo(i,img->Height);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
	int a,b;
	Image1->Canvas->Pen->Color=clRed;

	a=Image1->Width/10;
	b=Image1->Height/10;

	for(int i=0;i<Image1->Width;i+=a)
	{
		Image1->Canvas->MoveTo(i,0);
		Image1->Canvas->LineTo(i,Image1->Height);
	}

	for(int i=0;i<Image1->Height;i+=b)
	{
		Image1->Canvas->MoveTo(0,i);
		Image1->Canvas->LineTo(Image1->Width,i);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	int a,b,v=7;

	re(Image1->Picture->Bitmap,Image1->Picture->Bitmap,v);
	Image1->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::re(Graphics::TBitmap *sbmp,Graphics::TBitmap *tbmp,int v)
{

	int w,h;
	Byte *s_ptr,*t_ptr;

	w=(sbmp->Width)*3;
	h=sbmp->Height;
	v=(Image1->Height/10)*v;

	for (int y = 0; y < h; y++)
	{
		s_ptr=(Byte *)sbmp->ScanLine[y];
		t_ptr=(Byte *)tbmp->ScanLine[y];

		for(int x=0;x < w ; x+=3)
		{
			if(y>=v)
			{
				t_ptr[x+2]=BINARY_BACKGROUND;
				t_ptr[x+1]=BINARY_BACKGROUND;
				t_ptr[x]=BINARY_BACKGROUND;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
	Byte *s_ptr;
	int w,h;

	w=(Image1->Width)*3;
	h=Image1->Height;

	for (int y = 0; y < h; y++)
	{
		s_ptr=(Byte *)Image1->Picture->Bitmap->ScanLine[y];

		for(int x=0;x < w ; x+=3)
		{
			if(s_ptr[x]==0&&s_ptr[x+1]==0&&s_ptr[x+2]==0)
			{
				if(x<=mi_x)
					mi_x=(x);
				if(x>=mx_x)
					mx_x=(x);
				if(y<=mi_y)
					mi_y=y;
				if(y>=mx_y)
					mx_y=y;
			}
		}
	}
	mx_x/=3;
	mi_x/=3;

	Image1->Canvas->Brush->Style=bsClear;
	Image1->Canvas->Pen->Color=clRed;
	Image1->Canvas->Rectangle(TRect(mx_x,mx_y,mi_x,mi_y));

	//ShowMessage(IntToStr(mx_x)+" "+IntToStr(mx_y)+" "+IntToStr(mi_x)+" "+IntToStr(mi_y));
}
//---------------------------------------------------------------------------
void TForm1::InitCC()
{
	//???w???X?v??
	CC.Initial(bmp2->Width,bmp2->Height,bmp2,20000);
	CC.SetRemovalSize(20);
	//???w?@???}???v??????
	CC.Connection(bmp1);
	//?i?H????????
	CC.ShowComponents();
}
//---------------------------------------------------------------------------
void TForm1::MorphoInitial()
{
	//???w?v?????e
	Morphy.Inital(bmp2->Width,bmp2->Height);
	//???w?n???}???????v??
	Morphy.AssignSource(bmp2);
	//???w???X???v??
	Morphy.AssignOutput(bmp3);
}
//---------------------------------------------------------------------------
void TForm1::FillBlack(Graphics::TBitmap *sbmp)
{
	Byte *ptr;
	int width;

	width=sbmp->Width*3;

	for(int y=0;y<sbmp->Height;y++)
	{
		ptr=(Byte *)sbmp->ScanLine[y];
		for(int x=0;x<width;x+=3)
		{
			if(ptr[x]!=255)
			{
				ptr[x]=0;
				ptr[x+1]=0;
				ptr[x+2]=0;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button10Click(TObject *Sender)
{
	bmp1=Image1->Picture->Bitmap;

	InitCC();
	MorphoInitial();	//???}?t???k???l??
	FillBlack(bmp2);      	//???I???H?~???C??,???????????~???i?????????}
	Morphy.Opening();  	//?i?????????}

    //?b?@???Q?? connect conpoment?i???h???T
	CC.Initial(bmp4->Width,bmp4->Height,bmp4,20000);
	CC.SetRemovalSize(70);
	CC.Connection(bmp3);
	CC.ShowComponents();
	FillBlack(bmp4);

	Image1->Picture->Bitmap=bmp4;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
	Byte *s_ptr;
	int w,h,a,b;

	w=(Image1->Width)*3;
	h=Image1->Height;
	a=Image1->Height/10;
	b=Image1->Width/10;

	for(int i=0;i<Image1->Height;i++)
	{
		if(i>=a*3&&i<=a*4)
		{
			if(hProjection[i]<m1)
			{
				m1=hProjection[i];
				y1=i;
			}
		}
		if(i>=a*5&&i<=a*6)
		{
			if(hProjection[i]<m2)
			{
				m2=hProjection[i];
				y2=i;
			}
		}
	}

	for(int i=0;i<Image1->Width;i++)
	{
		if(i>=b*3&&i<=b*5)
		{
			if(vProjection[i]<m3)
			{
				m3=vProjection[i];
				x1=i;
			}
		}

		if(i>=b*5&&i<=b*7)
		{
			if(vProjection[i]<m4)
			{
				m4=vProjection[i];
				x2=i;
			}
		}

		if(i>=b*4&&i<=b*6)
		{
			if(vProjection[i]<m5)
			{
				m5=vProjection[i];
				x3=i;
			}
		}
	}

	//(x1,y1)????  (x2,y1)?k??  (x3,y2)?L??
	Image1->Canvas->Pen->Color=clYellow;
   /*	Image1->Canvas->Rectangle(TRect(x1,y1+ey,x1-ex,y1-ey));
	Image1->Canvas->Rectangle(TRect(x2+ex,y1+ey,x2,y1-ey));
	Image1->Canvas->Rectangle(TRect(x3,y2+coy,x3-cox,y2-coy));
	*/
	Image1->Canvas->Rectangle(TRect(x1+ex,y1+ey,x1-ex,y1-ey));
	Image1->Canvas->Rectangle(TRect(x2+ex,y1+ey,x2-ex,y1-ey));
	//Image1->Canvas->Rectangle(TRect(x3+cox,y2+coy,x3-cox,y2-coy));
	Image1->Canvas->Rectangle(TRect((x1+x2)/2+cox,y2+coy,(x1+x2)/2-cox,y2-coy));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{
	ee(Bmp,Image1->Picture->Bitmap);
  	Image1->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ee(Graphics::TBitmap *sbmp,Graphics::TBitmap *tbmp)
{
	Byte *s_ptr,*t_ptr;
	int w,h;

	w=(sbmp->Width)*3;
	h=sbmp->Height;

	for (int y = 0; y<h;y++)
	{
		s_ptr=(Byte *)sbmp->ScanLine[y];
		t_ptr=(Byte *)tbmp->ScanLine[y];

		for(int x=0;x<w;x+=3)
		{
			if((x>=3*(x1-ex) && x<=3*(x1+ex) && y>=y1-ey && y<=y1+ey)||
				(x>=3*(x2-ex) && x<=3*(x2+ex) && y>=y1-ey && y<=y1+ey)||
				(x>=3*(x3-cox) && x<=3*(x3+cox) && y>=y2-coy && y<=y2+coy))
			{
				if(t_ptr[x]!=0)
				{
					t_ptr[x]=s_ptr[x];
					t_ptr[x+1]=s_ptr[x+1];
					t_ptr[x+2]=s_ptr[x+2];
				}
				else
				{
                 	t_ptr[x]=BINARY_BACKGROUND;
					t_ptr[x+1]=BINARY_BACKGROUND;
					t_ptr[x+2]=BINARY_BACKGROUND;
				}
			}
			else
			{
				t_ptr[x]=BINARY_BACKGROUND;
				t_ptr[x+1]=BINARY_BACKGROUND;
				t_ptr[x+2]=BINARY_BACKGROUND;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button11Click(TObject *Sender)
{
/*	Image1->Canvas->Pen->Color=clBlue;
	Image1->Canvas->Rectangle(TRect(105,47,104,245));  */
     Image1->Canvas->Pen->Color=clBlue;
	Image1->Canvas->MoveTo((x1+x2)/2,mi_y);
 	Image1->Canvas->LineTo((x1+x2)/2,mx_y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
	int v;
	v=ScrollBar1->Position;
	Label6->Caption=IntToStr(v);
	mih=v;
	Memo1->Lines->Add(IntToStr(mih));
	HSV(Bmp,Image1->Picture->Bitmap);
 	Image1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar2Change(TObject *Sender)
{
	int v;
	v=ScrollBar2->Position;
	Label7->Caption=IntToStr(v);
	mxh=v;
	Memo1->Lines->Add(IntToStr(mxh));
	HSV(Bmp,Image1->Picture->Bitmap);
	Image1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar3Change(TObject *Sender)
{
	int v;
	v=ScrollBar3->Position;
	Label8->Caption=IntToStr(v);
	mis=v;
	Memo1->Lines->Add(IntToStr(mis));
	HSV(Bmp,Image1->Picture->Bitmap);
	Image1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar4Change(TObject *Sender)
{
	int v;
	v=ScrollBar4->Position;
	Label9->Caption=IntToStr(v);
	mxs=v;
	Memo1->Lines->Add(IntToStr(mxs));
	HSV(Bmp,Image1->Picture->Bitmap);
	Image1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar5Change(TObject *Sender)
{
	int v;
	v=ScrollBar5->Position;
	Label10->Caption=IntToStr(v);
	miv=v;
	Memo1->Lines->Add(IntToStr(miv));
	HSV(Bmp,Image1->Picture->Bitmap);
	Image1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar6Change(TObject *Sender)
{
	int v;
	v=ScrollBar6->Position;
	Label11->Caption=IntToStr(v);
	mxv=v;
	Memo1->Lines->Add(IntToStr(mxv));
	HSV(Bmp,Image1->Picture->Bitmap);
	Image1->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::HSV(Graphics::TBitmap *sbmp,Graphics::TBitmap *tbmp)
{
	Byte *s_ptr,*t_ptr;
	int r,g,b;
	int w,h;
	int hh,ss,vv;

	w=(sbmp->Width)*3;
	h=sbmp->Height;

	for (int y = 0; y < h; y++)
	{
		s_ptr=(Byte *)sbmp->ScanLine[y];
		t_ptr=(Byte *)tbmp->ScanLine[y];

		for(int x=0;x < w ; x+=3)
		{
			RGBToHSV(s_ptr[x+2], s_ptr[x+1], s_ptr[x], &hh,&ss,&vv);

			if(hh>=mih&&hh<=mxh&&ss>=mis&& ss<=mxs&&vv>=miv&&vv<=mxv)
			{
				t_ptr[x+2]=s_ptr[x+2];
				t_ptr[x+1]=s_ptr[x+1];
				t_ptr[x]=s_ptr[x];
			}
			else
			{
				t_ptr[x+2]=255;
				t_ptr[x+1]=255;
				t_ptr[x]=255;
			}
		}
	}
}
