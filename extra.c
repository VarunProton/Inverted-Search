#include "main.h"

// Function to create a main node
main_nd* create_mainnode(char* str) 
{
    // Allocate memory for the main node
    main_nd* mainnode = malloc(sizeof(main_nd));

    // Check if memory allocation failed
    if (mainnode == NULL)
        return mainnode;

    // Initialize main node fields
    mainnode->mainlink = NULL;  // No link to the next main node initially
    mainnode->sublink = NULL;   // No sublink initially
    mainnode->file_count = 1;   // Set file count to 1

    // Copy the word into the main node
    strcpy(mainnode->word, str);

    return mainnode;
}

// Function to create a sub node
sub_nd* create_subnode(char* str) 
{
    // Allocate memory for the sub node
    sub_nd* subnode = malloc(sizeof(sub_nd));

    // Check if memory allocation failed
    if (subnode == NULL)
        return subnode;

    // Initialize sub node fields
    subnode->word_count = 1;   // Set word count to 1
    subnode->sublink = NULL;   // No sublink initially

    // Copy the file name into the sub node
    strcpy(subnode->file_name, str);

    return subnode;
}

int myatoi(char *str)
{
    int i=0;
    int sum=0;
    //   while((str[i]>='0' && str[i]<='9') )
    // {
    //     num=num*10 +(str[i]-48);
    //     i++;
        
    // }
    while(str[i]!='\0')
    {
     sum=sum*10 +(str[i]-48);
        i++;
    }
    return sum;
}
void add_to_list(Slist **updated_list, const char *file_name) 
{
    Slist *temp = *updated_list;
    while (temp != NULL) 
    {
        if (strcmp(temp->file, file_name) == 0) 
        {
            return;
        }
        temp = temp->link;
    }

    Slist *newnode = (Slist *)malloc(sizeof(Slist));
    // if (!newnode) 
    // {
    //     printf("Memory allocation failed.\n");
    //     return;
    // }

    strcpy(newnode->file, file_name);
    newnode->link = NULL;

    if (*updated_list == NULL) 
    {
        *updated_list = newnode;
    } 
    else 
    {
        temp = *updated_list;
        while (temp->link != NULL) 
        {
            temp = temp->link;
        }
        temp->link = newnode;
    }
}
