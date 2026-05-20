// Student Fee Management System
// Features:
// Store student details
// Store semester fee details
// Check paid/unpaid fees
// Generate receipts
// Search student records
// Update payment status
// Save data permanently using files

#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student
{
    char name[50];
    int id;
    float fee;
    int paid;
};


void saveToFile(struct Student students[], int count);
void loadFromFile(struct Student students[], int *count);
void updatePaymentStatus(struct Student students[], int count, int id);
void generateReceipt(struct Student students[], int count, int id);
void searchStudent(struct Student students[], int count, int id);
void updateStudentRecord(struct Student students[], int count, int id, float newFee);
void displayUnpaidStudents(struct Student students[], int count);
void displayPaidStudents(struct Student students[], int count);
void displayAllStudents(struct Student students[], int count);
void deleteStudentRecord(struct Student students[], int *count, int id);
void displayMenu();
void handleUserChoice(struct Student students[], int *count, int choice);

void saveToFile(struct Student students[], int count)
{
    FILE *file = fopen("students.txt", "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s,%d,%.2f,%d\n",
                students[i].name,
                students[i].id,
                students[i].fee,
                students[i].paid
                );

    }

    fclose(file);
}

void loadFromFile(struct Student students[], int *count)
{
    FILE *file = fopen("students.txt", "r");

    if (file == NULL)
    {
        printf("No existing records found.\n");
        return;
    }

    while (fscanf(file, " %49[^,],%d,%f,%d",
                  students[*count].name,
                  &students[*count].id,
                  &students[*count].fee,
                  &students[*count].paid) == 4)
    {
        (*count)++;
    }

    fclose(file);
}

void updatePaymentStatus(struct Student students[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            students[i].paid = 1;

            printf("Payment status updated successfully.\n");
            return;
        }
    }

    printf("Student not found.\n");
}

void generateReceipt(struct Student students[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            printf("\n========================\n");
            printf("       FEE RECEIPT\n");
            printf("========================\n");

            printf("Name   : %s\n", students[i].name);
            printf("ID     : %d\n", students[i].id);
            printf("Fee    : %.2f\n", students[i].fee);
            printf("Status : %s\n",
                   students[i].paid ? "Paid" : "Unpaid");

            printf("========================\n");

            return;
        }
    }

    printf("Student not found.\n");
}

void searchStudent(struct Student students[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            printf("\nStudent Found\n");

            printf("Name   : %s\n", students[i].name);
            printf("ID     : %d\n", students[i].id);
            printf("Fee    : %.2f\n", students[i].fee);
            printf("Status : %s\n",
                   students[i].paid ? "Paid" : "Unpaid");

            return;
        }
    }

    printf("Student not found.\n");
}

void updateStudentRecord(struct Student students[], int count, int id, float newFee)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            students[i].fee = newFee;

            printf("Student record updated successfully.\n");
            return;
        }
    }

    printf("Student not found.\n");
}

void displayUnpaidStudents(struct Student students[], int count)
{
    printf("\n--- Unpaid Students ---\n");

    for (int i = 0; i < count; i++)
    {
        if (!students[i].paid)
        {
            printf("%s (ID: %d)\n",
                   students[i].name,
                   students[i].id);
        }
    }
}

void displayPaidStudents(struct Student students[], int count)
{
    printf("\n--- Paid Students ---\n");

    for (int i = 0; i < count; i++)
    {
        if (students[i].paid)
        {
            printf("%s (ID: %d)\n",
                   students[i].name,
                   students[i].id);
        }
    }
}

void displayAllStudents(struct Student students[], int count)
{
    printf("\n--- All Students ---\n");

    for (int i = 0; i < count; i++)
    {
        printf("Name   : %s\n", students[i].name);
        printf("ID     : %d\n", students[i].id);
        printf("Fee    : %.2f\n", students[i].fee);
        printf("Status : %s\n",
               students[i].paid ? "Paid" : "Unpaid");

        printf("----------------------\n");
    }
}

void deleteStudentRecord(struct Student students[], int *count, int id)
{
    char confirm;

    printf("Are you sure you want to delete? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm != 'y' && confirm != 'Y')
    {
        printf("Deletion cancelled.\n");
        return;
    }

    for (int i = 0; i < *count; i++)
    {
        if (students[i].id == id)
        {
            for (int j = i; j < *count - 1; j++)
            {
                students[j] = students[j + 1];
            }

            (*count)--;

            printf("Student record deleted successfully.\n");
            return;
        }
    }

    printf("Student not found.\n");
}

void displayMenu()
{
    printf("\n====================================\n");
    printf("   STUDENT FEES MANAGEMENT SYSTEM\n");
    printf("====================================\n");

    printf("1. Add Student\n");
    printf("2. Update Payment Status\n");
    printf("3. Generate Receipt\n");
    printf("4. Search Student\n");
    printf("5. Update Student Record\n");
    printf("6. Display Unpaid Students\n");
    printf("7. Display Paid Students\n");
    printf("8. Display All Students\n");
    printf("9. Delete Student Record\n");
    printf("0. Exit\n");
}

void handleUserChoice(struct Student students[], int *count, int choice)
{
    int id;
    float fee;
    char name[50];

    switch (choice)
    {
    case 1:

        if (*count >= MAX)
        {
            printf("Student limit reached!\n");
            break;
        }

        printf("Enter student name: ");
        scanf(" %[^\n]", name);

        printf("Enter student ID: ");
        scanf("%d", &id);

        // Duplicate ID Check
        for (int i = 0; i < *count; i++)
        {
            if (students[i].id == id)
            {
                printf("Student ID already exists!\n");
                return;
            }
        }

        printf("Enter semester fee: ");
        scanf("%f", &fee);

        students[*count].id = id;
        students[*count].fee = fee;
        students[*count].paid = 0;

        strcpy(students[*count].name, name);

        (*count)++;

        saveToFile(students, *count);

        printf("Student added successfully.\n");

        break;

    case 2:

        printf("Enter student ID: ");
        scanf("%d", &id);

        updatePaymentStatus(students, *count, id);

        saveToFile(students, *count);

        break;

    case 3:

        printf("Enter student ID: ");
        scanf("%d", &id);

        generateReceipt(students, *count, id);

        break;

    case 4:

        printf("Enter student ID: ");
        scanf("%d", &id);

        searchStudent(students, *count, id);

        break;

    case 5:

        printf("Enter student ID: ");
        scanf("%d", &id);

        printf("Enter new semester fee: ");
        scanf("%f", &fee);

        updateStudentRecord(students, *count, id, fee);

        saveToFile(students, *count);

        break;

    case 6:

        displayUnpaidStudents(students, *count);

        break;

    case 7:

        displayPaidStudents(students, *count);

        break;

    case 8:

        displayAllStudents(students, *count);

        break;

    case 9:

        printf("Enter student ID: ");
        scanf("%d", &id);

        deleteStudentRecord(students, count, id);

        saveToFile(students, *count);

        break;

    case 0:

        printf("Exiting Program...\n");

        break;

    default:

        printf("Invalid choice!\n");
    }
}

int main()
{
    struct Student students[MAX];

    int count = 0;

    int choice;

    loadFromFile(students, &count);

    do
    {
        displayMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        handleUserChoice(students, &count, choice);

    } while (choice != 0);

    return 0;
}