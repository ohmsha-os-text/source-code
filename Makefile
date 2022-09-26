#
# Makefile
#
# GNU make 用です．make -v を実行して GNU Make と表示されればOKです．
# デフォルトではC言語のプログラムのみをコンパイルします．
# Java言語のプログラムもコンパイルする場合は，make COMPILE_JAVA=1 のようにします．
#
OS = $(shell uname -s)
ARCH = $(shell uname -m)
CC = cc
GCC = gcc
CFLAGS = -Wall
COMPILE_JAVA = 0

ifeq ($(OS),Linux)
	LDLIBS+=-lpthread
endif

TARGET = stackframe \
	pthread-sample \
	prod-cons-semaphore \
	prod-cons-mutex \
	deadlock \
	exercise3-3
ifeq ($(COMPILE_JAVA),1)
	TARGET += ProducerConsumer.class
endif

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o stackframe.dSYM

# stackframe.c は gcc でなるべく単純な機械語が得られるようなオプションを
# 指定してコンパイルする．
LISTING_FILE = stackframe.lst
STK_GCC_CFLAGS = -g -Og -fno-inline 
ifeq ($(ARCH),x86_64)
	# x86_64用gccのオプション
	STK_GCC_CFLAGS += -fno-toplevel-reorder -fno-stack-protector \
	-mno-shstk -fcf-protection=none \
	-fno-asynchronous-unwind-tables -fno-mudflap
endif
ifeq ($(OS),Linux)
	STK_GCC_CFLAGS += -static -Wa,-adhln=$(LISTING_FILE) -D_FORTIFY_SOURCE=0
endif

stackframe: CFLAGS=$(STK_GCC_CFLAGS)
stackframe: stackframe.c
	$(GCC) stackframe.c -o $@ $(CFLAGS) $(LDLIBS)

# Java
ProducerConsumer.class: ProducerConsumer.java
	javac $<
