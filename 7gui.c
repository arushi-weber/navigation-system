#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#include "5location.h"
#include "6navigation.h"
#include "4search.h"

/* GLOBAL MAP */
static struct Location *campusMap = NULL;

/* login widgets */
static GtkWidget *login_window;
static GtkWidget *main_window;
static GtkWidget *username_entry;
static GtkWidget *password_entry;
static GtkWidget *login_status_label;

/* search widgets */
static GtkWidget *search_entry;
static GtkWidget *search_result_label;

/* dropdowns */
static GtkWidget *start_dropdown;
static GtkWidget *end_dropdown;

/* labels */
static GtkWidget *route_result_label;

/* ======================================================
   Build location list for dropdown
   ====================================================== */
static GtkStringList *build_location_list(void) {
    GtkStringList *list = gtk_string_list_new(NULL);
    struct Location *temp = campusMap;
    while (temp) {
        gtk_string_list_append(list, temp->name);
        temp = temp->next;
    }
    return list;
}

/* ======================================================
   Refresh dropdown when map updates
   ====================================================== */
static void refresh_dropdown_list(void) {
    GtkStringList *list = build_location_list();
    gtk_drop_down_set_model(GTK_DROP_DOWN(start_dropdown), G_LIST_MODEL(list));
    gtk_drop_down_set_model(GTK_DROP_DOWN(end_dropdown), G_LIST_MODEL(list));
}

/* ======================================================
   Login
   ====================================================== */
static void on_login_clicked(GtkWidget *w, gpointer data) {
    const char *u = gtk_editable_get_text(GTK_EDITABLE(username_entry));
    const char *p = gtk_editable_get_text(GTK_EDITABLE(password_entry));

    char fu[50], fp[50];
    FILE *file = fopen("signup.txt", "r");

    if (!file) {
        gtk_label_set_text(GTK_LABEL(login_status_label), "No account found!");
        return;
    }

    fscanf(file, "%s %s", fu, fp);
    fclose(file);

    if (strcmp(u, fu) == 0 && strcmp(p, fp) == 0) {
        gtk_window_destroy(GTK_WINDOW(login_window));
        gtk_window_present(GTK_WINDOW(main_window));
    } else {
        gtk_label_set_text(GTK_LABEL(login_status_label), "Wrong username or password");
    }
}

/* ======================================================
   Login Window
   ====================================================== */
static void create_login_window(GtkApplication *app) {

    login_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(login_window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(login_window), 350, 250);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);

    gtk_box_append(GTK_BOX(box), gtk_label_new("Login to Campus Navigator"));

    username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");
    gtk_box_append(GTK_BOX(box), username_entry);

    password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_box_append(GTK_BOX(box), password_entry);

    GtkWidget *btn = gtk_button_new_with_label("Login");
    g_signal_connect(btn, "clicked", G_CALLBACK(on_login_clicked), NULL);
    gtk_box_append(GTK_BOX(box), btn);

    login_status_label = gtk_label_new("");
    gtk_box_append(GTK_BOX(box), login_status_label);

    gtk_window_set_child(GTK_WINDOW(login_window), box);
    gtk_window_present(GTK_WINDOW(login_window));
}

/* ======================================================
   Search Handler
   ====================================================== */
static void on_search_clicked(GtkWidget *w, gpointer d) {
    const char *name = gtk_editable_get_text(GTK_EDITABLE(search_entry));
    if (!name || strlen(name) == 0) {
        gtk_label_set_text(GTK_LABEL(search_result_label), "Enter a location name");
        return;
    }

    struct Location *loc = search(campusMap, name);

    gtk_label_set_text(GTK_LABEL(search_result_label),
                       loc ? "Location found" : "Location not found");
}

/* ======================================================
   MAP BUTTON → PRINT MAP TO TERMINAL
   ====================================================== */
static void on_show_map(GtkWidget *w, gpointer d) {

    printf("\n===============================\n");
    printf("       CAMPUS MAP\n");
    printf("===============================\n\n");

    printMap(campusMap);   // <-- YOUR location module prints properly

    gtk_label_set_text(GTK_LABEL(route_result_label),
                       "Map printed to terminal.");
}

/* ======================================================
   ROUTE BUTTON → PRINT SHORTEST PATH TO TERMINAL
   ====================================================== */
static void on_route_clicked(GtkWidget *w, gpointer d) {

    GObject *o1 = gtk_drop_down_get_selected_item(GTK_DROP_DOWN(start_dropdown));
    GObject *o2 = gtk_drop_down_get_selected_item(GTK_DROP_DOWN(end_dropdown));

    if (!o1 || !o2) {
        gtk_label_set_text(GTK_LABEL(route_result_label), "Select both places");
        return;
    }

    const char *start = gtk_string_object_get_string(GTK_STRING_OBJECT(o1));
    const char *end   = gtk_string_object_get_string(GTK_STRING_OBJECT(o2));

    printf("\n========================================\n");
    printf(" SHORTEST PATH: %s → %s\n", start, end);
    printf("========================================\n\n");

    findShortestPath(campusMap, start, end);   // <-- Prints to TERMINAL

    gtk_label_set_text(GTK_LABEL(route_result_label),
                       "Route displayed in terminal.");
}

/* ======================================================
   ADD LOCATION HANDLER
   ====================================================== */
