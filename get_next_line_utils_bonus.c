/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:45:07 by mtarza            #+#    #+#             */
/*   Updated: 2024/11/23 08:48:28 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	copy = malloc(i + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	ft_lstclean_up(t_list **list, t_list *new_node, char *new_data)
{
	t_list	*tmp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->data);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (new_node->data[0])
		*list = new_node;
	else
	{
		free(new_data);
		free(new_node);
	}
}

t_list	*ft_lstnew(char *data)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(struct s_list));
	if (!new_node)
		return (NULL);
	new_node->data = ft_strdup(data);
	if (!new_node->data)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!*lst)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

char	*found_newline(t_list *list)
{
	t_list	*current;
	char	*ptr;

	current = list;
	if (!current)
		return (NULL);
	while (current->next)
		current = current->next;
	if (!current->data)
		return (NULL);
	ptr = current->data;
	while (*ptr != '\0')
	{
		if (*ptr == '\n')
			return (ptr);
		ptr++;
	}
	return (NULL);
}
