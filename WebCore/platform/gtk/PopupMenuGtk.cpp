/*
 * This file is part of the popup menu implementation for <select> elements in WebCore.
 *
 * Copyright (C) 2006 Apple Computer, Inc.
 * Copyright (C) 2006 Michael Emmel mike.emmel@gmail.com 
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#include "config.h"
#include "PopupMenu.h"

#include "NotImplemented.h"

#include <stdio.h>
 
namespace WebCore {

PopupMenu::PopupMenu(PopupMenuClient* menuList)
{
    notImplemented();
}

PopupMenu::~PopupMenu()
{
    notImplemented();
}

void PopupMenu::show(const IntRect&, FrameView*, int)
{
    notImplemented();
}

void PopupMenu::hide()
{
    notImplemented();
}

void PopupMenu::updateFromElement() 
{
    notImplemented(); 
}

bool PopupMenu::itemWritingDirectionIsNatural()
{
    return false;
}

}

