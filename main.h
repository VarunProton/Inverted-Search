#ifndef MAIN_H
#define MAIN_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#define SUCCESS 1
#define FAILURE 2

typedef struct main_node
{
    char word[50];
    int file_count;
    struct sub_node *sublink;
    struct main_node *mainlink;
}main_nd;

typedef struct sub_node
{
    int word_count;
    char file_name[30];
    struct sub_node *sublink;
}sub_nd;

typedef struct single
{
    char file[30];
    struct single*link;
}Slist;

typedef struct doublelink
{
    struct doublelink*prev;
    int data;
    struct doublelink*next;
}Dlist;

extern Slist *file_list;
extern Slist *updated_list;
extern Slist *unique_list;
extern int count;
extern int updated_count;
extern main_nd *hash[28];

void validation(int,char*[]);
int check_list(char*,Slist*);
int check_extension(char*);
int insert_at_last(char*,Slist**);
void print_list(Slist *);
int create_database(int,Slist*);
int my_to_lower(char);
main_nd*create_mainnode();
sub_nd*create_subnode();
void display_database(main_nd **);
void search_word(main_nd **,char*);
void save_database(main_nd**,char*);
int update_database(main_nd**,char*);
int myatoi(char*);
void add_to_list(Slist **, const char *); 
int updatedd_list(Slist**,Slist**,Slist**);
int exists_in_list(Slist *, const char *);
void add_node(Slist **, const char *);
Slist *create_node(const char *);

#endif