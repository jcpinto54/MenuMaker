#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>

/**
 * @brief A class for creating hierarchical console menus
 * 
 * The Menu class allows creation of nested menus with items that can either
 * trigger actions (functions) or open submenus. Each menu and menu item can
 * have a title/name and description.
 */
class Menu {
private:
    std::string title;        ///< The title displayed at the top of the menu
    std::string description;  ///< Optional description shown below the title

    /**
     * @brief Represents a single menu item that can be either an action or submenu
     */
    struct MenuItem {
        std::string name;        ///< Display name of the menu item
        std::string description; ///< Optional description of the menu item
        union Action {
            void (*func)();      ///< Function pointer for action items
            Menu* submenu;       ///< Pointer to submenu for submenu items
            Action() { func = nullptr; }
            ~Action() { }
        } action;
        bool isSubmenu;          ///< Flag indicating if item is a submenu

        /**
         * @brief Constructor for function-type menu items
         * @param n Item name
         * @param f Function to execute
         * @param desc Optional item description
         */
        MenuItem(const std::string& n, void (*f)(), const std::string& desc = "") 
            : name(n), description(desc), isSubmenu(false) {
            action.func = f;
        }

        /**
         * @brief Constructor for submenu-type menu items
         * @param n Item name
         * @param m Pointer to submenu
         * @param desc Optional item description
         */
        MenuItem(const std::string& n, Menu* m, const std::string& desc = "") 
            : name(n), description(desc), isSubmenu(true) {
            action.submenu = m;
        }
    };
    std::vector<MenuItem> items; ///< Container for all menu items

public:
    /**
     * @brief Constructs a new Menu
     * @param menuTitle Title to display at top of menu
     * @param menuDescription Optional description shown below title
     */
    Menu(const std::string& menuTitle = "Menu", const std::string& menuDescription = "") 
        : title(menuTitle), description(menuDescription) {}

    /**
     * @brief Adds a function-type item to the menu
     * @param name Display name of the item
     * @param action Function to execute when item is selected
     * @param description Optional description of the item
     */
    void addItem(const std::string& name, void (*action)(), const std::string& description = "") {
        items.emplace_back(name, action, description);
    }

    /**
     * @brief Adds a submenu item to the menu
     * @param name Display name of the submenu
     * @param submenu Pointer to the submenu
     * @param description Optional description of the submenu
     */
    void addSubmenu(const std::string& name, Menu* submenu, const std::string& description = "") {
        items.emplace_back(name, submenu, description);
    }

    /**
     * @brief Displays the menu and handles user input
     * 
     * Enters a loop that:
     * 1. Displays the menu title, description, and numbered list of items
     * 2. Prompts for user input
     * 3. Validates input and either:
     *    - Executes the selected function
     *    - Displays the selected submenu
     *    - Shows an error message
     *    - Exits if 0 is entered
     */
    void display() {
        while (true) {
            std::cout << "\n=== " << title << " ===\n";
            if (!description.empty()) {
                std::cout << "\n" <<  description << "\n\n";
            }
            for (size_t i = 0; i < items.size(); i++) {
                std::cout << i + 1 << ". " << items[i].name;
                if (!items[i].description.empty()) {
                    std::cout << " - " << items[i].description;
                }
                std::cout << "\n";
            }
            std::cout << "0. Exit\n";
            std::cout << "Choice: ";
            
            int choice;
            while (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a number.\n";
                std::cout << "Choice: ";
            }
            
            if (choice == 0) break;
            if (choice > 0 && choice <= static_cast<int>(items.size())) {
                const MenuItem& item = items[choice-1];
                if (!item.isSubmenu) {
                    item.action.func();
                } else {
                    item.action.submenu->display();
                }
            } else {
                std::cout << "Invalid choice! Please select a number between 0 and " 
                          << items.size() << ".\n";
            }
        }
    }
};
