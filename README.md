# MenuMaker

A lightweight C++ library for creating nested console menus with a clean and intuitive interface.

## Features

- Create multi-level nested menus
- Support for menu items with custom actions
- Menu descriptions and item descriptions
- Input validation and error handling
- Clean and intuitive navigation (using numbers)
- Memory-safe implementation

## Usage Example

The following example demonstrates how to create a main menu with a submenu and an action item.

A further and more complex example can be found in the `main.cpp` file.

```cpp

#include "menu.h"

int main() {
    // Create main menu
    Menu mainMenu("Main Menu", "Welcome to the application");

    // Create a submenu
    Menu* settingsMenu = new Menu("Settings");

    // Add items to submenu
    settingsMenu->addItem("Audio Settings", []() {
        std::cout << "Adjusting audio...\n";
    });

    // Add submenu to main menu
    mainMenu.addSubmenu("Settings", settingsMenu);

    // Add direct action to main menu 
    mainMenu.addItem("Start", []() {
        std::cout << "Starting...\n";
    });

    // Display the menu
    mainMenu.display();

    // Clean up
    delete settingsMenu;
    return 0;
}
```

## Building the Project

1. Make sure you have CMake (3.15 or higher) installed
2. Clone the repository
3. Create and navigate to build directory:

```bash
bash
mkdir build && cd build
```

4. Generate build files and compile:

```bash
cmake ..
make
```

5. Run the executable:

```bash
./MenuMaker
```

## Navigation

- Select options by entering their corresponding number
- Enter '0' to go back/exit current menu
- Invalid inputs are handled gracefully

## Requirements

- C++11 compatible compiler
- CMake 3.15 or higher