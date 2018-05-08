// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Keep count of words searched
int count_words = 0;

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// define a hashtable
node *hashtable[26];

// Convert letters to there ASCII value
int hash(const char *word)
{
    char first = word[0];
    int hashing = tolower(first) - 'a';
    return hashing;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_num = hash(word);
    node *cursor = hashtable[hash_num];

    while (cursor != NULL)
    {
        char *checker = cursor->word;
        //use strcasecmp to see if word from dictionary
        if (strcasecmp(word, checker) == 0)
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
    FILE *file_d = fopen(dictionary, "r");
    if (file_d == NULL)
    {
        printf("Unable to open dictionary.\n");
        unload();
        return false;
    }

    char word[LENGTH + 1];

    // read through the word and allocate space
    while (fscanf(file_d, "%s", word) != EOF)
    {
        count_words++;
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
    fclose(file_d);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (count_words > 0)
    {
        return count_words;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *next = cursor->next;
            free(cursor);
            cursor = next;
        }
    }
    return true;
}
