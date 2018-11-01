#include <stdio.h>  // TODO delete
/*
 * Modified CS:APP Data Lab
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 */

/* Read the following instructions carefully.

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  // pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
  int pow2plus1(int x) {
      // exploit ability of shifts to compute powers of 2
      return (1 << x) + 1;
  }

  // pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
  int pow2plus4(int x) {
      // exploit ability of shifts to compute powers of 2
      int result = (1 << x);
      result += 4;
      return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any
arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  2. Use the btest test harness to check your functions for correctness.
  3. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
 */

/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x)  // 4 ops
{
    int neg_mask = x >> 31;

    // Return x if x is nonnegative else ones' complement + 1 (two's complement)
    return (x ^ neg_mask) + (neg_mask & 1);
}

/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000, 0x80000000) = 0,
 *            addOK(0x80000000, 0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y)  // 6 op
{
    /*
     * Observe:
     * Return 0 (overflow) when (+,0) + (+,0) => (-) or (-) + (-) => (+,0),
     * that is, sign of x and y are same and sign of x (or y) and sum are
     * different. Since we can compute whether two signs are DIFFERENT faster,
     * convert the observation to sign of x and sum are DIFFERENT and sign of y
     * and sum are DIFFERENT.
     *
     * See also addOK_7()
     */
    int sum = x + y;
    return !(((x ^ sum) & (y ^ sum)) >> 31);
}

int addOK_7(int x, int y)  // 7 op
{
    // See addOK_9(), reduce ops by delaying getting sign

    int sum = x + y;
    return (((x ^ y) | ~(sum ^ x)) >> 31) & 1;
}

int addOK_9(int x, int y)  // 9 ops
{
    int sign_x = x >> 31;
    int sign_y = y >> 31;
    int sign_sum = (x + y) >> 31;

    // return 1 if sign of x and y are different or sign of sum and x are same
    return ((sign_x ^ sign_y) | ~(sign_sum ^ sign_x)) & 1;
}

/*
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x)  // 7 ops
{
    int hex5555 = (0x55 << 8) | 0x55;
    int hex55555555 = (hex5555 << 16) | hex5555;
    return !((x & hex55555555) ^ hex55555555);
}

int allEvenBits_9(int x)  // 9 ops
{
    x = x & x >> 16;
    x = x & x >> 8;
    x = x & x >> 4;
    x = x & x >> 2;
    return x & 1;
}

/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x)  // 7 ops
{
    int hexAAAA = (0xAA << 8) | 0xAA;
    int hexAAAAAAAA = (hexAAAA << 16) | hexAAAA;
    return !((x & hexAAAAAAAA) ^ hexAAAAAAAA);
}

int allOddBits_10(int x)  // 10 ops
{
    x = x & x >> 16;
    x = x & x >> 8;
    x = x & x >> 4;
    x = x & x >> 2;
    return (x >> 1) & 1;
}

/*
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x)  // 7 ops
{
    int hex5555 = (0x55 << 8) | 0x55;
    int hex55555555 = (hex5555 << 16) | hex5555;
    return !!(x & hex55555555);
}

int anyEvenBit_9(int x)  // 9 ops
{
    x = x | x >> 16;
    x = x | x >> 8;
    x = x | x >> 4;
    x = x | x >> 2;
    return x & 1;
}

/*
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x)  // 7 ops
{
    int hexAAAA = (0xAA << 8) | 0xAA;
    int hexAAAAAAAA = (hexAAAA << 16) | hexAAAA;
    return !!(x & hexAAAAAAAA);
}

int anyOddBit_10(int x)  // 10 ops
{
    x = x | x >> 16;
    x = x | x >> 8;
    x = x | x >> 4;
    x = x | x >> 2;
    return (x >> 1) & 1;
}

/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x)  // 6 ops
{
    /*
     * Consider sign bit of x and two's complement of x:
     * x = 0     => both are 0   WE NEED THIS
     * x = tmin  => both are 1
     * otherwise => exactly one 0 and one 1
     */

    int x_twos_comp = ~x + 1;
    return (((x | x_twos_comp) >> 31) ^ 1) & 1;
}

int bang_12(int x)  // 12 ops
{
    x = x | x >> 16;
    x = x | x >> 8;
    x = x | x >> 4;
    x = x | x >> 2;
    x = x | x >> 1;
    return ~x & 1;
}

/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y)  // 4 ops
{
    return ~(~x | ~y);
}

/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x)  // 24 ops
{
    // See bitCount_30()

    int hex0F0F = (0x0F << 8) | 0x0F;
    int hex0F0F0F0F = (hex0F0F << 16) | hex0F0F;
    int hex33333333 = hex0F0F0F0F ^ (hex0F0F0F0F << 2);
    int hex55555555 = hex33333333 ^ (hex33333333 << 1);

    x = (x & hex55555555) + ((x >> 1) & hex55555555);
    x = (x & hex33333333) + ((x >> 2) & hex33333333);

    /*
     * Idea from
     * http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
     * Since x is now 4-bit per group and the maximum number of 1 after add up
     * two group is 8, which is representable in 4-bit, so we can do mask after
     * add.
     * Benefits: save 1 op (no need to mask twice)
     */
    x = (x + (x >> 4)) & hex0F0F0F0F;

    // Same concept with above but save more ops
    x = x + (x >> 8);
    x = (x + (x >> 16)) & 0xFF;

    return x;
}

int bitCount_30(int x)  // 30 ops
{
    /*
     * Idea: https://www.viseator.com/2017/06/18/CS_APP_DataLab/
     *
     * Counting parallel and in place
     *
     * 'x' means ignore the column where '+' means add up the column
     *                                   x + x + x + x + x
     * consider 8-bit x:                |0|1|1|1|0|0|0|1|
     * shift 1 bit:                       |0|1|1|1|0|0|0|1|
     * add the specific column:         | 01| 10| 00| 01|
     * number of bit 1 in each group:   | 1 | 2 | 0 | 1 |
     *
     * repeat similar action              x  +  x  +  x
     * the value of x now:              |01|10|00|01|
     * shift 2 bit:                        |01|10|00|01|
     * add the specific column:         | 0011| 0001|
     * number of bit 1 in each group:   |  3  |  1  |
     *
     * repeat similar action               x    +    x
     * the value of x now:              |0011|0001|
     * shift 4 bit:                          |0011|0001|
     * add the specific column:         | 00000100|
     * number of bit 1 in each group:   |     4   | <- the total bit 1 in x
     */
    int hex0000FFFF = (0xFF << 8) | 0xFF;
    int hex00FF00FF = hex0000FFFF ^ (hex0000FFFF << 8);
    int hex0F0F0F0F = hex00FF00FF ^ (hex00FF00FF << 4);
    int hex33333333 = hex0F0F0F0F ^ (hex0F0F0F0F << 2);
    int hex55555555 = hex33333333 ^ (hex33333333 << 1);
    x = (x & hex55555555) + ((x >> 1) & hex55555555);
    x = (x & hex33333333) + ((x >> 2) & hex33333333);
    x = (x & hex0F0F0F0F) + ((x >> 4) & hex0F0F0F0F);
    x = (x & hex00FF00FF) + ((x >> 8) & hex00FF00FF);
    x = (x & hex0000FFFF) + ((x >> 16) & hex0000FFFF);
    return x;
}

