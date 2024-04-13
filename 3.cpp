#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Task {
    string task_desc;
    bool task_done;
};

void showTasks(const vector<Task>& all_tasks) {
    cout << "Task List:\n";
    for (size_t i = 0; i < all_tasks.size(); ++i) {
        cout << "[" << i + 1 << "] ";
        cout << (all_tasks[i].task_done ? "[Completed] " : "[Pending] ");
        cout << all_tasks[i].task_desc << "\n";
    }
}

void addNewTask(vector<Task>& all_tasks, const string& task_desc) {
    Task new_task = {task_desc, false};
    all_tasks.push_back(new_task);
}

void modifyTask(vector<Task>& all_tasks, size_t task_index, const string& new_task_desc) {
    if (task_index < all_tasks.size()) {
        all_tasks[task_index].task_desc = new_task_desc;
    } else {
        cout << "Invalid task index.\n";
    }
}

void markTaskComplete(vector<Task>& all_tasks, size_t task_index) {
    if (task_index < all_tasks.size()) {
        all_tasks[task_index].task_done = true;
    } else {
        cout << "Invalid task index.\n";
    }
}

void saveTasksToFile(const vector<Task>& all_tasks, const string& file_name) {
    ofstream file(file_name.c_str());
    if (file.is_open()) {
        vector<Task>::const_iterator it;
        for (it = all_tasks.begin(); it != all_tasks.end(); ++it) {
            const Task& task = *it;
            file << task.task_done << " " << task.task_desc << "\n";
        }
        file.close();
    } else {
        cout << "Error: Unable to save tasks to file.\n";
    }
}

void loadTasksFromFile(vector<Task>& all_tasks, const string& file_name) {
    ifstream file(file_name.c_str());
    if (file.is_open()) {
        all_tasks.clear();
        while (!file.eof()) {
            Task task;
            file >> task.task_done;
            getline(file >> ws, task.task_desc);
            all_tasks.push_back(task);
        }
        file.close();
    } else {
        cout << "Error: Unable to load tasks from file.\n";
    }
}

int main() {
    vector<Task> all_tasks;
    string file_name = "task_history.txt";
    loadTasksFromFile(all_tasks, file_name);

    while (true) {
        cout << "\nAvailable Options:\n";
        cout << "1. Show Tasks\n";
        cout << "2. Add New Task\n";
        cout << "3. Modify Task\n";
        cout << "4. Mark Task as Complete\n";
        cout << "5. Save and Quit\n";

        int user_choice;

        cout << "Enter your choice: ";
        cin >> user_choice;
        switch (user_choice) {
            case 1:
                showTasks(all_tasks);
                break;

            case 2:
                {
                    string task_desc;
                    cout << "Enter task description: ";
                    cin.ignore();
                    getline(cin, task_desc);
                    addNewTask(all_tasks, task_desc);
                    break;
                }
            case 3:
                {
                    size_t task_index;
                    string new_task_desc;
                    cout << "Enter task index to modify: ";
                    cin >> task_index;
                    cout << "Enter new task description: ";

                    cin.ignore();
                    getline(std::cin, new_task_desc);
                    modifyTask(all_tasks, task_index - 1, new_task_desc);
                    break;
                }

            case 4:
                {
                    size_t task_index;
                    cout << "Enter task index to mark as completed: ";
                    cin >> task_index;
                    markTaskComplete(all_tasks, task_index - 1);
                    break;
                }

            case 5:
                saveTasksToFile(all_tasks, file_name);
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
