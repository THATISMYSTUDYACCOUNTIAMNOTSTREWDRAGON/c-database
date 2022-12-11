Student testStudent() {
  Student student;

  student.storageSize = 0;
  student.storage = new KeyValue[student.storageSize];

  // cout << "Appending only" << endl;
  for (int j = 0; j < 1; j++) {
    for (int i = Fuild::Name; i <= Fuild::Mark3; i++) {
      KeyValue keyvalue;

      cout << "Transition: " << (Fuild(i)) << endl;
      keyvalue.key = (Fuild)i;
      // char snum[5];
      //
      // sprintf(snum, "%d", i);
      //
      // FuildType type = defineFuildType((char*)getFuildName((Fuild)i));
      //
      // cout << "Name: " << getFuildName((Fuild)i) << endl;
      // cout << "Type: " << type << endl;
      //
      // if (checkType(temp_str, type)) {
      //   cout << "Type OK" << endl;
      // } else {
      //   cout << "Type BAD" << endl;
      //   while (!checkType(temp_str, type)) {
      //     cout << temp_str << endl;
      //     strcpy(temp_str, "100");
      //   }
      // }

      strcpy(keyvalue.stringValue, "1000f");

      cout << "Checking key value..." << endl;
      cout << "Key: " << keyvalue.key << endl;
      cout << "Value: " << keyvalue.stringValue << endl;

      appendStudentFuild(student, keyvalue);
    }
  }

  // cout << "Print values of student" << endl;
  for (int i = 0; i < student.storageSize; i++) {
    cout << "Size: " << student.storageSize << endl;
    cout << "Key: " << student.storage[i].key << endl;
    cout << "Name: " << getFuildInfo((Fuild)student.storage[i].key) << endl;
    cout << "Value: " << student.storage[i].stringValue << endl;
  }

  cout << "Student fuild test OK" << endl;

  return student;
}

void testGlobalStorage() {
  Storage storage;

  storage.storageSize = 0;
  storage.storage = new Student[storage.storageSize];

  for (int i = 0; i < 10; i++) {
    Student student = testStudent();
    appendStudent(storage, student);
  }

  cout << "T: Storage size: " << storage.storageSize << endl;
  for (int i = 0; i < storage.storageSize; i++) {
    for (int j = 0; j < storage.storage[i].storageSize; j++) {
      cout << "Key: " << storage.storage[i].storage[j].key << " "
           << getFuildInfo(storage.storage[i].storage[j].key) << " : "
           << storage.storage[i].storage[j].stringValue << endl;
    }
    cout << "================" << endl;
  }

  cout << "Test passed" << endl;
}

