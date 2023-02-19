#include "sm3.h"

static const uint32_t IV[8] = {0x7380166F, 0x4914B2B9, 0x172442D7, 0xDA8A0600, 0xA96F30BC, 0x163138AA, 0xE38DEE4D, 0xB0FB0E4E};
static const uint32_t T0 = 0x79CC4519;
static const uint32_t T1 = 0x7A879D8A;

/**
 * @brief 将X循环左移n位
 *
 * @param
 * @param n
 * @return uint32_t
 */
static inline uint32_t rotl32(uint32_t X, int n)
{
    return (X << n) | (X >> (32 - n));
}

static inline uint32_t FF0(uint32_t X, uint32_t Y, uint32_t Z)
{
    return X ^ Y ^ Z;
}
static inline uint32_t FF1(uint32_t X, uint32_t Y, uint32_t Z)
{
    return (X & Y) | (X & Z) | (Y & Z);
}
static inline uint32_t GG0(uint32_t X, uint32_t Y, uint32_t Z)
{
    return X ^ Y ^ Z;
}
static inline uint32_t GG1(uint32_t X, uint32_t Y, uint32_t Z)
{
    return (X & Y) | ((~X) & Z);
}

static inline uint32_t P0(uint32_t X)
{
    return X ^ rotl32(X, 9) ^ rotl32(X, 17);
}
static inline uint32_t P1(uint32_t X)
{
    return X ^ rotl32(X, 15) ^ rotl32(X, 23);
}

/**
 * @brief uint8数组转uint32数组
 *
 * @param X uint8数组，长度512bit
 * @param Y uint32数组
 */
static void u8_2_u32_512(const uint8_t *X, uint32_t *Y)
{
    for (int i = 0; i < 16; i++)
    {
        Y[i] = ((uint32_t)X[i * 4] << 24) | ((uint32_t)X[i * 4 + 1] << 16) | ((uint32_t)X[i * 4 + 2] << 8) | ((uint32_t)X[i * 4 + 3] << 0);
    }
}

/**
 * @brief uint32数组转uint8数组
 *
 * @param X uint32数组，长度256bit
 * @param Y uint8数组
 */
static void u32_2_u8_256(const uint32_t *X, uint8_t *Y)
{
    for (int i = 0; i < 8; i++)
    {
        Y[i * 4] = (X[i] >> 24) & 0xFF;
        Y[i * 4 + 1] = (X[i] >> 16) & 0xFF;
        Y[i * 4 + 2] = (X[i] >> 8) & 0xFF;
        Y[i * 4 + 3] = (X[i] >> 0) & 0xFF;
    }
}

/**
 * @brief uint64转uint8数组
 *
 * @param X uint64数据
 * @param Y uint8数组
 */
static void u64_2_u8(uint64_t X, uint8_t *Y)
{
    Y[0] = (X >> 56) & 0xff;
    Y[1] = (X >> 48) & 0xff;
    Y[2] = (X >> 40) & 0xff;
    Y[3] = (X >> 32) & 0xff;
    Y[4] = (X >> 24) & 0xff;
    Y[5] = (X >> 16) & 0xff;
    Y[6] = (X >> 8) & 0xff;
    Y[7] = (X >> 0) & 0xff;
}

/**
 * @brief 消息扩展
 *
 * @param B 512bit 消息分组
 * @param W
 * @param WT
 */
static void message_extend(const uint32_t *B, uint32_t *W, uint32_t *WT)
{
    for (int i = 0; i < 16; i++)
    {
        W[i] = B[i];
    }
    for (int i = 16; i < 68; i++)
    {
        W[i] = P1(W[i - 16] ^ W[i - 9] ^ rotl32(W[i - 3], 15)) ^ rotl32(W[i - 13], 7) ^ W[i - 6];
    }
    for (int i = 0; i < 64; i++)
    {
        WT[i] = W[i] ^ W[i + 4];
    }
}

/**
 * @brief 压缩函数
 *
 * @param Vi V(i)
 * @param Bi B(i)
 * @param WT W'
 * @param V1 V(i+1)
 */
