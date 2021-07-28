/** *************************************
* The main file of the program, which creates a dictionary from data read from 
* an external data file and outputs the information in the dictionary into a 
* text file whose keys match the key which the user inputs.

* Student Name: Le Minh Truong
* Student ID: 1078113
* Subject Name: Algorithms and Data Structures
* Subject Code: COMP20003

* Assignment 1
***************************************** **/

#include "declarations.h"

int main(int argc, char* argv[]){
	
	char *trading_name, *buffer_str, *token;
	char *filename;
	char *output;
	company_t companies;
	list_t *company_list;
	int column, token_num = 0, quote = 0, i = 0, counter = 0, missing = 0;
	size_t len;
	FILE *company_file, *output_file;
	
	token = (char*)malloc(MAX_CHAR*sizeof(token));
	assert(token != NULL);
	trading_name = (char*)malloc(MAX_CHAR*sizeof(trading_name));
	assert(trading_name != NULL);
	buffer_str = (char*)malloc(BUFFER_SIZE*sizeof(buffer_str));
	assert(buffer_str != NULL);
	company_list = make_empty_dict();
	
	/* Obtain names of the data file (e.g. csv file) and the output file 
	* respectively. */
	filename = argv[1];
	output = argv[2];
	
	/* Check if the output file is properly opened. */
	if((output_file = fopen(output,"w")) == NULL){
		fprintf(stderr, "cannot write to %s\n", output);
		exit(EXIT_FAILURE);
	}
	
	/* Check if the data file is properly opened. */
	if((company_file = fopen(filename, "r")) == NULL){
		fprintf(stderr, "cannot read from %s\n",filename);
		exit(EXIT_FAILURE);
	}
	else{
		/* Loop through every line of information in the data file 
		* (e.g. csv file) and  process them. */
		while(fgets(buffer_str,BUFFER_SIZE,company_file) != NULL){
			counter++;
			
			/* Skip the first line, which contains only the field names. */
			if(counter == 1){
				continue;
			}
			
			i = 0;
			column = 0;
			
			/* Check to see if the data line being read is missing line 
			* terminators such as "\r" and "\n", and process the line based on
			* what is missing as well as assigning tags based on what is 
			* missing. */
			len = strlen(buffer_str);
			if(len>0 && buffer_str[len-1] != '\n'&& buffer_str[len-1]!= '\r'){
				missing = 2;
				strcat(buffer_str, "\r");
				strcat(buffer_str, "\n");
			}else if(len>0 && buffer_str[len-1] != '\n' && 
				buffer_str[len-1] == '\r'){
				missing = 1;
				strcat(buffer_str,"\n");
			}else if(len>0 && buffer_str[len -1] == '\n' && 
				buffer_str[len-2] != '\r'){
				missing = 3;
			}
			
			/*Partition the data line into values and add them into the 
			* predefined structure "companies" based on what fields they belong 
			* to in the data file. */
			while(buffer_str[i]){
				token[token_num++] = buffer_str[i];
				
				/*Process the values based on the warning tags assigned above, 
				and add them to the predefined structure "companies".*/
				if(!quote && (buffer_str[i] == ',' || buffer_str[i] == '\n' || 
					buffer_str[i] == '\0')){
					if((missing == 1||missing == 3) && column == 10){
						token[token_num - 1] = '\0';
						token_num = 0;
					} else if(missing == 2 && column == 10){
						token[token_num - 2] = '\0';
						token_num = 0;
					} else if (missing == 0 && column == 10){
						token[token_num-2] = '\0';
						token_num = 0;
					} else{
						token[token_num - 1] = '\0';
						token_num = 0;
					}
					make_struct(column++, &companies, token);
				}
				
				/* Process values contained in double quotes. */
				if(buffer_str[i] == '"' && buffer_str[i+1] != '"'){
					token_num--;
					quote = !quote;
				}
				
				/*Process values contained in double quotes that also
				* have double quotes. */
				if(buffer_str[i] == '"' && buffer_str[i+1] == '"'){
					i++;
				}
				
				i++;
			}
			/* ==============================================================
			* The above sequence of code is designed by Robert Torok on 
			* September 14th, 2018 in the website "codingboost: Parsing CSV 
			* Files in C" 
			
			* See https://codingboost.com/parsing-csv-files-in-c) for more
			* information
			
			* The sequence of code has been modified for the purpose of this 
			* assignment, and the modifications are my own personal work.
			================================================================= */
			
			company_list = insert_into_dict(company_list, &companies);
		}
	}
	
	fclose(company_file);
	
	/* Read inputs from users and process them into keys to search the 
	* dictionary with. */
	while(fgets(trading_name, MAX_CHAR+1, stdin) != NULL){
		if(trading_name[0] == ' ' || trading_name[0] == '\n'){
			continue;
		}
		
		len = strlen(trading_name);
		if(len >0 && trading_name[len-1] == '\n'){
			trading_name[--len] = '\0';
		}
		
		print_detail(company_list->head, trading_name, output_file);
	}
	
	fclose(output_file);
	
	/* Free every allocated memory in the main function. */
	free(buffer_str);
	free(token);
	free(trading_name);
	free_dict(company_list);
	return 0;
}