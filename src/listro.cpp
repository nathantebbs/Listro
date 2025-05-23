#include "listro.hpp"

using namespace ftxui;

Listro::Listro() 
    : screen(ScreenInteractive::TerminalOutput()) {
    // For demo: create a sample task list
    masterList = new TaskList();
    masterList->addTask("Walk the dog");
    masterList->addTask("Do homework");
    auto sublist = std::make_unique<TaskList>();
    sublist->addTask("Buy milk");
    sublist->addTask("Buy eggs");
    masterList->addTaskList(std::move(sublist));
}

Listro::~Listro() {
    delete masterList;
}

Component Listro::RenderTaskList(TaskList* list) {
    std::vector<Element> elements;

    for (const auto& task : list->getTasks()) {
        if (task.isSingle()) {
            elements.push_back(text("- " + task.getDesc()));
        } else {
            // Render nested list with indent
            TaskList* nested = task.getTaskList();
            if (nested) {
                std::vector<Element> nestedElements;
                for (const auto& subtask : nested->getTasks()) {
                    nestedElements.push_back(text("  * " + subtask.getDesc()));
                }
                elements.push_back(vbox(std::move(nestedElements)));
            }
        }
    }

    return Renderer([elements]() {
        return vbox(elements) | border | flex;
    });
}

void Listro::UpdateUI() {
    mainComponent = RenderTaskList(masterList);
}

void Listro::run() {
    UpdateUI();
    screen.Loop(mainComponent);
}

