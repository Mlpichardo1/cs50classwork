// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "dictionary.h"

typedef struct node
    {
        char word[LENGTH + 1];
        struct node *next;
    }
    node;

    node* hashtable[HASHTABLE_SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = head;

    while (cursor != NULL)
    {
        int strcmp(word, cursor);
        cursor = cursor->next;
    }

    if (word == cursor)
    {
        return true;
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // make all hash table elements NULL
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }


    // open dictionary
    FILE* file_d = fopen(dictionary, "r");
    if (file_d == NULL)
    {
        printf("Unable to open dictionary.\n");
        return false;
    }

    while (fscanf(dictionary, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            strcpy(new_node->word, word);
        }
        // new_node->next = head;
        // head = new_node;
    }

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
