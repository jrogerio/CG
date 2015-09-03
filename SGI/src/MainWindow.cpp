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
		window->showAddPopup();
	}

	void add_coord_cb(GtkWidget *widget, MainWindow *window)
	{
		window->addCoordComponent();
	}

	void remove_coord_cb(GtkWidget *widget, MainWindow *window)
	{
		window->removeCoordComponent();
	}

	void close_add_popup_cb(GtkWidget *widget, MainWindow *window)
	{
		window->closeAddPopup();
	}

	void add_obj_cb(GtkWidget *widget, MainWindow *window)
	{
		window->addObject();
	}

	void move_up_cb(GtkWidget *widget, MainWindow *window)
	{
		window->moveUp();
	}

//	void move_down_cb(GtkWidget *widget, MainWindow *window)
//	{
//		window->moveUp();
//	}
//
//	void move_left_cb(GtkWidget *widget, MainWindow *window)
//	{
//		window->addObject();
//	}
//
//	void move_right_cb(GtkWidget *widget, MainWindow *window)
//	{
//		window->addObject();
//	}
//
//	void zoom_in_cb(GtkWidget *widget, MainWindow *window)
//	{
//		window->addObject();
//	}
//
//	void zoom_out_cb(GtkWidget *widget, MainWindow *window)
//	{
//		window->addObject();
//	}
}


MainWindow::MainWindow() {
	builder = gtk_builder_new ();
	gtk_builder_add_from_file(builder, "main.glade", NULL);

	world = new World();
	connectSignals();

	GtkWidget *window = GTK_WIDGET (gtk_builder_get_object (builder, MAIN_WINDOW));
	gtk_widget_show_all (window);
	gtk_main ();
}

MainWindow::~MainWindow() {
}

void MainWindow::connectSignals() {
	GtkWidget *drawingArea = GTK_WIDGET (gtk_builder_get_object (builder, "drawingArea"));
	g_signal_connect (G_OBJECT (drawingArea), "draw",
						G_CALLBACK (draw_cb), this);

	GtkWidget *btnAddObject = GTK_WIDGET (gtk_builder_get_object (builder, "addObj"));
	g_signal_connect (G_OBJECT(btnAddObject), "clicked",
						G_CALLBACK(add_object_cb), this);

	GtkWidget *addButton = GTK_WIDGET (gtk_builder_get_object(builder, "addCoord"));
	g_signal_connect (G_OBJECT(addButton), "clicked",
							G_CALLBACK(add_coord_cb), this);

	GtkWidget *removeButton = GTK_WIDGET (gtk_builder_get_object(builder, "removeCoord"));
	g_signal_connect (G_OBJECT(removeButton), "clicked",
							G_CALLBACK(remove_coord_cb), this);

	GtkWidget *cancelButton = GTK_WIDGET (gtk_builder_get_object(builder, "cancelButton"));
	g_signal_connect (G_OBJECT(cancelButton), "clicked",
							G_CALLBACK(close_add_popup_cb), this);

	GtkWidget *okButton = GTK_WIDGET (gtk_builder_get_object(builder, "okButton"));
	g_signal_connect (G_OBJECT(okButton), "clicked",
								G_CALLBACK(add_obj_cb), this);

	GtkWidget *addObjWindow = GTK_WIDGET (gtk_builder_get_object (builder, ADD_OBJ_WINDOW));
	g_signal_connect (G_OBJECT(addObjWindow), "delete_event",
							G_CALLBACK(gtk_widget_hide_on_delete), NULL);

	GtkWidget *moveUpButton = GTK_WIDGET (gtk_builder_get_object (builder, MOVE_UP_BTN));
	g_signal_connect (G_OBJECT(moveUpButton), "clicked",
							G_CALLBACK(move_up_cb), this);
}

