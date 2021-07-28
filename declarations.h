/** ************************************ 
* This file is the header file of the program, which contains
* all the necessary declarations for the program to function.

* Student Name: Le Minh Truong
* Student ID: 1078113
* Subject Name: Algorithms and Data Structures
* Subject Code: COMP20003

* Assignment 1
**************************************** */

#ifndef DECLARATIONS
#define DECLARATIONS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_CHAR 128      /* Maximum characters of a value in a single field. */
#define MAX_COMPANIES 19117   /* Maximum number of data lines in a data file. */
#define BUFFER_SIZE 500 /* Maximum size of a data line when read as a string. */

/*Structure of a single company read from the data file.*/
typedef struct{
	char *census_year, *block_id, *property_id, *base_prop_id, *industry_code;
	char *x_coordinate, *y_coordinate;
	char *small_area, *name, *description, *location;
}company_t;


/* The following structures are structures of the dictionary in 
* the form of a linked list. These structure are defined by Alistair
* Moffat, as an example for the book "Programming, Problem Solving,
* and Abstraction with C", Pearson Custom Books, Sydney, Australia,
* 2002; revised edition 2012, ISBN 9781486010974.

* See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
  information.

* Prepared December 2012 for the Revised Edition. */
typedef struct node node_t;

struct node {
	company_t company;
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;

/** *********************************************************** **/

/* Function prototypes for functions contained in files
* "dict.c" and "make_dict.c" */
void make_struct(int column, company_t *companies, char *token);
list_t *make_empty_dict(void);
void free_dict(list_t *list);
list_t *insert_into_dict(list_t *list, company_t *value);
void print_detail(node_t *head, char *trading_name, FILE *filename);

#endif