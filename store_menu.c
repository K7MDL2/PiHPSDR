/* Copyright (C)
* 2016 - John Melton, G0ORX/N6LYT
* 2016 - Steve Wilson, KA6S
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "new_menu.h"
#include "store_menu.h"
#include "button_text.h"
#include "store.h"

static GtkWidget *parent_window=NULL;

static GtkWidget *dialog=NULL;

GtkWidget *store_button[NUM_OF_MEMORYS];

static void cleanup() {
  if(dialog!=NULL) {
    gtk_widget_destroy(dialog);
    dialog=NULL;
    sub_menu=NULL;
  }
}

static gboolean close_cb (GtkWidget *widget, GdkEventButton *event, gpointer data) {
  cleanup();
  return TRUE;
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
  cleanup();
  return FALSE;
}

static gboolean store_select_cb (GtkWidget *widget, gpointer data) {
   int index = GPOINTER_TO_INT(data);
   fprintf(stderr,"STORE BUTTON PUSHED=%d\n",index);
   char workstr[40];
     
   store_memory_slot(index);

   sprintf(workstr,"M%d=%8.6f MHz", index,((double) mem[index].frequency)/1000000.0);
   gtk_button_set_label(GTK_BUTTON(store_button[index]),workstr);

   return FALSE;
}


static gboolean recall_select_cb (GtkWidget *widget, gpointer data) {
    int index = GPOINTER_TO_INT(data);
    recall_memory_slot(index);
    return FALSE;
}

void store_menu(GtkWidget *parent) {
  GtkWidget *b;
  int i;
  char label_str[50];

  parent_window=parent;

  dialog=gtk_dialog_new();
  gtk_window_set_transient_for(GTK_WINDOW(dialog),GTK_WINDOW(parent_window));
  //gtk_window_set_decorated(GTK_WINDOW(dialog),FALSE);
  gtk_window_set_title(GTK_WINDOW(dialog),"piHPSDR - Store");
  g_signal_connect (dialog, "delete_event", G_CALLBACK (delete_event), NULL);

  GdkRGBA color;
  color.red = 1.0;
  color.green = 1.0;
  color.blue = 1.0;
  color.alpha = 1.0;
  gtk_widget_override_background_color(dialog,GTK_STATE_FLAG_NORMAL,&color);

  GtkWidget *content=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

  GtkWidget *grid=gtk_grid_new();

  gtk_grid_set_column_homogeneous(GTK_GRID(grid),TRUE);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid),TRUE);
  gtk_grid_set_column_spacing (GTK_GRID(grid),5);
  gtk_grid_set_row_spacing (GTK_GRID(grid),5);

  GtkWidget *close_b=gtk_button_new_with_label("Close");
  g_signal_connect (close_b, "pressed", G_CALLBACK(close_cb), NULL);
  gtk_grid_attach(GTK_GRID(grid),close_b,0,0,1,1);

  for(i=0;i<NUM_OF_MEMORYS;i++) {
     sprintf(label_str,"Store M%d",i); 
     b=gtk_button_new_with_label(label_str);
     g_signal_connect(b,"pressed",G_CALLBACK(store_select_cb),(gpointer)(long)i);
     gtk_grid_attach(GTK_GRID(grid),b,2,i,1,1);

     sprintf(label_str,"M%d=%8.6f MHz",i,((double) mem[i].frequency)/1000000.0);
     b=gtk_button_new_with_label(label_str);
     store_button[i]= b;
     g_signal_connect(b,"pressed",G_CALLBACK(recall_select_cb),(gpointer)(long)i);
     gtk_grid_attach(GTK_GRID(grid),b,3,i,1,1);
  }

  gtk_container_add(GTK_CONTAINER(content),grid);

  sub_menu=dialog;

  gtk_widget_show_all(dialog);
}
