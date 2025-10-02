#include "student.h"

void menuList(){
    printf("\t0. Exit System\n");
    printf("\t1. Register Student\n");
    printf("\t2. Display All Student\n");
    printf("\t3. Search Student\n");
    printf("\t4. Edit Student\n");
    printf("\t5. Delete Student\n");
    printf("\t6. Load Student\n");
    printf("\t7. Show Statistics\n");
    printf("\t8. Show Dashboard\n");
}

//user input for Main Menu
void keyMain(){
    int keyDown;
    keyDown = keyInput();
    switch(keyDown){
        case 0:
            printf("Exited\n");
            printf("Exited succesfully\n");
            system("pause");
            exit(0);
            break;
        case 1:
            printf("Registering...\n");
            add_student();
            break;
        case 2:
            printf("Displaying...\n");
            display_all_students();
            break;
        case 3:
            printf("Searching...\n");
            student_search();
            break;
        case 4:
            printf("Editing...\n");
            student_edit();
            break;
        case 5:
            printf("Deleting...\n");
            student_del();
            break;
        case 6:
            printf("Loading...\n");
            student_print();
            break;    
        case 7:
            printf("Loading...\n");
            calculate_statistics();
            break;   
        case 8:
            printf("Dashboard...\n");
            showDashboard();
        break;
        default:
            printf("Invalid input\n");
            break;

    }
}

//check input for Mainmenu(0 to 9)
int keyInput(){
    int keyM;
    while(1){
        printf("Enter choice: ");
        keyM = validateInteger();
        if (keyM < 0 || keyM > 9){
            printf("Invalid Choices, Must be between 0 and 9!!!\n");
        } else {
            return keyM;
        }
    }
}

void mainMenu(){
    while(1){
        menuList();
        keyMain();
    }
}

//selection menu to serch
void selectList(){
    printf("\t0.Back to Main Menu\n");
    printf("\t1.Student ID\n");
    printf("\t2.Student NAME\n");
}

//key select for selection menu
int keySelect(){
    int keyClicked, choice;
    keyClicked = keyInput();
    switch(keyClicked){
        case 0:
            mainMenu();
            break;
        case 1:
            choice = keyClicked;
            break;
        case 2:
            choice = keyClicked;
            break;
        default:
            printf("Invalid choice enter again\n");
            break;
    }
    return choice;
}

void editList(){
    printf("\t0.Back to Main Menu\n");
    printf("\t1.Student First Name\n");
    printf("\t2.Student Last Name\n");
    printf("\t3.Student Email\n");
    printf("\t4.Student Date of Birth\n");
    printf("\t5.Student GPA\n");
    printf("\t6.Student Enrollment year\n");
    printf("\t7.Student Gender\n");
    printf("\t8.Student Club\n");
    printf("\t9. All Fields\n");
}

int keyEdit(){
    int keyClicked, choice;
    editList();
    keyClicked = keyInput();
    switch(keyClicked){
        case 0:
            mainMenu();
            break;
        case 1:
            choice = 1;
            return choice;
            break;
        case 2:
            choice = keyClicked;
            break;
        case 3:
            choice = keyClicked;
            break;
        case 4:
            choice = keyClicked;
            break;
        case 5:
            choice = keyClicked;
            break;
        case 6:
            choice = keyClicked;
            break;
        case 7:
            choice = keyClicked;
            break;
        case 8:
            choice = keyClicked;
            break;
        case 9:
            choice = keyClicked;
            break;
        default:
            printf("Invalid choice enter again\n");
            break;
    }
    return choice;
}