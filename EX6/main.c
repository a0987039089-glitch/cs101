#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct employee {
    int id;
    int age;
    double salary;
    char name[50];
} employee_t;
void emp_info(employee_t emp) {
    printf("employee id = %d\n", emp.id);
    printf("employee name = %s\n", emp.name);
    printf("employee age = %d\n", emp.age);
    printf("employee salary = %f\n", emp.salary);
}
int emp_average_age(employee_t emp[], int n) {
    int i;
    int sum = 0;
    if (n == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        sum += emp[i].age;
    }
    return sum / n;
}
void emp_writefile(employee_t emp[], int n) {
    FILE *fp = fopen("employee.bin", "wb");
    if (fp == NULL) 
        printf("Error: Cannot open file for writing.\n");
        exit(1);
    }
    fwrite(emp, sizeof(employee_t), n, fp);
    fclose(fp);
}
void emp_readfile(employee_t emp[], int n) {
    FILE *fp = fopen("employee.bin", "rb");
    if (fp == NULL) {
        printf("Error: Cannot open file for reading.\n");
        exit(1);
    }
    fread(emp, sizeof(employee_t), n, fp);
    fclose(fp);
}
int main() {
    employee_t emp[3];
    emp[0].id = 1;
    emp[0].age = 20;
    emp[0].salary = 30000.0;
    strcpy(emp[0].name, "IU")
    emp[1].id = 2;
    emp[1].age = 26;
    emp[1].salary = 36000.0;
    strcpy(emp[1].name, "taylor");
    emp[2].id = 3
    emp[2].age = 31;
    emp[2].salary = 90000.0;
    strcpy(emp[2].name, "swift");
    emp_writefile(emp, 3);
    employee_t read_emp[10];
    emp_readfile(read_emp, 3);
    for (int i = 0; i < 3; i++) {
        emp_info(read_emp[i]);
    }
    return 0;
}
