#ifndef LISTRO_HPP
#define LISTRO_HPP

#include "task.hpp"
 
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Button, Horizontal, Renderer
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/component_options.hpp"   // for ButtonOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for gauge, separator, text, vbox, operator|, Element, border
#include "ftxui/screen/color.hpp"  // for Color, Color::Blue, Color::Green, Color::Red
#include <sqlite3.h>


class Listro {
private:
    TaskList* masterList;

    // UI
    ftxui::ScreenInteractive screen;
    ftxui::Component mainComponent;

    // Render a task list
    ftxui::Component RenderTaskList(TaskList* list);

    // Re-render UI
    void UpdateUI();


public:
    Listro();
    ~Listro();

    // Main loop
    void run();
};

#endif // LISTRO_HPP
