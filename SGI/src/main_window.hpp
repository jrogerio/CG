#ifndef VIEW_MAINWINDOW_H_
#define VIEW_MAINWINDOW_H_

#include <gtk/gtk.h>

#include "geometric_object.hpp"
#include "world.hpp"
#include "window.hpp"
#include "matrix.hpp"

class MainWindow {
private:
	GtkBuilder *_definitions;
	World *_world;

	const int MARGIN = 10;
	int _rowCount = 7;

public:

	MainWindow(GtkBuilder *definitions, World *world);
	virtual ~MainWindow();

	void updateViewport();
	void updateRowCount(int newValue);
	
	void drawViewport(cairo_t *cr);
	void drawObjects(cairo_t *cr);
	void drawSingleObject(cairo_t *cr, vector<Coordinate> coords);
	
	Coordinate readCoordFrom(GtkGrid *objGrid, int lineIndicator);
	int rowCount();

	vector<vector<Coordinate> > mapToViewport();
};

#endif /* VIEW_MAINWINDOW_H_ */
