#include <gtk/gtk.h>

#include "view/MainWindow.h"

int main (int argc, char *argv[])
{
        gtk_init (&argc, &argv);
        new MainWindow();

        return 0;
}
