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
}


MainWindow::MainWindow() {
	GtkWidget *window;
	GtkWidget *btnAddObject;

	// Init builder and loads xml description of ui
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "main.glade", NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "mainWindow"));

	drawingArea = GTK_WIDGET (gtk_builder_get_object (builder, "drawingArea"));
	g_signal_connect (G_OBJECT (drawingArea), "draw",
	                    G_CALLBACK (draw_cb), this);

	btnAddObject = GTK_WIDGET (gtk_builder_get_object (builder, "addObj"));
	g_signal_connect (G_OBJECT(btnAddObject), "clicked",
						G_CALLBACK(add_object_cb), this);

	world = new World();
	//addObjectWindow = new AddObjectWindow(builder);


	popup = GTK_WIDGET (gtk_builder_get_object (builder, "addObjectWindow"));
	g_signal_connect (G_OBJECT(popup), "delete_event",
							G_CALLBACK(gtk_widget_hide_on_delete), NULL);

	polygonGrid = GTK_GRID (gtk_builder_get_object (builder, "polygonGrid"));

	GtkWidget *coordTemplate = GTK_WIDGET (gtk_builder_get_object (builder, "coordTemplate"));
	GtkWidget templateCopy;


	gtk_grid_remove_row(polygonGrid, 2);
	gtk_widget_set_parent_window(coordTemplate, NULL);
	//gtk_widget_set_parent(coordTemplate, NULL);
	std::memcpy(&templateCopy, coordTemplate, sizeof(GtkWidget));
	gtk_widget_set_parent_window(&templateCopy, NULL);

	//GtkWidget *teste = createSpinButton();
	//gtk_widget_set_size_request(teste, 100, 50);
	//gtk_grid_attach(polygonGrid, teste, 0, 0, 1, 1);
	//GtkWidget *btn = gtk_button_new_with_label("TESTE");
	//gtk_grid_remove_row(polygonGrid, 3);
	//gtk_widget_show(btn);
	//gtk_grid_insert_row(polygonGrid, 3);
	//gtk_widget_set_parent_window(&templateCopy, NULL);
	//gtk_grid_attach( polygonGrid , &templateCopy, 0,2,1,1);
	//addCoordComponent();

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
	/*GtkGrid *coordGrid = gtk_grid_new();
	gtk_grid_insert_row(coordGrid, 0);

	for (int i = 0; i < 4; i++) {
		gtk_grid_insert_column(coordGrid, i);
	}

	gtk_grid_attach(coordGrid, GTK_WIDGET( gtk_label_new("X: ") ), 0, 0, 1, 1);
	gtk_grid_attach(coordGrid, GTK_WIDGET( gtk_label_new("Y: ") ), 2, 0, 1, 1);

	gtk_entry_set_placeholder_text(entryX, "0");
	*/

	GtkWidget *teste = createSpinButton();
	gtk_widget_show(teste);
	gtk_grid_attach(polygonGrid, teste, 0, 3, 1, 1);
}

GtkWidget* MainWindow::createSpinButton() {
	GtkAdjustment *adjustment = gtk_adjustment_new(0, -G_MAXDOUBLE, G_MAXDOUBLE, 1, 1, 1);
	return gtk_spin_button_new(adjustment, 1, G_MAXUINT);
}

void MainWindow::showAddObject()
{
	gtk_window_present( GTK_WINDOW(popup) );
}