/*
 * bitMask - Generate a mask consisting of all 1's
 *   lowbit and highbit
 *   Examples: bitMask(5, 3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit)  // 6 ops
{
    // Idea from < aben20807 >:
    // Use '~0 << lowbit' instead of '~((1 << lowbit) + ~0)'
    int ones = ~0;  // All bits are set to 1 or decimal -1
    int high_mask = ones << lowbit;
    int low_mask = ((1 << highbit << 1) + ones);
    return high_mask & low_mask;
}

/*
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and &
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y)  // 8 ops
{
    // (x & y) | (~x & ~y) <- Apply De Morgan's law
    return ~(~(x & y) & ~(~x & ~y));
}

/*
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y)  // 3 ops
{
    // De Morgan's law
    return ~x & ~y;
}

/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y)  // 4 ops
{
    return ~(~x & ~y);
}

/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x)  // 11 ops
{
    x = x ^ (x >> 16);
    x = x ^ (x >> 8);
    x = x ^ (x >> 4);
    x = x ^ (x >> 2);
    x = x ^ (x >> 1);
    return x & 1;
}

/*
 * bitReverse - Reverse bits in a 32-bit word
 *   Examples: bitReverse(0x80000002) = 0x40000001
 *             bitReverse(0x89ABCDEF) = 0xF7D3D591
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 45
 *   Rating: 4
 */
int bitReverse(int x)  // 10 + 24 = 34 ops
{
    int hex0000FFFF = (0xFF << 8) | 0xFF;
    int hex00FF00FF = hex0000FFFF ^ (hex0000FFFF << 8);
    int hex0F0F0F0F = hex00FF00FF ^ (hex00FF00FF << 4);
    int hex33333333 = hex0F0F0F0F ^ (hex0F0F0F0F << 2);
    int hex55555555 = hex33333333 ^ (hex33333333 << 1);
    x = x << 16 | ((x >> 16) & hex0000FFFF);
    x = (x & hex00FF00FF) << 8 | ((x >> 8) & hex00FF00FF);
    x = (x & hex0F0F0F0F) << 4 | ((x >> 4) & hex0F0F0F0F);
    x = (x & hex33333333) << 2 | ((x >> 2) & hex33333333);
    x = (x & hex55555555) << 1 | ((x >> 1) & hex55555555);
    return x;
}

/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y)  // 8 ops
{
    // (~x & y) | (x & ~y)  <- Apply De Morgan's law
    return ~(~(~x & y) & ~(x & ~y));
}

/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m)  // 14 ops
{
    int m_dis = m << 3;
    int n_dis = n << 3;
    int m_mask = (x >> m_dis) & 0xFF;
    int n_mask = (x >> n_dis) & 0xFF;

    // Clear mth and nth bytes if m != n (when m == n, x is already the answer)
    x = x ^ (m_mask << m_dis) ^ (n_mask << n_dis);

    // Set mth and nth bytes that after swap
    return x | (m_mask << n_dis) | (n_mask << m_dis);
}

/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z)  // 7 ops
{
    int false_mask = (!x << 31) >> 31;
    return (~false_mask & y) | (false_mask & z);
}

/*
 * countLeadingZero - count the number of zero bits preceding the
 *                    most significant one bit
 *   Example: countLeadingZero(0x00000F00) = 20,
 *            countLeadingZero(0x00000001) = 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int countLeadingZero(int x)  // 25 ops
{
    /*
     * Speed up from countLeadingZero_36()
     * Idea: ilog2() https://www.viseator.com/2017/06/18/CS_APP_DataLab/,
     * No need to use leading_n_zero as a mask!
     */

    int num_zero = 0;

    // value = 1 if the leading 16 bits are all zero else 0
    int leading_n_zero = !(x >> 16);
    int n = leading_n_zero << 4;  // n = 16 if leading_n_zero is true
    num_zero = n;
    x = x << n;

    // value = 1 if the leading 8 bits are all zero else 0
    leading_n_zero = !(x >> 24);
    n = leading_n_zero << 3;
    num_zero = num_zero + n;
    x = x << n;

    // value = 1 if the leading 4 bits are all zero else 0
    leading_n_zero = !(x >> 28);
    n = leading_n_zero << 2;
    num_zero = num_zero + n;
    x = x << n;

    // value = 1 if the leading 2 bits are all zero else 0
    leading_n_zero = !(x >> 30);
    n = leading_n_zero << 1;
    num_zero = num_zero + n;
    x = x << n;

    int bit_31_is_zero = !(x >> 31);
    num_zero = num_zero + bit_31_is_zero;

    int bit_31_to_30_is_zero = !(x >> 30);
    num_zero = num_zero + bit_31_to_30_is_zero;

    return num_zero;
}

int countLeadingZero_36(int x)  // 36 ops
{
    // See countLeadingZero_43()

    int num_zero = 0;

    // value = 11......11 if the leading 16 bits are all zero else 00......00
    int leading_n_zero = !(x >> 16) << 31 >> 31;
    num_zero = num_zero + (leading_n_zero & 16);
    x = x << (leading_n_zero & 16);

    // value = 11......11 if the leading 8 bits are all zero else 00......00
    leading_n_zero = !(x >> 24) << 31 >> 31;
    num_zero = num_zero + (leading_n_zero & 8);
    x = x << (leading_n_zero & 8);

    // value = 11......11 if the leading 4 bits are all zero else 00......00
    leading_n_zero = !(x >> 28) << 31 >> 31;
    num_zero = num_zero + (leading_n_zero & 4);
    x = x << (leading_n_zero & 4);

    /*
     * Method above takes 8 ops per iteration,
     * but the next interation (8 ops) can only get 2-bit information,
     * and we can get 1-bit information in 3 ops.
     * Hence, consider the remaining 4 bits seperately will be faster.
     */
    int bit_31_is_zero = !(x >> 31);
    num_zero = num_zero + bit_31_is_zero;

    int bit_31_to_30_is_zero = !(x >> 30);
    num_zero = num_zero + bit_31_to_30_is_zero;

    int bit_31_to_29_is_zero = !(x >> 29);
    num_zero = num_zero + bit_31_to_29_is_zero;

    int bit_31_to_28_is_zero = !(x >> 28);
    num_zero = num_zero + bit_31_to_28_is_zero;

    return num_zero;
}

