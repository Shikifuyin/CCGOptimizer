/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/ResourceIDs.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : HeroExplorer GUI : Resource IDs
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
#ifndef CCGOP_FRONTEND_RESOURCEIDS_H
#define CCGOP_FRONTEND_RESOURCEIDS_H

/////////////////////////////////////////////////////////////////////////////////
// Root Window
#define CCGOP_RESID_ROOT 1000

#define CCGOP_RESID_STATUSBAR         (CCGOP_RESID_ROOT + 0)
#define CCGOP_RESID_MAINMENU_TABS     (CCGOP_RESID_ROOT + 1)

#define CCGOP_RESID_MAINMENU_TABPANES (CCGOP_RESID_ROOT + 10) // CCGOP_MAINMENU_COUNT IDs

/////////////////////////////////////////////////////////////////////////////////
// Root/HeroExplorer
#define CCGOP_RESID_HEROEXPLORER (CCGOP_RESID_ROOT + 100)

#define CCGOP_RESID_HEROEXPLORER_HEROTABLE    (CCGOP_RESID_HEROEXPLORER + 0)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION (CCGOP_RESID_HEROEXPLORER + 10)

/////////////////////////////////////////////////////////////////////////////////
// Root/HeroExplorer/HeroCreation
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_GROUP    (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 0)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_NAME     (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 1)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_RANK     (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 2)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_LEVEL    (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 3)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_EVOLVED  (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 4)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_SANCTIFY (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 5)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_BUTTON   (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 6)

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RESOURCEIDS_H
