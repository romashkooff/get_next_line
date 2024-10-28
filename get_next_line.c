/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romashko <romashko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:37:01 by romashko          #+#    #+#             */
/*   Updated: 2024/10/28 22:58:37 by romashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_left_str(char *left_str, char **line)
{
	char	*left_ptr;
	char	*temp;

	left_ptr = NULL;
	if (left_str)
	{
		left_ptr = ft_strchr(left_str, '\n');
		if (left_ptr)
		{
			*left_ptr = '\0';
			*line = ft_strdup(left_str);
			temp = ft_strdup(left_ptr + 1);
			free(left_str);
			left_str = temp;
		}
		else
		{
			*line = ft_strdup(left_str);
			free(left_str);
			left_str = NULL;
		}
	}
	else
		*line = ft_strdup("\0");
	return (left_ptr);
}

char	*free_line(char **line, char buff[BUFFER_SIZE + 1])
{
	char	*temp_line;

	temp_line = *line;
	*line = ft_strjoin(temp_line, buff);
	free(temp_line);
	return (*line);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*line;
	char		*left_ptr;
	size_t		bytes_read;
	static char	*left_str;

	left_ptr = check_left_str(left_str, &line);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	while (bytes_read > 0 && !left_ptr)
	{
		buff[bytes_read] = '\0';
		left_ptr = ft_strchr(buff, '\n');
		if (left_ptr)
		{
			*left_ptr = '\0';
			left_str = ft_strdup(++left_ptr);
		}
		line = free_line(&line, buff);
		if (left_ptr)
			break ;
		bytes_read = read(fd, buff, BUFFER_SIZE);
	}
	return (line);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("text.txt", O_RDONLY);
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd));
// 	close(fd);
// }