int countLeadingZero_43(int x)  // 43 ops
{
    /*
     * https://hackmd.io/s/Bk-uxCYxz
     *   int clz(uint32_t x) {
     *       if (x == 0) return 32;
     *       int n = 1;
     *       if ((x >> 16) == 0) { n += 16; x <<= 16; }
     *       if ((x >> 24) == 0) { n += 8; x <<= 8; }
     *       if ((x >> 28) == 0) { n += 4; x <<= 4; }
     *       if ((x >> 30) == 0) { n += 2; x <<= 2; }
     *       n = n - (x >> 31);
     *       return n;
     *   }
     */
    int num_zero = 0;

    // value = 11......11 if the leading 16 bits are all zero else 00......00
    int leading_n_zero = !(x >> 16) << 31 >> 31;
    num_zero = num_zero + (leading_n_zero & 16);
    x = x << (leading_n_zero & 16);

    // value = 11......11 if the leading 8 bits are all zero else 00......00
    leading_n_zero = !(x >> 24) << 31 >> 31;
    num_zero = num_zero + (leading_n_zero & 8);
    x = x << (leading_n_zero & 8);

    // value = 11......11 if the leading 4 bits are all zero else 00......00
    leading_n_zero = !(x >> 28) << 31 >> 31;
    num_zero = num_zero + (leading_n_zero & 4);
    x = x << (leading_n_zero & 4);

    // value = 11......11 if the leading 2 bits are all zero else 00......00
    leading_n_zero = !(x >> 30) << 31 >> 31;
    num_zero = num_zero + (leading_n_zero & 2);
    x = x << (leading_n_zero & 2);

    // value = 11......11 if the leading 1 bits are all zero else 00......00
    leading_n_zero = !(x >> 31) << 31 >> 31;
    num_zero = num_zero + (leading_n_zero & 1);
    x = x << (leading_n_zero & 1);

    num_zero = num_zero + !(x >> 31);

    return num_zero;
}

/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x)  // 2 ops
{
    return (x << 31) >> 31;
}

/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
int distinctNegation(int x)  // 3 ops
{
    // Goal: Return 1 if x is not 0 (00......00) or tmin (10......00) else 0

    int throw_sign_bit = x << 1;  // Since !(x << 1) will get warning
    return !!throw_sign_bit;
}

int distinctNegation_5(int x)  // 5 ops
{
    int x_twos_comp = ~x + 1;

    // Check if x is different with two's complement of x
    return !!(x ^ x_twos_comp);
}

int distinctNegation_5_bang(int x)  // 5 ops
{
    // Goal: Return 1 if x is not 0 (00......00) or tmin (10......00) else 0

    // See bang() (case 1 and 2)
    return ((x ^ (~x + 1)) >> 31) & 1;
}

/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *                Round toward zero
 *   Examples: dividePower2(15, 1) = 7, dividePower2(-33, 4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n)  // 7 ops
{
    /*
     * x >> n is equal to floor(x/(2^n)), whether x is nonnegative or negative.
     *
     * But we want ceil(x/(2^n)) when x is negative, that is, round toward zero.
     * And ceil(x/(2^n)) equals to floor((x+(2^n)-1)/(2^n)) when divisor is
     * integer. As a result,  we add (2^n)-1 to x when x is negative.
     *
     * See also trueThreeFourths() for the details when x is negative
     */
    int neg_mask = x >> 31;
    return (x + (neg_mask & ((1 << n) + ~0))) >> n;
}

/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void)  // 4 ops
{
    int hex55 = 0x55;
    int hex5555 = hex55 | (hex55 << 8);
    return hex5555 | (hex5555 << 16);
}

/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *                  Should exactly duplicate effect of C expression (x*3/4),
 *                  including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */

int ezThreeFourths(int x)  // 6 ops
{
    // See dividePower2()

    int x_mul_3 = x + (x << 1);
    int x_mul_3_is_neg = x_mul_3 >> 31;
    return (x_mul_3 + (x_mul_3_is_neg & 3)) >> 2;
}

// ERROR: Test ezThreeFourths_wrong(-2147483647[0x80000001]) failed...
// Gives -536870912[0xe0000000]. Should be -536870911[0xe0000001]
int ezThreeFourths_wrong(int x)
{
    return (x + (x << 1)) >> 2;  // Error: Division of negative number
}

/*
 * fitsBits - return 1 if x can be represented as an n-bit, two's complement
 *            integer.
 *            1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n)  // 6 ops
{
    int m = 33 + ~n;  // => 32 + (~n + 1) => 32 - n
    int x_as_n_bit = (x << m) >> m;
    return !(x ^ x_as_n_bit);  // x == x_as_n_bit
}

/*
 * fitsShort - return 1 if x can be represented as a 16-bit, two's complement
 *             integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x)  // 4 ops
{
    int x_as_16_bit = (x << 16) >> 16;
    return !(x ^ x_as_16_bit);
}

/*
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *               floating point argument f.
 *               Both the argument and result are passed as unsigned int's,
 *               but they are to be interpreted as the bit-level
 *               representations of single-precision floating point values.
 *               When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf)  // 3? ops
{
    unsigned uf_abs = uf & 0x7FFFFFFF;
    return uf_abs > 0x7F800000 ? uf : uf_abs;
}

/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *                  for floating point argument f.
 *                  Argument is passed as unsigned int, but it is to be
 *                  interpreted as the bit-level representation of a
 *                  single-precision floating point value.
 *                  Anything out of range (including NaN and infinity) should
 *                  return 0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf)  // 21? ops
{
    int is_neg = uf >> 31;
    int exponent = (uf >> 23) & 0xFF;
    int fraction = uf & 0x7FFFFF;
    int bias = 127;
    int len_fraction = 23;

    // (NaN or INF) || greater than values that a 32-bit int can represent
    if (exponent == 0xFF || exponent > bias + 31)
        return 0x80000000;

    // Can be represented as 32-bit int
    if (exponent >= bias) {
        int power2 = exponent - bias;
        if (power2 <= len_fraction)
            fraction = fraction >> (len_fraction - power2);
        else
            fraction = fraction << (power2 - len_fraction);
        int value = (1 << power2) | fraction;
        return is_neg ? -value : value;
    }

    // Smaller than values that a 32-bit int can represent
    return 0;
}

/*
 * floatInt2Float - Return bit-level equivalent of expression (float) x
 *                  Result is returned as unsigned int, but it is to be
 *                  interpreted as the bit-level representation of a
 *                  single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatInt2Float(int x)  // 35? ops
{
    // See floatFloat2Int()
    if (x == 0)
        return 0;
    int x_sign = x & 0x80000000;
    int x_abs = x_sign ? -x : x;  // How about Tmin?

    int exponent, fraction;
    int bias = 127;
    int len_fraction = 23;
    int power2 = 31;
    while (!(x_abs >> power2) && power2 > 0) {
        power2--;
    }

    exponent = power2 + bias;
    fraction = ((1 << power2) - 1) & x_abs;
    if (power2 <= len_fraction) {
        fraction = fraction << (len_fraction - power2);
    } else {
        int num_fall_off = power2 - len_fraction;

        /*
         * Consider round off
         * GRS action: https://stackoverflow.com/questions/8981913
         */
        int G = x_abs & (1 << num_fall_off);
        int R = x_abs & (1 << (num_fall_off - 1));

        /*
         * Shift twice to avoid undefined bahavior (<< 32), since:
         *     24 <= power2 <= 31
         *     1 <= num_fall_off <= 8
         * We want 'x_abs << (33 - num_fall_off)'
         */
        int S = x_abs << (32 - num_fall_off) << 1;

        fraction = fraction >> (power2 - len_fraction);

        // Check if need to round up or round-to-even
        fraction += R && (S || G);
    }

    return (x_sign | (exponent << len_fraction)) + fraction;
}

