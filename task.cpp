#include "log.cpp"
using namespace std;

class TODO : public LOG {
 public:
  void add_task(int priority, string task);
  void delete_task(int index);
  void mark_task_done(int index, bool flag);
};
void TODO ::mark_task_done(int index, bool flag) {
  if (index > (int)task_vector.size() || index <= 0) {
    if (flag == true)
      cout << "Error: no incomplete item with index #" << index << " exists.";
    else
      cout << "Error: task with index #" << index
           << " does not exist. Nothing deleted.";
  } else {
    vector<task>::iterator it;
    it = task_vector.begin();

    if (flag == true) {
      task_struct task_done = task_vector[index - 1];
      task_vector_comp.push_back(task_done);
      task_vector.erase(it + index - 1);
      cout << "Marked item as done."<<endl;
    } else {
      task_vector.erase(it + index - 1);
      cout << "Deleted task #" << index << endl;
    }
  }
}
void TODO ::delete_task(int index) { mark_task_done(index, false); }
void TODO ::add_task(int priority, string task) {
  task_struct new_task = {task, priority};
  task_vector.push_back(new_task);
  // \"the thing i need to do\"
  cout << "Added task: \"" << task_vector[task_vector.size() - 1].task_title
       << "\" with priority " << task_vector[task_vector.size() - 1].priority
       << endl;
}

int main(int argc, char* argv[]) {
  TODO t_obj;
  if (argc >= 3) {
    // done index
    if (string(argv[1]) == "done") {
      t_obj.mark_task_done(stoi(argv[2]), true);
    }
    // del index
    else if (string(argv[1]) == "del") {
      t_obj.delete_task(stoi(argv[2]));
    } else if (string(argv[1]) == "add") {
      // add priority task
      t_obj.add_task(stoi(argv[2]), argv[3]);
    }
  } else if (argc == 2) {
    // ls
    if (string(argv[1]) == "ls") {
      if (t_obj.task_vector.size() == 0)
        cout << "There are no pending tasks!"<<endl;
      else
        t_obj.pending_tasks();
    }
    // report
    else if (string(argv[1]) == "report") {
      t_obj.report();
    }
    // help
    else if (string(argv[1]) == "help") {
      t_obj.help_page();
    }
    // add
    else if (string(argv[1]) == "add") {
      cout << "Error: Missing tasks string. Nothing added!"<<endl;
    }
    // del
    else if (string(argv[1]) == "del") {
      cout << "Error: Missing NUMBER for deleting tasks."<<endl;
    }
    // done
    else if (string(argv[1]) == "done") {
      cout << "Error: Missing NUMBER for marking tasks as done."<<endl;
    }
  }
  // help
  else {
    t_obj.help_page();
  }
  return 0;
}

/*
References:
1. https://stackoverflow.com/questions/33563874/open-file-in-constructor-c
2. https://www.codegrepper.com/code-examples/cpp/if+argv+%3D%3D+string
3. https://stackoverflow.com/questions/42022735/warning-unknown-escape-sequence
4. https://stackoverflow.com/questions/30445048/c-regex-match-not-working
5. https://www.geeksforgeeks.org/regex-regular-expression-in-c/
6. https://www.geeksforgeeks.org/smatch-regex-regular-expressions-in-c/
7. https://www.geeksforgeeks.org/vector-in-cpp-stl/
8. https://www.geeksforgeeks.org/file-handling-c-classes/
9. https://stackoverflow.com/questions/4892680/sorting-a-vector-of-structs
10. https://stackoverflow.com/questions/26228424/how-to-detect-an-empty-file-in-c/26228684

*/