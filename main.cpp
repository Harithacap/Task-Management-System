#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Task {
    int id;
    std::string description;
    std::string dueDate;
    int priority;
    bool isComplete;
};

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId = 1;

public:
    void addTask(const std::string &description, const std::string &dueDate, int priority) {
        tasks.push_back({nextId++, description, dueDate, priority, false});
        std::cout << "Task added successfully!\n";
    }

    void editTask(int id, const std::string &newDescription, const std::string &newDueDate, int newPriority) {
        for (auto &task : tasks) {
            if (task.id == id) {
                task.description = newDescription;
                task.dueDate = newDueDate;
                task.priority = newPriority;
                std::cout << "Task updated successfully!\n";
                return;
            }
        }
        std::cout << "Task not found!\n";
    }

    void deleteTask(int id) {
        auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task &task) {
            return task.id == id;
        });
        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            std::cout << "Task deleted successfully!\n";
        } else {
            std::cout << "Task not found!\n";
        }
    }

    void markTaskComplete(int id) {
        for (auto &task : tasks) {
            if (task.id == id) {
                task.isComplete = true;
                std::cout << "Task marked as complete!\n";
                return;
            }
        }
        std::cout << "Task not found!\n";
    }

    void filterTasks(bool completed) {
        std::cout << (completed ? "Completed Tasks:\n" : "Incomplete Tasks:\n");
        for (const auto &task : tasks) {
            if (task.isComplete == completed) {
                displayTask(task);
            }
        }
    }

    void sortTasksByPriority() {
        std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
            return a.priority < b.priority;
        });
        std::cout << "Tasks sorted by priority!\n";
    }

    void displayAllTasks() {
        std::cout << "All Tasks:\n";
        for (const auto &task : tasks) {
            displayTask(task);
        }
    }

private:
    void displayTask(const Task &task) {
        std::cout << "ID: " << task.id
                  << " | Description: " << task.description
                  << " | Due Date: " << task.dueDate
                  << " | Priority: " << task.priority
                  << " | Status: " << (task.isComplete ? "Complete" : "Incomplete")
                  << "\n";
    }
};

int main() {
    TaskManager manager;
    int choice;

    do {
        std::cout << "\nTask Management System\n";
        std::cout << "1. Add Task\n2. Edit Task\n3. Delete Task\n4. Mark Task as Complete\n5. Filter Tasks\n6. Sort Tasks by Priority\n7. Display All Tasks\n8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string description, dueDate;
            int priority;
            std::cin.ignore();
            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            std::cout << "Enter due date: ";
            std::getline(std::cin, dueDate);
            std::cout << "Enter priority (1-10): ";
            std::cin >> priority;
            manager.addTask(description, dueDate, priority);
            break;
        }
        case 2: {
            int id, priority;
            std::string description, dueDate;
            std::cout << "Enter task ID to edit: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Enter new description: ";
            std::getline(std::cin, description);
            std::cout << "Enter new due date: ";
            std::getline(std::cin, dueDate);
            std::cout << "Enter new priority (1-10): ";
            std::cin >> priority;
            manager.editTask(id, description, dueDate, priority);
            break;
        }
        case 3: {
            int id;
            std::cout << "Enter task ID to delete: ";
            std::cin >> id;
            manager.deleteTask(id);
            break;
        }
        case 4: {
            int id;
            std::cout << "Enter task ID to mark as complete: ";
            std::cin >> id;
            manager.markTaskComplete(id);
            break;
        }
        case 5: {
            bool completed;
            std::cout << "Enter 1 for completed tasks, 0 for incomplete tasks: ";
            std::cin >> completed;
            manager.filterTasks(completed);
            break;
        }
        case 6:
            manager.sortTasksByPriority();
            break;
        case 7:
            manager.displayAllTasks();
            break;
        case 8:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 8);

    return 0;
}
