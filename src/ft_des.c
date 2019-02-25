/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 15:12:44 by marvin            #+#    #+#             */
/*   Updated: 2019/02/25 17:20:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "libft.h"
#include <inttypes.h>

/* Key Permutation 1 */
int32_t pc_1[] = {57, 49,  41, 33,  25,  17,  9,
			   1, 58,  50, 42,  34,  26, 18,
			  10,  2,  59, 51,  43,  35, 27,
			  19, 11,   3, 60,  52,  44, 36,
			  63, 55,  47, 39,  31,  23, 15,
			   7, 62,  54, 46,  38,  30, 22,
			  14,  6,  61, 53,  45,  37, 29,
			  21, 13,   5, 28,  20,  12,  4};

/* Key Permutation 2 */
int32_t pc_2[] = {14, 17, 11, 24,  1,  5,
			   3, 28, 15,  6, 21, 10,
			  23, 19, 12,  4, 26,  8,
			  16,  7, 27, 20, 13,  2,
			  41, 52, 31, 37, 47, 55,
			  30, 40, 51, 45, 33, 48,
			  44, 49, 39, 56, 34, 53,
			  46, 42, 50, 36, 29, 32};

/* Initial Message Permutation */
int32_t ip[] = {58, 50, 42, 34, 26, 18, 10, 2,
			60, 52, 44, 36, 28, 20, 12, 4,
			62, 54, 46, 38, 30, 22, 14, 6,
			64, 56, 48, 40, 32, 24, 16, 8,
			57, 49, 41, 33, 25, 17,  9, 1,
			59, 51, 43, 35, 27, 19, 11, 3,
			61, 53, 45, 37, 29, 21, 13, 5,
			63, 55, 47, 39, 31, 23, 15, 7};

/* Message Expansion E */
int32_t mex[] =  {32,  1,  2,  3,  4,  5,
			   4,  5,  6,  7,  8,  9,
			   8,  9, 10, 11, 12, 13,
			  12, 13, 14, 15, 16, 17,
			  16, 17, 18, 19, 20, 21,
			  20, 21, 22, 23, 24, 25,
			  24, 25, 26, 27, 28, 29,
			  28, 29, 30, 31, 32,  1};

/* KeySet Shift */
int32_t ks_shift[] = {-1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

/* Address Boxes */
int32_t s1[] = {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
				 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
				 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
				 15, 12, 8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13};

int32_t s2[] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
				 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
				 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
				13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

int32_t s3[] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
				13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
				13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
				 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

int32_t s4[] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
				13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
				10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
				 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};

int32_t s5[] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
				14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
				 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
				11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

int32_t s6[] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
				10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
				 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
				 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};

int32_t s7[] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
				13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
				 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
				 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12};

int32_t s8[] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
				 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
				 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
				 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};

/* Right Sub Message Permutation */
int32_t rp[] = {16,  7, 20, 21,
				29, 12, 28, 17,
				 1, 15, 23, 26,
				 5, 18, 31, 10,
				 2,  8, 24, 14,
				 2, 27,  3,  9,
				 9, 13, 30,  6,
				 2, 11,  4, 25};

/* Final Message Permutation */
int32_t fp[] = {40,  8, 48, 16, 56, 24, 64, 32,
				39,  7, 47, 15, 55, 23, 63, 31,
				38,  6, 46, 14, 54, 22, 62, 30,
				37,  5, 45, 13, 53, 21, 61, 29,
				36,  4, 44, 12, 52, 20, 60, 28,
				35,  3, 43, 11, 51, 19, 59, 27,
				34,  2, 42, 10, 50, 18, 58, 26,
				33,  1, 41,  9, 49, 17, 57, 25};

