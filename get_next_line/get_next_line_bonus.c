/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:09:19 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/19 12:26:59 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_filler(int fd, char *backup, char *buffer);
char	*ft_make_line(char *buffer, char *backup);
char	*ft_strjoin_gnl(char *s1, char *s2);

/**
 * @brief Main function :
 * Get the next line of a file descriptor
 * Stops if '\'n is detected or it there's nothing to read
 * /!\ Needs to be freed after use
 *
 * @param fd File descriptor
 * @return char* Next line of the file
 */
char	*get_next_line(int fd)
{
	static char	backup[MAX_FD][BUFFER_SIZE + 1] = {0};
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * 1);
	if (buffer == NULL)
		return (NULL);
	buffer[0] = '\0';
	line = ft_filler(fd, backup[fd], buffer);
	if (line == NULL || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * @brief Fills 'backup', stores in a buffer,
 * Stops if '\'n is detected or it there's nothing to read
 * Read of fixed size at compilation (default is 42 bytes)
 *
 * @param fd File descriptor
 * @param backup Backup of the buffer
 * @param buffer Buffer to store the read data
 * @return char* Next line of the file
 */
char	*ft_filler(int fd, char *backup, char *buffer)
{
	ssize_t	read_ret;

	read_ret = 1;
	while (read_ret > 0)
	{
		if (backup[0] == '\0')
		{
			read_ret = read(fd, backup, BUFFER_SIZE);
			if (read_ret < 0)
			{
				free(buffer);
				return (NULL);
			}
			backup[read_ret] = '\0';
		}
		buffer = ft_strjoin_gnl(buffer, backup);
		if (buffer == NULL)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			return (ft_make_line(buffer, backup));
	}
	return (buffer);
}

/**
 * @brief Build a new array containing the new line
 * and stores the rest of buffer into backup
 *
 * @param buffer Buffer to extract the line from
 * @param backup Rest of the buffer
 * @return char* Array containing the new line
 */
char	*ft_make_line(char *buffer, char *backup)
{
	size_t	index;
	char	*line;

	if (!buffer || buffer[0] == '\0')
		return (NULL);
	index = 0;
	while (buffer[index] != '\0' && buffer[index] != '\n')
		index++;
	line = malloc(sizeof(char) * (index + 2));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	ft_strlcpy(line, buffer, index + 2);
	if (buffer[index] == '\n')
		line[index + 1] = '\0';
	if (buffer[index] != '\0')
		ft_strlcpy(backup, &buffer[index + 1], BUFFER_SIZE + 1);
	else
		backup[0] = '\0';
	free(buffer);
	return (line);
}

/**
 * @brief Modified strjoin to work with GNL
 * Frees s1 after use
 * Sets s2 to empty string after use
 *
 * @param s1 First array to copy from
 * @param s2 Second array to concatenate
 * @return char* Array containing s1 and s2
 */
char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	s2[0] = '\0';
	return (result);
}
