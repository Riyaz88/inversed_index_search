#include"inversed.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 /*   
    ->create database
      ->open file
      ->fetch words
      ->generate key
      ->check existence and store it
      ->close file
*/

void create_database(File_Names *files_head,Main_Node *array[],Stored_File_Names *stored_files_head)
{
    if(stored_files_head != NULL)
    {
        File_Names *files_temp = files_head;
        Stored_File_Names *stored_files_temp;

        while(files_temp != NULL)
        {
           stored_files_temp = stored_files_head;
            while(stored_files_temp != NULL)
            {
                if(!strcmp(files_temp->file_names,stored_files_temp->file_names))
                {
                    printf("%s file already exist !\n",files_temp->file_names);
                    return;
                }
                stored_files_temp = stored_files_temp->link;
            }
            files_temp = files_temp->link;
        }
    }

    char word[20],key;
    while(files_head != NULL)
    {
        rewind(files_head->file_ptr);
        while(fscanf(files_head->file_ptr,"%s",word) != EOF)
        {
            key = generate_key(word);
            store_data(files_head,array,key,word);
        } 
        files_head = files_head->link;
    }
    printf("INFO : Database created Successfully !\n");
}
void store_data(File_Names *file_head,Main_Node *array[],char key,char *word)
{
    Main_Node *temp_main_node;
    Main_Node *curr_main_node;
    Main_Node *prev_main_node;

    Sub_Node *curr_sub_node;
    Sub_Node *prev_sub_node;
    char word_flag,file_name_flag;

    if(array[key] == NULL)
    {
        create_main_node(&temp_main_node,file_head,word);
        array[key] = temp_main_node;
        return;
    }

    curr_main_node = array[key];
    prev_main_node = array[key];
    
    while(curr_main_node != NULL)
    {
        word_flag = strcmp(curr_main_node->word,word);
        if(word_flag == 0)
        break;
        prev_main_node = curr_main_node;
        curr_main_node = curr_main_node->main_link;
    }

    if(word_flag != 0)
    {
        create_main_node(&temp_main_node,file_head,word);
        prev_main_node->main_link = temp_main_node;
        return;
    }

    curr_sub_node = curr_main_node->sub_link;
    prev_sub_node = curr_main_node->sub_link;

    while(curr_sub_node != NULL)
    {
        file_name_flag = strcmp(curr_sub_node->file_name,file_head->file_names);
        if(file_name_flag == 0)
        break;
        prev_sub_node = curr_sub_node;
        curr_sub_node = curr_sub_node->link;  
    }

    if(file_name_flag != 0)
    {
        create_sub_node(&prev_sub_node->link,file_head);
        curr_main_node->file_count++;
        return;
    }
    
    curr_sub_node->word_count++;
    
}

void create_main_node(Main_Node **temp_main_node,File_Names *file_head,char* word)
{
    Sub_Node *temp_sub_node;
    create_sub_node(&temp_sub_node,file_head);

    *temp_main_node = malloc(sizeof(Main_Node));
    if(*temp_main_node == NULL)
    {
        printf("ERROR : UNABLE TO CREATE MEMORY FOR MAIN NODE !\n");
        exit(1);
    }
    strcpy((*temp_main_node)->word,word);
    (*temp_main_node)->file_count = 1;
    (*temp_main_node)->sub_link = temp_sub_node;
    (*temp_main_node)->main_link = NULL;
    
}

void create_sub_node(Sub_Node **temp_sub_node,File_Names *file_head)
{
    *temp_sub_node = malloc(sizeof(Sub_Node));
    if(*temp_sub_node == NULL)
    {
        printf("ERROR : UNABLE TO CREATE MEMORY FOR SUB NODE !\n");
        exit(1);
    }
    strcpy((*temp_sub_node)->file_name,file_head->file_names);
    (*temp_sub_node)->word_count = 1;
    (*temp_sub_node)->link = NULL;

}

char generate_key(char *word)
{
    if(word[0] > 64 && word[0] < 91)
    return word[0] - 65;
    else if(word[0] > 96 && word[0] < 123)
    return word[0] - 97;
    else if(word[0] > 47 && word[0] < 58)
    return 26;
    else
    return 27;
}
