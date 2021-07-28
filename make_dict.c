/* *********
* This file contains functions that enable the creation of empty dictionaries,
* the passing of data from files to structures, the insertion of new data 
* in the form of structures into the dictionaries as well as the searching 
* and printing of information in the dictionaries using users' inputs 
* as keys.

* Student Name: Le Minh Truong
* Student ID: 1078113
* Subject Name: Algorithms and Data Structures
* Subject Code: COMP20003

* Assignment 1
******* */

#include "declarations.h"

/* Create an empty dictionary. */
list_t
*make_empty_dict(void) {
	
	list_t *list;
	
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	
	list->head = list->foot = NULL;
	
	return list;
}

/* Free the memory allocated for the dictionary as well as memory
* allocated for every entry in the dictionary. */
void free_dict(list_t *list) {

	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev->company.census_year);
		free(prev->company.block_id);
		free(prev->company.property_id);
		free(prev->company.base_prop_id);
		free(prev->company.small_area);
		free(prev->company.name);
		free(prev->company.industry_code);
		free(prev->company.description);
		free(prev->company.x_coordinate);
		free(prev->company.y_coordinate);
		free(prev->company.location);
		free(prev);
	}
	free(list);
}

/* Insert data read from data file into the dictionary as new entry. */
list_t *insert_into_dict(list_t *list, company_t *value) {

	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->company = *value;
	new->next = NULL;
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

/* =============================================================================
   Functions above are written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974. These functions have been modified for the
   purpose of this assignment. All modifications made are my own
   personal work.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ========================================================================== */


/** ******************
* The following functions are my personal creations.
******************* **/

/* Create a structure containing data of a company, 
* which is obtained from the data file.*/ 
void make_struct(int column, company_t *companies, char *token){
	
	if(column == 0){
		companies->census_year = (char*)malloc(MAX_CHAR*sizeof(companies->
			census_year));
		assert(companies->census_year != NULL);
		strcpy(companies->census_year, token);
	}
	
	if(column == 1){
		companies->block_id = (char*)malloc(MAX_CHAR*sizeof(companies->
			block_id));
		assert(companies->block_id != NULL);
		strcpy(companies->block_id, token);
	}
	
	if(column == 2){
		companies->property_id = (char*)malloc(MAX_CHAR*sizeof(companies->
			property_id));
		assert(companies->property_id != NULL);
		strcpy(companies->property_id, token);
	}
	
	if(column == 3){
		companies->base_prop_id = (char*)malloc(MAX_CHAR*sizeof(companies->
			base_prop_id));
		assert(companies->base_prop_id != NULL);
		strcpy(companies->base_prop_id, token);
	}
	
	if(column == 4){
		companies->small_area = (char*)malloc(MAX_CHAR*sizeof(companies->
			small_area));
		assert(companies->small_area != NULL);
		strcpy(companies->small_area, token);
	}
	
	if(column == 5){
		companies->name = (char*)malloc(MAX_CHAR*sizeof(companies->name));
		assert(companies->name != NULL);
		strcpy(companies->name, token);
	}
	
	if(column == 6){
		companies->industry_code = (char*)malloc(MAX_CHAR*sizeof(companies->
			industry_code));
		assert(companies->industry_code != NULL);
		strcpy(companies->industry_code, token);
	}
	
	if(column == 7){
		companies->description =(char*)malloc(MAX_CHAR*sizeof(companies->
			description));
		assert(companies->description != NULL);
		strcpy(companies->description, token);
	}
	
	if(column == 8){
		companies->x_coordinate = (char*)malloc(MAX_CHAR*sizeof(companies->
			x_coordinate));
		assert(companies->x_coordinate != NULL);
		strcpy(companies->x_coordinate, token);
	}
	
	if(column == 9){
		companies->y_coordinate = (char*)malloc(MAX_CHAR*sizeof(companies->
			y_coordinate));
		assert(companies->y_coordinate != NULL);
		strcpy(companies->y_coordinate, token);
	}
	
	if(column == 10){
		companies->location = (char*)malloc(MAX_CHAR*sizeof(companies->
			location));
		assert(companies->location != NULL);
		strcpy(companies->location, token);
	}
}

/* Print the information of the entry in the dictionary that matches 
* the users' inputs to a text file. */
void print_detail(node_t *head, char *trading_name, FILE *file){

	int found = 0;
	node_t *curr_node = head;
	
	while(curr_node != NULL){
		if(strncmp(trading_name, curr_node->company.name, strlen(trading_name))
		   == 0){
			found = 1;
			fprintf(file,"%s --> ",  trading_name);
			fprintf(file,"Census year: %s || ", 
				curr_node->company.census_year);
			fprintf(file,"Block ID: %s || ", 
				curr_node->company.block_id);
			fprintf(file,"Property ID: %s || ", 
				curr_node->company.property_id);
			fprintf(file,"Base property ID: %s || ", 
				curr_node->company.base_prop_id);
			fprintf(file,"CLUE small area: %s || ", 
				curr_node->company.small_area);
			fprintf(file,"Industry (ANZSIC4) code: %s || ", 
				curr_node->company.industry_code);
			fprintf(file,"Industry (ANZSIC4) description: %s || ", 
				curr_node->company.description);
			fprintf(file,"x coordinate: %s || ", 
				curr_node->company.x_coordinate);
			fprintf(file,"y coordinate: %s || ", 
				curr_node->company.y_coordinate);
			fprintf(file,"Location: %s || \n", 
				curr_node->company.location);
		}
		curr_node = curr_node->next;
	}
	
	if(found == 0){
		fprintf(file,"%s --> NOTFOUND\n",trading_name);
	}
}

