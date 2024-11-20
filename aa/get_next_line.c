#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

void cleanup_list(t_list **head)
{
    t_list *tail_node;
    t_list *new_clean_node;
    int i = 0, k = 0;
    char *buffer;

    buffer = malloc(BUFFER_SIZE + 1);
    new_clean_node = malloc(sizeof(t_list));
    if (buffer == NULL || new_clean_node == NULL)
        return;

    tail_node = find_last_node(*head);
    while (tail_node->str_buf[i] && tail_node->str_buf[i] != '\n')
        ++i;
    while (tail_node->str_buf[i] && tail_node->str_buf[++i])
        buffer[k++] = tail_node->str_buf[i];
    buffer[k] = '\0';

    new_clean_node->str_buf = buffer;
    new_clean_node->next = NULL;

    dealloc(head, new_clean_node, buffer);
}

char *extract_line(t_list *head)
{
    int line_length;
    char *line_buffer;

    if (head == NULL)
        return NULL;

    line_length = len_to_newline(head);
    line_buffer = malloc(line_length + 1);
    if (line_buffer == NULL)
        return NULL;

    copy_str(head, line_buffer);
    return line_buffer;
}

void append_node(t_list **head, char *buffer)
{
    t_list *new_node;
    t_list *tail_node;

    tail_node = find_last_node(*head);
    new_node = malloc(sizeof(t_list));
    if (new_node == NULL)
        return;

    if (tail_node == NULL)
        *head = new_node;
    else
        tail_node->next = new_node;

    new_node->str_buf = buffer;
    new_node->next = NULL;
}

void populate_list(t_list **head, int fd)
{
    int bytes_read;
    char *buffer;

    while (!found_newline(*head))
    {
        buffer = malloc(BUFFER_SIZE + 1);
        if (buffer == NULL)
            return;

        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
        {
            free(buffer);
            return;
        }

        buffer[bytes_read] = '\0';
        append_node(head, buffer);
    }
}

char *get_next_line(int fd)
{
    static t_list *head = NULL;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    populate_list(&head, fd);
    if (head == NULL)
        return NULL;

    line = extract_line(head);
    cleanup_list(&head);
    return line;
}
