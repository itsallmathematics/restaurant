#include "standard.h"
#include <limits.h>
#include <ctype.h>
#include <math.h>
#include "restaurant.h"

#define NAME_LEN 25

MAIN_V
{

    ui_display_main_menu();
    int choice;
    int err = ui_prompt_menu_choice(&choice);

    switch(choice)
    {
        case 1:
        menu_open();
        break;

        case 2:
        menu_pre_create();
        break;

        case 3:
        RES;

        default:
        PS("Enter a choice 1, 2, or 3.");
        REF;


    }
    Menu *menu = menu_create(12);
    int position = menu_prompt_add_item(menu);
    while(1)
    {
        position = menu_prompt_add_item(menu);
        if(position == -2) break;
        menu_scan_item_data(menu, position);
    }
    menu_display_items(menu);
    menu_calculate_total(menu);
    menu_display_total(menu);
    payment_handle_total(menu);
    menu_destroy(menu);
    RES;
}

