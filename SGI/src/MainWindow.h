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
	const char* MOVE_DOWN_BTN = "btnDown";
	const char* MOVE_LEFT_BTN = "btnLeft";
	const char* MOVE_RIGHT_BTN = "btnRight";
	const char* ZOOM_IN_BTN = "btnZoomIn";
	const char* ZOOM_OUT_BTN = "btnZoomOut";

	const int MARGIN = 0;

	int rowCount = 7;

	GtkBuilder *builder;
	World *world;

	void connectSignals();
	void updateViewport();

public:

	MainWindow();
	virtual ~MainWindow();

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
	void moveLeft();
	void moveRight();
	void zoomIn();
	void zoomOut();

	vector<vector<Coordinate> > mapToViewport();
};

#endif /* VIEW_MAINWINDOW_H_ */
