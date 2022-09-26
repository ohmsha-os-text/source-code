/*
 * 工学基礎シリーズ オペレーティングシステム (オーム社)
 * (3.3.6)
 *  
 * デッドロックが発生するプログラム例 (p.82)
 * コンパイル方法:
 * - Linux: cc deadlock.c -lpthread -o deadlock
 * - macOS: cc deadlock.c -o deadlock
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void func1() {
  while (1) {
    pthread_mutex_lock(&m1);
    pthread_mutex_lock(&m2);
    printf("func1 %d\n", count++);
    pthread_mutex_unlock(&m2);
    pthread_mutex_unlock(&m1);
  }
}

void func2() {
  while (1) {
    pthread_mutex_lock(&m2);
    pthread_mutex_lock(&m1);
    printf("func2 %d\n", count++);
    pthread_mutex_unlock(&m1);
    pthread_mutex_unlock(&m2);
  }
}

extern int main(int argc, char **argv)
{
  pthread_t t1, t2;
  pthread_create(&t1, NULL, (void*(*)(void*))func1, NULL);
  pthread_create(&t2, NULL, (void*(*)(void*))func2, NULL);
  pthread_join(t1, NULL);
}
