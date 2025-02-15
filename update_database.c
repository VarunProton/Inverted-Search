#include "main.h"

// Function to update the hash table from a backup file
int update_database(main_nd **hash, char *backup_file) {
    // Open the file in read mode
    FILE *fptr = fopen(backup_file, "r");
    
    // Check if the file opened successfully
    if (fptr == NULL) {
        printf("Error: Unable to open file %s for reading.\n", backup_file);
        return FAILURE;
    }
    
    // Validate the first and last characters of the file
    long l = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    char first = fgetc(fptr);
    fseek(fptr, l, SEEK_SET);
    char last = fgetc(fptr);
    rewind(fptr);
    
    if (first != '#' || last != '#') {
        printf("The file is not valid.\n");
        fclose(fptr);
        return FAILURE;
    }
    
    // Check if the hash table is already present
    for (int i = 0; i < 27; i++) {
        if (hash[i] != NULL) {
            printf("Hash table is already present.\n");
            fclose(fptr);
            return FAILURE;
        }
    }
    
    char line[200];
    
    // Read each line from the file until EOF
    while (fscanf(fptr, "%s", line) != EOF) {
        char delim[3] = "#;";
        char *token = strtok(line, delim); // Extract each token
        
        int index = myatoi(token); // Create the index
        main_nd *mainnode = create_mainnode(); // Create the main node
        
        token = strtok(NULL, delim);
        strcpy(mainnode->word, token); // Copy the word
        
        token = strtok(NULL, delim);
        int filecount = myatoi(token); // Extract the file count
        mainnode->file_count = filecount;
        
        sub_nd **temp = &mainnode->sublink; // Assign it to temp link
        
        // Create and populate subnodes
        for (int i = 0; i < filecount; i++) {
            sub_nd *subnode = create_subnode();
            
            token = strtok(NULL, delim);
            strcpy(subnode->file_name, token); // Extract the file name
            
            token = strtok(NULL, delim);
            int wc = myatoi(token); // Convert to integer
            subnode->word_count = wc;
            
            *temp = subnode; // Append at the last
            temp = &subnode->sublink; // Update temp to subnode->sublink
            
            add_to_list(&updated_list, subnode->file_name);
        }
        
        main_nd *maintemp = hash[index];
        
        // If hash[index] is NULL, assign the created node to hash table
        if (maintemp == NULL) {
            hash[index] = mainnode;
        } else {
            // Traverse till the last node and then assign
            while (maintemp->mainlink != NULL) {
                maintemp = maintemp->mainlink;
            }
            maintemp->mainlink = mainnode;
        }
    }
    
    fclose(fptr);
    return SUCCESS;
}
