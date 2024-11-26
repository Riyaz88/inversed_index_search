#include"inversed.h"
#include<stdio.h>
#include<string.h>

void search_database(Main_Node *array[],char *word)
{
    if(is_database_empty(array))
    {
        printf("INFO : Database is Empty !\n");
        return;
    }
    
    char key = generate_key(word);
    Main_Node *temp_main_node;
    Sub_Node *temp_sub_node;
    char word_flag;

    if(array[key] == NULL)
    {
        printf("%s Word not exist in database\n",word);
        return;
    }
    
    temp_main_node = array[key];
    while(temp_main_node != NULL)
    {
        word_flag = strcmp(temp_main_node->word,word);
        if(word_flag == 0)
        break;
        temp_main_node = temp_main_node->main_link;
    }
    
    if(word_flag != 0)
    {
        printf("%s Word not exist in database\n",word);
        return;
    }
    
    printf("%s Word exist in %ld file(s)\n",temp_main_node->word,temp_main_node->file_count);
    temp_sub_node = temp_main_node->sub_link;

    while(temp_sub_node != NULL)
    {
        printf("%s - %ld time(s)\n",temp_sub_node->file_name,temp_sub_node->word_count);
        temp_sub_node = temp_sub_node->link;
    }

}