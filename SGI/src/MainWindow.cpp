/*
 * MainWindow.cpp
 *
 *  Created on: 17 de ago de 2015
 *      Author: plab
 */

#include "MainWindow.h"

MainWindow::MainWindow() {
	// TODO Auto-generated constructor stub
	GtkBuilder              *builder;
	GtkWidget               *window;
	GError *error = NULL;

	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "main.glade", &error);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "mainWindow"));
	gtk_builder_connect_signals (builder, NULL);
	g_object_unref (G_OBJECT (builder));
	gtk_widget_show (window);
	gtk_main ();
}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

void MainWindow::onWindowDestroy(GtkWidget* object, gpointer user_data)
{
	gtk_main_quit();
}

