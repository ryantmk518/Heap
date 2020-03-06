//Ryan Thammakhoune. Heap. Puts integers into a tree, and sorts it from highest to lowest.

#include <cstring>
#include <fstream>
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void heap (int* array, int input, int count) {
  int index;
  int temp;
  temp = array[input];
  index = input*2;
  while (index <= count) { //Sorts the numbers in the tree
    if (array[index+1] > array[index] && index < count)
      ++index;
    if (temp > array[index])
      break;
    else if (temp <= array[index]) {
      array[index/2] = array[index];
      index = 2 * index;
    }
  }
  array[index/2] = temp;
  return;
}

void build (int* array, int count) {
  for(int i = count/2; i >= 1; i--) { //From wikipedia for heap algorithm. 
    heap(array, i, count);
  }
}

void print (int* array, int count, int input, int input2) { //Idea from Ethan Wang to print the tree sideways
  int left = input2*2; //From wikipedia. Left is 2n, right is 2n+2
  int right = (input2*2)+1;
  if (right <= count) {
    print(array, count, input+1, right);
  }
  int current = input;
  while (input > 0) {
    cout << "    "; //Spacing for sideways tree method
    input = input - 1;
  }
  cout << array[input2] << endl;
  if (left <= count) {
    print(array, count, current + 1, left);
  }
}

int main() {
  char input[9];
  cout << "Choose input type: (Enter, File)" << endl; //Ask for input type
  cin.get(input, 9);
  cin.clear();
  cin.ignore();
  if (strcmp(input, "Enter") == 0) { //Console method
    cout << "Enter input" << endl;
    char* array = new char[999];
    cin.getline(array, 999);
    cout << "\n" << endl;
    int c = 0;
    int a = 1;
    int* out = new int[999];
    char* split = strtok(array, " "); //Split the string by space
    while (split != NULL) { //Idea for strtok from Ethan Wang
      out[a] = atoi(split); //Copy to integer array
      split = strtok(NULL, " ");
      ++c;
      ++a;
    }




    build(out, c); //Build tree
    print(out, c, 0, 1); //Print the tree using the sideways method
    cout << " " << endl; 
    cout << "High to low: ";
    for (int i = c; i > 0; i--) { //Prints out the sorted numbers
      cout << out[1] << " "; 
      out[1] = out[i];
      out[i] = 0; 
      build(out, i);
      out[i] = out[i - 1];
    }
  }
  else if (strcmp(input, "File") == 0) { //For file method
    cout << "Enter file name" << endl;
    char fname[99];
    cin.getline(fname, 99);
    cout << "\n" << endl;
    ifstream file;
    file.open(fname); //Open the inputted file name
    char* output = new char[999];
    int* out = new int[999];
    int i = 0;
    while(!file.eof()) { //If has not reached end of file
      file.get(output[i]);
      i++;
    }
    char* split = strtok(output, " "); //Basically do the same thing from the console method
    int a = 1;
    int c = 0;
    while(split != NULL) {
      out[a] = atoi(split);
      split = strtok(NULL, " ");
      a++;
      c++;
    }
    build(out, c);
    print(out, c, 0, 1);
    cout << " " << endl; 
    cout << "High to low: ";
    for (int i = c; i > 0; i--) {
      cout << out[1] << " "; 
      out[1] = out[i];
      out[i] = 0; 
      build(out, i);
      out[i] = out[i - 1];
    }
  }
}
