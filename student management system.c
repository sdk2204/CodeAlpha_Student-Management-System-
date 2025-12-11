#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Student 
{
    int roll;
    char name[50];
    int age;
    float marks;
};
void addStudent() 
{
    struct Student s;
    FILE *fp=fopen("students.dat","ab");
    if(!fp) 
	{
        printf("Error opening file!\n");
        return;
    }
    printf("\nEnter Roll Number: ");
    scanf("%d",&s.roll);
    printf("Enter Name: ");
    scanf("%s",s.name);
    printf("Enter Age: ");
    scanf("%d",&s.age);
    printf("Enter Marks: ");
    scanf("%f",&s.marks);
    fwrite(&s,sizeof(s), 1, fp);
    fclose(fp);
    printf("\nStudent added successfully!\n");
}
void displayStudents() 
{
    struct Student s;
    FILE *fp=fopen("students.dat","rb");

    if(!fp) 
	{
        printf("\nNo records found!\n");
        return;
    }
    printf("\n--- Student Records ---\n");
    while(fread(&s,sizeof(s),1,fp)) 
	{
        printf("\nRoll: %d\nName: %s\nAge: %d\nMarks: %.2f\n",
               s.roll, s.name, s.age, s.marks);
    }
    fclose(fp);
}
void searchStudent() 
{
    struct Student s;
    int roll,found=0;
    printf("\nEnter roll number to search: ");
    scanf("%d",&roll);
    FILE *fp=fopen("students.dat","rb");
    if(!fp) 
	{
        printf("File not found!\n");
        return;
    }
    while (fread(&s,sizeof(s),1,fp)) 
	{
        if(s.roll==roll) 
		{
            printf("\n--- Student Found ---\n");
            printf("Roll: %d\nName: %s\nAge: %d\nMarks: %.2f\n",s.roll,
			s.name,s.age,s.marks);
            found=1;
            break;
        }
    }
    if (!found)
        printf("\nNo student found with roll %d\n",roll);
    fclose(fp);
}
void deleteStudent() 
{
    struct Student s;
    int roll,found=0;
    printf("\nEnter roll number to delete: ");
    scanf("%d",&roll);
    FILE *fp=fopen("students.dat","rb");
    FILE *ft=fopen("temp.dat","wb");
    if(!fp || !ft) 
	{
        printf("Error opening file!\n");
        return;
    }
    while (fread(&s,sizeof(s),1,fp)) 
	{
        if (s.roll==roll) 
		{
            found=1;
            continue;
        }
        fwrite(&s,sizeof(s),1,ft);
    }
    fclose(fp);
    fclose(ft);
    remove("students.dat");
    rename("temp.dat","students.dat");
    if(found)
        printf("\nRecord deleted successfully!\n");
    else
        printf("\nRecord not found.\n");
}
void updateStudent() 
{
    struct Student s;
    int roll,found=0;
    printf("\nEnter roll number to update: ");
    scanf("%d",&roll);
    FILE *fp =fopen("students.dat","rb+");
    if(!fp) 
	{
        printf("File not found!\n");
        return;
    }
    while(fread(&s,sizeof(s),1,fp)) 
	{
        if(s.roll==roll) 
		{
            found=1;
            printf("\nEnter new Name: ");
            scanf("%s",s.name);
            printf("Enter new Age: ");
            scanf("%d",&s.age);
            printf("Enter new Marks: ");
            scanf("%f",&s.marks);
            fseek(fp,-sizeof(s),SEEK_CUR);
            fwrite(&s,sizeof(s),1,fp);
            printf("\nRecord updated successfully!\n");
            break;
        }
    }
    if(!found)
        printf("\nRecord not found.\n");
    fclose(fp);
}
int main() 
{
    int choice;
    while (1) 
	{
        printf("\n--- STUDENT MANAGEMENT SYSTEM ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch (choice) 
		{
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
