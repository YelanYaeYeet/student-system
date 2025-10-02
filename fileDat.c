#include "student.h"


//save to file
void save_students(){
    FILE *file = fopen("students.dat", "a");
    if(file == NULL){
        printf("Unable to open the file\n");
        exit(1);
    }
        fprintf(file, "%d,%s,%s,%s,%s,%.2f,%d,%c,%s\n",
                    students[count].uid,
                    students[count].first_name,
                    students[count].last_name,
                    students[count].email,
                    students[count].dateOfBirth,
                    students[count].gpa,
                    students[count].enrollment_year,
                    students[count].gender,
                    students[count].club);
    fclose(file);
}

//rewrite fie after edit
void save_studentsafteredit(){
    FILE *file = fopen("students.dat", "w"); // rewrite instead of append
    if(file == NULL){
        printf("Unable to open the file\n");
        exit(1);
    }

    for(int i = 0; i < count; i++){
        fprintf(file, "%d,%s,%s,%s,%s,%.2f,%d,%c,%s\n",
                students[i].uid,
                students[i].first_name,
                students[i].last_name,
                students[i].email,
                students[i].dateOfBirth,
                students[i].gpa,
                students[i].enrollment_year,
                students[i].gender,
                students[i].club);
    }
    fclose(file);
}

//load student to file
void load_students(){
    FILE *file = fopen("students.dat", "r");
    if(file == NULL){
        printf("Its empty\n");
        return;
    }

    int i = 0;
    char line[512];

    while (fgets(line, sizeof line, file)) {
        int uid, year;
        char first[50], last[50], email[100], dob[11], club[50], gender;
        float gpa;

        int n = sscanf(line, "%d,%49[^,],%49[^,],%99[^,],%10[^,],%f,%d,%c,%49[^\n]",
                       &uid, first, last, email, dob, &gpa, &year, &gender, club);
        if (n == 9) {
            students[i].uid = uid;
            strncpy(students[i].first_name, first, sizeof(students[i].first_name)-1);
            students[i].first_name[sizeof(students[i].first_name)-1] = '\0';
            strncpy(students[i].last_name, last, sizeof(students[i].last_name)-1);
            students[i].last_name[sizeof(students[i].last_name)-1] = '\0';
            strncpy(students[i].email, email, sizeof(students[i].email)-1);
            students[i].email[sizeof(students[i].email)-1] = '\0';
            strncpy(students[i].dateOfBirth, dob, sizeof(students[i].dateOfBirth)-1);
            students[i].dateOfBirth[sizeof(students[i].dateOfBirth)-1] = '\0';
            students[i].gpa = gpa;
            students[i].enrollment_year = year;
            students[i].gender = gender;
            strncpy(students[i].club, club, sizeof(students[i].club)-1);
            students[i].club[sizeof(students[i].club)-1] = '\0';

            i++;
            if (i >= MAX_ROWS) break;
        }
    }
    count = i;
    fclose(file);
}

//clean precious scans
void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Generate unique random UID
int randUid() {
    int random_uid, unique;

    do {
        random_uid = rand() % 9000 + 1000; // Range 1000–9999
        unique = 1;
        for (int i = 0; i < count; i++) {
            if (students[i].uid == random_uid) {
                unique = 0;
                break;
            }
        }
    } while (!unique);

    return random_uid;
}