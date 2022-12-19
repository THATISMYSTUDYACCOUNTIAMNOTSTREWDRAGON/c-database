#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string.h>

const int stringLength = 255;

using namespace std;

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

  function<Storage(Storage &)> globalStoreCallback;

  function<Student(function<Student(Student &)>)> studentStoreCallback;
  // function<Student(function<Student(Student&)>)> studentsStoreCallback;
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

void fillStudentFuild(Date date) {
  cout << endl;
  cout << "День : "; fillStudentFuild(date.day);
  cout << "Месяц : "; fillStudentFuild(date.month);
  cout << "Год : "; fillStudentFuild(date.year);

  if (!isValidDate(date.year, date.month, date.day)) {
    cout << " Некорректный формат даты" << endl;
    fillStudentFuild(date);
  }
}

void fillStudentFuild(Mark mark) {
  fillStudentFuild(mark.mark);

  if (!(1 <= mark.mark  && mark.mark <= 5)) {
    cout << " Некорректный ввод оценки" << endl;
    fillStudentFuild(mark);
  }
}

void fillStudentFuild(struct Course course) {
  fillStudentFuild(course.course);

  if (!(1 <= course.course  && course.course <= 6)) {
    cout << " Некорректный ввод курса" << endl;
    fillStudentFuild(course);
  }
}


Student fillStudentWithKeybord(Student student) {
  Student newStudent = student;

  for (int i = Fuild::Name; i <= Fuild::Mark3; ++i) {
    KeyValue keyvalue;
    keyvalue.key = (Fuild)i;
    FuildInfo fuildInfo = getFuildInfo((Fuild)i);

    cout << fuildInfo.description;

    switch (fuildInfo.fuildType) {
      case (int)FuildType::DATE:
        Date date;
        fillStudentFuild(date);
        break;
      case (int)FuildType::MARK:
        Mark mark;
        fillStudentFuild(mark);
        break;
      case (int)FuildType::COURSE:
        struct Course course;
        fillStudentFuild(course);
        break;
      case (int)FuildType::STRING:
        char stringFuild[100];
        fillStudentFuild(stringFuild);
        break;
      case (int)FuildType::INT:
        int intValue;
        fillStudentFuild(intValue);
        break;
      default:
        cout << "Unknown type on student addition";
        break;
    }

    appendStudentFuild(newStudent, keyvalue);
  }

  return newStudent;
}

Student createNewStudent(function<Student(Student &)> callback) {
  Student student;

  student.storageSize = 0;
  student.storage = new KeyValue[student.storageSize];

  student = callback(student);

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

MenuItem createMenuItem(const char *name, Menu menu,
    function<Storage(Storage &)> callback) {
  MenuItem menuItem;

  fillMenuItemsWithNonePolimorfdata(name, menuItem, menu);

  menuItem.globalStoreCallback = callback;

  return menuItem;
}

MenuItem
createMenuItem(const char *name, Menu menu,
    function<Student(function<Student(Student &)>)> callback) {
  MenuItem menuItem;

  fillMenuItemsWithNonePolimorfdata(name, menuItem, menu);

  menuItem.studentStoreCallback = callback;

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

Storage printAllStudents(Storage storage) {

  if (storage.storageSize == 0) {
    cout << "There is no data for now" << endl;
  }

  for (int i = 0; i < storage.storageSize; i++) {
    for (int j = Fuild::Name; j <= Fuild::Mark3; j++) {
      cout << storage.storage[i].storage[j].value << endl;
    }
  }

  return storage;
}

void fillMenu(Menu &menu) {
  appendMenuItem(menu,
      createMenuItem("Print all students", menu, printAllStudents));
  appendMenuItem(menu,
      createMenuItem("Append new student", menu, createNewStudent));
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
      if (menu.storage[i].globalStoreCallback) {
        menu.storage[i].globalStoreCallback(storage);
      }
      if (menu.storage[i].studentStoreCallback) {
        appendStudent(storage, menu.storage[i].studentStoreCallback(fillStudentWithKeybord));
      }
    }
  }

  userEventLisenter(menu, storage);
}

int main() {
  Storage storage = createNewStorage();
  Menu menu = createMenu();
  fillMenu(menu);
  printMenu(menu);
  userEventLisenter(menu, storage);

  return 0;
}
