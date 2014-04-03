// Author: Sean Davis

#ifndef VECTORS_H
#define	VECTORS_H

#include "main.h"

#define ID_SIZE 20
#define SPOUSES_SIZE 40

void deallocate(int individual_count, int family_count, Individual *individuals,
  Family *families);
void initialize(int individual_count, int family_count, 
  Individual **individuals, Family **families);
#endif	

