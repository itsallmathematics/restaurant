#ifndef RESTAURANT_H
#define RESTAURANT_H
    #define NAME_LEN 25
    typedef struct _item
    {
        char name[NAME_LEN];
        float price;
    } Item;

    typedef struct _menu
    {
        Item **items;
        int nitems;
        float total;

    } Menu;
    Menu* menu_create(int const nitems);
    int menu_prompt_add_item(const Menu* menu);
    void menu_scan_item_data(Menu* menu, int position);
    Item* menu_add_item(Menu* menu, char name[], float price, int position);
    void menu_display_items(const Menu *menu);
    void menu_destroy(Menu *menu);
    bool str_contains_all_digits(const char *str);
    int san_get_string_int_nonneg(const char *input, int *output);
    bool match_lower(const char *str, const char *comp);
    void menu_calculate_total(Menu *menu);
    void menu_display_total(Menu *menu);
    void payment_handle_total(Menu *menu);
#endif