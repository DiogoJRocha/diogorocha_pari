/**
 *       @file  myf.c
 *      @brief  Ficheiro com funções auxiliares
 *
 *	Outras funções para os exercicios da aula: isprime, etc...
 *
 *     @author  Diogo Rocha, email@ua.pt
 *
 *   @internal
 *     Created  20-Set-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Diogo Rocha
 *
 * =====================================================================================
 */

#include "myf.h"
#include <gtk/gtk.h>
#include <string.h>

/**
 * @brief  Callback to process the delete_event (usually, window kill request)
 *
 * @param  window - The widget that generated the event (not used here)
 * @param  event - The event description (not used here)
 * @param  data - generic user data (not used here)
 * @return FALSE - destroy window but does not leave gtk_main loop, and generates a "destroy" event that you can intersect with another callback.
 * @return TRUE - ignore this delete_event request and does nothing. This can be used to give a second chance to user before closing window!
 * The same effect of <b>TRUE</b> is obtained by returning no value, that is using a <b>void</b> type of function.
 */

void pari_delete_event(GtkWidget * window, GdkEvent * event, gpointer data)
{
        //puts("Pedido de delete event");
	g_print("You should not use the OS to force leave!\n");
	gtk_main_quit();

        //return FALSE; //destroy window but does not leave gtk_main loop, and generates a "destroy" event
        //return TRUE; //ignore this delete_event request and does nothing. Same effect as returning 'void'
}


/**
 * @brief  Callback to process the "destroy" event
 *
 * Here you can decide whether you keep in the gtk_main loop operation or if you terminate it
 * That is, you can decide to continue with the GUI running or close the GUI, but not necessarily the application
 * Stop the GTK+ main loop function when the window is destroyed.
 * This event only occurs if delete_event returns FALSE
 * @param  window - The widget that generated the event (not used here)
 * @param  data - generic user data (not used here)
 * @return void
 */

void InterceptCTRL_C(int a){

g_print("Sair por CTRL-C\n");
gtk_main_quit(); 


}

/*
static void pari_destroy(GtkWidget * window, gpointer data)
{
        puts("Pedido de destruição de janela");
        gtk_main_quit();  //necessary to to leave GTK main loop
}
*/


/**
 * @brief  Manage button 3 click with the intention to leave application
 *    Either shows a message or exits
 *
 * @param  w - The Widget ID
 * @param user_data - Custom data with the ID of another widget to check. In this case the switch1
 * @return void
 */

/* Estava a dar problemas nesta aula
void on_button2_clicked(GtkWidget * widget, gpointer user_data)
{
  gboolean a=gtk_switch_get_active(user_data); //user_data points to switch (é suposto ter aqui GTK_SWITCH(user_data) em vez de user_data
  if (a == FALSE)
        printf("Must enable the Quit switch before leaving\n");
  else
        gtk_main_quit(); 
}
*/

/**
 * @brief  Function to process the text from entry and label
 *
 * @param widget - the one that originated the call
 * @param user_data - Custom data with a widget ID to fetch some info
 * @return void
 */
void on_button1_clicked(GtkWidget *widget, gpointer user_data)
{
#if 1
  GtkEntry *ts = GTK_ENTRY(user_data); // podia até nem ser preciso colocar GTK_ENTRY, tal como em cima não foi preciso colocar GTK_SWITCH
  GtkLabel *lbl= GTK_LABEL(gtk_builder_get_object(builderG,"label3")); //Get some specific label ID to change it
  if(ts)
  {
        const char* tss = gtk_entry_get_text(ts); //get the text from entry1 widget
	ReverseString((char*)tss);
        printf("Text available in entry1: %s\n", tss);
        gtk_label_set_text(lbl, tss);   //set entry text in "label2" widget

	//gtk_entry_set_text (ts, tss); //esta linha não é precisa para fazer refresh do widget

	gtk_widget_hide( GTK_WIDGET(ts) ); //nestas duas funções é necessário colocar GTK_WIDGET para não dar warning
	gtk_widget_show( GTK_WIDGET(ts) ); 
  }
#endif
}
/*
void ReverseString(char *str)
{
  int n;
  char c;
  char *t1 = str;                       //aux pointer to manage input string up to middle
  char *t2 = str + strlen(str) - 1;     //aux pointer to manage input string after the middle
  for(n = 0; n < strlen(str) >> 1; n++) //perform a loop until the middle of the string >>divide por 2
  {
        c = *t1;        // save current char of first half of string
        *t1++ = *t2;    // copy char from second half of string into first half
        *t2-- = c;      // copy saved char into second half of string
  }
}
*/

void ReverseString(char *str)
{
  char c, *t1, *t2;
  for(t1 = str, t2 = str + strlen(str); t1 < t2;) //notice that 3rd param of for is empty
      c = *t1, *t1++ = *--t2, *t2 = c;
}

CvCapture *pari_StartImageAcquisition()
{
        CvCapture *capture = cvCaptureFromCAM(0);              //Capture using 1st camera: i.e., no. 0
        IplImage *frame=cvQueryFrame(capture);                 //Update frame. Pointer does not change.
        src_imageG = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);//create image for color (8 bits, 3 channels)
        dst_imageG = cvClone(src_imageG);                       //create clone of source image
        return capture;
}

void pari_PerformImageAcquisition(CvCapture *capt)
{
        static IplImage *frame;
        frame=cvQueryFrame(capt);               //Update frame pointer.
        cvCopy(frame, src_imageG, NULL);        //copy frame as it is (preserve color)
        cvCopy(src_imageG, dst_imageG, NULL);   //copy src into dst and ready to process (admitt similar image structure)
}


GdkPixbuf *pari_ConvertOpenCv2Gtk(IplImage * image, int dst_w, int dst_h)
{
    IplImage *gtkMask=image;
    GdkPixbuf *pix, *rpix;
    cvCvtColor(image, gtkMask, CV_BGR2RGB);
    pix = gdk_pixbuf_new_from_data((guchar *) gtkMask->imageData,
                       GDK_COLORSPACE_RGB,
                       FALSE,
                       gtkMask->depth,
                       gtkMask->width,
                       gtkMask->height,
                       gtkMask->widthStep, NULL, NULL);
    rpix = gdk_pixbuf_scale_simple(pix, dst_w, dst_h, GDK_INTERP_BILINEAR); //rescale image
    g_object_unref(pix);  //free the intermediate pixbuf...
    return rpix;
}

//copy from IplImage to pixbuf and paint DA
void pari_RefreshDrawingArea( char * widgetName, IplImage *img)
{
        GtkWidget *da=GTK_WIDGET(gtk_builder_get_object (builderG, widgetName));
        if( ! da )
        {
          printf("failed\n");
          return;
        }
        GdkPixbuf *pix=pari_ConvertOpenCv2Gtk(img, da->allocation.width, da->allocation.height );
        cairo_t *cr = gdk_cairo_create (gtk_widget_get_window(da));
        gdk_cairo_set_source_pixbuf(cr, pix, 0, 0);
        cairo_paint(cr);
        cairo_fill(cr);
        cairo_destroy(cr);
        g_object_unref(pix);  //free the pixbuf...
}

void pari_ProcessUserOperations(IplImage *src, IplImage *dst)
{
}
