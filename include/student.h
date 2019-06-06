#ifndef STUDENT
#define STUDENT

// student record containing an id and grade point average
struct Student
{
    int     studID;
    float   gpa;
};  

// overload "==" by comparing student id
int operator== (Student a, Student b)
{
    return a.studID == b.studID;
}

#endif	// STUDENT
