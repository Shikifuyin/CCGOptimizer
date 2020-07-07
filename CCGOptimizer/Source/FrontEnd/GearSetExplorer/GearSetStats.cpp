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
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(0,1,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(0,HERO_STAT_COUNT+1,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_SPACING_BORDER + (CCGOP_LAYOUT_TABLE_WIDTH >> 1) + CCGOP_LAYOUT_SPACING_GAP_HORIZ;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStatsDisplayModel implementation
UIGearSetStatsDisplayModel::UIGearSetStatsDisplayModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_DISPLAY)
{
	m_pGUI = NULL;
	m_iHeroStat = HERO_STAT_COUNT;
}
UIGearSetStatsDisplayModel::~UIGearSetStatsDisplayModel()
{
	// nothing to do
}

Void UIGearSetStatsDisplayModel::Initialize( CCGOPGUI * pGUI, HeroStat iHeroStat )
{
	m_pGUI = pGUI;
	m_iHeroStat = iHeroStat;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetStatsDisplayModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;
	GChar strStatText[64];

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Retrieve Stat Name
	GChar strStatName[64];
	StringFn->NCopy( strStatName, GameDataFn->GetHeroStatName(m_iHeroStat), 63 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		StringFn->Format( strStatText, TEXT( "%s = ---" ), strStatName );
		pController->SetText( strStatText );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// Retrieve Stat Value
	Bool bStatIsPercent = false;
	Bool bStatIsBoth = false;
	UInt iStatFlatTotal = 0;
	UInt iStatPercentTotal = 0;

	switch( m_iHeroStat ) {
		case HERO_STAT_HP: {
				bStatIsBoth = true;
				for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
					RuneID iRuneID = pGearSet->GetEquippedRune( i );
					if ( iRuneID == INVALID_OFFSET )
						continue;
					const Rune * pRune = CCGOPFn->GetRune( iRuneID );

					if ( pRune->GetMainStat() == RUNE_STAT_HP_FLAT )
						iStatFlatTotal += pRune->GetMainStatValue();
					else if ( pRune->GetMainStat() == RUNE_STAT_HP_PERCENT )
						iStatPercentTotal += pRune->GetMainStatValue();

					if ( pRune->GetInnateStat() == RUNE_STAT_HP_FLAT )
						iStatFlatTotal += pRune->GetInnateStatValue();
					else if ( pRune->GetInnateStat() == RUNE_STAT_HP_PERCENT )
						iStatPercentTotal += pRune->GetInnateStatValue();

					if ( pRune->HasRandomStat(RUNE_STAT_HP_FLAT) )
						iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_HP_FLAT );
					if ( pRune->HasRandomStat(RUNE_STAT_HP_PERCENT) )
						iStatPercentTotal += pRune->GetRandomStatValue( RUNE_STAT_HP_PERCENT );
				}
			} break;
		case HERO_STAT_ATTACK: {
				bStatIsBoth = true;
				for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
					RuneID iRuneID = pGearSet->GetEquippedRune( i );
					if ( iRuneID == INVALID_OFFSET )
						continue;
					const Rune * pRune = CCGOPFn->GetRune( iRuneID );

					if ( pRune->GetMainStat() == RUNE_STAT_ATTACK_FLAT )
						iStatFlatTotal += pRune->GetMainStatValue();
					else if ( pRune->GetMainStat() == RUNE_STAT_ATTACK_PERCENT )
						iStatPercentTotal += pRune->GetMainStatValue();

					if ( pRune->GetInnateStat() == RUNE_STAT_ATTACK_FLAT )
						iStatFlatTotal += pRune->GetInnateStatValue();
					else if ( pRune->GetInnateStat() == RUNE_STAT_ATTACK_PERCENT )
						iStatPercentTotal += pRune->GetInnateStatValue();

					if ( pRune->HasRandomStat(RUNE_STAT_ATTACK_FLAT) )
						iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_FLAT );
					if ( pRune->HasRandomStat(RUNE_STAT_ATTACK_PERCENT) )
						iStatPercentTotal += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_PERCENT );
				}
			} break;
		case HERO_STAT_DEFENSE: {
				bStatIsBoth = true;
				for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
					RuneID iRuneID = pGearSet->GetEquippedRune( i );
					if ( iRuneID == INVALID_OFFSET )
						continue;
					const Rune * pRune = CCGOPFn->GetRune( iRuneID );

					if ( pRune->GetMainStat() == RUNE_STAT_DEFENSE_FLAT )
						iStatFlatTotal += pRune->GetMainStatValue();
					else if ( pRune->GetMainStat() == RUNE_STAT_DEFENSE_PERCENT )
						iStatPercentTotal += pRune->GetMainStatValue();

					if ( pRune->GetInnateStat() == RUNE_STAT_DEFENSE_FLAT )
						iStatFlatTotal += pRune->GetInnateStatValue();
					else if ( pRune->GetInnateStat() == RUNE_STAT_DEFENSE_PERCENT )
						iStatPercentTotal += pRune->GetInnateStatValue();

					if ( pRune->HasRandomStat(RUNE_STAT_DEFENSE_FLAT) )
						iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_FLAT );
					if ( pRune->HasRandomStat(RUNE_STAT_DEFENSE_PERCENT) )
						iStatPercentTotal += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_PERCENT );
				}
			} break;
		case HERO_STAT_SPEED: {
				for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
					RuneID iRuneID = pGearSet->GetEquippedRune( i );
					if ( iRuneID == INVALID_OFFSET )
						continue;
					const Rune * pRune = CCGOPFn->GetRune( iRuneID );

					if ( pRune->GetMainStat() == RUNE_STAT_SPEED )
						iStatFlatTotal += pRune->GetMainStatValue();
					else if ( pRune->GetInnateStat() == RUNE_STAT_SPEED )
						iStatFlatTotal += pRune->GetInnateStatValue();
					else if ( pRune->HasRandomStat(RUNE_STAT_SPEED) )
						iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_SPEED );
				}
			} break;
		case HERO_STAT_CRIT_RATE: {
				bStatIsPercent = true;
				for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
					RuneID iRuneID = pGearSet->GetEquippedRune( i );
					if ( iRuneID == INVALID_OFFSET )
						continue;
					const Rune * pRune = CCGOPFn->GetRune( iRuneID );

					if ( pRune->GetMainStat() == RUNE_STAT_CRIT_RATE )
						iStatFlatTotal += pRune->GetMainStatValue();
					else if ( pRune->GetInnateStat() == RUNE_STAT_CRIT_RATE )
						iStatFlatTotal += pRune->GetInnateStatValue();
					else if ( pRune->HasRandomStat(RUNE_STAT_CRIT_RATE) )
						iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_CRIT_RATE );
				}
			} break;
		case HERO_STAT_CRIT_DMG: {
				bStatIsPercent = true;
				for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
					RuneID iRuneID = pGearSet->GetEquippedRune( i );
					if ( iRuneID == INVALID_OFFSET )
						continue;
					const Rune * pRune = CCGOPFn->GetRune( iRuneID );

					if ( pRune->GetMainStat() == RUNE_STAT_CRIT_DMG )
						iStatFlatTotal += pRune->GetMainStatValue();
					else if ( pRune->GetInnateStat() == RUNE_STAT_CRIT_DMG )
						iStatFlatTotal += pRune->GetInnateStatValue();
					else if ( pRune->HasRandomStat(RUNE_STAT_CRIT_DMG) )
						iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_CRIT_DMG );
				}
			} break;
		case HERO_STAT_HIT: {
				bStatIsPercent = true;
				for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
					RuneID iRuneID = pGearSet->GetEquippedRune( i );
					if ( iRuneID == INVALID_OFFSET )
						continue;
					const Rune * pRune = CCGOPFn->GetRune( iRuneID );

					if ( pRune->GetMainStat() == RUNE_STAT_HIT )
						iStatFlatTotal += pRune->GetMainStatValue();
					else if ( pRune->GetInnateStat() == RUNE_STAT_HIT )
						iStatFlatTotal += pRune->GetInnateStatValue();
					else if ( pRune->HasRandomStat(RUNE_STAT_HIT) )
						iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_HIT );
				}
			} break;
		case HERO_STAT_RESISTANCE: {
				bStatIsPercent = true;
				for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
					RuneID iRuneID = pGearSet->GetEquippedRune( i );
					if ( iRuneID == INVALID_OFFSET )
						continue;
					const Rune * pRune = CCGOPFn->GetRune( iRuneID );

					if ( pRune->GetMainStat() == RUNE_STAT_RESISTANCE )
						iStatFlatTotal += pRune->GetMainStatValue();
					else if ( pRune->GetInnateStat() == RUNE_STAT_RESISTANCE )
						iStatFlatTotal += pRune->GetInnateStatValue();
					else if ( pRune->HasRandomStat(RUNE_STAT_RESISTANCE) )
						iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_RESISTANCE );
				}
			} break;
		default: Assert(false); break;
	}
	
	// Build Stat Text
	if ( bStatIsPercent )
		StringFn->Format( strStatText, TEXT( "%s = %d %%" ), strStatName, iStatFlatTotal );
	else if ( bStatIsBoth )
		StringFn->Format( strStatText, TEXT( "%s = %d + %d %%" ), strStatName, iStatFlatTotal, iStatPercentTotal );
	else
		StringFn->Format( strStatText, TEXT( "%s = %d" ), strStatName, iStatFlatTotal );

	// Done
	pController->SetText( strStatText );
}

