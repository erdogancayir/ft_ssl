#include "md5_compute.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// MD5 context yapısı (opsiyonel, basitleştirmek için doğrudan kullanabiliriz)
typedef uint32_t u32;
typedef uint8_t u8;

// K tablosu
static const u32 K[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    // Round 2
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    // Round 3
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    // Round 4
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

// S shift tablosu
static const u32 S[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

// Sola döndürme
static u32 left_rotate(u32 x, u32 c)
{
    return (x << c) | (x >> (32 - c));
}

// md5_compute.c
char *md5_compute(const char *input)
{
    // 1. Get the initial length of the input string (in bytes)
    size_t initial_len = strlen(input);

    // 2. Compute the bit-length (MD5 requires this to be appended at the end)
    uint64_t bit_len = (uint64_t)initial_len * 8;

    // 3. Compute the new length after padding:
    //    +1 for the 0x80 byte (binary 10000000)
    //    pad with 0x00 until the total length (mod 64) equals 56
    //    (56 bytes = 448 bits, leaving 64 bits for the bit length)
    size_t new_len = initial_len + 1;
    while (new_len % 64 != 56)
        new_len++;

    // 4. Allocate memory for the final padded message:
    //    total size = new_len (data + padding) + 8 bytes (bit length)
    uint8_t *msg = calloc(new_len + 8, 1);
    if (!msg)
        return NULL; // Memory allocation failed

    // 5. Copy the original message into the allocated buffer
    memcpy(msg, input, initial_len);

    // 6. Append the 0x80 byte to mark the start of padding (10000000 in binary)
    msg[initial_len] = 0x80;

    // 7. Append the original message length (in bits) as a 64-bit little-endian value
    memcpy(msg + new_len, &bit_len, 8);

    // 8. Initialize MD5 buffer variables (A, B, C, D) with standard constants from RFC 1321
    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    // 9. Process each 512-bit (64-byte) block of the message
    for (size_t offset = 0; offset < new_len; offset += 64)
    {
        // Interpret the current 64-byte block as 16 32-bit little-endian words
        uint32_t *w = (uint32_t *)(msg + offset);

        // Create working variables A, B, C, D initialized with the current hash values
        uint32_t A = a0, B = b0, C = c0, D = d0;

        for (uint32_t i = 0; i < 64; i++)
        {
            uint32_t F, g;

            if (i < 16)
            {
                F = (B & C) | ((~B) & D);
                g = i;
            }
            else if (i < 32)
            {
                F = (D & B) | ((~D) & C);
                g = (5 * i + 1) % 16;
            }
            else if (i < 48)
            {
                F = B ^ C ^ D;
                g = (3 * i + 5) % 16;
            }
            else
            {
                F = C ^ (B | ~D);
                g = (7 * i) % 16;
            }

            uint32_t tmp = D;
            D = C;
            C = B;
            B = B + left_rotate(A + F + K[i] + w[g], S[i]);
            A = tmp;
        }

        // 6. Bu bloğun sonucunu ana hash'e ekle
        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    free(msg);

    // 7. Hash’i little-endian olarak döndür
    uint8_t *digest = malloc(16);
    if (!digest)
        return NULL;

    memcpy(digest, &a0, 4);
    memcpy(digest + 4, &b0, 4);
    memcpy(digest + 8, &c0, 4);
    memcpy(digest + 12, &d0, 4);

    // 8. Hex string oluştur
    char *hex = malloc(33);
    if (!hex)
    {
        free(digest);
        return NULL;
    }

    for (int i = 0; i < 16; i++)
        sprintf(hex + i * 2, "%02x", digest[i]);

    free(digest);
    return hex;
}
