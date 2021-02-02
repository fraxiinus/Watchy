#ifndef WATCHY_MENU_H
#define WATCHY_MENU_H

#include "Arduino.h"
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "config.h"

// unique action codes
#define MENU_ACTION_APP 0 // open app action
#define MENU_ACTION_SUB 1 // open submenu action

// data for the individual menu choices
typedef struct menuItem
{
    char* name;                 // the name to display
    uint8_t action;             // define how an entry acts
    uint8_t id;                 // unique within action type, used to differentiate things in the same type
} menuItem;

// data for list of menu choices
typedef struct menuList
{
    const menuList* parent;     // reference to parent menu
    const menuItem* items;
    uint8_t length;             // number of items
    uint8_t parentIndex;        // the menu item this sub menu is under
} menuList;

// data stored in RTC memory
typedef struct menuState
{
    uint8_t menuIndex;
    const menuList* currentMenu;
} menuState;

class Menu
{
    public: // public members
        
    public: // public methods
        Menu(GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT>* displayPtr, int* guiStatePtr, menuState* statePtr);
        void goToMenu(bool goToMain);
        bool goToPreviousMenu();
        uint8_t clickMenuItem();
        void navigate(int movement);
        void drawMenu(const menuItem* items, uint8_t length, uint8_t selectedIndex, bool partialRefresh);
        void drawMenu(const menuList* menu, bool partialRefresh);
    
    private:    // private members
        static GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT>* display;
        static int* guiState;
        static menuState* state;

    private:    // private methods
        const menuList* getSubMenu(uint8_t id);
};

#endif