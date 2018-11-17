/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:50:42 by lfabbro           #+#    #+#             */
/*   Updated: 2018/10/04 17:02:09 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	md5_transform_round_one(uint32_t *regz, uint32_t x[16])
{
	FF(regz[A], regz[B], regz[C], regz[D], x[0], S11, 0xd76aa478);
	FF(regz[D], regz[A], regz[B], regz[C], x[1], S12, 0xe8c7b756);
	FF(regz[C], regz[D], regz[A], regz[B], x[2], S13, 0x242070db);
	FF(regz[B], regz[C], regz[D], regz[A], x[3], S14, 0xc1bdceee);
	FF(regz[A], regz[B], regz[C], regz[D], x[4], S11, 0xf57c0faf);
	FF(regz[D], regz[A], regz[B], regz[C], x[5], S12, 0x4787c62a);
	FF(regz[C], regz[D], regz[A], regz[B], x[6], S13, 0xa8304613);
	FF(regz[B], regz[C], regz[D], regz[A], x[7], S14, 0xfd469501);
	FF(regz[A], regz[B], regz[C], regz[D], x[8], S11, 0x698098d8);
	FF(regz[D], regz[A], regz[B], regz[C], x[9], S12, 0x8b44f7af);
	FF(regz[C], regz[D], regz[A], regz[B], x[10], S13, 0xffff5bb1);
	FF(regz[B], regz[C], regz[D], regz[A], x[11], S14, 0x895cd7be);
	FF(regz[A], regz[B], regz[C], regz[D], x[12], S11, 0x6b901122);
	FF(regz[D], regz[A], regz[B], regz[C], x[13], S12, 0xfd987193);
	FF(regz[C], regz[D], regz[A], regz[B], x[14], S13, 0xa679438e);
	FF(regz[B], regz[C], regz[D], regz[A], x[15], S14, 0x49b40821);
}

void	md5_transform_round_two(uint32_t *regz, uint32_t x[16])
{
	GG(regz[A], regz[B], regz[C], regz[D], x[1], S21, 0xf61e2562);
	GG(regz[D], regz[A], regz[B], regz[C], x[6], S22, 0xc040b340);
	GG(regz[C], regz[D], regz[A], regz[B], x[11], S23, 0x265e5a51);
	GG(regz[B], regz[C], regz[D], regz[A], x[0], S24, 0xe9b6c7aa);
	GG(regz[A], regz[B], regz[C], regz[D], x[5], S21, 0xd62f105d);
	GG(regz[D], regz[A], regz[B], regz[C], x[10], S22, 0x02441453);
	GG(regz[C], regz[D], regz[A], regz[B], x[15], S23, 0xd8a1e681);
	GG(regz[B], regz[C], regz[D], regz[A], x[4], S24, 0xe7d3fbc8);
	GG(regz[A], regz[B], regz[C], regz[D], x[9], S21, 0x21e1cde6);
	GG(regz[D], regz[A], regz[B], regz[C], x[14], S22, 0xc33707d6);
	GG(regz[C], regz[D], regz[A], regz[B], x[3], S23, 0xf4d50d87);
	GG(regz[B], regz[C], regz[D], regz[A], x[8], S24, 0x455a14ed);
	GG(regz[A], regz[B], regz[C], regz[D], x[13], S21, 0xa9e3e905);
	GG(regz[D], regz[A], regz[B], regz[C], x[2], S22, 0xfcefa3f8);
	GG(regz[C], regz[D], regz[A], regz[B], x[7], S23, 0x676f02d9);
	GG(regz[B], regz[C], regz[D], regz[A], x[12], S24, 0x8d2a4c8a);
}

void	md5_transform_round_three(uint32_t *regz, uint32_t x[16])
{
	HH(regz[A], regz[B], regz[C], regz[D], x[5], S31, 0xfffa3942);
	HH(regz[D], regz[A], regz[B], regz[C], x[8], S32, 0x8771f681);
	HH(regz[C], regz[D], regz[A], regz[B], x[11], S33, 0x6d9d6122);
	HH(regz[B], regz[C], regz[D], regz[A], x[14], S34, 0xfde5380c);
	HH(regz[A], regz[B], regz[C], regz[D], x[1], S31, 0xa4beea44);
	HH(regz[D], regz[A], regz[B], regz[C], x[4], S32, 0x4bdecfa9);
	HH(regz[C], regz[D], regz[A], regz[B], x[7], S33, 0xf6bb4b60);
	HH(regz[B], regz[C], regz[D], regz[A], x[10], S34, 0xbebfbc70);
	HH(regz[A], regz[B], regz[C], regz[D], x[13], S31, 0x289b7ec6);
	HH(regz[D], regz[A], regz[B], regz[C], x[0], S32, 0xeaa127fa);
	HH(regz[C], regz[D], regz[A], regz[B], x[3], S33, 0xd4ef3085);
	HH(regz[B], regz[C], regz[D], regz[A], x[6], S34, 0x04881d05);
	HH(regz[A], regz[B], regz[C], regz[D], x[9], S31, 0xd9d4d039);
	HH(regz[D], regz[A], regz[B], regz[C], x[12], S32, 0xe6db99e5);
	HH(regz[C], regz[D], regz[A], regz[B], x[15], S33, 0x1fa27cf8);
	HH(regz[B], regz[C], regz[D], regz[A], x[2], S34, 0xc4ac5665);
}

void	md5_transform_round_four(uint32_t *regz, uint32_t x[16])
{
	II(regz[A], regz[B], regz[C], regz[D], x[0], S41, 0xf4292244);
	II(regz[D], regz[A], regz[B], regz[C], x[7], S42, 0x432aff97);
	II(regz[C], regz[D], regz[A], regz[B], x[14], S43, 0xab9423a7);
	II(regz[B], regz[C], regz[D], regz[A], x[5], S44, 0xfc93a039);
	II(regz[A], regz[B], regz[C], regz[D], x[12], S41, 0x655b59c3);
	II(regz[D], regz[A], regz[B], regz[C], x[3], S42, 0x8f0ccc92);
	II(regz[C], regz[D], regz[A], regz[B], x[10], S43, 0xffeff47d);
	II(regz[B], regz[C], regz[D], regz[A], x[1], S44, 0x85845dd1);
	II(regz[A], regz[B], regz[C], regz[D], x[8], S41, 0x6fa87e4f);
	II(regz[D], regz[A], regz[B], regz[C], x[15], S42, 0xfe2ce6e0);
	II(regz[C], regz[D], regz[A], regz[B], x[6], S43, 0xa3014314);
	II(regz[B], regz[C], regz[D], regz[A], x[13], S44, 0x4e0811a1);
	II(regz[A], regz[B], regz[C], regz[D], x[4], S41, 0xf7537e82);
	II(regz[D], regz[A], regz[B], regz[C], x[11], S42, 0xbd3af235);
	II(regz[C], regz[D], regz[A], regz[B], x[2], S43, 0x2ad7d2bb);
	II(regz[B], regz[C], regz[D], regz[A], x[9], S44, 0xeb86d391);
}
