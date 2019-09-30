#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"

START_TEST(test_check_word_normal)
{
    //test1 - word in dictionary
    //test2 - word not in dictionary
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* incorrect_word = "CaoimhÃ­n";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST

START_TEST(test_check_word_format)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    //test10 - work contains special character at end
    const char* correct_word = "Justice?";
    //test9 - word contains special character
    const char* incorrect_word = "?Jus?tice?";
    //test8 - word contains special character
    const char* incorrect_word2 = "Justice2";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(incorrect_word, hashtable));
    ck_assert(!check_word(incorrect_word2, hashtable));
}
END_TEST

START_TEST(test_check_mixed_case)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    //test5 - word is in upper case
    const char* correct_word = "JUSTICE";
    const char* incorrect_word = "?JuS?TIce?";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST

START_TEST(test_check_special_char)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "JUSTICE";
    const char* incorrect_word = "https://news.google.com/?tab=rn&hl=en-US&gl=US&ceid=US:en";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST


START_TEST(test_check_word_buffer_overflow)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    //test 14 - test buffer overflow
    char incorrect_word[500000];
    for(int i = 0; i < 499999; i++)
        incorrect_word[i] = 'A';
    incorrect_word[499999] = 0;
    ck_assert(!check_word(incorrect_word, hashtable));
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_mixed_case);
    tcase_add_test(check_word_case, test_check_special_char);
    tcase_add_test(check_word_case, test_check_word_format);
    //tcase_add_test(check_word_case, test_check_word_buffer_overflow);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}