/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *                Both the arguments are passed as unsigned int's, but
 *                they are to be interpreted as the bit-level representations
 *                of single-precision floating point values.
 *                If either argument is NaN, return 0.
 *                +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug)  // 11? ops
{
    // return (uf is not NaN && ug is not NaN && (uf equals to ug || both are
    // zero))
    return (uf & 0x7FFFFFFF) <= 0x7F800000 && (ug & 0x7FFFFFFF) <= 0x7F800000 &&
           (uf == ug || !((uf | ug) << 1));
}

/*
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *               Both the arguments are passed as unsigned int's, but
 *               they are to be interpreted as the bit-level representations
 *               of single-precision floating point values.
 *               If either argument is NaN, return 0.
 *               +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug)  // 23? ops
{
    // Check if uf is NaN or ug is NaN or both are zero
    if ((uf & 0x7FFFFFFF) > 0x7F800000 || (ug & 0x7FFFFFFF) > 0x7F800000 ||
        !((uf | ug) << 1))
        return 0;
    int uf_sign = uf >> 31;
    int ug_sign = ug >> 31;
    // (uf is neg and ug is pos || (both are neg && uf < ug) ||
    // (both are pos && uf > ug))
    if (uf_sign > ug_sign ||
        (ug_sign == uf_sign && ((ug_sign && ug < uf) || (!ug_sign && uf < ug))))
        return 1;
    return 0;
}

/*
 * floatNegate - Return bit-level equivalent of expression -f for
 *               floating point argument f.
 *               Both the argument and result are passed as unsigned int's,
 *               but they are to be interpreted as the bit-level
 *               representations of single-precision floating point values.
 *               When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf)  // 5? ops
{
    int is_NaN = (uf & 0x7FFFFFFF) > 0x7F800000;
    // Toggle sign bit if uf is not NaN
    return is_NaN ? uf : uf ^ 0x80000000;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *               (2.0 raised to the power x) for any 32-bit integer x.
 *
 *               The unsigned value that is returned should have the
 *               identical bit representation as the single-precision
 *               floating-point number 2.0^x.
 *               If the result is too small to be represented as a denorm,
 *               return 0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x)  // 12? ops
{
    /*
     * Observe:
     *   exp = 2^8,   frac = 0     =>  2 ^ INF
     *   exp = 2^8-1, frac = 0     =>  2 ^ (128)
     *   exp = 2,     frac = 0     =>  2 ^ (-125)
     *   exp = 1,     frac = 0     =>  2 ^ (-126)
     *   exp = 0,     frac = 2^23  =>  2 ^ (-127)
     *   exp = 0,     frac = 2^22  =>  2 ^ (-128)
     *   exp = 0,     frac = 2^0   =>  2 ^ (-150)
     */
    if (x < -150)
        return 0;
    if (x <= -127)
        return 1 << (x + 127);
    if (x <= 128)
        return (x + 127) << 23;
    return 0x7F800000;  // INF;
}

/*
 * floatScale1d2 - Return bit-level equivalent of expression 0.5*f for
 *                 floating point argument f.
 *                 Both the argument and result are passed as unsigned int's,
 *                 but they are to be interpreted as the bit-level
 *                 representation of single-precision floating point values.
 *                 When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale1d2(unsigned uf)  // 12? ops
{
    int sign = uf & 0x80000000;
    int exponent = uf & 0x7F800000;
    if (exponent <= 0x800000) {
        // Round-to-even
        uf = uf + ((uf & 0x3) == 0x3);
        int uf_abs = uf ^ sign;
        uf = sign | (uf_abs >> 1);
    } else if (exponent < 0x7F800000) {
        uf = uf - 0x800000;
    }
    return uf;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *               floating point argument f.
 *               Both the argument and result are passed as unsigned int's,
 *               but they are to be interpreted as the bit-level representation
 *               of single-precision floating point values.
 *               When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf)  // 8? ops
{
    int sign = uf & 0x80000000;
    int exponent = uf & 0x7F800000;
    int exponent_is_zero = !exponent;
    if (exponent_is_zero) {
        uf = sign | (uf << 1);
    } else if (exponent != 0x7F800000) {
        uf = uf + 0x800000;
    }
    return uf;
}

/*
 * floatScale64 - Return bit-level equivalent of expression 64*f for
 *                floating point argument f.
 *                Both the argument and result are passed as unsigned int's,
 *                but they are to be interpreted as the bit-level
 *                representation of single-precision floating point values.
 *                When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 35
 *   Rating: 4
 */
unsigned floatScale64(unsigned uf)  // 15? ops
{
    int sign = uf & 0x80000000;
    int num_loop = 6;
    while (num_loop--) {
        int exponent = uf & 0x7F800000;
        int exponent_is_zero = !exponent;
        if (exponent_is_zero) {
            uf = sign | (uf << 1);
        } else if (exponent != 0x7F800000) {
            uf = uf + 0x800000;
            exponent = uf & 0x7F800000;
            // Check if grater than INF
            if (exponent == 0x7F800000) {
                uf = uf & 0xFF800000;  // clear fraction
            }
        }
    }
    return uf;
}

