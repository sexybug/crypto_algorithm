#ifndef _TEST_H
#define _TEST_H

#include <stdint.h>

/**
 * @brief 打印内存数据
 * 
 * @param ptr 
 * @param len 
 */
void dump_mem(const void *ptr, int len);
/**
 * @brief 16进制字符串转数组
 * 
 * @param str 16进制字符串
 * @param strLen 字符串长度(in Byte)
 * @param out 输出
 */
void HexString2Hex(const char *str, int strLen, uint8_t *out);

#endif // _TEST_H