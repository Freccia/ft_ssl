/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:38:47 by marvin            #+#    #+#             */
/*   Updated: 2019/02/07 22:58:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# define ENCRYPTION_MODE 0
# define DECRYPTION_MODE 1

typedef struct		s_des_ctx {
	uint32_t		regs[4];
	uint8_t			buff[MD5_BUFFER_SIZE];
}					t_des;

typedef struct		s_des_keyset {
	uint8_t			k[8];
	uint8_t			c[4];
	uint8_t			d[4];
}					t_keyset;

char				*ft_des_getopt(int ac, char **av, t_ssl_cipher *ci,
		int64_t *opt);

int					des_file (const char *filename, uint32_t digest[]);
void				des_string(const char *msg, int opt);
void				des_data(const uint8_t *msg, uint32_t len, uint32_t dig[]);
void				des_filter(int quiet);
int					des_files(int ac, char **av, int opt);

#endif
