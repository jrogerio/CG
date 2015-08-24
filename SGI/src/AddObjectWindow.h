/*
 * AddObjectWindow.h
 *
 *  Created on: 21 de ago de 2015
 *      Author: joao
 */

#ifndef SRC_ADDOBJECTWINDOW_H_
#define SRC_ADDOBJECTWINDOW_H_

#include <gtk/gtk.h>

class AddObjectWindow {
private:
	GtkWidget *window;
	GtkGrid *polygonGrid;

public:
	AddObjectWindow(GtkBuilder *builder);
	virtual ~AddObjectWindow();

	GObject* g_object_clone(GObject *src);
	void addCoordComponent();
	void showAddObject();
};

#endif /* SRC_ADDOBJECTWINDOW_H_ */
