/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/Layout.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOP GUI : Rune Explorer Layout
/////////////////////////////////////////////////////////////////////////////////
// Part of Scarab-Engine, licensed under the
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Header prelude
#ifndef CCGOP_FRONTEND_RUNEEXPLORER_LAYOUT_H
#define CCGOP_FRONTEND_RUNEEXPLORER_LAYOUT_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "../Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Rune Table
#define CCGOP_LAYOUT_RUNEEXPLORER_TABLE_WIDTH  (CCGOP_LAYOUT_CLIENT_WIDTH - 2 * CCGOP_LAYOUT_SPACING_BORDER)
#define CCGOP_LAYOUT_RUNEEXPLORER_TABLE_HEIGHT (CCGOP_LAYOUT_CLIENT_HEIGHT - 2 * CCGOP_LAYOUT_SPACING_BORDER - 410) // This one is a choice (setup for 24 item rows in the table)

/////////////////////////////////////////////////////////////////////////////////
// Available Room (Client Area - Table)
#define CCGOP_LAYOUT_RUNEEXPLORER_ROOM_WIDTH  CCGOP_LAYOUT_RUNEEXPLORER_TABLE_WIDTH
#define CCGOP_LAYOUT_RUNEEXPLORER_ROOM_HEIGHT (CCGOP_LAYOUT_CLIENT_HEIGHT - 2 * CCGOP_LAYOUT_SPACING_BORDER - CCGOP_LAYOUT_RUNEEXPLORER_TABLE_HEIGHT)

#define CCGOP_LAYOUT_RUNEEXPLORER_ROOM_LEFT  CCGOP_LAYOUT_SPACING_BORDER
#define CCGOP_LAYOUT_RUNEEXPLORER_ROOM_RIGHT (CCGOP_LAYOUT_RUNEEXPLORER_ROOM_LEFT + CCGOP_LAYOUT_RUNEEXPLORER_ROOM_WIDTH)

#define CCGOP_LAYOUT_RUNEEXPLORER_ROOM_BOTTOM (CCGOP_LAYOUT_CLIENT_HEIGHT - CCGOP_LAYOUT_SPACING_BORDER)
#define CCGOP_LAYOUT_RUNEEXPLORER_ROOM_TOP    (CCGOP_LAYOUT_RUNEEXPLORER_ROOM_BOTTOM - CCGOP_LAYOUT_RUNEEXPLORER_ROOM_HEIGHT)

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RUNEEXPLORER_LAYOUT_H

