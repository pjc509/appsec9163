#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <check.h>

#define DICTIONARY "wordlist.txt"
#define TESTDOC "test1.txt"

//bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[])

//int main(const char* dict_file, const char* test_file)
int main(int argc, char **argv)

    {
/*
	Test dictionary load
*/
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(argv[2], hashtable);
    //char* expected[3];
    //expected[0] = "sogn";
    //expected[1] = "skyn";
    //expected[2] = "betta";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen(argv[1], "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);

    printf("Misspelled words: %d\n",num_misspelled);
    for (int i = 0; i < num_misspelled; i++)
    {
    printf("Misspelled words: %s\n",misspelled[i]);
    }
    printf("Misspelled words: %d\n",num_misspelled);



    return 0;
    }

