// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// representation of a node
typedef struct node
{
    bool is_word;
    struct node *children[27];
    struct node *prev;
    int firstIndex;
    bool next_is_word;
    bool hasNext;
    // struct node *next;
}
node;

// keep track of top beginning or try
node *root;

// maintain pointer to root
node *trav;

node *temp;

// track new node
node *newNode;

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
bool unloadAgain(void);
bool freeAllNodes(int i, int k);



#endif // DICTIONARY_H
