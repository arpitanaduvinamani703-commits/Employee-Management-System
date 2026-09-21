#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employees.dat"

struct Employee {
    int id;
    char name[50];
    int age;
    char department[50];
    char designation[50];
    float salary;
};

void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
void updateEmployee(void);
void deleteEmployee(void);

int main(void) {
    int choice;

    do {
        printf("\n========================================\n");
        printf("       EMPLOYEE MANAGEMENT SYSTEM\n");
        printf("========================================\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                updateEmployee();
                break;
            case 5:
                deleteEmployee();
                break;
            case 6:
                printf("\nThank you for using the system!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}

void addEmployee(void) {
    struct Employee emp;
    FILE *file = fopen(FILE_NAME, "ab");

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    printf("\nEnter Employee ID: ");
    scanf("%d", &emp.id);

    printf("Enter Name: ");
    scanf(" %[^\n]", emp.name);

    printf("Enter Age: ");
    scanf("%d", &emp.age);

    printf("Enter Department: ");
    scanf(" %[^\n]", emp.department);

    printf("Enter Designation: ");
    scanf(" %[^\n]", emp.designation);

    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(struct Employee), 1, file);
    fclose(file);

    printf("\nEmployee added successfully!\n");
}

void displayEmployees(void) {
    struct Employee emp;
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo employee records found.\n");
        return;
    }

    printf("\n=========== EMPLOYEE RECORDS ===========\n");

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        printf("\nID          : %d", emp.id);
        printf("\nName        : %s", emp.name);
        printf("\nAge         : %d", emp.age);
        printf("\nDepartment  : %s", emp.department);
        printf("\nDesignation : %s", emp.designation);
        printf("\nSalary      : %.2f\n", emp.salary);
        printf("----------------------------------------\n");
    }

    fclose(file);
}

void searchEmployee(void) {
    struct Employee emp;
    int id, found = 0;

    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo employee records found.\n");
        return;
    }

    printf("\nEnter Employee ID to search: ");
    scanf("%d", &id);

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.id == id) {
            printf("\nEmployee Found!\n");
            printf("ID          : %d\n", emp.id);
            printf("Name        : %s\n", emp.name);
            printf("Age         : %d\n", emp.age);
            printf("Department  : %s\n", emp.department);
            printf("Designation : %s\n", emp.designation);
            printf("Salary      : %.2f\n", emp.salary);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nEmployee not found.\n");
    }

    fclose(file);
}

void updateEmployee(void) {
    struct Employee emp;
    int id, found = 0;

    FILE *file = fopen(FILE_NAME, "rb+");

    if (file == NULL) {
        printf("\nNo employee records found.\n");
        return;
    }

    printf("\nEnter Employee ID to update: ");
    scanf("%d", &id);

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.id == id) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", emp.name);

            printf("Enter New Age: ");
            scanf("%d", &emp.age);

            printf("Enter New Department: ");
            scanf(" %[^\n]", emp.department);

            printf("Enter New Designation: ");
            scanf(" %[^\n]", emp.designation);

            printf("Enter New Salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -(long)sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);

            found = 1;
            printf("\nEmployee updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("\nEmployee not found.\n");
    }

    fclose(file);
}

void deleteEmployee(void) {
    struct Employee emp;
    int id, found = 0;

    FILE *file = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (file == NULL || temp == NULL) {
        printf("\nUnable to open file.\n");

        if (file != NULL)
            fclose(file);

        if (temp != NULL)
            fclose(temp);

        return;
    }

    printf("\nEnter Employee ID to delete: ");
    scanf("%d", &id);

    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.id == id) {
            found = 1;
            continue;
        }

        fwrite(&emp, sizeof(struct Employee), 1, temp);
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("\nEmployee deleted successfully!\n");
    else
        printf("\nEmployee not found.\n");
}