void		gen_subkeys(uint8_t *key, t_keyset *ks)
{
	int32_t		i;
	int32_t		j;
	int32_t		shift_size;
	uint8_t		shift_byte;
	uint8_t		shift_bits;

	ft_memset(ks[0].k, 0, sizeof(ks[0].k));

/* First permutation */
	i = 0;
	while (i < 8)
	{
		shift_size = pc_1[i] - 1;
		shift_byte = 0x80 >> (shift_size % 8);
		shift_byte &= key[shift_size / 8];
		shift_byte <<= shift_size % 8;
		ks[0].k[i / 8] |= (shift_byte >> (i % 8));
		++i;
	}

/* Creating subkeys */
	i = 0;
	while (i < 3)
	{
		ks[0].c[i] = ks[0].k[i];
		++i;
	}
	ks[0].c[3] = ks[0].k[3] & 0xF0;

	j = 0;
	while (j < 3)
	{
		ks[0].d[j] = (ks[0].k[i] & 0x0F) << 4;
		ks[0].d[j] |= (ks[0].k[++i] & 0xF0) >> 4;
		++j;
	}
	ks[0].d[3] = (ks[0].k[6] & 0x0F) << 4;

/* Splitting subkeys in C and D */
	i = 1;
	while (i < 17)
	{
		j = 0;
		while (j < 4)
		{
			ks[i].c[j] = ks[i - 1].c[j];
			ks[i].d[j] = ks[i - 1].d[j];
		}

		shift_size = ks_shift[i];
		shift_byte = (shift_size == 1) ? 0x80 : 0xC0;

/* Shifting C */
		j = 0;
		while (j < 3)
		{
			shift_bits = shift_byte & ks[i].c[j + 1];
			ks[i].c[j] <<= shift_size;
			ks[i].c[j] |= (shift_bits >> (8 - shift_size));
			++j;
		}
		shift_bits = shift_byte & ks[i].c[0];
		ks[i].c[3] <<= shift_size;
		ks[i].c[3] |= (shift_bits >> (4 - shift_size));

/* Shifting D */
		j = 0;
		while (j < 3)
		{
			shift_bits = shift_byte & ks[i].d[j + 1];
			ks[i].d[j] <<= shift_size;
			ks[i].d[j] |= (shift_bits >> (8 - shift_size));
			++j;
		}
		shift_bits = shift_byte & ks[i].d[0];
		ks[i].d[3] <<= shift_size;
		ks[i].d[3] |= (shift_bits >> (4 - shift_size));

/* Last permutation */
		j = 0;
		while (j < 48)
		{
			shift_size = pc_2[j];
			if (shift_size <= 28)
			{
				shift_byte = 0x80 >> ((shift_size - 1) % 8);
				shift_byte &= ks[i].c[(shift_size - 1) / 8];
				shift_byte <<= ((shift_size - 1) % 8);
			}
			else
			{
				shift_byte = 0x80 >> ((shift_size - 29) % 8);
				shift_byte &= ks[i].d[(shift_size - 29) / 8];
				shift_byte <<= ((shift_size - 29) % 8);
			}
			ks[i].k[j / 8] |= (shift_byte >> j % 8);
		}
	}
}

