#include"inversed.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void update_database(Main_Node *array[],char *file_name,Stored_File_Names **stored_files_head)
{
    // validate file name
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

    //check if database Empty
    if(!is_database_empty(array))
    {
        printf("Error : Update Operation Cannot be performed after Create Operation !\n");
        return;
    }

    FILE *file_ptr = fopen(file_name,"r");
    if(file_ptr == NULL)
    {
        printf("Error : Cannot Open File or File Not Exist %s!\n",file_name);
        return;
    }
    

    char buffer[1000];
    rewind(file_ptr);
    char *token;
    fscanf(file_ptr,"%s",buffer);
    if(buffer[0] != '#')
    {
    printf("Error : %s Not a valid backup File !",file_name);
    return;
    }
    token = strtok(buffer+1,";");
    Stored_File_Names *temp = *stored_files_head;
    while(token != NULL)
    {
        Stored_File_Names *new = malloc(sizeof(Stored_File_Names));
        if(new == NULL)
        {
            printf("ERROR : Unable to allocate memory for stored_file_names\n");
            return;
        }
        strcpy(new->file_names,token);
        new->link = NULL;
        if(*stored_files_head == NULL)
        {
            *stored_files_head = new;
            token = strtok(NULL,";#");
            temp = new;
            continue;
        }
        temp->link = new;
        temp = new;  

        token = strtok(NULL,";#"); 
    }
    
    char index;
    Main_Node *new_main_node;
    Sub_Node *new_sub_node;
    Main_Node *temp_main_node;
    Sub_Node *temp_sub_node;
    while(fscanf(file_ptr,"%s",buffer) != EOF)
    {
       if(buffer[0] != '#')
       {
        printf("Error : %s Not a valid backup File !",file_name);
        return;
       }
       // Allocating values to main node
       new_main_node = malloc(sizeof(Main_Node));
       if(new_main_node == NULL)
       {
        printf("Error : Cannot alloacate memory for main node\n");
        return;
       }

       // Allocating memory to first sub node 
       new_sub_node = malloc(sizeof(Sub_Node));
       if(new_sub_node == NULL)
       {
        printf("Error : Cannot alloacate memory for sub node\n");
        return;
       }

       //allocating values into main node
       index =  atoi(strtok(buffer+1,";"));
       strcpy(new_main_node->word,strtok(NULL,";"));
       new_main_node->file_count = atoi(strtok(NULL,";"));
       new_main_node->main_link = NULL;
       new_main_node->sub_link = new_sub_node;

        //ckecking if array[n] is null
       if(array[index] == NULL)
       {
        array[index] = new_main_node;
       }
       else
       {      
        temp_main_node = array[index];
        while(temp_main_node->main_link != NULL)
        {
            temp_main_node = temp_main_node->main_link;
        }
        temp_main_node->main_link = new_main_node;
       }
       
       //Allocating values to first sub node
       strcpy(new_sub_node->file_name,strtok(NULL,";"));
       new_sub_node->word_count = atoi(strtok(NULL,";"));
       new_sub_node->link = NULL;

       temp_sub_node = new_sub_node;
       for(int iter = 1;iter < new_main_node->file_count;iter++)
       {
            new_sub_node = malloc(sizeof(Sub_Node));
            if(new_sub_node == NULL)
            {
            printf("Error : Cannot alloacate memory for sub node\n");
            return;
            }

            strcpy(new_sub_node->file_name,strtok(NULL,";"));
            new_sub_node->word_count = atoi(strtok(NULL,";"));
            new_sub_node->link = NULL;

            temp_sub_node->link = new_sub_node;
            temp_sub_node = new_sub_node;
       }
    }
    printf("INFO : Update Successfull !\n");
}

Status is_database_empty(Main_Node *array[])
{
    char index = 0;
    while (index < 28)
    {
       if(array[index] != NULL)
       return FAILURE;
       index++;
    }
    return SUCCESS;
}


