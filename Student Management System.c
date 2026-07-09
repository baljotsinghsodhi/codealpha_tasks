#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Exiting Program...\n");
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}

// Add Student
void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("File cannot be opened!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student Record Added Successfully.\n");
}

// Display Students
void displayStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n%-10s %-25s %-10s\n", "Roll", "Name", "Marks");
    printf("-----------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%-10d %-25s %-10.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}

// Search Student
void searchStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found\n");
            printf("Roll : %d\n", s.roll);
            printf("Name : %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Record Not Found.\n");

    fclose(fp);
}

// Update Student
void updateStudent() {
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Record Updated Successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Record Not Found.\n");

    fclose(fp);
}

// Delete Student
void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Record Deleted Successfully.\n");
    else
        printf("Student Record Not Found.\n");
}