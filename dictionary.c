// Implements a dictionary's functionality
/*--------------------------------------------------------------------------------------
Qualified for Big Board on 6/28/18. Ranked 472.
Go to https://speller.cs50.net/cs50/2018/x/challenges/speller/#user/GREGG-CHRISTOFFERSON
for results
---------------------------------------------------------------------------------------*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// track number of words in dictionary
int words = 0;

// track if the dictionary was loaded
int loaded = 0; // false or unloaded

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int c;

    // maintain pointer to root of try
    trav = root;

    // for each letter in input word, go to corresponding element in children
    for (int i = 0; i < strlen(word) + 1; i++)
    {
        // if we have an apostrophe, assign it to index 26 in children
        if (word[i] == 39)
        {
            c = 26;
        }

        // check if we are at the end of the word
        else if (word[i] != '\0')
        {

            // check if we have an uppercase letter
            if (word[i] >= 65 && word[i] <= 90)
            {
                // convert to lowercase
                c = word[i] + 32;

                // covert to alphabetical index
                c = c - 97;
            }
            else
            {
            // just convert to alphabetical index
            c = word[i] - 97;
            }
        }

        // if corresponding element in children is NULL, word is not in dictionary
        if (trav->children[c] == NULL && word[i] != '\0')
        {
            return false;
        }
        else
        {
            // if we are at the end of the word, the word is in the dictionary
            if (word[i] == '\0')
            {
                if (trav->is_word == true)
                {
                    return true;
                }
            }
            // if corresponding element in children isn't NULL, go to next node
            trav = trav->children[c];
        }
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // Try to open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return 1;
    }

    // Prepare to load dictionary
    int chIndex = 0;
    root = calloc(1, sizeof(node));

    // check if NULL
    if (root == NULL)
    {
        // end program
        return 2;
    }

    // maintain pointer to root of try
    trav = root;

    // Iterate through the letters of each word in the dictionary
    // Load each word of dictionary into the trie, letter by letter
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // check for apostrophe and assign to index 26 of children
        if (c == 39)
        {
            chIndex = 26;
        }
        else
        {
            // convert letter to alphabetical index
            chIndex = c - 97;
        }

        // check if we are not at end of word
        if (chIndex >= 0)
        {
            // check if children index is NULL
            if (trav->children[chIndex] == NULL)
            {
                // check that we have a lowercase letter or apostrophe
                if ((c >= 97 && c <= 122) || c == 39)
                {
                    // calloc a new node * for each letter of the word
                    newNode = calloc(1, sizeof(node));

                    // check if NULL
                    if (newNode == NULL)
                    {
                        // end program
                        return 2;
                    }

                    // set newNode prev pointer to previous node
                    newNode->prev = trav;

                    // have node.children[chIndex] point to new node
                    trav->children[chIndex] = newNode;

                    // set hasNext to true
                    trav->hasNext = true;

                    // point trav to newNode
                    trav = newNode;
                }
            }
            else
            {
                // if children index isn't NULL, travel to next Node
                if ((c >= 97 && c <= 122) || c == 39)
                {
                trav = trav->children[chIndex];
                }
            }
        }

        if (c == 10)
        {
            // We must have found a whole word

            // Update counter
            words++;

            // set is_word booleans
            trav->is_word = true;
            trav = trav->prev;
            trav->next_is_word = true;

            // prepare for new word
            trav = root;
        }
    }
    if (EOF)
    {
        // success
        loaded = 1;

        // close dictionary
        fclose(file);
        return true;
    }
    if (loaded != 1)
    {
        // no success
        return false;
    }
    return 0;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (loaded == 1)
    {
        return words;
    }
    else
    {
        return 0;
    }
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // maintain pointer to root of try
    trav = root;

    // create temporary node to preserve pointer
    temp = trav;

    bool allFreed = unloadAgain();
    if (!allFreed)
    {
        return false;
    }
    else
    {
        return true;
    }

}

bool unloadAgain(void)
{
    // iterate through the node children
    for (int i = 0; i < 27; i++)
    {
        // if not NULL, travel to lowest node by recursively unloading again
        if (trav->children[i] != NULL)
        {
           trav = trav->children[i];
           unloadAgain();
        }
    }
    // free all nodes and children from lowest node to top
    temp = trav->prev;
    free(trav);
    trav = temp;
    return true;
}