/*
 * floatUnsigned2Float - Return bit-level equivalent of expression (float) u
 *                       Result is returned as unsigned int, but it is to be
 *                       interpreted as the bit-level representation of a
 *                       single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatUnsigned2Float(unsigned u)  // 26? ops
{
    if (u) {
        int len_fraction = 23;
        int greatest_bit_pos = 31;
        while (!((1 << greatest_bit_pos) & u)) {
            greatest_bit_pos--;
        }
        int diff = len_fraction - greatest_bit_pos;
        int bias = 127;
        int exponent = bias + len_fraction - diff;  // 127 (bias) + 23 - diff
        if (diff >= 0) {
            u <<= diff;
        } else {
            diff = -diff;
            // GRS action: https://stackoverflow.com/questions/8981913
            int G = u & (1 << diff);
            int R = u & (1 << (diff - 1));
            int S = u << (33 - diff);
            u >>= diff;
            // ( Obvious || Round-to-even )
            u += R && (S || G);
        }
        // | sign=0 | exponent | fraction |
        u = (exponent << len_fraction) | (u & 0x7FFFFF);
    }
    return u;
}

/*
 * getByte - Extract byte n from word x
 *           Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n)  // 3 ops
{
    return (x >> (n << 3)) & 0xFF;
}

/*
 * greatestBitPos - return a mask that marks the position of the
 *                  most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4
 */

int greatestBitPos(int x)  // 30 ops
{
    // See countLeadingZero()

    int t = x;
    int num_zero = 0;

    int leading_n_zero = !(t >> 16);
    int n = leading_n_zero << 4;
    num_zero = n;
    t = t << n;

    leading_n_zero = !(t >> 24);
    n = leading_n_zero << 3;
    num_zero = num_zero + n;
    t = t << n;

    leading_n_zero = !(t >> 28);
    n = leading_n_zero << 2;
    num_zero = num_zero + n;
    t = t << n;

    leading_n_zero = !(t >> 30);
    n = leading_n_zero << 1;
    num_zero = num_zero + n;
    t = t << n;

    num_zero = num_zero + !(t >> 31) + !(t >> 30);

    // if (x != 0) return 1 << (31 - n) else return 0
    return !!x << (32 + ~num_zero);
}

int greatestBitPos_61(int x)  // 61 ops
{
    // bitReverse() -> leastBitPos() -> bitReverse()

    int hex0000FFFF = (0xFF << 8) | 0xFF;
    int hex00FF00FF = hex0000FFFF ^ (hex0000FFFF << 8);
    int hex0F0F0F0F = hex00FF00FF ^ (hex00FF00FF << 4);
    int hex33333333 = hex0F0F0F0F ^ (hex0F0F0F0F << 2);
    int hex55555555 = hex33333333 ^ (hex33333333 << 1);

    int reverse = x << 16 | ((x >> 16) & hex0000FFFF);
    reverse = (reverse & hex00FF00FF) << 8 | ((reverse >> 8) & hex00FF00FF);
    reverse = (reverse & hex0F0F0F0F) << 4 | ((reverse >> 4) & hex0F0F0F0F);
    reverse = (reverse & hex33333333) << 2 | ((reverse >> 2) & hex33333333);
    reverse = (reverse & hex55555555) << 1 | ((reverse >> 1) & hex55555555);

    // x & (x - 1) clear the least bit
    // x ^ (x & (x - 1)) get the least bit
    int rev_no_least = reverse ^ (reverse & (reverse + ~0));

    x = rev_no_least << 16 | ((rev_no_least >> 16) & hex0000FFFF);
    x = (x & hex00FF00FF) << 8 | ((x >> 8) & hex00FF00FF);
    x = (x & hex0F0F0F0F) << 4 | ((x >> 4) & hex0F0F0F0F);
    x = (x & hex33333333) << 2 | ((x >> 2) & hex33333333);
    x = (x & hex55555555) << 1 | ((x >> 1) & hex55555555);

    return x;
}

/*
 * howManyBits - return the minimum number of bits required to represent x in
 *               two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x)  // 34 ops
{
    /*
     * Trivial method:
     * Goal: Return 32 - (max(leading zeros, leading ones) - 1)
     *
     * return 33 - maximumOfTwo(countLeadingZero(x), countLeadingZero(~x));
     * Done! But this method needs 25 + 26 + 13 + 2 = 66 ops
     *
     * We can use the same concept of counting leading zero to implement this
     * function. See countLeadingZero()
     */

    int num_bits_redundant = 0;

    // value = 11......11 if the leading 17 bits are the same else 00......00
    int x_as_16_bit = x << 16 >> 16;
    int leading_n_same = !(x_as_16_bit ^ x);
    int n = leading_n_same << 4;
    num_bits_redundant = num_bits_redundant + n;
    x = x << n;

    // value = 11......11 if the leading 9 bits are the same else 00......00
    leading_n_same = !((x << 8 >> 8) ^ x);
    n = leading_n_same << 3;
    num_bits_redundant = num_bits_redundant + n;
    x = x << n;

    // value = 11......11 if the leading 5 bits are the same else 00......00
    leading_n_same = !((x << 4 >> 4) ^ x);
    n = leading_n_same << 2;
    num_bits_redundant = num_bits_redundant + n;
    x = x << n;

    // value = 11......11 if the leading 3 bits are the same else 00......00
    leading_n_same = !((x << 2 >> 2) ^ x);
    n = leading_n_same << 1;
    num_bits_redundant = num_bits_redundant + n;
    x = x << n;

    // value = 11......11 if the leading 2 bits are the same else 00......00
    leading_n_same = !((x << 1 >> 1) ^ x);
    num_bits_redundant = num_bits_redundant + leading_n_same;

    // Return 32 - num_bits_redundant
    return 33 + ~num_bits_redundant;
}

