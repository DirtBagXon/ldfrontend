/*
 * daphne.c
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
#include "daphne.h"


GtkWidget	*window;
GtkWidget	*outerfixed;
GtkWidget	*listfixed;
GtkWidget	*scroll;
GtkWidget	*imageoverlay;
GtkWidget	*start;
GtkWidget	*fullscreen;
GtkWidget	*logobutton;
GtkBuilder	*builder;
GtkWidget	* init_tree();

GtkWidget	*astron;
GtkWidget	*badlands;
GtkWidget	*bega;
GtkWidget	*cliff;
GtkWidget	*cobra;
GtkWidget	*lair;
GtkWidget	*lair2;
GtkWidget	*esh;
GtkWidget	*galaxy;
GtkWidget	*gpworld;
GtkWidget	*interstellar;
GtkWidget	*mach3;
GtkWidget	*roadblaster;
GtkWidget	*ace;
GtkWidget	*blazer;
GtkWidget	*sdq;
GtkWidget	*tq;
GtkWidget	*uvt;

void	image_overlay();
void	run_game(char *GAME);
char	game[32] = GAME_ASTRON;

GtkWidget * init_tree()
{
	GtkListStore *liststore = gtk_list_store_new(1, G_TYPE_STRING);
	GtkTreeIter treeiter;

	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_ASTRON , -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_BADLANDS, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_BEGA, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_CLIFF, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_COBRA, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_LAIR, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_LAIR2, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_ESH, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_GALAXY, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_GPWORLD, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_STELLAR, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_MACH3, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_RB, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_ACE, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_BLAZER, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_SDQ, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_TQ, -1);
	gtk_list_store_append(liststore, &treeiter);
	gtk_list_store_set(liststore, &treeiter, 0, NAME_UVT, -1);

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

	if (strcmp(string, NAME_BADLANDS) == 0) {
		sprintf(game, GAME_BADLANDS);
		graphic = badlands;
	} else if (strcmp(string, NAME_BEGA) == 0) {
		sprintf(game, GAME_BEGA);
		graphic = bega;
	} else if (strcmp(string, NAME_CLIFF) == 0) {
		sprintf(game, GAME_CLIFF);
		graphic = cliff;
	} else if (strcmp(string, NAME_COBRA) == 0) {
		sprintf(game, GAME_COBRA);
		graphic = cobra;
	} else if (strcmp(string, NAME_LAIR) == 0) {
		sprintf(game, GAME_LAIR);
		graphic = lair;
	} else if (strcmp(string, NAME_LAIR2) == 0) {
		sprintf(game, GAME_LAIR2);
		graphic = lair2;
	} else if (strcmp(string, NAME_ESH) == 0) {
		sprintf(game, GAME_ESH);
		graphic = esh;
	} else if (strcmp(string, NAME_GALAXY) == 0) {
		sprintf(game, GAME_GALAXY);
		graphic = galaxy;
	} else if (strcmp(string, NAME_GPWORLD) == 0) {
		sprintf(game, GAME_GPWORLD);
		graphic = gpworld;
	} else if (strcmp(string, NAME_STELLAR) == 0) {
		sprintf(game, GAME_STELLAR);
		graphic = interstellar;
	} else if (strcmp(string, NAME_MACH3) == 0) {
		sprintf(game, GAME_MACH3);
		graphic = mach3;
	} else if (strcmp(string, NAME_RB) == 0) {
		sprintf(game, GAME_RB);
		graphic = roadblaster;
	} else if (strcmp(string, NAME_SDQ) == 0) {
		sprintf(game, GAME_SDQ);
		graphic = sdq;
	} else if (strcmp(string, NAME_ACE) == 0) {
		sprintf(game, GAME_ACE);
		graphic = ace;
	} else if (strcmp(string, NAME_BLAZER) == 0) {
		sprintf(game, GAME_BLAZER);
		graphic = blazer;
	} else if (strcmp(string, NAME_TQ) == 0) {
		sprintf(game, GAME_TQ);
		graphic = tq;
	} else if (strcmp(string, NAME_UVT) == 0) {
		sprintf(game, GAME_UVT);
		graphic = uvt;
	} else {
		sprintf(game, GAME_ASTRON);
		graphic = astron;
	}

	gtk_overlay_reorder_overlay(GTK_OVERLAY (imageoverlay), graphic, -1);
 }

void   image_overlay()
{
	// Reverse order of init_tree()
	// top image goes last..
	uvt= gtk_image_new_from_resource("/daphne/images/uvt.jpg");
	tq = gtk_image_new_from_resource("/daphne/images/tq.jpg");
	sdq = gtk_image_new_from_resource("/daphne/images/sdq.jpg");
	blazer = gtk_image_new_from_resource("/daphne/images/blazer.jpg");
	ace = gtk_image_new_from_resource("/daphne/images/ace.jpg");
	roadblaster = gtk_image_new_from_resource("/daphne/images/roadblaster.jpg");
	mach3 = gtk_image_new_from_resource("/daphne/images/mach3.jpg");
	interstellar = gtk_image_new_from_resource("/daphne/images/interstellar.jpg");
	gpworld = gtk_image_new_from_resource("/daphne/images/gpworld.jpg");
	esh = gtk_image_new_from_resource("/daphne/images/esh.jpg");
	galaxy = gtk_image_new_from_resource("/daphne/images/galaxy.jpg");
	lair2 = gtk_image_new_from_resource("/daphne/images/lair2.jpg");
	lair = gtk_image_new_from_resource("/daphne/images/lair.jpg");
	cobra = gtk_image_new_from_resource("/daphne/images/cobra.jpg");
	cliff = gtk_image_new_from_resource("/daphne/images/cliff.jpg");
	bega = gtk_image_new_from_resource("/daphne/images/bega.jpg");
	badlands = gtk_image_new_from_resource("/daphne/images/badlands.jpg");
	astron = gtk_image_new_from_resource("/daphne/images/astron.jpg");

	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), uvt);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), tq);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), sdq);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), blazer);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), ace);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), roadblaster);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), mach3);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), interstellar);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), gpworld);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), galaxy);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), esh);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), lair2);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), lair);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), cobra);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), cliff);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), bega);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), badlands);
	gtk_overlay_add_overlay (GTK_OVERLAY (imageoverlay), astron);
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	builder = gtk_builder_new_from_resource ("/daphne/daphne.glade");
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

	loadResCSS("/daphne/css/main.css");
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

	if (strcmp(fs, "-fullscreen") != 0 && strcmp(GAME, GAME_TQ) == 0) {

		GtkWidget *image;
		GtkWidget *overlay;
		GtkWidget *keyboard = gtk_window_new(GTK_WINDOW_TOPLEVEL);

		gtk_window_set_title(GTK_WINDOW(keyboard), NAME_TQKB);
		gtk_window_set_position(GTK_WINDOW(keyboard), GTK_WIN_POS_CENTER);
		gtk_window_set_default_size(GTK_WINDOW(keyboard), 595, 234);
		gtk_window_set_resizable(GTK_WINDOW(keyboard), FALSE);

		g_signal_connect(keyboard, "destroy", G_CALLBACK (gtk_widget_destroyed), &keyboard);

		image = gtk_image_new_from_resource("/daphne/images/tq_keyboard.jpg");

		overlay = gtk_overlay_new ();
		gtk_container_add (GTK_CONTAINER (keyboard), overlay);
		gtk_overlay_add_overlay (GTK_OVERLAY (overlay), image);
		gtk_widget_show_all(keyboard);
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
