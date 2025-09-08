/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eganassi <eganassi@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:32:54 by eganassi          #+#    #+#             */
/*   Updated: 2025/09/08 11:23:04 by eganassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minish.h"

// Function to display the linked list of string arrays
void display_linked_list_of_string_array(t_list *head)
{
    t_list *current;
    int node_count;
    int i;

    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    current = head;
    node_count = 0;

    printf("=== Linked List of String Arrays ===\n");
    
    while (current != NULL) {
        printf("Node %d:\n", node_count);
        
        if (current->arr_content == NULL) {
            printf("  [Empty array]\n");
        } else {
            printf("  Strings: ");
            i = 0;
            // Display all strings in the array until we hit NULL
            while (current->arr_content[i] != NULL) {
                printf("\"%s\"", (char *)current->arr_content[i]);
                if (current->arr_content[i + 1] != NULL) {
                    printf(", ");
                }
                i++;
            }
            printf("\n");
        }
        
        current = current->next;
        node_count++;
    }
    
    printf("Total nodes: %d\n", node_count);
}

void display_linked_list_of_string(t_list *head)
{
    t_list *current;
    int node_count;
    
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    current = head;
    node_count = 0;

    printf("=== Linked List of Strings ===\n");
    
    while (current != NULL) {
        printf("Node %d: \"%s\"\n", node_count, (char *)current->content);
        current = current->next;
        node_count++;
    }
    
    printf("Total nodes: %d\n", node_count);
}

void display_linked_list_dic_env(t_list *head)
{
    t_list *current;
    int node_count;
    
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    current = head;
    node_count = 0;

    printf("=== Linked List of Strings ===\n");
    t_dic *dic;
    while (current != NULL) {

        dic = (t_dic *)current->content;
        printf("Node %d: key: %s\tvalue: %s\n", node_count, (char *)dic->key, (char *)dic->value);
        current = current->next;
        node_count++;
    }
    
    printf("Total nodes: %d\n", node_count);
}

void display_string_array(char *arr[]) {
    int i;
    for (i = 0; arr[i]!=NULL ; i++) {
        if (arr[i] != NULL) {
            printf("%s\t", arr[i]);
        }
    }
    printf("len %d ", i);
    printf("\n");
}