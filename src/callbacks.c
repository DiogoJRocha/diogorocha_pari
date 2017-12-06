
#include <gtk/gtk.h>
#include "myf.h"


gboolean p_ForceRefreshDA(gpointer user_data)
{
        GtkWidget *da;

//if de segurança caso não se desse sempre user_data
        if( ! user_data)
           da = GTK_WIDGET(gtk_builder_get_object (builderG, "drawingarea1"));
        else
           da=GTK_WIDGET(user_data);

        gtk_widget_queue_draw(da);  //make draw the widget

        return TRUE;  //continue running
}

void p_InitTimer()
{
  //Get widget ID for "drawingarea1"
  GtkWidget *da=GTK_WIDGET(gtk_builder_get_object (builderG, "drawingarea1"));
  //define timeout (timer): interval, callback to execute, and pass the window ID to refresh
  g_timeout_add (200, p_ForceRefreshDA, da); // in miliseconds
}

gboolean pari_UpdateImageAreas(gpointer data)
{
        //generate an expose event (draw event) on drawingarea1
        GtkWidget *da1 = GTK_WIDGET(gtk_builder_get_object(builderG, "drawingarea1"));
        gtk_widget_queue_draw(da1);
        return TRUE;
}

gboolean on_drawingarea1_expose_event(GtkWidget * widget, GdkEvent * event, gpointer user_data)
{
        pari_PerformImageAcquisition(captureG);             //acquire new image
        pari_ProcessUserOperations(src_imageG, dst_imageG); // Perform here the openCV transformations

        //update the drawing area displays
        pari_RefreshDrawingArea("drawingarea1", src_imageG);
        pari_RefreshDrawingArea("drawingarea2", dst_imageG);
        return TRUE;
}



