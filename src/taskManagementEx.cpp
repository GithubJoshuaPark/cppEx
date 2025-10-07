// Making task management using vector in C++ and struct
// This is a simple task management system that allows adding, removing, and displaying tasks.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::find_if, std::remove_if
#include <limits>    // For std::numeric_limits
#include <fstream>   // For file I/O (ifstream, ofstream)
#include "helloEx.h" // for printLine
#include "taskManagementEx.h"
#include "json.hpp"  // For nlohmann::json

using json = nlohmann::json;

// Task structure defined in helloEx.h
// typedef struct Task {
//     int id;
//     bool completed;
//     int priority; // 1 (highest) to 5 (lowest)
//     std::string title;
//     std::string description; //     std::string dueDate;
// };

// --- JSON Serialization/Deserialization for Task struct ---
// This tells the nlohmann::json library how to convert our Task struct.
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

// --- Function Prototypes for Task Management ---
static void displayTaskMenu();
static void saveTasksToFile(const std::vector<Task>& tasks);
static void loadTasksFromFile(std::vector<Task>& tasks, int& nextId);
static void addTask(std::vector<Task>& tasks, int& nextId, bool save);
static void viewTasks(const std::vector<Task>& tasks);
static void markTaskComplete(std::vector<Task>& tasks, bool save);
static void removeTask(std::vector<Task>& tasks, bool save);


static void displayTaskMenu() {
    printLine("Task Manager Menu");
    std::cout << "1. Add Task" << std::endl;
    std::cout << "2. View Tasks" << std::endl;
    std::cout << "3. Mark Task as Complete" << std::endl;
    std::cout << "4. Remove Task" << std::endl;
    std::cout << "5. Exit to Main Menu" << std::endl;
    std::cout << "--------------------------" << std::endl;
}

static void saveTasksToFile(const std::vector<Task>& tasks) {
    // The second argument '4' makes the JSON output nicely indented.
    json j = tasks;
    std::ofstream file("tasks.json");
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    } else {
        std::cerr << "Error: Could not open tasks.json for writing." << std::endl;
    }
}

static void loadTasksFromFile(std::vector<Task>& tasks, int& nextId) {
    std::ifstream file("tasks.json");
    if (file.is_open()) {
        json j;
        // Handle empty file case
        if (file.peek() == std::ifstream::traits_type::eof()) {
            return;
        }
        file >> j;

        // Deserialize into a temporary vector of Task objects
        tasks = j.get<std::vector<Task>>();
        file.close();

        // Update nextId to be greater than the max existing ID
        if (!tasks.empty()) {
            int maxId = 0;
            for (const auto& task : tasks) {
                if (task.id > maxId) {
                    maxId = task.id;
                }
            }
            nextId = maxId + 1;
        }
    }
}

static void addTask(std::vector<Task>& tasks, int& nextId, bool save) {
    Task newTask;
    newTask.id = nextId++;
    newTask.completed = false;

    std::cout << "Enter task title: ";
    std::getline(std::cin, newTask.title);

    std::cout << "Enter task description: ";
    std::getline(std::cin, newTask.description);

    std::cout << "Enter priority (1-5): ";
    std::cin >> newTask.priority;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter due date (e.g., YYYY-MM-DD): ";
    std::getline(std::cin, newTask.dueDate);

    tasks.push_back(newTask);
    if (save) {
        saveTasksToFile(tasks);
    }
    std::cout << "\nTask added successfully!\n" << std::endl;
}

static void viewTasks(const std::vector<Task>& tasks) {
    printLine("Current Tasks");
    if (tasks.empty()) {
        std::cout << "No tasks to display." << std::endl;
    } else {
        for (const auto& task : tasks) {
            std::cout << "ID: " << task.id << " [" << (task.completed ? "X" : " ") << "]"
                      << " | Priority: " << task.priority
                      << " | Due: " << task.dueDate
                      << "\n   Title: " << task.title
                      << "\n   Desc: " << task.description << std::endl;
            std::cout << "--------------------------------------------------\n";
        }
    }
    std::cout << std::endl;
}

static void markTaskComplete(std::vector<Task>& tasks, bool save) {
    int id;
    std::cout << "Enter ID of task to mark as complete: ";
    std::cin >> id;

    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.id == id;
    });

    if (it != tasks.end()) {
        it->completed = true;
        if (save) {
            saveTasksToFile(tasks);
        }
        std::cout << "\nTask " << id << " marked as complete.\n" << std::endl;
    } else {
        std::cout << "\nTask with ID " << id << " not found.\n" << std::endl;
    }
}

static void removeTask(std::vector<Task>& tasks, bool save) {
    int id;
    std::cout << "Enter ID of task to remove: ";
    std::cin >> id;

    auto new_end = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.id == id;
    });

    if (new_end != tasks.end()) {
        tasks.erase(new_end, tasks.end());
        if (save) {
            saveTasksToFile(tasks);
        }
        std::cout << "\nTask " << id << " removed.\n" << std::endl;
    } else {
        std::cout << "\nTask with ID " << id << " not found.\n" << std::endl;
    }
}

/**
 * @brief Main function for task management using vector and struct.
 */
void taskManagementEx(void) {
    printLine("taskManagementEx function.");    
    std::vector<Task> tasks;
    int nextId = 1;
    int choice = 0;
    bool saveToFile = true; // Set to true to enable file persistence

    if (saveToFile) {
        loadTasksFromFile(tasks, nextId);
    }

    while (choice != 5) {
        displayTaskMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Basic input validation
        if (std::cin.fail()) {
            std::cout << "\nInvalid input. Please enter a number.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Consume the rest of the line, especially the newline character
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        switch (choice) {
            case 1:
                addTask(tasks, nextId, saveToFile);
                break;
            case 2:
                viewTasks(tasks);
                break;
            case 3:
                markTaskComplete(tasks, saveToFile);
                break;
            case 4:
                removeTask(tasks, saveToFile);
                break;
            case 5:
                std::cout << "\nReturning to the main menu." << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please try again.\n" << std::endl;
                break;
        }
    }
}