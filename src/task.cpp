#include "task.hpp"

// TODO: Deep copy function?

// Task Object ================================================================

TaskObject::TaskObject(const std::string& description)
    : data_(description) {}

TaskObject::TaskObject(std::unique_ptr<TaskList> list)
    : data_(std::move(list)) {}

TaskObject::TaskObject(const TaskObject& other) {
    if (other.isSingle()) {
	// Copy string desc
	data_ = std::get<std::string>(other.data_);
    } else {
	const TaskList* otherList = other.getTaskList();
	data_ = std::make_unique<TaskList>(*otherList);
    }
}

TaskObject::TaskObject(TaskObject&& other) noexcept
    : data_(std::move(other.data_)) {}


TaskObject& TaskObject::operator=(const TaskObject& other) {
    if (this == &other) return *this;
    if (other.isSingle()) {
	data_ = std::get<std::string>(other.data_);
    } else {
	const TaskList* otherList = other.getTaskList();
	data_ = std::make_unique<TaskList>(*otherList);
    }
    return *this;
}

TaskObject& TaskObject::operator=(TaskObject&& other) noexcept {
    if (this == &other) return *this;
    data_ = std::move(other.data_);
    return *this;
}

bool TaskObject::isSingle() const {
    return std::holds_alternative<std::string>(data_);
}

std::string TaskObject::getDesc() const {
    if (isSingle()) {
	return std::get<std::string>(data_);
    }
    return "";
}

TaskList* TaskObject::getTaskList() const {
    if (!isSingle()) {
	return std::get<std::unique_ptr<TaskList>>(data_).get();
    }
    return nullptr;
}

// ============================================================================
//
// Task List ==================================================================

void TaskList::addTask(const std::string& description) {
    tasks_.emplace_back(description);
}

void TaskList::addTaskList(std::unique_ptr<TaskList> list) {
    tasks_.emplace_back(std::move(list));
}

const std::vector<TaskObject>& TaskList::getTasks() const {
    return tasks_;
}

TaskList::TaskList(const TaskList& other) {
    for (const auto& task : other.tasks_) {
	tasks_.push_back(task);
    }
}

TaskList& TaskList::operator=(const TaskList& other) {
    if (this == &other) return *this;

    tasks_.clear();
    for (const auto& task : other.tasks_) {
	tasks_.push_back(task);	
    }
    return *this;
}
