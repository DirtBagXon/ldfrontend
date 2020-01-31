/*
 * util.c
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
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>

GtkWidget *window;

char    fs[16];
char    game[32];
void    run_game(char *GAME);

void    on_destroy()
{
        gtk_main_quit();
}

void    on_logobutton_clicked(GtkButton *b)
{
	on_destroy();
}

void   on_quit_clicked(GtkButton *b) {
	on_destroy();
}

void    on_start_clicked(GtkButton *b)
{
	run_game(game);
}

void    on_fullscreen_toggled(GtkToggleButton *b)
{
	gboolean F = gtk_toggle_button_get_active(b);
	if (F) sprintf(fs, "-fullscreen");
	else sprintf(fs, NULL);
}

void	display_error(char *ERROR)
{
	GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	GtkWidget *dialog = gtk_message_dialog_new(NULL, flags, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", ERROR);
	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));
	gtk_window_set_title(GTK_WINDOW(dialog), "Error");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy (dialog);
	return;
}

void loadResCSS(char *CSS)
{
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;

	provider = gtk_css_provider_new ();
	display = gdk_display_get_default ();
	screen = gdk_display_get_default_screen (display);
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	gtk_css_provider_load_from_resource(provider, CSS);
	g_object_unref (provider);
}

const char * check_fd(int fd)
{
	char line[1024];
	char buffer[1024];
	char *s_ptr = line;
	ssize_t nbytes = read(fd, buffer, sizeof(buffer));

	if (nbytes <= 0) {
		return "EOF";
	} else {
		sprintf(line, "%.*s\n", (int)nbytes - 1, buffer);
		return s_ptr;
	}
}

void watch_game(GPid pid, gint status, gpointer user_data)
{
	char err_line[1024] = "";
	g_autoptr(GError) game_error = NULL;
	gint fd = GPOINTER_TO_INT(user_data);

	sprintf(err_line, check_fd(fd));
	if (strstr(err_line, "EOF") == NULL) display_error(err_line);

	if (g_spawn_check_exit_status (status, &game_error) != TRUE ) {
		display_error(game_error->message);
	}
	g_spawn_close_pid (pid);
}
