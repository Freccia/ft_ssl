/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 15:42:31 by lfabbro           #+#    #+#             */
/*   Updated: 2018/11/17 18:20:00 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

void	base64_data(const uint8_t *msg, uint32_t len, uint8_t **encoded)
{
	t_base64	ctx;
	uint64_t	b64len;

	b64len = (len * 3) + 1;
	if ((*encoded = (uint8_t*)malloc(len)) == NULL)
		ft_exit(EXIT_FAILURE, FAIL_MALLOC);
}

void	base64_filter(int quiet)
{
	int64_t		len;
	uint8_t		*encoded;
	uint8_t		*buffer;

	len = 0;
	if ((buffer = (uint8_t*)malloc(BASE64_BUFSIZE)) == NULL)
		ft_exit(EXIT_FAILURE, FAIL_MALLOC);
	while ((len += read(STDIN_FILENO, buffer, sizeof(BASE64_BUFSIZE))))
	{
		
	}
}

void	base64_string(const char *msg, int opt)
{
	int64_t		len;
	uint8_t		*encoded;

	encoded = NULL;
	if ((len = ft_ssl_strlen(msg)) > UINT32_MAX)
		ft_exit(EXIT_FAILURE, g_base64_longerr);
	base64_data((uint8_t)mg, (uint32_t)len, &encoded);
	if (opt & SSL_OPT_Q)
		ft_printf("%s\n", &encoded);
	else if (opt & SSL_OPT_R)
		ft_printf("%s \"%s\"\n", &encoded, msg);
	else
		ft_printf("sha256 (\"%s\") = %s\n", msg, &encoded);
	if (encoded != NULL)
	{
		ft_memset(encoded, 0, len);
		free(encoded);
	}
}

int		base64_file(const char *filename, uint32_t **encoded)
{
	int			fd;
	int			len;

	len = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("%s can't be opened\n", filename);
		return (EXIT_FAILURE);
	}
	base64_data(msg, len, encoded);
	// memset?
}

int		base64_files(int ac, char **av, int opt)
{
	int			i;
	int			fail;
	uint8_t		*encoded;

	encoded = NULL;
	fail = 0;
	i = g_optind;
	while (i < ac && av[i])
	{
		fail = base64_file(av[i], &encoded);
		if (!fail)
		{
			if (opt & SSL_OPT_Q)
				ft_printf("%s\n", &encoded);
			else if (opt & SSL_OPT_R)
				ft_printf("%s %s\n", &encoded, av[i]);
			else
				ft_printf("%s %s\n", av[i], &encoded);
		}
		++i;
		// should I memset encoded?
	}
	return (fail);
}
