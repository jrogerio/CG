#include <cstdlib>
#include <cstring>
#include "main_window.hpp"

MainWindow::MainWindow(GtkBuilder *definitions, World *world) {
	_definitions = definitions;
	_world = world;
}

MainWindow::~MainWindow() {}

void MainWindow::updateViewport() {
	GtkWidget *drawingArea = GTK_WIDGET(gtk_builder_get_object(_definitions, "drawingArea"));
	gtk_widget_queue_draw(drawingArea);
}

Coordinate MainWindow::readCoordFrom(GtkGrid *objGrid, int lineIndicator) {
	GtkSpinButton *input;

	// posicao (0,1) -> valor de x
	// posicao (0,3) -> valor de y
	GtkGrid *coordGrid = GTK_GRID( gtk_grid_get_child_at(objGrid, 0, lineIndicator));
	input = GTK_SPIN_BUTTON(gtk_grid_get_child_at(coordGrid, 1, 0));
	int x = gtk_spin_button_get_value(input);

	input = GTK_SPIN_BUTTON(gtk_grid_get_child_at(coordGrid, 3, 0));
	int y = gtk_spin_button_get_value(input);

	return Coordinate(x, y);
}

void MainWindow::drawObjects(cairo_t *cr) {
	/* Set color for background */
	cairo_set_source_rgb(cr, 1, 1, 1);
	/* fill in the background color*/
	cairo_paint(cr);

	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_line_width(cr, 1);

	//vector<GraphicObject> objects = world->getObjects();
	vector< vector<Coordinate> > objects = mapToViewport();

	if (objects.size() > 0) {
		for (uint i = 0; i < objects.size(); ++i) {
			//GraphicObject go = objects[i];
			vector<Coordinate> coords = objects[i];

			drawSingleObject(cr, coords);
		}
	}
}

void MainWindow::drawSingleObject(cairo_t *cr, vector<Coordinate> coords) {
	cairo_move_to(cr, coords[0]._x, coords[0]._y);
	cairo_line_to(cr, coords.front()._x, coords.front()._y);

	for (uint i = 1; i < coords.size(); i++) {
		cairo_line_to(cr, coords[i]._x, coords[i]._y);
	}

	if (coords.size() == 1)
		cairo_line_to(cr, coords[0]._x + 1, coords[0]._y + 1);
	else
		cairo_line_to(cr, coords.front()._x, coords.front()._y);

	cairo_stroke(cr);
}

vector<vector<Coordinate>> MainWindow::mapToViewport() {
	vector<vector<Coordinate> > coords;
	vector<GraphicObject> objects = _world->getObjects();

	GtkWidget *drawingArea = GTK_WIDGET(gtk_builder_get_object(_definitions, "drawingArea"));
	Window window = _world->getWindow();

	int Xvmax = gtk_widget_get_allocated_width(drawingArea);
	int Yvmax = gtk_widget_get_allocated_height(drawingArea);

	int x,y;

	for (uint i = 0; i < objects.size(); ++i) {
		vector<Coordinate> newcoords;
		GraphicObject obj = objects[i];

		for (uint j = 0; j < obj.coords().size(); ++j) {
			x = ((obj.coords()[j]._x - (-1))/(2)) * (Xvmax);
			y = (1 - (obj.coords()[j]._y - (-1) )/( 2 )) * (Yvmax);

			newcoords.push_back(Coordinate(x, y));
		}

		coords.push_back(newcoords);
	}

	return coords;
}

void MainWindow::updateRowCount(int newValue) {
	_rowCount = newValue;
}

int MainWindow::rowCount() {
	return _rowCount;
}
