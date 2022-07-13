## C++ TODO CLI 💻📑
### ⚡ Usage

### 1. Help

Executing the command without any arguments, or with a single argument help prints the CLI usage.

```
$ ./task help
Usage :-
$ ./task add 2 hello world    # Add a new item with priority 2 and text "hello world" to the list
$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order
$ ./task del INDEX            # Delete the incomplete item with the given index
$ ./task done INDEX           # Mark the incomplete item with the given index as complete
$ ./task help                 # Show usage
$ ./task report               # Statistics
```

### 2. List all pending items

Use the ls command to see all the items that are not yet complete, in ascending order of priority.

Every item should be printed on a new line. with the following format

```
[index] [task] [priority]
```

Example:

```
$ ./task ls
1. change light bulb [2]
2. water the plants [5]
```

index starts from 1, this is used to identify a particular task to complete or delete it.

### 3. Add a new item

Use the add command. The text of the task should be enclosed within double quotes (otherwise only the first word is considered as the item text, and the remaining words are treated as different arguments).

```
$ ./task add 5 "the thing i need to do"
Added task: "the thing i need to do" with priority 5
```

### 4. Delete an item

Use the del command to remove an item by its index.

```
$ ./task del 3
Deleted item with index 3
```

Attempting to delete a non-existent item should display an error message.

```
$ ./task del 5
Error: item with index 5 does not exist. Nothing deleted.
```

### 5. Mark a task as completed

Use the done command to mark an item as completed by its index.

```
$ ./task done 1
Marked item as done.
```

Attempting to mark a non-existed item as completed will display an error message.

```
$ ./task done 5
Error: no incomplete item with index 5 exists.
```

### 6. Generate a report

Show the number of complete and incomplete items in the list. and the complete and incomplete items grouped together.

```
$ ./task report
Pending : 2
1. this is a pending task [1]
2. this is a pending task with priority [4]

Completed : 3
1. completed task
2. another completed task
3. yet another completed task
```

### Files included:
1. **task.cpp** : This has to be compiled as this is main file that includes the other file's classes and functions. 
```cpp
// TODO class have the below member functions.
class TODO : public LOG {
 public:
  void add_task(int priority, string task);
  void delete_task(int index);
  void mark_task_done(int index, bool flag);
};
// main function includes the CLI arguments and its handling
```
2. **log.cpp** : This file contains class that deals with logging statements into the CLI. It includes vector construction from file contents, sorting based on priorities and other basic TODO print functionalities based on categories (help/report/pending/completed). It stores the completed tasks in a vector and all pending tasks in other vector for operations.
```cpp
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
```
3. **task_struct.cpp** : This contains the structure of how a task in TODO list looks like.
```cpp
typedef struct task {
  string task_title;
  int priority;
} task_struct;
```
4. **quick_sort.cpp** : This file has the quicksort of vector of *task_struct*s, used for prioritizing the tasks while adding into the list.
```cpp
void quickSort(vector<task_struct> *array, int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}
```

***
### This project was made as part of the even - "Global Digital Corps - Software Engineering Test Problem | Priority list"