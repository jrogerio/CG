#include <gtk/gtk.h>

#include "MainWindow.hpp"

int main (int argc, char *argv[])
{
        gtk_init (&argc, &argv);
        new MainWindow();

        return 0;
}