/*
 * implication - return x -> y in propositional logic - 0 for false,
 *               1 for true
 *   Example: implication(1, 1) = 1
 *            implication(1, 0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y)  // 2 ops
{
    return (!x) | y;
}

/*
 * intLog2 - return floor(log base 2 of x), where x > 0
 *   Example: intLog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int intLog2(int x)  // 24 ops
{
    // See countLeadingZero()

    int num_zero = 0;

    int leading_n_zero = !(x >> 16);
    int n = leading_n_zero << 4;  // n = 16 if leading_n_zero is true
    num_zero = n;
    x = x << n;

    leading_n_zero = !(x >> 24);
    n = leading_n_zero << 3;
    num_zero = num_zero + n;
    x = x << n;

    leading_n_zero = !(x >> 28);
    n = leading_n_zero << 2;
    num_zero = num_zero + n;
    x = x << n;

    leading_n_zero = !(x >> 30);
    n = leading_n_zero << 1;
    num_zero = num_zero + n;
    x = x << n;

    // Since x > 0, no need to check if bit 31 and bit 30 are both 0
    num_zero = num_zero + !(x >> 31);

    // Return 31 - num_zero
    return 32 + ~num_zero;
}

/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters
 *                '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x)  // 8 ops
{
    // x - 0x30 >= 0 && x - 0x39 <= 0
    // x - 0x30 >= 0 && x - 0x3A < 0 , easier to check if a number is negative
    // (!((x - 0x30) >> 31)) & ((x - 0x3A) >> 31);
    return (!((x + ~0x2F) >> 31)) & ((x + ~0x39) >> 31);
}

/*
 * isEqual - return 1 if x == y, and 0 otherwise
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y)  // 2 ops
{
    return !(x ^ y);
}

/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y)  // 10 ops
{
    // See isGreater_12()
    return (((y & ~x) | ~((x ^ y) | (x + ~y))) >> 31) & 1;
}

int isGreater_12(int x, int y)  // 12 ops
{
    // (x is +,0 && y is -) || (x, y have same sign && (x - y) > 0) <- De Morgan
    return ((y >> 31) & !(x >> 31)) | !(((x ^ y) >> 31) | ((x + ~y) >> 31));
}

/*
 * isLess - if x < y  then return 1, else return 0
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y)  // 10 ops
{
    // See isGreater()

    // Return isGreater(y, x)
    return (((x & ~y) | ~((x ^ y) | (y + ~x))) >> 31) & 1;
}

/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y)  // 9 ops
{
    // See isGreater() + De Morgan's law

    // Return !isGreater(x, y)
    return (((~y | x) & ((x ^ y) | (x + ~y))) >> 31) & 1;
}

int isLessOrEqual_11(int x, int y)  // 11 ops
{
    // See isLessOrEqual_13()
    return (((x & ~y) | ~((x ^ y) | (y + ~x + 1))) >> 31) & 1;
}

int isLessOrEqual_13(int x, int y)  // 13 ops
{
    // (x is - && y is +,0) || (x, y have same sign && (y - x) >= 0)
    return ((x >> 31) & !(y >> 31)) | !(((x ^ y) >> 31) | ((y + ~x + 1) >> 31));
}

/*
 * isNegative - return 1 if x < 0, return 0 otherwise
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x)  // 2 ops
{
    return (x >> 31) & 1;
}

/*
 * isNonNegative - return 1 if x >= 0, return 0 otherwise
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNonNegative(int x)  // 2 ops
{
    return !(x >> 31);
}

/*
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int isNonZero(int x)  // 5 ops
{
    // Sign bit of both zero and two's complement of zero is 0, see Bang()
    return ((x | (~x + 1)) >> 31) & 1;
}

/*
 * isNotEqual - return 0 if x == y, and 1 otherwise
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y)  // 3 ops
{
    return !!(x ^ y);
}

/*
 * isPallindrome - Return 1 if bit pattern in x is equal to its mirror image
 *   Example: isPallindrome(0x01234567E6AC2480) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 45
 *   Rating: 4
 */
int isPallindrome(int x)  // faster? 36 ops
{
    // See bitReverse()

    int hex0000FFFF = (0xFF << 8) | 0xFF;
    int hex00FF00FF = hex0000FFFF ^ (hex0000FFFF << 8);
    int hex0F0F0F0F = hex00FF00FF ^ (hex00FF00FF << 4);
    int hex33333333 = hex0F0F0F0F ^ (hex0F0F0F0F << 2);
    int hex55555555 = hex33333333 ^ (hex33333333 << 1);
    int reverse = x << 16 | ((x >> 16) & hex0000FFFF);
    reverse = (reverse & hex00FF00FF) << 8 | ((reverse >> 8) & hex00FF00FF);
    reverse = (reverse & hex0F0F0F0F) << 4 | ((reverse >> 4) & hex0F0F0F0F);
    reverse = (reverse & hex33333333) << 2 | ((reverse >> 2) & hex33333333);
    reverse = (reverse & hex55555555) << 1 | ((reverse >> 1) & hex55555555);
    return !(x ^ reverse);
}

/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int isPositive(int x)  // 4 ops
{
    return !(x >> 31 | !x);  // isPositive_5() + De Morgan's law
}

int isPositive_5(int x)  // 5 ops
{
    return (!(x >> 31)) & (!!x);  // nonnegative and not zero
}

/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x)  // 8 ops
{
    // (x & (x-1)) == 0 && x > 0
    // !(x & (x + ~0)) & !(x >> 31) & !!x  11 ops
    // Apply De Morgan's law
    return !((x & (x + ~0)) | (x >> 31) | !x);
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x)  // 7 ops
{
    // See isTmax_8() + De Morgan's law
    int x_plus_1 = x + 1;
    return !(~(x ^ x_plus_1) | !~x);
}

int isTmax_8(int x)  // 8 ops
{
    // Observe: ~(x ^ (x+1)) only equal to 0 when x is tmax or -1
    int x_plus_1 = x + 1;
    // ~(x ^ (x+1)) equal to 0 && x is not -1
    return !~(x ^ x_plus_1) & !!~x;
}

int isTmax_shift(int x)  // Can't use shift
{
    int tmax = (0 << 31);
    return !(x ^ tmax);
}

/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x)  // 7 ops
{
    // See isTmax()
    int x_minus_1 = x + ~0;
    return !(~(x ^ x_minus_1) | !x);
}

int isTmin_shift(int x)  // Can't use shift
{
    int tmin = 1 << 31;
    return !(x ^ tmin);
}

