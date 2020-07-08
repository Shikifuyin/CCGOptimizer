/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/ImportExport/LoadSave.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Import / Export GUI : Load & Save from/to XML
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
#ifndef CCGOP_FRONTEND_IMPORTEXPORT_LOADSAVE_H
#define CCGOP_FRONTEND_IMPORTEXPORT_LOADSAVE_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "ThirdParty/WinGUI/WinGUI.h"

#include "../../BackEnd/CCGOPManager.h"

#include "../ResourceIDs.h"
#include "../Layout.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

// Prototypes
class CCGOPGUI;

/////////////////////////////////////////////////////////////////////////////////
// The UIFileGroupModel class
class UIFileGroupModel : public WinGUIGroupBoxModel
{
public:
	UIFileGroupModel();
	virtual ~UIFileGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIFileNameModel class
class UIFileNameModel : public WinGUITextEditModel
{
public:
	UIFileNameModel();
	virtual ~UIFileNameModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIFileLoadModel class
class UIFileLoadModel : public WinGUIButtonModel
{
public:
	UIFileLoadModel();
	virtual ~UIFileLoadModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UIFileSaveModel class
class UIFileSaveModel : public WinGUIButtonModel
{
public:
	UIFileSaveModel();
	virtual ~UIFileSaveModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Bool OnClick();

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The UILoadSave class
class UILoadSave
{
public:
	UILoadSave( CCGOPGUI * pGUI );
	~UILoadSave();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

	// Load / Save
	inline Void GetArea( WinGUIRectangle * outClientArea ) const;

	inline WinGUITextEdit * GetFileName() const;

	inline Bool HasUnsavedChangesMark() const;
	Void SetUnsavedChangesMark();
	Void ClearUnsavedChangesMark();

private:
	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Load/Save UI
	UIFileGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	UIFileNameModel m_hFileNameModel;
	WinGUITextEdit * m_pFileName;

	UIFileLoadModel m_hLoadModel;
	WinGUIButton * m_pLoad;

	UIFileSaveModel m_hSaveModel;
	WinGUIButton * m_pSave;

	Bool m_bUnsavedChanges;
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "LoadSave.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_IMPORTEXPORT_LOADSAVE_H

