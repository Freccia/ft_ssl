/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 15:43:32 by lfabbro           #+#    #+#             */
/*   Updated: 2018/12/14 14:14:30 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include "libft.h"
# include <stdint.h>

/*
** bits in a word
*/
# define BASE64_WORD			sizeof(uint32_t) * 8
# define BASE64_BUFSIZE			1024

/*
** Base64 isn't fixed
*/
# define BASE64_DIGEST_SIZE		0

/*
** BASE64 STRUCTURE
*/
typedef struct		s_base64_ctx
{
	uint64_t		bitlen;
	uint32_t		datalen;
	uint32_t		regs[8];
	uint8_t			data[64];
}					t_base64;

/*
** base64 CORE
*/
void				b64_encode(const uint8_t *d, uint32_t len, uint8_t *e);
void				b64_decode(const uint8_t *e, uint32_t len, uint8_t **d);

/*
** base64 WRAPPERS
*/
void				ssl_base64_init(void *ctx);
void				ssl_base64_update(void *ctx, const uint8_t data[],
						uint32_t len);
void				ssl_base64_final(void *ctx, uint32_t hash[]);

int					base64_file (const char *filename, uint8_t **encoded);
void				base64_string(const char *msg, int opt);
void				base64_data(const uint8_t *msg, uint32_t len, uint8_t **e);
void				base64_filter(int quiet);
int					base64_files(int ac, char **av, int opt);


#endif
