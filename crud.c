#include "student.h"

//add student
void add_student(){
    int i, flag = 0;
    for(i = count; i < count+1; i++){
        students[count].uid = randUid();
        printf("Generated UID: %d\n", students[count].uid);

        validateFirstName(students[count].first_name, sizeof(students[count].first_name));
        validateLastName(students[count].last_name, sizeof(students[count].last_name));
        strcpy(students[count].email, validateEmail());
        validateDOB(students[count].dateOfBirth, sizeof(students[count].dateOfBirth));
        students[count].gpa = validateGPA();
        students[count].enrollment_year = validateEnrollment();
        students[count].gender = validateGender();

        // IMPORTANT: clear newline before using fgets in validateClub
        flush_stdin();
        validateClub(students[count].club, sizeof(students[count].club));

        printf("\nStudent saved successfully\n");

        save_students();
        flag = 1;
    }
    if(flag == 1){
        count++;
    }else{
        printf("Error adding name\n");
    } 
}

void display_all_students() {
    if (count == 0) {
        printf("No students loaded yet\n");
        return;
    }

    printf("List of students:\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| UID  | Name                   | Last Name              | Email                       | GPA  | DOB        | Year | Gender | Club           |\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("| %-4d | %-22s | %-22s | %-27s | %.2f | %-10s | %-4d | %-6c | %-13s |\n",
               students[i].uid,
               students[i].first_name,
               students[i].last_name,
               students[i].email,
               students[i].gpa,
               students[i].dateOfBirth,
               students[i].enrollment_year,
               students[i].gender,
               students[i].club);
    }

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Press Enter to continue...");
    flush_stdin();
    getchar();
}

//search student
int student_search() {
    int choice;
    char search_first_name[30], search_last_name[30];
    printf("Searching student...\n");
    printf("1. Name\n");
    printf("2. UID\n");
    printf("Enter choice: ");
    choice = validateInteger();
//search by name
if (choice == 1) {
    printf("Enter first name (or press Enter to skip): ");
    validateFirstName(search_first_name, sizeof(search_first_name));
    validateLastName(search_last_name, sizeof(search_last_name));

    int found = 0;
    int matches[MAX_ROWS];
    int match_count = 0;

    for (int i = 0; i < count; i++) {
        int first_ok = (strlen(search_first_name) == 0 || strcasecmp(students[i].first_name, search_first_name) == 0);
        int last_ok  = (strlen(search_last_name) == 0 || strcasecmp(students[i].last_name, search_last_name) == 0);

        if (first_ok && last_ok) {
            matches[match_count++] = i;
            found = 1;
        }
    }

    if (!found) {
        printf("No students found.\n");
        return -1;
    }

    // If multiple matches, let user choose
    if (match_count > 1) {
        printf("\nMultiple students found:\n");
        for (int i = 0; i < match_count; i++) {
            int idm = matches[i];
            printf("%d) UID: %d | %s %s | %s\n", i + 1,
                   students[idm].uid,
                   students[idm].first_name,
                   students[idm].last_name,
                   students[idm].email);
        }
        printf("Choose a student number to view: ");
        int choice = validateInteger();
        if (choice < 1 || choice > match_count) {
            printf("Invalid choice.\n");
            return -1;
        }
        int idm = matches[choice - 1];

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| UID  | Name                   | Last Name              | Email                       | GPA  | DOB        | Year | Gender | Club           |\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-4d | %-22s | %-22s | %-27s | %.2f | %-10s | %-4d | %-6c | %-13s |\n",
       students[idm].uid,
       students[idm].first_name,
       students[idm].last_name,
       students[idm].email,
       students[idm].gpa,
       students[idm].dateOfBirth,
       students[idm].enrollment_year,
       students[idm].gender,
       students[idm].club);
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");


    } else {
    // Only one match, display directly
    int idm = matches[0];
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| UID  | Name                   | Last Name              | Email                       | GPA  | DOB        | Year | Gender | Club           |\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-4d | %-22s | %-22s | %-27s | %.2f | %-10s | %-4d | %-6c | %-13s |\n",
           students[idm].uid,
           students[idm].first_name,
           students[idm].last_name,
           students[idm].email,
           students[idm].gpa,
           students[idm].dateOfBirth,
           students[idm].enrollment_year,
           students[idm].gender,
           students[idm].club);
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

    return 1;
}

 //search by uid
    else if (choice == 2) {
        int search_uid;
        printf("Enter UID to search: ");
        search_uid = validateUID();

        int found = 0;

    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| UID  | Name                   | Last Name              | Email                       | GPA  | DOB        | Year | Gender | Club          |\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
//in case got multiple entries
        for (int i = 0; i < count; i++) {
            if (students[i].uid == search_uid) {
                printf("| %-4d | %-22s | %-22s | %-27s | %.2f | %-10s | %-4d | %-6c | %-13s |\n",
                       students[i].uid,
                       students[i].first_name,
                       students[i].last_name,
                       students[i].email,
                       students[i].gpa,
                       students[i].dateOfBirth,
                       students[i].enrollment_year,
                       students[i].gender,
                       students[i].club );
                found = 1;
                break; // UID is unique, so we can break
            }
        }

        if (!found) {
            printf("No student found with that UID.\n");
        } else {
                    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
        }

        return found ? 1 : -1;

    } else {
        printf("Invalid choice.\n");
        return -1;
    }
}

