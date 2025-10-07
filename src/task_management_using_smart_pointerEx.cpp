#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <memory> // Required for smart pointers (shared_ptr, unique_ptr, weak_ptr)
#include "helloEx.h" // for printLine
#include "task_management_using_smart_pointerEx.h"
#include "json.hpp"  // For nlohmann::json

using json = nlohmann::json;

// --- JSON Serialization/Deserialization for Task struct ---
// These functions remain the same as they operate on Task objects, not pointers.
static void to_json(json& j, const Task& t) {
    j = json{{"id", t.id}, {"completed", t.completed}, {"priority", t.priority},
             {"title", t.title}, {"description", t.description}, {"dueDate", t.dueDate}};
}

static void from_json(const json& j, Task& t) {
    j.at("id").get_to(t.id);
    j.at("completed").get_to(t.completed);
    j.at("priority").get_to(t.priority);
    j.at("title").get_to(t.title);
    j.at("description").get_to(t.description);
    j.at("dueDate").get_to(t.dueDate);
}

// --- Function Prototypes ---
static void displaySmartTaskMenu();
static void saveTasksToFile(const std::vector<std::unique_ptr<Task>>& tasks);
static void loadTasksFromFile(std::vector<std::unique_ptr<Task>>& tasks, int& nextId);
static void addTask(std::vector<std::unique_ptr<Task>>& tasks, int& nextId, bool save);
static void viewTasks(const std::vector<std::unique_ptr<Task>>& tasks);
static void markTaskComplete(std::vector<std::unique_ptr<Task>>& tasks, bool save);
static void removeTask(std::vector<std::unique_ptr<Task>>& tasks, bool save);

static void displaySmartTaskMenu() {
    printLine("Task Manager Menu (Smart Pointers)");
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. View Tasks" << std::endl;
    std::cout << "3. Mark Task as Complete" << std::endl;
    std::cout << "4. Remove Task" << std::endl;
    std::cout << "5. Exit to Main Menu" << std::endl;
    std::cout << "------------------------------------" << std::endl;
}

static void saveTasksToFile(const std::vector<std::unique_ptr<Task>>& tasks) {
    json j = json::array();
    for (const auto& task_ptr : tasks) {
        j.push_back(*task_ptr); // Dereference the pointer to serialize the Task object
    }

    std::ofstream file("tasks_smart.json");
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    } else {
        std::cerr << "Error: Could not open tasks_smart.json for writing." << std::endl;
    }
}

static void loadTasksFromFile(std::vector<std::unique_ptr<Task>>& tasks, int& nextId) {
    std::ifstream file("tasks_smart.json");
    if (file.is_open()) {
        json j;
        // Handle empty file case
        if (file.peek() == std::ifstream::traits_type::eof()) {
            return;
        }
        file >> j;
        
        // Deserialize into a temporary vector of Task objects
        std::vector<Task> temp_tasks = j.get<std::vector<Task>>();
        file.close();

        // Convert Task objects to unique_ptr<Task> and move them into the main vector
        tasks.clear();
        for (auto& task_obj : temp_tasks) {
            tasks.push_back(std::make_unique<Task>(std::move(task_obj)));
        }

        if (!tasks.empty()) {
            int maxId = 0;
            for (const auto& task_ptr : tasks) {
                if (task_ptr->id > maxId) {
                    maxId = task_ptr->id;
                }
            }
            nextId = maxId + 1;
        }
    }
}

static void addTask(std::vector<std::unique_ptr<Task>>& tasks, int& nextId, bool save) {
    auto newTask = std::make_unique<Task>();
    newTask->id = nextId++;
    newTask->completed = false;

    std::cout << "Enter task title: ";
    std::getline(std::cin, newTask->title);

    std::cout << "Enter task description: ";
    std::getline(std::cin, newTask->description);

    std::cout << "Enter priority (1-5): ";
    std::cin >> newTask->priority;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter due date (e.g., YYYY-MM-DD): ";
    std::getline(std::cin, newTask->dueDate);

    tasks.push_back(std::move(newTask));
    if (save) {
        saveTasksToFile(tasks);
    }
    std::cout << "\nTask added successfully!\n" << std::endl;
}

static void viewTasks(const std::vector<std::unique_ptr<Task>>& tasks) {
    printLine("Current Tasks");
    if (tasks.empty()) {
        std::cout << "No tasks to display." << std::endl;
    } else {
        for (const auto& task_ptr : tasks) {
            std::cout << "ID: " << task_ptr->id << " [" << (task_ptr->completed ? "X" : " ") << "]"
                      << " | Priority: " << task_ptr->priority
                      << " | Due: " << task_ptr->dueDate
                      << "\n   Title: " << task_ptr->title
                      << "\n   Desc: " << task_ptr->description << std::endl;
            std::cout << "--------------------------------------------------\n";
        }
    }
    std::cout << std::endl;
}

static void markTaskComplete(std::vector<std::unique_ptr<Task>>& tasks, bool save) {
    int id;
    std::cout << "Enter ID of task to mark as complete: ";
    std::cin >> id;

    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const std::unique_ptr<Task>& task_ptr) {
        return task_ptr->id == id;
    });

    if (it != tasks.end()) {
        (*it)->completed = true; // Dereference iterator to get unique_ptr, then dereference unique_ptr
        if (save) {
            saveTasksToFile(tasks);
        }
        std::cout << "\nTask " << id << " marked as complete.\n" << std::endl;
    } else {
        std::cout << "\nTask with ID " << id << " not found.\n" << std::endl;
    }
}

static void removeTask(std::vector<std::unique_ptr<Task>>& tasks, bool save) {
    int id;
    std::cout << "Enter ID of task to remove: ";
    std::cin >> id;

    auto new_end = std::remove_if(tasks.begin(), tasks.end(), [id](const std::unique_ptr<Task>& task_ptr) {
        return task_ptr->id == id;
    });

    if (new_end != tasks.end()) {
        tasks.erase(new_end, tasks.end()); // Erasing the unique_ptr automatically deletes the Task object
        if (save) {
            saveTasksToFile(tasks);
        }
        std::cout << "\nTask " << id << " removed.\n" << std::endl;
    } else {
        std::cout << "\nTask with ID " << id << " not found.\n" << std::endl;
    }
}

/**
 * @brief The main function for task management using smart pointers.
 */
void task_management_using_smart_pointerEx(void) {
    printLine("Task Management with Smart Pointers");
    std::vector<std::unique_ptr<Task>> tasks;
    int nextId = 1;
    int choice = 0;
    bool saveToFile = true;

    if (saveToFile) {
        loadTasksFromFile(tasks, nextId);
    }

    while (choice != 5) {
        displaySmartTaskMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "\nInvalid input. Please enter a number.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: addTask(tasks, nextId, saveToFile); break;
            case 2: viewTasks(tasks); break;
            case 3: markTaskComplete(tasks, saveToFile); break;
            case 4: removeTask(tasks, saveToFile); break;
            case 5: std::cout << "\nReturning to the main menu." << std::endl; break;
            default: std::cout << "\nInvalid choice. Please try again.\n" << std::endl; break;
        }
    }
}