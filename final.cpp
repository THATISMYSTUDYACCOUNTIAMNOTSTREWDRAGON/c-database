#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>

// ! hello

const int stringLength = 255;
const int WIDTH = 14;

using namespace std;

char *getFileName(const char *defaultFileName) {
  char *fileName = (char *)malloc(stringLength * sizeof(char));

  cout << "Введить имя файла(по умолчанию " << defaultFileName << ")"
       << " : ";
  cin.ignore();
  cin.getline(fileName, stringLength);

  if (strcmp(fileName, "") == 0) {
    strcpy(fileName, defaultFileName);
  }

  return fileName;
}

bool isYes() {
  char yes;
  cout << "Y/n: ";
  cin >> yes;
  if (yes == 'y') {
    return true;
  }
  return false;
}

void clear() { system("clear"); }

void cleanOrNot() {
  char y;
  cout << "Clearn output(Y/n): ";
  cin >> y;
  if (y == 'y') {
    clear();
  }
}

char *itoa(int value, char *result, int base) {
  // check that the base if valid
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result, *ptr1 = result, tmp_char;
  int tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
             "uvwxyz"[35 + (tmp_value - value * base)];
  } while (value);

  // Apply negative sign
  if (tmp_value < 0)
    *ptr++ = '-';
  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

enum Fuild {
  ID,
  Sername,
  Name,
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

enum FuildType { Id, INT, STRING, DATE, COURSE, MARK, NONE };

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
  case Fuild::ID:
    fuildInfo = {"ID", "ID : ", FuildType::Id};
    break;
  case Sername:
    fuildInfo = {"Sernam", "Фамилия: ", FuildType::STRING};
    break;
  case Name:
    fuildInfo = {"Name", "Имя: ", FuildType::STRING};
    break;
  case Patronical:
    fuildInfo = {"Patronical", "Отчество: ", FuildType::STRING};
    break;
  case Enterance_Date:
    fuildInfo = {"Enterance date", "Дата поступления", FuildType::DATE};
    break;
  case Course:
    fuildInfo = {"Course", "Курс: ", FuildType::COURSE};
    break;
  case Subject1:
    fuildInfo = {"Sub 1", "Предмет 1: ", FuildType::STRING};
    break;
  case Mark1:
    fuildInfo = {"Mark 1", "Оценка по предмету 1: ", FuildType::MARK};
    break;
  case Subject2:
    fuildInfo = {"Sub 2", "Предмет 2: ", FuildType::STRING};
    break;
  case Mark2:
    fuildInfo = {"Mark 2", "Оценка 2: ", FuildType::MARK};
    break;
  case Subject3:
    fuildInfo = {"Sub 3", "Пердмет 3: ", FuildType::STRING};
    break;
  case Mark3:
    fuildInfo = {"Mark 3", "Оценка 3: ", FuildType::MARK};
    break;
  default:
    fuildInfo = {"[Unknown]", FuildType::NONE};
    break;
  }
  return fuildInfo;
}

