// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include "dictionary.h"

typedef struct node
    {
        char word[LENGTH + 1];
        struct node *next;
    }
    node;

    node* hashtable[26];

    int hash(char* word)
    {
        int input = tolower(word[0]) - 'a';
        return input;
    }

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_num = hash(word);
    node *cursor = hashtable[hash_num];

    while (cursor != NULL)
    {
        //use strcasecmp to see if word from dictionary
        if (strcmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open dictionary
    FILE* file_d = fopen(dictionary, "r");
    if (file_d == NULL)
    {
        printf("Unable to open dictionary.\n");
        return false;
    }

    // read through the word and allocate space
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

        int hash_num = hash(word);
        new_node->next = hashtable[hash_num];
        hashtable[hash_num] = new_node;

    }

    return true;
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
