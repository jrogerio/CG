/*
 * MainWindow.h
 *
 * Author: plab
 */

#ifndef VIEW_MAINWINDOW_H_
#define VIEW_MAINWINDOW_H_

#include <gtk/gtk.h>

#include "World.hpp"
#include "Window.hpp"
#include "GraphicObject.hpp"
#include "Matrix.hpp"

class MainWindow {
private:
	GtkBuilder *_definitions;
	World *_world;

	const int MARGIN = 0;
	int _rowCount = 7;

public:

	MainWindow(GtkBuilder *definitions, World *world);
	virtual ~MainWindow();

	void updateViewport();
	Coordinate readCoordFrom(GtkGrid *objGrid, int lineIndicator);
	void drawObjects(cairo_t *cr);
	void drawSingleObject(cairo_t *cr, vector<Coordinate> coords);
	void updateRowCount(int newValue);
	int rowCount();

	vector<vector<Coordinate> > mapToViewport();
};

#endif /* VIEW_MAINWINDOW_H_ */
