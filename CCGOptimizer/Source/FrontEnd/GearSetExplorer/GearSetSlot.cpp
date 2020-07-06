/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetSlot.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Slots Display
/////////////////////////////////////////////////////////////////////////////////
// Part of Scarab-Engine, licensed under the
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "GearSetSlot.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetSlotGroupModel implementation
UIGearSetSlotGroupModel::UIGearSetSlotGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSLOT_GROUP)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetSlotGroupModel::~UIGearSetSlotGroupModel()
{
	// nothing to do
}

Void UIGearSetSlotGroupModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->Format( m_hCreationParameters.strLabel, TEXT("Slot %d :"), m_iSlot + 1 );
}

const WinGUILayout * UIGearSetSlotGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = 180 + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = 180 + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_CLIENT_WIDTH ) - CCGOP_LAYOUT_SPACING_BORDER
							 - ( (2 - (m_iSlot >> 1)) * (hLayout.FixedSize.iX + CCGOP_LAYOUT_SPACING_GAP_HORIZ) );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER
							 + ( (m_iSlot & 1) ? (hLayout.FixedSize.iY + CCGOP_LAYOUT_SPACING_GAP_VERT) : 0 );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetSlotHeadLineModel implementation
UIGearSetSlotHeadLineModel::UIGearSetSlotHeadLineModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSLOT_HEADLINE)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetSlotHeadLineModel::~UIGearSetSlotHeadLineModel()
{
	// nothing to do
}

Void UIGearSetSlotHeadLineModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("Rune : ---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetSlotHeadLineModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("Rune : ---") );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET ) {
		pController->SetText( TEXT("Rune : ---") );
		return;
	}

	// Retrieve Rune
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// Build HeadLine
	GChar strHeadLine[64];
	StringFn->Format( strHeadLine, TEXT("Rune (%d) : %s %s %s +%d"),
		iRuneID,
		GameDataFn->GetRuneRankName( pRune->GetRank() ),
		GameDataFn->GetRuneQualityName( pRune->GetQuality() ),
		GameDataFn->GetRuneSetName( pRune->GetSet() ),
		pRune->GetLevel()
	);

	// Done
	pController->SetText( strHeadLine );
}

const WinGUILayout * UIGearSetSlotHeadLineModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetSlotMainStatModel implementation
UIGearSetSlotMainStatModel::UIGearSetSlotMainStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSLOT_MAINSTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetSlotMainStatModel::~UIGearSetSlotMainStatModel()
{
	// nothing to do
}

Void UIGearSetSlotMainStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("Main Stat : ---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetSlotMainStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("Main Stat : ---") );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET ) {
		pController->SetText( TEXT("Main Stat : ---") );
		return;
	}

	// Retrieve Rune
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// Build Main Stat String
	GChar strMainStat[64];
	StringFn->Format( strMainStat, TEXT("Main Stat : %s %d"),
		GameDataFn->GetRuneStatName( pRune->GetMainStat() ),
		pRune->GetMainStatValue()
	);

	// Done
	pController->SetText( strMainStat );
}

const WinGUILayout * UIGearSetSlotMainStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetSlotInnateStatModel implementation
UIGearSetSlotInnateStatModel::UIGearSetSlotInnateStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSLOT_INNATESTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetSlotInnateStatModel::~UIGearSetSlotInnateStatModel()
{
	// nothing to do
}

Void UIGearSetSlotInnateStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("Innate Stat : ---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetSlotInnateStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("Innate Stat : ---") );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET ) {
		pController->SetText( TEXT("Innate Stat : ---") );
		return;
	}

	// Retrieve Rune
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// No Innate Stat case
	if ( pRune->GetInnateStat() == RUNE_STAT_COUNT ) {
		pController->SetText( TEXT("Innate Stat : ---") );
		return;
	}

	// Build Innate Stat String
	GChar strInnateStat[64];
	StringFn->Format( strInnateStat, TEXT("Innate Stat : %s %d"),
		GameDataFn->GetRuneStatName( pRune->GetInnateStat() ),
		pRune->GetInnateStatValue()
	);

	// Done
	pController->SetText( strInnateStat );
}

const WinGUILayout * UIGearSetSlotInnateStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,2,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetSlotRandomStatModel implementation
UIGearSetSlotRandomStatModel::UIGearSetSlotRandomStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSLOT_RANDOMSTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
	m_iIndex = INVALID_OFFSET;
}
UIGearSetSlotRandomStatModel::~UIGearSetSlotRandomStatModel()
{
	// nothing to do
}

Void UIGearSetSlotRandomStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot, UInt iIndex )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;
	m_iIndex = iIndex;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("Random Stat : ---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetSlotRandomStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("Random Stat : ---") );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET ) {
		pController->SetText( TEXT("Random Stat : ---") );
		return;
	}

	// Retrieve Rune
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// No Random Stat case
	if ( pRune->GetRandomStatCount() <= m_iIndex ) {
		pController->SetText( TEXT("Random Stat : ---") );
		return;
	}

	// Retrieve Random Stat
	RuneStat iRuneStat = pRune->GetRandomStat( m_iIndex );

	// Build Random Stat String
	GChar strRandomStat[64];
	StringFn->Format( strRandomStat, TEXT("Random Stat : %s %d"),
		GameDataFn->GetRuneStatName( iRuneStat ),
		pRune->GetRandomStatValue( iRuneStat )
	);

	// Done
	pController->SetText( strRandomStat );
}

const WinGUILayout * UIGearSetSlotRandomStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,3 + m_iIndex,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetSlot implementation
UIGearSetSlot::UIGearSetSlot()
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pHeadLine = NULL;
	m_pMainStat = NULL;
	m_pInnateStat = NULL;
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i )
		m_arrRandomStats[i].pStat = NULL;
}
UIGearSetSlot::~UIGearSetSlot()
{
	// nothing to do
}

Void UIGearSetSlot::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_GEARSET_EXPLORER );

	// Build GearSet Stats UI
	m_hGroup.Initialize( m_pGUI, m_iSlot );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroup );

	m_hHeadLine.Initialize( m_pGUI, m_iSlot );
	m_pHeadLine = WinGUIFn->CreateStatic( m_pRoot, &m_hHeadLine );

	m_hMainStat.Initialize( m_pGUI, m_iSlot );
	m_pMainStat = WinGUIFn->CreateStatic( m_pRoot, &m_hMainStat );

	m_hInnateStat.Initialize( m_pGUI, m_iSlot );
	m_pInnateStat = WinGUIFn->CreateStatic( m_pRoot, &m_hInnateStat );

	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		m_arrRandomStats[i].hStat.Initialize( m_pGUI, m_iSlot, i );
		m_arrRandomStats[i].pStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrRandomStats[i].hStat) );
	}
}
Void UIGearSetSlot::Cleanup()
{
	// nothing to do
}
