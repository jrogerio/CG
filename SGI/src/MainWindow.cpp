/*
 * MainWindow.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include <cstdlib>

#include "MainWindow.h"

extern "C"
{
	gboolean draw_cb(GtkWidget *widget, cairo_t *cr, MainWindow *window)
	{
		window->drawObjects(cr);

	   return FALSE;
	}

	void click_cb(GtkWidget *widget, MainWindow *window)
	{
		window->addObject();
	}
}


MainWindow::MainWindow() {
	GtkBuilder *builder;
	GtkWidget *window;
	GtkWidget *btnAddObject;

	world = new World();

	// Init builder and loads xml description of ui
	builder = gtk_builder_new ();

	gtk_builder_add_from_file (builder, "main.glade", NULL);


	window = GTK_WIDGET (gtk_builder_get_object (builder, "mainWindow"));

	drawingArea = GTK_WIDGET (gtk_builder_get_object (builder, "drawingArea"));
	g_signal_connect (G_OBJECT (drawingArea), "draw",
	                    G_CALLBACK (draw_cb), this);

	btnAddObject = GTK_WIDGET (gtk_builder_get_object (builder, "addObj"));
	g_signal_connect (G_OBJECT(btnAddObject), "clicked",
						G_CALLBACK(click_cb), this);

	gtk_builder_connect_signals (builder, this);
	g_object_unref (G_OBJECT (builder));
	gtk_widget_show (window);
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
