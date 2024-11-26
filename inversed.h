#ifndef INVERSED_H
#define INVERSED_H

#include<stdio.h>

typedef enum 
{
    FAILURE,
    SUCCESS
}Status;

typedef struct Err_File_Names
{
  char file_names[20];
  char err_flag;
  struct Err_File_Names *link;
}Err_File_Names;

typedef struct Sub_Node
{
   long word_count;
   char file_name[20];
   struct Sub_Node *link;
}Sub_Node;

typedef struct Main_Node
{
   long file_count;
   char word[20];
   struct Sub_Node *sub_link;
   struct Main_Node *main_link;

}Main_Node;

typedef enum
{
   FILE_DUPLICATE = 1,
   FILE_NOT_EXIST,
   FILE_EMPTY
}file_errors;

typedef struct File_Names
{
  char file_names[20];
  FILE *file_ptr;
  struct File_Names *link;
  
}File_Names;

typedef struct Stored_File_Names
{
  char file_names[20];
  struct Stored_File_Names *link;
  
}Stored_File_Names;

void create_database(File_Names *files_head,Main_Node *array[],Stored_File_Names *stored_files_head);
void store_data(File_Names *file_head,Main_Node *array[],char key,char *word);
char generate_key(char *word);
void create_main_node(Main_Node **temp_main_node,File_Names *file_head,char* word);
void create_sub_node(Sub_Node **temp_sub_node,File_Names *file_head);

void display_database(Main_Node *array[]);
void search_database(Main_Node *array[],char *word);
void save_database(Main_Node *array[],char *file_name,File_Names *files_head);
void update_database(Main_Node *array[],char *file_name,Stored_File_Names **stored_files_head);

Status is_database_empty(Main_Node *array[]);
Status is_backup_file(FILE *file_ptr);

Status validate_file_name(int argc,char **argv);
Status validate_files(int argc,char **argv,Err_File_Names **err_files_head,File_Names **files_head);
Status is_file_duplicate(char **argv, char curr_index);
Status is_file_empty(FILE *file_ptr);
void display_error_files(Err_File_Names *err_files_head);


#endif