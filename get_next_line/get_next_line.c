/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abekri <abekri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 03:52:41 by abekri            #+#    #+#             */
/*   Updated: 2024/08/29 03:53:18 by abekri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*extract_next_line(char **buff)
{
	char	*line;
	char	*ptr;

	ptr = *buff;
	while (*ptr && *ptr != '\n')
		ptr++;
	ptr += (*ptr == '\n');
	line = ft_substr(*buff, 0, ptr - *buff);
	if (!line)
	{
		free(*buff);
		return (NULL);
	}
	ptr = ft_strdup(ptr);
	free(*buff);
	*buff = ptr;
	return (line);
}

static char	*read_file_and_handle_error(int fd, char *buff, ssize_t *bytes_read)
{
	*bytes_read = read(fd, buff, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		free(buff);
		return (NULL);
	}
	buff[*bytes_read] = '\0';
	return (buff);
}

static char	*read_until_newline(char *buff, int fd, char *temp_buff)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read && !ft_strchr(buff, '\n'))
	{
		temp_buff = read_file_and_handle_error(fd, temp_buff, &bytes_read);
		if (!temp_buff)
		{
			free(buff);
			return (NULL);
		}
		buff = ft_strjoin(buff, temp_buff);
		if (!buff)
		{
			free(temp_buff);
			return (NULL);
		}
	}
	free(temp_buff);
	return (buff);
}

char	*update_buffer_and_extract_line(int fd, char *buff[], char *temp_buff)
{
	buff[fd] = read_until_newline(buff[fd], fd, temp_buff);
	if (!buff[fd])
		return (NULL);
	if (!*buff[fd])
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	return (extract_next_line(&buff[fd]));
}

char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX];
	char		*temp_buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buff[fd])
		buff[fd] = ft_strdup("");
	if (!buff[fd])
		return (NULL);
	temp_buff = malloc(sizeof(*temp_buff) * (BUFFER_SIZE + 1));
	if (!temp_buff)
	{
		free(buff[fd]);
		return (NULL);
	}
	return (update_buffer_and_extract_line(fd, buff, temp_buff));
}
