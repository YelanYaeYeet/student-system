#include "student.h"

/*
TODO:
MENU CHOICE: check alphabet, check out of range (done)
UID: check alphabet, check more than 1000, check less than 9999(done)
Names: contains number or symbols, only alphabets(done)
Email: No @ no double @addtogroup(done)
DOB: wrong day month year range, seperator
GPA: not a number, 0-5
Enrollment year: check alphabet, in valid range 1800 to 2100(done)
Gender: M or F allows, convert male and female to M and F(done)
*/

//check for valid Integer
int validateInteger(){
    char buffer[100];
    char *endptr;
    long value;

    while(1){
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            printf("Input error, try again");
            continue;
        }
        buffer[strcspn(buffer,  "\n")] = '\0';

        // check empty
        int space = 1;
        for(int i = 0; buffer[i] != '\0'; i++){
            if (!isspace((unsigned char) buffer[i])){
                space = 0;
                break;
            }
        }
        if(buffer[0] == '\0' || space){
            printf("Input cannot be empty. try again\n");
            continue;
        }

        value = strtol(buffer,&endptr, 10);

        if(*endptr != '\0'){
            printf("Invalid input. Numbers only\n");
            continue;
        }

        return (int)value;
    }
}

//check for valid alphabets
char* validateAlpha(){
    static char buffer[200];
    int i;
    while(1){
        int throwError = 0, space = 0;
        printf("Enter only words: ");
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            printf("Input string error\n");
            continue;
        }

        buffer[strcspn(buffer, "\r\n")] = 0;

        if(buffer[0] == '\0'){
            printf("Input cannot be empty!\n");
            continue;
        }
        if(buffer[0] == ' ' || buffer[strlen(buffer) - 1] == ' ')
        {
            printf("No front and bad space!\n");
            continue;
        }

        for(i = 0; buffer[i] != '\0'; i++){
            if(isalpha((unsigned char)buffer[i]))
            {
                continue;
            }else if(buffer[i] == ' '){
                space++;
                if (space > 1){
                    throwError = 1;
                    break;
                }
            }else{
                throwError = 2;
                break;
            }
        }
            if(throwError == 1){
            printf("Only one space between words!\n");
            continue;
            }
            if(throwError == 2){
            printf("Only alphabets allowed!\n");
            continue;

            }

            return buffer;

    }

}

char* upperValidateAlpha(){
    char *s = validateAlpha();
    int i;
    for (i = 0; s[i] != '\0'; i++){
        s[i] = (char)toupper((unsigned char) s[i]);
    }
    return s;
}

//validate first
void validateFirstName(char *dest, int size){
    char *input;
    while(1){
        printf("Enter first name\n");
        input = upperValidateAlpha();
        //check for buffer overflow
        if((int)strlen(input) >= size){
            printf("Name too long shorter abit!\n");
        }
        else{
            strcpy(dest, input);
            break;
        }
    }
}

//validate second
void validateLastName(char *dest, int size){
    char *input;
    while(1){
        printf("Enter second name\n");
        input = upperValidateAlpha();
        //check for buffer overflow for name
        if((int)strlen(input) >= size){
            printf("Name too long shorter abit!\n");
        }
        else{
            strcpy(dest, input);
            break;
        }
    }
}

//check for valid email
char* validateEmail(){
    static char buffer[200];
    const char *domain = "@school.com";
    int domain_length = strlen(domain);
    printf("Email should be in this format!\n");
    printf("YOURINPUT@school.com\n");
    while(1){
        int throwError = 0;
        printf("Enter Email: ");
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            printf("Input string error\n");
            continue;
        }

        buffer[strcspn(buffer, "\r\n")] = 0;

        //check for null input
        if(buffer[0] == '\0'){
            printf("Email cannot be empty!\n");
            continue;
        }

        int len = strlen(buffer);
        //domain length already 11 chars
        //buffer len cannot be less than 11 chars
        if (len <= domain_length) {
            printf("Invalid email! Email bust be  xxx%s\n", domain);
            continue;
        }

        //TODO: check for start with @
        //if user enter anything shorter than @school.com
        //compare @school.com to @school.com
        if (strcmp(buffer + (len - domain_length), domain) != 0){
            printf("Invalid email! Email bust be  xxx%s\n", domain);
            continue;
        }

        //check if got words before the @
        //noob@school.com = 15, 15 - 11 = 4 > 0
        int before_length = len - domain_length;
        if(before_length == 0){
            printf("cannot be empty before @school.com\n");
            continue;
        }

        for(int i = 0; i < before_length; i++){
            char c = buffer[i];
            if(!(isalnum((unsigned char)c) || c == '_' || c == '.')){
                throwError = 1;
                break;
            }
        }

        if(throwError){
            printf("Only letters, numbers and '_' is allowed!\n");
            continue;
        }

        return buffer;

    }

}

