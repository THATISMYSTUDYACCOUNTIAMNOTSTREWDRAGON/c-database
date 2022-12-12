#include <cstring>
#include<iostream>

using namespace std;

bool isValidDate(int year, int month, int day) {
  unsigned int leap;
  unsigned char mon_day[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if ((year < 1) || (year > 2022)) {
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

int main() {
  int arr[5][3] = {
    {31, 01, 2010},
    {12, 10, 2011},
    {31, 01, 2010},
    {-31, 01, 3000},
    {31, -01, 2010},
  };

  for (int i = 0; i < 5; i++) {
    cout << arr[i][0] << " " << arr[i][1] << " " << arr[i][2] << " " << isValidDate(arr[i][2], arr[i][1], arr[i][0]) << endl;
  }

  return 0;
}