/*
 * isZero - returns 1 if x == 0, and 0 otherwise
 *   Examples: isZero(5) = 0, isZero(0) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int isZero(int x)  // 1 ops
{
    return !x;
}

/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x)  // 4 ops
{
    int x_no_least_bit = x & (x + ~0);
    return x ^ x_no_least_bit;
}

/*
 * leftBitCount - returns count of number of consective 1's in
 *                left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x)  // 26 ops
{
    // Convert to counting leading zeros, see countLeadingZero()
    x = ~x;

    int num_zero = 0;

    int leading_n_zero = !(x >> 16);
    int n = leading_n_zero << 4;
    num_zero = n;
    x = x << n;

    leading_n_zero = !(x >> 24);
    n = leading_n_zero << 3;
    num_zero = num_zero + n;
    x = x << n;

    leading_n_zero = !(x >> 28);
    n = leading_n_zero << 2;
    num_zero = num_zero + n;
    x = x << n;

    leading_n_zero = !(x >> 30);
    n = leading_n_zero << 1;
    num_zero = num_zero + n;
    x = x << n;

    num_zero = num_zero + !(x >> 31) + !(x >> 30);

    return num_zero;
}

/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x)  // 6 ops
{
    // See bang()
    int x_twos_comp = ~x + 1;
    return (((x | x_twos_comp) >> 31) ^ 1) & 1;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *                Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n)  // 6 ops
{
    int mask = ~(1 << 31 >> n << 1);
    return (x >> n) & mask;
}

int logicalShift_9(int x, int n)  // 9 ops
{
    int sign = (x >> 31) & 1;
    // Clear sign bit to 0 and set it after shift
    // return ((x ^ (sign << 31)) >> n) | (sign << (31 - n));
    return ((x ^ (sign << 31)) >> n) | (sign << (32 + ~n));
}

/*
 * maximumOfTwo - compute the maximum of two integers without branching
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int maximumOfTwo(int x, int y)  // 13 ops
{
    // See isGreater() and conditional()
    int x_is_greater_mask = ((y & ~x) | ~((x ^ y) | (x + ~y))) >> 31;
    return (x_is_greater_mask & x) | (~x_is_greater_mask & y);
}

/*
 * minimumOfTwo - compute the minimum of two integers without branching
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int minimumOfTwo(int x, int y)  // 13 ops
{
    // see isLess() and conditional()
    int x_is_less_mask = ((x & ~y) | ~((x ^ y) | (y + ~x))) >> 31;
    return (x_is_less_mask & x) | (~x_is_less_mask & y);
}

/*
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void)  // 1 ops
{
    return ~0;
}

/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *                   Should exactly duplicate effect of C expression (x*5/8),
 *                   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x)  // 6 ops
{
    int x_mul_5 = x + (x << 2);
    return (x_mul_5 + ((x_mul_5 >> 31) & 7)) >> 3;
}

/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x)  // 2 ops
{
    return ~x + 1;
}

/*
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void)  // 4 ops
{
    int hexAAAA = 0xAA | (0xAA << 8);
    return hexAAAA | (hexAAAA << 16);
}

/*
 * remainderPower2 - Compute x%(2^n), for 0 <= n <= 30
 *                   Negative arguments should yield negative remainders
 *   Examples: remainderPower2(15, 2) = 3, remainderPower2(-35, 3) = -3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int remainderPower2(int x, int n)  // 10 ops
{
    /*
     * Observe:
     * For nonnegative x, return x & (2^n - 1)
     * For negative x and remainder is not 0,
     * return x & (2^n - 1) with upper 32 - n bits set to 1
     */

    int ones = ~0;  // All bits are set to 1 or decimal -1

    int remainder_mask = (1 << n) + ones;
    int remainder = x & remainder_mask;

    int sign_mask = x >> 31 << n;
    int remainder_is_not_0_mask = !remainder + ones;

    return (sign_mask & remainder_is_not_0_mask) | remainder;
}

int remainderPower2_16(int x, int n)  // faster, 16 ops
{
    int x_sign = x >> 31;
    int x_abs = (x ^ x_sign) + (x_sign & 1);
    int remainder_mask = (1 << n) + ~0;
    int remainder_abs = x_abs & remainder_mask;
    int remainder_sign = (x & (!!remainder_abs << 31)) >> 31;

    // Return remainder_abs two's complement if remainder should be negative
    return (remainder_abs ^ remainder_sign) + (remainder_sign & 1);
}

/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *                      Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678, 1, 0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c)  // 6 ops
{
    int n_dis = n << 3;
    int clear_mask = 0xFF << n_dis;
    int new_mask = c << n_dis;
    return (x & ~clear_mask) | new_mask;
}

/*
 * rotateLeft - Rotate x to the left by n
 *              Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321, 4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3
 */
int rotateLeft(int x, int n)  // 9 ops
{
    int keep_mask = (1 << n) + ~0;                // (1 << n) - 1
    int fall_off = (x >> (33 + ~n)) & keep_mask;  // 33 + ~n => 32 - n
    return (x << n) | fall_off;
}

/*
 * rotateRight - Rotate x to the right by n
 *               Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321, 4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3
 */
int rotateRight(int x, int n)  // change neg to pos maybe faster? 12 ops
{
    int keep_mask = (1 << n) + ~0;
    int shift_dis = 33 + ~n;  // 32 - n
    int fall_off = (x & keep_mask) << shift_dis;
    int clear_mask = keep_mask << shift_dis;
    return ((x >> n) & ~clear_mask) | fall_off;
}

/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000, 0x40000000) = 0x7fffffff
 *             satAdd(0x80000000, 0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y)  // 13 ops
{
    int sum = x + y;
    int no_overflow_mask = ((x ^ y) | ~(sum ^ x)) >> 31;
    int tmin = 1 << 31;
    int sum_is_neg = sum >> 31;
    // return (no_overflow_mask & sum) |
    //     (~no_overflow_mask & (sum < 0 ? tmax : tmin));
    return (no_overflow_mask & sum) | (~no_overflow_mask & (tmin ^ sum_is_neg));
}

/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x80000001) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x)  // 10 ops
{
    int x_mul_2 = x << 1;
    int overflow_mask = (x_mul_2 ^ x) >> 31;
    int tmin = 1 << 31;
    int x_mul_2_is_neg = x_mul_2 >> 31;
    return (~overflow_mask & x_mul_2) |
           (overflow_mask & (tmin ^ (x_mul_2_is_neg)));
}

/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *   Examples: satMul3(0x10000000) = 0x30000000
 *             satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *             satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *              satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *             satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int satMul3(int x)  // 14 ops
{
    int x_mul_2 = x << 1;
    int x_mul_3 = x_mul_2 + x;
    int overflow_mask = ((x_mul_2 ^ x) | (x_mul_3 ^ x)) >> 31;
    int tmax = ~(1 << 31);
    int x_is_neg = x >> 31;
    return (~overflow_mask & x_mul_3) | (overflow_mask & (tmax ^ (x_is_neg)));
}

/*
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *   Examples: sign(130) = 1
 *             sign(-23) = -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 2
 */
