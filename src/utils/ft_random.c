/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:26:04 by ppontet           #+#    #+#             */
/*   Updated: 2025/05/17 11:35:11 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

// TODO Etudier remplacement par celui de Minishell

int	ft_random(int fd);
int	ft_random_init(void);

int	ft_random_init(void)
{
	int	fd;

	fd = open("/dev/urandom", 0);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	ft_random(int fd)
{
	int	random;

	if (read(fd, &random, sizeof(int)) == -1)
		return (-1);
	return (random);
}
