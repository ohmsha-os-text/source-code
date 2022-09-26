/*
 * 工学基礎シリーズ オペレーティングシステム (オーム社)
 * (3章 演習問題3)
 */
#include <stdio.h>

int global = 10;
int not_init;

int main(int argc, char **argv) {
    int local = 20;
    printf("  &global=%p\n", &global);
    printf("&not_init=%p\n", &not_init);
    printf("    &main=%p\n", &main);
    printf("   &local=%p\n", &local);
    return 0;
}
