//位运算
//去掉最后一位          | (101101->10110)           | x shr 1
//在最后加一个0         | (101101->1011010)         | x shl 1
//在最后加一个1         | (101101->1011011)         | x shl 1+1
//把最后一位变成1       | (101100->101101)          | x or 1
//把最后一位变成0       | (101101->101100)          | x or 1-1
//最后一位取反          | (101101->101100)          | x xor 1
//把右数第k位变成1      | (101001->101101,k=3)      | x or (1 shl (k-1))
//把右数第k位变成0      | (101101->101001,k=3)      | x and not (1 shl (k-1))
//右数第k位取反         | (101001->101101,k=3)      | x xor (1 shl (k-1))
//取末三位              | (1101101->101)            | x and 7
//取末k位               | (1101101->1101,k=5)       | x and (1 shl k-1)
//取右数第k位           | (1101101->1,k=4)          | x shr (k-1) and 1
//把末k位变成1          | (101001->101111,k=4)      | x or (1 shl k-1)
//末k位取反             | (101001->100110,k=4)      | x xor (1 shl k-1)
//把右边连续的1变成0    | (100101111->100100000)    | x and (x+1)
//把右起第一个0变成1    | (100101111->100111111)    | x or (x+1)
//把右边连续的0变成1    | (11011000->11011111)      | x or (x-1)
//取右边连续的1         | (100101111->1111)         | (x xor (x+1)) shr 1
//去掉右起第一个1的左边 | (100101000->1000)         | x and (x xor (x-1))

//builtin函数
int __builtin_ffs(int x);
int __builtin_ffsll(long long);
//Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.

int __builtin_clz(unsigned int x);
int __builtin_clzll(unsigned long long);
//Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.

int __builtin_ctz(unsigned int x);
int __builtin_ctzll(unsigned long long);
//Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.

int __builtin_clrsb(int x);
int __builtin_clrsbll(long long);
//Returns the number of leading redundant sign bits in x, i.e. the number of bits following the most significant bit that are identical to it. There are no special cases for 0 or other values.

int __builtin_popcount(unsigned int x);
int __builtin_popcountll(unsigned long long);
//Returns the number of 1-bits in x.

int __builtin_parity(unsigned int x);
int __builtin_parityll(unsigned long long);
//Returns the parity of x, i.e. the number of 1-bits in x modulo 2.

uint32_t __builtin_bswap32(uint32_t x);
uint64_t __builtin_bswap64(uint64_t x);
//Returns x with the order of the bytes reversed; for example, 0xaabb becomes 0xbbaa. Byte here always means exactly 8 bits.
