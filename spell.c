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
	//char wordcheck[length+1];


        node* new_node = malloc(sizeof(node));
	while(fscanf(fp, "%s", new_node->word)!=EOF)
   
	{
            //new_node = malloc(sizeof(node));
		//wordcheck = new_node->word;
		//printf("The word being checked is %s\n",new_node->word);
	 //read the line
	 //split the line on spaces
         //For each word in line:
		//printf("fscanf word: %s\n",new_node->word);

	      if (new_node->word != NULL)
	      {
		//int len1 = strlen(new_node->word);
		char* newString;
		//char* newString2[len1+1];
		newString= strtok(new_node->word, " ,.-");
		//newString= strtok(new_node->word, " ,-");
		while (newString!=NULL)
		 {
		//printf("strok word: %s\n",newString);

		   //if (check_word(new_node->word, hashtable) == false)

		  if (strlen(newString) <= LENGTH)
		  {
		   //newString2[len1] - '\0';
		   if (check_word(newString, hashtable) == false)
  	             //If not check_word(word):
		   {
                        //Append word to misspelled.
                        //Increment num_misspelled.
			//misspelled[num_misspelled] = newString;
			//strcpy(misspelled[num_misspelled],newString);
			misspelled[num_misspelled] = malloc(strlen(newString));
			strcpy(misspelled[num_misspelled],newString);
	           	num_misspelled += 1;
	//memset(misspelled[num_misspelled], 0, sizeof misspelled[num_misspelled]);
	//misspelled[num_misspelled][sizeof(misspelled[num_misspelled])-1]='\0';
	//strncpy(misspelled[num_misspelled],newString, sizeof(misspelled[num_misspelled])-1);
		//printf("misspell: %s\n",newString);
		//printf("misspell: %s\n",misspelled[num_misspelled]);
		//printf("number: %d\n",num_misspelled);

		    }
		   } else {
			num_misspelled += 1;
		   }
		   newString= strtok(NULL, " ,.-");
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
   //   FILE* fpdict = fopen(dictionary_file, "r");

	FILE* the_dictionary;    
    	the_dictionary = fopen(dictionary_file, "r"); 


      if (the_dictionary == NULL)
         {
          //printf("Could not open %s.\n", dictionary_file);
          //unload();
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

        //free(new_node);
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
    
    // Convert word to lowercase to accurately compare to hash table.
    for (int i = 0; i < word_length; i++)
    {
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
    // Add null character to end of char array.
    lower_word[word_length] = '\0';
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
    
    return false;


/*
    //printf("check_word: %s\n",word);

    if (strlen(word) >= LENGTH)
    {
        return false;
    }



    //char tmp[length + 1];
    int lenghtw = strlen(word);
    char tmp[lenghtw + 1];
    for (int i = 0; i < lenghtw; i++)
    {
        tmp[i] = tolower(word[i]);
    }

    //printf("check_word lower: %s\n",tmp);

    tmp[length] = '\0';

    //printf ("word:%s\n", word);
    //printf ("tmp:%s\n", tmp);

//	printf("char:%s\n", tmp[i]);
//      if (! ispunct(tmp[i])) {



    //int index = hash_function(tmp);
    int index = hash_function(word);

    //printf("check_word index: %d\n",index);


    if (hashtable[index] == NULL)
    {
        //printf("Word %s \n",word);
        //printf("spell check: false \n");
        return false;
    }
    node* cursor = hashtable[index];

    while(cursor != NULL)
    {
        //if(strcmp(tmp, cursor -> word) == 0)
        if(strcmp(word, cursor -> word) == 0)
        {
            //printf("Word %s \n",cursor->word);
            //printf("spell check: true \n");
            return true;
        }
        cursor = cursor -> next;
    }
        //printf("Word %s \n",word);
        //printf("spell check: false \n");
    return false;



    Remove punctuation from beginning and end of word.
    Set int bucket to the output of hash_function(word).
    Set hashmap_t cursor equal to hashmap[bucket].
    While cursor is not NULL:
        If word equals cursor->word:
            return True.
        Else if lower_case(word) equals curosr->word:
            return True.
        Set curosr to cursor->next.
    return False.

*/


}






/*
//Determine the length of the word
   int len = strlen(word);

   char copy[len+1];

   for (int i = 0; i < len; i++)
   {
       copy[i] = tolower(word[i]);
   }

   copy[len] = '\0';
   int hashed = hash(copy) % HASH_SIZE;

   node *head = hashtable[hashed];



   if(head != NULL)
   {
       node *cursor = head;
       // Treverse the linked list
       while (cursor != NULL)
       {
        if (strcasecmp(cursor->word, word) != 0)
        {
            cursor = cursor->next;
        }
        else
        {
            return true;
        }
    }

  }
*/


