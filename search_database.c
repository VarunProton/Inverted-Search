#include"main.h"

void search_word(main_nd**hash,char*word)
{
    int flag=0;
    // int index = my_to_lower(word[0]) - 97;//convert this to index
    // if (index < 0 || index > 25)
    //             index = 26;
    int index;
    if (isupper(word[0]))  // Check if it's an uppercase letter
        index = word[0] - 'A'; // Convert to index (0-25)
    else if (islower(word[0]))  // Check if it's a lowercase letter
        index = word[0] - 'a'; // Convert to index (0-25)
    else if (isdigit(word[0]))  // Check if it's a digit (0-9)
        index = 26;
    else  // Special characters
        index = 27;
    main_nd*temp=hash[index];
    while(temp!=NULL)
    {
        if(strcmp(word,temp->word)==0)//search for the word match
        {
            flag=1;
            printf("The word \"%s\" is present.\n",word);
            sub_nd*temp2=temp->sublink;
            printf("\t\tFile name \t Word count\n");
            printf("\t\t----------------------------\n");
            while(temp2!=NULL)//print the associated file names and word counts
            {
                printf("\t\t%s \t\t %d\n",temp2->file_name,temp2->word_count);
                temp2=temp2->sublink;
            }
        }
        temp=temp->mainlink;
    }
    if(flag==0)//if temp is null then the word is not found
    {
        printf("The word \"%s\" is not present.\n",word);
    }

}