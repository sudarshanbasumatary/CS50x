/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <cs50.h>
#include <stdlib.h>

#include "dictionary.h"
#define MAX 27

FILE *dc;
int dic_size = 0;
typedef struct node {
    bool is_word;
    struct node* letter[MAX]; //MAX - 1 reserved for '
} node;

node *root = NULL;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* crawler = root;
    const int wLen = strlen(word);
    for(int i = 0; i < wLen; i++) {
        crawler = crawler->letter[isalpha(word[i]) ? tolower(word[i]) - 'a' : MAX - 1];
        if(crawler == NULL) {
            return false;
        }
    }
    return crawler->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    dc = fopen(dictionary, "r");
    if(dc == NULL)
        return false;

    if(!root) {
        root = malloc(sizeof(node));
        root->is_word = false;
        for(int i = 0; i < MAX; i++)
            root->letter[i] = NULL;
    }
    node *crawler = root;
    int ch = fgetc(dc);
    while(1) {
        while(ch < 'a' || ch > 'z') {
            ch = fgetc(dc);
            if(ch == EOF)
                return true;
        }
        while((ch >= 'a' && ch <= 'z') || ch == '\'') {
            if(ch == '\'') {
                if(crawler->letter[MAX - 1] == NULL) {
                    crawler->letter[MAX - 1] = malloc(sizeof(node));
                    crawler->letter[MAX - 1]->is_word = false;
                    for(int i = 0; i < MAX; i++)
                        crawler->letter[MAX - 1]->letter[i] = NULL;
                }
                crawler = crawler->letter[MAX - 1];
            }
            else {
                if(crawler->letter[ch - 'a'] == NULL) {
                    crawler->letter[ch - 'a'] = malloc(sizeof(node));
                    crawler->letter[ch - 'a']->is_word = false;
                    for(int i = 0; i < MAX; i++)
                        crawler->letter[ch - 'a']->letter[i] = NULL;   
                }
                crawler = crawler->letter[ch - 'a'];
            }
            ch = fgetc(dc);
        }
        if(ch == 10) {
            dic_size++;
            crawler->is_word = true;
            crawler = root;
        }
    }

    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dic_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

void unload_node(node* curr) {
    if(curr != NULL) {
        for(int i = 0; i < MAX; i++)
            if(curr->letter[i] != NULL)
                unload_node(curr->letter[i]);
        free(curr);
    }
}

bool unload(void)
{
    unload_node(root);
    fclose(dc);
    return true;
}
