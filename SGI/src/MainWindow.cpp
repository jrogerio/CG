/*
 * MainWindow.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include <cstdlib>
#include <cstring>

#include "MainWindow.h"

extern "C"
{
	gboolean draw_cb(GtkWidget *widget, cairo_t *cr, MainWindow *window)
	{
		window->drawObjects(cr);

		return FALSE;
	}

	void add_object_cb(GtkWidget *widget, MainWindow *window)
	{
		window->showAddObject();
	}

	void add_coord_cb(GtkWidget *widget, MainWindow *window)
	{
		window->addCoordComponent();
	}

	void remove_coord_cb(GtkWidget *widget, MainWindow *window)
	{
		window->removeCoordComponent();
	}
}


MainWindow::MainWindow() {
	GtkWidget *window;
	GtkWidget *btnAddObject;

	// Init builder and loads xml description of ui
	builder = gtk_builder_new ();
	gtk_builder_add_from_file(builder, "main.glade", NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "mainWindow"));
	buttonsGrid = GTK_WIDGET (gtk_builder_get_object (builder, "buttonsGrid"));

	drawingArea = GTK_WIDGET (gtk_builder_get_object (builder, "drawingArea"));
	g_signal_connect (G_OBJECT (drawingArea), "draw",
	                    G_CALLBACK (draw_cb), this);

	btnAddObject = GTK_WIDGET (gtk_builder_get_object (builder, "addObj"));
	g_signal_connect (G_OBJECT(btnAddObject), "clicked",
						G_CALLBACK(add_object_cb), this);

	GtkWidget *addButton = GTK_WIDGET (gtk_builder_get_object(builder, "addCoord"));
	g_signal_connect (G_OBJECT(addButton), "clicked",
							G_CALLBACK(add_coord_cb), this);

	GtkWidget *removeButton = GTK_WIDGET (gtk_builder_get_object(builder, "removeCoord"));
		g_signal_connect (G_OBJECT(removeButton), "clicked",
								G_CALLBACK(remove_coord_cb), this);

	world = new World();

	popup = GTK_WIDGET (gtk_builder_get_object (builder, "addObjectWindow"));
	g_signal_connect (G_OBJECT(popup), "delete_event",
							G_CALLBACK(gtk_widget_hide_on_delete), NULL);

	polygonGrid = GTK_GRID (gtk_builder_get_object (builder, "polygonGrid"));

	g_object_unref (G_OBJECT (builder));
	gtk_widget_show_all (window);
	gtk_main ();
}

MainWindow::~MainWindow() {
}


void MainWindow::addObject()
{
	//Coordinate begin(10,10);
	//Coordinate end(100,100);

	vector<Coordinate> coords;
	coords.push_back(Coordinate(10,60));
	coords.push_back(Coordinate(60,10));
	coords.push_back(Coordinate(110,60));
	coords.push_back(Coordinate(60,110));
	coords.push_back(Coordinate(110,60));
	coords.push_back(Coordinate(60,110));

	world->addPolygon("teste", coords);
	gtk_widget_queue_draw(drawingArea);
}

void MainWindow::drawObjects(cairo_t *cr) {
	/* Set color for background */
	cairo_set_source_rgb(cr, 1, 1, 1);
	/* fill in the background color*/
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);

	vector<GraphicObject> objects = world->getObjects();

	if (objects.size() > 0) {
		GraphicObject go = objects[0];
		vector<Coordinate> coords = go.coords();

		drawSingleObject(cr, coords);
	}
}

void MainWindow::drawSingleObject(cairo_t *cr, vector<Coordinate> coords) {

	cairo_move_to(cr, coords[0]._x, coords[0]._y);

	for (uint i = 1; i < coords.size(); i++) {
		cairo_line_to(cr, coords[i]._x, coords[i]._y);
	}

	cairo_line_to(cr, coords.front()._x, coords.front()._y);

	cairo_stroke(cr);
}

void MainWindow::addCoordComponent() {
	GtkWidget *coordGrid = gtk_grid_new();
	GtkWidget *labelX = gtk_label_new("X: ");
	GtkWidget *labelY = gtk_label_new("Y: ");
	GtkWidget *entry1 = gtk_entry_new();
	GtkWidget *entry2 = gtk_entry_new();

	gtk_widget_show(labelX);
	gtk_widget_show(labelY);
	gtk_widget_show(entry1);
	gtk_widget_show(entry2);

	gtk_grid_attach( GTK_GRID(coordGrid), labelX, 0,0,1,1);
	gtk_grid_attach(GTK_GRID(coordGrid), entry1, 1,0,1,1);
	gtk_grid_attach(GTK_GRID(coordGrid), labelY, 2,0,1,1);
	gtk_grid_attach(GTK_GRID(coordGrid), entry2, 3,0,1,1);

	gtk_widget_show(coordGrid);

	GtkWidget *coordLabel = gtk_label_new("Coordenada:");
	gtk_widget_show(coordLabel);
	gtk_label_set_justify( GTK_LABEL(coordLabel), GTK_JUSTIFY_LEFT);

	gtk_widget_set_halign(coordLabel, GTK_ALIGN_START);
	gtk_widget_set_margin_left(coordLabel, 5);
	gtk_widget_set_margin_left(labelX, 5);
	gtk_widget_set_margin_left(labelY, 5);

	gtk_grid_insert_next_to(polygonGrid, buttonsGrid, GTK_POS_TOP);
	gtk_grid_insert_next_to(polygonGrid, buttonsGrid, GTK_POS_TOP);

	gtk_grid_attach(polygonGrid, coordLabel, 0, rowCount - 1, 1, 1);
	gtk_grid_attach(polygonGrid, coordGrid, 0, rowCount, 1, 1);

	rowCount += 2;
}

void MainWindow::removeCoordComponent() {
	if (rowCount > 7) {
		gtk_grid_remove_row(polygonGrid, rowCount - 2);
		gtk_grid_remove_row(polygonGrid, rowCount - 3);

		rowCount -= 2;
	}
}

GtkWidget* MainWindow::createSpinButton() {
	GtkAdjustment *adjustment = gtk_adjustment_new(0, -G_MAXDOUBLE, G_MAXDOUBLE, 1, 1, 1);
	return gtk_spin_button_new(adjustment, 1, G_MAXUINT);
}

void MainWindow::showAddObject()
{
	gtk_window_present( GTK_WINDOW(popup) );
}
