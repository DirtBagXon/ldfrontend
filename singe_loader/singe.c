/*
 * singe.c
 *
 * Copyright (C) 2020 DirtBagXon
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#define _GNU_SOURCE

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <ctype.h>
#include <sys/mman.h>
#include "../common/util.h"
#include "singe.h"

GtkWidget	*window;
GtkWidget	*outerfixed;
GtkWidget	*listfixed;
GtkWidget	*scroll;
GtkWidget	*imageoverlay;
GtkWidget	*start;
GtkWidget	*fullscreen;
GtkWidget	*logobutton;
GtkBuilder	*builder;
GtkWidget 	* init_tree();

GtkWidget	*crimepatrol;
GtkWidget	*drugwars;
GtkWidget	*freedomfighter;
GtkWidget	*hayate;
GtkWidget	*maddog;
GtkWidget	*maddog2;
GtkWidget	*lbh;
GtkWidget	*platoon;
GtkWidget	*spacepirates;
GtkWidget	*starblazers;
GtkWidget	*timegal;
GtkWidget	*timetraveler;
GtkWidget	*johnnyrock;

void	image_overlay();
void	run_game(char *GAME);
char	game[32] = GAME_CRIME;

GtkWidget * init_tree()
{
	GtkListStore *liststore = gtk_list_store_new(1, G_TYPE_STRING);
	GtkTreeIter treeiter;

	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0,NAME_CRIME , -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_DRUG, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_FREEDOM, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_LBH, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_MADDOG, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_MADDOG2, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_HAYATE, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_PLATOON, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_PIRATES, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_BLAZERS, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_TIMEGAL, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_TIMETRAV, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_JOHNNY, -1);

	GtkWidget *treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(liststore));
	GtkCellRenderer *cellrenderertext = gtk_cell_renderer_text_new();

	GtkTreeViewColumn *treeviewcolumn = gtk_tree_view_column_new_with_attributes("ROM Image", cellrenderertext, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), treeviewcolumn);

	return treeview;
}

static void selected(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
	GtkWidget *graphic;
	gchar *string;
	GtkTreeIter iter;
	GtkTreeModel *model = gtk_tree_view_get_model (tree_view);
	gtk_tree_model_get_iter(model, &iter, path); 
	gtk_tree_model_get (model, &iter, 0, &string, -1);

	if (strcmp(string, NAME_DRUG) == 0) {
		sprintf(game, GAME_DRUG);
		graphic = drugwars;
	} else if (strcmp(string, NAME_FREEDOM) == 0) {
		sprintf(game, GAME_FREEDOM);
		graphic = freedomfighter;
	} else if (strcmp(string, NAME_LBH) == 0) {
		sprintf(game, GAME_LBH);
		graphic = lbh;
	} else if (strcmp(string, NAME_MADDOG) == 0) {
		sprintf(game, GAME_MADDOG);
		graphic = maddog;
	} else if (strcmp(string, NAME_MADDOG2) == 0) {
		sprintf(game, GAME_MADDOG2);
		graphic = maddog2;
	} else if (strcmp(string, NAME_HAYATE) == 0) {
		sprintf(game, GAME_HAYATE);
		graphic = hayate;
	} else if (strcmp(string, NAME_PLATOON) == 0) {
		sprintf(game, GAME_PLATOON);
		graphic = platoon;
	} else if (strcmp(string, NAME_PIRATES) == 0) {
		sprintf(game, GAME_PIRATES);
		graphic = spacepirates;
	} else if (strcmp(string, NAME_BLAZERS) == 0) {
		sprintf(game, GAME_BLAZERS);
		graphic = starblazers;
	} else if (strcmp(string, NAME_TIMEGAL) == 0) {
		sprintf(game, GAME_TIMEGAL);
		graphic = timegal;
	} else if (strcmp(string, NAME_TIMETRAV) == 0) {
		sprintf(game, GAME_TIMETRAV);
		graphic = timetraveler;
	} else if (strcmp(string, NAME_JOHNNY) == 0) {
		sprintf(game, GAME_JOHNNY);
		graphic = johnnyrock;
	} else {
		sprintf(game, GAME_CRIME);
		graphic = crimepatrol;
	}

	gtk_overlay_reorder_overlay(GTK_OVERLAY (imageoverlay), graphic, -1);
 }

void	image_overlay()
{
	// Reverse order of init_tree()
	// top image goes last..
	johnnyrock = gtk_image_new_from_resource("/singe/images/johnnyrock.jpg");
	timetraveler = gtk_image_new_from_resource("/singe/images/timetraveler.jpg");
	timegal = gtk_image_new_from_resource("/singe/images/timegal.jpg");
	starblazers = gtk_image_new_from_resource("/singe/images/starblazers.jpg");
	spacepirates = gtk_image_new_from_resource("/singe/images/spacepirates.jpg");
	platoon = gtk_image_new_from_resource("/singe/images/platoon.jpg");
	hayate = gtk_image_new_from_resource("/singe/images/hayate.jpg");
	maddog2 = gtk_image_new_from_resource("/singe/images/maddog2.jpg");
	maddog = gtk_image_new_from_resource("/singe/images/maddog.jpg");
	lbh = gtk_image_new_from_resource("/singe/images/lbh.jpg");
	freedomfighter = gtk_image_new_from_resource("/singe/images/freedomfighter.jpg");
	drugwars = gtk_image_new_from_resource("/singe/images/drugwars.jpg");
	crimepatrol = gtk_image_new_from_resource("/singe/images/crimepatrol.jpg");

	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), johnnyrock);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), timetraveler);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), timegal);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), starblazers);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), spacepirates);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), platoon);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), hayate);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), maddog2);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), maddog);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), lbh);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), freedomfighter);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), drugwars);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), crimepatrol);
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	builder = gtk_builder_new_from_resource ("/singe/singe.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);
        gtk_builder_connect_signals(builder, NULL);

	outerfixed		= GTK_WIDGET(gtk_builder_get_object(builder, "outerfixed"));
	listfixed		= GTK_WIDGET(gtk_builder_get_object(builder, "listfixed"));
	scroll			= GTK_WIDGET(gtk_builder_get_object(builder, "scroll"));
	imageoverlay		= GTK_WIDGET(gtk_builder_get_object(builder, "imageoverlay"));
	start			= GTK_WIDGET(gtk_builder_get_object(builder, "start"));
	logobutton		= GTK_WIDGET(gtk_builder_get_object(builder, "logobutton"));
	fullscreen		= GTK_WIDGET(gtk_builder_get_object(builder, "fullscreen"));

	g_object_unref(builder);
	gtk_window_set_keep_above (GTK_WINDOW(window), FALSE);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	image_overlay();
	GtkWidget* list = init_tree();
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(list), TRUE);
	g_signal_connect(list, "row-activated", G_CALLBACK(selected), &game);
	gtk_container_add(GTK_CONTAINER(scroll), list);

	loadResCSS("/singe/css/main.css");
	gtk_widget_set_name(start, "shadow");
	gtk_widget_set_name(logobutton, "logo");
	
	gtk_widget_show_all(window);

	gtk_main();

	return EXIT_SUCCESS;
}

void	run_game(char *GAME)
{
	char cmd[64];
	char rom[32];
	GPid child_pid;
	g_autoptr(GError) error = NULL;
	gint child_stdout, child_stderr;

	if (strlen(SCRIPT_HOME) > 128 || strlen(SCRIPT_NAME) > 64 || strlen(GAME) > 32) {
		display_error("#define values exceed max length in header file..");
		return;
	}

	sprintf(cmd, "./%s", SCRIPT_NAME);
	sprintf(rom, "%s", GAME);

	if (strcmp(fs, "-fullscreen") != 0) {
		sprintf(fs, "%s", GAME);
		rom[0]='\0';
	}

	gchar * argv[] = { cmd, fs, rom, NULL };
	g_spawn_async_with_pipes(SCRIPT_HOME, argv, NULL, G_SPAWN_DO_NOT_REAP_CHILD, NULL,
			NULL, &child_pid, NULL, &child_stdout, &child_stderr, &error);

	if (error != NULL)
	{
		display_error(error->message);
		return;
	}

	gpointer user_ptr = GINT_TO_POINTER(child_stderr);
	g_child_watch_add(child_pid, watch_game, user_ptr);
	return;
}
