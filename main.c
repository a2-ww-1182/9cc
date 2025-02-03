#include "9cc.h"
#include <stdio.h>

char *user_input;
Token *token;

int main(int argc, char **argv) {
    if (argc != 2) {
        error("引数の個数が正しくありません\n");
        return 1;
    }

    // トークナイズしてパースする
    user_input = argv[1];
    token = tokenize(user_input);
    Node *node = expr();

    // アセンブリの前半部分を出力
    printf(".intel_syntax noprefix\n");
    printf(".globl main\n");
    printf("main:\n");

    // 抽象構文木を下りながらコード生成
    gen(node);

    // スタックトップの式全体の計算結果をRAXにロードして関数からの返り値とする
    printf("    pop rax\n");    
    printf("    ret\n");
    return 0;
}