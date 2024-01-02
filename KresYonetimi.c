#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[50];
    int age;
    struct Student* next;
} Student;

typedef struct Class {
    char className[30];
    Student* studentList;
    char toyList[5][30];
    int toyListCount;
    struct Class* next;
} Class;

// Fonksiyon prototipleri
void createClass(Class** classList);
void addStudent(Class* classList);
void listClasses(Class* classList);
void listStudents(Class* classList);
void removeClass(Class** classList);
void removeStudent(Class* classList);
void addToy(Class* classList);
void removeToy(Class* classList);
void listToys(Class* classList);

int main() {
    Class* classList = NULL;
    int choice;

    do {
        printf("\n--- Ana Menu ---\n");
        printf("1- Yeni bir sinif olustur\n");
        printf("2- Yeni bir ogrenci ekle\n");
        printf("3- Siniflari listele\n");
        printf("4- Ogrencileri listele\n");
        printf("5- Sinif sil\n");
        printf("6- Ogrenci sil\n");
        printf("7- Oyuncak ekle\n");
        printf("8- Oyuncak cikar\n");
        printf("9- Oyuncaklari listele\n");
        printf("0- Cikis\n");

        printf("Seciminizi yapin: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createClass(&classList);
                break;
            case 2:
                addStudent(classList);
                break;
            case 3:
                listClasses(classList);
                break;
            case 4:
                listStudents(classList);
                break;
            case 5:
                removeClass(&classList);
                break;
            case 6:
                removeStudent(classList);
                break;
            case 7:
                addToy(classList);
                break;
            case 8:
                removeToy(classList);
                break;
            case 9:
                listToys(classList);
                break;
            case 0:
                printf("Program sonlandiriliyor...\n");
                break;
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }

    } while (choice != 0);

    return 0;
}

void createClass(Class** classList) {
    Class* newClass = (Class*)malloc(sizeof(Class));
    newClass->next = *classList;
    *classList = newClass;
    printf("Sinif adini girin: ");
    scanf("%s", newClass->className);
    newClass->studentList = NULL;
    printf("Sinif olusturuldu: %s\n", newClass->className);
}

void addStudent(Class* classList) {
    if (classList == NULL) {
        printf("Ogrenci eklemek icin once sinif olusturmalisiniz.\n");
        return;
    }

    char className[30];
    printf("Sinif adini girin, ana menüye dönmek için 'menu' yazın: ");
    scanf("%s", className);
    if (strcmp(className, "menu") == 0) {
        return;
    }

    Class* currentClass = classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        currentClass = currentClass->next;
    }

    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    Student* newStudent = (Student*)malloc(sizeof(Student));
    printf("Ogrenci adini girin: ");
    scanf("%s", newStudent->name);
    printf("Ogrenci yasini girin: ");
    scanf("%d", &newStudent->age);

    newStudent->next = currentClass->studentList;
    currentClass->studentList = newStudent;

    printf("Ogrenci eklendi: %s, %d yasinda\n", newStudent->name, newStudent->age);
}

void listClasses(Class* classList) {
    if (classList == NULL) {
        printf("Listelenecek sinif bulunamadi.\n");
        return;
    }

    printf("Siniflar:\n");
    while (classList != NULL) {
        printf("- %s\n", classList->className);
        classList = classList->next;
    }
}

void listStudents(Class* classList) {
    if (classList == NULL) {
        printf("Once sinif olusturmalisiniz.\n");
        return;
    }

    char className[30];
    printf("Hangi sinifin ogrencilerini listelemek istiyorsunuz? ('menu' yazarak ana menuye donun) ");
    scanf("%s", className);

    if (strcmp(className, "menu") == 0) {
        return;
    }

    Class* currentClass = classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        currentClass = currentClass->next;
    }

    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    printf("Ogrencileri listelenen sinif: %s\n", currentClass->className);

    Student* currentStudent = currentClass->studentList;
    while (currentStudent != NULL) {
        printf("- %s, %d yasinda\n", currentStudent->name, currentStudent->age);
        currentStudent = currentStudent->next;
    }
}

