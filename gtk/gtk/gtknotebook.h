/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/. 
 */

#ifndef __GTK_NOTEBOOK_H__
#define __GTK_NOTEBOOK_H__


#include <gdk/gdk.h>
#include <gtk/gtkcontainer.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GTK_TYPE_NOTEBOOK                  (gtk_notebook_get_type ())
#define GTK_NOTEBOOK(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_NOTEBOOK, GtkNotebook))
#define GTK_NOTEBOOK_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_NOTEBOOK, GtkNotebookClass))
#define GTK_IS_NOTEBOOK(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_NOTEBOOK))
#define GTK_IS_NOTEBOOK_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_NOTEBOOK))
#define GTK_NOTEBOOK_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_NOTEBOOK, GtkNotebookClass))


typedef enum
{
  GTK_NOTEBOOK_TAB_FIRST,
  GTK_NOTEBOOK_TAB_LAST
} GtkNotebookTab;

typedef struct _GtkNotebook       GtkNotebook;
typedef struct _GtkNotebookClass  GtkNotebookClass;
typedef struct _GtkNotebookPage   GtkNotebookPage;

struct _GtkNotebook
{
  GtkContainer container;
  
  GtkNotebookPage *cur_page;
  GList *children;
  GList *first_tab;		/* The first tab visible (for scrolling notebooks) */
  GList *focus_tab;
  
  GtkWidget *menu;
  GdkWindow *event_window;
  
  guint32 timer;
  
  guint16 tab_hborder;
  guint16 tab_vborder;
  
  guint show_tabs          : 1;
  guint homogeneous        : 1;
  guint show_border        : 1;
  guint tab_pos            : 2;
  guint scrollable         : 1;
  guint in_child           : 2;
  guint click_child        : 2;
  guint button             : 2;
  guint need_timer         : 1;
  guint child_has_focus    : 1;
  guint have_visible_child : 1;
  guint focus_out          : 1;	/* Flag used by ::move-focus-out implementation */
};

struct _GtkNotebookClass
{
  GtkContainerClass parent_class;
  
  void (* switch_page)       (GtkNotebook     *notebook,
                              GtkNotebookPage *page,
			      guint            page_num);

