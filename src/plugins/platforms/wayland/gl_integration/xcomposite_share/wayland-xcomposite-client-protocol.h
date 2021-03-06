/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef XCOMPOSITE_CLIENT_PROTOCOL_H
#define XCOMPOSITE_CLIENT_PROTOCOL_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include "wayland-util.h"

struct wl_client;

struct wl_xcomposite;

struct wl_proxy;

extern void
wl_proxy_marshal(struct wl_proxy *p, uint32_t opcode, ...);
extern struct wl_proxy *
wl_proxy_create(struct wl_proxy *factory,
		const struct wl_interface *interface);
extern struct wl_proxy *
wl_proxy_create_for_id(struct wl_display *display,
		       const struct wl_interface *interface, uint32_t id);
extern void
wl_proxy_destroy(struct wl_proxy *proxy);

extern int
wl_proxy_add_listener(struct wl_proxy *proxy,
		      void (**implementation)(void), void *data);

extern void
wl_proxy_set_user_data(struct wl_proxy *proxy, void *user_data);

extern void *
wl_proxy_get_user_data(struct wl_proxy *proxy);

extern const struct wl_interface wl_xcomposite_interface;

struct wl_xcomposite_listener {
	void (*root)(void *data,
		     struct wl_xcomposite *xcomposite,
		     const char *display_name,
		     uint32_t root_window);
};

static inline int
wl_xcomposite_add_listener(struct wl_xcomposite *xcomposite,
			   const struct wl_xcomposite_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) xcomposite,
				     (void (**)(void)) listener, data);
}

#define WL_XCOMPOSITE_CREATE_BUFFER	0

static inline struct wl_xcomposite *
wl_xcomposite_create(struct wl_display *display, uint32_t id)
{
	return (struct wl_xcomposite *)
		wl_proxy_create_for_id(display, &wl_xcomposite_interface, id);
}

static inline void
wl_xcomposite_set_user_data(struct wl_xcomposite *xcomposite, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) xcomposite, user_data);
}

static inline void *
wl_xcomposite_get_user_data(struct wl_xcomposite *xcomposite)
{
	return wl_proxy_get_user_data((struct wl_proxy *) xcomposite);
}

static inline void
wl_xcomposite_destroy(struct wl_xcomposite *xcomposite)
{
	wl_proxy_destroy((struct wl_proxy *) xcomposite);
}

static inline struct wl_buffer *
wl_xcomposite_create_buffer(struct wl_xcomposite *xcomposite, uint32_t x_window, int width, int height, struct wl_visual *visual)
{
	struct wl_proxy *id;

	id = wl_proxy_create((struct wl_proxy *) xcomposite,
			     &wl_buffer_interface);
	if (!id)
		return NULL;

	wl_proxy_marshal((struct wl_proxy *) xcomposite,
			 WL_XCOMPOSITE_CREATE_BUFFER, id, x_window, width, height, visual);

	return (struct wl_buffer *) id;
}

#ifdef  __cplusplus
}
#endif

#endif
