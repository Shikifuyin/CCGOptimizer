/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetStats.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Stats Display
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
#include "GearSetStats.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStatsGroupModel implementation
UIGearSetStatsGroupModel::UIGearSetStatsGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_GROUP)
{
	m_pGUI = NULL;
}
UIGearSetStatsGroupModel::~UIGearSetStatsGroupModel()
{
	// nothing to do
}

Void UIGearSetStatsGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("GearSet Stats :") );
}

const WinGUILayout * UIGearSetStatsGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = 600 + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = 400 + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_CLIENT_WIDTH );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStatsRuneGroupModel implementation
UIGearSetStatsRuneGroupModel::UIGearSetStatsRuneGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_RUNEGROUP)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetStatsRuneGroupModel::~UIGearSetStatsRuneGroupModel()
{
	// nothing to do
}

Void UIGearSetStatsRuneGroupModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->Format( m_hCreationParameters.strLabel, TEXT("Slot %d :"), iSlot + 1 );
}

const WinGUILayout * UIGearSetStatsRuneGroupModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetGearSetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = 160 + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = 160 + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + ( (m_iSlot >> 1) * (hLayout.FixedSize.iX + CCGOP_LAYOUT_SPACING_GAP_HORIZ) );
	hLayout.FixedPosition.iY = hClientArea.iTop + ( (m_iSlot & 1) ? (hLayout.FixedSize.iY + CCGOP_LAYOUT_SPACING_GAP_VERT) : 0 );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStatsRuneHeadLineModel implementation
UIGearSetStatsRuneHeadLineModel::UIGearSetStatsRuneHeadLineModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_RUNEHEADLINE)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetStatsRuneHeadLineModel::~UIGearSetStatsRuneHeadLineModel()
{
	// nothing to do
}

Void UIGearSetStatsRuneHeadLineModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
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
Void UIGearSetStatsRuneHeadLineModel::Update()
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

const WinGUILayout * UIGearSetStatsRuneHeadLineModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetRuneArea( &hClientArea, m_iSlot );

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
// UIGearSetStatsRuneMainStatModel implementation
UIGearSetStatsRuneMainStatModel::UIGearSetStatsRuneMainStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_RUNEMAINSTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetStatsRuneMainStatModel::~UIGearSetStatsRuneMainStatModel()
{
	// nothing to do
}

Void UIGearSetStatsRuneMainStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
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
Void UIGearSetStatsRuneMainStatModel::Update()
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

const WinGUILayout * UIGearSetStatsRuneMainStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetRuneArea( &hClientArea, m_iSlot );

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
// UIGearSetStats implementation
UIGearSetStats::UIGearSetStats( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		m_arrRuneStats[i].pGroup = NULL;
		m_arrRuneStats[i].pHeadLine = NULL;
		m_arrRuneStats[i].pMainStat = NULL;
		m_arrRuneStats[i].pInnateStat = NULL;
		for( UInt j = 0; j < RUNE_RANDOM_STAT_COUNT; ++j )
			m_arrRuneStats[i].arrRandomStats[j].pStat = NULL;
	}

	m_pSetBonus = NULL;
}
UIGearSetStats::~UIGearSetStats()
{
	// nothing to do
}

Void UIGearSetStats::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_GEARSET_EXPLORER );

	// Build GearSet Stats UI
	m_hGroup.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroup );

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		m_arrRuneStats[i].hGroup.Initialize( m_pGUI, i );
		m_arrRuneStats[i].pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &(m_arrRuneStats[i].hGroup) );

		m_arrRuneStats[i].hHeadLine.Initialize( m_pGUI, i );
		m_arrRuneStats[i].pHeadLine = WinGUIFn->CreateStatic( m_pRoot, &(m_arrRuneStats[i].hHeadLine) );

		m_arrRuneStats[i].hMainStat.Initialize( m_pGUI, i );
		m_arrRuneStats[i].pMainStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrRuneStats[i].hMainStat) );

	}
}
Void UIGearSetStats::Cleanup()
{
	// nothing to do
}
