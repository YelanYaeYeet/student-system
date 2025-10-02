#ifndef STUDENTS_H
#define STUDENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <float.h>

#define MAX_ROWS 100
extern int count;

struct Student{
    int uid; //4digit
    char first_name[50]; //student first name
    char last_name[50]; //student last name
    char email[100]; //student email 
    char dateOfBirth[11];//DOB
    float gpa; //gpa 0 to 5
    int enrollment_year; //year of enrollment
    char gender;
    char club[50];
};

extern struct Student students[MAX_ROWS];

typedef struct {
    int uid;
    char name[50];
    char lastname[50];
    char email[100];
    char dateOfBirth[11];
    float gpa;
    int enrollment_year;
    char gender;
    char club[50];
    int update_count;
    unsigned long added_seq;
    int valid;
} StudentRec;

// Struct for club statistics
typedef struct {
    char club[50];
    int maleCount;
    int femaleCount;
    int total;
} ClubStats;

//selection menu.c
void menuList();
void keyMain();
int keyInput();
void mainMenu();
void selectList();
int keySelect();
void editList();
int keyEdit();

//fileDat.c
void save_students();
void save_studentsafteredit();
void load_students();
void flush_stdin();
int randUid();

//validation
int validateInteger();
char* validateAlpha();
char* upperValidateAlpha();
void validateFirstName(char *dest, int size);
void validateLastName(char *dest, int size);
char* validateEmail();
void validateDOB(char *dob, int size);
float validateGPA();
int validateEnrollment();
int validateUID();
void validateClub(char* club, int size);
char validateGender();
char validateYesNo();

//crud
void add_student();
void display_all_students();
int student_search();
void student_edit();
int student_del();
void student_print();

//class satistic and dashboard
int checkDOB(const char *dob1, const char *dob2);
void calculate_statistics();
void showDashboard();


#endif