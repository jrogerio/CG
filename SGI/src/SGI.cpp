#include <gtk/gtk.h>

#include "MainWindow.h"

int main (int argc, char *argv[])
{
        gtk_init (&argc, &argv);
        new MainWindow();

        return 0;
}