const WinGUILayout * UIGearSetStatsDisplayModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetStatsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,m_iHeroStat,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStatsSetBonusModel implementation
UIGearSetStatsSetBonusModel::UIGearSetStatsSetBonusModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_SETBONUS)
{
	m_pGUI = NULL;
}
UIGearSetStatsSetBonusModel::~UIGearSetStatsSetBonusModel()
{
	// nothing to do
}

Void UIGearSetStatsSetBonusModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetStatsSetBonusModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;
	GChar strSetBonusText[64];
	UInt i;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("Set Bonus = ---") );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// Compute Set Counts
	UInt arrSetCounts[RUNE_SET_COUNT];
	for( i = 0; i < RUNE_SET_COUNT; ++i )
		arrSetCounts[i] = 0;

	for( i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		RuneID iRuneID = pGearSet->GetEquippedRune( i );
		if ( iRuneID == INVALID_OFFSET )
			continue;
		const Rune * pRune = CCGOPFn->GetRune( iRuneID );
		++( arrSetCounts[pRune->GetSet()] );
	}

	// Compute Active Set Bonuses
	GChar * pAppend = strSetBonusText;
	pAppend = StringFn->NCopy( pAppend, TEXT("Set Bonus ="), 63 );

	for( i = 0; i < RUNE_SET_COUNT; ++i ) {
		RuneSet iRuneSet = (RuneSet)i;
		const GChar * strSetName = GameDataFn->GetRuneSetName( iRuneSet );
		UInt iSetSize = GameDataFn->GetRuneSetSize( iRuneSet );
		if ( arrSetCounts[i] < iSetSize )
			continue;
		if ( iSetSize = 2 ) {
			UInt iAmount = ( arrSetCounts[i] >> 1 );
			if ( iAmount > 1 )
				pAppend = StringFn->Format( pAppend, TEXT(" %s x%d,"), strSetName, iAmount );
			else
				pAppend = StringFn->Format( pAppend, TEXT(" %s,"), strSetName );
		} else if ( iSetSize == 4 ) {
			Bool bHas6Bonus = ( arrSetCounts[i] == 6 );
			pAppend = StringFn->Format( pAppend, TEXT(" %s(%d),"), strSetName, bHas6Bonus ? 6 : 4 );
		} else { // Should never happen
			Assert( false );
		}
	}

	// Done
	pController->SetText( strSetBonusText );
}

const WinGUILayout * UIGearSetStatsSetBonusModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetStatsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,HERO_STAT_COUNT,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStats implementation
UIGearSetStats::UIGearSetStats( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	for( UInt i = 0; i < HERO_STAT_COUNT; ++i )
		m_arrHeroStats[i].pStat = NULL;
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

	// Build Hero Creation UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroupModel );

	for( UInt i = 0; i < HERO_STAT_COUNT; ++i ) {
		m_arrHeroStats[i].hStatModel.Initialize( m_pGUI, (HeroStat)i );
		m_arrHeroStats[i].pStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrHeroStats[i].hStatModel) );
		m_arrHeroStats[i].hStatModel.Update();
	}

	m_hSetBonusModel.Initialize( m_pGUI );
	m_pSetBonus = WinGUIFn->CreateStatic( m_pRoot, &m_hSetBonusModel );
	m_hSetBonusModel.Update();
}
Void UIGearSetStats::Cleanup()
{
	// nothing to do (for now)
}

Void UIGearSetStats::UpdateModels()
{
	for( UInt i = 0; i < HERO_STAT_COUNT; ++i )
		m_arrHeroStats[i].hStatModel.Update();
	m_hSetBonusModel.Update();
}

