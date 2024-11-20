#include "get_next_line.h"
#include <stdlib.h>

int found_newline(t_list *list)
{
    int i;

    if (list == NULL)
        return 0;
    while (list)
    {
        i = 0;
        while (list->str_buf[i] && i < BUFFER_SIZE)
        {
            if (list->str_buf[i] == '\n')
                return 1;
            ++i;
        }
        list = list->next;
    }
    return 0;
}

t_list *find_last_node(t_list *list)
{
    if (list == NULL)
        return NULL;
    while (list->next)
        list = list->next;
    return list;
}

void copy_str(t_list *list, char *str)
{
    int i;
    int k = 0;

    if (list == NULL)
        return;

    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i] == '\n')
            {
                str[k++] = '\n';
                str[k] = '\0';
                return;
            }
            str[k++] = list->str_buf[i++];
        }
        list = list->next;
    }
    str[k] = '\0';
}

int len_to_newline(t_list *list)
{
    int i;
    int len = 0;

    if (list == NULL)
        return 0;

    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i] == '\n')
            {
                ++len;
                return len;
            }
            ++i;
            ++len;
        }
        list = list->next;
    }
    return len;
}

void dealloc(t_list **list, t_list *clean_node, char *buf)
{
    t_list *tmp;

    if (list == NULL || *list == NULL)
        return;

    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->str_buf);
        free(*list);
        *list = tmp;
    }

    *list = NULL;

    if (clean_node->str_buf[0])
        *list = clean_node;
    else
    {
        free(buf);
        free(clean_node);
    }
}
