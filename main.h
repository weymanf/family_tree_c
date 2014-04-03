// Author: Sean Davis

#ifndef MAIN_H
#define	MAIN_H

typedef struct {
  char *INDI;
  char *NAME;
  char *FAMC;
  char *FAMS;
} Individual;

typedef struct {
  char *FAM;
  char *HUSB;
  char *WIFE;
  char **CHILs;
  int chil_count;
} Family;

void run(int individual_count, int family_count, Individual *individuals, 
  Family *families);
#endif	

