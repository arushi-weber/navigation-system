#include <gtk/gtk.h>
#include <string.h>
#include "5location.h"
#include "6navigation.h"
#include "4search.h"

static struct Location *campusMap = NULL;

// ---------- Login Globals ----------
static GtkWidget *login_window;
static GtkWidget *nav_window;
static GtkWidget *username_entry;
static GtkWidget *password_entry;
static GtkWidget *login_status_label;

// ---------- Search UI ----------
static GtkWidget *search_entry;
static GtkWidget *search_result_label;

// ---------- Route UI ----------
static GtkWidget *start_combo;
static GtkWidget *end_combo;
static GtkWidget *route_result_label;

// ===============================================
// LOGIN HANDLER
// ===============================================
static void on_login_clicked(GtkWidget *widget, gpointer data) {
    const char *enteredUser = gtk_editable_get_text(GTK_EDITABLE(username_entry));
    const char *enteredPass = gtk_editable_get_text(GTK_EDITABLE(password_entry));

    char storedUser[50], storedPass[50];
    FILE *file = fopen("signup.txt", "r");

    if (!file) {
        gtk_label_set_text(GTK_LABEL(login_status_label), "⚠ No account found.");
        return;
    }

    fscanf(file, "%s %s", storedUser, storedPass);
    fclose(file);

    if (strcmp(enteredUser, storedUser) == 0 && strcmp(enteredPass, storedPass) == 0) {

        gtk_label_set_text(GTK_LABEL(login_status_label), "✔ Login Successful!");

        gtk_window_destroy(GTK_WINDOW(login_window));  // Close login
        gtk_window_present(GTK_WINDOW(nav_window));    // Open main UI

    } else {
        gtk_label_set_text(GTK_LABEL(login_status_label), "❌ Incorrect username or password.");
    }
}

// ===============================================
// CREATE LOGIN WINDOW
// ===============================================
static void create_login_window(GtkApplication *app) {

    login_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(login_window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(login_window), 400, 250);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 20);
    gtk_widget_set_margin_start(box, 20);
    gtk_widget_set_margin_end(box, 20);

    GtkWidget *title = gtk_label_new("🔐 Login to Campus Navigation");

    username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Username");

    password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Password");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);

    GtkWidget *login_button = gtk_button_new_with_label("➡ Login");
    login_status_label = gtk_label_new("");

    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), NULL);

    gtk_box_append(GTK_BOX(box), title);
    gtk_box_append(GTK_BOX(box), username_entry);
    gtk_box_append(GTK_BOX(box), password_entry);
    gtk_box_append(GTK_BOX(box), login_button);
    gtk_box_append(GTK_BOX(box), login_status_label);

    gtk_window_set_child(GTK_WINDOW(login_window), box);
    gtk_window_present(GTK_WINDOW(login_window));
}

// ===============================================
// SEARCH FUNCTION
// ===============================================
static void on_search_clicked(GtkWidget *widget, gpointer data) {
    const char *name = gtk_editable_get_text(GTK_EDITABLE(search_entry));

    if (!name || strlen(name) == 0) {
        gtk_label_set_text(GTK_LABEL(search_result_label), "⚠ Enter location name.");
        return;
    }

    struct Location *loc = search(campusMap, name);
    gtk_label_set_text(GTK_LABEL(search_result_label),
                       loc ? "✅ Found in campus!" : "❌ Not found.");
}

// ===============================================
// ROUTE FUNCTION
// ===============================================
static void fill_locations(GtkComboBoxText *combo) {
    struct Location *tmp = campusMap;
    while (tmp) {
        gtk_combo_box_text_append_text(combo, tmp->name);
        tmp = tmp->next;
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
}

static void on_route_clicked(GtkWidget *widget, gpointer data) {
    const char *start = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(start_combo));
    const char *end   = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(end_combo));

    if (!start || !end) {
        gtk_label_set_text(GTK_LABEL(route_result_label), "⚠ Select both locations!");
        return;
    }

    findShortestPath(campusMap, start, end);
    gtk_label_set_text(GTK_LABEL(route_result_label), "📍 Route shown in console.");
}

// ===============================================
// SHOW MAP
// ===============================================
static void on_show_map(GtkWidget *widget, gpointer data) {
    printMap(campusMap);
}

// ===============================================
// MAIN UI WINDOW
// ===============================================
static void create_navigation_ui(GtkApplication *app) {

    nav_window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(nav_window), "Campus Navigation System");
    gtk_window_set_default_size(GTK_WINDOW(nav_window), 600, 400);


    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(box, 15);
    gtk_widget_set_margin_start(box, 15);
    gtk_widget_set_margin_end(box, 15);

    gtk_box_append(GTK_BOX(box), gtk_label_new("🏫 Campus Navigation System"));

    // Search UI
    gtk_box_append(GTK_BOX(box), gtk_label_new("Search Location:"));
    search_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_entry), "Enter name");
    gtk_box_append(GTK_BOX(box), search_entry);

    GtkWidget *search_button = gtk_button_new_with_label("🔍 Search");
    g_signal_connect(search_button, "clicked", G_CALLBACK(on_search_clicked), NULL);
    gtk_box_append(GTK_BOX(box), search_button);

    search_result_label = gtk_label_new("");
    gtk_box_append(GTK_BOX(box), search_result_label);

    // Route UI
    gtk_box_append(GTK_BOX(box), gtk_label_new("Find Route:"));
    start_combo = gtk_combo_box_text_new();
    end_combo = gtk_combo_box_text_new();

    fill_locations(GTK_COMBO_BOX_TEXT(start_combo));
    fill_locations(GTK_COMBO_BOX_TEXT(end_combo));

    gtk_box_append(GTK_BOX(box), start_combo);
    gtk_box_append(GTK_BOX(box), end_combo);

    GtkWidget *route_button = gtk_button_new_with_label("📍 Find Route");
    g_signal_connect(route_button, "clicked", G_CALLBACK(on_route_clicked), NULL);
    gtk_box_append(GTK_BOX(box), route_button);

    route_result_label = gtk_label_new("");
    gtk_box_append(GTK_BOX(box), route_result_label);

    // Map Button
    GtkWidget *map_button = gtk_button_new_with_label("🗺 Show Full Map");
    g_signal_connect(map_button, "clicked", G_CALLBACK(on_show_map), NULL);
    gtk_box_append(GTK_BOX(box), map_button);

    gtk_window_set_child(GTK_WINDOW(nav_window), box);
}

// ===============================================
// ACTIVATE (Start)
static void on_activate(GtkApplication *app, gpointer data) {

    // Create navigation UI but don’t show yet
    create_navigation_ui(app);

    // Apply CSS SAFELY
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(provider, "style.css");
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );

    // Finally open login window
    create_login_window(app);
}


// ===============================================
// PUBLIC ENTRY FUNCTION
void launch_gui(struct Location *map) {

    campusMap = map;

    GtkApplication *app = gtk_application_new("com.navsystem.gui", G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    int status = g_application_run(G_APPLICATION(app), 0, NULL);

    g_object_unref(app);
}