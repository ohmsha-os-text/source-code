/*
 * 工学基礎シリーズ オペレーティングシステム (オーム社)
 * (3.3.5)
 *
 * Javaによる生産者・消費者問題のプログラム (p.81)
 * コンパイル:
 * - javac ProducerConsumer.java
 * 実行:
 * - java ProducerConsumer
 */
public class ProducerConsumer {
  final int N = 10;
  int[] buf = new int[N]; // リングバッファ
  int nitems = 0; // バッファ内のデータ数
  int wind = 0;   // 生産者が次に書き込むインデックス
  int rind = 0;   // 消費者が次に読み込むインデックス
  int wdata = 0;  // 書き込むデータ(1づつ増やす)

  synchronized void producer() {
    while (true) {
      while (nitems == N) { // バッファに空きがない間…
        try {
          this.wait(); // このインスタンスの条件変数で待つ．
        } catch (InterruptedException e) {}
      }
      // バッファにデータを書き込む
      buf[wind] = wdata;
      wind = (wind + 1) % N; // 書き込みインデックスを次に進める
      nitems++;
      System.out.printf("producer: write %d, nitems %d%n", wdata, nitems);
      wdata++;
      this.notify(); // バッファが空ではないことを条件変数で通知
    }
  }

  synchronized void consumer() {
    while (true) {
      while (nitems == 0) { // バッファが空の間…
        try {
          this.wait(); // このインスタンスの条件変数で待つ．
        } catch (InterruptedException e) {}
      }
      // バッファからデータを取り出す
      int rdata = buf[rind];
      rind = (rind + 1) % N; // 読み込みインデックスを次に進める
      nitems--;
      System.out.printf("consumer: read %d, nitems %d%n", rdata, nitems);
      this.notify(); // バッファに空きがあることを条件変数で通知
    }
  }

  public static void main(String[] args) throws InterruptedException {
    ProducerConsumer instance = new ProducerConsumer();
    new Thread(() -> instance.producer()).start(); // 生産者スレッド開始
    new Thread(() -> instance.consumer()).start(); // 消費者スレッド開始
  }
}