static void on_addloc_confirm(GtkWidget *btn, gpointer data) {

    GtkWidget *popup = g_object_get_data(G_OBJECT(btn), "popup");
    GtkWidget *name  = g_object_get_data(G_OBJECT(btn), "name");
    GtkWidget *conn  = g_object_get_data(G_OBJECT(btn), "conn");
    GtkWidget *dist  = g_object_get_data(G_OBJECT(btn), "dist");

    const char *n = gtk_editable_get_text(GTK_EDITABLE(name));
    const char *c = gtk_editable_get_text(GTK_EDITABLE(conn));
    const char *d = gtk_editable_get_text(GTK_EDITABLE(dist));

    int dv = atoi(d);

    if (strlen(n) > 0 && strlen(c) > 0 && dv > 0) {
        addLocationNamed(&campusMap, n, c, dv);
        refresh_dropdown_list();
        printf("\nAdded: %s connected to %s (%d m)\n", n, c, dv);
    }

    gtk_window_destroy(GTK_WINDOW(popup));
}

/* ======================================================
   ADD LOCATION WINDOW
   ====================================================== */
static void on_add_location(GtkWidget *w, gpointer d) {

    GtkWidget *popup = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(popup), "Add Location");
    gtk_window_set_default_size(GTK_WINDOW(popup), 300, 250);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);
    gtk_widget_set_margin_top(box, 20);

    GtkWidget *name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name),"Location Name");

    GtkWidget *conn = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(conn),"Connect To");

    GtkWidget *dist = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(dist),"Distance (m)");

    GtkWidget *btn = gtk_button_new_with_label("Add");

    gtk_box_append(GTK_BOX(box), gtk_label_new("Location name:"));
    gtk_box_append(GTK_BOX(box), name);
    gtk_box_append(GTK_BOX(box), gtk_label_new("Connect to:"));
    gtk_box_append(GTK_BOX(box), conn);
    gtk_box_append(GTK_BOX(box), gtk_label_new("Distance (m):"));
    gtk_box_append(GTK_BOX(box), dist);
    gtk_box_append(GTK_BOX(box), btn);

    g_object_set_data(G_OBJECT(btn),"popup", popup);
    g_object_set_data(G_OBJECT(btn),"name", name);
    g_object_set_data(G_OBJECT(btn),"conn", conn);
    g_object_set_data(G_OBJECT(btn),"dist", dist);

    g_signal_connect(btn,"clicked",G_CALLBACK(on_addloc_confirm),NULL);

    gtk_window_set_child(GTK_WINDOW(popup), box);
    gtk_window_present(GTK_WINDOW(popup));
}

/* ======================================================
   MAIN WINDOW
   ====================================================== */
static void create_main_window(GtkApplication *app) {

    main_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(main_window), "Campus Navigation");
    gtk_window_set_default_size(GTK_WINDOW(main_window), 500, 450);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 16);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);
    gtk_widget_set_margin_top(box, 20);

    gtk_box_append(GTK_BOX(box), gtk_label_new("Campus Navigation System"));

    /* Search */
    search_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_entry),"Enter location name");
    gtk_box_append(GTK_BOX(box), search_entry);

    GtkWidget *sb = gtk_button_new_with_label("Search");
    g_signal_connect(sb,"clicked",G_CALLBACK(on_search_clicked),NULL);
    gtk_box_append(GTK_BOX(box), sb);

    search_result_label = gtk_label_new("");
    gtk_box_append(GTK_BOX(box), search_result_label);

    /* Route Selection */
    GtkStringList *list = build_location_list();
    start_dropdown = gtk_drop_down_new(G_LIST_MODEL(list), 0);
    end_dropdown   = gtk_drop_down_new(G_LIST_MODEL(list), 0);

    gtk_box_append(GTK_BOX(box), start_dropdown);
    gtk_box_append(GTK_BOX(box), end_dropdown);

    GtkWidget *rb = gtk_button_new_with_label("Find Shortest Path");
    g_signal_connect(rb,"clicked",G_CALLBACK(on_route_clicked),NULL);
    gtk_box_append(GTK_BOX(box), rb);

    route_result_label = gtk_label_new("");
    gtk_box_append(GTK_BOX(box), route_result_label);

    /* Map */
    GtkWidget *mapbtn = gtk_button_new_with_label("Show Map");
    g_signal_connect(mapbtn,"clicked",G_CALLBACK(on_show_map),NULL);
    gtk_box_append(GTK_BOX(box), mapbtn);

    /* Add Location */
    GtkWidget *addbtn = gtk_button_new_with_label("Add Location");
    g_signal_connect(addbtn,"clicked",G_CALLBACK(on_add_location),NULL);
    gtk_box_append(GTK_BOX(box), addbtn);

    gtk_window_set_child(GTK_WINDOW(main_window), box);
}

/* ======================================================
   ACTIVATE
   ====================================================== */
static void on_activate(GtkApplication *app, gpointer data) {
    create_main_window(app);
    create_login_window(app);
}

/* ======================================================
   PUBLIC ENTRY
   ====================================================== */
void launch_gui(struct Location *map) {

    campusMap = map;

    GtkApplication *app =
        gtk_application_new("com.campus.navigation.system",
                            G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app,"activate",G_CALLBACK(on_activate),NULL);

    g_application_run(G_APPLICATION(app),0,NULL);
    g_object_unref(app);
}
