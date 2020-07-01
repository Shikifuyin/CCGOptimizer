/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/ResourceIDs.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOP GUI : Resource IDs
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
#define CCGOP_RESID_HEROEXPLORER_HEROOPTIONS  (CCGOP_RESID_HEROEXPLORER + 20)
#define CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE (CCGOP_RESID_HEROEXPLORER + 30)

/////////////////////////////////////////////////////////////////////////////////
// Root/HeroExplorer/HeroTable
#define CCGOP_RESID_HEROEXPLORER_HEROTABLE_GROUP           (CCGOP_RESID_HEROEXPLORER_HEROTABLE + 0)
#define CCGOP_RESID_HEROEXPLORER_HEROTABLE_SELECTALL       (CCGOP_RESID_HEROEXPLORER_HEROTABLE + 1)
#define CCGOP_RESID_HEROEXPLORER_HEROTABLE_UNSELECTALL     (CCGOP_RESID_HEROEXPLORER_HEROTABLE + 2)
#define CCGOP_RESID_HEROEXPLORER_HEROTABLE_CHECKALL        (CCGOP_RESID_HEROEXPLORER_HEROTABLE + 3)
#define CCGOP_RESID_HEROEXPLORER_HEROTABLE_UNCHECKALL      (CCGOP_RESID_HEROEXPLORER_HEROTABLE + 4)
#define CCGOP_RESID_HEROEXPLORER_HEROTABLE_CHECKSELECTED   (CCGOP_RESID_HEROEXPLORER_HEROTABLE + 5)
#define CCGOP_RESID_HEROEXPLORER_HEROTABLE_UNCHECKSELECTED (CCGOP_RESID_HEROEXPLORER_HEROTABLE + 6)

/////////////////////////////////////////////////////////////////////////////////
// Root/HeroExplorer/HeroCreation
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_GROUP    (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 0)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_NAME     (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 1)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_RANK     (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 2)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_LEVEL    (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 3)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_EVOLVED  (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 4)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_SANCTIFY (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 5)
#define CCGOP_RESID_HEROEXPLORER_HEROCREATION_CREATE   (CCGOP_RESID_HEROEXPLORER_HEROCREATION + 6)

/////////////////////////////////////////////////////////////////////////////////
// Root/HeroExplorer/HeroOptions
#define CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_GROUP          (CCGOP_RESID_HEROEXPLORER_HEROOPTIONS + 0)
#define CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_MAXRANK        (CCGOP_RESID_HEROEXPLORER_HEROOPTIONS + 1)
#define CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_MAXLEVEL       (CCGOP_RESID_HEROEXPLORER_HEROOPTIONS + 2)
#define CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_EVOLVED        (CCGOP_RESID_HEROEXPLORER_HEROOPTIONS + 3)
#define CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_SANCTIFYCHOICE (CCGOP_RESID_HEROEXPLORER_HEROOPTIONS + 4)
#define CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_SANCTIFY       (CCGOP_RESID_HEROEXPLORER_HEROOPTIONS + 5)
#define CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_DELETE         (CCGOP_RESID_HEROEXPLORER_HEROOPTIONS + 6)

/////////////////////////////////////////////////////////////////////////////////
// Root/HeroExplorer/HeroLoadSave
#define CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE_GROUP    (CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE + 0)
#define CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE_FILENAME (CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE + 1)
#define CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE_LOAD     (CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE + 2)
#define CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE_SAVE     (CCGOP_RESID_HEROEXPLORER_HEROLOADSAVE + 3)

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RESOURCEIDS_H

