
/* Copyright (C)
* 2016 - John Melton, G0ORX/N6LYT
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
#include <glib/gprintf.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "new_menu.h"
#include "agc_menu.h"
#include "agc.h"
#include "band.h"
#include "channel.h"
#include "radio.h"
#include "receiver.h"
#include "vfo.h"
#include "button_text.h"
#include "toolbar.h"
#include "actions.h"
#include "action_dialog.h"
#include "gpio.h"
#include "i2c.h"

static GtkWidget *parent_window=NULL;

static GtkWidget *dialog=NULL;

static SWITCH *temp_switches;


static void cleanup() {
  if(dialog!=NULL) {
    gtk_widget_destroy(dialog);
    dialog=NULL;
    active_menu=NO_MENU;
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

static void switch_page_cb(GtkNotebook *notebook,GtkWidget *page,guint page_num,gpointer user_data) {
  temp_switches=switches_controller1[page_num];
}

static gboolean switch_cb(GtkWidget *widget, GdkEvent *event, gpointer data) {
  int sw=GPOINTER_TO_INT(data);
  int action=action_dialog(dialog,CONTROLLER_SWITCH,temp_switches[sw].switch_function);
  gtk_button_set_label(GTK_BUTTON(widget),ActionTable[action].str);
  temp_switches[sw].switch_function=action;
  update_toolbar_labels();
  return TRUE;
}

static void response_event(GtkWidget *mydialog,gint id,gpointer user_data) {
  // mydialog is a copy of dialog
  gtk_widget_destroy(mydialog);
  dialog=NULL;
  active_menu=NO_MENU;
  sub_menu=NULL;
}

void toolbar_menu(GtkWidget *parent) {
  gint row;
  gint col;
  gchar label[64];
  GtkWidget *notebook;
  GtkWidget *grid;
  GtkWidget *widget;
  gint function=0;


  dialog=gtk_dialog_new_with_buttons("piHPSDR - Toolbar Actions",GTK_WINDOW(parent),GTK_DIALOG_DESTROY_WITH_PARENT,"_OK",GTK_RESPONSE_ACCEPT,NULL);
  g_signal_connect (dialog, "response", G_CALLBACK (response_event), NULL);

  GtkWidget *content=gtk_dialog_get_content_area(GTK_DIALOG(dialog));

  function=0;

  notebook=gtk_notebook_new();
 
next_function_set:

  grid=gtk_grid_new();
  gtk_grid_set_column_homogeneous(GTK_GRID(grid),TRUE);
  gtk_grid_set_row_homogeneous(GTK_GRID(grid),FALSE);
  gtk_grid_set_column_spacing (GTK_GRID(grid),0);
  gtk_grid_set_row_spacing (GTK_GRID(grid),0);


  row=0;
  col=0;

  gint max_switches=MAX_SWITCHES;
  max_switches=8;
  temp_switches=switches_controller1[function];

  for(int i=0;i<max_switches;i++) {
    if(temp_switches[i].switch_function==FUNCTION) {
      widget=gtk_button_new_with_label(ActionTable[temp_switches[i].switch_function].str);
      // no signal for Function button
    } else {
      widget=gtk_button_new_with_label(ActionTable[temp_switches[i].switch_function].str);
      g_signal_connect(widget,"button-press-event",G_CALLBACK(switch_cb),GINT_TO_POINTER(i));
    }
    gtk_grid_attach(GTK_GRID(grid),widget,col,row,1,1);
    col++;
  }

  g_sprintf(label,"Function %d",function);
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook),grid,gtk_label_new(label));
  function++;
  if(function<MAX_FUNCTIONS) {
    goto next_function_set;
  }
  gtk_container_add(GTK_CONTAINER(content),notebook);
  g_signal_connect (notebook, "switch-page",G_CALLBACK(switch_page_cb),NULL);

  sub_menu=dialog;

  gtk_widget_show_all(dialog);
}
