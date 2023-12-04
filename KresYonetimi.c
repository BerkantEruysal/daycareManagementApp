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
    newClass->next = NULL;
    char className[30];
    printf("Sinif adini girin: ");
    scanf("%s", className);
    strcpy(newClass->className, className);
    classList = &newClass;
    printf("Sinif olusturuldu.\n");
}

void addStudent(Class* classList) {
    // classList linked listi boş ise öğrenci eklenemez.
    if (classList == NULL) {
        printf("Ogrenci eklemek icin once sinif olusturmalisiniz.\n");
        return;
    }
    char className[30];
    printf("Sinif adini girin, ana menüye dönmek için menu yazın: ");
    scanf("%s", className);
    if (strcmp(className, "menu") == 0) {
        return;
    }

    // classList linked listinde className ile eşleşen bir sınıf var mı kontrol edilir.
    Class* currentClass = classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        currentClass = currentClass->next;
    }

    // Eğer eşleşen bir sınıf yoksa hata mesajı verilir.
    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    // Eğer eşleşen bir sınıf varsa öğrenci eklenir.
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->next = NULL;
    printf("Ogrenci adini girin: ");
    scanf("%s", newStudent->name);
    printf("Ogrenci yasini girin: ");
    scanf("%d", &newStudent->age);

    // Eğer sınıfın öğrenci listesi boş ise yeni öğrenci ilk öğrenci olarak atanır.
    if (currentClass->studentList == NULL) {
        currentClass->studentList = newStudent;
    } else {
        // Eğer sınıfın öğrenci listesi boş değilse son öğrenciye yeni öğrenci eklenir.
        Student* currentStudent = currentClass->studentList;
        while (currentStudent->next != NULL) {
            currentStudent = currentStudent->next;
        }
        currentStudent->next = newStudent;
    }
    printf("Ogrenci eklendi.\n");
}

void listClasses(Class* classList) {
    // Sınıfları listeleme işlemi burada gerçekleştirilir.

    // Eğer sınıf listesi boş ise hata mesajı verilir.
    if (classList == NULL) {
        printf("Listelenecek sinif bulunamadi.\n");
        return;
    }

    // Sınıflar listelenir.
    Class* currentClass = classList;
    while (currentClass != NULL) {
        printf("%s\n", currentClass->className);
        currentClass = currentClass->next;
    }

    return;
}

void listStudents(Class* classList) {
    // Öğrencileri listeleme işlemi burada gerçekleştirilir.

    // Hangi sınıfın öğrencileri listelenecek kullanıcıdan alınır.
    char className[30];
    printf("Sinif adini girin, ana menüye dönmek için menu yazın: ");
    scanf("%s", className);
    if (strcmp(className, "menu") == 0) {
        return;
    }

    // classList linked listinde className ile eşleşen bir sınıf var mı kontrol edilir.
    Class* currentClass = classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        currentClass = currentClass->next;
    }

    // Eğer eşleşen bir sınıf yoksa hata mesajı verilir.
    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    // Eğer eşleşen bir sınıf varsa öğrenciler listelenir.
    Student* currentStudent = currentClass->studentList;
    while (currentStudent != NULL) {
        printf("%s %d\n", currentStudent->name, currentStudent->age);
        currentStudent = currentStudent->next;
    }

}

void removeClass(Class** classList) {
    // Sınıf silme işlemi burada gerçekleştirilir.

    // Eğer hiç sinif yok ise hata mesajı verilir.
    if (*classList == NULL) {
        printf("Silinecek sinif bulunamadi.\n");
        return;
    }

    printf("Silmek istediğiniz sinifin adini girin, ana menüye dönmek için menu yazın: ");
    char className[30];
    scanf("%s", className);
    if (strcmp(className, "menu") == 0) {
        return;
    }

    // classList linked listinde className ile eşleşen bir sınıf var mı kontrol edilir.
    Class* previousClass = NULL;
    Class* currentClass = *classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        previousClass = currentClass;
        currentClass = currentClass->next;
    }

    // Eğer eşleşen bir sınıf yoksa hata mesajı verilir.
    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    // Eğer eşleşen bir sınıf varsa sınıf silinir.
    if(previousClass == NULL) {
        *classList = currentClass->next;
    } else {
        previousClass->next = currentClass->next;
    }


}

void removeStudent(Class* classList) {
    // Öğrenci silme işlemi burada gerçekleştirilir.

    // Hangi sınıfın öğrencileri listelenecek kullanıcıdan alınır.
    char className[30];
    printf("Öğrencinin bulunduğu Sinifin adini girin, ana menüye dönmek için menu yazın: ");
    scanf("%s", className);
    if (strcmp(className, "menu") == 0) {
        return;
    }

    // classList linked listinde className ile eşleşen bir sınıf var mı kontrol edilir.
    Class* currentClass = classList;
    while (currentClass != NULL) {
        if (strcmp(currentClass->className, className) == 0) {
            break;
        }
        currentClass = currentClass->next;
    }

    // Eğer eşleşen bir sınıf yoksa hata mesajı verilir.
    if (currentClass == NULL) {
        printf("Boyle bir sinif bulunamadi.\n");
        return;
    }

    // Eğer eşleşen bir sınıf varsa öğrenciler listelenir.
    printf("Silmek istediğiniz öğrencinin adini girin, ana menüye dönmek için menu yazın : ");
    char studentName[50];
    scanf("%s", studentName);
    if (strcmp(studentName, "menu") == 0) {
        return;
    }

    // Eğer sınıfın öğrenci listesi boş ise hata mesajı verilir.
    if (currentClass->studentList == NULL) {
        printf("Silinecek öğrenci bulunamadi.\n");
        return;
    }

    // Eğer sınıfın öğrenci listesi boş değilse öğrenci silinir.
    Student* previousStudent = NULL;
    Student* currentStudent = currentClass->studentList;
    while (currentStudent != NULL) {
        if (strcmp(currentStudent->name, studentName) == 0) {
            break;
        }
        previousStudent = currentStudent;
        currentStudent = currentStudent->next;
    }

    // Eğer eşleşen bir öğrenci yoksa hata mesajı verilir.
    if (currentStudent == NULL) {
        printf("Boyle bir ogrenci bulunamadi.\n");
        return;
    }

    // Eğer eşleşen bir öğrenci varsa öğrenci silinir.
    if(previousStudent == NULL) {
        currentClass->studentList = currentStudent->next;
    } else {
        previousStudent->next = currentStudent->next;
    }
}

void addToy(Class* classList) {
    // Oyuncak ekleme işlemi burada gerçekleştirilir.
}

void removeToy(Class* classList) {
    // Oyuncak çıkarma işlemi burada gerçekleştirilir.
}

void listToys(Class* classList) {
    // Oyuncakları listeleme işlemi burada gerçekleştirilir.
}