void MainWindow::addObject()
{
	GtkGrid *objGrid;
	GtkWidget *drawingArea = GTK_WIDGET( gtk_builder_get_object( builder, DRAWING_AREA ) );
	GtkEntry *objName = GTK_ENTRY( gtk_builder_get_object( builder, OBJ_NAME ) );
	GtkNotebook *objNotebook = GTK_NOTEBOOK( gtk_builder_get_object( builder, OBJ_NOTEBOOK ) );
	GtkListStore *objStore = GTK_LIST_STORE( gtk_builder_get_object( builder, OBJ_STORE ) );

	const char* name = gtk_entry_get_text( objName );
	int pageIndex = gtk_notebook_get_current_page( GTK_NOTEBOOK(objNotebook) );

	switch (pageIndex) {
		case 0:
			// addPoint
			objGrid = GTK_GRID( gtk_notebook_get_nth_page( GTK_NOTEBOOK(objNotebook), pageIndex ) );
			world->addPoint(name, readCoordFrom(objGrid, 1));

			break;
		case 1:
			// addLine
			objGrid = GTK_GRID( gtk_notebook_get_nth_page( GTK_NOTEBOOK(objNotebook), pageIndex ) );
			world->addLine(name, readCoordFrom(objGrid, 1), readCoordFrom(objGrid, 3));

			break;
		default:
			// addPolygon
			vector<Coordinate> coords;
			objGrid = GTK_GRID( gtk_builder_get_object( builder, POLYGON_GRID ) );

			for (int i = 1; i < rowCount; i += 2) {
				coords.push_back( readCoordFrom(objGrid, i) );
			}

			world->addPolygon(name, coords);

			break;
	}

	GtkTreeIter iter;
	gtk_list_store_append(objStore, &iter);
	gtk_list_store_set(  objStore, &iter,
			0, name,
			-1);

	gtk_widget_queue_draw( drawingArea );

	closeAddPopup();
}

