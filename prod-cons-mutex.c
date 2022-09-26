/*
 * 工学基礎シリーズ オペレーティングシステム (オーム社)
 * (3.3.4)
 *
 * mutexと条件変数を用いた生産者／消費者問題のプログラム (pp.79-80)
 * p.79では擬似コードで示しているが，ここではC言語(Pthread)で記述している．
 *
 * コンパイル方法:
 * - Linux: cc producer-consumer.c -lpthread -o producer-consumer
 * - macOS: cc producer-consumer.c -o producer-consumer
 */
#include <stdio.h>
#include <pthread.h>

#define N 10    // バッファのサイズ
int buf[N];     // バッファ
int nitems = 0; // バッファ内のデータ数
int wind = 0;   // 生産者が次に書き込むインデックス
int rind = 0;   // 消費者が次に読み込むインデックス
int wdata = 0;  // 書き込むデータ(1づつ増やす)

// 共有データ（バッファとnitems）を排他制御するためのmutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
// バッファに空きがあることを通知するための条件変数
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
// バッファが空ではないことを通知するための条件変数
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void producer() { // 生産者
  while (1) {
    pthread_mutex_lock(&lock); // 排他制御
    while (nitems == N) { // バッファに空きがない間…
       pthread_cond_wait(&not_full, &lock); // 空きができるまで待つ．
    }
    // バッファにデータを書き込む
    buf[wind] = wdata;
    wind = (wind + 1) % N; // 書き込みインデックスを次に進める
    nitems++;
    printf("producer: write %d, nitems %d\n", wdata, nitems);
    wdata++;
    pthread_cond_signal(&not_empty); // バッファが空ではないことを条件変数で通知
    pthread_mutex_unlock(&lock);
  }
}

void consumer() { // 消費者
  while (1) {
    pthread_mutex_lock(&lock); // 排他制御
    while (nitems == 0) { // バッファが空の間…
      pthread_cond_wait(&not_empty, &lock); // 空ではなくなるまで待つ．
    }
    //バッファからデータを取り出す
    int rdata = buf[rind];
    rind = (rind + 1) % N; // 読み込みインデックスを次に進める
    nitems--;
    printf("consumer: read %d, nitems %d\n", rdata, nitems);
    pthread_cond_signal(&not_full); // バッファに空きがあることを条件変数で通知
    pthread_mutex_unlock(&lock);
  }
}

extern int main(int argc, char **argv) {
  pthread_t prod_thread, cons_thread;
  pthread_create(&prod_thread, NULL, (void*(*)(void*))producer, NULL); // 生産者スレッド開始
  pthread_create(&cons_thread, NULL, (void*(*)(void*))consumer, NULL); // 消費者スレッド開始
  pthread_join(prod_thread, NULL); // 生産者の終了を待つ(実際は終わらないので永遠に待つ)
  return 0;
}
