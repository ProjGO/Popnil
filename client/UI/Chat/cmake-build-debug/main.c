#include <gtk/gtk.h>

extern void list(int argc, char *argv[]);

int main(int argc,char *argv[])
{

    list(&argc, &argv);
    return 0;
}