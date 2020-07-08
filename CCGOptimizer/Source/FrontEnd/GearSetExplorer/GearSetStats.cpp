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
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(0,2,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,HERO_STAT_COUNT+1,1,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_SPACING_BORDER + CCGOP_LAYOUT_GEARSETEXPLORER_TABLE_WIDTH + CCGOP_LAYOUT_SPACING_GAP_HORIZ;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStatsLabelModel implementation
UIGearSetStatsLabelModel::UIGearSetStatsLabelModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_LABEL)
{
	m_pGUI = NULL;
	m_iHeroStat = HERO_STAT_COUNT;
}
UIGearSetStatsLabelModel::~UIGearSetStatsLabelModel()
{
	// nothing to do
}

Void UIGearSetStatsLabelModel::Initialize( CCGOPGUI * pGUI, HeroStat iHeroStat )
{
	m_pGUI = pGUI;
	m_iHeroStat = iHeroStat;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, GameDataFn->GetHeroStatName(m_iHeroStat) );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetStatsLabelModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetArea( &hClientArea );

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
// UIGearSetStatsValueModel implementation
UIGearSetStatsValueModel::UIGearSetStatsValueModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_VALUE)
{
	m_pGUI = NULL;
	m_iHeroStat = HERO_STAT_COUNT;
}
UIGearSetStatsValueModel::~UIGearSetStatsValueModel()
{
	// nothing to do
}

