[工学基礎シリーズ オペレーティングシステム（オーム社）](https://www.ohmsha.co.jp/book/9784274229152/) に掲載しているプログラムのソースコードです．

教科書では擬似コードで示しているコードも，ここでは実際に動作するコードを示しています．

Linux や macOS などのUnix系OSで動作します．
Windows では WSL2 などを使って Linux 環境を作って実行して下さい．

動作確認は macOS 12.5.1 および WSL2 上の Linux (Ubuntu 20.04 LTS) で行っています．

コンパイルするための Makefile を用意しておきました．
Makefile は GNU make の書式で書いてあります．
ターミナルから `make -v` を実行して GNU Make と表示されればOKです．

デフォルトではC言語のプログラムのみをコンパイルします．
Java言語のプログラムもコンパイルする場合は，`make COMPILE_JAVA=1` のようにして下さい
（Javaコンパイラ(`javac`)がインストールされている必要があります）．

Cコンパイラ，Javaコンパイラ，makeコマンドのインストール方法についてはネット上の記事などを参照して下さい．

# 2章
## stackframe.c
p.26 スタックフレームの確認用プログラム.  
Makefile では gcc (GNUのCコンパイラ) を使って，図2.3を出力する際に用いたオプションでコンパイルするようになっています．

# 3章
## pthread-sample.c
p.55 Pthreadによるマルチスレッドプログラムの例.

## prod-cons-semaphore.c
p.76 セマフォを用いた生産者／消費者問題のプログラム.

## prod-cons-mutex.c
pp.79-80 mutexと条件変数を用いた生産者／消費者問題のプログラム.
## ProducerConsumer.java
p.81 Java言語による生産者・消費者問題のプログラム.
## deadlock.c
p.82 デッドロックが発生するプログラム例.
## exercise3-3.c
p.85 演習問題3のプログラム.
