/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneCreation.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI : Rune Creation
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
#ifndef CCGOP_FRONTEND_RUNEEXPLORER_RUNECREATION_H
#define CCGOP_FRONTEND_RUNEEXPLORER_RUNECREATION_H

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
// The RuneCreationGroupModel class
class RuneCreationGroupModel : public WinGUIGroupBoxModel
{
public:
	RuneCreationGroupModel();
	virtual ~RuneCreationGroupModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationSlotModel class
class RuneCreationSlotModel : public WinGUIComboBoxModel
{
public:
	RuneCreationSlotModel();
	~RuneCreationSlotModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationSetModel class
class RuneCreationSetModel : public WinGUIComboBoxModel
{
public:
	RuneCreationSetModel();
	~RuneCreationSetModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationRankModel class
class RuneCreationRankModel : public WinGUIComboBoxModel
{
public:
	RuneCreationRankModel();
	~RuneCreationRankModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationQualityModel class
class RuneCreationQualityModel : public WinGUIComboBoxModel
{
public:
	RuneCreationQualityModel();
	~RuneCreationQualityModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationLevelModel class
class RuneCreationLevelModel : public WinGUIComboBoxModel
{
public:
	RuneCreationLevelModel();
	~RuneCreationLevelModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationMainStatModel class
class RuneCreationMainStatModel : public WinGUIComboBoxModel
{
public:
	RuneCreationMainStatModel();
	~RuneCreationMainStatModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( UInt iSelectedSlot, RuneStat * arrExcludedStats, UInt iExcludedStatsCount );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	UInt m_iSelectedSlot;
	UInt m_iExcludedStatsCount;
	RuneStat m_arrExcludedStats[2+RUNE_RANDOM_STAT_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationInnateStatModel class
class RuneCreationInnateStatModel : public WinGUIComboBoxModel
{
public:
	RuneCreationInnateStatModel();
	~RuneCreationInnateStatModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI );
	Void Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;

	UInt m_iExcludedStatsCount;
	RuneStat m_arrExcludedStats[2+RUNE_RANDOM_STAT_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationInnateStatValueModel class
class RuneCreationInnateStatValueModel : public WinGUITextEditModel
{
public:
	RuneCreationInnateStatValueModel();
	~RuneCreationInnateStatValueModel();

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
// The RuneCreationRandomStatModel class
class RuneCreationRandomStatModel : public WinGUIComboBoxModel
{
public:
	RuneCreationRandomStatModel();
	~RuneCreationRandomStatModel();

	// Initialization / Update
	Void Initialize( CCGOPGUI * pGUI, UInt iIndex );
	Void Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount );

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

	virtual Bool OnSelectionOK();

	// Item Callback Events
	virtual Void OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData );

private:
	CCGOPGUI * m_pGUI;
	UInt m_iIndex;

	UInt m_iExcludedStatsCount;
	RuneStat m_arrExcludedStats[2+RUNE_RANDOM_STAT_COUNT];
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationRandomStatValueModel class
class RuneCreationRandomStatValueModel : public WinGUITextEditModel
{
public:
	RuneCreationRandomStatValueModel();
	~RuneCreationRandomStatValueModel();

	// Initialization
	Void Initialize( CCGOPGUI * pGUI, UInt iIndex );
	Void Update();

	// Layout
	virtual const WinGUILayout * GetLayout() const;

	// Events
	virtual Void OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey );

private:
	CCGOPGUI * m_pGUI;
	UInt m_iIndex;
};

/////////////////////////////////////////////////////////////////////////////////
// The RuneCreationButtonModel class
class RuneCreationButtonModel : public WinGUIButtonModel
{
public:
	RuneCreationButtonModel();
	~RuneCreationButtonModel();

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
// The RuneCreation class
class RuneCreation
{
public:
	RuneCreation( CCGOPGUI * pGUI );
	~RuneCreation();

	// Initialization / Cleanup
	Void Initialize();
	Void Cleanup();

private:
	friend class RuneCreationSlotModel;
	friend class RuneCreationSetModel;
	friend class RuneCreationRankModel;
	friend class RuneCreationQualityModel;
	friend class RuneCreationLevelModel;
	friend class RuneCreationMainStatModel;
	friend class RuneCreationInnateStatModel;
	friend class RuneCreationInnateStatValueModel;
	friend class RuneCreationRandomStatModel;
	friend class RuneCreationRandomStatValueModel;
	friend class RuneCreationButtonModel;

	// Helpers
	Void _UpdateAvailableMainStats();
	Void _UpdateRandomStatsCount();
	Void _ExcludeRuneStats( WinGUIComboBox * pJustSelected );

	// GUI Instance
	CCGOPGUI * m_pGUI;
	WinGUIContainer * m_pRoot;

	// Rune Creation UI
	RuneCreationGroupModel m_hGroupModel;
	WinGUIGroupBox * m_pGroup;

	RuneCreationSlotModel m_hSlotModel;
	WinGUIComboBox * m_pSlot;

	RuneCreationSetModel m_hSetModel;
	WinGUIComboBox * m_pSet;

	RuneCreationRankModel m_hRankModel;
	WinGUIComboBox * m_pRank;

	RuneCreationQualityModel m_hQualityModel;
	WinGUIComboBox * m_pQuality;

	RuneCreationLevelModel m_hLevelModel;
	WinGUIComboBox * m_pLevel;

	RuneCreationMainStatModel m_hMainStatModel;
	WinGUIComboBox * m_pMainStat;

	RuneCreationInnateStatModel m_hInnateStatModel;
	WinGUIComboBox * m_pInnateStat;

	RuneCreationInnateStatValueModel m_hInnateStatValueModel;
	WinGUITextEdit * m_pInnateStatValue;

	struct _random_stats {
		RuneCreationRandomStatModel m_hRandomStatModel;
		WinGUIComboBox * m_pRandomStat;
		RuneCreationRandomStatValueModel m_hRandomStatValueModel;
		WinGUITextEdit * m_pRandomStatValue;
	} m_arrRandomStats[RUNE_RANDOM_STAT_COUNT];

	RuneCreationButtonModel m_hButtonModel;
	WinGUIButton * m_pButton;
};


/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "RuneCreation.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_FRONTEND_RUNEEXPLORER_RUNECREATION_H

