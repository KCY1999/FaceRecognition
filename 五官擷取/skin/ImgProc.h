//---------------------------------------------------------------------------

#ifndef ImgProcH
#define ImgProcH
#include <vcl.h>
#include <jpeg.hpp>
#include <algorithm>

#define BINARY_FOREGROUND 0
#define BINARY_BACKGROUND 255

 Graphics::TBitmap*LoadImage(AnsiString);
 void GetRGB(Graphics::TBitmap *bmp,int,int, int * ,int * ,int * );
 void ToGray(Graphics::TBitmap *Source,Graphics::TBitmap *Target);
 void RGBToHSV(int , int , int , int *, int *, int *);
 void ToBinary_B(Graphics::TBitmap*,Graphics::TBitmap*,int);
 int compare(const void *a,const void *b);
 void Ddifferenc(Graphics::TBitmap *,Graphics::TBitmap *,Graphics::TBitmap *);
 void H_projection(Graphics::TBitmap *,int []);
 void DrawHProjection(int [],TImage *Img,int ,float);
 void S_projection(Graphics::TBitmap *,int []);
 void DrawSProjection(int [],TImage *Img,int ,float);
 void SobelFilter(Graphics::TBitmap *, Graphics::TBitmap *);
 void Converlution2Times(Graphics::TBitmap *,Graphics::TBitmap *,int *,int *,int);
 void Skin(Graphics::TBitmap *Source,Graphics::TBitmap *Target);
 void search(Graphics::TBitmap *Source,Graphics::TBitmap *Target);
 //---------------------------------------------------------------------------
#endif