//edit student
void student_edit() {
    int i, id_change, choice;
    char search_first_name[50];
    char search_last_name[50];
    selectList();
    choice = keySelect();
    if(choice == 1){
        id_change = validateUID();
    }else if(choice == 2){
        validateFirstName(search_first_name, sizeof(search_first_name));
        validateLastName(search_last_name, sizeof(search_last_name));
    }

    for (i = 0; i < count; i++) {
        if ((students[i].uid == id_change) || ((strcmp(students[i].first_name, search_first_name) == 0) &&(strcmp(students[i].last_name,search_last_name) == 0))) {
            printf("\nCurrent Student Info:\n");
            printf("UID: %d | Name: %s %s | Email: %s | DoB: %s | GPA: %.2f | Enrollment Year: %d | Gender: %c | Club: %s\n",
                   students[i].uid,
                   students[i].first_name, students[i].last_name,
                   students[i].email, students[i].dateOfBirth, students[i].gpa,
                   students[i].enrollment_year, students[i].gender,
                   students[i].club);

            while (1) {
                switch (keyEdit()) {
                    case 1:
                        validateFirstName(students[i].first_name, sizeof(students[i].first_name));
                        break;
                    case 2:
                        validateLastName(students[i].last_name, sizeof(students[i].last_name));
                        break;
                    case 3:
                        strcpy(students[i].email, validateEmail());
                        break;
                    case 4:
                        validateDOB(students[i].dateOfBirth, sizeof(students[i].dateOfBirth));
                        break;
                    case 5:
                        students[i].gpa = validateGPA();
                        break;
                    case 6:
                        students[i].enrollment_year = validateEnrollment();
                        break;
                    case 7:
                        students[i].gender = validateGender();
                        break;
                    case 8: { // Club only
                        char newClub[50];
                        validateClub(newClub, sizeof(newClub));
                        strncpy(students[i].club, newClub, sizeof(students[i].club) - 1);
                        students[i].club[sizeof(students[i].club) - 1] = '\0';
                        break;
                    }
                    case 9: { // All fields
                        char newClub[50];
                        validateFirstName(students[i].first_name, sizeof(students[i].first_name));
                        validateLastName(students[i].last_name, sizeof(students[i].last_name));
                        strcpy(students[i].email, validateEmail());
                        validateDOB(students[i].dateOfBirth, sizeof(students[i].dateOfBirth));
                        students[i].gpa = validateGPA();
                        students[i].enrollment_year = validateEnrollment();
                        students[i].gender = validateGender();
                        validateClub(newClub, sizeof(newClub));
                        strncpy(students[i].club, newClub, sizeof(students[i].club) - 1);
                        students[i].club[sizeof(students[i].club) - 1] = '\0';
                        break;
                    }
                    case 10:
                        printf("No changes made.\n");
                        return;
                    default:
                        printf("Invalid choice. Try again.\n");
                        continue;
                }

                save_studentsafteredit();
                printf("Changes saved successfully!\n");
                return;
            }
        }
    }

    printf("\nTHis student doesnt exist\n");
    getchar();
}

//delete student
int student_del(){
    int i, num, j, key;
    char search_first_name[50];
    char search_last_name[50];
    printf("Delete students\n");
    selectList();
    key = keySelect();
    if(key == 1){
        num = validateUID();
    }else if(key == 2){
        validateFirstName(search_first_name, sizeof(search_first_name));
        validateLastName(search_last_name, sizeof(search_last_name));
    }
    for(i = 0; i < count; i++){
        if((students[i].uid == num) || ((strcmp(students[i].first_name, search_first_name) == 0) &&(strcmp(students[i].last_name,search_last_name) == 0))){
            // Show student info
            printf("UID: %4d | Name: %s %s | Email: %s | DoB: %s | GPA: %.2f | Enrollment year: %d | Gender: %c, Club: %s\n",
                   students[i].uid,
                   students[i].first_name,
                   students[i].last_name,
                   students[i].email,
                   students[i].dateOfBirth,
                   students[i].gpa,
                   students[i].enrollment_year,
                   students[i].gender,
                   students[i].club);

            // Ask confirmation
            char confirm;
            confirm = validateYesNo();

            if((confirm == 'Y') == 1){
                for(j = i; j < count-1; j++){
                    students[j] = students[j+1];
                }
                count--;
                save_studentsafteredit();
                printf("This student is deleted!!!\n");
                return i;
            } else if((confirm == 'N') == 1){
                printf("Deletion cancelled.\n");
                return -1;
            }else{
                printf("some error maybe\n");
                return -1;
            }
        }
    }
    printf("Cannot find student\n");
    getchar();
    return -1;
}

// Load all student
void student_print() {
    if (count == 0) {
        printf("No student loaded yet\n");
        return;
    }
    printf("printing now...\n");
    for (int i = 0; i < count; i++) {
        printf("UID: %4d | Name: %s %s | Email: %s | DoB: %s | GPA: %.2f | Enrollment year: %d | Gender: %c | Club: %s\n",
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
}