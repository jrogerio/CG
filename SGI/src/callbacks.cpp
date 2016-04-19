#include "app.hpp"
#include "clipper.hpp"

extern "C" {
	// General -------------------------------------------------------------------------------

	void close_app_handler(GtkWidget *widget, App *app) {
		gtk_main_quit();
	}

	gboolean draw_handler(GtkWidget *widget, cairo_t *cr, App *app) {
		app->mainWindow->drawViewport(cr);
		app->mainWindow->drawObjects(cr);

		return FALSE;
	}

	void add_object_handler(GtkWidget *widget, App *app) {
		GtkGrid *objGrid;
		GtkWidget *drawingArea = GTK_WIDGET(app_get_ui_element(app, "drawingArea"));
		GtkEntry *objName = GTK_ENTRY(app_get_ui_element(app, "objName"));
		GtkNotebook *objNotebook = GTK_NOTEBOOK(app_get_ui_element(app, "objNotebook"));
		GtkListStore *objStore = GTK_LIST_STORE(app_get_ui_element(app, "objStore"));

		const char* name = gtk_entry_get_text(objName);
		name = (name[0] == '\0') ? "objeto" : name;
		
		int pageIndex = gtk_notebook_get_current_page(GTK_NOTEBOOK(objNotebook));

		switch (pageIndex) {
			case 0:
				// addPoint
				objGrid = GTK_GRID(gtk_notebook_get_nth_page(GTK_NOTEBOOK(objNotebook), pageIndex));
				app->world->addPoint(name, app->mainWindow->readCoordFrom(objGrid, 1));

				break;
			case 1:
				// addLine
				objGrid = GTK_GRID(gtk_notebook_get_nth_page(GTK_NOTEBOOK(objNotebook), pageIndex));
				app->world->addLine(name, app->mainWindow->readCoordFrom(objGrid, 1), 
										  app->mainWindow->readCoordFrom(objGrid, 3));

				break;
			default:
				// addPolygon
				vector<Coordinate> coords;
				objGrid = GTK_GRID(app_get_ui_element(app, "polygonGrid"));
				GtkToggleButton *fillPolygon = GTK_TOGGLE_BUTTON(app_get_ui_element(app, "fillPolygon"));

				for (int i = 2; i < app->mainWindow->rowCount(); i += 2) {
					coords.push_back(app->mainWindow->readCoordFrom(objGrid, i) );
				}

				app->world->addPolygon(name, coords, gtk_toggle_button_get_active(fillPolygon));

				break;
		}

		GtkTreeIter iter;
		gtk_list_store_append(objStore, &iter);
		gtk_list_store_set(objStore, &iter, 0, name, -1);

		gtk_widget_queue_draw(drawingArea);

		GtkWindow *addObjWindow = GTK_WINDOW(app_get_ui_element(app, "addObjectWindow"));
		gtk_window_close(addObjWindow);
	}

	void add_coord_handler(GtkWidget *widget, App *app) {
		GtkGrid *polygonGrid = GTK_GRID(app_get_ui_element(app, "polygonGrid"));
		GtkWidget *buttonsGrid = GTK_WIDGET(app_get_ui_element(app, "buttonsGrid" ) );

		GtkAdjustment *adjustment1 = gtk_adjustment_new(0, -9999999, 9999999, 1, 1, 1);
		GtkAdjustment *adjustment2 = gtk_adjustment_new(0, -9999999, 9999999, 1, 1, 1);

		GtkWidget *coordGrid = gtk_grid_new();
		GtkWidget *labelX = gtk_label_new("X: ");
		GtkWidget *labelY = gtk_label_new("Y: ");
		GtkWidget *entry1 = gtk_spin_button_new(adjustment1, 1, 0);
		GtkWidget *entry2 = gtk_spin_button_new(adjustment2, 1, 0);

		gtk_widget_set_size_request(entry1, 50, -1);
		gtk_widget_set_size_request(entry2, 50, -1);

		gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(entry1), true);
		gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(entry2), true);

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
		gtk_label_set_justify(GTK_LABEL(coordLabel), GTK_JUSTIFY_LEFT);

		gtk_widget_set_halign(coordLabel, GTK_ALIGN_START);
		gtk_widget_set_margin_left(coordLabel, 5);
		gtk_widget_set_margin_left(labelX, 5);
		gtk_widget_set_margin_left(labelY, 5);

		gtk_grid_insert_next_to(polygonGrid, buttonsGrid, GTK_POS_TOP);
		gtk_grid_insert_next_to(polygonGrid, buttonsGrid, GTK_POS_TOP);

		gtk_grid_attach(polygonGrid, coordLabel, 0, app->mainWindow->rowCount() - 1, 1, 1);
		gtk_grid_attach(polygonGrid, coordGrid, 0, app->mainWindow->rowCount(), 1, 1);

		app->mainWindow->updateRowCount(app->mainWindow->rowCount() + 2);
	}

	void remove_coord_handler(GtkWidget *widget, App *app) {
		GtkGrid *polygonGrid = GTK_GRID(app_get_ui_element(app, "polygonGrid"));

		if (app->mainWindow->rowCount() > 7) {
			gtk_grid_remove_row(polygonGrid, app->mainWindow->rowCount() - 2);
			gtk_grid_remove_row(polygonGrid, app->mainWindow->rowCount() - 3);

			app->mainWindow->updateRowCount(app->mainWindow->rowCount() - 2);
		}
	}

	void show_add_popup_handler(GtkWidget *widget, App *app) {
		GtkWindow *addObjWindow = GTK_WINDOW(app_get_ui_element(app, "addObjectWindow"));
		gtk_window_present(addObjWindow);
	}

	void close_add_popup_handler(GtkWidget *widget, App *app) {
		GtkWidget *addObjWindow = GTK_WIDGET(app_get_ui_element(app, "addObjectWindow"));
		gtk_widget_hide_on_delete(addObjWindow);
	}

	void close_no_object_handler(GtkWidget *widget, App *app) {
		GtkWidget *noObject = GTK_WIDGET(app_get_ui_element(app, "noObject"));
		gtk_widget_hide_on_delete(noObject);
	}

	// Movements Handler ----------------------------------------------------------------------

	void move_up_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *stepInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "stepSpinBtn"));
		app->world->moveWindow( VECTOR(0, gtk_spin_button_get_value(stepInput)) );

		app->mainWindow->updateViewport();
	}

	void move_right_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *stepInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "stepSpinBtn"));
		app->world->moveWindow( VECTOR( gtk_spin_button_get_value(stepInput), 0 ) );

		app->mainWindow->updateViewport();
	}
	
	void move_down_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *stepInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "stepSpinBtn"));
		app->world->moveWindow( VECTOR( 0, -gtk_spin_button_get_value(stepInput) ) );

		app->mainWindow->updateViewport();

	}

	void move_left_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *stepInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "stepSpinBtn"));
		app->world->moveWindow( VECTOR( -gtk_spin_button_get_value(stepInput), 0 ) );

		app->mainWindow->updateViewport();
	}

	// Zoom Handler ---------------------------------------------------------------------------

	void zoom_in_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *stepInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "stepSpinBtn"));
		app->world->zoomWindow(gtk_spin_button_get_value(stepInput));

		app->mainWindow->updateViewport();
	}
	void zoom_out_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *stepInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "stepSpinBtn"));
		app->world->zoomWindow(-gtk_spin_button_get_value(stepInput));

		app->mainWindow->updateViewport();
	}

	// Transformations ------------------------------------------------------------------------

	void window_rotate_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *angleInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "windowAngleSpin"));
		app->world->rotateWindow( gtk_spin_button_get_value(angleInput) );

		app->mainWindow->updateViewport();
	}

	void translate_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *xAxisInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "xFactorBtn"));
		GtkSpinButton *yAxisInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "yFactorBtn"));
		GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(app_get_ui_element(app, "objectsList")));
		GtkTreeModel *model;
		GtkTreeIter iter;

		VECTOR deslocation(gtk_spin_button_get_value(xAxisInput), gtk_spin_button_get_value(yAxisInput));

		if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
			gchar *name;
			
			gtk_tree_model_get(model, &iter, 0, &name, -1);
			app->world->translateObject(string(name), deslocation);

			g_free(name);
		} else {
			GtkWindow *noObject = GTK_WINDOW(app_get_ui_element(app, "noObject"));
			gtk_window_present(noObject);
		}

		app->mainWindow->updateViewport();
	}

	void scale_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *xAxisInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "xFactorBtn"));
		GtkSpinButton *yAxisInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "yFactorBtn"));
		GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(app_get_ui_element(app, "objectsList")));
		GtkTreeModel *model;
		GtkTreeIter iter;

		VECTOR factor(gtk_spin_button_get_value(xAxisInput), gtk_spin_button_get_value(yAxisInput));

		if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
			gchar *name;
			
			gtk_tree_model_get(model, &iter, 0, &name, -1);
			app->world->scaleObject(string(name), factor);

			g_free(name);
		} else {
			GtkWindow *noObject = GTK_WINDOW(app_get_ui_element(app, "noObject"));
			gtk_window_present(noObject);
		}

		app->mainWindow->updateViewport();		
	}

	void rotate_handler(GtkWidget *widget, App *app) {
		GtkSpinButton *xAxisInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "xFactorBtn"));
		GtkSpinButton *yAxisInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "yFactorBtn"));
		GtkSpinButton *angleInput = GTK_SPIN_BUTTON(app_get_ui_element(app, "angleBtn"));
		GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(app_get_ui_element(app, "objectsList")));
		GtkToggleButton *rotateUsingCentroid = GTK_TOGGLE_BUTTON(app_get_ui_element(app, "rotateUsingCentroid"));
		GtkTreeModel *model;
		GtkTreeIter iter;

		if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
			gchar *name;
			
			gtk_tree_model_get(model, &iter, 0, &name, -1);

			if(gtk_toggle_button_get_active(rotateUsingCentroid)) {
				app->world->rotateObject(string(name), gtk_spin_button_get_value(angleInput));
			} else {
				Coordinate coordinate(gtk_spin_button_get_value(xAxisInput), gtk_spin_button_get_value(yAxisInput));
				app->world->rotateObject(string(name), gtk_spin_button_get_value(angleInput), coordinate);
			}

			g_free(name);
		} else {
			GtkWindow *noObject = GTK_WINDOW(app_get_ui_element(app, "noObject"));
			gtk_window_present(noObject);
		}

		app->mainWindow->updateViewport();				
	}

	void lb_handler(GtkWidget *widget, App *app) {
		Clipper::clippingFunction = Clipper::liangBarsky;
	}

	void cs_handler(GtkWidget *widget, App *app) {
		Clipper::clippingFunction = Clipper::cohenSutherland;
	}

	// Import/Export ----------------------------------------------------------------------------

	void export_handler(GtkWidget *widget, App *app) {
		GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(app_get_ui_element(app, "textview")));
		GtkTextIter end;

		app->world->exportToObj();

		gtk_text_buffer_get_end_iter(buffer, &end);
		gtk_text_buffer_insert(buffer, &end, "Criado arquivo: export.obj\n", -1);
	}

	void import_handler(GtkWidget *widget, App *app) {
		GtkWidget *dialog;
		GtkListStore *objStore = GTK_LIST_STORE(app_get_ui_element(app, "objStore"));
		GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
		gint response;
		vector<string> objects;
		GtkTreeIter iter;

		dialog = gtk_file_chooser_dialog_new("Importar arquivo", NULL, action, ("_Cancelar"), GTK_RESPONSE_CANCEL, 
											 ("_Importar"), GTK_RESPONSE_ACCEPT, NULL);

		response = gtk_dialog_run(GTK_DIALOG(dialog));
		if (response == GTK_RESPONSE_ACCEPT) {
			GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
			string filePath = gtk_file_chooser_get_filename(chooser);

			objects = app->world->importFromObj(filePath);
		}

		for(string name : objects) {
			gtk_list_store_append(objStore, &iter);
			gtk_list_store_set(objStore, &iter, 0, name.c_str(), -1);
		}

		app->mainWindow->updateViewport();				

		gtk_widget_destroy(dialog);
	}
}
