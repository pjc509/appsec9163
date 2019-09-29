#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <check.h>

//#define DICTIONARY "wordlist1.txt"
#define DICTIONARY "wordlist.txt"
//#define TESTDOC "test_w.txt"
#define TESTDOC "test_w.txt"

int main()

    {
/*
	Test dictionary load
*/

    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "ethics";
    const char* incorrect_word = "Caoimh­n";
    check_word(correct_word, hashtable);
    check_word(incorrect_word, hashtable);

    char *misspelled[MAX_MISSPELLED];
    //FILE *fp = fopen("test_w.txt", "r");
    FILE *fp = fopen("2cities1.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    printf("Misspelled words: %d\n",num_misspelled);
    for (int i = 0; i < num_misspelled; i++)
    {
    printf("Misspelled words: %s\n",misspelled[i]);
    }



/*

      FILE *fp = fopen(TESTDOC, "r");
      if (fp == NULL)
         {
          printf("Could not open %d.\n", TESTDOC);
          //unload();
          return 0;    
          }
      else
        {
	int wordCount = 0;
	char *wordcheck[LENGTH+1];
        //node* new_node = malloc(sizeof(node));
	int num_misspelled = check_words(fp, hashtable, wordcheck);
          printf("number of misspelled %s.\n", num_misspelled);

	}
*/


    return 0;
    }

