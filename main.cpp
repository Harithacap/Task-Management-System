#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Task {
    std::string title;
    std::string dueDate;
    int priority; // 1 (High), 2 (Medium), 3 (Low)
    bool isComplete;

    Task(std::string t, std::string d, int p)
        : title(t), dueDate(d), priority(p), isComplete(false) {}
};

std::vector<Task> tasks;

// Function prototypes
void addTask();
void editTask();
void deleteTask();
void listTasks();
void markTaskComplete();
void filterTasks();
void sortTasks();

int main() {
    int choice;
    do {
        std::cout << "\nTask Management System\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Edit Task\n";
        std::cout << "3. Delete Task\n";
        std::cout << "4. List Tasks\n";
        std::cout << "5. Mark Task as Complete\n";
        std::cout << "6. Filter Tasks\n";
        std::cout << "7. Sort Tasks\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: editTask(); break;
            case 3: deleteTask(); break;
            case 4: listTasks(); break;
            case 5: markTaskComplete(); break;
            case 6: filterTasks(); break;
            case 7: sortTasks(); break;
            case 8: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 8);

    return 0;
}

void addTask() {
    std::string title, dueDate;
    int priority;
    std::cout << "Enter task title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Enter due date (YYYY-MM-DD): ";
    std::cin >> dueDate;
    std::cout << "Enter priority (1=High, 2=Medium, 3=Low): ";
    std::cin >> priority;

    tasks.emplace_back(title, dueDate, priority);
    std::cout << "Task added successfully!\n";
}

void editTask() {
    listTasks();
    int index;
    std::cout << "Enter task number to edit: ";
    std::cin >> index;

    if (index < 1 || index > tasks.size()) {
        std::cout << "Invalid task number!\n";
        return;
    }

    Task &task = tasks[index - 1];
    std::cout << "Editing task: " << task.title << "\n";
    std::cout << "Enter new title (or press enter to keep current): ";
    std::cin.ignore();
    std::string title;
    std::getline(std::cin, title);
    if (!title.empty()) task.title = title;

    std::cout << "Enter new due date (YYYY-MM-DD) or press enter to keep current: ";
    std::string dueDate;
    std::getline(std::cin, dueDate);
    if (!dueDate.empty()) task.dueDate = dueDate;

    std::cout << "Enter new priority (1=High, 2=Medium, 3=Low) or press enter to keep current: ";
    std::string priorityStr;
    std::getline(std::cin, priorityStr);
    if (!priorityStr.empty()) task.priority = std::stoi(priorityStr);

    std::cout << "Task updated successfully!\n";
}

void deleteTask() {
    listTasks();
    int index;
    std::cout << "Enter task number to delete: ";
    std::cin >> index;

    if (index < 1 || index > tasks.size()) {
        std::cout << "Invalid task number!\n";
        return;
    }

    tasks.erase(tasks.begin() + index - 1);
    std::cout << "Task deleted successfully!\n";
}

void listTasks() {
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }

    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i].title
                  << " [Priority: " << tasks[i].priority
                  << ", Due: " << tasks[i].dueDate
                  << ", Complete: " << (tasks[i].isComplete ? "Yes" : "No") << "]\n";
    }
}

void markTaskComplete() {
    listTasks();
    int index;
    std::cout << "Enter task number to mark as complete: ";
    std::cin >> index;

    if (index < 1 || index > tasks.size()) {
        std::cout << "Invalid task number!\n";
        return;
    }

    tasks[index - 1].isComplete = true;
    std::cout << "Task marked as complete!\n";
}

void filterTasks() {
    int filter;
    std::cout << "Filter by: 1. Complete, 2. Incomplete, 3. Priority\n";
    std::cout << "Enter your choice: ";
    std::cin >> filter;

    if (filter == 1 || filter == 2) {
        bool showComplete = (filter == 1);
        for (const auto &task : tasks) {
            if (task.isComplete == showComplete) {
                std::cout << task.title << " [Priority: " << task.priority
                          << ", Due: " << task.dueDate << "]\n";
            }
        }
    } else if (filter == 3) {
        int priority;
        std::cout << "Enter priority to filter (1=High, 2=Medium, 3=Low): ";
        std::cin >> priority;
        for (const auto &task : tasks) {
            if (task.priority == priority) {
                std::cout << task.title << " [Due: " << task.dueDate << "]\n";
            }
        }
    } else {
        std::cout << "Invalid filter choice!\n";
    }
}

void sortTasks() {
    std::cout << "Sort by: 1. Due Date, 2. Priority\n";
    int sortOption;
    std::cin >> sortOption;

    if (sortOption == 1) {
        std::sort(tasks.begin(), tasks.end(),
                  [](const Task &a, const Task &b) { return a.dueDate < b.dueDate; });
        std::cout << "Tasks sorted by due date!\n";
    } else if (sortOption == 2) {
        std::sort(tasks.begin(), tasks.end(),
                  [](const Task &a, const Task &b) { return a.priority < b.priority; });
        std::cout << "Tasks sorted by priority!\n";
    } else {
        std::cout << "Invalid sort choice!\n";
    }
}

