//student managment system
//create, delete, edit, check
#include "student.h"

struct Student students[MAX_ROWS];
int count = 0;

int main()
{
    srand(time(NULL));  // seed RNG once
    load_students();
    mainMenu();
}