Coordinate MainWindow::readCoordFrom(GtkGrid *objGrid, int lineIndicator) {
	GtkSpinButton *input;

	// posicao (0,1) -> valor de x
	// posicao (0,3) -> valor de y
	GtkGrid *coordGrid = GTK_GRID( gtk_grid_get_child_at( objGrid, 0, lineIndicator ) );
	input = GTK_SPIN_BUTTON( gtk_grid_get_child_at( coordGrid, 1, 0 ) );
	int x = gtk_spin_button_get_value(input);

	input = GTK_SPIN_BUTTON( gtk_grid_get_child_at(coordGrid, 3, 0) );
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

void MainWindow::addCoordComponent() {
	GtkGrid *polygonGrid = GTK_GRID( gtk_builder_get_object( builder, POLYGON_GRID ) );
	GtkWidget *buttonsGrid = GTK_WIDGET( gtk_builder_get_object( builder, BUTTONS_GRID ) );

	GtkAdjustment *adjustment1 = gtk_adjustment_new(0, -9999999, 9999999, 1, 1, 1);
	GtkAdjustment *adjustment2 = gtk_adjustment_new(0, -9999999, 9999999, 1, 1, 1);

	GtkWidget *coordGrid = gtk_grid_new();
	GtkWidget *labelX = gtk_label_new("X: ");
	GtkWidget *labelY = gtk_label_new("Y: ");
	GtkWidget *entry1 = gtk_spin_button_new(adjustment1, 1, 0);
	GtkWidget *entry2 = gtk_spin_button_new(adjustment2, 1, 0);

	gtk_widget_set_size_request(entry1, 50, -1);
	gtk_widget_set_size_request(entry2, 50, -1);

	gtk_spin_button_set_numeric( GTK_SPIN_BUTTON(entry1), true );
	gtk_spin_button_set_numeric( GTK_SPIN_BUTTON(entry2), true );

	gtk_widget_show(labelX);
	gtk_widget_show(labelY);
	gtk_widget_show(entry1);
	gtk_widget_show(entry2);

	gtk_grid_attach( GTK_GRID(coordGrid), labelX, 0,0,1,1);
	gtk_grid_attach(GTK_GRID(coordGrid), entry1, 1,0,1,1);
	gtk_grid_attach(GTK_GRID(coordGrid), labelY, 2,0,1,1);
	gtk_grid_attach(GTK_GRID(coordGrid), entry2, 3,0,1,1);

	gtk_widget_show(coordGrid);

	GtkWidget *coordLabel = gtk_label_new("Coordenada:");
	gtk_widget_show(coordLabel);
	gtk_label_set_justify( GTK_LABEL(coordLabel), GTK_JUSTIFY_LEFT);

	gtk_widget_set_halign(coordLabel, GTK_ALIGN_START);
	gtk_widget_set_margin_left(coordLabel, 5);
	gtk_widget_set_margin_left(labelX, 5);
	gtk_widget_set_margin_left(labelY, 5);

	gtk_grid_insert_next_to(polygonGrid, buttonsGrid, GTK_POS_TOP);
	gtk_grid_insert_next_to(polygonGrid, buttonsGrid, GTK_POS_TOP);

	gtk_grid_attach(polygonGrid, coordLabel, 0, rowCount - 1, 1, 1);
	gtk_grid_attach(polygonGrid, coordGrid, 0, rowCount, 1, 1);

	rowCount += 2;
}

void MainWindow::removeCoordComponent() {
	GtkGrid *polygonGrid = GTK_GRID( gtk_builder_get_object( builder, POLYGON_GRID ) );

	if (rowCount > 7) {
		gtk_grid_remove_row(polygonGrid, rowCount - 2);
		gtk_grid_remove_row(polygonGrid, rowCount - 3);

		rowCount -= 2;
	}
}

GtkWidget* MainWindow::createSpinButton() {
	GtkAdjustment *adjustment = gtk_adjustment_new(0, -G_MAXDOUBLE, G_MAXDOUBLE, 1, 1, 1);
	return gtk_spin_button_new(adjustment, 1, G_MAXUINT);
}

void MainWindow::showAddPopup() {
	GtkWindow *addObjWindow = GTK_WINDOW( gtk_builder_get_object( builder, ADD_OBJ_WINDOW ) );
	gtk_window_present( addObjWindow );
}

void MainWindow::closeAddPopup() {
	GtkWindow *addObjWindow = GTK_WINDOW( gtk_builder_get_object( builder, ADD_OBJ_WINDOW ) );
	gtk_window_close( addObjWindow );
}

void MainWindow::moveUp() {
	Window window = world->getWindow();
	window.moveUp(100);

	GtkWidget *drawingArea = GTK_WIDGET( gtk_builder_get_object( builder, DRAWING_AREA ) );
	gtk_widget_queue_draw( drawingArea );
}

void MainWindow::moveDown() {

}

vector<vector<Coordinate> > MainWindow::mapToViewport() {
	vector<vector<Coordinate> > coords;
	vector<GraphicObject> objects = world->getObjects();

	GtkWidget *drawingArea = GTK_WIDGET( gtk_builder_get_object( builder, DRAWING_AREA ) );
	Window window = world->getWindow();

	int Xvmax = gtk_widget_get_allocated_width(drawingArea);
	int Yvmax = gtk_widget_get_allocated_height(drawingArea);

	int x,y;

	for (uint i = 0; i < objects.size(); ++i) {
		vector<Coordinate> newcoords;
		GraphicObject obj = objects[i];

		for (uint j = 0; j < obj.coords().size(); ++j) {
			x = ((obj.coords()[j]._x - window.Xmin())/(window.Xmax() - window.Xmin())) * (Xvmax - MARGIN);
			y = (1 - (obj.coords()[j]._y - window.Ymin())/(window.Ymax() - window.Ymin())) * (Yvmax - MARGIN);

			newcoords.push_back(Coordinate(x, y));
		}

		coords.push_back(newcoords);
	}

	return coords;
}
