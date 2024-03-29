/**
 * @file test_sm4_1.c
 * @author sexybug (hello.bug@outlook.com)
 * @brief GB_T 32907-2016信息安全技术 SM4分组密码算法 示例1测试
 * @version 0.1
 * @date 2023-02-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../sm4.h"
#include "../../test.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    uint8_t p_str[32] = "000102030405060708090A0B0C0D0E0F";
    // uint8_t key_str[32] = "2b7e151628aed2a6abf7158809cf4f3c";    //sm4.ets
    uint8_t key_str[32] = "01010101010101010101010101010101";
    uint8_t c_str[32] = "681EDF34D206965E86B3E94F536E4246";
    uint8_t p[16];
    HexString2Hex(p_str, 32, p);
    uint8_t key[16];
    HexString2Hex(key_str, 32, key);
    uint8_t c[16];
    SM4_Encrypt(key, p, 16, c);
    dump_mem(c, 16);

    // uint8_t p_out[16];
    // SM4_Decrypt(key, c, 16, p_out);
    // dump_mem(p_out, 16);
    return 0;
}