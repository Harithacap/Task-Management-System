#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Task {
    int id;
    string description;
    string dueDate;
    string priority;
    bool completed;
};

vector<Task> tasks;
int nextId = 1;

// Add a new task
void addTask(const string& description, const string& dueDate, const string& priority) {
    tasks.push_back({nextId++, description, dueDate, priority, false});
    cout << "Task added successfully!" << endl;
}

// Edit an existing task
void editTask(int id, const string& newDescription, const string& newDueDate, const string& newPriority) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.description = newDescription;
            task.dueDate = newDueDate;
            task.priority = newPriority;
            cout << "Task updated successfully!" << endl;
            return;
        }
    }
    cout << "Task not found!" << endl;
}

// Delete a task
void deleteTask(int id) {
    tasks.erase(remove_if(tasks.begin(), tasks.end(), [id](Task& task) {
        return task.id == id;
    }), tasks.end());
    cout << "Task deleted successfully!" << endl;
}

// Mark a task as complete
void completeTask(int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            cout << "Task marked as complete!" << endl;
            return;
        }
    }
    cout << "Task not found!" << endl;
}

// Display tasks
void displayTasks(bool onlyPending = false) {
    // Header
    cout << left << setw(5) << "ID"
         << setw(30) << "Description"
         << setw(15) << "Due Date"
         << setw(10) << "Priority"
         << setw(10) << "Completed" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // Display tasks
    for (const auto& task : tasks) {
        if (onlyPending && task.completed) continue; // Skip completed tasks if onlyPending is true

        cout << left << setw(5) << task.id
             << setw(30) << task.description
             << setw(15) << task.dueDate
             << setw(10) << task.priority
             << setw(10) << (task.completed ? "Yes" : "No") << endl;
    }
}

// Filter tasks by priority
void filterByPriority(const string& priority) {
    cout << "ID\tDescription\tDue Date\tPriority\tCompleted" << endl;
    cout << "-----------------------------------------------------------" << endl;
    for (const auto& task : tasks) {
        if (task.priority == priority) {
            cout << task.id << "\t" << task.description << "\t" << task.dueDate << "\t" << task.priority << "\t"
                 << (task.completed ? "Yes" : "No") << endl;
        }
    }
}
// Main menu
int main() {
    // Example data
    tasks = {
        {1, "Complete C++ project", "2025-01-15", "High", false},
        {2, "Buy groceries", "2025-01-16", "Medium", false},
        {3, "Call John", "2025-01-14", "Low", true},
        {4, "Attend team meeting", "2025-01-14", "High", false},
        {5, "Pay electricity bill", "2025-01-18", "Medium", false},
        {6, "Prepare presentation", "2025-01-20", "High", false},
        {7, "Plan weekend trip", "2025-01-17", "Low", false},
        {8, "Clean the house", "2025-01-19", "Medium", false},
        {9, "Fix the car", "2025-01-21", "High", false},
        {10, "Visit the doctor", "2025-01-22", "Medium", false},
    };

    int choice;
    do {
        cout << "\nTask Management System\n";
        cout << "1. Add Task\n2. Edit Task\n3. Delete Task\n4. Mark Task as Complete\n";
        cout << "5. Display All Tasks\n6. Display Pending Tasks\n7. Filter by Priority\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string description, dueDate, priority;
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, description);
                cout << "Enter due date (YYYY-MM-DD): ";
                cin >> dueDate;
                cout << "Enter priority (High/Medium/Low): ";
                cin >> priority;
                addTask(description, dueDate, priority);
                break;
            }
            case 2: {
                int id;
                string newDescription, newDueDate, newPriority;
                cout << "Enter task ID to edit: ";
                cin >> id;
                cout << "Enter new description: ";
                cin.ignore();
                getline(cin, newDescription);
                cout << "Enter new due date (YYYY-MM-DD): ";
                cin >> newDueDate;
                cout << "Enter new priority (High/Medium/Low): ";
                cin >> newPriority;
                editTask(id, newDescription, newDueDate, newPriority);
                break;
            }
            case 3: {
                int id;
                cout << "Enter task ID to delete: ";
                cin >> id;
                deleteTask(id);
                break;
            }
            case 4: {
                int id;
                cout << "Enter task ID to mark as complete: ";
                cin >> id;
                completeTask(id);
                break;
            }
            case 5:
                displayTasks();
                break;
            case 6:
                displayTasks(true);
                break;
            case 7: {
                string priority;
                cout << "Enter priority to filter by (High/Medium/Low): ";
                cin >> priority;
                filterByPriority(priority);
                break;
            }
            case 8:
                cout << "Exiting Task Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
