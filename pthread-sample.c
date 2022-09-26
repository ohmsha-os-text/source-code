/*
 * 工学基礎シリーズ オペレーティングシステム (オーム社)
 * (3.1.9)
 *
 * Pthreadによるマルチスレッドプログラムのサンプル (p.55)
 * コンパイル方法:
 * - Linux: cc pthread.c -lpthread -o pthread
 * - macOS: cc pthread.c -o pthread
 */
// マルチスレッドプログラムのサンプル
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// スレッドとして実行する関数の定義
static char *thread_func(void *arg)
{
  printf("sub: sleep 1sec\n");
  sleep(1); /* sleep for 1sec. */
  printf("sub: done\n");
  return "bye!";
}

extern int main(int argc, char **argv)
{
  pthread_t th;
  printf("main: creating a thread\n");
  // thread_funcから実行開始するスレッドを生成する．引数はNULL．
  int rc = pthread_create(&th, NULL, (void*(*)(void*))&thread_func, NULL);
  if (rc) {
    perror("pthread_create");
    exit(1);
  }
  printf("main: waiting for its termination...\n");
  char *val;
  // 生成したスレッドが終了するのを待機し，戻り値をvalに受け取る．
  rc = pthread_join(th, (void**)&val);
  if (rc) {
    perror("pthread_join");
    exit(1);
  }
  printf("main: finished (%s)\n", val);
}
