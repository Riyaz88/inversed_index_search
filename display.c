#include"inversed.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void display_database(Main_Node *array[])
{
    Main_Node *temp_main_node;
    Sub_Node *temp_sub_node;

    if(is_database_empty(array))
    {
        printf("INFO : Database is Empty !\n");
        return;
    }

    for(int i = 0;i < 28;i++)
    {
        if(array[i] != NULL)
        {
            temp_main_node = array[i];
            printf("[%d]\n",i);
            while(temp_main_node != NULL)
            {
              
                printf("  %-15s %-5ld file(s)   ",temp_main_node->word,temp_main_node->file_count);
                temp_sub_node = temp_main_node->sub_link;
                while(temp_sub_node != NULL)
                {
                    printf(": file : %-15s : %-5ld time(s) ",temp_sub_node->file_name,temp_sub_node->word_count);
                    temp_sub_node = temp_sub_node->link;
                }
                printf("\n");
                temp_main_node = temp_main_node->main_link;
            }     
        }
    }
}