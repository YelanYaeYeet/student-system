#include "student.h"

//calculate class statistic
int checkDOB(const char *dob1, const char *dob2) {
    int d1, m1, y1, d2, m2, y2;
    sscanf(dob1, "%d/%d/%d", &d1, &m1, &y1);
    sscanf(dob2, "%d/%d/%d", &d2, &m2, &y2);

    int date1 = y1 * 10000 + m1 * 100 + d1; // display in this format yyyymmdd
    int date2 = y2 * 10000 + m2 * 100 + d2; // display in this format yyyymmdd

    if (date1 < date2) {
        return -1;  // dob1 is older
    } else if (date1 > date2) {
        return 1;   // dob2 is older
    } else if (date1 == date2){
        return 0;  // both are the same age
    } 

    return 0;
}

void calculate_statistics() {
    if (count == 0) {
        printf("\nZero students.\n");
        return;
    }

    int totalStudents = count;
    
    float gpaSum = 0.0;
    float avgGPA;
    float maxGPA = students[0].gpa;
    float minGPA = students[0].gpa;
    
    int minYear = students[0].enrollment_year;
    int maxYear = students[0].enrollment_year;
    
    int oldestIndex = 0;
    int youngestIndex = 0;

    for (int i = 0; i < count; i++) {
        gpaSum += students[i].gpa;

        if (students[i].gpa > maxGPA) 
            maxGPA = students[i].gpa;
        if (students[i].gpa < minGPA) 
            minGPA = students[i].gpa;

        if (students[i].enrollment_year < minYear) 
            minYear = students[i].enrollment_year;
        if (students[i].enrollment_year > maxYear) 
            maxYear = students[i].enrollment_year;

        if (checkDOB(students[i].dateOfBirth, students[oldestIndex].dateOfBirth) < 0)
            oldestIndex = i;
        if (checkDOB(students[i].dateOfBirth, students[youngestIndex].dateOfBirth) > 0)
            youngestIndex = i;
    }

    avgGPA = gpaSum / totalStudents;

    printf("\n----- Class Statistics -----\n");
    printf("Total Students: %d\n", totalStudents);
    printf("Enrollment Year Range: %d - %d\n", minYear, maxYear);
    printf("Average GPA: %.2f\n", avgGPA);
    printf("Highest GPA: %.2f\n",maxGPA);
    printf("Lowest GPA: %.2f\n", minGPA);

    printf("Oldest Student (UID | Name | DOB): %4d | %s %s | %s\n",
        students[oldestIndex].uid,   
        students[oldestIndex].first_name,
        students[oldestIndex].last_name,
        students[oldestIndex].dateOfBirth);

    printf("Youngest Student (UID | Name | DOB): %4d | %s %s | %s\n",
        students[youngestIndex].uid,
        students[youngestIndex].first_name,
        students[youngestIndex].last_name,
        students[youngestIndex].dateOfBirth);

    printf("------------------------------\n");
    
    printf("Press Enter to continue...");
    flush_stdin();  // make sure any leftover input is cleared
    getchar();      // wait for user input
}

//dashboard
void showDashboard() {
    int choice = -1;

    do {
        printf("\nDashboard Options:\n");
        printf("1. Club summary (all clubs)\n");
        printf("2. Recent Student's Club Records \n");
        printf("3. New Student Records \n");
        printf("0. Exit dashboard\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            printf("Invalid input. Try again.\n");
            choice = -1;
            continue;
        }
        getchar();  /* clear newline */

        if (choice == 0) {
            printf("Exiting dashboard...\n");
            break;
        }
        if (count == 0) {
            printf("No records found.\n");
            continue;
        }

        if (choice == 1) {
            /* === Club summary (all) === */
            typedef struct {
                char club[50];
                int maleCount;
                int femaleCount;
                int total;
            } ClubStats;

            ClubStats stats[100];
            int clubCount = 0;

            for (int k = 0; k < count; k++) {
                /* find this club in stats[] */
                int found = -1;
                for (int i = 0; i < clubCount; i++) {
                    if (strcmp(stats[i].club, students[k].club) == 0) {
                        found = i; break;
                    }
                }
                /* new club bucket */
                if (found == -1) {
                    strncpy(stats[clubCount].club, students[k].club, sizeof(stats[clubCount].club) - 1);
                    stats[clubCount].club[sizeof(stats[clubCount].club) - 1] = '\0';
                    stats[clubCount].maleCount = 0;
                    stats[clubCount].femaleCount = 0;
                    stats[clubCount].total = 0;
                    found = clubCount++;
                }
                /* count by gender */
                if (students[k].gender == 'M' || students[k].gender == 'm')
                    stats[found].maleCount++;
                else if (students[k].gender == 'F' || students[k].gender == 'f')
                    stats[found].femaleCount++;
                stats[found].total++;
            }

            /* sort by total desc */
            for (int i = 0; i < clubCount - 1; i++) {
                for (int j = i + 1; j < clubCount; j++) {
                    if (stats[j].total > stats[i].total) {
                        ClubStats t = stats[i]; stats[i] = stats[j]; stats[j] = t;
                    }
                }
            }

            printf("\n=== Club Dashboard (All Clubs) ===\n");
            printf("Club         | Male | Female | Total\n");
            printf("-------------+------+------+------\n");
            for (int i = 0; i < clubCount; i++) {
                printf("%-11s | %4d | %6d | %5d\n",
                       stats[i].club, stats[i].maleCount, stats[i].femaleCount, stats[i].total);
            }
        }
        else if (choice == 2) {
            /* === Recent Student's Club Records (by enrollment year, newest first) === */
            int idx[MAX_ROWS];
            for (int i = 0; i < count; i++) idx[i] = i;

            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (students[idx[j]].enrollment_year > students[idx[i]].enrollment_year) {
                        int t = idx[i]; idx[i] = idx[j]; idx[j] = t;
                    }
                }
            }

            printf("\n=== Top 5 Recent Student's Club Records (by Enrollment Year) ===\n");
            printf("UID   | Name                    | Club           | Year\n");
            printf("------+-------------------------+----------------+------\n");
            for (int k = 0; k < count && k < 5; k++) {
                int i = idx[k];
                printf("%4d | %-11s %-12s | %-14s | %4d\n",
                       students[i].uid,
                       students[i].first_name,
                       students[i].last_name,
                       students[i].club,
                       students[i].enrollment_year);
            }
        }
        else if (choice == 3) {
            /* === New Student Records (by UID, highest first) === */
            int idx[MAX_ROWS];
            for (int i = 0; i < count; i++) idx[i] = i;

            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    if (students[idx[j]].uid > students[idx[i]].uid) {
                        int t = idx[i]; idx[i] = idx[j]; idx[j] = t;
                    }
                }
            }

            printf("\n=== New Student Records ===\n");
            printf("UID   | Name                    \n");
            printf("------+-------------------------\n");
            for (int k = 0; k < count && k < 5; k++) {
                int i = idx[k];
                printf("%4d | %-11s %-12s\n",
                       students[i].uid,
                       students[i].first_name,
                       students[i].last_name);
            }
        }
        else {
            printf("Invalid dashboard option.\n");
        }

    } while (1);
}