// Date of Birth – format dd/mm/yyyy with zero padding
void validateDOB(char *dob, int size) {
    int valid = 0, d, m, y;
    while (!valid) {
        printf("Enter your date of birth (dd/mm/yyyy): ");
        scanf("%s", dob);
        if (sscanf(dob, "%d/%d/%d", &d, &m, &y) == 3) {
            valid = 1;
            if (y < 1900 || y > 2025) valid = 0;
            if (m < 1 || m > 12) valid = 0;
            if (d < 1 || d > 31) valid = 0;
        } else {
            valid = 0;
        }
        if (!valid) {
            printf("Invalid date. Please try again.\n");
        } else {
            // Format properly with zero padding
            snprintf(dob, size, "%02d/%02d/%04d", d, m, y);
        }
    }
}

// GPA – must be between 0.0 and 5.0
float validateGPA() {
    float gpa;
    int valid = 0;
    while (!valid) {
        printf("Enter GPA (0.0 - 5.0): ");
        scanf("%f", &gpa);
        if (gpa >= 0.0 && gpa <= 5.0) {
            valid = 1;
        } else {
            printf("Invalid GPA. Try again.\n");
        }
    }
    return gpa;
}

int validateEnrollment(){
    int year;
    while(1) {
        printf("Enter Enrollment Year: ");  // prompt here
        flush_stdin();           // flush any leftover input        
        year = validateInteger();           // no arguments
        if(year >= 1800 && year <= 2100){
            return year;
        } else {
            printf("Invalid year, please enter between 1800 and 2100\n");
        }
    }
}

// UID validation (4 digits)
int validateUID(){
    int uid;
    while(1){
        printf("Enter uid (4digits): ");
        uid = validateInteger();
        if (uid >= 1000 && uid <= 9999){
            return uid;
        } else {
            printf("Invalid UID, Must be 4 digits and within 1000 and 9999!!!\n");
        }
    }
}

// Club name. Makes sure the input not empty, contains only letters or spaces.
void validateClub(char* club, int size) {
    int valid = 0; // false at start
    do {
        printf("Enter Club: ");
        if (fgets(club, size, stdin) == NULL) {
            printf("Error reading club.\n");
            return;
        }

        int len = strlen(club);
        if (len > 0 && club[len - 1] == '\n') {
            club[len - 1] = '\0'; // remove the ENTER key at the end
            len--;
        }

        if (len == 0) {
            printf("Club name cannot be empty.\n");
            continue; // ask again
        }

        int onlyLetters = 1;
        for (int i = 0; i < len; i++) {
            if (!isalpha((unsigned char)club[i]) && club[i] != ' ') {
                onlyLetters = 0;
                break;
            }
        }

        if (!onlyLetters) {
            printf("Club name must contain only letters and spaces.\n");
            continue; // ask again
        }

        valid = 1; // everything ok
    } while (!valid);
}

// Gender – only M or F
char validateGender() {
    char *input;
    char output;
    while(1){
        printf("Enter gender (M/F)");
        input = upperValidateAlpha();

        if((strcmp(input,"MALE") == 0) || (strcmp(input,"M") == 0)){
            output = 'M';
            break;
        }else if((strcmp(input,"FEMALE") == 0) || (strcmp(input,"F") == 0)){
            output = 'F';
            break;
        }else{
            printf("Invalid gender, only male and female");
        }
    }

    return output;
}

// Yes No Y and N
char validateYesNo() {
    char *input;
    char output;
    while(1){
        printf("Are you sure you want to delete this student? (Y/N): ");
        input = upperValidateAlpha();

        if((strcmp(input,"YES") == 0) || (strcmp(input,"Y") == 0)){
            output = 'Y';
            break;
        }else if((strcmp(input,"NO") == 0) || (strcmp(input,"N") == 0)){
            output = 'N';
            break;
        }else{
            printf("Invalid input, only YES and NO!\n");
        }
    }

    return output;
}