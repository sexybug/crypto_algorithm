#ifndef _TEST_H
#define _TEST_H

#include <stdint.h>

void dump_mem(const void *ptr, int len);
void HexString2Hex(const char *str, int strLen, uint8_t *out);

#endif // _TEST_H