#ifndef __FFT_H__
#define __FFT_H__


typedef struct    //����һ�������ṹ��
{
  float real;
  float imag;
}compx;
void BubbleSort(float pt[], int Cnt);
void FFT(compx *xin, int Num);
void IFFT(compx *xin, int Num);

#endif      