Void UIGearSetStatsValueModel::Initialize( CCGOPGUI * pGUI, HeroStat iHeroStat )
{
	m_pGUI = pGUI;
	m_iHeroStat = iHeroStat;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetStatsValueModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;
	GChar strStatText[64];

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT( "---" ) );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// Retrieve Display Mode
	WinGUICheckBox * pMode = m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetMode();
	Bool bUseMaxedRunes = pMode->IsChecked();

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

					if ( pRune->GetMainStat() == RUNE_STAT_HP_FLAT ) {
						if ( bUseMaxedRunes )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HP_FLAT, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatFlatTotal += pRune->GetMainStatValue();
					} else if ( pRune->GetMainStat() == RUNE_STAT_HP_PERCENT ) {
						if ( bUseMaxedRunes )
							iStatPercentTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HP_PERCENT, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatPercentTotal += pRune->GetMainStatValue();
					}

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

					if ( pRune->GetMainStat() == RUNE_STAT_ATTACK_FLAT ) {
						if ( bUseMaxedRunes )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_ATTACK_FLAT, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatFlatTotal += pRune->GetMainStatValue();
					} else if ( pRune->GetMainStat() == RUNE_STAT_ATTACK_PERCENT ) {
						if ( bUseMaxedRunes )
							iStatPercentTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_ATTACK_PERCENT, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatPercentTotal += pRune->GetMainStatValue();
					}

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

					if ( pRune->GetMainStat() == RUNE_STAT_DEFENSE_FLAT ) {
						if ( bUseMaxedRunes )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_DEFENSE_FLAT, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatFlatTotal += pRune->GetMainStatValue();
					} else if ( pRune->GetMainStat() == RUNE_STAT_DEFENSE_PERCENT ) {
						if ( bUseMaxedRunes )
							iStatPercentTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_DEFENSE_PERCENT, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatPercentTotal += pRune->GetMainStatValue();
					}

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

					if ( pRune->GetMainStat() == RUNE_STAT_SPEED ) {
						if ( bUseMaxedRunes )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_SPEED, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatFlatTotal += pRune->GetMainStatValue();
					}
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

					if ( pRune->GetMainStat() == RUNE_STAT_CRIT_RATE ) {
						if ( bUseMaxedRunes )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_CRIT_RATE, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatFlatTotal += pRune->GetMainStatValue();
					}
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

					if ( pRune->GetMainStat() == RUNE_STAT_CRIT_DMG ) {
						if ( bUseMaxedRunes )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_CRIT_DMG, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatFlatTotal += pRune->GetMainStatValue();
					}
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

					if ( pRune->GetMainStat() == RUNE_STAT_HIT ) {
						if ( bUseMaxedRunes )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HIT, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatFlatTotal += pRune->GetMainStatValue();
					}
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

					if ( pRune->GetMainStat() == RUNE_STAT_RESISTANCE ) {
						if ( bUseMaxedRunes )
							iStatFlatTotal += GameDataFn->GetRuneMainStatValue( RUNE_STAT_RESISTANCE, pRune->GetRank(), RUNE_MAX_LEVEL );
						else
							iStatFlatTotal += pRune->GetMainStatValue();
					}
					else if ( pRune->GetInnateStat() == RUNE_STAT_RESISTANCE )
						iStatFlatTotal += pRune->GetInnateStatValue();
					else if ( pRune->HasRandomStat(RUNE_STAT_RESISTANCE) )
						iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_RESISTANCE );
				}
			} break;
		default: Assert(false); break;
	}

	// Retrieve Hero View
	WinGUIComboBox * pHeroView = m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetHeroView();
	iSelected = pHeroView->GetSelectedItem();

	// Build Stat Text
	if ( iSelected == INVALID_OFFSET ) {
		// GearSet View Mode
		if ( bStatIsPercent )
			StringFn->Format( strStatText, TEXT( "%d %%" ), iStatFlatTotal );
		else if ( bStatIsBoth )
			StringFn->Format( strStatText, TEXT( "%d + %d %%" ), iStatFlatTotal, iStatPercentTotal );
		else
			StringFn->Format( strStatText, TEXT( "%d" ), iStatFlatTotal );
	} else {
		// Hero View Mode
		HeroID iHeroID = (HeroID)(UIntPtr)( pHeroView->GetItemData(iSelected) );
		const Hero * pHero = CCGOPFn->GetHero( iHeroID );

		UInt iBaseValue = GameDataFn->GetHeroBaseStat( pHero->GetName(), m_iHeroStat, pHero->GetRank(), pHero->GetLevel(), pHero->IsEvolved() );
		if ( pHero->IsSanctified() ) {
			HeroSanctify iSanctify = pHero->GetSanctification();
			UInt iSanctifyBonus = GameDataFn->GetHeroSanctifyBonus( iSanctify );
			switch( iSanctify ) {
				case HERO_SANCTIFY_HP:
					if ( m_iHeroStat == HERO_STAT_HP )
						iBaseValue += (UInt)( ((Float)iSanctifyBonus) * 0.01f * (Float)iBaseValue );
					break;
				case HERO_SANCTIFY_ATT:
					if ( m_iHeroStat == HERO_STAT_ATTACK )
						iBaseValue += (UInt)( ((Float)iSanctifyBonus) * 0.01f * (Float)iBaseValue );
					break;
				case HERO_SANCTIFY_DEF:
					if ( m_iHeroStat == HERO_STAT_DEFENSE )
						iBaseValue += (UInt)( ((Float)iSanctifyBonus) * 0.01f * (Float)iBaseValue );
					break;
				case HERO_SANCTIFY_HIT:
					if ( m_iHeroStat == HERO_STAT_HIT )
						iBaseValue += iSanctifyBonus;
					break;
				case HERO_SANCTIFY_RES:
					if ( m_iHeroStat == HERO_STAT_RESISTANCE )
						iBaseValue += iSanctifyBonus;
					break;
				default: Assert(false); break;
			}
		}

		UInt iBonusValue = iStatFlatTotal + (UInt)( ((Float)iStatPercentTotal) * 0.01f * (Float)iBaseValue );
		UInt iTotalValue = iBaseValue + iBonusValue;

		StringFn->Format( strStatText, TEXT( "%d (+%d)" ), iTotalValue, iBonusValue );
	}

	// Done
	pController->SetText( strStatText );
}

const WinGUILayout * UIGearSetStatsValueModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,1,0,0);
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

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("Set Bonus = ---") );
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
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH * 2;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,HERO_STAT_COUNT,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStatsModeModel implementation
UIGearSetStatsModeModel::UIGearSetStatsModeModel():
	WinGUICheckBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_MODE)
{
	m_pGUI = NULL;
}
UIGearSetStatsModeModel::~UIGearSetStatsModeModel()
{
	// nothing to do
}

Void UIGearSetStatsModeModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->NCopy( m_hCreationParameters.strLabel, TEXT("Max Rune Levels"), 63 );

	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetStatsModeModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_CHECKBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_CHECKBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iX, hClientArea.iWidth );
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1 + HERO_STAT_COUNT,0,0);

	return &hLayout;
}

