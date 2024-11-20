/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 05:19:48 by mtarza            #+#    #+#             */
/*   Updated: 2024/11/20 05:31:30 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# if BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}				t_list;

int		found_newline(t_list *list);
t_list	*find_last_node(t_list *list);
char	*extract_line(t_list *list);
void	copy_str(t_list *list, char *str);
int		len_to_newline(t_list *list);
void	clean_node(t_list **list);
char	*get_next_line(int fd);
void	free_node(t_list **list, t_list *clean_node, char *buf);
void	read_and_add(t_list **list, int fd);

#endif
