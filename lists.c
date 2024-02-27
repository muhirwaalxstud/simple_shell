#include "shell.h"

/**
 * add_node - Adds a new node to the beginning of the linked list.
 *
 * This function creates a new node with the provided string and index,
 * and inserts it at the start of the linked list. If successful, it
 * returns a pointer to the newly added node. If memory allocation fails,
 * it returns NULL.
 *
 * @head: Address of a pointer to the head node of the linked list.
 * @str: String field of the new node.
 * @num: Index of the node used for history.
 *
 * Return: A pointer to the newly added node on success, otherwise NULL.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
    list_t *new_head;

    if (!head)
        return (NULL);
    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);
    _memset((void *)new_head, 0, sizeof(list_t));
    new_head->num = num;
    if (str)
    {
        new_head->str = _strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return (NULL);
        }
    }
    new_head->next = *head;
    *head = new_head;
    return (new_head);
}

/**
 * add_node_end - Adds a new node to the end of the linked list.
 *
 * This function creates a new node with the provided string and index,
 * and appends it to the end of the linked list. If successful, it
 * returns a pointer to the newly added node. If memory allocation fails,
 * it returns NULL.
 *
 * @head: Address of a pointer to the head node of the linked list.
 * @str: String field of the new node.
 * @num: Index of the node used for history.
 *
 * Return: A pointer to the newly added node on success, otherwise NULL.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    list_t *new_node, *node;

    if (!head)
        return (NULL);

    node = *head;
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
        *head = new_node;
    return (new_node);
}

/**
 * print_list_str - Prints only the string element of the linked list.
 *
 * This function traverses the linked list and prints the string element
 * of each node. If a node's string element is NULL, it prints "(nil)".
 * It returns the size of the list.
 *
 * @h: Pointer to the first node of the linked list.
 *
 * Return: The size of the linked list.
 */
size_t print_list_str(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }
    return (i);
}

/**
 * delete_node_at_index - Deletes a node at the given index from the linked list.
 *
 * This function deletes the node at the specified index from the linked list.
 * It returns 1 on success and 0 on failure.
 *
 * @head: Address of a pointer to the head node of the linked list.
 * @index: Index of the node to delete.
 *
 * Return: 1 if the deletion is successful, 0 otherwise.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int i = 0;

    if (!head || !*head)
        return (0);

    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return (1);
    }
    node = *head;
    while (node)
    {
        if (i == index)
        {
            prev_node->next = node->next;
            free(node->str);
            free(node);
            return (1);
        }
        i++;
        prev_node = node;
        node = node->next;
    }
    return (0);
}

/**
 * free_list - Frees all nodes of the linked list.
 *
 * This function frees all nodes of the linked list and sets the head
 * pointer to NULL.
 *
 * @head_ptr: Address of a pointer to the head node of the linked list.
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
    list_t *node, *next_node, *head;

    if (!head_ptr || !*head_ptr)
        return;
    head = *head_ptr;
    node = head;
    while (node)
    {
        next_node = node->next;
        free(node->str);
        free(node);
        node = next_node;
    }
    *head_ptr = NULL;
}

