//CS-GY9163 Application Security
//Unit Assignment 1 - spell checker system
//Peter Crefeld
#include "dictionary.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
//#include "dictionary.c"

#define length 45

/*  spell checker system in C
*/

// create a variable to count the words in a dictionary
int word_counter = 0;

/*   function called check_words to tie them all together
*/

int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[])
{

	int num_misspelled = 0;	

        node* new_node = malloc(sizeof(node));
	while(fscanf(fp, "%s", new_node->word)!=EOF)
	 //read the line
	 //split the line on spaces
         //For each word in line:
   
	{
	      if (new_node->word != NULL)
	      {
		char* newString;
		newString= strtok(new_node->word, " ");
		while (newString!=NULL)
		 {

		  if (strlen(newString) <= LENGTH)
		  {
		   //newString2[len1] - '\0';

		//pjc-add for end as well
		    int word_length2 = strlen(newString);
		    if (ispunct(newString[word_length2-1]))
			{
			   //printf ("word-out:%s\n", newString);
			   newString[word_length2-1] = '\0';
			}
		//pjc

		   if (check_word(newString, hashtable) == false)
  	             //If not check_word(word):
		   {
                        //Append word to misspelled.
                        //Increment num_misspelled.
			misspelled[num_misspelled] = malloc(strlen(newString));
			strcpy(misspelled[num_misspelled],newString);
	           	num_misspelled += 1;
		    }
		   } else {
			num_misspelled += 1;
		   }
		   //newString= strtok(NULL, " ,.-");
		   newString= strtok(NULL, " ");
		  }
	       }
	}
	//printf("Complete check_words\n");
    	return num_misspelled;
}

/*  function to load the list of words into the hash map (called load_dictionary)
*/

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])
{
int number_of_words = 0;

// Initialize each value in hash table to NULL.
    for(int i = 0; i < HASH_SIZE; i++)
    {
        hashtable[i] = NULL;
    }   

   // open dictionary and check for NULL
	FILE* the_dictionary;    
    	the_dictionary = fopen(dictionary_file, "r"); 

      if (the_dictionary == NULL)
         {
          //printf("Could not open %s.\n", dictionary_file);
          //unload(); - future fix
          return false;    
      }
    // read in txt file
   else
    {
    char buffer[LENGTH+1];
    while (fscanf(the_dictionary, "%s", buffer) > 0)
    {
        if (strlen(buffer) >= LENGTH+1){
		return false;	
	}
        // Allocate memory for a new node.
        node* new_node = malloc(sizeof(node));
        // Set node's next pointer to NULL.
        new_node->next = NULL;
        // Set node's word to value stored in buffer.
        strcpy(new_node->word, buffer);
        // Run word through hash function to set bucket in hash table.
        int bucket = hash_function(new_node->word);
        // If it's the first node being added to the bucket, replace 
        // the NULL value with the new node.
        if (hashtable[bucket] == NULL)
        {
            hashtable[bucket] = new_node;
        }
        // Otherwise set new node's pointer to the first node in the linked list.
        // Then set new node to be the first node in the linked list.
        else
        {
            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;
        }
        // Track number of words in dictionary.
        number_of_words++;
    }
      fclose(the_dictionary);

        //free(new_node); - future fix
	//free(newString2);
        return true;           
    }    
    return false;
}

/*   function to check if a word is correctly spelled (called check_word)
*/

bool check_word(const char* word, hashmap_t hashtable[])
{
    int word_length = strlen(word);
    char lower_word[LENGTH+1];
    char reg_word[LENGTH+1];    

    // Convert word to lowercase to accurately compare to hash table.
    for (int i = 0; i < word_length; i++)
    {
	reg_word[i] = word[i];
        // If character is uppercase, make it lowercase.
        if(isupper(word[i]))
        {
            lower_word[i] = tolower(word[i]) ;
        }
        // Otherwise it's already lowercase or it's not a letter.
        else
        {
            lower_word[i] = word[i];
        }
    }    

    //Remove punctuation from beginning and end of word.
    if (ispunct(word[word_length-1]))
	{
	   //printf ("word:%s\n", word);
	   reg_word[word_length-1] = '\0';
	}
    if (ispunct(word[0]))
	{
	 //printf ("word:%s\n", word);
	 for (int i = 0; i < word_length; i++)
	   {
		reg_word[i] = word[i+1];

	   }
	 reg_word[word_length-1] = '\0';
	}

    // Add null character to end of char array.
    lower_word[word_length] = '\0';
    reg_word[word_length] = '\0';
    // Use hash function to find correct "bucket" to place word.
    int bucket = hash_function(lower_word);
    // Set cursor to first node in bucket.
    node* cursor = hashtable[bucket];   
    // Until the end of the linked list is reached (cursor == NULL),
    // compare each word stored in each node to lower_word.  If they're
    // the same, then the word is in the dictionary and is not mispelled.
    // Otherwise, it is spelled incorrectly.
    while (cursor != NULL)
    {
        if (strcmp(lower_word, cursor->word) == 0)
        {
            // If lowercase'd word is the same as another in the bucket,
            // it's a match and return true.
            return true;
        }
        cursor = cursor->next;
    }

    int bucket2 = hash_function(reg_word);
    node* cursor2 = hashtable[bucket2];   
    while (cursor2 != NULL)
    {
        if (strcmp(reg_word, cursor2->word) == 0)
        {
            return true;
        }
        cursor2 = cursor2->next;
    }
    
    return false;
}