void removeClass(Class** classList) {
    if (*classList == NULL) {
        printf("Silinecek sinif bulunamadi.\n");
        return;
    }

    printf("Silmek istediğiniz sinifin adini girin, ana menüye dönmek için 'menu' yazın: ");
    char className[30];
    scanf("%s", className);
    if (strcmp(className, "menu") == 0) {
        return;
    }

    Class* previousClass = NULL;
    Class* currentClass = *classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        previousClass = currentClass;
        currentClass = currentClass->next;
    }

    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    if (previousClass == NULL) {
        *classList = currentClass->next;
    } else {
        previousClass->next = currentClass->next;
    }

    free(currentClass);
    printf("Sinif silindi: %s\n", className);
}

void removeStudent(Class* classList) {
    if (classList == NULL) {
        printf("Once sinif olusturmalisiniz.\n");
        return;
    }

    char className[30];
    printf("Hangi sinifin ogrencisini silmek istiyorsunuz? ('menu' yazarak ana menuye donun) ");
    scanf("%s", className);

    if (strcmp(className, "menu") == 0) {
        return;
    }

    Class* currentClass = classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        currentClass = currentClass->next;
    }

    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    printf("Silmek istediğiniz ogrencinin adini girin, ana menüye dönmek için 'menu' yazın: ");
    char studentName[50];
    scanf("%s", studentName);
    if (strcmp(studentName, "menu") == 0) {
        return;
    }

    Student* previousStudent = NULL;
    Student* currentStudent = currentClass->studentList;
    while (currentStudent != NULL) {
        if (strcmp(currentStudent->name, studentName) == 0) {
            break;
        }
        previousStudent = currentStudent;
        currentStudent = currentStudent->next;
    }

    if (currentStudent == NULL) {
        printf("Boyle bir ogrenci bulunamadi.\n");
        return;
    }

    if (previousStudent == NULL) {
        currentClass->studentList = currentStudent->next;
    } else {
        previousStudent->next = currentStudent->next;
    }

    free(currentStudent);
    printf("Ogrenci silindi: %s, %s\n", studentName, className);
}

void addToy(Class* classList) {
    if (classList == NULL) {
        printf("Once sinif olusturmalisiniz.\n");
        return;
    }

    char className[30];
    printf("Hangi sinifa oyuncak eklemek istiyorsunuz? ('menu' yazarak ana menuye donun) ");
    scanf("%s", className);

    if (strcmp(className, "menu") == 0) {
        return;
    }

    Class* currentClass = classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        currentClass = currentClass->next;
    }

    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    if (currentClass->toyListCount == 5) {
        printf("Sinifin oyuncak kapasitesi dolu.\n");
        return;
    }

    printf("Oyuncak adini girin: ");
    scanf("%s", currentClass->toyList[currentClass->toyListCount]);
    currentClass->toyListCount++;

    printf("Oyuncak eklendi: %s, %s sinifi\n", currentClass->toyList[currentClass->toyListCount - 1], className);
}

void removeToy(Class* classList) {
    if (classList == NULL) {
        printf("Once sinif olusturmalisiniz.\n");
        return;
    }

    char className[30];
    printf("Hangi sinifin oyuncagini cikarmak istiyorsunuz? ('menu' yazarak ana menuye donun) ");
    scanf("%s", className);

    if (strcmp(className, "menu") == 0) {
        return;
    }

    Class* currentClass = classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        currentClass = currentClass->next;
    }

    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    if (currentClass->toyListCount == 0) {
        printf("Sinifin oyuncak listesi bos.\n");
        return;
    }

    printf("Oyuncak cikarildi: %s, %s sinifi\n", currentClass->toyList[currentClass ->toyListCount - 1], className);

    currentClass->toyListCount--;
}

void listToys(Class* classList) {
    if (classList == NULL) {
        printf("Once sinif olusturmalisiniz.\n");
        return;
    }

    char className[30];
    printf("Hangi sinifin oyuncaklarini listelemek istiyorsunuz? ('menu' yazarak ana menuye donun) ");
    scanf("%s", className);

    if (strcmp(className, "menu") == 0) {
        return;
    }

    Class* currentClass = classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        currentClass = currentClass->next;
    }

    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    if (currentClass->toyListCount == 0) {
        printf("%s sinifinin oyuncak listesi bos.\n", className);
        return;
    }

    printf("%s sinifinin oyuncaklari:\n", className);
    for (int i = 0; i < currentClass->toyListCount; ++i) {
        printf("- %s\n", currentClass->toyList[i]);
    }
}

