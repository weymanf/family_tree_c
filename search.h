// Author: Sean Davis

#ifndef SEARCH_H
#define	SEARCH_H
#include "main.h"

int family_cmp(const void *ptr, const void *ptr2);
void find_children(int individual_count, int family_count, 
  Individual *individuals, Family *families, char* INDI); 
int find_name(char name[80], int individual_count, Individual *individuals);
int find_spouse(const char* ID,  int count, Family *families);
int individual_cmp(const void *ptr, const void *ptr2);
void print_children(Family *family, Individual *individuals, 
  int individual_count);
void printTree(int individual_count, int family_count, 
  Individual *individuals, Family *families, char *INDI);

#endif	

