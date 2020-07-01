/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/Layout.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOP GUI : Layout
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
#ifndef CCGOP_FRONTEND_LAYOUT_H
#define CCGOP_FRONTEND_LAYOUT_H

/////////////////////////////////////////////////////////////////////////////////
// Application Window
#define CCGOP_LAYOUT_WINDOW_WIDTH  1600
#define CCGOP_LAYOUT_WINDOW_HEIGHT 960

/////////////////////////////////////////////////////////////////////////////////
// Spacing
#define CCGOP_LAYOUT_SPACING_BORDER 16

#define CCGOP_LAYOUT_SPACING_HORIZ 4
#define CCGOP_LAYOUT_SPACING_VERT  4

#define CCGOP_LAYOUT_SPACING_GAP_HORIZ 16
#define CCGOP_LAYOUT_SPACING_GAP_VERT  16

/////////////////////////////////////////////////////////////////////////////////
// Buttons
#define CCGOP_LAYOUT_BUTTON_WIDTH  120
#define CCGOP_LAYOUT_BUTTON_HEIGHT 24

/////////////////////////////////////////////////////////////////////////////////
// CheckBoxes
#define CCGOP_LAYOUT_CHECKBOX_WIDTH  CCGOP_LAYOUT_BUTTON_WIDTH
#define CCGOP_LAYOUT_CHECKBOX_HEIGHT CCGOP_LAYOUT_BUTTON_HEIGHT

/////////////////////////////////////////////////////////////////////////////////
// Radio Buttons
#define CCGOP_LAYOUT_RADIOBUTTON_WIDTH  CCGOP_LAYOUT_BUTTON_WIDTH
#define CCGOP_LAYOUT_RADIOBUTTON_HEIGHT CCGOP_LAYOUT_BUTTON_HEIGHT

/////////////////////////////////////////////////////////////////////////////////
// ComboBoxes
#define CCGOP_LAYOUT_COMBOBOX_WIDTH        CCGOP_LAYOUT_BUTTON_WIDTH
#define CCGOP_LAYOUT_COMBOBOX_HEIGHT       120 // Fit the dropdown
#define CCGOP_LAYOUT_COMBOBOX_BUTTONHEIGHT 26

/////////////////////////////////////////////////////////////////////////////////
// GroupBoxes
#define CCGOP_LAYOUT_GROUPBOX_PADDING 8

#define CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH  (CCGOP_LAYOUT_BUTTON_WIDTH  + 24)
#define CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT (CCGOP_LAYOUT_BUTTON_HEIGHT + 24)

/////////////////////////////////////////////////////////////////////////////////
// Shift Macros
#define CCGOP_LAYOUT_SHIFT_HORIZ( _num_buttons, _num_combos, _num_gaps ) ( \
	(CCGOP_LAYOUT_BUTTON_WIDTH + CCGOP_LAYOUT_SPACING_HORIZ)   * (_num_buttons) + \
	(CCGOP_LAYOUT_COMBOBOX_WIDTH + CCGOP_LAYOUT_SPACING_HORIZ) * (_num_combos) + \
	CCGOP_LAYOUT_SPACING_GAP_HORIZ                             * (_num_gaps) \
)

#define CCGOP_LAYOUT_SHIFT_VERT( _num_buttons, _num_combos, _num_gaps ) ( \
	(CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT)         * (_num_buttons) + \
	(CCGOP_LAYOUT_COMBOBOX_BUTTONHEIGHT + CCGOP_LAYOUT_SPACING_VERT) * (_num_combos) + \
	CCGOP_LAYOUT_SPACING_GAP_VERT                                    * (_num_gaps) \
)

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_LAYOUT_H

