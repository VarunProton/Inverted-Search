#include "main.h"

// Function to validate and process the input files
void validation(int size, char *arr[])
{
    for (int i = 1; i < size; i++)
    {
        // Check if the file has a .txt extension
        if (check_extension(arr[i]) == SUCCESS)
        {
            FILE *fptr = fopen(arr[i], "r");
            
            // Check if the file exists
            if (fptr != NULL)
            {
                fseek(fptr, 0, SEEK_END);
                
                // Check if the file is non-empty
                if (ftell(fptr) != 0)
                {
                    fclose(fptr);
                    
                    // Check if the file is already in the list
                    if (check_list(arr[i], file_list) == SUCCESS)
                    {
                        // Insert the file into the list
                        if (insert_at_last(arr[i], &file_list) == SUCCESS)
                        {
                            printf("%s is successfully stored in the list.\n", arr[i]);
                            count++; // Increment file count
                        }
                        else
                        {
                            printf("Failed to store the file.\n");
                        }
                    }
                    else
                    {
                        printf("%s is already stored in the list.\n", arr[i]);
                    }
                }
                else
                {
                    fclose(fptr);
                    printf("%s file is empty.\n", arr[i]);
                }
            }
            else
            {
                printf("%s is not present in the directory.\n", arr[i]);
            }
        }
        else
        {
            printf("%s does not have .txt extension.\n", arr[i]);
        }
    }
}

// Function to check if the file has a .txt extension
int check_extension(char *str)
{
    char *extension = strchr(str, '.');
    
    // Validate if the extension is .txt
    if (extension != NULL && strcmp(extension, ".txt") == 0)
    {
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}

// Function to check if the file is already in the linked list
int check_list(char *str, Slist *file_list)
{
    if (file_list == NULL)
    {
        return SUCCESS;
    }
    
    Slist *temp = file_list;
    
    while (temp != NULL)
    {
        if (strcmp(temp->file, str) == 0)
        {
            return FAILURE; // File already exists
        }
        temp = temp->link;
    }
    
    return SUCCESS;
}

// Function to insert a file at the end of the linked list
int insert_at_last(char *str, Slist **file_list)
{
    Slist *newnode = malloc(sizeof(Slist));
    
    // Check if memory allocation was successful
    if (newnode == NULL)
    {
        return FAILURE;
    }
    
    newnode->link = NULL;
    strcpy(newnode->file, str);
    
    // If list is empty, set the new node as the head
    if (*file_list == NULL)
    {
        *file_list = newnode;
        return SUCCESS;
    }
    
    // Traverse to the last node
    Slist *temp = *file_list;
    while (temp->link != NULL)
    {
        temp = temp->link;
    }
    
    temp->link = newnode; // Insert at the end
    return SUCCESS;
}

// Function to print the linked list
void print_list(Slist *head)
{
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        while (head)
        {
            printf("%s\n", head->file); // Print file name
            head = head->link; // Move to the next node
        }
    }
}
