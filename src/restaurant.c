#include <ctype.h>
#include <limits.h>
#include <math.h>
#include "standard.h"
#include "restaurant.h"

void payment_handle_total(Menu *menu)
{
    assert(menu);
    assert(menu->total);

    PS("Enter amount paid");

    float paid = 0;

    fscanf(stdin, "%f", &paid);

    float change = paid - menu->total;

    if(change > 0)
    {
        printf("Change: %f\n", change);
    }
    else if(!change)
    {
        PS("Have a nice day!");
    }
    else
    {
        printf("You owe %f\n", fabs(change));
    }
    return;
    
}

int menu_prompt_add_item(const Menu* menu)
{
    assert(menu);
    PS("The following menu position #s are available:");
    int i, position, count = 0;
    char position_str[5]; // Do we need a getchar function wrapper to stop before the NULLBYTE?
    for(i = 1; i < menu->nitems; i++)
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
    fscanf(stdin,"%s", position_str);
    position_str[4] = '\0';
    D PS(position_str);
    if(match_lower(position_str, "exit"))
    {
        return -2;
    }
    san_get_string_int_nonneg(position_str, &position);
    if(menu->items[position])
    {
        ERR("Error: Menu position not available. Remove item there first.");
        return -1;
    }
    if(position >= menu->nitems)
    {
        return -1;
    }
    return position;

}

void menu_scan_item_data(Menu* menu, int position)
{
    assert(menu);
    assert(position > 0);
    char name[25];
    float price;
    printf("Adding item at menu position %d...\n", position);
    PS("Enter item name, no more than 25 characters long: ");
    fscanf(stdin,"%s", name);
    PS("Enter price: ");
    fscanf(stdin,"%f", &price);
    menu_add_item(menu, name, price, position);
}

Item* menu_add_item(Menu* menu, char name[], float price, int position)
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



void menu_display_items(const Menu *menu)
{
    assert(menu);
    int i;
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
    int i;
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

// return -1 = fail, 0 = success
int san_get_string_int_nonneg(const char *input, int *output)
{
    assert(input && output);
    if(!str_contains_all_digits(input)) return -1;

    *output = atoi(input);
    if(*output < 0) return -1;
    return 0;
}

bool str_contains_all_digits(const char *str)
{
    assert(str);
    size_t i = 0;
    while(str[i] != '\0')
    {
        if(!(str[i] > 0x2F && str[i] < 0x3A))
        {
            return false;
        }
        i++;
    }
    return true;
}

bool match_lower(const char *str, const char *comp)
{
    assert(str);
    size_t i = 0;
    while(str[i++] != '\0')
    {
        if((char) tolower((int) str[i]) != (int) comp[i]) return false;
    }
    return true;
}

void menu_calculate_total(Menu *menu)
{
    assert(menu);
    size_t i = 0;
    menu->total = 0;
    while(i < menu->nitems)
    {
        if(menu->items[i])
        {
            menu->total += menu->items[i]->price;
        }
        i++;
    }
    return;

}

void menu_display_total(Menu *menu)
{
    assert(menu);

    printf("Total bill: %f\n", menu->total);
    return;
}

Menu* menu_create(int const nitems)
{
    Menu *menu = malloc(sizeof(Menu));
    assert(menu);
    menu->nitems = nitems;
    menu->items = malloc((size_t) nitems*sizeof(Item*));
    menu->total = 0;

    size_t i;
    for(i = 0; i < nitems; i++)
    {
        menu->items[i] = NULL;
    }
    return menu;
}

void get_path(const char *path)
{
    assert(path);
    printf("Enter the path to the menu file: ");
    assert(sizeof(*path) > 50);
    fscanf(stdin, "%s", path);
    return;
}

void ui_display_main_menu(void )
{
    PS("1. Open menu");
    PS("2. New Menu");
    PS("3. Exit");
    return;
}

int ui_prompt_menu_choice(char *choice)
{
    assert(choice);
    int output;
    assert(sizeof(*choice) > 2);
    PS("Enter your choice:");
    fscanf(stdin, "%s", choice);
    choice[2] = '\0';
    return san_get_string_int_nonneg(choice, &output);
}

int menu_open()
{
    
}

void menu_pre_create()
{

}
// First, write Menu struct, then write items into file
int menu_save(const Menu *menu, const char *filename)
{
    assert(menu && menu->items && filename);

    FILE *fp = fopen(filename, "wb");

    fseek(fp, 0, SEEK_SET);
    Item **items = menu->items;
    menu->items = NULL; // We don't save the pointer addresses to the file
    fwrite(menu, sizeof(Menu), 1, fp);
    menu->items = items;

    fseek(fp, sizeof(menu), SEEK_SET); // Move ptr to start writing items list after Menu

    int i;

    for(i = 0; i < menu->nitems; ++i)
    {
        fwrite(*menu->items[i], sizeof(Item), 1, fp);
    }

    fclose(fp);
}