  /* Action signals for keybindings */
  gboolean (* select_page)     (GtkNotebook       *notebook,
                                gboolean           move_focus);
  gboolean (* focus_tab)       (GtkNotebook       *notebook,
                                GtkNotebookTab     type);
  void (* change_current_page) (GtkNotebook       *notebook,
                                gint               offset);
  void (* move_focus_out)      (GtkNotebook       *notebook,
				GtkDirectionType   direction);

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

/***********************************************************
 *           Creation, insertion, deletion                 *
 ***********************************************************/

GType   gtk_notebook_get_type       (void) G_GNUC_CONST;
GtkWidget * gtk_notebook_new        (void);
void gtk_notebook_append_page       (GtkNotebook *notebook,
				     GtkWidget   *child,
				     GtkWidget   *tab_label);
void gtk_notebook_append_page_menu  (GtkNotebook *notebook,
				     GtkWidget   *child,
				     GtkWidget   *tab_label,
				     GtkWidget   *menu_label);
void gtk_notebook_prepend_page      (GtkNotebook *notebook,
				     GtkWidget   *child,
				     GtkWidget   *tab_label);
void gtk_notebook_prepend_page_menu (GtkNotebook *notebook,
				     GtkWidget   *child,
				     GtkWidget   *tab_label,
				     GtkWidget   *menu_label);
void gtk_notebook_insert_page       (GtkNotebook *notebook,
				     GtkWidget   *child,
				     GtkWidget   *tab_label,
				     gint         position);
void gtk_notebook_insert_page_menu  (GtkNotebook *notebook,
				     GtkWidget   *child,
				     GtkWidget   *tab_label,
				     GtkWidget   *menu_label,
				     gint         position);
void gtk_notebook_remove_page       (GtkNotebook *notebook,
				     gint         page_num);

/***********************************************************
 *            query, set current NoteebookPage             *
 ***********************************************************/

gint       gtk_notebook_get_current_page (GtkNotebook *notebook);
GtkWidget* gtk_notebook_get_nth_page     (GtkNotebook *notebook,
					  gint         page_num);
gint       gtk_notebook_get_n_pages      (GtkNotebook *notebook);
gint       gtk_notebook_page_num         (GtkNotebook *notebook,
					  GtkWidget   *child);
void       gtk_notebook_set_current_page (GtkNotebook *notebook,
					  gint         page_num);
void       gtk_notebook_next_page        (GtkNotebook *notebook);
void       gtk_notebook_prev_page        (GtkNotebook *notebook);

/***********************************************************
 *            set Notebook, NotebookTab style              *
 ***********************************************************/

void     gtk_notebook_set_show_border      (GtkNotebook     *notebook,
					    gboolean         show_border);
gboolean gtk_notebook_get_show_border      (GtkNotebook     *notebook);
void     gtk_notebook_set_show_tabs        (GtkNotebook     *notebook,
					    gboolean         show_tabs);
gboolean gtk_notebook_get_show_tabs        (GtkNotebook     *notebook);
void     gtk_notebook_set_tab_pos          (GtkNotebook     *notebook,
				            GtkPositionType  pos);
GtkPositionType gtk_notebook_get_tab_pos   (GtkNotebook     *notebook);

#ifndef GTK_DISABLE_DEPRECATED
void     gtk_notebook_set_homogeneous_tabs (GtkNotebook     *notebook,
					    gboolean         homogeneous);
void     gtk_notebook_set_tab_border       (GtkNotebook     *notebook,
					    guint            border_width);
void     gtk_notebook_set_tab_hborder      (GtkNotebook     *notebook,
					    guint            tab_hborder);
void     gtk_notebook_set_tab_vborder      (GtkNotebook     *notebook,
					    guint            tab_vborder);
#endif /* GTK_DISABLE_DEPRECATED */

void     gtk_notebook_set_scrollable       (GtkNotebook     *notebook,
					    gboolean         scrollable);
gboolean gtk_notebook_get_scrollable       (GtkNotebook     *notebook);

/***********************************************************
 *               enable/disable PopupMenu                  *
 ***********************************************************/

void gtk_notebook_popup_enable  (GtkNotebook *notebook);
void gtk_notebook_popup_disable (GtkNotebook *notebook);

/***********************************************************
 *             query/set NotebookPage Properties           *
 ***********************************************************/

GtkWidget * gtk_notebook_get_tab_label    (GtkNotebook *notebook,
					   GtkWidget   *child);
void gtk_notebook_set_tab_label           (GtkNotebook *notebook,
					   GtkWidget   *child,
					   GtkWidget   *tab_label);
void gtk_notebook_set_tab_label_text      (GtkNotebook *notebook,
					   GtkWidget   *child,
					   const gchar *tab_text);
G_CONST_RETURN gchar *gtk_notebook_get_tab_label_text (GtkNotebook *notebook,
						       GtkWidget   *child);
GtkWidget * gtk_notebook_get_menu_label   (GtkNotebook *notebook,
					   GtkWidget   *child);
void gtk_notebook_set_menu_label          (GtkNotebook *notebook,
					   GtkWidget   *child,
					   GtkWidget   *menu_label);
void gtk_notebook_set_menu_label_text     (GtkNotebook *notebook,
					   GtkWidget   *child,
					   const gchar *menu_text);
G_CONST_RETURN gchar *gtk_notebook_get_menu_label_text (GtkNotebook *notebook,
							GtkWidget   *child);
void gtk_notebook_query_tab_label_packing (GtkNotebook *notebook,
					   GtkWidget   *child,
					   gboolean    *expand,
					   gboolean    *fill,
					   GtkPackType *pack_type);
void gtk_notebook_set_tab_label_packing   (GtkNotebook *notebook,
					   GtkWidget   *child,
					   gboolean     expand,
					   gboolean     fill,
					   GtkPackType  pack_type);
void gtk_notebook_reorder_child           (GtkNotebook *notebook,
					   GtkWidget   *child,
					   gint         position);

#ifndef GTK_DISABLE_DEPRECATED
#define	gtk_notebook_current_page               gtk_notebook_get_current_page
#define gtk_notebook_set_page                   gtk_notebook_set_current_page
#endif /* GTK_DISABLE_DEPRECATED */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GTK_NOTEBOOK_H__ */
