/**
 * @file test_sm4_2.c
 * @author sexybug (hello.bug@outlook.com)
 * @brief GB_T 32907-2016信息安全技术 SM4分组密码算法 示例2测试
 * @version 0.1
 * @date 2023-02-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "sm4.h"
#include "../test.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    uint8_t p_str[] = "0123456789ABCDEFFEDCBA9876543210";
    uint8_t p[16];
    HexString2Hex(p_str, 32, p);
    uint8_t key[16];
    HexString2Hex(p_str, 32, key);
    uint8_t c[16];

    for (int i = 0; i < 1000000; i++)
    {
        SM4_Encrypt(key, p, 16, c);
        memcpy(p,c,16);
    }

    dump_mem(c, 16);

    return 0;
}