#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p2-support.h"



// File              : p2-support.c
// // Description    : The source code file for this project
// // Author         : Mohammad Garada
// // Date           : 04-02-23


//creates a brand new employee record and stores it inside the database
void create_record(char* ID , char* first_name, char* last_name, char* email, double salary,struct date hire_date,struct DataBase* db){
	//copies into a new Employee struct then adds it to the database
	strcpy( db -> emp[db->total].ID, ID);
	strcpy( db -> emp[db->total].first_name , first_name);
	strcpy( db -> emp[db->total].last_name, last_name);
	strcpy( db -> emp[db->total].email, email); 
	db->emp[db->total].salary= salary; 
	db ->emp[db->total].hire_date = hire_date;
	//increase the total number of employees
	db -> total++;
}

//prints the header for the employee database
void print_title(){

	printf ("No. ID    Name          Email        Salary     Hire Date\n");
	printf ("--- ----- ------------- ------------ ---------- --/--/----\n");

}



//This function is for saving the database into a text file
void save (dataBase_ptr db){

	int i = 0;
	FILE *dbfu;

	//open an Std IO file to write into	
	dbfu = fopen ("database_updated", "w");
	if (dbfu == NULL)
	{
		printf ("File cannot be created");
		return;
	}
	//iterates through every employee, then prints their record
	for (i = 0; i < db->total; i++)
	{
		fprintf(dbfu, "%s %s %s %s %0.2lf %d/%d/%d\n", db->emp[i].ID,db->emp[i].first_name,db->emp[i].last_name,
				db->emp[i].email,db->emp[i].salary,db->emp[i].hire_date.month, db->emp[i].hire_date.day,
				db->emp[i].hire_date.year);

	}

	//close file after writing
	fclose (dbfu);
	return;

}

//a compare function which is later used for the qsort of sorting the employees by ID
int cmpfunc_id (const void* a, const void* b) {

	struct Employee* a_first = (struct Employee*) a;
	struct Employee* b_second = (struct Employee*) b;

	//use of "atoi" for converting string argument into an integer
	if (atoi(a_first->ID) > atoi(b_second->ID)){
		return 1;
	}  
	else if (atoi(b_second->ID) > atoi(a_first->ID)) { 
		return 0;
	}
	return 0;
}

//a compare function which is later used for the qsort of sorting t
//he employees by hire date 
int cmpfunc_date (const void* a, const void* b){
	struct Employee* a_first = (struct Employee*) a;
	struct Employee* b_second = (struct Employee*) b;

	if(a_first->hire_date.year < b_second->hire_date.year){ 
		return 0;
	}
	else if (a_first->hire_date.year > b_second->hire_date.year){
		return 1;
	}
	else if (a_first->hire_date.month < b_second->hire_date.month){ 
		return 0;
	}
	else if (a_first->hire_date.month > b_second->hire_date.month){
		return 1;
	}
	else if (a_first->hire_date.day < b_second->hire_date.day){ 
		return 0;
	}
	else if (a_first->hire_date.day > b_second->hire_date.day){ 
		return 1;
	}

	return 0;
}


//sort the employees by hire date from earliest to lastest while usimg the compare function above
void sort_by_date (struct DataBase *db){ 
	qsort(&db -> emp[0], db->total, sizeof(struct Employee), cmpfunc_date);
}


//sort the employees by ID from lowest to highest while usimg the compare function 
//above
void sort_by_id (struct DataBase *db){
	qsort(&db -> emp[0], db->total,sizeof(struct Employee), cmpfunc_id);
}


//search for an employee by inputting their ID number
void search_by_id(struct DataBase *db){

	//prompt the user to enter an ID number 
	char search[10];
	printf("Enter the ID you are searching for: ");
	scanf("%s", search);
	int i = 0;

	//iterate through every employee in the list to look for a match
	for(i = 0; i < db -> total; i++){

		//if a match is found, print that specific employee's record
		if(atoi(db->emp[i].ID) == atoi(search)){
			print_title();
			struct Employee emp = db -> emp[i];

			//new char for the combination of a "first & last name"
			char first_and_last[20];

			//use strcpy to copy the first name into the new string 
			strcpy(first_and_last, emp.first_name);

			//use strcat to concatenate a space, and a last name to the new string
			strcat(first_and_last, " ");
			strcat(first_and_last, emp.last_name);

			//print out the matching employee's record
			printf("%-3d %-3s %-13.13s %-12.12s $%9.2lf %02d/%02d/%4d\n",
					i, emp.ID, first_and_last, emp.email, emp.salary, emp.hire_date.month, emp.hire_date.day, emp.hire_date.year);
			return;


		}
	}

	//if there is no match, print out the error message	
	printf("Employee with the ID %s cannot be found.\n", search);

}


