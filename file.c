// Author: Sean Davis
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"
#include "vector.h"

FILE* count_records(const char *filename, int *individual_count, 
  int *family_count)
{
  char line[1000];
  FILE *fp = fopen(filename, "r");
  
  if(fp == NULL)
  {
    printf("Unable to read %s.\n", filename);
    exit(1);
  }  // if unable to open file
  
  *individual_count = *family_count = 0;
  
  while(fgets(line, 1000, fp) != NULL)
  {

    if(strstr(line, "INDI") && line[0] == '0')
      (*individual_count)++;
    
    if(strstr(line, "FAM") && line[0] == '0')
      (*family_count)++;
  } // while more in file
  
  rewind(fp);
  return fp;
} // count_records()

char* read_other(char *line, FILE *fp)
{
  char *ptr;

  while((ptr = fgets(line, 1000, fp)) != NULL && line[0] != '0');
  
  return ptr;
} //read_other()


char* get_ID(char *line)
{
  char *temp, *ptr = strrchr(line, '@');
  *ptr = '\0';
  ptr = strchr(line, '@');
  temp = (char*) malloc(strlen(ptr));
  strcpy(temp, ptr + 1);
  return temp;
} // get_ID()


char* read_indi(int *individual_count, char *line,
  FILE *fp, Individual *individuals)
{
  char *ptr, name[80];

  individuals[*individual_count].INDI = get_ID(line);
  
  while((ptr = fgets(line, 1000, fp)) != NULL && line[0] != '0')
  {
    if((ptr = strstr(line, "NAME")) != NULL)
    {
      strtok(ptr, " /");
      name[0] = '\0';
     
      ptr = strtok(NULL, " /\n");
      
      if(ptr)
        strcpy(name, ptr);
   
      while((ptr = strtok(NULL, " /\n\r")) != NULL)
        sprintf(name, "%s %s", name, ptr);
      
      individuals[*individual_count].NAME = (char*) malloc(strlen(name) + 1);
      strcpy(individuals[*individual_count].NAME, name);
    } // if a NAME tagged line
    else // not NAME
      if(strstr(line, "FAMC"))
        individuals[*individual_count].FAMC = get_ID(line);
      else
        if(strstr(line, "FAMS"))
          individuals[*individual_count].FAMS = get_ID(line);
  } // while more in the record
  
  (*individual_count)++;
  return ptr;
}  // read_indi()


void add_child(char *line, Family *family)
{
  int i;
  char **temp;
  
  temp = (char**) malloc((family->chil_count + 1) * sizeof(char*));
  
  for(i = 0; i < family->chil_count; i++)
    temp[i] = family->CHILs[i];
  
  temp[i] = get_ID(line);
  free(family->CHILs);
  family->CHILs = temp;
  family->chil_count++;
}  // add_child()


char* read_family(int *family_count, char *line, FILE *fp, Family *families)
{
  char *ptr;
  
  families[*family_count].FAM = get_ID(line);
  
  while((ptr = fgets(line, 1000, fp)) != NULL && line[0] != '0')
  {
    if(strstr(line, "HUSB"))
       families[*family_count].HUSB = get_ID(line);
    
    if(strstr(line, "WIFE"))
       families[*family_count].WIFE = get_ID(line);
   
    if(strstr(line, "CHIL"))
      add_child(line, &families[*family_count]);
  } // while more in record
  
  (*family_count)++;
  return ptr;
}  // read_indi()

void read_file(FILE *fp, Individual *individuals, Family *families)
{
  char line[256], *ptr;
  int individual_count = 0, family_count = 0;
  
  ptr = fgets(line, 256, fp);
  
  while(ptr != NULL)
  {
    if(strstr(line, "INDI"))
      ptr = read_indi(&individual_count, line, fp, individuals);
    else
      if(strstr(line, "FAM"))
        ptr = read_family(&family_count, line, fp,families);
      else
        ptr = read_other(line, fp);
    
  } // while more in the file
} // read_file()
