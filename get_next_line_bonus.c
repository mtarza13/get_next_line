/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:44:14 by mtarza            #+#    #+#             */
/*   Updated: 2024/11/23 08:47:46 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	add_line_to_list(struct s_list **list, int fd)
{
	ssize_t	bytes_read;
	char	*buffer;

	while (!found_newline(*list))
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		ft_lstadd_back(list, ft_lstnew(buffer));
		free(buffer);
	}
}

int	get_line_length(struct s_list *list)
{
	struct s_list	*current;
	int				line_count;
	char			*data;

	current = list;
	line_count = 0;
	while (current)
	{
		data = current->data;
		while (*data)
		{
			line_count++;
			if (*data == '\n')
				break ;
			data++;
		}
		current = current->next;
	}
	return (line_count);
}

char	*construct_line(struct s_list *list)
{
	struct s_list	*current;
	char			*line;
	char			*ptr;
	char			*data;

	line = (char *)malloc((get_line_length(list) + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ptr = line;
	current = list;
	while (current)
	{
		data = current->data;
		while (*data && *data != '\n')
			*ptr++ = *data++;
		if (*data == '\n')
			*ptr++ = *data++;
		current = current->next;
	}
	*ptr = '\0';
	return (line);
}

void	next_line(struct s_list **list)
{
	struct s_list	*last_node;
	struct s_list	*new_node;
	char			*new_data;
	int				i;
	int				j;

	i = 0;
	j = 0;
	new_data = malloc(BUFFER_SIZE + 1);
	new_node = malloc(sizeof(struct s_list));
	if (new_node == NULL || new_data == NULL)
		return ;
	last_node = *list;
	if (last_node == NULL)
		return ;
	while (last_node->next)
		last_node = last_node->next;
	while (last_node->data[i] && last_node->data[i] != '\n')
		++i;
	while (last_node->data[i] && last_node->data[++i])
		new_data[j++] = last_node->data[i];
	new_data[j] = '\0';
	new_node->data = new_data;
	new_node->next = NULL;
	ft_lstclean_up(list, new_node, new_data);
}

char	*get_next_line(int fd)
{
	static struct s_list	*list[FDS];
	char					*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	add_line_to_list(&list[fd], fd);
	if (!list[fd])
		return (NULL);
	line = construct_line(list[fd]);
	if (!line)
		return (NULL);
	next_line(&list[fd]);
	return (line);
}
