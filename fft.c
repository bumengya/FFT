#include "math.h"
#include "fft.h"

#include <math.h>
#include <stdio.h>

compx EE(compx a,compx b) {
    compx result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

void FFT(compx *xin, int Num) {
    int f, m, LH, nm, i, k, j, L;
    double p, ps;
    int le, B, ip;
    const double PI = M_PI;
//    const double PI = 3.141592653589793;
    compx w, t;

    LH = Num / 2; 
    f = Num;
    for (m = 1; (f = f / 2) != 1; m++);

    for (L = m; L >= 1; L--) {
        le = 1 << L;
        B = le / 2;

        for (j = 0; j <= B - 1; j++) {
            ps = 2 * PI * j / le;
            w.real = cos(ps);
            w.imag = -sin(ps);

            for (i = j; i < Num; i += le) {
                ip = i + B;
                t = xin[i];
                xin[i].real = xin[i].real + xin[ip].real;
                xin[i].imag = xin[i].imag + xin[ip].imag;
                xin[ip].real = t.real - xin[ip].real;
                xin[ip].imag = t.imag - xin[ip].imag;
                xin[ip] = EE(xin[ip], w);
            }
        }
    }

    // 变址运算
    for (i = 0; i < Num; i++) {
        j = 0;
        for (k = 0; k < m; k++) {
            if (i & (1 << k)) {
                j |= (1 << (m - 1 - k));
            }
        }
        if (i < j) {
            t = xin[j];
            xin[j] = xin[i];
            xin[i] = t;
        }
    }
}



void IFFT(compx *xin, int Num) {
    int i;

    // 1. 对 FFT 权重取共轭，即将虚部取反
    for (i = 0; i < Num; i++) {
        xin[i].imag = -xin[i].imag;
    }

    // 2. 调用 FFT 函数
    FFT(xin, Num);

    // 3. 再次对结果虚部取反，并将所有结果除以序列长度 Num
    for (i = 0; i < Num; i++) {
        xin[i].real /= Num;
        xin[i].imag = -xin[i].imag / Num;
    }
}
