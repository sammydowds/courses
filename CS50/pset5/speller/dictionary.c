// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

/////////////////////////////////////////////////////////////////

//global to hold how many words are in the dictionary
int numberofwords = 0;


//structure for a node in the trie
typedef struct node
{
    bool isAword;
    struct node* children[27];
}
node;

//creating a pointer to reference in load (also updated there with value) and then referenced by check
node *firstnode;


//this function deallocates the last node with children in the tree. It is recursive.
void freenode(node *frstnode)
{

    //scan through each child of the node
    for (int i = 0; i < 27; i++)
    {
        //if child of the node in ith location is no null, recurse passing in updated node location
        if (frstnode -> children[i] != NULL)
        {
            freenode(frstnode -> children[i]);
        }
    }
    //once node exists without children, deallocate memory for this node
    free(frstnode);
    return;
}



// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    //update a var to hold the root as the first node location
    node *currentnode = firstnode;

    int letter;

    //var to iterate through each character of the word
    int i = 0;

    //loop to go through each node of the tree. If the node has a null value for the child return false, because word does not exist in the trie
    while (word[i] != '\0')
    {
        //updating letter character to value 0-27
        if (word[i] == '\'')
        {
            letter = ('z' + 1) - 'a';
        }
        else
        {
            letter = tolower(word[i]) - 'a';
        }


        //checking if node has child that is not null, if null then return false. If true update pointer to current node to node with non-null location
        if (currentnode -> children[letter] != NULL)
        {
            currentnode = currentnode -> children[letter];
            i++;
        }
        else
        {
            return false;
        }

    }

    //at this point, word has been iterated through entirely. So we need to check if the node has feature of is_word true
    if (currentnode -> isAword == true)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO

     // integer mapping for a and z
   int aAsInt = (int)'a';
   int zAsInt = (int)'z';

   // opening the dictionary file
   FILE* fp = fopen(dictionary,"r");

   // sanity check for null returned reference
   if (fp == NULL)
   {
    return false;
   }
   // mallocking memory for first node
   firstnode = (node*) calloc(sizeof(node), sizeof(char*));

   // integer for current position in children array
   int character = 0;

   // looping through dictionary until end of file is encountered
   while(EOF != (character = fgetc(fp)))
   {
   		// setting current node to first node
   		node* currentnode = firstnode;

   		// iterating through character and adding each
   		// letter to children until "\n"
   		for(; character != '\n'; character = fgetc(fp))
   		{
   			// if apostrophe then store in
   			if (character == '\'')
   			{
   				character = zAsInt + 1;
   			}

   			// if the character is not in trie...create one
   			if (currentnode -> children[character - aAsInt] == NULL)
   			{
   				// malloc a new node
   				currentnode -> children[character - aAsInt] = (node*)calloc(sizeof(node), sizeof(char*));
   				currentnode = currentnode -> children[character - aAsInt];
   			}
   			// got to address in children
   			else
   			{
   				currentnode = currentnode -> children[character - aAsInt];
   			}

   		}
   		currentnode -> isAword = true;
   		numberofwords++;
   }

   // close the dictionary file
   fclose(fp);
   return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{

    return numberofwords;

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    node *currentnode = firstnode;
    freenode(currentnode);
    return true;
}


