/* 
Problem Statement : Consider a student database of SEIT class (at least 15
records). Database contains different fields of
every student like Roll No, Name and SGPA.(array of structure)
a)  Design a roll call list, arrange list of students according to roll numbers   in ascending order (Use Bubble Sort)
b)  Arrange list of students alphabetically. (Use Insertion sort)
c)  Arrange list of students to find out first ten toppers from a class. (Use Quick
sort)
d)  Search students according to SGPA. If more than one student having same
SGPA, then print list of all students having same SGPA.
e)  Search a particular student according to name using binary search *
*/
#include<iostream>
#include<cstring>
using namespace std;

struct Student {
    char name[30];
    int roll;
    double sgpa;
};

void display(struct Student s[], int n);
void displaycolmn(struct Student s[], int l, int n);
void bubblesort(struct Student s[], int n);
void InsertionSort(struct Student s[], int n);
int partition(Student s[], int low, int high);
void QuickSort(Student s[], int low, int high);
void LinearSearch(Student s[], int n, double sgpa);
int BinarySearch(Student s[], int low, int high, char target[]);

int main() {
    Student s[15] = { {"Rohan", 05, 8.5},{"Meera", 9, 9.8},{"Ananya", 06, 7.8},
                      {"Karan", 10, 8.9},{"Priya", 02, 9.2}, {"Aditya", 12, 8.5},
                      {"Sneha", 04, 8.3},{"Vikram",15, 8.7}, {"Nisha",  8, 8.1},
                      {"Arjun", 01, 8.5},{"Kavya", 11, 9.2}, {"Rahul",  13, 7.2},
                      {"Ishita",14, 8.5},{"Pratik", 07, 9.2},{"Manish", 03, 8.1} };
    
    int choice;
    double sgpa;
    char name[30];
    
    do {
        cout << "\n=============================================";
        cout << "\nMenu:\n";
        cout << "1. Display Students\n";
        cout << "2. Bubble Sort by Roll Number\n";
        cout << "3. Insertion Sort by Name\n";
        cout << "4. QuickSort by SGPA and Display Top 10\n";
        cout << "5. Linear Search by SGPA\n";
        cout << "6. Binary Search by Name\n";
        cout << "7. Exit\n";
        cout << "=============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                display(s, 15);
                break;
                
            case 2:
                bubblesort(s, 15);
                cout << "Sorted by Roll Number:\n";
                display(s, 15);
                break;
                
            case 3:
                InsertionSort(s, 15);
                cout << "Sorted by Name:\n";
                display(s, 15);
                break;
                
            case 4:
                QuickSort(s, 0, 14);
                cout << "Top 10 Students by SGPA:\n";
                displaycolmn(s, 14, 10);
                break;
                
            case 5:
                cout << "Enter SGPA to search: ";
                cin >> sgpa;
                LinearSearch(s, 15, sgpa);
                break;
                
            case 6:{
                cout << "Enter Name to search: ";
                cin >> name;
                bubblesort(s, 15); // Ensure array is sorted by name for binary search
                int result = BinarySearch(s, 0, 14, name);
                if (result != -1) {
                    cout << "Student Found: " << s[result].name << " with Roll No. " << s[result].roll << " and SGPA " << s[result].sgpa << endl;
                } else {
                    cout << "Student not found!\n";
                }
                break;
            }
            case 7:
                cout << "Exiting...\n";
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);
    
    return 0;
}

void displaycolmn(struct Student s[], int l, int n) {
    cout << "==============================\n";
    cout << "Idx  NAME  \tROLL\tSGPA\n";
    cout << "==============================\n";
    for (int k = 1, i = l; i > l - n; i--, k++) {
        cout << k << ". " << s[i].name << "  \t" << s[i].roll << "\t" << s[i].sgpa << endl;
    }
}

void display(struct Student s[], int n) {
    cout << "==============================\n";
    cout << "Idx  NAME  \tROLL\tSGPA\n";
    cout << "==============================\n";
    for (int i = 0; i < n; i++) {
        cout << i+1 << ". " << s[i].name << "  \t" << s[i].roll << "\t" << s[i].sgpa << endl;
    }
    cout << "==============================\n\n";
}

