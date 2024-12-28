/**
 * @file main.cpp
 * @brief Example usage of the MenuMaker library
 *
 * This file demonstrates how to use the MenuMaker library to create a hierarchical
 * console menu system. It shows various features including:
 * - Creating menus with titles and descriptions
 * - Adding items that trigger functions
 * - Creating and nesting submenus
 * - Adding descriptions to menu items
 * - Proper memory management of dynamically allocated menus
 */

#include "menu.h"

void viewRecords() {
    std::cout << "Viewing records...\n";
}

void addRecord() {
    std::cout << "Adding new record...\n";
}

void audioSettings() {
    std::cout << "Adjusting audio settings...\n";
}

void displaySettings() {
    std::cout << "Adjusting display settings...\n";
}

void viewHelp() {
    std::cout << "Displaying help documentation...\n";
}

void about() {
    std::cout << "Record Management System v1.0\n";
}

/**
 * @brief Main function demonstrating MenuMaker usage
 * 
 * Creates a sample application with a main menu and several submenus:
 * - Main Menu
 *   - Start Game
 *   - View Records
 *   - Add Record  
 *   - Settings Menu
 *     - Audio Menu
 *       - Adjust Volume
 *       - Toggle Mute
 *     - Video Menu
 *       - Change Resolution
 *       - Toggle Fullscreen
 *   - Help Menu
 *     - View Help
 *     - About
 */
int main() {
    Menu mainMenu("Record Management System", "Welcome to the Record Management System. Please select an option to continue.");
    
    // Create sub menus
    Menu* settingsMenu = new Menu("Settings", "Configure system preferences");
    Menu* audioMenu = new Menu("Audio Settings");
    Menu* videoMenu = new Menu("Video Settings");
    
    // Add items to the deepest menus
    audioMenu->addItem("Adjust Volume", []() { std::cout << "Adjusting volume...\n"; });
    audioMenu->addItem("Toggle Mute", []() { std::cout << "Toggling mute...\n"; });
    
    videoMenu->addItem("Change Resolution", []() { std::cout << "Changing resolution...\n"; });
    videoMenu->addItem("Toggle Fullscreen", []() { std::cout << "Toggling fullscreen...\n"; });
    
    // Build the menu hierarchy
    settingsMenu->addSubmenu("Audio", audioMenu);
    settingsMenu->addSubmenu("Video", videoMenu);
    
    // Add everything to main menu
    mainMenu.addItem("Start Game", []() { std::cout << "Starting game...\n"; }); 

    Menu helpMenu("Help & Information", "Get help and system information");

    helpMenu.addItem("View Help", viewHelp, "Access user documentation");
    helpMenu.addItem("About", about, "View system information");

    mainMenu.addItem("View Records", viewRecords, "Browse existing records");
    mainMenu.addItem("Add Record", addRecord, "Create a new record entry");
    mainMenu.addSubmenu("Settings", settingsMenu, "Configure system preferences");
    mainMenu.addSubmenu("Help", &helpMenu, "Get help and system information");

    mainMenu.display();

    // Clean up dynamically allocated menus
    delete videoMenu;
    delete audioMenu;
    delete settingsMenu;
    
    return 0;
}
