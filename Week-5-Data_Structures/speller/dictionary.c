// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1024;

// Hash table
node *table[N];

// Word count
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to get bucket index
    unsigned int index = hash(word);

    // Traverse linked list at that bucket
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int h = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        h = (h * 31 + tolower(word[i])) % N;
    }
    return h;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    // Read each word in the file
    while (fscanf(source, "%s", word) != EOF)
    {
        // Allocate memory for new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(source);
            return false;
        }

        // Copy word into node
        strcpy(new_node->word, word);

        // Hash word to get bucket index
        unsigned int index = hash(word);

        // Insert node at beginning of linked list
        new_node->next = table[index];
        table[index] = new_node;

        // Increment word count
        word_count++;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through each bucket
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
