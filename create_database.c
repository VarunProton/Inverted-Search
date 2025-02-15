#include"main.h"
// Function to create the database
int create_database(int size, Slist *files) {
    if (files == NULL)//if not files return failure
        return FAILURE;

    Slist *temp = files;//create a temp 
    char word[50];

    for (int i = 0; i < size; i++) //run the loop size times
    {
        FILE *fptr = fopen(temp->file, "r");//open the file in the read mode
        if (fptr == NULL)
            return FAILURE;

        while (fscanf(fptr, "%s", word) != EOF)//run the loop till end of he file 
        {
            int index;
            if (isupper(word[0]))  // Check if it's an uppercase letter
                index = word[0] - 'A'; // Convert to index (0-25)
            else if (islower(word[0]))  // Check if it's a lowercase letter
                index = word[0] - 'a'; // Convert to index (0-25)
            else if (isdigit(word[0]))  // Check if it's a digit (0-9)
                index = 26;
            else  // Special characters
                index = 27;

            if (hash[index] == NULL) //if hash of index is null create a mainnode,subnode and attach to the hash table
            {
                // Create new main node and sub node
                main_nd *mainnode = create_mainnode(word);
                if (!mainnode) {
                    fclose(fptr);
                    return FAILURE;
                }

                sub_nd *subnode = create_subnode(temp->file);
                if (!subnode) {
                    fclose(fptr);
                    return FAILURE;
                }

                mainnode->sublink = subnode;
                hash[index] = mainnode;
            } else 
            {
                // Handle existing hash index
                main_nd *temp1 = hash[index];//create a temp
                main_nd *prev1 = NULL;
                int found = 0;

                while (temp1 != NULL) //till temp !=NULL
                {
                    if (strcmp(word, temp1->word) == 0) 
                    {
                        found = 1;//if same word found break
                        break;
                    }
                    prev1 = temp1;
                    temp1 = temp1->mainlink;
                }

                if (!found) 
                {
                    // Create a new main node
                    main_nd *mainnode = create_mainnode(word);
                    if (!mainnode) {
                        fclose(fptr);
                        return FAILURE;
                    }

                    sub_nd *subnode = create_subnode(temp->file);
                    if (!subnode) {
                        fclose(fptr);
                        return FAILURE;
                    }

                    mainnode->sublink = subnode;

                    if (prev1 == NULL) 
                    {
                        hash[index] = mainnode;
                    } else 
                    {
                        prev1->mainlink = mainnode;//if not found then it is new word attach at the last subnode
                    }
                } else 
                {
                    // Handle existing word
                    sub_nd *temp2 = temp1->sublink;
                    sub_nd *prev2 = NULL;
                    int sub_found = 0;

                    while (temp2 != NULL) 
                    {
                        if (strcmp(temp2->file_name, temp->file) == 0) //if same file 
                        {
                            temp2->word_count++;//increment count
                            sub_found = 1;
                            break;
                        }
                        prev2 = temp2;
                        temp2 = temp2->sublink;
                    }

                    if (!sub_found) 
                    {
                        // Add a new sub node
                        sub_nd *subnode = create_subnode(temp->file);//if different file create subnode with different file name
                        if (!subnode) {
                            fclose(fptr);
                            return FAILURE;
                        }

                        if (prev2 == NULL) 
                        {
                            temp1->sublink = subnode;
                        } else 
                        {
                            prev2->sublink = subnode;
                        }
                        temp1->file_count++;//increment file count in main node
                    }
                }
            }
        }
        fclose(fptr);
        temp = temp->link;//update the temp to next file
    }
    return SUCCESS;
}

