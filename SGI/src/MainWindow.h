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
#include "Window.h"
#include "GraphicObject.h"
#include "AddObjectWindow.h"

class MainWindow {
private:
	int rowCount = 7;

	GtkBuilder *builder;
	GtkWidget *drawingArea;
	int Xvmin, Yvmin, Xvmax, Yvmax;
	World *world;
	Window *window;
	GtkWidget *popup;
	GtkGrid *polygonGrid;
	GtkWidget *buttonsGrid;

	vector<vector<Coordinate> > mapToViewport();

public:

	MainWindow();
	virtual ~MainWindow();

	void addObject();

	void drawObjects(cairo_t *cr);
	void drawSingleObject(cairo_t *cr, vector<Coordinate> coords);

	void addCoordComponent();
	void removeCoordComponent();

	GtkWidget* createSpinButton();

	void showAddPopup();
	void closeAddPopup();
};

#endif /* VIEW_MAINWINDOW_H_ */
