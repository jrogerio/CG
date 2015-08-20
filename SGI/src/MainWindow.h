/*
 * MainWindow.h
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#ifndef VIEW_MAINWINDOW_H_
#define VIEW_MAINWINDOW_H_

#include <gtk/gtk.h>

#include "World.h"
#include "GraphicObject.h"

class MainWindow {
private:
	GtkWidget *drawingArea;
	World *world;

public:

	MainWindow();
	virtual ~MainWindow();

	void addObject();
	void drawObjects(cairo_t *cr);
	void drawSingleObject(cairo_t *cr, vector<Coordinate> coords);
};

#endif /* VIEW_MAINWINDOW_H_ */
