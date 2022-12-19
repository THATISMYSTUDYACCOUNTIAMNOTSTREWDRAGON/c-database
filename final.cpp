#include <cstring>
#include <stdio.h>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string.h>

const int stringLength = 255;

using namespace std;

char* itoa(int value, char* result, int base) {
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

enum Fuild {
  ID,
  Name,
  Sername,
  Patronical,
  Enterance_Date,
  Course,
  Subject1,
  Mark1,
  Subject2,
  Mark2,
  Subject3,
  Mark3,
};

enum FuildType { INT, STRING, DATE, COURSE, MARK };

struct Course {
  int course;
};

struct Mark {
  int mark;
};

struct FuildInfo {
  char name[stringLength];
  char description[stringLength];
  FuildType fuildType;
};

struct KeyValue {
  Fuild key;
  char value[stringLength];
};

struct Student {
  int storageSize;
  KeyValue *storage;
};

struct Storage {
  int storageSize;
  Student *storage;
};

struct MenuItem {
  int id;
  const char *name;

  function<void(Storage &)> globalStoreCallback;
};

struct Date {
  int day;
  int month;
  int year;
};

struct Menu {
  int storageSize;
  MenuItem *storage;
};

FuildInfo getFuildInfo(Fuild v) {
  FuildInfo fuildInfo;
  switch (v) {
    case ID:
      fuildInfo = {"ID", "ID : ", FuildType::INT};
      break;
    case Sername:
      fuildInfo = {"Фамилия", "Фамилия: ", FuildType::STRING};
      break;
    case Name:
      fuildInfo = {"Имя", "Имя: ", FuildType::STRING};
      break;
    case Patronical:
      fuildInfo = {"Отчество", "Отчество: ", FuildType::STRING};
      break;
    case Enterance_Date:
      fuildInfo = {"Дата поступления", "Дата поступления", FuildType::DATE};
      break;
    case Course:
      fuildInfo = {"Курс", "Курс: ", FuildType::COURSE};
      break;
    case Subject1:
      fuildInfo = {"Предемет 1", "Предмет 1: ", FuildType::STRING};
      break;
    case Mark1:
      fuildInfo = {"Оценка 1", "Оценка по предмету 1: ", FuildType::MARK};
      break;
    case Subject2:
      fuildInfo = {"Предмет 2", "Предмет 2: ", FuildType::STRING};
      break;
    case Mark2:
      fuildInfo = {"Оценка 2", "Оценка 2: ",  FuildType::MARK};
      break;
    case Subject3:
      fuildInfo = {"Предмет 3", "Пердмет 3: ", FuildType::STRING};
      break;
    case Mark3:
      fuildInfo = {"Оценка 3", "Оценка 3: ", FuildType::MARK};
      break;
    default:
      fuildInfo = {"[Unknown]", FuildType::STRING};
      break;
  }
  return fuildInfo;
}

bool isValidDate(int year, int month, int day) {
  unsigned int leap;
  unsigned char mon_day[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if ((year < 1991) || (year > 2022)) {
    return false;
  }

  if ((month < 1) || (month > 12)) {
    return false;
  }

  if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
    leap = 1;
  } else {
    leap = 0;
  }

  mon_day[1] += leap;

  if ((day > mon_day[month - 1]) || (day < 1)) {
    return false;
  }

  return true;
}

void appendStudentFuild(Student &student, KeyValue keyvalue) {
  int newStorageSize = student.storageSize + 1;

  KeyValue *newStorage = new KeyValue[newStorageSize];

  for (int i = 0; i < student.storageSize; i++) {
    newStorage[i] = student.storage[i];
  }

  newStorage[student.storageSize] = keyvalue;

  delete[] student.storage;

  student.storage = newStorage;

  newStorage = NULL;

  student.storageSize = newStorageSize;
}

void fillStudentWithFile(Student &student) {}

bool validateFuild() {
  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      return false;
    }
    if (!cin.fail())
      return true;
  }
}

void fillStudentFuild(int &fuild) {
  cin >> fuild;
  if (!validateFuild()) {
    cout << " Введенное заначение должно быть числом: ";
    fillStudentFuild(fuild);
  }
}

void fillStudentFuild(char (&fuild)[100]) {
  cin >> fuild;
  if (!validateFuild()) {
    cout << " Введенное заначение должно быть строкой: ";
    fillStudentFuild(fuild);
  }
}

