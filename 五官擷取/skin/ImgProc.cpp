//---------------------------------------------------------------------------
#pragma hdrstop

#include "ImgProc.h"

int min(int a,int b)
{
   if(a>=b)
	return b;
   else
	return a;
}
int max(int a,int b)
{
   if(a>=b)
	return a;
   else
	return b;
}
int X11,X22,Y11,Y22;
//---------------------------------------------------------------------------
#pragma package(smart_init)
Graphics::TBitmap*LoadImage(AnsiString Str)
{
   AnsiString ext;
   Graphics::TBitmap*Pic;

   TJPEGImage*Jpeg=new TJPEGImage;

   Pic=new Graphics::TBitmap;
   ext=ExtractFileExt(Str);
   ext=ext.LowerCase();

   if(ext==".bmp")
   {
	  Pic->LoadFromFile(Str);
   }
   else  //jpg
   {
	  Jpeg->LoadFromFile(Str);
	  Pic->Assign(Jpeg);
	  delete Jpeg;
   }
   return Pic;
}
void GetRGB(Graphics::TBitmap *bmp, int x, int y ,int *r ,int *g ,int *b )
{
	Byte *ptr;

	ptr=(Byte *)bmp->ScanLine[y];
	int x1;

	x1=(x<<1)+x;
	*r=ptr[x1+2];
	*g=ptr[x1+1];
	*b=ptr[x1];
}
//---------------------------------------------------------------------------
void ToGray(Graphics::TBitmap *Source,Graphics::TBitmap *Target)
{
	Byte *s_ptr,*t_ptr;
	int r,g,b;
	int width,height;
	int gray;

	width=Source->Width*3;
	height=Source->Height;

	for(int y=0;y<height;y++)
	{
		s_ptr=(Byte *)Source->ScanLine[y];
		t_ptr=(Byte *)Target->ScanLine[y];

		for(int x=0;x<width;x+=3)
		{
			r=s_ptr[x+2];
			g=s_ptr[x+1];
			b=s_ptr[x];

			gray=b*0.114+g*0.587+r*0.299;

			t_ptr[x+2]=gray;
			t_ptr[x+1]=gray;
			t_ptr[x]=gray;
		}

	}
}
void RGBToHSV(int r, int g, int b, int *ch, int *cs, int *cv)
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
void ToBinary_B(Graphics::TBitmap *Source,Graphics::TBitmap *Target,int th)
{
	Byte *s_ptr,*t_ptr;
	int b;                //rgb因為二值化無論取哪個都可以算所以省時間只用一個
	int width,height;

	width=Source->Width*3;
	height=Source->Height;

	for(int y=0;y<height;y++)
	{
		s_ptr=(Byte *)Source->ScanLine[y];
		t_ptr=(Byte *)Target->ScanLine[y];

		for(int x=0;x<width;x+=3)
		{
			b=s_ptr[x];

			if(b<=th)
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
int compare(const void *a,const void *b)
{
	int aa=*( int *)a;
	int bb=*( int *)b;

	if(aa<bb)
		return -1;
	if(aa>bb)
		return 1;
	else
		return 0;
}
void Ddifferenc(Graphics::TBitmap *Source1,Graphics::TBitmap *Source2,Graphics::TBitmap *Target)
{
	Byte *sptr1,*sptr2,*tptr;
	int dif;
	int v=55;

	int width1,height1,width2,height2;

	width1=Source1->Width*3;
	height1=Source1->Height;

	width2=Source2->Width*3;
	height2=Source2->Height;

	if(width1!=width2||height1!=height2)
	{
		ShowMessage("圖片不符合");
		return;
	}

	for(int y=0;y<height1;y++)
	{
		sptr1=(Byte *)Source1->ScanLine[y];
		sptr2=(Byte *)Source2->ScanLine[y];
		tptr=(Byte *)Target->ScanLine[y];

		for(int x=0;x<width1;x++)
		{
				dif=sptr1[x]-sptr2[x];

			if(dif<v&&dif>-v)
			{
				tptr[x]=255;
			}
			else
			{
				tptr[x]=0;
			}
		}
	}
}
void H_projection(Graphics::TBitmap *Bmp,int H[])
{
   Byte *ptr;
   int width;

   width=Bmp->Width*3;

   for(int y=0;y<Bmp->Height;y++)
	{
		ptr=(Byte *)Bmp->ScanLine[y];

		for(int x=0;x<width;x+=3)
		{
		   if(ptr[x]==0)
				H[y]++;
		}
	}
}
void DrawHProjection(int H[],TImage *Img,int Height ,float scale)
{
	int Count;

	Img->Canvas->Pen->Color=clBlack;

	for(int i=0;i<Height;i++)
	{
	   Count=(float)H[i]/scale;
	   Img->Canvas->MoveTo(Img->Width-Count,i);
	   Img->Canvas->LineTo(Img->Width,i);
	}
}
void S_projection(Graphics::TBitmap *Bmp,int H[])
{
   Byte *ptr;
 int w,h;
 w=Bmp->Width*3;
 h=Bmp->Height;
 for(int y=0;y<h;y++)
 {
  ptr=(Byte *)Bmp->ScanLine[y];

  for(int x=0;x<w;x+=3)
  {
	  if(ptr[x]==0)
		H[x/3]++;
  }

 }
}
void DrawSProjection(int H[],TImage *Img,int width ,float scale)
{
	int c;
	Img->Canvas->Pen->Color=clBlack;

 for(int i=0;i<width;i++)
 {
   c=(float)H[i]/scale;
   Img->Canvas->MoveTo(i,Img->Height-c);
   Img->Canvas->LineTo(i,Img->Height);
 }

}
void SobelFilter(Graphics::TBitmap *Source, Graphics::TBitmap *Target)
{
  int Mask1[9] = { -1.0 , 0.0 ,  1.0 ,
                   -2.0 , 0.0 ,  2.0 ,
                   -1.0 , 0.0 ,  1.0
                 }; // detect the horizontal edges
  int Mask2[9] = {  1.0 , 2.0 , 1.0 ,
                    0.0 , 0.0 , 0.0 ,
                   -1.0 ,-2.0 ,-1.0
                 }; // detect the vertical edges

  Converlution2Times(Source,Target,Mask1,Mask2,4);

}
//---------------------------------------------------------------------------
void Converlution2Times(Graphics::TBitmap *Source,Graphics::TBitmap *Target,
                        int *Mask1, int *Mask2,int factor)
{
  int value;
  int height,width;
  Byte *spt0,*tptr,*spt1,*spt2;

  width=(Source->Width-2)*3;
  height=Source->Height-2;

   for(int y=0;y<height;y++)
     {
        spt0 = (Byte *)Source->ScanLine[y];
        spt1 = (Byte *)Source->ScanLine[y+1];
        spt2 = (Byte *)Source->ScanLine[y+2];
        tptr = (Byte *)Target->ScanLine[y+1];
        for(int x=0;x<width;x+=3)
          {
            value=abs(spt0[x]*Mask1[0]+spt0[x+3]*Mask1[1]+spt0[x+6]*Mask1[2]+
                      spt1[x]*Mask1[3]+spt1[x+3]*Mask1[4]+spt1[x+6]*Mask1[5]+
                      spt2[x]*Mask1[6]+spt2[x+3]*Mask1[7]+spt2[x+6]*Mask1[8]);

            value/=factor;

            tptr[x+3]=value;
            tptr[x+4]=value;
            tptr[x+5]=value;
          }
     }
 //-----------------------------------------------------------------
   for(int y=0;y<height;y++)
     {
          spt0 = (Byte *)Source->ScanLine[y];
          spt1 = (Byte *)Source->ScanLine[y+1];
          spt2 = (Byte *)Source->ScanLine[y+2];
          tptr = (Byte *)Target->ScanLine[y+1];

          for(int x=0;x<width;x+=3)
            {
               value=abs(spt0[x]*Mask2[0]+spt0[x+3]*Mask2[1]+spt0[x+6]*Mask2[2]+
                         spt1[x]*Mask2[3]+spt1[x+3]*Mask2[4]+spt1[x+6]*Mask2[5]+
                         spt2[x]*Mask2[6]+spt2[x+3]*Mask2[7]+spt2[x+6]*Mask2[8]);

               value/=factor;

               // 新的程式碼： 白色為背景
               if(tptr[x+3]+value>255)
                 {
                   tptr[x+3]=BINARY_FOREGROUND;
                   tptr[x+4]=BINARY_FOREGROUND;
                   tptr[x+5]=BINARY_FOREGROUND;
                 }

               if(tptr[x+3]+value<0)
                 {
                   tptr[x+3]=BINARY_BACKGROUND;
                   tptr[x+4]=BINARY_BACKGROUND;
                   tptr[x+5]=BINARY_BACKGROUND;
                 }
               else
                 {
                   tptr[x+3]+=value;
                   tptr[x+4]+=value;
                   tptr[x+5]+=value;

                   tptr[x+3]=255-tptr[x+3];
                   tptr[x+4]=255-tptr[x+4];
                   tptr[x+5]=255-tptr[x+5];
                 }


            }
     }

}
void Skin(Graphics::TBitmap *Source,Graphics::TBitmap *Target)
{
	Byte *s_ptr,*t_ptr;
	int x1,r,g,b;
	float temp,mi,delta;
	float h,s,v,width,height;

	width=Source->Width*3;
	height=Source->Height;

	for(int y=0;y<height;y++)
	{
		s_ptr=(Byte *)Source->ScanLine[y];
		t_ptr=(Byte *)Target->ScanLine[y];

		for(int x=0;x<width;x+=3)
		{
			r=s_ptr[x+2];
			g=s_ptr[x+1];
			b=s_ptr[x];

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

			v=255.0;

			if(h>=20 &&h<=40 &&s>=0 &&s<=255 && v>=0 &&v<=255)
			{
				t_ptr[x+2]=r;
				t_ptr[x+1]=g;
				t_ptr[x]=b;
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
void search(Graphics::TBitmap *Source,Graphics::TBitmap *Target)
{
     Byte *s_ptr,*t_ptr;
	int x1;
	float width,height,t=0;

	width=Source->Width*3;
	height=Source->Height;

	for(int y=0;y<height;y++)
	{
		s_ptr=(Byte *)Source->ScanLine[y];
		t_ptr=(Byte *)Target->ScanLine[y];

		for(int x=0;x<width;x+=3)
		{
			x1=s_ptr[x];
			if(x1!=255 && t==0)
			{
			   X11=x1;
			   t++;
			}

		}
	}

}

