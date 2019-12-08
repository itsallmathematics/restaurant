#include "standard.h"

#define NAME_LEN 25
typedef struct _item
{
    char name[NAME_LEN];
    float price;
} Item;

typedef struct _menu
{
    Item **items;
    short nitems;

} Menu;
Menu* create_menu(unsigned short nitems);
short prompt_add_item(Menu* menu);
void scan_item_data(Menu* menu, short position);
Item* add_item(Menu* menu, char name[], float price, short position);
void display_menu_items(Menu *menu);
void menu_destroy(Menu *menu);

//TODO: Change all inputs to string and try convert to other types.
MAIN_V
{
    Menu *menu = create_menu(12);
    short position = prompt_add_item(menu);
    scan_item_data(menu, position);
    position = prompt_add_item(menu);
    scan_item_data(menu, position);
    position = prompt_add_item(menu);
    scan_item_data(menu, position);
    position = prompt_add_item(menu);
    scan_item_data(menu, position);
    display_menu_items(menu);
    menu_destroy(menu);
    RES;
}

Menu* create_menu(unsigned short nitems)
{
    Menu *menu = malloc(sizeof(Menu));
    assert(menu);
    menu->nitems = nitems;
    menu->items = malloc((size_t) nitems*sizeof(Item*));

    size_t i;
    for(i = 0; i < nitems; i++)
    {
        menu->items[i] = NULL;
    }
    return menu;

}

short prompt_add_item(Menu* menu)
{
    assert(menu);
    PS("The following menu position #s are available:");
    short i, position, count = 0;
    for(i = 0; i < menu->nitems; i++)
    {
        if(!menu->items[i])
        {
            printf("%d,", i);
            count++;
        }
    }
    if(!count)
    {
        PS("The menu is full. Remove an item first.");
        return -1;
    }
    PS("Which position # do you want this item to be at?");
    fscanf(stdin,"%hd", &position);
    if(menu->items[position])
    {
        ERR("Error: Menu position not available. Remove item there first.");
        return -1;
    }
    return position;

}

void scan_item_data(Menu* menu, short position)
{
    assert(menu);
    assert(position > 0);
    char name[25];
    float price;
    printf("Adding item at menu position %d...\n", position);
    PS("Enter item name, no more than 25 characters long: ");
    fscanf(stdin,"%s", name);
    PS("Enter price: ");
    fscanf(stdin,"%e", &price);
    add_item(menu, name, price, position);
}

Item* add_item(Menu* menu, char name[], float price, short position)
{
    assert(menu && name);
    if(strlen(name) > NAME_LEN)
    {
        ERR("Cannot add item: name must be 25 characters or less");
        return NULL;
    }
    menu->items[position] = malloc(sizeof(Item));
    assert(menu->items[position]);
    strcpy(menu->items[position]->name, name);
    menu->items[position]->price = price;
    return menu->items[position];
}



void display_menu_items(Menu *menu)
{
    assert(menu);
    short i;
    PS("====Menu Items====");
    for(i = 0; i < menu->nitems; i++)
    {
        if(menu->items[i])
        {
            printf("%d. %s\t%f\n", i, menu->items[i]->name, menu->items[i]->price);
        }
    }
}

void menu_destroy(Menu *menu)
{
    assert(menu);
    short i;
    if(menu->items)
    {
        for(i = 0; i < menu->nitems; i++)
        {
            if(menu->items[i])
            {
                free(menu->items[i]);
                menu->items[i] = NULL;
            }
        }
        free(menu->items);
        menu->items = NULL;
    }
    free(menu);
    menu = NULL;
    return;
}