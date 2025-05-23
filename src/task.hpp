#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>
#include <variant>
#include <memory>

class TaskList;

class TaskObject {
public:
    // Single task constructor
    TaskObject(const std::string& description);

    // Task list constructor
    TaskObject(std::unique_ptr<TaskList> list);

    // Copy constructor
    TaskObject(const TaskObject& other);

    // Move constructor
    TaskObject(TaskObject&& other) noexcept;

    // Copy assignment
    TaskObject& operator=(const TaskObject& other);

    // Move assignment
    TaskObject& operator=(TaskObject&& other) noexcept;

    // Destructor
    ~TaskObject() = default;

    // Check if TaskObject is single
    bool isSingle() const;

    // Get description if single
    std::string getDesc() const;

    // Get the task list if it's a list
    TaskList* getTaskList() const;
private:
    std::variant<std::string, std::unique_ptr<TaskList>> data_;
};

class TaskList {
public:
    // Constructor
    TaskList() = default;

    // Add single task
    void addTask(const std::string& description);

    // Add a task list
    void addTaskList(std::unique_ptr<TaskList> list);

    // Get all tasks
    const std::vector<TaskObject>& getTasks() const;

    // Copy constructor
    TaskList(const TaskList& other);

    // Move constructor
    TaskList(TaskList&& other) noexcept = default;

    // Copy assignment
    TaskList& operator=(const TaskList& other);

    // Move assignment
    TaskList& operator=(TaskList&& other) noexcept = default;

    // Destructor
    ~TaskList() = default;

private:
    std::vector<TaskObject> tasks_;
};

#endif // TASK_HPP
