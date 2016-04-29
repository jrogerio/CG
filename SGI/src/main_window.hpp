#ifndef VIEW_MAINWINDOW_H_
#define VIEW_MAINWINDOW_H_

#include <gtk/gtk.h>

#include "geometric_object.hpp"
#include "world.hpp"
#include "window.hpp"
#include "matrix.hpp"

struct DrawableObject {

	DrawableObject(bool filled, vector<Coordinate> coords, GeometricObjectType type) :
		_filled(filled), _coords(coords), _type(type) {};

private:
	bool _filled;
	vector<Coordinate> _coords;
	GeometricObjectType _type;

public:
	bool filled() {
		return _filled;
	}

	vector<Coordinate> coords() {
		return _coords;
	}

	GeometricObjectType type() { return _type; }
};

class MainWindow {
private:
	GtkBuilder *_definitions;
	World *_world;

	const int MARGIN = 10;
	int _rowCount = 8;

public:

	MainWindow(GtkBuilder *definitions, World *world);
	virtual ~MainWindow();

	void updateViewport();
	void updateRowCount(int newValue);

	void drawViewport(cairo_t *cr);
	void drawObjects(cairo_t *cr);
	void drawSingleObject(cairo_t *cr, DrawableObject object);

	Coordinate readCoordFrom(GtkGrid *objGrid, int lineIndicator);
	int rowCount();

	vector<DrawableObject> mapToViewport();
};

#endif /* VIEW_MAINWINDOW_H_ */
