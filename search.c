// Author: Sean Davis

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "main.h"

int family_cmp(const void *ptr, const void *ptr2)
{
  return strcmp(((Family*) ptr)->FAM, ((Family*) ptr2)->FAM);
} // individual_cmp()


void find_children(int individual_count, int family_count, 
  Individual *individuals, Family *families, char* INDI)
{
  Family family, *family_ptr;
  Individual individual_key, *individual_ptr;
  
  individual_key.INDI = INDI;
  individual_ptr = bsearch(&individual_key, individuals, individual_count, 
    sizeof(Individual), individual_cmp);
  
  if(individual_ptr == NULL)
    return;
  
  printf("%s", individual_ptr->NAME);
  family.FAM = individual_ptr->FAMS;

  if(family.FAM == NULL)
     printf(" never married.\n");
  else
  {
     family_ptr = bsearch(&family, families, family_count, sizeof(Family), 
          family_cmp);

      if(family_ptr->chil_count == 0)
        printf(" had no children.\n");
      else // had at least one child
      {
        printf(": ");
        print_children(family_ptr, individuals, individual_count);
      }
   } // else he married
} // find_children()

int find_spouse(const char* ID, int count, Family *families)
{
  int i;
  
  for(i = 0; i < count; i++)
    if(strstr(families[i].HUSB, ID) || strstr(families[i].WIFE, ID))
      return i;
  
  return -1;
} // find_IDs
 
int find_name(char name[80], int individual_count,  Individual *individuals)
{
  char  name2[80], *name_ptrs[5], *ptr;
  int count = 0, i, j;

  name[strlen(name) - 1] = '\0';
  strcpy(name2, name);
  
  for(ptr = strtok(name2, " ,\n"); ptr; ptr = strtok(NULL, " ,\n"))
    name_ptrs[count++] = ptr;
    
  for(i = 0; i < individual_count; i++)
  {
    for(j = 0; j < count; j++)
      if(strstr(individuals[i].NAME, name_ptrs[j]) == NULL)
        break;
      
    if(j == count)
      return i; // found the name
  } // for i
  
  printf("%s not found.\n", name);
  return -1;
} // find_name()


int individual_cmp(const void *ptr, const void *ptr2)
{
  return strcmp(((Individual*) ptr)->INDI, ((Individual*) ptr2)->INDI);
} // individual_cmp()


void print_children(Family *family, Individual *individuals, 
  int individual_count)
{
  int i;
  Individual individual_key, *individual_ptr;
  
  for(i = 0; i < family->chil_count; i++)
  {
    individual_key.INDI = family->CHILs[i];
    individual_ptr = bsearch(&individual_key, individuals, individual_count, 
      sizeof(Individual), individual_cmp);
    
    if(i > 0)
      printf(", ");
    
    printf("%s", individual_ptr->NAME);
  } // for i
  
  printf("\n");
} // print_children()

void printTree(int individual_count, int family_count, 
  Individual *individuals, Family *families, char *INDI)
{
  int i;
  Family family, *family_ptr;
  Individual individual_key, *individual_ptr;
  find_children(individual_count, family_count, individuals, families, INDI);
    individual_key.INDI = INDI;
  individual_ptr = bsearch(&individual_key, individuals, individual_count, 
    sizeof(Individual), individual_cmp);
  
  if(individual_ptr == NULL)
    return;
  
  family.FAM = individual_ptr->FAMS;
  
  if(family.FAM != NULL)
  {
     family_ptr = bsearch(&family, families, family_count, sizeof(Family), 
          family_cmp);
     if(family_ptr)
       for(i = 0; i < family_ptr->chil_count; i++)
          printTree(individual_count, family_count, individuals, 
            families, family_ptr->CHILs[i]);
  } // if family.FAM
}  // printTree()
