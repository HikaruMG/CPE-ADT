#include <stdio.h>
#include <math.h>
#define namel 31
typedef struct student {
    char name[namel];
    int gpa;

} student_t;

inputStudent(student_t students[], int n) {
    for (int i = 0; i < n; ++i) {
        scanf("%s %d", students[i].name, &students[i].gpa);
    }
}
float calmean(student_t students[], int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += students[i].gpa;
    }
    return sum / n;
}
float calstd(student_t students[],int n,float mean){
    float sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += pow(students[i].gpa - mean, 2);
    }
    return sqrt(sum / (n - 1));
}

showStudentGrade(student_t students[], int n) {
    float mean = calmean(students,n);
    float std = calstd(students,n,mean);
    for (int i = 0; i < n; ++i) {
        char grade;
        double score = students[i].gpa;

        if (score >= mean + 1.5 * std) {
            grade = 'A';
        } else if (score >= mean + std) {
            grade = 'B';
        } else if (score >= mean - std) {
            grade = 'C';
        } else if (score >= mean - 1.5 * std) {
            grade = 'D';
        } else {
            grade = 'F';
        }
        
        printf("%s %c\n", students[i].name, grade);
    }
}
int main(void) {
student_t students[1000];
int n;
scanf("%d", &n);
inputStudent(students, n);
showStudentGrade(students, n);
return 0;
}