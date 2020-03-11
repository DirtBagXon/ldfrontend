/*
 * util.h
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

char	fs[16];
void	on_destroy();
void	loadResCSS(char *CSS);
void	display_error(char *ERROR);
void	on_fullscreen_toggled(GtkToggleButton *b);
void	watch_game(GPid pid, gint status, gpointer user_data);
void	on_logobutton_clicked(GtkButton *b);
void	on_quit_clicked(GtkButton *b);
void	on_start_clicked(GtkButton *b);
const char * check_fd(int fd);
