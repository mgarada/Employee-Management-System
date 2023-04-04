
// File           : p2-support.h
// Description    : Header file for this project
// Author         : Mohammad Garada
// Date           : 04-02-23

#ifndef P2Header //To prevent double inclusion of header
#define P2Header //To prevent double inclusion of header

#include <stdio.h>
#define byID 1
#define byNAME 2
#define dbSIZE 100
#define idSIZE 6
#define nameSIZE 10
#define emailSIZE 20


typedef struct date
{
  int day; 
  int month;
  int year;
}date;

typedef struct Employee
{
  char ID[idSIZE];
  char first_name[10];
  char last_name[10];
  char email[20];
  double salary;
  date hire_date;
  
}employee, *employee_ptr;

typedef struct DataBase
{
 struct Employee *emp;
  int total;  
//a pointer to first element of empoloyee array
  //number of employees in database
}*dataBase_ptr;


//Function     : initialize
// Description  : This function creates an array in the database
//                then initalializes each array elemet with the data 
//                in the given file
// Inputs       : a pointer to DataBase struct
// Output       : none
void initialize (dataBase_ptr);




// Function     : create_record
// Description  : creates a brand new employee record and stores it inside the database
// Inputs       : (char*): of an employee "ID, first & last name, and email
// 		  (double): salary 
// 		  (struct date): hire_date 
// 		  (struct Database*): a pointer to DataBase struct
// Output       : none 
void create_record (char* , char* , char* , char* , double , struct date  , dataBase_ptr );//specify parameters types. Clues are in the initalize function.



//Function     : print_title 
//Description  : prints the employee title header 
//Inputs       : none
//Output       : none
void print_title ();



//Function     : display_menu 
//Description  : displays the menu for the user to interact with and change the employee database 
//Inputs       : (struct Database*): a pointer to the DataBase struct
//Output       : none
void display_menu (dataBase_ptr);




//Function     : sort_by_id
//Description  : sort employee records by ID numbers from lowest to highest.    
//Inputs       : (struct Database*): a pointer to the DataBase struct
//Output       : none
void sort_by_id(struct DataBase *db);



//Function     : sort_by_date 
//Description  : sort employee records by hire date from lowest to highest.   
//Inputs       : (struct Database*): a pointer to the DataBase struct
//Output       : none
void sort_by_date(struct DataBase *db);



//Function     : search_by_id 
//Description  : display the employee with the given ID from the user input 
//Inputs       :(struct Database*): a pointer to the DataBase struct 
//Output       : none
void search_by_id(struct DataBase *db);



//Function     : search_by_last 
//Description  : search the database by last name and display employee(s) partially or completely matching with the given string
//Inputs       : (struct Database*): a pointer to the DataBase struct 
//Output       : none
void search_by_last(struct DataBase *db);



//Function     : save 
//Description  : This function saves the database to a text file 
//Inputs       : (struct Database*): a pointer to the DataBase struct 
//Output       : none
void save(struct DataBase *db);



//Function     : delete_by_id 
//Description  : delete one employee record with the matching ID from user input from the list
//Inputs       : (struct Database*): a pointer to the DataBase struct  
//Output       : none
void delete_by_id(struct DataBase *db);



//Function     : display_all_records 
//Description  : displays the records of all employees that are within the database
//Inputs       : (struct Database*): a pointer to the DataBase struct   
//Output       : none
void display_all_records(struct DataBase *db);


//Function     : cmpfunc_id
//Description  : a compare function which is used for the qsort of sorting the employees by ID
//Inputs       : (const void* a, const void* b) 
//Output       : none
//a compare function which is later used for the qsort of sorting the employees by ID
int cmpfunc_id (const void* a, const void* b);




//Function     : cmpfunc_date
//Description  : a compare function which is used for the qsort of sorting the employees by hire date
//Inputs       : (const void* a, const void* b) 
//Output       : none
int cmpfunc_date (const void* a, const void* b);

#endif //To prevent double inclusion of header
