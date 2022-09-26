/*
 * 工学基礎シリーズ オペレーティングシステム (オーム社)
 * (3.3.3)
 *
 * セマフォを用いた生産者／消費者問題のプログラム (pp.76)
 * p.76では擬似コードで示しているが，ここではC言語(Pthread)で記述している．
 * POSIXに準拠したUnix系OSで動作する．
 *
 * コンパイル方法:
 * - Linux: cc prod-cons-semaphore.c -lpthread -o prod-cons-semaphore
 * - macOS: cc prod-cons-semaphore.c -o prod-cons-semaphore
 */
#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <semaphore.h>
#include <stdlib.h>

#define N 10    // バッファのサイズ
int buf[N];     // バッファ
int wind = 0;   // 生産者が次に書き込むインデックス
int rind = 0;   // 消費者が次に読み込むインデックス
int wdata = 0;  // 書き込むデータ(1づつ増やす)

// セマフォの名前 (ここでは名前付きセマフォを使う)
#define SEM_LOCK "/prod-cons-lock"
#define SEM_FULL "/prod-cons-full"
#define SEM_EMPTY "/prod-cons-empty"

// バッファを排他制御するためのセマフォ
sem_t *lock;
// バッファ中のデータ数を保持するセマフォ
sem_t *full;
// バッファの空きの数を保持するセマフォ
sem_t *empty;

void producer() { // 生産者スレッド
  while (1) {
    sem_wait(empty); // バッファが空くのを待つ
    sem_wait(lock);  // バッファの排他制御
    // バッファにデータを書き込む
    buf[wind] = wdata;
    wind = (wind + 1) % N; // 書き込みインデックスを次に進める
    printf("producer: write %d\n", wdata);
    wdata++;
    sem_post(lock);
    sem_post(full);  // バッファのデータ数を+1
  }
}

void consumer() { // 消費者スレッド
  while (1) {
    sem_wait(full); // データが書き込まれるのを待つ．
    sem_wait(lock); // バッファの排他制御
    //バッファからデータを取り出す
    int rdata = buf[rind];
    rind = (rind + 1) % N; // 読み込みインデックスを次に進める
    printf("consumer: read %d\n", rdata);
    sem_post(lock);
    sem_post(empty); // バッファの空きの数を+1
  }
}

extern int main(int argc, char **argv) {
  // セマフォが残っていると正常に動作しないので削除しておく
  sem_unlink(SEM_LOCK);
  sem_unlink(SEM_FULL);
  sem_unlink(SEM_EMPTY);
  // 名前付きセマフォを生成
  lock = sem_open(SEM_LOCK, O_CREAT, 0777, 1);
  full = sem_open(SEM_FULL, O_CREAT, 0777, 0);
  empty = sem_open(SEM_EMPTY, O_CREAT, 0777, N);
  if (lock == SEM_FAILED || full == SEM_FAILED || empty == SEM_FAILED) {
    perror("sem_open failed");
    exit(1);
  }
  pthread_t prod_thread, cons_thread;
  pthread_create(&prod_thread, NULL, (void*(*)(void*))producer, NULL); // 生産者スレッド開始
  pthread_create(&cons_thread, NULL, (void*(*)(void*))consumer, NULL); // 消費者スレッド開始
  pthread_join(prod_thread, NULL); // 生産者の終了を待つ(実際は終わらないので永遠に待つ)
  // 以下のコードは実際には実行されない
  sem_unlink(SEM_LOCK);
  sem_unlink(SEM_FULL);
  sem_unlink(SEM_EMPTY);
  return 0;
}
