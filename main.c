// Author: Sean Davis

#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "vector.h"
#include "search.h"
#include "main.h"

enum {DONE, PRINT_CHILDREN, PRINT_TREE};

int main(int argc, char **argv)
{
  int individual_count, family_count;
  Individual *individuals;
  Family *families;
  
  FILE *fp;
  
  if(argc != 2)
  {
    printf("Usage: family.out <ged_filname>\n");
    return 1;
  } // if the number of arguments is wrong
  
  fp = count_records(argv[1], &individual_count, &family_count);
  initialize(individual_count, family_count, &individuals, &families);
  read_file(fp, individuals, families);
  qsort(individuals, individual_count, sizeof(Individual), individual_cmp);
  qsort(families, family_count, sizeof(Family), family_cmp);
  run(individual_count, family_count, individuals, families);
  deallocate(individual_count,family_count, individuals, families);
  return 0;
} // main()


void run(int individual_count, int family_count, Individual *individuals, 
  Family *families)
{
  char name[80];
  int name_index, choice;
  
  do
  {
    printf("\nMenu\n");
    printf("0. Done.\n");
    printf("1. Find children.\n");
    printf("2. Print family tree.\n");
    printf("Your choice: ");
    scanf("%d", &choice);
    
    if(choice == PRINT_CHILDREN || choice == PRINT_TREE)
    {
      fgets(name, 80, stdin);
      printf("Please enter a name: ");
      fgets(name, 80, stdin);
      name_index = find_name(name, individual_count, individuals); 
      
      if(name_index >= 0)
      {
        if(choice == PRINT_CHILDREN)
          find_children(individual_count, family_count, 
            individuals, families, individuals[name_index].INDI);
        else 
          printTree(individual_count, family_count, 
            individuals, families, individuals[name_index].INDI);
      }
    } // if choice
  } while(choice != DONE);
} // run()
