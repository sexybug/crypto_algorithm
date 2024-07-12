/**
 * @file sm3.h
 * @author sexybug (hello.bug@outlook.com)
 * @brief 多次输入消息测试
 * @version 0.1
 * @date 2023-03-05
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../sm3.h"
#include "../../test.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    uint8_t m[32*1024];
    int mlen = 32*1024;
    memset(m,1,mlen);
    uint8_t out[32];

    sm3(m, mlen, out);

    printf("hash:\n");
    dump_mem(out, 32);
    return 0;
}