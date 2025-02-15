//Name:VARUN H
//DESCRIPTION:INVERTED SEARCH
//DATE:12/02/2025
#include "main.h"

Slist *file_list = NULL;
Slist *updated_list = NULL;
Slist *unique_list = NULL;//after the updation if the given file is different from the updated files it will store that
int count = 0;
int updated_count = 0;
main_nd *hash[28] = {NULL};

int main(int argc, char *argv[])
{
    char word[50];
    char file[30];
    char backupfile[30];
    int create_flag=0;
    int update_flag=0;

    validation(argc,argv);
    printf("The files are:\n");
    print_list(file_list);
    int choice;
    printf("Number of files stored successfully: %d\n",count);
    printf("1.create database\n2.Display database\n3.Search database\n4.Save database\n5.Update database\n6.Exit\n");

    while(1)
    {
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice)
        {
            default:
                printf("Invalid Choice.\n");
                break;

            case 1:
                if (create_flag == 1) // Check if the creation is done
                {
                    printf("Database can be created only once.\n");
                }
                if (create_flag == 0) // If not, create the hash table
                {
                    if (update_flag == 0) // Check if updation not done
                    {
                        if (create_database(count, file_list) == SUCCESS) // Create the database
                            create_flag = 1;
                        printf("Database is Successfully created.\n");
                    }
                    if (update_flag == 1) // If updation already done, create the hash table for only unique files
                    {
                        // int updated_count = updatedd_list(&file_list, &updated_list, &unique_list);
                        if (create_database(updated_count, unique_list) == SUCCESS)
                            create_flag = 1;
                        print_list(unique_list);
                        printf("Database is Successfully created.\n");
                    }
                }
                break;

            case 2:
                display_database(hash); // Display the database
                break;

            case 3:
                printf("Enter the word to be searched: ");
                scanf("%s", word);
                search_word(hash, word); // Search for the given word
                break;

            case 4:
                printf("Enter the file name: ");
                scanf("%s", file);
                char *extension = strrchr(file, '.');
                if (strcmp(extension, ".txt") == 0) // Check if the backup file has the extension .txt
                {
                    save_database(hash, file); // Save to the given file
                    printf("File is successfully saved.\n");
                }
                else
                {
                    printf("The file should have extension .txt\n");
                }
                break;

            case 5:
                if (create_flag == 1)
                {
                    printf("After creating, updating is not possible\n");
                    goto label;
                }
                if (update_flag == 1) // Check if database is already updated
                {
                    printf("Database can be updated only once.\n");
                }
                if (update_flag == 0) // If not, check the type of file; it should be of the type .txt
                {
                    printf("Enter the backup file name: ");
                    scanf("%s", backupfile);
                    char *ext = strrchr(backupfile, '.');
                    if (strcmp(ext, ".txt") == 0)
                    {
                        if (update_database(hash, backupfile) == SUCCESS)
                        {
                            printf("The files include:\n");
                            print_list(updated_list);
                            printf("File is successfully updated to the hash table.\n");
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        printf("The file should have extension .txt\n");
                    }
                    update_flag = 1;
                }
            label:
                break;

            case 6:
                printf("Invalid choice\n");
                exit(0);
                break;
        }
    }
}