static void CF(const uint32_t *Vi, const uint32_t *Bi, uint32_t *V1)
{
    uint32_t A, B, C, D, E, F, G, H;
    uint32_t SS1, SS2, TT1, TT2;

    uint32_t W[68], WT[64];
    message_extend(Bi, W, WT);

    A = Vi[0];
    B = Vi[1];
    C = Vi[2];
    D = Vi[3];
    E = Vi[4];
    F = Vi[5];
    G = Vi[6];
    H = Vi[7];

    for (int j = 0; j < 16; ++j)
    {
        SS1 = rotl32(rotl32(A, 12) + E + rotl32(T0, j), 7);
        SS2 = SS1 ^ rotl32(A, 12);
        TT1 = FF0(A, B, C) + D + SS2 + WT[j];
        TT2 = GG0(E, F, G) + H + SS1 + W[j];
        D = C;
        C = rotl32(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = rotl32(F, 19);
        F = E;
        E = P0(TT2);
    }
    for (int j = 16; j < 64; ++j)
    {
        SS1 = rotl32(rotl32(A, 12) + E + rotl32(T1, j), 7);
        SS2 = SS1 ^ rotl32(A, 12);
        TT1 = FF1(A, B, C) + D + SS2 + WT[j];
        TT2 = GG1(E, F, G) + H + SS1 + W[j];
        D = C;
        C = rotl32(B, 9);
        B = A;
        A = TT1;
        H = G;
        G = rotl32(F, 19);
        F = E;
        E = P0(TT2);
    }
    V1[0] = A ^ Vi[0];
    V1[1] = B ^ Vi[1];
    V1[2] = C ^ Vi[2];
    V1[3] = D ^ Vi[3];
    V1[4] = E ^ Vi[4];
    V1[5] = F ^ Vi[5];
    V1[6] = G ^ Vi[6];
    V1[7] = H ^ Vi[7];
}

/**
 * @brief 填充
 * 
 * @param m 原始输入消息
 * @param mlen 消息长度（in Byte)
 * @param pad_blocks 填充后待压缩数据
 * @param pad_blocks_len 填充后待压缩数据长度（in Byte)
 */
static void sm3_padding(const uint8_t *m, int mlen, uint8_t *pad_blocks, int *pad_blocks_len)
{
    int block_len = 0;
    // 复制非整512分组数据。如果消息m是整512分组，则不复制任何数据。
    for (int i = mlen - mlen % SM3_BLOCK_SIZE; i < mlen; i++)
    {
        pad_blocks[block_len] = m[i];
        block_len++;
    }
    // 在末尾添加1
    pad_blocks[block_len] = 0x80;
    block_len++;
    // 填充0
    // 情形1：1个分组够用
    if ((block_len + 8) <= SM3_BLOCK_SIZE)
    {
        while (block_len < (SM3_BLOCK_SIZE - 8))
        {
            pad_blocks[block_len] = 0;
            block_len++;
        }
    }
    // 情形2：需要再加1个分组
    else
    {
        while (block_len < SM3_BLOCK_SIZE * 2 - 8)
        {
            pad_blocks[block_len] = 0;
            block_len++;
        }
    }
    // 最后填充64bit表示的长度l
    uint64_t l = mlen * 8;
    u64_2_u8(l, pad_blocks + block_len);
    block_len += 8;
    *pad_blocks_len = block_len;
}

/**
 * @brief sm3摘要函数
 * 
 * @param m 输入
 * @param mlen 输入消息长度（in Byte）
 * @param out 输出：256bit摘要
 */
void sm3(const uint8_t *m, int mlen, uint8_t *out)
{
    uint32_t V[8], B[16], V1[8];
    for (int i = 0; i < 8; i++)
    {
        V[i] = IV[i];
    }
    // 压缩非填充分组
    for (int i = 0; i < mlen / SM3_BLOCK_SIZE; i++)
    {
        u8_2_u32_512(m + i * SM3_BLOCK_SIZE, B);
        CF(V, B, V1);
        for (int j = 0; j < 8; j++)
        {
            V[j] = V1[j];
        }
    }

    // 填充，填充后的分组可能为1个512bit分组，也可能为2个512bit分组
    uint8_t pad_blocks[SM3_BLOCK_SIZE * 2];
    int pad_blocks_len = 0;
    sm3_padding(m, mlen, pad_blocks, &pad_blocks_len);

    // 压缩填充后的分组
    u8_2_u32_512(pad_blocks, B);
    CF(V, B, V1);
    pad_blocks_len -= SM3_BLOCK_SIZE;
    if (pad_blocks_len > 0)
    {
        for (int j = 0; j < 8; j++)
        {
            V[j] = V1[j];
        }
        u8_2_u32_512(pad_blocks + SM3_BLOCK_SIZE, B);
        CF(V, B, V1);
    }

    u32_2_u8_256(V1, out);
}