bool isDate(int year, int month, int day) {
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

bool isNormalInput() {
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

bool isInt(char *string) {
  int j = 0;
  while (string[j]) {
    if (!(47 < string[j] && string[j] < 58)) {
      return false;
    }
    j++;
  }
  return true;
}

void fillStudentFuild(int &fuild) {
  cin >> fuild;
  if (!isNormalInput()) {
    cout << " Введенное заначение должно быть "
            "числом: ";
    fillStudentFuild(fuild);
  }
}

void fillStudentFuild(char (&fuild)[stringLength]) {
  cin.getline(fuild, stringLength);
  if (!isNormalInput()) {
    cout << " Введенное заначение должно быть "
            "строкой: ";
    fillStudentFuild(fuild);
  }
}

void fillStudentFuild(Date &date) {
  cout << '\n';
  cout << "День : ";
  fillStudentFuild(date.day);
  cout << "Месяц : ";
  fillStudentFuild(date.month);
  cout << "Год : ";
  fillStudentFuild(date.year);

  if (!isDate(date.year, date.month, date.day)) {
    cout << " Некорректный формат даты" << endl;
    fillStudentFuild(date);
  }
}

bool isMark(Mark mark) {
  if (!(1 <= mark.mark && mark.mark <= 5)) {
    return false;
  }
  return true;
}

void fillStudentFuild(Mark &mark) {
  fillStudentFuild(mark.mark);
  if (!isMark(mark)) {
    cout << " Некорректный ввод оценки" << endl;
    fillStudentFuild(mark);
  }
}

bool isCurse(struct Course course) {
  if (!(1 <= course.course && course.course <= 6)) {
    return false;
  }
  return true;
}

void fillStudentFuild(struct Course &course) {
  fillStudentFuild(course.course);

  if (!isCurse(course)) {
    cout << " Некорректный ввод курса" << endl;
    fillStudentFuild(course);
  }
}

void fillStudentWithKeybord(Storage &storage, Student &student) {
  KeyValue keyvalue;
  keyvalue.key = Fuild::ID;
  FuildInfo fuildInfo = getFuildInfo(Fuild::ID);

  int maxID = 0;
  for (int i = 0; i < storage.storageSize; i++) {
    Student tempStudent = storage.storage[i];
    if (atoi(tempStudent.storage[Fuild::ID].value) > maxID) {
      maxID = atoi(tempStudent.storage[Fuild::ID].value);
    }
  }


  maxID += 1;

  itoa(maxID, keyvalue.value, 10);
  appendStudentFuild(student, keyvalue);

  for (int i = Fuild::Sername; i <= Fuild::Mark3; i++) {
    KeyValue keyvalue;
    keyvalue.key = (Fuild)i;
    FuildInfo fuildInfo = getFuildInfo((Fuild)i);

    if (Fuild::Sername == (Fuild)i || Fuild::Subject1 == (Fuild)i ||
        Fuild::Subject2 == (Fuild)i || Fuild::Subject3 == (Fuild)i) {
      cin.ignore();
    }

    cout << fuildInfo.description;

    char dateString[stringLength] = "";
    char stringFuild[stringLength] = "";

    switch (fuildInfo.fuildType) {
    case (int)FuildType::DATE:
      Date date;
      char day[stringLength];
      char month[stringLength];
      char year[stringLength];

      fillStudentFuild(date);

      itoa(date.day, day, 10);
      itoa(date.month, month, 10);
      itoa(date.year, year, 10);

      strcat(dateString, day);
      strcat(dateString, ".");
      strcat(dateString, month);
      strcat(dateString, ".");
      strcat(dateString, year);

      strcpy(keyvalue.value, dateString);
      break;
    case (int)FuildType::MARK:
      Mark mark;
      fillStudentFuild(mark);
      itoa(mark.mark, keyvalue.value, 10);
      break;
    case (int)FuildType::COURSE:
      struct Course course;
      fillStudentFuild(course);
      itoa(course.course, keyvalue.value, 10);
      break;
    case (int)FuildType::STRING:
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

Student initStudent() {
  Student student;

  student.storageSize = 0;
  student.storage = new KeyValue[student.storageSize];

  return student;
}

Student createNewStudentFromKeyboard(Storage &storage) {
  Student student = initStudent();

  fillStudentWithKeybord(storage, student);

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

Storage initStorage() {
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
                        function<void(Storage &)> callback) {
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

void printDevider() {
  for (int i = 0; i < 13 * WIDTH - 1; i++) {
    cout << "-";
  }
  cout << '\n';
}

void printHeader() {
  printDevider();
  cout << "|";
  for (int i = Fuild::ID; i <= Fuild::Mark3; i++) {
    FuildInfo fuildInfo = getFuildInfo((Fuild)i);
    cout << setw(WIDTH) << fuildInfo.name << "|";
  }
  cout << '\n';
  printDevider();
}

void printStudent(Student student) {
  cout << "|";
  for (int j = 0; j <= Fuild::Mark3; j++) {
    cout << setw(WIDTH) << student.storage[j].value << "|";
  }
  cout << '\n';
  printDevider();
}

void printStudents(Storage storage) {
  printHeader();
  for (int i = 0; i < storage.storageSize; i++) {
    printStudent(storage.storage[i]);
  }
}

void printGlobalStoreStudents(Storage storage) {
  if (storage.storageSize == 0) {
    cout << "There is no data for now" << endl;
    cleanOrNot();
    return;
  }

  printStudents(storage);
  cleanOrNot();
}

bool validateStudent(Student student) {
  for (int j = Fuild::ID; j <= Fuild::Mark3; j++) {
    bool isFuild = false;

    char *value = student.storage[j].value;

    switch (j) {
    case Fuild::ID:
      isFuild = isInt(value);
      break;
    case Fuild::Sername:
    case Fuild::Name:
    case Fuild::Patronical:
    case Fuild::Subject1:
    case Fuild::Subject2:
    case Fuild::Subject3:
      break;
    case Fuild::Course:
      struct Course course;
      course.course = atoi(value);
      isFuild = isCurse(course);
      break;
    case Fuild::Enterance_Date:
      isFuild = true;
      break;
    case Fuild::Mark1:
    case Fuild::Mark2:
    case Fuild::Mark3:
      Mark mark = {atoi(value)};
      isFuild = isMark(mark);
      break;
    }

    if (!isFuild) {
      cout << "GG vp приплыли, student не student мана" << endl;
      break;
    }
  }
  return true;
}

Storage getStudentsBySubstring(Storage &storage, char substring[],
                               Fuild fuildID) {
  Storage foundedStudents = initStorage();

  for (int i = 0; i < storage.storageSize; i++) {
    Student student = storage.storage[i];
    KeyValue keyvalue = student.storage[fuildID];
    if (strstr(keyvalue.value, substring) != NULL) {
      appendStudent(foundedStudents, student);
    }
  }

  return foundedStudents;
}

void printFuilds() {
  for (int i = Fuild::ID; i <= Fuild::Mark3; i++) {
    FuildInfo fuildInfo = getFuildInfo((Fuild)i);
    cout << i << " " << fuildInfo.name << endl;
  }
}

Storage searchByFuilds(Storage &storage) {
  int fuildID = Fuild::ID;

  printFuilds();

  cout << endl;

  cout << "Input fuild id you wanna find: ";
  cin >> fuildID;

  FuildInfo fuildInfo = getFuildInfo((Fuild)fuildID);

  if (fuildInfo.fuildType == FuildType::NONE) {
    cout << "Вы ввели неправильное поле! " << endl;
    searchByFuilds(storage);
  }

  cout << "Ищем в поле " << fuildInfo.name << endl;
  char substring[stringLength] = "";

  cout << "Введите что хотели найти: ";
  cin >> substring;

  Storage foundedStudents =
      getStudentsBySubstring(storage, substring, (Fuild)fuildID);

  return foundedStudents;
}

void menuFindStudents(Storage &storage) {
  Storage foundedStudents = searchByFuilds(storage);

  if (foundedStudents.storageSize == 0) {
    cout << "А ничего не найдено!" << endl;
    return;
  }

  for (int i = 0; i < foundedStudents.storageSize; i++) {
    Student student = foundedStudents.storage[i];
    printStudent(student);
  }

  cleanOrNot();
}

void importDatabaseFromFile(Storage &storage) {
  ifstream file(getFileName("input.txt"));

  if (!file.is_open()) {
    cout << "Нет такого файла либо каталога" << endl;
    return;
  }

  char line[stringLength * 13] = "";
  char delim[] = ";";

  Storage newStorage = initStorage();

  while (file.getline(line, stringLength * 13)) {
    char *ptr = strtok(line, delim);
    Student student = initStudent();

    if (strlen(line) == 0) {
      continue;
    }

    for (int i = Fuild::ID; i <= Fuild::Mark3; i++) {
      KeyValue keyvalue;
      keyvalue.key = (Fuild)i;
      if (NULL != ptr) {
        strcpy(keyvalue.value, ptr);
        appendStudentFuild(student, keyvalue);
        ptr = strtok(NULL, delim);
      }
    }

    appendStudent(newStorage, student);
  }

  storage = newStorage;
  cout << "Успешно" << endl;
  cleanOrNot();
}

void appendStudentFromKeyboard(Storage &storage) {
  Student student = createNewStudentFromKeyboard(storage);
  cout << "Хотите вставить пользователя в конец" << endl;
  if (isYes()) {
    appendStudent(storage, student);
  } else {
    int position;
    cout << "Введите подходящую позицию(max " << storage.storageSize << " ): ";
    cin >> position;
    Storage newStorage = initStorage();
    if (0 <= position && position <= storage.storageSize) {
      for (int i = 0; i < position; i++) {
        appendStudent(newStorage, storage.storage[i]);
      }
      appendStudent(newStorage, student);
      for (int i = position; i < storage.storageSize; i++) {
        appendStudent(newStorage, storage.storage[i]);
      }
    }
    storage = newStorage;
  }

  cleanOrNot();
}

void updateSingleStudent(Student &student, Storage &storage) {
  cout << "Хотите заполнить все поля зоново?" << endl;
  if (isYes()) {
    student = createNewStudentFromKeyboard(storage);
  }
}

void updateStudent(Storage &storage) {
  Storage foundedStudents = searchByFuilds(storage);

  if (foundedStudents.storageSize == 0) {
    cout << "Ничего не найдено!" <<endl;
    cleanOrNot();
    return;
  }

  for (int i = 0; i < foundedStudents.storageSize; i++) {
    Student student = foundedStudents.storage[i];
    cout << "╭─Изменить: " << i << endl;
    printDevider();
    printStudent(student);
  }

  cout << "Какого пользователя вы хотите изменить?: ";
  int indexToUpdate;
  fillStudentFuild(indexToUpdate);

  cout << "Хотите изменить пользователя полностью?" << endl;

  bool updateFull = isYes();

  for (int i = 0; i < storage.storageSize; i++) {
    Student globalStudent = storage.storage[i];
    for (int j = 0; j < foundedStudents.storageSize; j++) {
      Student localStudent = foundedStudents.storage[j];
      if (globalStudent.storage[Fuild::ID].value == localStudent.storage[Fuild::ID].value && j == indexToUpdate) {
        if (updateFull) {
          updateSingleStudent(localStudent, storage);
        } else {
          int fuildID;
          cout << "Введите поле которое хотите изменить: ";
          fillStudentFuild(fuildID);
          cout << "Введить новое значение поля: ";
          cin.ignore();
          fillStudentFuild(localStudent.storage[fuildID].value);
        }
      }
      storage.storage[i] = localStudent;
    }
  }

  cleanOrNot();
}

void clearFile(char fileName[stringLength]) {
  ofstream file(fileName);
  file << "";
  file.close();
}

void doClearFile(char fileName[stringLength]) {
  cout << "Do you wanna clear the file? " << endl;
  if (isYes()) {
    clearFile(fileName);
  }
}

void exportDatabaseToFile(Storage &storage) {
  // cout << "Input file name: "; cin >> fileName;
  for (int i = 0; i < storage.storageSize; i++) {
    ofstream file(getFileName("output.txt"), ios::app);

    if (!file.is_open()) {
      cout << "File can not be created" << endl;
      return;
    }

    Student student = storage.storage[i];

    for (int j = 0; j < student.storageSize; j++) {
      KeyValue keyvalue = student.storage[j];
      if (!(j == 0 || j == student.storageSize - 1)) {
        file << ";";
      }
      file << keyvalue.value;
    }

    file << "\n";

    file.close();
  }

  cleanOrNot();
}

void deleteElementFromStorage(Storage &storage, int index) {
  int newStorageSize = storage.storageSize - 1;

  Student *newStorage = new Student[newStorageSize];

  int newIndex = 0;
  for (int i = 0; i < storage.storageSize; i++) {
    if (i == index) {
      continue;
    }
    newStorage[newIndex] = storage.storage[i];
    newIndex++;
  }

  delete[] storage.storage;

  storage.storage = newStorage;

  newStorage = NULL;

  storage.storageSize = newStorageSize;
}

void exportToBinaryFile(Storage &storage) {
  ofstream file(getFileName("output.bin"), ios::out | ios::binary);
  if (!file.is_open()) {
    cout << "Ошибки при открытии файла" << endl;
    return;
  }
  // записываем сколько студентов
  file.write((char *)&storage.storageSize, sizeof(storage.storageSize));
  for (int i = 0; i < storage.storageSize; i++) {
    Student student = storage.storage[i];
    // записываем сколько полей у студентов
    file.write((char *)&student.storageSize, sizeof(student.storageSize));
    for (int j = 0; j < student.storageSize; j++) {
      file.write((char *)&student.storage[j], sizeof(KeyValue));
    }
  }
  file.close();
  if (!file.good()) {
    cout << "Error occurred at writing time!" << endl;
    return;
  }
  cout << "Успешно" << endl;
  cleanOrNot();
}

void importFromBinaryFile(Storage &storage) {

  Storage newStorage = initStorage();

  ifstream file(getFileName("input.bin"), ios::out | ios::binary);

  if (!file.is_open()) {
    cout << "Нет такого файла или каталога" << endl;
    return;
  }

  file.read((char *)&newStorage.storageSize, sizeof(newStorage.storageSize));
  newStorage.storage = new Student[newStorage.storageSize];
  for (int i = 0; i < newStorage.storageSize; i++) {
    Student student;
    file.read((char *)&student.storageSize, sizeof(student.storageSize));
    student.storage = new KeyValue[student.storageSize];
    for (int j = 0; j < student.storageSize; j++) {
      file.read((char *)&student.storage[j], sizeof(KeyValue));
      // cout << student.storage[j].value << endl;
    }
    newStorage.storage[i] = student;
  }

  storage = newStorage;

  cout << "Успешно" << endl;
  cleanOrNot();
}

void deleteStudent(Storage &storage) {
  Storage foundedStudents = searchByFuilds(storage);

  if (foundedStudents.storageSize == 0) {
    cout << "Ничего не найдено" << endl;
    cleanOrNot();
    return;
  }

  for (int i = 0; i < foundedStudents.storageSize; i++) {
    Student student = foundedStudents.storage[i];
    cout << "╭─Удалить: " << i << endl;
    printDevider();
    printStudent(student);
  }

  cout << "Хотите удалить все результаты?" << endl;

  if (isYes()) {
    for (int i = 0; i < storage.storageSize; i++) {
      Student globalStudent = storage.storage[i];
      for (int j = 0; j < foundedStudents.storageSize; j++) {
        Student localStudent = foundedStudents.storage[j];
        if (globalStudent.storage[Fuild::ID].value ==
            localStudent.storage[Fuild::ID].value) {
          deleteElementFromStorage(storage, i);
        }
      }
    }
    cleanOrNot();
    return;
  }

  char studentsToDelete[stringLength] = "";
  cout << "Укажите каких пользователей вы хотите удалить(1,2,3,4): ";
  cin >> studentsToDelete;

  char token = ',';
  char *ptr = strtok(studentsToDelete, &token);

  while (ptr) {
    if (isInt(ptr)) {
      for (int i = 0; i < storage.storageSize; i++) {
        Student globalStudent = storage.storage[i];
        for (int j = 0; j < foundedStudents.storageSize; j++) {
          Student localStudent = foundedStudents.storage[j];
          if (globalStudent.storage[Fuild::ID].value ==
                  localStudent.storage[Fuild::ID].value &&
              j == atoi(ptr)) {
            deleteElementFromStorage(storage, i);
          }
        }
      }
    }
    ptr = strtok(nullptr, &token);
  }

  cleanOrNot();
}

Storage getChosenStudents(Storage storage) {
  Storage chosenStudents = initStorage();

  for (int i = 0; i < storage.storageSize; i++) {
    Student student = storage.storage[i];

    if ((strcmp(student.storage[Fuild::Mark1].value, "4") == 0 &&
         strcmp(student.storage[Fuild::Mark2].value, "4") != 0 &&
         strcmp(student.storage[Fuild::Mark3].value, "4") != 0) ||
        (strcmp(student.storage[Fuild::Mark1].value, "4") != 0 &&
         strcmp(student.storage[Fuild::Mark2].value, "4") == 0 &&
         strcmp(student.storage[Fuild::Mark3].value, "4") != 0) ||
        (strcmp(student.storage[Fuild::Mark1].value, "4") != 0 &&
         strcmp(student.storage[Fuild::Mark2].value, "4") != 0 &&
         strcmp(student.storage[Fuild::Mark3].value, "4") == 0)) {
      appendStudent(chosenStudents, student);
    }
  }

  return chosenStudents;
}

void printChosenStudents(Storage storage) {
  printStudents(getChosenStudents(storage));
  cleanOrNot();
}

void sortStudents(Storage &storage) {

  printFuilds();

  cout << endl;

  int fuildID;
  cout << "Input fuild id you wanna sort by: ";
  cin >> fuildID;

  FuildInfo fuildInfo = getFuildInfo((Fuild)fuildID);

  if (fuildInfo.fuildType == FuildType::NONE) {
    cout << "Вы ввели неправильное поле! " << endl;
  }

  cout << "Сортируем по полю: " << fuildInfo.name << endl;
  char substring[stringLength] = "";

  Student temp;

  for (int i = 0; i < storage.storageSize - 1; i++) {
    for (int j = 0; j < storage.storageSize - i - 1; j++) {
      KeyValue currentKeyvalue = storage.storage[j].storage[fuildID];
      KeyValue nextKeyvalue = storage.storage[j + 1].storage[fuildID];

      cout << (char)currentKeyvalue.value[0] << " "
           << (char)nextKeyvalue.value[0] << endl;
      if ((char)currentKeyvalue.value[0] > (char)nextKeyvalue.value[0]) {
        cout << currentKeyvalue.value[0] << " " << nextKeyvalue.value[0]
             << endl;
        temp = storage.storage[j];
        storage.storage[j] = storage.storage[j + 1];
        storage.storage[j + 1] = temp;
      }
    }
  }

  cout << "Успешно" << endl;

  cleanOrNot();
}

void syncAll(Storage &storage) {
  exportDatabaseToFile(storage);
  exportToBinaryFile(storage);
}

void convertTextToBinary(Storage &storage) {
  Storage newStorage = initStorage();
  importDatabaseFromFile(newStorage);
  exportToBinaryFile(newStorage);
}

void quit(Storage &storage) {
  if (storage.storageSize != 0) {
    cout << "Хотите сохранить текущее состояние бд?" << endl;
    if(isYes()) {
      syncAll(storage);  
    } 
  }
  exit(0);
}

void fillMenu(Menu &menu) {
  appendMenuItem(menu, createMenuItem("Показать всех студентов", menu,
                                      printGlobalStoreStudents));
  appendMenuItem(menu, createMenuItem("Добавить студента", menu,
                                      appendStudentFromKeyboard));
  appendMenuItem(menu,
                 createMenuItem("Изменить студента", menu, updateStudent));
  appendMenuItem(menu, createMenuItem("Удалить студента", menu, deleteStudent));
  appendMenuItem(menu,
                 createMenuItem("Поиск по полям", menu, menuFindStudents));
  appendMenuItem(menu, createMenuItem("Сортировать", menu, sortStudents));
  appendMenuItem(
      menu, createMenuItem("Экспортировать базу данных в текстовый документ",
                           menu, exportDatabaseToFile));
  appendMenuItem(
      menu, createMenuItem("Импортировать базу данных из текстового документа",
                           menu, importDatabaseFromFile));
  appendMenuItem(menu, createMenuItem("Экспортировать базу данных в бинарник",
                                      menu, exportToBinaryFile));
  appendMenuItem(menu, createMenuItem("Импортировать базу данных из бинарника",
                                      menu, importFromBinaryFile));
  appendMenuItem(menu, createMenuItem("Показать избранных студентов", menu,
                                      printChosenStudents));
  appendMenuItem(menu, createMenuItem("Конвертировать текcтовый файл в бинарник", menu, convertTextToBinary));
  appendMenuItem(menu, createMenuItem("Выйти", menu, quit));
}

void printMenu(Menu menu) {
  for (int i = 0; i < menu.storageSize; i++) {
    cout << menu.storage[i].id << " " << menu.storage[i].name << endl;
  }
}

void userEventLisenter(Menu menu, Storage &storage) {

  printMenu(menu);
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

int main() {
  Storage storage = initStorage();
  Menu menu = createMenu();
  fillMenu(menu);
  // importDatabaseFromFile(storage);
  userEventLisenter(menu, storage);

  return 0;
}
