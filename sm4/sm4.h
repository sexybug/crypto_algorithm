/**
 * @file sm4.h
 * @author sexybug (hello.bug@outlook.com)
 * @brief GB_T 32907-2016信息安全技术 SM4分组密码算法 c语言实现
 * @version 0.1
 * @date 2023-02-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _SM4_H_
#define _SM4_H_

#include <stdint.h>

/**
 * @brief SM4加密函数，输入必须是整分组
 *
 * @param key 128bit密钥
 * @param in 明文输入
 * @param inlen 明文长度(in Byte)
 * @param out 密文输出
 */
void SM4_Encrypt(const uint8_t *key, const uint8_t *in, int inlen, uint8_t *out);

/**
 * @brief SM4解密函数，输入必须是整分组
 *
 * @param key 128bit密钥
 * @param in 密文输入
 * @param inlen 密文长度(in Byte)
 * @param out 明文输出
 */
void SM4_Decrypt(const uint8_t *key, const uint8_t *in, int inlen, uint8_t *out);

#endif /* _SM4_H_ */