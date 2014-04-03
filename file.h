// Author: Sean Davis

#ifndef FILE_H
#define	FILE_H

#include "main.h"

void add_child(char *line, Family *family);
FILE* count_records(const char *filename, int *individual_count, 
  int *family_count);
char* get_ID(char *line);
void read_file(FILE *fp, Individual *individuals, Family *families);

char* read_other(char *line, FILE *fp);
char* read_indi(int *individual_count, char *line,
  FILE *fp, Individual *individuals);
char* read_family(int *family_count, char *line, FILE *fp, Family *families);

#endif	