void bubblesort(struct Student s[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(s[j].name, s[j + 1].name) > 0) {
                Student temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}

void InsertionSort(struct Student s[], int n) {
    for (int i = 1; i < n; i++) {
        Student temp = s[i];
        int hole = i;
        while (hole > 0 && strcmp(s[hole - 1].name, temp.name) > 0) {
            s[hole] = s[hole - 1];
            hole--;
        }
        s[hole] = temp;
    }
}

int partition(Student s[], int low, int high) {
    Student pvt = s[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (s[j].sgpa < pvt.sgpa) {
            i++;
            Student temp = s[j];
            s[j] = s[i];
            s[i] = temp;
        }
    }
    i++;
    Student temp = s[high];
    s[high] = s[i];
    s[i] = temp;
    return i;
}

void QuickSort(Student s[], int low, int high) {
    if (low < high) {
        int pvt = partition(s, low, high);
        QuickSort(s, low, pvt - 1);
        QuickSort(s, pvt + 1, high);
    }
}

void LinearSearch(Student s[], int n, double sgpa) {
    bool notfound = true;
    cout << "==============================\n";
    cout << "NAME  \t\tROLL\n";
    cout << "==============================\n";
    for (int i = 0; i < n; i++) {
        if (s[i].sgpa == sgpa) {
            cout << s[i].name << " \t\t" << s[i].roll << endl;
            notfound = false;
        }
    }
    if (notfound)
        cout << "No students found having " << sgpa << " SGPA!\n";
}

int BinarySearch(Student s[], int low, int high, char target[]) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int res = strcmp(s[mid].name, target);
        if (res == 0) {
            return mid;
        }
        if (res < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}



=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 1
==============================
Idx  NAME       ROLL    SGPA
==============================
1. Rohan        5       8.5
2. Meera        9       9.8
3. Ananya       6       7.8
4. Karan        10      8.9
5. Priya        2       9.2
6. Aditya       12      8.5
7. Sneha        4       8.3
8. Vikram       15      8.7
9. Nisha        8       8.1
10. Arjun       1       8.5
11. Kavya       11      9.2
12. Rahul       13      7.2
13. Ishita      14      8.5
14. Pratik      7       9.2
15. Manish      3       8.1
==============================


=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 2
Sorted by Roll Number:
==============================
Idx  NAME       ROLL    SGPA
==============================
1. Aditya       12      8.5
2. Ananya       6       7.8
3. Arjun        1       8.5
4. Ishita       14      8.5
5. Karan        10      8.9
6. Kavya        11      9.2
7. Manish       3       8.1
8. Meera        9       9.8
9. Nisha        8       8.1
10. Pratik      7       9.2
11. Priya       2       9.2
12. Rahul       13      7.2
13. Rohan       5       8.5
14. Sneha       4       8.3
15. Vikram      15      8.7
==============================


=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 3
Sorted by Name:
==============================
Idx  NAME       ROLL    SGPA
==============================
1. Aditya       12      8.5
2. Ananya       6       7.8
3. Arjun        1       8.5
4. Ishita       14      8.5
5. Karan        10      8.9
6. Kavya        11      9.2
7. Manish       3       8.1
8. Meera        9       9.8
9. Nisha        8       8.1
10. Pratik      7       9.2
11. Priya       2       9.2
12. Rahul       13      7.2
13. Rohan       5       8.5
14. Sneha       4       8.3
15. Vikram      15      8.7
==============================


=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 4
Top 10 Students by SGPA:
==============================
Idx  NAME       ROLL    SGPA
==============================
1. Meera          9         9.8
2. Kavya        11         9.2
3. Priya           2         9.2
4. Pratik          7         9.2
5. Karan        10         8.9
6. Vikram      15         8.7
7. Rohan         5         8.5
8. Ishita        14         8.5
9. Arjun          1         8.5
10. Aditya     12        8.5


=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 5
Enter SGPA to search: 9.2
==============================
NAME            ROLL
==============================
Pratik          7
Priya           2
Kavya           11

=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 5
Enter SGPA to search: 8.5
==============================
NAME            ROLL
==============================
Aditya          12
Arjun           1
Ishita          14
Rohan           5

=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 5 
Enter SGPA to search: 10
==============================
NAME            ROLL
==============================
No students found having 10 SGPA!

=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 6
Enter Name to search: Pratik
Student Found: Pratik with Roll No. 7 and SGPA 9.2

=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 6
Enter Name to search: ABC
Student not found!

=============================================
Menu:
1. Display Students
2. Bubble Sort by Roll Number
3. Insertion Sort by Name
4. QuickSort by SGPA and Display Top 10
5. Linear Search by SGPA
6. Binary Search by Name
7. Exit
=============================================
Enter your choice: 7
Exiting...
