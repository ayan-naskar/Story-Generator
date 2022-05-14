#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "common structure.h"

void create_hash();
void increaseSize();
int hashcode1(int);
int hashcode2(int);
int getHash(char*);
void insert(char*,struct node*);
struct node* create_list();
void show_hashtable();
struct node* reference(char*);
void add_WORD(char*, char*, float);
int countKeys();

#endif