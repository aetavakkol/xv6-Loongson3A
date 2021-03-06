
#ifndef _MATHOP_H
#define _MATHOP_H

#define LOWBITS(ord)			((1 << (ord)) - 1)

#define DIV_ROUNDDOWN(x, d)		((x) / (d))
#define DIV_ROUNDUP(x, d)		DIV_ROUNDDOWN((x) + (d) - 1, d)

#define ROUNDDOWN(x, d)			(DIV_ROUNDDOWN(x, d) * (d))
#define ROUNDUP(x, d)			(DIV_ROUNDUP(x, d) * (d))

#define RSHIFT_ROUNDDOWN(x, ord)	(((unsigned long)x) >> (ord))
#define RSHIFT_ROUNDUP(x, ord)		RSHIFT_ROUNDDOWN((x) + LOWBITS(ord), ord)

#define POW2_ROUNDDOWN(x, ord)		(((unsigned long)x) & ~LOWBITS(ord))
#define POW2_ROUNDUP(x, ord)		POW2_ROUNDDOWN((x) + LOWBITS(ord), ord)

#define ROUNDUP_TO_POW2(x)		__roundup_to_pow2(x)

#include <asm/bitops.h>

static inline unsigned long __roundup_to_pow2(unsigned long x)
{
	return 1ULL << fls(x - 1);
}

#endif
