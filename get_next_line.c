/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romashko <romashko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:37:01 by romashko          #+#    #+#             */
/*   Updated: 2024/11/23 00:58:03 by romashko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *stash)
{
	int		bytes_read;
	char	*buffer;
	char	*temp;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buffer == NULL)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stash, buffer);
		free(stash);
		stash = temp;
		if (ft_strchr(stash, '\n') || !stash)
			break ;
	}
	return (free(buffer), stash);
}

char	*line_from_stash(char *stash)
{
	int		i;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = ft_calloc(i + (stash[i] == '\n') + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, i + (stash[i] == '\n'));
	return (line);
}

char	*new_stash_from_stash(char *stash)
{
	int		i;
	int		len;
	char	*new_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	len = ft_strlen(stash) - i - 1;
	new_stash = ft_calloc(len + 1, sizeof(char));
	if (!new_stash)
		return (free(stash), NULL);
	ft_memcpy(new_stash, stash + i + 1, len + 1);
	return (free(stash), new_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (stash != NULL)
			return (free(stash), stash = NULL, NULL);
		return (NULL);
	}
	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	if (!ft_strchr(stash, '\n'))
		stash = read_file(fd, stash);
	if (!stash)
		return (free(stash), NULL);
	line = line_from_stash(stash);
	stash = new_stash_from_stash(stash);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*next_line;
// 	int		count;

// 	count = 0;
// 	fd = open("text.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error opening file...");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		next_line = get_next_line(fd);
// 		if (next_line == NULL)
// 			break ;
// 		count++;
// 		printf("[%d]: %s\n", count, next_line);
// 		free(next_line);
// 		next_line = NULL;
// 	}
// 	close(fd);
// 	return (0);
// }
