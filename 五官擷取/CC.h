//===========================================================================
//          Binary Image Connected Components      2006/07/03
//                            Cite from:
//   "A simple and efficient connected components labeling algorithm"
//   Di Stefano, L.; Bulgarelli, A.; Image Analysis and Processing, 1999.
//   Proceedings. International Conference on 27-29 Sept. 1999 Page(s):322 - 327
//===========================================================================

//---------------------------------------------------------------------------
//  This program is only used for C++ Builder 6.0 enviornment,
//  the images of input and output are 24 bits of bi-color in which only
//  containing black 0 and white 255 two colors.
//---------------------------------------------------------------------------
#ifndef CC1H
#define CC1H

#define BACKGROUND_COLOR 255    //�I���⪺�w�]��
#define FOREGROUND_COLOR 0      //�e���⪺�w�]��
#define MAX_LABEL_LIMIT 30000   //���\�@�i�v������label���̤j�ƶq, �Фť��N���.
                                //�Y�n���,�ݷf�t��� LabelMatrix, ConnectSet,
                                //Buf, F �o���ܼƪ���ƫ��A, �H�ά�����functions.
#define DEFAULT_MAX_LABEL 1000  //�w�]�@�i�v�����̦h�i�]�t��label�ƥ�, ���o�j��
                                //MAX_LABEL_LIMIT
#define REMOVAL_SIZE 0          //�w�]�����T�j�p=0, �Y���B�z���T.
#define MAX_X 9999999
#define MAX_Y 9999999
//---------------------------------------------------------------------------
#include <vcl.h>

typedef struct _COO{
        int x1,x2,y1,y2;
        }COO;

//---------------------------------------------------------------------------
class ConntdCompnt
{
private:
        int NewLabel; // ���V�ثe�s�W��label�s��, �Ycomponent���`��
        int Width, Height,TotalWidth; //�v�����e�P��, TotalWidth=Width*3 (R,G,B�T��chennels)
        int MaxLabel;      //�@�i�v�����̦h�i�]�t��label�ƥ�,�i�� ConntdCompnt(),
                           //�� Initial()�]�w. �е����p�ӳ]�w, ���ȶV�j�|���O�O����Ŷ�,
                           //�Ω�C���檺�t��.
        int up,left,lx;
        int RemovalSize;   // ���T���j�p, �i��SetRemovalSize()�]�w.
        int x,y,x1,i,j,k,y1;
        BYTE *ptr,*Upptr;
        Graphics::TBitmap *Show; // ���V����X���G���v��������, �i��SetShow()�]�w.
        int **LabelMatrix;  // �x�s�v����labels. label���s�����@�w�����ǩ�
        int *ConnectSet;   //�x�s�C�ӧ�쪺label��size�A���i��Y��label��size=0
        unsigned char **Buf;
        char *F;
        COO *CompntPos; //�Ψ��x�s�C�Ӥ��󪺮y��
        int CompntNum;

        bool AllocateLabelMatrix();
        inline void FirstScan(Graphics::TBitmap *);
        inline void SecondScan();
        void DeleteConnectSet();
        void DeleteMatrix();
        void DeleteBuf();
        inline void DeleteCompntPos();
        bool SetMaxLabel(int);
        bool AllocateSet();
        bool AllocateBuf();
        inline bool AllocateCompntPos();
        inline void InitialSet();
        inline void InitialMatrix();
        inline void InitialBuf(Graphics::TBitmap*);
        inline void LabelIgnoredComponents();

public:
        unsigned char ERRORMSG;
        // ERROTMSG: 1: allocate label matrix failure.
        //

        ConntdCompnt();
        ConntdCompnt(int , int, int ,int); //�ǤJ: �v���e, �v����, �̤j��label�ƥ�, ���T��size.
        ~ConntdCompnt();
        bool Initial(int,int,Graphics::TBitmap *,int); // ��l��, �ǤJ: �v���e, �v����, ��X�v��������, �̤j��label�ƥ�.
        void Connection(Graphics::TBitmap *);  //�I�sConnected Components�{�Ƕi��B�z,
                                               //�w�Q�B�z���v������.
        int **GetLabelMatrix(){ return LabelMatrix; }; //�Ǧ^Label table���}�C����.
        void SetShow(Graphics::TBitmap *); // �f�tShowComponents�ϥ�.
        void ShowComponents();     //�H�H�����C����ܨC�@��components, ����
                                   // �HSetShow()�]�w����X���e��������.
        void SetRemovalSize(int);  // �]�w�����������T��size(�Hpixels�����).
                                   //�ä��v�T label table�}�C�����e, �u�v�T��X���v��. �w�]�Ȭ����B�z���T.
        int FindMaxCompnt(int *, int *, int *, int *, int *); //��X�̤j��component�A�Ǧ^size�ήy��
        int GetCompntNum(bool); //�Ǧ^object���ƶq�C �Ѽ�=1��ܩ������n�p��]�w���A�h����
        int *GetConnectSet(){ return ConnectSet; };
        int GetLabels(){ return NewLabel; };
        COO *GetCompntPos();  //�`�N�G�������ϥ�GetCompntNum()��X���󪺼ƶq

};

//---------------------------------------------------------------------------

#endif
 