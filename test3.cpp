#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>

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

enum FuildType {
  INT,
  STRING
};

struct MenuItem {
  const int id;
  const char *name;
  const function<void()> func;
};

bool isInt(char *string) {
  for (int i = 0; i < strlen(string); i++) {
    if(!(47 < string[i] && string[i] < 58)) return false;
  }
  return true;
}

bool checkType(char *string, FuildType type) {
  bool isCorect = true;
  switch (type) {
    case FuildType::INT:
      isCorect = isInt(string);
      break;
  }
  return isCorect;
}

FuildType defineFuildType(char *string) {
  if (strstr(string, "(int)") != NULL) {
    return FuildType::INT;
  }
  return FuildType::STRING;
}


inline const char *getFuildName(Fuild v) {
  switch (v) {
  case ID:
    return "ID(int)";
  case Sername:
    return "Sername(string)";
  case Name:
    return "Name(string)";
  case Patronical:
    return "Patronical(string)";
  case Enterance_Date:
    return "Enterance_Date(string)";
  case Course:
    return "Course(int)";
  case Subject1:
    return "Subject1(string)";
  case Mark1:
    return "Mark1(int)";
  case Subject2:
    return "Subject2(string)";
  case Mark2:
    return "Mark2(int)";
  case Subject3:
    return "Subject3(string)";
  case Mark3:
    return "Mark3(int)";

  default:
    return "[Unknown]";
  }
}

struct KeyInt {
  Fuild key;
  int value;
};

struct KeyString {
  Fuild key;
  char value[100];
};

struct Student {
  int storageSize;
  KeyString *storage;
};

struct Storage {
  int storageSize;
  Student *storage;
};

void appendStudentFuild(Student &student, KeyString keyvalue) {
  int newStorageSize = student.storageSize + 1;

  KeyString *newStorage = new KeyString[newStorageSize];

  for (int i = 0; i < student.storageSize; i++) {
    newStorage[i] = student.storage[i];
  }

  newStorage[student.storageSize] = keyvalue;

  delete[] student.storage;

  student.storage = newStorage;

  newStorage = NULL;

  student.storageSize = newStorageSize;
}

void fillStudentWithFile(Student &student) {

}

void fillStudentWithKeybord(Student &student) {
  for (int i = Fuild::Name; i < Fuild::Mark3; ++i) {
    KeyString keyvalue;

    keyvalue.key = (Fuild)i;
    cout << "Input " << getFuildName((Fuild)i) << ": ";
    cin >> keyvalue.value;
    appendStudentFuild(student, keyvalue);
  }
}

Student createNewStudent(function<void(Student &)> callback) {
  Student student;

  student.storageSize = 0;
  student.storage = new KeyString[student.storageSize];

  callback(student);

  return student;
}

void appendStudent(Storage &storage, Student student) {
  int newStorageSize = storage.storageSize + 1;

  Student *newStorage = new Student[newStorageSize];

  for (int i = 0; i < storage.storageSize; i++) {
    newStorage[i] = storage.storage[i];
  }

  newStorage[storage.storageSize] = student;

  delete[] student.storage;

  storage.storage = newStorage;

  newStorage = NULL;

  storage.storageSize = newStorageSize;
}

Storage createNewStorage() {
  Storage storage;

  storage.storageSize = 0;
  storage.storage = new Student[0];

  return storage;
}

Student testStudent() {
  Student student;

  student.storageSize = 0;
  student.storage = new KeyString[student.storageSize];

  cout << "Appending only" << endl;
  for (int j = 0; j < 10; j++) {
    for (int i = Fuild::Name; i <= Fuild::Mark3; i++) {
      KeyString keyvalue;

      keyvalue.key = (Fuild)i;
      char temp_str[100] = "100f";
      // char snum[5];
      //
      // sprintf(snum, "%d", i);

      FuildType type = defineFuildType((char*)getFuildName((Fuild)i));

      cout << "Name: " << getFuildName((Fuild)i) << endl;
      cout << "Type: " << type << endl;

      if (checkType(temp_str, type)) {
        cout << "Type OK" << endl;
      } else {
        cout << "Type BAD" << endl;
        while (!checkType(temp_str, type)) {
          cout << temp_str << endl;
          strcpy(temp_str, "100");
        }
      }

      strcpy(keyvalue.value, temp_str);

      cout << "Checking key value..." << endl;
      cout << "Key: " << keyvalue.key << endl;
      cout << "Value: " << keyvalue.value << endl;

      appendStudentFuild(student, keyvalue);
    }
  }

  cout << "Print values of student" << endl;
  for (int i = 0; i < student.storageSize; i++) {
    cout << "Size: "<< student.storageSize << endl;
    cout << "Key: "<< student.storage[i].key << endl;
    cout << "Value: "<< student.storage[i].value << endl;
  }

  cout << "Student fuild test OK" << endl;

  return student;
}

void testGlobalStorage() {
  Storage storage;

  storage.storageSize = 0;
  storage.storage = new Student[storage.storageSize];

  for (int i = 0; i<100; i++) {
    Student student = testStudent();
    cout << "Size: " << student.storageSize << endl;
    cout << "Value: " << student.storage[i].value << endl;
    appendStudent(storage, student);
  }

  cout << "T: Storage size: " << storage.storageSize << endl;
  for (int i = 0; i < storage.storageSize; i++) {
    for (int j = 0; j< storage.storage[i].storageSize; j++) {
      cout << "Value: " << storage.storage[i].storage[j].value << endl;
    }
  }

  cout << "Test pessed" << endl;
}

struct Menu {
  int storageSize;
  MenuItem *storage;
};


int main() {
  testStudent();
  testGlobalStorage();

  return 0;
}