Bool UIGearSetStatsModeModel::OnClick()
{
	// Update Models
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->UpdateModels();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStatsHeroViewModel implementation
UIGearSetStatsHeroViewModel::UIGearSetStatsHeroViewModel():
	WinGUIComboBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETSTATS_HEROVIEW)
{
	m_pGUI = NULL;
}
UIGearSetStatsHeroViewModel::~UIGearSetStatsHeroViewModel()
{
	// nothing to do
}

Void UIGearSetStatsHeroViewModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	m_hCreationParameters.iItemCallBackMode = WINGUI_COMBOBOX_ITEMCALLBACK_LABELS;

	m_hCreationParameters.iType = WINGUI_COMBOBOX_BUTTON;
	m_hCreationParameters.iCase = WINGUI_COMBOBOX_CASE_BOTH;
	m_hCreationParameters.iInitialSelectedItem = 0;
	m_hCreationParameters.bAllowHorizontalScroll = false;
	m_hCreationParameters.bItemTextEllipsis = true;
	m_hCreationParameters.bCaseSensitiveSearch = false;
	m_hCreationParameters.bAutoSort = false;
	m_hCreationParameters.bEnableTabStop = true;
}
Void UIGearSetStatsHeroViewModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	UInt iIndex = 0;
	HeroInventory::HeroMap::Iterator itHero = CCGOPFn->EnumHeroes();
	while( !(itHero.IsNull()) ) {
		pController->AddItem( iIndex );
		pController->SetItemData( iIndex, (Void*)(itHero.GetKey()) );

		++iIndex;
		++itHero;
	}

	pController->SetCueText( TEXT("Hero View ...") );
}

const WinGUILayout * UIGearSetStatsHeroViewModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iX, hClientArea.iWidth );
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,1 + HERO_STAT_COUNT,0,0);

	return &hLayout;
}

Void UIGearSetStatsHeroViewModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Update Models
		m_pGUI->GetGearSetExplorer()->GetGearSetStats()->UpdateModels();
	}
}

Bool UIGearSetStatsHeroViewModel::OnSelectionOK()
{
	// Update Models
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->UpdateModels();

	return true;
}

Void UIGearSetStatsHeroViewModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);
	HeroID iHeroID = (HeroID)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->Format( outBuffer, TEXT("%s (%d)"), CCGOPFn->GetHero(iHeroID)->GetName(), iHeroID );
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetStats implementation
UIGearSetStats::UIGearSetStats( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	for( UInt i = 0; i < HERO_STAT_COUNT; ++i ) {
		m_arrHeroStats[i].pLabel = NULL;
		m_arrHeroStats[i].pValue = NULL;
	}
	m_pSetBonus = NULL;
	m_pMode = NULL;
	m_pHeroView = NULL;
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
		m_arrHeroStats[i].hLabelModel.Initialize( m_pGUI, (HeroStat)i );
		m_arrHeroStats[i].pLabel = WinGUIFn->CreateStatic( m_pRoot, &(m_arrHeroStats[i].hLabelModel) );

		m_arrHeroStats[i].hValueModel.Initialize( m_pGUI, (HeroStat)i );
		m_arrHeroStats[i].pLabel = WinGUIFn->CreateStatic( m_pRoot, &(m_arrHeroStats[i].hValueModel) );
		m_arrHeroStats[i].hValueModel.Update();
	}

	m_hSetBonusModel.Initialize( m_pGUI );
	m_pSetBonus = WinGUIFn->CreateStatic( m_pRoot, &m_hSetBonusModel );
	m_hSetBonusModel.Update();

	m_hModeModel.Initialize( m_pGUI );
	m_pMode = WinGUIFn->CreateCheckBox( m_pRoot, &m_hModeModel );

	m_hHeroViewModel.Initialize( m_pGUI );
	m_pHeroView = WinGUIFn->CreateComboBox( m_pRoot, &m_hHeroViewModel );
	m_hHeroViewModel.Update();
}
Void UIGearSetStats::Cleanup()
{
	// nothing to do (for now)
}

Void UIGearSetStats::UpdateModels()
{
	for( UInt i = 0; i < HERO_STAT_COUNT; ++i )
		m_arrHeroStats[i].hValueModel.Update();
	m_hSetBonusModel.Update();
}
Void UIGearSetStats::UpdateHeroViewList()
{
	m_hHeroViewModel.Update();
	UpdateModels();
}
