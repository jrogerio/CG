/*
 * AddObjectWindow.cpp
 *
 *  Created on: 21 de ago de 2015
 *      Author: joao
 */

#include <cstring>

#include "AddObjectWindow.h"

AddObjectWindow::AddObjectWindow(GtkBuilder * builder) {
	// TODO Auto-generated constructor stub
	window = GTK_WIDGET (gtk_builder_get_object (builder, "addObjectWindow"));
	g_signal_connect (G_OBJECT(window), "delete_event",
							G_CALLBACK(gtk_widget_hide_on_delete), NULL);

	polygonGrid = GTK_GRID (gtk_builder_get_object (builder, "polygonGrid"));
	gtk_grid_insert_row(polygonGrid, 3);

	GtkWidget *ctemplate = GTK_WIDGET (gtk_builder_get_object (builder, "coordTemplate"));
	//GtkWidget *teste = GTK_WIDGET( g_object_clone( ctemplate) );
	gtk_grid_attach(polygonGrid, ctemplate, 0, 3, 1, 1);

	//addCoordComponent();
}

AddObjectWindow::~AddObjectWindow() {
	// TODO Auto-generated destructor stub
}

GObject * AddObjectWindow::g_object_clone(GObject *src) {
    GObject *dst;
    GParameter *params;
    GParamSpec **specs;
    guint n, n_specs, n_params;

    specs = g_object_class_list_properties(G_OBJECT_GET_CLASS(src), &n_specs);
    params = g_new0(GParameter, n_specs);
    n_params = 0;

    for (n = 0; n < n_specs; ++n)
        if (strcmp(specs[n]->name, "parent") &&
            (specs[n]->flags & G_PARAM_READWRITE) == G_PARAM_READWRITE) {
            params[n_params].name = g_intern_string(specs[n]->name);
            g_value_init(&params[n_params].value, specs[n]->value_type);
            g_object_get_property(src, specs[n]->name, &params[n_params].value);
            ++ n_params;
        }

    //dst = g_object_newv(G_TYPE_FROM_INSTANCE(src), n_params, params);
    g_free(specs);
    g_free(params);

    return dst;
}

void AddObjectWindow::addCoordComponent() {
	GtkWidget *frame = gtk_frame_new("Coordenada teste");

	gtk_widget_set_size_request( frame, -1, 50 );
	gtk_grid_attach(polygonGrid, frame, 0, 3, 1, 1);
}

void AddObjectWindow::showAddObject()
{
	gtk_window_present( GTK_WINDOW(window) );
}

