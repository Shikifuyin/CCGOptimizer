/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/Optimizer/OptimizerOptions.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Optimizer GUI : Optimizer Options
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
#ifndef CCGOP_FRONTEND_OPTIMIZER_OPTIMIZEROPTIONS_H
#define CCGOP_FRONTEND_OPTIMIZER_OPTIMIZEROPTIONS_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"
#include "Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIOptimizerOptionsGroupModel class
class UIOptimizerOptionsGroupModel : public WinGUIGroupBoxModel
{
public:
	UIOptimizerOptionsGroupModel();
	virtual ~UIOptimizerOptionsGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIOptimizerOptions class
class UIOptimizerOptions
{
public:
	UIOptimizerOptions( CCGOPGUI * pGUI );
	~UIOptimizerOptions();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Optimizer Options
	inline Void GetArea( WinGUIRectangle * outClientArea ) const;

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Optimizer Options UI
	UIOptimizerOptionsGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;


};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "OptimizerOptions.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_OPTIMIZER_OPTIMIZEROPTIONS_H