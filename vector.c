// Author: Sean Davis
#include <stdlib.h>
#include "vector.h"
#include "main.h"

void deallocate(int individual_count, int family_count,
  Individual *individuals, Family *families)
{
  int i, j;
  
  for(i = 0; i < individual_count; i++)
  {
    if(individuals[i].INDI)
      free(individuals[i].INDI);
    
    if(individuals[i].NAME)
      free(individuals[i].NAME);
    
    if(individuals[i].FAMC)
      free(individuals[i].FAMC);
    
    if(individuals[i].FAMS)
      free(individuals[i].FAMS);
  } // for i
  
  for(i = 0; i < family_count; i++)
  {
    if(families[i].HUSB)
      free(families[i].HUSB);
    
    if(families[i].WIFE)
      free(families[i].WIFE);
    
    if(families[i].FAM)
      free(families[i].FAM);
    
    for(j = 0; j < families[i].chil_count; j++)
      free(families[i].CHILs[j]);
  } // for i

  free(individuals);
  free(families);
} // deallocate

void initialize(int individual_count, int family_count,
  Individual **individuals, Family **families)
{
  int i;
  
  *individuals = (Individual*) malloc(individual_count * sizeof(Individual));
  *families = (Family*) malloc(family_count * sizeof(Family));
  
  for(i = 0; i < individual_count; i++)
    (*individuals)[i].FAMS = (*individuals)[i].INDI = (*individuals)[i].NAME
      = (*individuals)[i].FAMC = NULL;
  
  for(i = 0; i < family_count; i++)
  {
    (*families)[i].FAM = (*families)[i].HUSB = (*families)[i].WIFE = NULL;
    (*families)[i].CHILs = NULL;
    (*families)[i].chil_count = 0;
  }
} // initialize()
