#include <vector>
#include "task_struct.cpp"
using namespace std;

void swap(task_struct* a, task_struct* b) {
  task_struct t = *a;
  *a = *b;
  *b = t;
}

int partition(vector<task_struct>* array, int low, int high) {
  task_struct t=array[0].at(high);
  int pivot = t.priority;
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (array[0].at(j).priority <= pivot) {
      i++;
      swap(array[0].at(i), array[0].at(j));
    }
  }
  swap(array[0].at(i+1), array[0].at(high));
  return (i + 1);
}

void quickSort(vector<task_struct> *array, int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}