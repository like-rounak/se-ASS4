#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Learner
{
    int roll_no;
    char full_name[50];
    int marks1;
    int marks2;
    int marks3;
    int marks4;
    int marks5;
    int total_marks;
} student;

FILE *file_pointer;
int count_students = 0;

void add_learner()
{
    file_pointer = fopen("learner.txt", "ab");

    printf("Enter learner's full name: ");
    scanf("%s", &student.full_name);
    getchar();

    printf("Enter learner's roll number: ");
    scanf("%d", &student.roll_no);
    getchar();

    int sum = 0;
    int i = 0;
    printf("Enter marks of Calculus: ");
    scanf("%d", &student.marks1);
    printf("Enter marks of Computer Programming: ");
    scanf("%d", &student.marks2);
    printf("Enter marks of Physics: ");
    scanf("%d", &student.marks3);
    printf("Enter marks of Chemistry: ");
    scanf("%d", &student.marks4);
    printf("Enter marks of Biology: ");
    scanf("%d", &student.marks5);
    student.total_marks = student.marks1 + student.marks2 + student.marks3 + student.marks4 + student.marks5;

    printf("Learner added successfully...\n");
    count_students++;
    fwrite(&student, sizeof(student), 1, file_pointer);
    fclose(file_pointer);
}

void update_marks()
{
    int roll_number, found;

    printf("\n-----Update marks-----\n");
    printf("Enter learner's roll number to update: ");
    scanf("%d", &roll_number);

    file_pointer = fopen("learner.txt", "rb+");

    while (fread(&student, sizeof(student), 1, file_pointer) == 1)
    {
        if (roll_number == student.roll_no)
        {
            found = 1;
            printf("Enter the new set of marks\n");
            int i = 0;
            student.total_marks = 0;
            printf("Enter marks of Calculus: ");
            scanf("%d", &student.marks1);
            printf("Enter marks of Computer Programming: ");
            scanf("%d", &student.marks2);
            printf("Enter marks of Physics: ");
            scanf("%d", &student.marks3);
            printf("Enter marks of Chemistry: ");
            scanf("%d", &student.marks4);
            printf("Enter marks of Biology: ");
            scanf("%d", &student.marks5);
            student.total_marks = student.marks1 + student.marks2 + student.marks3 + student.marks4 + student.marks5;

            fseek(file_pointer, -sizeof(student), 1);
            fwrite(&student, sizeof(student), 1, file_pointer);
            fclose(file_pointer);
            break;
        }
    }

    if (found == 1)
    {
        printf("\nMarks updated successfully...\n");
    }
    else
    {
        printf("\nLearner not found...\n");
    }
}

void display_learners()
{
    system("cls");
    printf("\n---Learner Details----\n");
    printf("%-10s %-30s %-20s %-20s %-20s %-20s %-20s %-20s\n", "Roll No", "Name",
           "Calculus", "Computer Programming", "Physics", "Chemistry", "Biology", "Total Marks");

    file_pointer = fopen("learner.txt", "rb");
    while (fread(&student, sizeof(student), 1, file_pointer) == 1)
    {
        printf("%-10d %-30s %-20d %-20d %-20d %-20d %-20d %-20d\n", student.roll_no, student.full_name,
               student.marks1, student.marks2, student.marks3, student.marks4, student.marks5, student.total_marks);
    }
    fclose(file_pointer);
}

void teacher_interface()
{
    int choice;
    printf("\n1. Add learner\n");
    printf("2. Update marks\n");
    printf("3. Display marks\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        add_learner();
        break;
    case 2:
        update_marks();
        break;
    case 3:
        display_learners();
        break;
    default:
        printf("Invalid choice\n");
    }
}

void student_interface()
{
    display_learners();
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n1. Teacher\n");
        printf("2. Student\n");
        printf("0. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            teacher_interface();
            break;
        case 2:
            student_interface();
            break;
        case 0:
            exit(0);
        default:
            printf("Invalid input\n");
        }
    }
}
