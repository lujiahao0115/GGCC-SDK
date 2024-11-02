#include <cstddef>  // 对于 size_t
#include <cstdint>  // 对于 uint32_t 和 uint8_t

#include <cstring>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>

#include <cstdint> // 用于uint32_t和uint8_t
#include <string>

#define MD5_BLOCK_SIZE 64
// 辅助函数定义
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define MD5F__(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define MD5G__(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define MD5H__(x, y, z) ((x) ^ (y) ^ (z))
#define MD5I__(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define MD5FF__(a, b, c, d, x, s, ac) { \
(a) += MD5F__ ((b), (c), (d)) + (x) + (uint32_t)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define MD5GG__(a, b, c, d, x, s, ac) { \
(a) += MD5G__ ((b), (c), (d)) + (x) + (uint32_t)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define MD5HH__(a, b, c, d, x, s, ac) { \
(a) += MD5H__ ((b), (c), (d)) + (x) + (uint32_t)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}
#define MD5II__(a, b, c, d, x, s, ac) { \
(a) += MD5I__ ((b), (c), (d)) + (x) + (uint32_t)(ac); \
(a) = ROTATE_LEFT ((a), (s)); \
(a) += (b); \
}

namespace ggcc {
	
	namespace ec{
		// MD5 上下文结构
		typedef struct hash_context {
			uint8_t buffer[MD5_BLOCK_SIZE]; // 数据块缓冲区
			uint32_t state[5];              // 状态数组，存储中间值的状态
			uint32_t total[2];              // 位数计数器，当前已处理数据的长度
		} hash_context;
		
		// MD5 算法的主要函数声明
		void hash_start(hash_context* ctx);
		void hash_update(hash_context* ctx, const uint8_t* data, size_t len);
		void hash_finish(hash_context* ctx, uint8_t* digest);
		void MD5_Transform(uint32_t state[4], const uint8_t block[MD5_BLOCK_SIZE]);
		void MD5_Encode(uint8_t* output, const uint32_t* input, size_t len);
		void MD5_Decode(uint32_t* output, const uint8_t* input, size_t len);
		
		static const uint8_t PADDING[64] = { 0x80, 0 };
		
		typedef struct {
			uint8_t buffer[64];
			uint32_t state[4];
			uint32_t count[2];
		} MD5_CTX;
		
		void hash_start(hash_context* ctx) {
			ctx->state[0] = 0x67452301;
			ctx->state[1] = 0xEFCDAB89;
			ctx->state[2] = 0x98BADCFE;
			ctx->state[3] = 0x10325476;
			ctx->state[4] = 0xC3D2E1F0;
			
			ctx->total[0] = 0;
			ctx->total[1] = 0;
		}
		
		void hash_update(hash_context* ctx, const uint8_t* data, size_t len) {
			uint32_t i, index, partLen;
			
			index = (uint32_t)((ctx->total[0] >> 3) & 0x3F);
			if ((ctx->total[0] += (uint32_t)len << 3) < (uint32_t)len << 3)
				ctx->total[1]++;
			ctx->total[1] += (uint32_t)len >> 29;
			
			partLen = 64 - index;
			
			if (len >= partLen) {
				memcpy(&ctx->buffer[index], data, partLen);
				MD5_Transform(ctx->state, ctx->buffer);
				
				for (i = partLen; i + 63 < len; i += 64) {
					MD5_Transform(ctx->state, &data[i]);
				}
				
				index = 0;
			} else {
				i = 0;
			}
			
			memcpy(&ctx->buffer[index], &data[i], len - i);
		}
		
		void hash_finish(hash_context* ctx, uint8_t* digest) {
			uint8_t bits[8];
			uint32_t index, padLen;
			
			MD5_Encode(bits, ctx->total, 8);
			
			index = (uint32_t)((ctx->total[0] >> 3) & 0x3F);
			padLen = (index < 56) ? (56 - index) : (120 - index);
			hash_update(ctx, PADDING, padLen);
			
			hash_update(ctx, bits, 8);
			
			MD5_Encode(digest, ctx->state, 16);
			
			memset(ctx, 0, sizeof(*ctx));
		}
		
		// MD5_Transform 函数实现
		void MD5_Transform(uint32_t state[4], const uint8_t block[MD5_BLOCK_SIZE]) {
			uint32_t a = state[0], b = state[1], c = state[2], d = state[3], x[16];
			
			MD5_Decode(x, block, 64);
			
			//Round 1 使用 MD5FF__ 函数和一个系列的常数和数据块索引。
			//Round 2 使用 MD5GG__ 函数，常数和数据块索引按照MD5算法规范变化。
			//Round 3 使用 MD5HH__ 函数，常数和数据块索引继续变化。
			//Round 4 使用 MD5II__ 函数，再次变化常数和数据块索引。
			// Round 1
			MD5FF__(a, b, c, d, x[0], S11, 0xd76aa478); /* 1 */ //预定义常数是由正弦函数的值计算得出的，确保每次操作都略有不同，从而增加了哈希过程的熵和不可预测性。
			MD5FF__(d, a, b, c, x[1], S12, 0xe8c7b756); /* 2 */
			MD5FF__(c, d, a, b, x[2], S13, 0x242070db); /* 3 */
			MD5FF__(b, c, d, a, x[3], S14, 0xc1bdceee); /* 4 */
			MD5FF__(a, b, c, d, x[4], S11, 0xf57c0faf); /* 5 */
			MD5FF__(d, a, b, c, x[5], S12, 0x4787c62a); /* 6 */
			MD5FF__(c, d, a, b, x[6], S13, 0xa8304613); /* 7 */
			MD5FF__(b, c, d, a, x[7], S14, 0xfd469501); /* 8 */
			MD5FF__(a, b, c, d, x[8], S11, 0x698098d8); /* 9 */
			MD5FF__(d, a, b, c, x[9], S12, 0x8b44f7af); /* 10 */
			MD5FF__(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
			MD5FF__(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
			MD5FF__(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
			MD5FF__(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
			MD5FF__(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
			MD5FF__(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */
			
			// Round 2
			MD5GG__(a, b, c, d, x[1], S21, 0xf61e2562); /* 17 */
			MD5GG__(d, a, b, c, x[6], S22, 0xc040b340); /* 18 */
			MD5GG__(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
			MD5GG__(b, c, d, a, x[0], S24, 0xe9b6c7aa); /* 20 */
			MD5GG__(a, b, c, d, x[5], S21, 0xd62f105d); /* 21 */
			MD5GG__(d, a, b, c, x[10], S22, 0x2441453); /* 22 */
			MD5GG__(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
			MD5GG__(b, c, d, a, x[4], S24, 0xe7d3fbc8); /* 24 */
			MD5GG__(a, b, c, d, x[9], S21, 0x21e1cde6); /* 25 */
			MD5GG__(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
			MD5GG__(c, d, a, b, x[3], S23, 0xf4d50d87); /* 27 */
			MD5GG__(b, c, d, a, x[8], S24, 0x455a14ed); /* 28 */
			MD5GG__(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
			MD5GG__(d, a, b, c, x[2], S22, 0xfcefa3f8); /* 30 */
			MD5GG__(c, d, a, b, x[7], S23, 0x676f02d9); /* 31 */
			MD5GG__(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */
			
			// Round 3
			MD5HH__(a, b, c, d, x[5], S31, 0xfffa3942); /* 33 */
			MD5HH__(d, a, b, c, x[8], S32, 0x8771f681); /* 34 */
			MD5HH__(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
			MD5HH__(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
			MD5HH__(a, b, c, d, x[1], S31, 0xa4beea44); /* 37 */
			MD5HH__(d, a, b, c, x[4], S32, 0x4bdecfa9); /* 38 */
			MD5HH__(c, d, a, b, x[7], S33, 0xf6bb4b60); /* 39 */
			MD5HH__(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
			MD5HH__(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
			MD5HH__(d, a, b, c, x[0], S32, 0xeaa127fa); /* 42 */
			MD5HH__(c, d, a, b, x[3], S33, 0xd4ef3085); /* 43 */
			MD5HH__(b, c, d, a, x[6], S34, 0x4881d05); /* 44 */
			MD5HH__(a, b, c, d, x[9], S31, 0xd9d4d039); /* 45 */
			MD5HH__(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
			MD5HH__(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
			MD5HH__(b, c, d, a, x[2], S34, 0xc4ac5665); /* 48 */
			
			// Round 4
			MD5II__(a, b, c, d, x[0], S41, 0xf4292244); /* 49 */
			MD5II__(d, a, b, c, x[7], S42, 0x432aff97); /* 50 */
			MD5II__(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
			MD5II__(b, c, d, a, x[5], S44, 0xfc93a039); /* 52 */
			MD5II__(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
			MD5II__(d, a, b, c, x[3], S42, 0x8f0ccc92); /* 54 */
			MD5II__(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
			MD5II__(b, c, d, a, x[1], S44, 0x85845dd1); /* 56 */
			MD5II__(a, b, c, d, x[8], S41, 0x6fa87e4f); /* 57 */
			MD5II__(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
			MD5II__(c, d, a, b, x[6], S43, 0xa3014314); /* 59 */
			MD5II__(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
			MD5II__(a, b, c, d, x[4], S41, 0xf7537e82); /* 61 */
			MD5II__(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
			MD5II__(c, d, a, b, x[2], S43, 0x2ad7d2bb); /* 63 */
			MD5II__(b, c, d, a, x[9], S44, 0xeb86d391); /* 64 */
			
			state[0] += a;
			state[1] += b;
			state[2] += c;
			state[3] += d;
			
			// 清除敏感信息
			memset(x, 0, sizeof(x));
		}
		
		
		// MD5_Encode 函数实现
		void MD5_Encode(uint8_t* output, const uint32_t* input, size_t len) {
			for (size_t i = 0, j = 0; j < len; i++, j += 4) {
				output[j] = (uint8_t)(input[i] & 0xff);
				output[j + 1] = (uint8_t)((input[i] >> 8) & 0xff);
				output[j + 2] = (uint8_t)((input[i] >> 16) & 0xff);
				output[j + 3] = (uint8_t)((input[i] >> 24) & 0xff);
			}
		}
		
		// MD5_Decode 函数实现
		void MD5_Decode(uint32_t* output, const uint8_t* input, size_t len) {
			for (size_t i = 0, j = 0; j < len; i++, j += 4) {
				output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) |
				(((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);
			}
		}
		
		// MD5函数实现，将字符串转换为MD5哈希
		std::string MD5(const std::string& input) {
			hash_context ctx;
			uint8_t digest[16]; // MD5哈希是16字节
			char buffer[33];    // 存储32个字符的哈希值和一个终止符
			
			hash_start(&ctx);
			hash_update(&ctx, reinterpret_cast<const uint8_t*>(input.c_str()), input.length());
			hash_finish(&ctx, digest);
			
			// 将16字节的哈希转换为32个字符的十六进制字符串
			for (int i = 0; i < 16; i++) {
				sprintf_s(buffer + i * 2, 3, "%02x", digest[i]); // 每次写入3个字符（2个十六进制数字和一个终止符）
			}
			
			return std::string(buffer);
		}
	}
}
