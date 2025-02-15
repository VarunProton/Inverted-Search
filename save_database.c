#include "main.h"

// Function to save the hash table database into a file
void save_database(main_nd **hash, char *file) {
    // Open the file in write mode
    FILE *fptr = fopen(file, "w");
    
    // Check if the file opened successfully
    if (fptr == NULL) {
        printf("Error: Unable to open file %s for writing.\n", file);
        return;
    }
    
    // Loop through all 27 hash table slots
    for (int i = 0; i < 27; i++) {
        // If the hash slot is empty, continue to the next iteration
        if (hash[i] == NULL)
            continue;
        
        main_nd *temp = hash[i];
        
        // Traverse the main nodes
        while (temp != NULL) {
            // Write the main node's index, word, and file count to the file
            fprintf(fptr, "#%d;%s;%d", i, temp->word, temp->file_count);
            
            sub_nd *temp2 = temp->sublink;
            
            // Traverse the sub-nodes and write their details to the file
            while (temp2 != NULL) {
                fprintf(fptr, ";%s;%d", temp2->file_name, temp2->word_count);
                temp2 = temp2->sublink;
            }
            
            // End the line with '#' followed by a newline
            fprintf(fptr, "#\n");
            
            // Move to the next main node
            temp = temp->mainlink;
        }
    }
    
    // Close the file
    fclose(fptr);
}