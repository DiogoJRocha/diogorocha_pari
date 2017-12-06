/**
 *       @file  myf.h
 *      @brief  Breve Descrição
 *
 * Descrição mais detalhada do ficheiro que até poderiam incluir links para imagens etc.
 *
 *     @author  Diogo Rocha, email@ua.pt
 *
 *   @internal
 *     Created  27-Set-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Diogo Rocha
 *
 * =====================================================================================
 */
#ifndef _MYF_H
#define _MYF_H

#include <gtk/gtk.h>
#include <cairo.h>
#include <cv.h>
#include <highgui.h>

//no ficheiro myf.h ou similar
#define MAXFFBUFFER 1000
typedef struct {
  int count;
  double x[MAXFFBUFFER];
  double y[MAXFFBUFFER];
} free_form;

//e as variáveis globais sugeridas são:
#if defined (_MAIN_C_)
        GtkBuilder *builderG;
        double xoffG=100;
        double yoffG=150;
        free_form ffG={0};   //init count to zero. Do not affect x and y.
	double fontSizeFactorG=1;

	GtkBuilder *builderG;
        IplImage *dst_imageG , *src_imageG;
        CvCapture *captureG;

#else
        extern GtkBuilder *builderG;
        extern double xoffG;
        extern double yoffG;
        extern free_form ffG;
	extern 	double fontSizeFactorG;

        extern GtkBuilder *builderG;
        extern IplImage *dst_imageG , *src_imageG;
        extern CvCapture *captureG;
#endif

#include "prototypes.h"	

#endif /* _MYF_H */
