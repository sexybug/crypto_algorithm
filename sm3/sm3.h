/**
 * @file sm3.h
 * @author sexybug (hello.bug@outlook.com)
 * @brief GB_T 32905-2016 信息安全技术 SM3密码杂凑算法 c语言实现
 * @version 0.1
 * @date 2023-02-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _SM3_H_
#define _SM3_H_

#include <stdint.h>

#define SM3_BLOCK_SIZE 64

/**
 * @brief sm3摘要函数
 *
 * @param msg 输入
 * @param msg_len 输入消息长度（in Byte）
 * @param digest 输出：256bit摘要
 */
void sm3(const uint8_t *msg, int msg_len, uint8_t *digest);

#endif /* _SM3_H_ */