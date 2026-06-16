#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define MAX_STUDENTS 1000

typedef struct 
{
    int id;
    char name[100];
    int age;
    float gpa;
}Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveStudent();

int main()
{
    int choice = 0;
    do
    {
        printf("\n=== Student Management ===\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. View All\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case  1:
            addStudent();
            break;
        case 2:
            searchStudent();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            viewStudents();
            break;
        case 6:
            printf("Thank you!");
            break;
        default:
            break;
        }
    } while (choice != 6);
    
    return 0;
}

void addStudent()
{
    if(studentCount >= MAX_STUDENTS)
    {
        printf("Already Full!");
        return;
    }
    
    printf("Enter your ID: ");
    scanf("%d", &students[studentCount].id);
    while(getchar() !=  '\n');
    printf("Enter Name: ");
    fgets(students[studentCount].name, sizeof(students[studentCount].name), stdin);
    students[studentCount].name[strcspn(students[studentCount].name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &students[studentCount].age);
    printf("Enter GPA: ");
    scanf("%f", &students[studentCount].gpa);
    studentCount++;
    printf("Student added successfully");
}

void viewStudents()
{
    if(studentCount == 0)
    {
        printf("No student available.\n");
        return;
    }
    printf("\n=== Student Lists ===\n");
    for(int i = 0 ; i < studentCount ; i++)
    {
        printf("Name: %s, Age: %d, ID: %d, GPA: %.2f\n",
                students[i].name,
                students[i].age,
                students[i].id,
                students[i].gpa);
    }
}

void searchStudent()
{   
    int choice;
    int found = 0;

    //i want to search it by ID or gpa
    printf("Search Student ID/GPA(1 or 2): ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        int searchID;
        printf("Enter Student ID to search: ");
        scanf("%d",&searchID);
        for(int i = 0 ; i < studentCount ; i++)
        {
            if(students[i].id == searchID)
            {
                printf("Student Found!\nName: %s\nAge: %d\nID: %d\nGPA: %.2f",
                students[i].name,
                students[i].age,
                students[i].id,
                students[i].gpa
            );
                found = 1;
            }
        }
    }
    else if(choice == 2)
    {
        float searchGpa;
        printf("Enter Student GPA: ");
        scanf("%f", &searchGpa);
        for(int i = 0; i < studentCount ; i++)
        {
            if(students[i].gpa == searchGpa)
            {
                printf("Student Found\nName: %s\nAge: %d\nID: %d\nGPA: %.2f",
                    students[i].name,
                    students[i].age,
                    students[i].id,
                    students[i].gpa                
                );
                found = 1;
            }
        }
    }else{
        if(found == 0)
        {
            printf("Student not found");
        }
    }
}

void updateStudent()
{
    //we updated tru ID:
    int searchID;
    viewStudents();
    printf("Enter student ID to update: ");
    scanf("%d",&searchID);
    for(int i = 0 ; i < studentCount ; i++)
    {
        if(students[i].id == searchID)
        {
            printf("Student Found\nName: %s\nAge: %d\nID: %d\nGPA: %.2f",
                students[i].name,
                students[i].age,
                students[i].id,
                students[i].gpa                
            );

            getchar();

            printf("Enter new name: \n");
            fgets(students[i].name, sizeof(students[i].name), stdin);

            printf("Enter new age: \n");
            scanf("%d", &students[i].age);

            printf("Enter new GPA: \n");
            scanf("%f", &students[i].gpa);

            printf("Student updated successfully!");
        }
    }
}

void deleteStudent()
{
    int searchID;
    printf("Search Student to Delete: ");
    scanf("%d", &searchID);
    for(int i = 0 ; i < studentCount ; i++)
    {
        if(students[i].id == searchID)
        {
            for(int j = 0 ; j < studentCount ; j++)
            {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Student deleted successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void saveStudent()
{
    FILE *fp = fopen("students.txt", "w");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    for(int i = 0 ; i < studentCount ; i++)
    {
        fprintf(fp, "%d %s %d %.2f\n",
            students[i].id,
            students[i].name,
            students[i].age,
            students[i].gpa);
    }
    fclose(fp);
}