//deletes an employee by inputting their ID number
void delete_by_id(struct DataBase *db){
	char search[10];
	printf("Enter the ID you are searching for: ");
	scanf("%s", search);
	int i = 0;
	int j = 0;
	for(i = 0; i < db -> total; i++){
		if(atoi(db->emp[i].ID) == atoi(search)){
			printf("The following employee is deleted:\n");
			print_title();
			struct Employee emp = db -> emp[i];
			char first_and_last[20];
			strcpy(first_and_last, emp.first_name);
			strcat(first_and_last, " ");
			strcat(first_and_last, emp.last_name);
			printf("%-3d %-3s %-13.13s %-12.12s $%9.2lf %02d/%02d/%4d\n",                                                                                                                              i, emp.ID, first_and_last, emp.email, emp.salary, emp.hire_date.month, emp.hire_date.day, emp.hire_date.year);

			//for loop for shifting all the employees
			for(j = i; j < db->total -1; j++){
				db->emp[j] = db->emp[j+1];
			}

			//decrement the total number of employees after you have deleted one from the database 
			db->total--;
			return;
		}
	}

	//error message is there is no ID match 
	printf("Employee with the ID %s cannot be found.\n", search);

}



//displays the records of all employees
void display_all_records(struct DataBase *db){
	print_title();
	int i = 0;
	for(i = 0; i < db -> total; i++){
		struct Employee emp = db -> emp[i];
		char first_and_last[20];
		strcpy(first_and_last,emp.first_name);
		strcat(first_and_last, " ");
		strcat(first_and_last,emp.last_name);	
		printf("%-3d %-3s %-13.13s %-12.12s $%9.2lf %02d/%02d/%4d\n",
				i, emp.ID,first_and_last, emp.email, emp.salary,emp.hire_date.month, emp.hire_date.day, emp.hire_date.year);
	}
}


//searches for an employee or multiple by characters in their last name
void search_by_last(struct DataBase *db){
	char search[10];
	printf("Enter the Last Name that you are searching for: ");
	scanf("%s", search);
	int i = 0;

	//count variable to check if employee or multiple with taht last name are found  
	int count = 0;

	print_title();
	for(i = 0; i < db -> total; i++){

		//use strcasestr to find the first occurrence of the substring. Is also NOT case sensitive like 'strstr'
		if(strcasestr(db->emp[i].last_name, search) != NULL){

			//increment count
			count++;

			struct Employee emp = db -> emp[i];
			char first_and_last[20];
			memset(first_and_last, '\0', 20);
			strcpy(first_and_last, emp.first_name);
			strcat(first_and_last, " ");
			strcat(first_and_last, emp.last_name);
			printf("%-3d %-3s %-13.13s %-12.12s $%9.2lf %02d/%02d/%4d\n",
					i, emp.ID, first_and_last, emp.email, emp.salary, emp.hire_date.month, emp.hire_date.day, emp.hire_date.year);


		}
	}


	//if no last name is found with the corressponding string, display error message
	if(count == 0){ 
		printf("Employees with that Last Name %s cannot be found.\n", search);
	}

}




//display menu for user to interact with or change the employee records
void display_menu (struct DataBase *db)
{
	int input = 0;
	while (input != 8)
	{
		puts
			("\n**************************************************************");
		printf
			(  "********** Employee Database - Total Employees: %03d **********\n",
			   db->total); 
		puts
			("**************************************************************\n");
		puts ("Choose one of the menu options below:");
		puts ("1. Sort by ID");
		puts ("2. Sort by Hire Date");
		puts ("3. Display all employees");
		puts ("4. Search employees by ID");
		puts ("5. Search employees by Last Name");
		puts ("6. Delete employee by ID");
		puts ("7. Save");
		puts ("8. Exit");

		scanf ("%d", &input);

		//implement functions that were created above 
		switch (input)
		{
			case 1:
				sort_by_id(db);
				break;
			case 2:
				sort_by_date(db);
				break;
			case 3:
				display_all_records(db);
				break;
			case 4:
				search_by_id(db);
				break;
			case 5:
				search_by_last(db);
				break;
			case 6:
				delete_by_id(db);
				break;
			case 7:
				save(db);
				break;
			case 8:
				printf("Bye!\n");
				free(db->emp);
				free(db);
				break;

		}
	}

}
