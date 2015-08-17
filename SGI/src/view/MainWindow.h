/*
 * MainWindow.h
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#ifndef VIEW_MAINWINDOW_H_
#define VIEW_MAINWINDOW_H_

#include <gtk/gtk.h>

class MainWindow {
private:
	void onWindowDestroy(GtkWidget *object, gpointer user_data);

public:
	MainWindow();
	virtual ~MainWindow();
};

#endif /* VIEW_MAINWINDOW_H_ */
