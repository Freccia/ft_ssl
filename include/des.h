/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <>                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 18:38:47 by marvin            #+#    #+#             */
/*   Updated: 2019/02/25 17:00:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include "libft.h"
# include "getopt.h"
# include "error.h"
# include "ft_ssl.h"
# include <inttypes.h>
# include <sys/types.h>

# define ENCRYPTION_MODE	0
# define DECRYPTION_MODE	1
# define DES_BUFFER_SIZE	512
# define DES_OPTIONS		"hadei:k:o:p:s:v:"

typedef struct		s_des_ctx {
	uint8_t			buff[DES_BUFFER_SIZE];
	char			*infile;
	char			*key;
	char			*outfile;
	char			*passwd;
	char			*salt;
	char			*ivect;
}					t_des;

typedef struct		s_des_keyset {
	uint8_t			k[8];
	uint8_t			c[4];
	uint8_t			d[4];
}					t_keyset;

int					ft_des(t_des *ctx, const int opt);
char				*ft_des_getopt(int ac, char **av, t_ssl_cipher *ci,
		int64_t *opt);

#endif
