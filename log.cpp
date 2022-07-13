#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include "quick_sort.cpp"
using namespace std;

class LOG {
 private:
  void construct_vector(string filename, vector<task_struct> *vec);
  void prioritize_vector(vector<task_struct> *vec);
 public:
  vector<task> task_vector;
  vector<task> task_vector_comp;
  void help_page();
  void report();
  void pending_tasks();
  void completed_tasks();
  LOG();
  ~LOG();
};

void LOG ::construct_vector(string filename, vector<task_struct> *vec) {
  fstream ifs(filename, ios::ate); 
  if(ifs.tellg() != 0){
    ifs.close();
    fstream taskfile_pending(filename, ios::in | ios::out | ios::app);
    string line;
    regex task_pattern("^(.*)\\[([0-9]+)\\]$");
    while (getline(taskfile_pending, line)) {
      smatch matches;
      regex_search(line, matches, task_pattern);
      task_struct t = {matches.str(1), stoi(matches.str(2))};
      vec->push_back(t);
    }
  }
}
void LOG ::prioritize_vector(vector<task_struct>* vec){
  quickSort(vec, 0, (*vec).size()-1);
}
LOG ::LOG() {
  // after object constructing, put all file content into vector.
  construct_vector("task.txt", &task_vector);
  construct_vector("completed.txt", &task_vector_comp);
  prioritize_vector(&task_vector);
  prioritize_vector(&task_vector_comp);
}
LOG ::~LOG() {
  fstream taskfile_pending("task.txt", ios::out);
  fstream taskfile_completed("completed.txt", ios::out);
  // before destructing the object, write all vector to the file.
  if (taskfile_pending.is_open()) {
    for (int i = 0; i < (int)task_vector.size(); i++) {
      taskfile_pending << task_vector[i].task_title << "["
                       << task_vector[i].priority << "]" << endl;
    }
    taskfile_pending.close();
  } else {
    cout << "Unable to open the file"<<endl;
  }
  if (taskfile_completed.is_open()) {
    for (int i = 0; i < (int)task_vector_comp.size(); i++) {
      taskfile_completed << task_vector_comp[i].task_title << "["
                         << task_vector_comp[i].priority << "]" << endl;
    }
    taskfile_completed.close();
  } else {
    cout << "Unable to open the file"<<endl;
  }
}
void LOG ::help_page() {
  fstream help("help.txt", ios::in);
  string line;
  while (getline(help, line)) {
    cout << line << endl;
  }
}
void LOG ::report() {
  pending_tasks();
  completed_tasks();
}
void LOG ::pending_tasks() {
  cout << "Pending : " << task_vector.size() << endl;
  for (int i = 0; i < (int)task_vector.size(); i++) {
    cout << i + 1 << ". " << task_vector[i].task_title << " ["
         << task_vector[i].priority << "]"<<endl;
  }
}
void LOG ::completed_tasks() {
  cout << "Completed : " << task_vector_comp.size() << endl;
  for (int i = 0; i < (int)task_vector_comp.size(); i++) {
    cout << i + 1 << ". " << task_vector_comp[i].task_title << " ["
         << task_vector_comp[i].priority << "]"<<endl;
  }
}