/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/Layout.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOP GUI : Global Layout
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
#define CCGOP_LAYOUT_SPACING_BORDER 8

#define CCGOP_LAYOUT_SPACING_HORIZ 4
#define CCGOP_LAYOUT_SPACING_VERT  4

#define CCGOP_LAYOUT_SPACING_GAP_HORIZ 8
#define CCGOP_LAYOUT_SPACING_GAP_VERT  8

/////////////////////////////////////////////////////////////////////////////////
// Tabs
#define CCGOP_LAYOUT_TABS_WIDTH  CCGOP_LAYOUT_WINDOW_WIDTH
#define CCGOP_LAYOUT_TABS_HEIGHT 24

/////////////////////////////////////////////////////////////////////////////////
// Status Bar
#define CCGOP_LAYOUT_STATUSBAR_WIDTH  CCGOP_LAYOUT_WINDOW_WIDTH
#define CCGOP_LAYOUT_STATUSBAR_HEIGHT 26

/////////////////////////////////////////////////////////////////////////////////
// TabPanes Client Area
#define CCGOP_LAYOUT_CLIENT_WIDTH  (CCGOP_LAYOUT_WINDOW_WIDTH - 8)
#define CCGOP_LAYOUT_CLIENT_HEIGHT (CCGOP_LAYOUT_WINDOW_HEIGHT - CCGOP_LAYOUT_TABS_HEIGHT - CCGOP_LAYOUT_STATUSBAR_HEIGHT - 4)

/////////////////////////////////////////////////////////////////////////////////
// Buttons
#define CCGOP_LAYOUT_BUTTON_WIDTH  120
#define CCGOP_LAYOUT_BUTTON_HEIGHT 24

/////////////////////////////////////////////////////////////////////////////////
// CheckBoxes
#define CCGOP_LAYOUT_CHECKBOX_WIDTH  CCGOP_LAYOUT_BUTTON_WIDTH
#define CCGOP_LAYOUT_CHECKBOX_HEIGHT CCGOP_LAYOUT_BUTTON_HEIGHT

/////////////////////////////////////////////////////////////////////////////////
// RadioButtons
#define CCGOP_LAYOUT_RADIOBUTTON_WIDTH  CCGOP_LAYOUT_BUTTON_WIDTH
#define CCGOP_LAYOUT_RADIOBUTTON_HEIGHT CCGOP_LAYOUT_BUTTON_HEIGHT

/////////////////////////////////////////////////////////////////////////////////
// TextEdit
#define CCGOP_LAYOUT_TEXTEDIT_WIDTH  CCGOP_LAYOUT_BUTTON_WIDTH
#define CCGOP_LAYOUT_TEXTEDIT_HEIGHT 20

/////////////////////////////////////////////////////////////////////////////////
// StaticText
#define CCGOP_LAYOUT_STATICTEXT_WIDTH  CCGOP_LAYOUT_TEXTEDIT_WIDTH
#define CCGOP_LAYOUT_STATICTEXT_HEIGHT CCGOP_LAYOUT_TEXTEDIT_HEIGHT

/////////////////////////////////////////////////////////////////////////////////
// ComboBoxes
#define CCGOP_LAYOUT_COMBOBOX_WIDTH        CCGOP_LAYOUT_BUTTON_WIDTH
#define CCGOP_LAYOUT_COMBOBOX_HEIGHT       160 // Fit the dropdown
#define CCGOP_LAYOUT_COMBOBOX_BUTTONHEIGHT 26

/////////////////////////////////////////////////////////////////////////////////
// GroupBoxes
#define CCGOP_LAYOUT_GROUPBOX_PADDING 8

#define CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH  20
#define CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT 20

/////////////////////////////////////////////////////////////////////////////////
// ScrollBars
#define CCGOP_LAYOUT_SCROLLBAR_WIDTH  18
#define CCGOP_LAYOUT_SCROLLBAR_HEIGHT 18

/////////////////////////////////////////////////////////////////////////////////
// Shift Macros
#define CCGOP_LAYOUT_SHIFT_HORIZ( _num_buttons, _num_texts, _num_combos, _num_gaps ) ( \
	(CCGOP_LAYOUT_BUTTON_WIDTH + CCGOP_LAYOUT_SPACING_HORIZ)   * (_num_buttons) + \
	(CCGOP_LAYOUT_TEXTEDIT_WIDTH + CCGOP_LAYOUT_SPACING_HORIZ) * (_num_texts) + \
	(CCGOP_LAYOUT_COMBOBOX_WIDTH + CCGOP_LAYOUT_SPACING_HORIZ) * (_num_combos) + \
	CCGOP_LAYOUT_SPACING_GAP_HORIZ                             * (_num_gaps) \
)

#define CCGOP_LAYOUT_SHIFT_VERT( _num_buttons, _num_texts, _num_combos, _num_gaps ) ( \
	(CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT)         * (_num_buttons) + \
	(CCGOP_LAYOUT_TEXTEDIT_HEIGHT + CCGOP_LAYOUT_SPACING_VERT)       * (_num_texts) + \
	(CCGOP_LAYOUT_COMBOBOX_BUTTONHEIGHT + CCGOP_LAYOUT_SPACING_VERT) * (_num_combos) + \
	CCGOP_LAYOUT_SPACING_GAP_VERT                                    * (_num_gaps) \
)

/////////////////////////////////////////////////////////////////////////////////
// Alignment Macros
#define CCGOP_LAYOUT_ALIGNRIGHT( _size, _parent_size ) ( \
	(_parent_size) - (_size) \
)
#define CCGOP_LAYOUT_CENTER( _size, _parent_size ) ( \
	( (_parent_size) - (_size) ) >> 1 \
)

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_LAYOUT_H

