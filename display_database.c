#include "main.h"

// Function to display the database
void display_database(main_nd **hash) 
{
    // Print table headers
    printf("\t\t\t%-8s %-10s %-10s %-15s %-10s\n", 
           "Index", "Word", "Filecount", "Filename", "Wordcount");
    printf("\t\t\t----------------------------------------------------------\n");

    // Loop through each index of the hash table (0 to 26)
    for (int i = 0; i < 28; i++) 
    {
        // If the current hash index is empty, continue to the next index
        if (hash[i] == NULL)
            continue;

        // Pointer to traverse the main nodes
        main_nd *temp = hash[i];

        // Traverse through the main nodes at this index
        while (temp != NULL) 
        {
            // Pointer to traverse the sub nodes (files associated with the word)
            sub_nd *temp1 = temp->sublink;

            // Flag to track the first line of the main node
            int first_line = 1;

            // Loop through the number of files associated with the word
            for (int j = 0; j < temp->file_count; j++) 
            {
                // If not the first line, print empty spaces for index, word, and file count
                if (!first_line)
                    printf("\t\t\t%-8s %-10s %-10s", "", "", ""); 
                else 
                    // Print the main node details (Index, Word, File Count)
                    printf("\t\t\t%-8d %-10s %-10d", i, temp->word, temp->file_count);

                // Print sub node details (Filename and Word Count)
                if (temp1 != NULL) 
                {
                    printf("%-15s %-10d\n", temp1->file_name, temp1->word_count);
                    temp1 = temp1->sublink; // Move to the next sub node
                } 
                else 
                    printf("%-15s %-10s\n", "N/A", "N/A"); // If no sub node exists

                       first_line = 0; // Set flag to indicate first line is printed
            }

            // Move to the next main node in the list
            temp = temp->mainlink;
        }
    }
}
