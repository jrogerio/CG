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
	const char* MAIN_WINDOW = "mainWindow";
	const char* DRAWING_AREA = "drawingArea";
	const char* ADD_OBJ_WINDOW = "addObjectWindow";
	const char* POLYGON_GRID = "polygonGrid";
	const char* BUTTONS_GRID = "buttonsGrid";
	const char* OBJ_NAME = "objName";
	const char* OBJ_NOTEBOOK = "objNotebook";
	const char* OBJ_STORE = "objStore";
	const char* STEP_SPIN_BTN = "stepSpinBtn";
	const char* MOVE_UP_BTN = "btnUp";

	const int MARGIN = 0;

	int rowCount = 7;

	GtkBuilder *builder;
	World *world;


public:

	MainWindow();
	virtual ~MainWindow();

	void connectSignals();

	void addObject();
	Coordinate readCoordFrom(GtkGrid *objGrid, int lineIndicator);

	void drawObjects(cairo_t *cr);
	void drawSingleObject(cairo_t *cr, vector<Coordinate> coords);

	void addCoordComponent();
	void removeCoordComponent();
	GtkWidget* createSpinButton();

	void showAddPopup();
	void closeAddPopup();

	void moveUp();
	void moveDown();

	vector<vector<Coordinate> > mapToViewport();
};

#endif /* VIEW_MAINWINDOW_H_ */
