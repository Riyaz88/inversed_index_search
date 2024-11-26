#include"inversed.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void save_database(Main_Node *array[],char *file_name,File_Names *files_head)
{
    if(strstr(file_name,".txt") != NULL)
    {
        if(strcmp(strstr(file_name,".txt"),".txt") != 0)
        {
            printf("Error : Invalid File Name ! File must contain (.txt)\n");
            return;
        }  
    }
    else
    {
        printf("Error : Invalid File Name ! File must contain (.txt)\n");
        return;
    }

    if(is_database_empty(array))
    {
        printf("INFO : Database is Empty !\n");
        return;
    }

    Main_Node *temp_main_node;
    Sub_Node *temp_sub_node;

    FILE * file_ptr = fopen(file_name,"w");
    if(file_ptr == NULL)
    {
        printf("Error : unable to open file %s\n",file_name);
        return;
    }

    fprintf(file_ptr,"%c",'#');
    while (files_head != NULL)
    {
        fprintf(file_ptr,"%s;",files_head->file_names);
        files_head = files_head->link;
    }
    fprintf(file_ptr,"%c\n",'#');
    
    for(char i = 0;i < 28;i++)
    {

        if(array[i] != NULL)
        {

            temp_main_node = array[i];         
            while(temp_main_node != NULL)
            {
                fprintf(file_ptr,"%c",'#');
                fprintf(file_ptr,"%d;",i);
                fprintf(file_ptr,"%s;%ld;",temp_main_node->word,temp_main_node->file_count);
                temp_sub_node = temp_main_node->sub_link;
                while(temp_sub_node != NULL) 
                {
                    fprintf(file_ptr,"%s;%ld;",temp_sub_node->file_name,temp_sub_node->word_count);
                    temp_sub_node = temp_sub_node->link;
                }
                fprintf(file_ptr,"%c\n",'#');
                temp_main_node = temp_main_node->main_link;
            }     
        }
    }
    printf("INFO : Data Backup Successfull !\n");
}