void fillStudentFuild(Date &date) {
  cout << endl;
  cout << "День : "; fillStudentFuild(date.day);
  cout << "Месяц : "; fillStudentFuild(date.month);
  cout << "Год : "; fillStudentFuild(date.year);

  if (!isValidDate(date.year, date.month, date.day)) {
    cout << " Некорректный формат даты" << endl;
    fillStudentFuild(date);
  }
}

void fillStudentFuild(Mark &mark) {
  fillStudentFuild(mark.mark);
  if (!(1 <= mark.mark  && mark.mark <= 5)) {
    cout << " Некорректный ввод оценки" << endl;
    fillStudentFuild(mark);
  }
}

void fillStudentFuild(struct Course &course) {
  fillStudentFuild(course.course);

  if (!(1 <= course.course  && course.course <= 6)) {
    cout << " Некорректный ввод курса" << endl;
    fillStudentFuild(course);
  }
}



void fillStudentWithKeybord(Student &student) {
  for (int i = Fuild::Name; i <= Fuild::Mark3; ++i) {
    KeyValue keyvalue;
    keyvalue.key = (Fuild)i;
    FuildInfo fuildInfo = getFuildInfo((Fuild)i);

    cout << fuildInfo.description;

    char str[stringLength] = "";

    switch (fuildInfo.fuildType) {
      case (int)FuildType::DATE:
        Date date;
        fillStudentFuild(date);
        strcpy(keyvalue.value, "fuckkk");
        break;
      case (int)FuildType::MARK:
        Mark mark;
        fillStudentFuild(mark);
        itoa(mark.mark, keyvalue.value, 10);
        break;
      case (int)FuildType::COURSE:
        struct Course course;
        fillStudentFuild(course);
        cout << course.course << endl;
        itoa(course.course, keyvalue.value, 10);
        break;
      case (int)FuildType::STRING:
        char stringFuild[100];
        fillStudentFuild(stringFuild);
        strcpy(keyvalue.value, stringFuild);
        break;
      case (int)FuildType::INT:
        int intValue;
        fillStudentFuild(intValue);
        itoa(intValue, keyvalue.value, 10);
        break;
      default:
        cout << "Unknown type on student addition";
        break;
    }

    appendStudentFuild(student, keyvalue);
  }
}

Student createNewStudentFromKeyboard() {
  Student student;

  student.storageSize = 0;
  student.storage = new KeyValue[student.storageSize];

  fillStudentWithKeybord(student);

  return student;
}

void appendStudent(Storage &storage, Student student) {
  int newStorageSize = storage.storageSize + 1;

  Student *newStorage = new Student[newStorageSize];

  for (int i = 0; i < storage.storageSize; i++) {
    newStorage[i] = storage.storage[i];
  }

  newStorage[storage.storageSize] = student;

  delete[] storage.storage;

  storage.storage = newStorage;

  newStorage = NULL;

  storage.storageSize = newStorageSize;
}

Storage createNewStorage() {
  Storage storage;

  storage.storageSize = 0;
  storage.storage = new Student[storage.storageSize];

  return storage;
}

void fillMenuItemsWithNonePolimorfdata(const char *name, MenuItem &menuItem,
    Menu menu) {
  menuItem.id = menu.storageSize;
  menuItem.name = name;
}

MenuItem createMenuItem(const char *name, Menu menu, function<void(Storage &)> callback) {
  MenuItem menuItem;

  fillMenuItemsWithNonePolimorfdata(name, menuItem, menu);

  menuItem.globalStoreCallback = callback;

  return menuItem;
}

Menu createMenu() {
  Menu menu;

  menu.storageSize = 0;
  menu.storage = new MenuItem[menu.storageSize];

  return menu;
}

void appendMenuItem(Menu &menu, MenuItem menuItem) {
  int newStorageSize = menu.storageSize + 1;

  MenuItem *newStorage = new MenuItem[newStorageSize];

  for (int i = 0; i < menu.storageSize; i++) {
    newStorage[i] = menu.storage[i];
  }

  newStorage[menu.storageSize] = menuItem;

  delete[] menu.storage;

  menu.storage = newStorage;

  newStorage = NULL;

  menu.storageSize = newStorageSize;
}

void printAllStudents(Storage storage) {

  if (storage.storageSize == 0) {
    cout << "There is no data for now" << endl;
  }

  for (int i = 0; i < storage.storageSize; i++) {
    for (int j = Fuild::Name; j <= Fuild::Mark3; j++) {
      cout << storage.storage[i].storage[j].value << endl;
    }
  }
}