int sign(int x)  // 3 ops
{
    return (x >> 31) | !!x;
}

/*
 * signMag2TwosComp - Convert from sign-magnitude to two's complement
 *                    where the MSB is the sign bit
 *   Example: signMag2TwosComp(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int signMag2TwosComp(int x)  // 6 ops
{
    // See twosComp2SignMag()

    int neg_mask = x >> 31;
    int x_sign = neg_mask << 31;
    int x_without_sign = x ^ x_sign;

    int x_twos_comp_if_neg = (x_without_sign ^ neg_mask) + (neg_mask & 1);
    return x_twos_comp_if_neg;
}

int signMag2TwosComp_15(int x)  // faster, 15 ops
{
    int no_sign_bit = x << 1;         // Since !(x << 1) has warning
    x = x & ~(!(no_sign_bit) << 31);  // Convert -0 to +0
    int neg_mask = x >> 31;
    int x_abs = x & ~(1 << 31);
    return (neg_mask & (~x_abs + 1)) | (~neg_mask & x);
}

/*
 * specialBits - return bit pattern 0xffca3fff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 3
 *   Rating: 1
 */
int specialBits(void)  // 2 ops
{
    return ~(0xD7 << 14);
}

/*
 * subtractionOK - Determine if can compute x-y without overflow
 *   Example: subtractionOK(0x80000000, 0x80000000) = 1,
 *            subtractionOK(0x80000000, 0x70000000) = 0,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subtractionOK(int x, int y)  // 8 ops
{
    /*
     * Observe:
     * Return 0 (overflow) when (+,0) - (-) => (-) or (-) - (+,0) => (+,0),
     * that is, sign of x and y are different and sign of x and result are
     * different.
     *
     * See addOK()
     */

    int diff = x + ~y + 1;
    return !(((x ^ y) & (x ^ diff)) >> 31);
}

int subtractionOK_13(int x, int y)  // 13 ops
{
    /*
     * Reuse addOK(x, -y). However, since -Tmin equals to Tmin in c,
     * the result of subtraction(x, Tmin) and addOK(x, -Tmin)
     * should be the opposite.
     *
     * For example, if addOK(x, Tmin) returns ok, then addOK(x, -Tmin) is
     * equals to addOK(x, Tmin) and will return ok with the result
     * x + Tmin, but the value we want to represent is x - Tmin.
     */

    int y_neg = ~y + 1;
    int sum = x + y_neg;

    // See addOK()
    int x_add_y_neg_is_OK = (((x ^ y_neg) | ~(sum ^ x)) >> 31) & 1;

    int tmin = 1 << 31;
    int y_is_Tmin = !(y ^ tmin);

    // Toggle the result if y is Tmin
    return x_add_y_neg_is_OK ^ y_is_Tmin;
}

/*
 * thirdBits - return word with every third bit (starting from the LSB)
 *             set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void)  // 4 ops
{
    // 0x49249249
    int hex9249 = (0x92 << 8) | 0x49;
    return (hex9249 << 15) | hex9249;
}

int thirdBits_6(void)  // 6 ops
{
    return (0x49 << 24) | (0x24 << 16) | (0x92 << 8) | 0x49;
}

/*
 * tmax - return maximum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void)  // 2 ops
{
    return ~(1 << 31);
}

/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void)  // 1 ops
{
    return 1 << 31;
}

/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *                   avoiding errors due to overflow
 *   Examples: trueFiveEighths(11) = 6
 *             trueFiveEighths(-9) = -5
 *             trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 4
 */
int trueFiveEighths(int x)  // 11 op
{
    // See trueThreeFourths() for the concept

    int x_div_8 = x >> 3;
    int remainder = x & 0x7;  // The remainder of x/8

    int x_div_8_mul_5 = (x_div_8 << 2) + x_div_8;

    int x_is_neg = x >> 31;
    int remainder_mul_5 = (remainder << 2) + remainder;
    int carry = (remainder_mul_5 + (x_is_neg & 0x7)) >> 3;

    return x_div_8_mul_5 + carry;
}

/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *                    avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)  // 11 op
{
    /*
     * Since we have to avoid errors due to overflow, we can calculate
     * the result of x/4 with remainder first and then calculate the
     * result of 3*(x/4) + 3*remainder.
     *
     * For negative x, since the right shift perform division that rounds
     * towards negative infinity, we must add one to it if there is any
     * remainder after division so that the result is rounding towards 0.
     */

    int x_div_4 = x >> 2;
    int remainder = x & 0x3;  // The remainder of x/4

    int x_div_4_mul_3 = (x_div_4 << 1) + x_div_4;

    int x_is_neg = x >> 31;
    int remainder_mul_3 = (remainder << 1) + remainder;
    int carry = (remainder_mul_3 + (x_is_neg & 0x3)) >> 2;

    return x_div_4_mul_3 + carry;
}

/*
 * twosComp2SignMag - Convert from two's complement to sign-magnitude
 *                    where the MSB is the sign bit
 *                    You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x)  // 6 ops
{
    // See absVal()

    int neg_mask = x >> 31;
    int x_sign = neg_mask << 31;
    int x_abs = (x ^ neg_mask) + (neg_mask & 1);

    return x_sign | x_abs;
}

/*
 * upperBits - pads n upper bits with 1's
 *             You may assume 0 <= n <= 32
 *   Example: upperBits(4) = 0xF0000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 1
 */
int upperBits(int n)  // 7 ops
{
    /*
     * If directly return ~0 << (32 - n), the result is only correct when
     * 1 <= n <= 32.
     * However, if n is 0, the return value should be 0 and we will compute
     * ~0 << (32 - 0), that is, ~0 << 32 which behavior is undefined.
     * Therefore, we can mask the shift amount with 0x0 if n is 0 to avoid
     * this undefined behavior.
     */

    // value = 11......11 if n != 0 else 00......00
    int n_is_not_0_mask = !n + ~0;
    return n_is_not_0_mask << ((33 + ~n) & n_is_not_0_mask);
}

int upperBits_undefined_behavior(int n)  // 6 ops
{
    /* INTEGER CODING RULES:
     * You may assume that your machine:
     * 3. Has unpredictable behavior when shifting if the shift amount
     *    is less than 0 or greater than 31.
     */

    // >> -1 is has unpredictable behavior! (when n == 0)
    return (!!n << 31) >> (n + ~0);
}

int upperBits_9(int n)  // 9 ops
{
    // return n ? (1 << 31) >> (n-1) : 0;
    int n_is_0 = (!n << 31) >> 31;
    return ~n_is_0 & ((1 << 31) >> (n + ~0));
}
