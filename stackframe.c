/*
 * 工学基礎シリーズ オペレーティングシステム (オーム社)
 *
 * スタックフレームの確認用プログラム (p.26)
 * 図2.3は，このファイルを Windows WSL 2 上の Ubuntu 20.04 LTS 上で gcc (version 9.4.0) を使用し，
 * 以下のコマンドラインを使ってコンパイルして得られた実行ファイルを gdb で逆アセンブルしたもの．
 * gcc stackframe.c -Wa,-adhln -static -g -Og -fno-stack-protector -mno-shstk -fcf-protection=none -fno-asynchronous-unwind-tables -fno-mudflap -fno-inline -fno-toplevel-reorder -D_FORTIFY_SOURCE=0
 */
#include <stdio.h>

/* プロトタイプ宣言 */
long t(long a, long b, long c, long d, long e,
       long f, long g, long h, long i, long j);
void u(long *p);

int main(int argc, char *argv[])
{
  long ret = t(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  printf("ret=%ld\n", ret);
  return 0;
}

long t(long a, long b, long c, long d, long e,
       long f, long g, long h, long i, long j)
{
  long x[4];
  x[0] = a + b + c + d + e + f + g + h + i + j;
  u(x);
  return x[0];
}

void u(long *p)
{
  long y = *p;
  long z = y;
  printf("%p, %p\n", &y, &z);
}
