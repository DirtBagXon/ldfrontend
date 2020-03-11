/*
 * actionmax.c
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
#include <assert.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <ctype.h>
#include <sys/mman.h>
#include "../common/util.h"
#include "actionmax.h"

GtkWidget	*window;
GtkWidget	*fixed;
GtkWidget	*quit;
GtkWidget	*ambushalleylaunch;
GtkWidget	*ambushalleyimage;
GtkWidget	*bluethunderlaunch;
GtkWidget	*bluethunderimage;
GtkWidget	*hydrosub2021image;
GtkWidget	*hydrosub2021launch;
GtkWidget	*popsghostlyimage;
GtkWidget	*popsghostlylaunch;
GtkWidget	*sonicfuryimage;
GtkWidget	*sonicfurylaunch;
GtkWidget	*fullscreen;
GtkBuilder	*builder;

static	GdkWindow* G_WINDOW = 0;
static	GdkCursor* G_CURSOR = 0;
void	run_game(char *GAME);

void changecursor()
{
	assert(G_WINDOW != NULL);
	gdk_window_set_cursor(G_WINDOW, G_CURSOR);
}

static void WindowRealize(GtkWidget *window, gpointer data)
{
	G_CURSOR = gdk_cursor_new_for_display(gdk_display_get_default(), GDK_CROSS);
	G_WINDOW = gtk_widget_get_window(window);
}

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv);
	builder = gtk_builder_new_from_resource ("/actionmax/actionmax.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	g_signal_connect(window, "destroy", G_CALLBACK(on_destroy), NULL);
        gtk_builder_connect_signals(builder, NULL);

	fixed			= GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
	ambushalleylaunch	= GTK_WIDGET(gtk_builder_get_object(builder, "ambushalleylaunch"));
	ambushalleyimage	= GTK_WIDGET(gtk_builder_get_object(builder, "ambushalleyimage"));
	bluethunderlaunch	= GTK_WIDGET(gtk_builder_get_object(builder, "bluethunderlaunch"));
	bluethunderimage	= GTK_WIDGET(gtk_builder_get_object(builder, "bluethunderimage"));
	hydrosub2021launch	= GTK_WIDGET(gtk_builder_get_object(builder, "hydrosub2021launch"));
	hydrosub2021image	= GTK_WIDGET(gtk_builder_get_object(builder, "hydrosub2021image"));
	popsghostlylaunch	= GTK_WIDGET(gtk_builder_get_object(builder, "popsghostlylaunch"));
	popsghostlyimage	= GTK_WIDGET(gtk_builder_get_object(builder, "popsghostlyimage"));
	sonicfurylaunch		= GTK_WIDGET(gtk_builder_get_object(builder, "sonicfurylaunch"));
	sonicfuryimage		= GTK_WIDGET(gtk_builder_get_object(builder, "sonicfuryimage"));
	fullscreen		= GTK_WIDGET(gtk_builder_get_object(builder, "fullscreen"));
	quit			= GTK_WIDGET(gtk_builder_get_object(builder, "quit"));

	g_object_unref(builder);
	gtk_window_set_keep_above (GTK_WINDOW(window), FALSE);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	g_signal_connect(window, "realize", G_CALLBACK(WindowRealize), NULL);

	loadResCSS("/actionmax/css/main.css");
	gtk_widget_set_name(quit, "quit_button");
	gtk_widget_set_name(ambushalleylaunch, "shadow");
	gtk_widget_set_name(bluethunderlaunch, "shadow");
	gtk_widget_set_name(hydrosub2021launch, "shadow");
	gtk_widget_set_name(popsghostlylaunch, "shadow");
	gtk_widget_set_name(sonicfurylaunch, "shadow");
	gtk_widget_set_name(ambushalleyimage, "shadow");
	gtk_widget_set_name(bluethunderimage, "shadow");
	gtk_widget_set_name(hydrosub2021image, "shadow");
	gtk_widget_set_name(popsghostlyimage, "shadow");
	gtk_widget_set_name(sonicfuryimage, "shadow");

	gtk_widget_show(window);
	changecursor();
	gtk_main();

	return EXIT_SUCCESS;
}

void    run_game(char *GAME)
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
		sprintf(fs, GAME);
		sprintf(rom, NULL);
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

void	on_ambushalleylaunch_clicked(GtkButton *b) {
	run_game(GAME_AMBUSH);
}

void	on_bluethunderlaunch_clicked(GtkButton *b) {
	run_game(GAME_THUNDER);
}

void	on_hydrosub2021launch_clicked(GtkButton *b) {
	run_game(GAME_HYDRO);
}

void	on_popsghostlylaunch_clicked(GtkButton *b) {
	run_game(GAME_POPS);
}

void	on_sonicfurylaunch_clicked(GtkButton *b) {
	run_game(GAME_SONIC);
}