void		process_message(uint8_t *msg, uint8_t *enc, t_keyset *ks, int mode)
{
	int32_t		i;
	int32_t		k;
	int32_t		shift_size;
	uint8_t		shift_byte;
	uint8_t		init_perm[8];
	uint8_t		l[4];
	uint8_t		r[4];
	uint8_t		ln[4];
	uint8_t		rn[4];
	uint8_t		er[6];
	uint8_t		ser[4];
	int32_t		key_index;
	uint8_t		row;
	uint8_t		column;
	uint8_t		pep[8]; /* pre-end-permutation */

	ft_memset(init_perm, 0, 8);
	ft_memset(enc, 0, 8); /* eeuh... sure ?? */
	/* pretty sure this is bad */

	/* Initial Message Permutation */
	i = 0;
	while (i < 64)
	{
		shift_size = ip[i] - 1;
		shift_byte = 0x80 >> (shift_size % 8);
		shift_byte &= msg[shift_size / 8];
		shift_byte <<= shift_size % 8;
		init_perm[i / 8] |= (shift_byte >> i % 8);
		++i;
	}

	/* Split Message in Two: Left Right */
	i = 0;
	while (i < 4)
	{
		l[i] = init_perm[i];
		r[i] = init_perm[i + 4];
		++i;
	}

	/* Ln = Rn-1 */
	/* Rn = Ln-1 + f(Rn-1,Kn) */
	k = 0;
	while (k < 16)
	{
		ft_memcpy(ln, r, 4);
		ft_memset(er, 0, 6);

		i = 0;
		while (i < 48)
		{
			shift_size = mex[i] - 1;
			shift_byte = 0x80 >> (shift_size % 8);
			shift_byte &= r[shift_size / 8];
			shift_byte <<= shift_size % 8;
			er[i / 8] |= shift_byte >> i % 8;
		}

		if (mode == DECRYPTION_MODE)
			key_index = 17 - k;
		else
			key_index = k;

		i = 0;
		while (i < 6)
		{
			er[i] ^= ks[key_index].k[i];
			++i;
		}

		i = 0;
		while (i < 4)
		{
			ser[i] = 0;
			++i;
		}

		/* 0000 0000 0000 0000 0000 0000 */
		/* rccc crrc cccr rccc crrc cccr */

		/* Row: i */
		/* Column: j */

		/* Byte 1 */
		row = 0;
		row |= ((er[0] & 0x80) >> 6);
		row |= ((er[0] & 0x04) >> 2);

		column = 0;
		column |= ((er[0] & 0x78) >> 3);

		ser[0] |= ((uint8_t)s1[row * 16 + column] << 4);

		row = 0;
		row |= ((er[0] & 0x02));
		row |= ((er[1] & 0x10) >> 4);

		column = 0;
		column |= ((er[0] & 0x01) << 3);
		column |= ((er[1] & 0xE0) >> 5);

		ser[0] |= ((uint8_t)s2[row * 16 + column]);

		/* Byte 2 */
		row = 0;
		row |= ((er[1] & 0x8) >> 2);
		row |= ((er[2] & 0x40) >> 6);

		column = 0;
		column |= ((er[1] & 0x07) << 1);
		column |= ((er[2] & 0x80) >> 7);

		ser[1] |= ((uint8_t)s3[row * 16 + column] << 4);

		row = 0;
		row |= ((er[2] & 0x20) >> 4);
		row |= (er[2] & 0x01);

		column = 0;
		column |= ((er[2] & 0x1E) >> 1);

		ser[1] |= (uint8_t)s4[row * 16 + column];

		/* Byte 3 */
		row = 0;
		row |= ((er[3] & 0x80) >> 6);
		row |= ((er[3] & 0x04) >> 2);

		column = 0;
		column |= ((er[3] & 0x78) >> 3);

		ser[2] |= ((uint8_t)s5[row * 16 + column] << 4);

		row = 0;
		row |= (er[3] & 0x02);
		row |= ((er[4] & 0x10) >> 4);

		column = 0;
		column |= ((er[3] & 0x01) << 3);
		column |= ((er[4] & 0xE0) >> 5);

		ser[2] |= (uint8_t)s6[row * 16 + column];

		/* Byte 4 */
		row = 0;
		row |= ((er[4] & 0x08) >> 2);
		row |= ((er[5] & 0x40) >> 6);

		column = 0;
		column |= ((er[4] & 0x07) << 1);
		column |= ((er[5] & 0x80) >> 7);

		ser[3] |= ((uint8_t)s7[row * 16 + column] << 4);

		row = 0;
		row |= ((er[5] & 0x20) >> 4);
		row |= (er[5] & 0x01);

		column = 0;
		column |= ((er[5] & 0x1E) >> 1);

		ser[3] |= (uint8_t)s8[row * 16 + column];

		ft_memset(rn, 0, sizeof(rn));

		i = 0;
		while (i < 32)
		{
			shift_size = rp[i] - 1;
			shift_byte = 0x80 >> (shift_size % 8);
			shift_byte &= ser[shift_size / 8];
			shift_byte <<= (shift_size % 8);
			rn[i / 8] = (shift_byte >> i % 8);
			++i;
		}

		i = 0;
		while (i < 4)
		{
			rn[i] ^= l[i];
			++i;
		}

		i = 0;
		while (i < 4)
		{
			l[i] = ln[i];
			r[i] = rn[i];
		}

		++k;
	}

	i = 0;
	while (i < 4)
	{
		pep[i] = r[i];
		pep[i + 4] = l[i];
	}

	i = 0;
	while (i < 64)
	{
		shift_size = fp[i] - 1;
		shift_byte = 0x80 >> (shift_size % 8);
		shift_byte &= pep[shift_size / 8];
		shift_byte <<= (shift_size % 8);
		enc[i / 8] |= (shift_byte > i % 8);
	}
}