void appendStudentFromKeyboard(Storage &storage) {
  Student student = createNewStudentFromKeyboard();
  appendStudent(storage, student);
}

void fillMenu(Menu &menu) {
  appendMenuItem(menu, createMenuItem("Print all students", menu, printAllStudents));
  appendMenuItem(menu, createMenuItem("Append new student", menu, appendStudentFromKeyboard));
  // appendMenuItem(menu, createMenuItem("Update student", menu, updateStudent));
  // appendMenuItem(menu, createMenuItem("Delete student", menu,
  // printAllStudents)); appendMenuItem(menu, createMenuItem("Load students from
  // file", menu, printAllStudents)); appendMenuItem(menu,
  // createMenuItem("Upload students to file", menu, printAllStudents));
}

void printMenu(Menu menu) {
  for (int i = 0; i < menu.storageSize; i++) {
    cout << menu.storage[i].id << " " << menu.storage[i].name << endl;
  }
}

void userEventLisenter(Menu menu, Storage &storage) {

  int command;
  cout << "Please input command: ";
  cin >> command;

  while (true) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "You have entered wrong input" << endl;
      userEventLisenter(menu, storage);
    }
    if (!cin.fail())
      break;
  }

  for (int i = 0; i < menu.storageSize; i++) {
    if (command == menu.storage[i].id) {
      menu.storage[i].globalStoreCallback(storage);
    }
  }

  userEventLisenter(menu, storage);
}

// Student testStudent() {
//   Student student;
//
//   student.storageSize = 0;
//   student.storage = new KeyValue[student.storageSize];
//
//   // cout << "Appending only" << endl;
//   for (int j = 0; j < 1; j++) {
//     for (int i = Fuild::Name; i <= Fuild::Mark3; i++) {
//       KeyValue keyvalue;
//
//       cout << "Transition: " << (Fuild(i)) << endl;
//       keyvalue.key = (Fuild)i;
//       // char snum[5];
//       //
//       // sprintf(snum, "%d", i);
//       //
//       // FuildType type = defineFuildType((char*)getFuildName((Fuild)i));
//       //
//       // cout << "Name: " << getFuildName((Fuild)i) << endl;
//       // cout << "Type: " << type << endl;
//       //
//       // if (checkType(temp_str, type)) {
//       //   cout << "Type OK" << endl;
//       // } else {
//       //   cout << "Type BAD" << endl;
//       //   while (!checkType(temp_str, type)) {
//       //     cout << temp_str << endl;
//       //     strcpy(temp_str, "100");
//       //   }
//       // }
//
//       strcpy(keyvalue.value, "1000f");
//
//       cout << "Checking key value..." << endl;
//       cout << "Key: " << keyvalue.key << endl;
//       cout << "Value: " << keyvalue.value << endl;
//
//       appendStudentFuild(student, keyvalue);
//     }
//   }
//
//   // cout << "Print values of student" << endl;
//   for (int i = 0; i < student.storageSize; i++) {
//     cout << "Size: " << student.storageSize << endl;
//     cout << "Key: " << student.storage[i].key << endl;
//     cout << "Name: " << getFuildInfo(student.storage[i].key).name << endl;
//     cout << "Value: " << student.storage[i].value << endl;
//   }
//
//   cout << "Student fuild test OK" << endl;
//
//   return student;
// }
//
// void testGlobalStorage() {
//   Storage storage;
//
//   storage.storageSize = 0;
//   storage.storage = new Student[storage.storageSize];
//
//   for (int i = 0; i < 10; i++) {
//     Student student = testStudent();
//     appendStudent(storage, student);
//   }
//
//   cout << "T: Storage size: " << storage.storageSize << endl;
//   for (int i = 0; i < storage.storageSize; i++) {
//     for (int j = 0; j < storage.storage[i].storageSize; j++) {
//       cout << "Key: " << storage.storage[i].storage[j].key << " " << getFuildInfo(storage.storage[i].storage[i].key).name << " : " << storage.storage[i].storage[j].value << endl;
//     }
//     cout << "================" << endl;
//   }
//
//   cout << "Test passed" << endl;
// }


int main() {
  Storage storage = createNewStorage();
  Menu menu = createMenu();
  fillMenu(menu);
  printMenu(menu);
  userEventLisenter(menu, storage);

  return 0;
}
