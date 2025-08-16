/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:44:46 by mtarza            #+#    #+#             */
/*   Updated: 2024/11/23 08:44:48 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef FDS
#  define FDS 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(char *data);
void				ft_lstclean_up(struct s_list **list,
						struct s_list *new_node, char *new_data);
void				ft_lstadd_back(struct s_list **lst, struct s_list *new);
char				*ft_strdup(const char *s);
char				*found_newline(struct s_list *list);
void				add_line_to_list(struct s_list **list, int fd);
char				*construct_line(struct s_list *list);
int					get_line_length(struct s_list *list);
void				next_line(struct s_list **list);
char				*get_next_line(int fd);

#endif
