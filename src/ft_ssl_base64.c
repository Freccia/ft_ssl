/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_base64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 15:42:31 by lfabbro           #+#    #+#             */
/*   Updated: 2018/12/14 15:11:34 by lfabbro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"
#include "error.h"
#include "ft_ssl.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static const char	*g_base64_longerr =
{
	"base64: Error: message too long.\n"\
	"	Limit fixed to 34,35 GB (34359738360 bytes)\n"
};


const char bb64[] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void	base64_data(const uint8_t *msg, uint32_t len, uint8_t **encoded)
{
	uint64_t	b64len;

	//b64len = ((len * 8) / 6) + ((len * 8) % 6) + 1;
	b64len = (len * 3) + 1;
	if ((*encoded = (uint8_t*)malloc(b64len)) == NULL)
		ft_exit(EXIT_FAILURE, FAIL_MALLOC);
	bzero(*encoded, b64len);
	b64_encode(msg, len, *encoded);
	write(1, *encoded, b64len);
	write(1, "\n", 1);
}

/*
** (void)quiet for compatibility with hashes
*/
void	base64_filter(int quiet)
{
	int64_t		len;
	uint8_t		*encoded;
	uint8_t		*msg;
	uint8_t		*tmp;
	uint8_t		buffer[BASE64_BUFSIZE];

	(void)quiet;
	len = 0;
	msg = NULL;
	encoded = NULL;
	while ((len += read(STDIN_FILENO, buffer, sizeof(BASE64_BUFSIZE))))
	{
		tmp = (uint8_t*)ft_strjoin((char*)msg, (char*)buffer);
		free(msg);
		msg = tmp;
	}
	base64_data(msg, len, &encoded);
	ft_printf("%s\n", encoded);
	ft_memset(encoded, 0, len);
}

void	base64_string(const char *msg, int opt)
{
	int64_t		len;
	uint8_t		*encoded;

	encoded = NULL;
	if ((len = ft_ssl_strlen(msg)) > UINT32_MAX)
		ft_exit(EXIT_FAILURE, g_base64_longerr);
	base64_data((uint8_t*)msg, (uint32_t)len, &encoded);
	if (opt & SSL_OPT_Q)
		ft_printf("%s\n", &encoded);
	else if (opt & SSL_OPT_R)
		ft_printf("%s \"%s\"\n", &encoded, msg);
	else
		ft_printf("base64 (\"%s\") = %s\n", msg, encoded);
	if (encoded != NULL)
	{
		ft_memset(encoded, 0, len);
		free(encoded);
	}
}

int		base64_file(const char *filename, uint8_t **encoded)
{
	int			fd;
	uint8_t		*msg;
	struct stat	stat_file;

	ft_printf("File: %s\n", filename);
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf("%s can't be opened\n", filename);
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &stat_file) == -1)
	{
		ft_printf("Failed to stat file: %s\n", filename);
		return (EXIT_FAILURE);
	}
	if ((msg = (uint8_t*)malloc(stat_file.st_size)) == NULL)
		ft_exit(EXIT_FAILURE, FAIL_MALLOC);
	if (read(fd, (char*)msg, stat_file.st_size) == -1)
		ft_exit(EXIT_FAILURE, FAIL_READ);
	base64_data(msg, stat_file.st_size, encoded);
	// memset 0?
	if (close(fd))
	{
		ft_printf("Failed to close file: %s\n", filename);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		base64_files(int ac, char **av, int opt)
{
	int			i;
	int			fail;
	uint8_t		*encoded;

	ft_printf("Files: %d\n", ac);
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
