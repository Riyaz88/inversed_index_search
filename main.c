#include<stdio.h>
#include<stdlib.h>
#include"inversed.h"
#include<string.h>

int main(int argc,char *argv[])
{
    
    //validate agrguments present or not
    if(argc == 1)
    {
       printf("ERROR : Atleast one file name must be given !\n");
       exit(1);
    }
    
    // //validate file names
    // if(!validate_file_name(argc,argv)) 
    // {
    //   printf("Error : All file must contain .txt extension !\n");
    //   exit(1);
    // } 

    Err_File_Names *err_files_head = NULL;
    Err_File_Names *temp_err_files;
    File_Names *files_head = NULL;
    Stored_File_Names *stored_files_head = NULL;
    Main_Node *array[28] = {NULL};
    int choice;
    char word[50],file_name[50];

    // Validate all files & Store correct files and Error files in seperate list
    if(validate_files(argc,argv,&err_files_head,&files_head) != SUCCESS)
    { 
        printf("File Validation Failed !\n");
        exit(1);
    }
     
   
    while(1)
    {
       printf("\n1. Create \n2. Display \n3. Search \n4. Save \n5. Update \n6. Exit \n");
       printf("Enter your Choice : ");
      if(scanf("%d", &choice) != 1)
      {
          while(getchar() != '\n');
      } 
        switch(choice)
        {
          case 1:
                  if(files_head != NULL)
                  {
                    create_database(files_head,array,stored_files_head);
                    if(err_files_head != NULL)
                    display_error_files(err_files_head);  
                  }
                  else
                  {
                    display_error_files(err_files_head);                  
                  }  
                  break;
          case 2:
                  display_database(array);
                  break;
          case 3:
                  printf("Enter Word to Search : ");
                  if(scanf("%50s",word ) != 1)
                    while(getchar() != '\n');
                  search_database(array,word);
                  break;
          case 4:
                  printf("Enter Backup FileName to  Store Backup Data : ");
                  if(scanf("%50s",file_name ) != 1)
                    while(getchar() != '\n');
                  save_database(array,file_name,files_head);
                  break;
          case 5:
                  printf("Enter Backup FileName to Update Data : ");
                  if(scanf("%50s",file_name ) != 1)
                    while(getchar() != '\n');
                  update_database(array,file_name,&stored_files_head);
                  break;
          case 6:
                 exit(0);
          default:
                  printf("Invalid Choice !\n");          
       }
  }   
}

Status validate_file_name(int argc,char **argv)
{
    char *temp;
    for(int i = 1;i < argc;i++)
    {
      temp = strstr(argv[i],".txt");
      if(temp != NULL)
      {
        if(strcmp(temp,".txt"))
        return FAILURE;
      }
      else
      return FAILURE;
    }
    return SUCCESS;
}


Status validate_files(int argc,char **argv,Err_File_Names **err_files_head,File_Names **files_head)
{
  /*
  ->validate files 
      ->check file exist
      ->check file is not duplicate
      ->check file is not empty
  */  

  FILE *file_ptr = NULL;
  char err_flag;

  for(int index = 1;index < argc;index++)
  {
    err_flag = 0;
    if(is_file_duplicate(argv,index) == FAILURE)
    {
      file_ptr = fopen(argv[index],"r");
      if(file_ptr != NULL)
      {
        if(is_file_empty(file_ptr) == SUCCESS)
        err_flag = FILE_EMPTY;
      }
      else
      err_flag = FILE_NOT_EXIST;
    }
    else
    err_flag = FILE_DUPLICATE;

    if(err_flag != 0)
    {
        Err_File_Names *new = malloc(sizeof(Err_File_Names));
        Err_File_Names *temp = *err_files_head;

        if(new == NULL)
        {
        printf("Error unable to allocate memory for error_files !\n");
        return FAILURE;
        }

        strcpy(new->file_names,argv[index]);
        new->err_flag = err_flag;
        new->link = NULL;

        if(*err_files_head == NULL)
          *err_files_head = new;
        else
        {
            while(temp->link != NULL)
            {
              temp = temp->link;
            } 
            temp->link = new;     
        }  
    }
    else
    {
       File_Names *new = malloc(sizeof(File_Names));
       File_Names *temp = *files_head;

        if(new == NULL)
        {
        printf("Error unable to allocate memory for error_files !\n");
        return FAILURE;
        }

        strcpy(new->file_names,argv[index]);
        new->link = NULL;
        new->file_ptr = file_ptr;

        if(*files_head == NULL)
          *files_head = new;
        else
        {
            while(temp->link != NULL)
            {
              temp = temp->link;
            } 
            temp->link = new;     
        }
    }   
  }
  return SUCCESS;
}

Status is_file_duplicate(char **argv, char curr_index)
{
    for(int index = 1;index < curr_index;index++)
    {
      if(!strcmp(argv[index],argv[curr_index]))
      return SUCCESS;
    }
    return FAILURE;
}

Status is_file_empty(FILE *file_ptr)
{
  fseek(file_ptr,0,SEEK_END);
  if(ftell(file_ptr)  == 0)
  return SUCCESS;
  return FAILURE;
}

void display_error_files(Err_File_Names *err_files_head)
{
  Err_File_Names *temp_err_files = err_files_head;
  printf("Error Files : \n");
  while(temp_err_files != NULL)
  {
      printf("%s ",temp_err_files->file_names);
      if(temp_err_files->err_flag == FILE_DUPLICATE)
      printf("File is Duplicate\n");
      else if(temp_err_files->err_flag == FILE_NOT_EXIST)
      printf("File Not exist\n");
      else if(temp_err_files->err_flag == FILE_EMPTY)
      printf("File is Empty\n");
      temp_err_files = temp_err_files->link;
      
  }
  printf("\n");
}
