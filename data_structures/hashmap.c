#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

int hash(char *str, int length)
{
    printf("what is the string read:%s %d\n", str, length);
    int corr_hash = 0;
    for (int i = 0; i < length; i++)
    {
        corr_hash += (int)str[i];
    }
    return corr_hash % HASHTABLE_SIZE;
}

hashtable initHashtable()
{
    hashtable ht;
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        ht.table[i] = malloc(sizeof(hashtable_node *));
        ht.table[i]->idx = i;
        ht.table[i]->bucket_ptr = NULL;
    }
    return ht;
}

bool insert(hashtable *ht, char *str, int length, token_names tok)
{
    int getHash = hash(str, length);
    bucket_node *ptr = ht->table[getHash]->bucket_ptr;

    if (ptr == NULL)
    {
        ptr = malloc(sizeof(bucket_node *));
        ptr->str = str;
        ptr->tok = tok;
        ptr->next = NULL;
        ht->table[getHash]->bucket_ptr = ptr;
        return true;
    }
    while (ptr->next != NULL)
    {

        ptr = ptr->next;
    }
    ptr->next = malloc(sizeof(bucket_node *));
    ptr->next->str = str;
    ptr->next->tok = tok;
    ptr->next->next = NULL;
    return false;
}

bool exists(hashtable ht, char *str, int length)
{
    int getHash = hash(str, length);
    printf("hash:%d\n", getHash);
    bucket_node *ptr = ht.table[getHash]->bucket_ptr;
    while (ptr != NULL)
    {
        printf("inside exists %s\n", ptr->str);
        if (strcmp(ptr->str, str) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool delete(hashtable ht, char *str, int length)
{
    if (!exists(ht, str, length))
        return false;
    int getHash = hash(str, length);
    bucket_node *ptr = ht.table[getHash]->bucket_ptr;
    if (strcmp(ptr->str, str) == 0)
    {
        bucket_node *temp = ptr;
        ht.table[getHash]->bucket_ptr = ptr->next;
        free(temp);
        return true;
    }
    bucket_node *prev = ptr;
    while (ptr != NULL)
    {
        if (strcmp(ptr->str, str) == 0)
        {
            prev->next = ptr->next;
            free(ptr);
            return true;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    // probably wont reach here
    return false;
}

token_names get(hashtable *ht, char *str, int length)
{
    int getHash = hash(str, length);

    bucket_node *ptr = ht->table[getHash]->bucket_ptr;
    while (ptr != NULL)
    {
        if (strcmp(ptr->str, str) == 0)
        {
            return ptr->tok;
        }
        ptr = ptr->next;
    }
    printf("Entered string does not exist in the hashtable!");
    return -1;
}

// int main()
// {
//     hashtable ht = initHashtable();
//     insert(&ht, "jnt", 3, "INTEGER");
//     insert(&ht, " ", 1, "SPACE");
//     printf(get(&ht, "jnt", 3));
//     printf("%d", delete (ht, " ", 1));
//     printf(get(&ht, " ", 1));
// }