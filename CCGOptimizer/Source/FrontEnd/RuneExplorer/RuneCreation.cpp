/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneCreation.cpp
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
// Includes
#include "RuneCreation.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationGroupModel implementation
UIRuneCreationGroupModel::UIRuneCreationGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_GROUP)
{
	m_pGUI = NULL;
}
UIRuneCreationGroupModel::~UIRuneCreationGroupModel()
{
	// nothing to do
}

Void UIRuneCreationGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Rune Creation :") );
}

const WinGUILayout * UIRuneCreationGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(0,0,4,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,1,3,2) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_RUNEEXPLORER_ROOM_LEFT;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_RUNEEXPLORER_ROOM_TOP + CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iY, CCGOP_LAYOUT_RUNEEXPLORER_ROOM_HEIGHT );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationSlotModel implementation
UIRuneCreationSlotModel::UIRuneCreationSlotModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_SLOT)
{
	m_pGUI = NULL;
}
UIRuneCreationSlotModel::~UIRuneCreationSlotModel()
{
	// nothing to do
}

Void UIRuneCreationSlotModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneCreationSlotModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Slot ...") );
}

const WinGUILayout * UIRuneCreationSlotModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Void UIRuneCreationSlotModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure available MainStats are consistent
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->UpdateAvailableMainStats();
	}
}

Bool UIRuneCreationSlotModel::OnSelectionOK()
{
	// Ensure available MainStats are consistent
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->UpdateAvailableMainStats();

	// Done
	return true;
}

Void UIRuneCreationSlotModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_SLOT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iSlot = (UInt)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->FromUInt( outBuffer, iSlot + 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationSetModel implementation
UIRuneCreationSetModel::UIRuneCreationSetModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_SET)
{
	m_pGUI = NULL;
}
UIRuneCreationSetModel::~UIRuneCreationSetModel()
{
	// nothing to do
}

Void UIRuneCreationSetModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneCreationSetModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_SET_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Set ...") );
}

const WinGUILayout * UIRuneCreationSetModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,1,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Void UIRuneCreationSetModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SelectItem( INVALID_OFFSET );
}

Bool UIRuneCreationSetModel::OnSelectionOK()
{
	// nothing to do
	return true;
}

Void UIRuneCreationSetModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_SET_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneSet iSet = (RuneSet)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneSetName(iSet), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationRankModel implementation
UIRuneCreationRankModel::UIRuneCreationRankModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_RANK)
{
	m_pGUI = NULL;
}
UIRuneCreationRankModel::~UIRuneCreationRankModel()
{
	// nothing to do
}

Void UIRuneCreationRankModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneCreationRankModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_RANK_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Rank ...") );
}

const WinGUILayout * UIRuneCreationRankModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,2,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Void UIRuneCreationRankModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SelectItem( INVALID_OFFSET );
}

Bool UIRuneCreationRankModel::OnSelectionOK()
{
	// nothing to do
	return true;
}

Void UIRuneCreationRankModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_RANK_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneRank iRank = (RuneRank)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneRankName(iRank), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationQualityModel implementation
UIRuneCreationQualityModel::UIRuneCreationQualityModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_QUALITY)
{
	m_pGUI = NULL;
}
UIRuneCreationQualityModel::~UIRuneCreationQualityModel()
{
	// nothing to do
}

Void UIRuneCreationQualityModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneCreationQualityModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_QUALITY_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Quality ...") );
}

const WinGUILayout * UIRuneCreationQualityModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	return &hLayout;
}

Void UIRuneCreationQualityModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure available RandomStat Count is consistent
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->UpdateRandomStatsCount();
	}
}

Bool UIRuneCreationQualityModel::OnSelectionOK()
{
	// Ensure available RandomStat Count is consistent
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->UpdateRandomStatsCount();

	// Done
	return true;
}

Void UIRuneCreationQualityModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_QUALITY_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneQuality iQuality = (RuneQuality)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneQualityName(iQuality), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationLevelModel implementation
UIRuneCreationLevelModel::UIRuneCreationLevelModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_LEVEL)
{
	m_pGUI = NULL;
}
UIRuneCreationLevelModel::~UIRuneCreationLevelModel()
{
	// nothing to do
}

Void UIRuneCreationLevelModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneCreationLevelModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i <= RUNE_MAX_LEVEL; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Level ...") );
}

const WinGUILayout * UIRuneCreationLevelModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,1,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	return &hLayout;
}

Void UIRuneCreationLevelModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure available RandomStat Count is consistent
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->UpdateRandomStatsCount();
	}
}

Bool UIRuneCreationLevelModel::OnSelectionOK()
{
	// Ensure available RandomStat Count is consistent
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->UpdateRandomStatsCount();

	// Done
	return true;
}

Void UIRuneCreationLevelModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex <= RUNE_MAX_LEVEL );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iLevel = (RuneQuality)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->Format( outBuffer, TEXT("+%d"), iLevel );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationMainStatModel implementation
UIRuneCreationMainStatModel::UIRuneCreationMainStatModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_MAINSTAT)
{
	m_pGUI = NULL;

	m_iSelectedSlot = INVALID_OFFSET;
	m_iExcludedStatsCount = 0;
}
UIRuneCreationMainStatModel::~UIRuneCreationMainStatModel()
{
	// nothing to do
}

Void UIRuneCreationMainStatModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneCreationMainStatModel::Update( UInt iSelectedSlot, RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	if ( iSelectedSlot != INVALID_OFFSET )
		m_iSelectedSlot = iSelectedSlot;
	if ( arrExcludedStats != NULL ) {
		Assert( iExcludedStatsCount < 2 + RUNE_RANDOM_STAT_COUNT );
		m_iExcludedStatsCount = iExcludedStatsCount;
		for( UInt i = 0; i < iExcludedStatsCount; ++i )
			m_arrExcludedStats[i] = arrExcludedStats[i];
	}

	UInt iIndex = 0;
	for( UInt i = 0; i < RUNE_STAT_COUNT; ++i ) {
		// Check if the stat is allowed on selected slot
		if ( (m_iSelectedSlot == RUNE_SLOT_COUNT) || GameDataFn->IsRuneMainStatAllowed((RuneStat)i, m_iSelectedSlot) ) {
			// Check if the stat is excluded
			Bool bExcluded = false;
			for( UInt j = 0; j < m_iExcludedStatsCount; ++j ) {
				if ( m_arrExcludedStats[j] == (RuneStat)i ) {
					bExcluded = true;
					break;
				}
			}
			if ( bExcluded )
				continue;

			pController->AddItem( iIndex );
			pController->SetItemData( iIndex, (Void*)i );
			++iIndex;
		}
	}

	pController->SetCueText( TEXT("Rune MainStat ...") );
}

const WinGUILayout * UIRuneCreationMainStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,2,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	return &hLayout;
}

Void UIRuneCreationMainStatModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure RuneStat selection doesn't collide
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->ExcludeRuneStats( pController );
	}
}

Bool UIRuneCreationMainStatModel::OnSelectionOK()
{
	// Ensure RuneStat selection doesn't collide
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->ExcludeRuneStats( (WinGUIComboBox*)m_pController );

	// Done
	return true;
}

Void UIRuneCreationMainStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_STAT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationInnateStatModel implementation
UIRuneCreationInnateStatModel::UIRuneCreationInnateStatModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_INNATESTAT)
{
	m_pGUI = NULL;

	m_iExcludedStatsCount = 0;
}
UIRuneCreationInnateStatModel::~UIRuneCreationInnateStatModel()
{
	// nothing to do
}

Void UIRuneCreationInnateStatModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneCreationInnateStatModel::Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	if ( arrExcludedStats != NULL ) {
		Assert( iExcludedStatsCount < 2 + RUNE_RANDOM_STAT_COUNT );
		m_iExcludedStatsCount = iExcludedStatsCount;
		for( UInt i = 0; i < iExcludedStatsCount; ++i )
			m_arrExcludedStats[i] = arrExcludedStats[i];
	}

	UInt iIndex = 0;
	for( UInt i = 0; i < RUNE_STAT_COUNT; ++i ) {
		// Check if the stat is excluded
		Bool bExcluded = false;
		for( UInt j = 0; j < m_iExcludedStatsCount; ++j ) {
			if ( m_arrExcludedStats[j] == (RuneStat)i ) {
				bExcluded = true;
				break;
			}
		}
		if ( bExcluded )
			continue;

		pController->AddItem( iIndex );
		pController->SetItemData( iIndex, (Void*)i );
		++iIndex;
	}

	pController->SetCueText( TEXT("InnateStat ...") );
}

const WinGUILayout * UIRuneCreationInnateStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,3,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Void UIRuneCreationInnateStatModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure RuneStat selection doesn't collide
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->ExcludeRuneStats( pController );
	}
}

Bool UIRuneCreationInnateStatModel::OnSelectionOK()
{
	// Ensure RuneStat selection doesn't collide
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->ExcludeRuneStats( (WinGUIComboBox*)m_pController );

	// Done
	return true;
}

Void UIRuneCreationInnateStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_STAT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationInnateStatValueModel implementation
UIRuneCreationInnateStatValueModel::UIRuneCreationInnateStatValueModel():
	WinGUITextEditModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_INNATESTATVALUE)
{
	m_pGUI = NULL;
}
UIRuneCreationInnateStatValueModel::~UIRuneCreationInnateStatValueModel()
{
	// nothing to do
}

Void UIRuneCreationInnateStatValueModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strInitialText, TEXT("") );
	m_hCreationParameters.iAlign = WINGUI_TEXTEDIT_ALIGN_RIGHT;
	m_hCreationParameters.iCase = WINGUI_TEXTEDIT_CASE_BOTH;
	m_hCreationParameters.iMode = WINGUI_TEXTEDIT_MODE_NUMERIC;
	m_hCreationParameters.bAllowHorizontalScroll = false;
	m_hCreationParameters.bDontHideSelection = false;
	m_hCreationParameters.bReadOnly = false;
	m_hCreationParameters.bEnableTabStop = true;
}
Void UIRuneCreationInnateStatValueModel::Update()
{
	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;
	pController->SetText( TEXT("") );

	pController->SetCueText( TEXT("InnateStat Value ..."), false );
}

const WinGUILayout * UIRuneCreationInnateStatValueModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,3,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	return &hLayout;
}

Void UIRuneCreationInnateStatValueModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUITextEdit * pController = ((WinGUITextEdit*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SetText( TEXT("") );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationRandomStatModel implementation
UIRuneCreationRandomStatModel::UIRuneCreationRandomStatModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_RANDOMSTAT)
{
	m_pGUI = NULL;
	m_iIndex = INVALID_OFFSET;

	m_iExcludedStatsCount = 0;
}
UIRuneCreationRandomStatModel::~UIRuneCreationRandomStatModel()
{
	// nothing to do
}

Void UIRuneCreationRandomStatModel::Initialize( CCGOPGUI * pGUI, UInt iIndex )
{
	m_pGUI = pGUI;
	m_iIndex = iIndex;

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
Void UIRuneCreationRandomStatModel::Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	if ( arrExcludedStats != NULL ) {
		Assert( iExcludedStatsCount < 2 + RUNE_RANDOM_STAT_COUNT );
		m_iExcludedStatsCount = iExcludedStatsCount;
		for( UInt i = 0; i < iExcludedStatsCount; ++i )
			m_arrExcludedStats[i] = arrExcludedStats[i];
	}

	UInt iIndex = 0;
	for( UInt i = 0; i < RUNE_STAT_COUNT; ++i ) {
		// Check if the stat is excluded
		Bool bExcluded = false;
		for( UInt j = 0; j < m_iExcludedStatsCount; ++j ) {
			if ( m_arrExcludedStats[j] == (RuneStat)i ) {
				bExcluded = true;
				break;
			}
		}
		if ( bExcluded )
			continue;

		pController->AddItem( iIndex );
		pController->SetItemData( iIndex, (Void*)i );
		++iIndex;
	}

	pController->SetCueText( TEXT("RandomStat ...") );
}

const WinGUILayout * UIRuneCreationRandomStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,m_iIndex,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,2,1);

	return &hLayout;
}

Void UIRuneCreationRandomStatModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure RuneStat selection doesn't collide
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->ExcludeRuneStats( pController );
	}
}

Bool UIRuneCreationRandomStatModel::OnSelectionOK()
{
	// Ensure RuneStat selection doesn't collide
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->ExcludeRuneStats( (WinGUIComboBox*)m_pController );
	
	// Done
	return true;
}

Void UIRuneCreationRandomStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_STAT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationRandomStatValueModel implementation
UIRuneCreationRandomStatValueModel::UIRuneCreationRandomStatValueModel():
	WinGUITextEditModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_RANDOMSTATVALUE)
{
	m_pGUI = NULL;
	m_iIndex = INVALID_OFFSET;
}
UIRuneCreationRandomStatValueModel::~UIRuneCreationRandomStatValueModel()
{
	// nothing to do
}

Void UIRuneCreationRandomStatValueModel::Initialize( CCGOPGUI * pGUI, UInt iIndex )
{
	m_pGUI = pGUI;
	m_iIndex = iIndex;

	StringFn->Copy( m_hCreationParameters.strInitialText, TEXT("") );
	m_hCreationParameters.iAlign = WINGUI_TEXTEDIT_ALIGN_RIGHT;
	m_hCreationParameters.iCase = WINGUI_TEXTEDIT_CASE_BOTH;
	m_hCreationParameters.iMode = WINGUI_TEXTEDIT_MODE_NUMERIC;
	m_hCreationParameters.bAllowHorizontalScroll = false;
	m_hCreationParameters.bDontHideSelection = false;
	m_hCreationParameters.bReadOnly = false;
	m_hCreationParameters.bEnableTabStop = true;
}
Void UIRuneCreationRandomStatValueModel::Update()
{
	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;
	pController->SetText( TEXT("") );

	pController->SetCueText( TEXT("RandomStat Value ..."), false );
}

const WinGUILayout * UIRuneCreationRandomStatValueModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,m_iIndex,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,3,1);

	return &hLayout;
}

Void UIRuneCreationRandomStatValueModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUITextEdit * pController = ((WinGUITextEdit*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SetText( TEXT("") );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreationButtonModel implementation
UIRuneCreationButtonModel::UIRuneCreationButtonModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_CREATE)
{
	m_pGUI = NULL;
}
UIRuneCreationButtonModel::~UIRuneCreationButtonModel()
{
	// nothing to do
}

Void UIRuneCreationButtonModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Create") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneCreationButtonModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,3,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,3,2);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool UIRuneCreationButtonModel::OnClick()
{
	UIRuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();

	// Error Message
	WinGUIMessageBoxOptions hOptions;
	hOptions.iType = WINGUI_MESSAGEBOX_OK;
	hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_ERROR;
	hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_OK;
	hOptions.bMustAnswer = true;

	// Retrieve Rune Slot
	WinGUIComboBox * pRuneSlot = pRuneCreation->GetSlot();
	UInt iSelected = pRuneSlot->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Slot !"), hOptions );
		return true;
	}

	UInt iSlot = (UInt)(UIntPtr)( pRuneSlot->GetItemData(iSelected) );

	// Retrieve Rune Set
	WinGUIComboBox * pRuneSet = pRuneCreation->GetSet();
	iSelected = pRuneSet->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Set !"), hOptions );
		return true;
	}

	RuneSet iSet = (RuneSet)(UIntPtr)( pRuneSet->GetItemData(iSelected) );

	// Retrieve Rune Rank
	WinGUIComboBox * pRuneRank = pRuneCreation->GetRank();
	iSelected = pRuneRank->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Rank !"), hOptions );
		return true;
	}

	RuneRank iRank = (RuneRank)(UIntPtr)( pRuneRank->GetItemData(iSelected) );

	// Retrieve Rune Quality
	WinGUIComboBox * pRuneQuality = pRuneCreation->GetQuality();
	iSelected = pRuneQuality->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Quality !"), hOptions );
		return true;
	}

	RuneQuality iQuality = (RuneQuality)(UIntPtr)( pRuneQuality->GetItemData(iSelected) );

	// Retrieve Rune Level
	WinGUIComboBox * pRuneLevel = pRuneCreation->GetLevel();
	iSelected = pRuneLevel->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Level !"), hOptions );
		return true;
	}

	UInt iLevel = (UInt)(UIntPtr)( pRuneLevel->GetItemData(iSelected) );

	// Retrieve Rune MainStat
	WinGUIComboBox * pRuneMainStat = pRuneCreation->GetMainStat();
	iSelected = pRuneMainStat->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Main Stat !"), hOptions );
		return true;
	}

	RuneStat iMainStat = (RuneStat)(UIntPtr)( pRuneMainStat->GetItemData(iSelected) );

	// Retrieve Rune InnateStat
	WinGUIComboBox * pRuneInnateStat = pRuneCreation->GetInnateStat();
	iSelected = pRuneInnateStat->GetSelectedItem();
	
	RuneStat iInnateStat = RUNE_STAT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iInnateStat = (RuneStat)(UIntPtr)( pRuneInnateStat->GetItemData(iSelected) );

	// Retrieve Rune InnateStat Value
	WinGUITextEdit * pRuneInnateStatValue = pRuneCreation->GetInnateStatValue();

	UInt iInnateStatValue = 0;
	if ( iInnateStat != RUNE_STAT_COUNT ) {
		GChar strBuffer[64];
		pRuneInnateStatValue->GetText( strBuffer, 63 );

		iInnateStatValue = (UInt)( StringFn->ToUInt(strBuffer) );
		if ( iInnateStatValue == 0 ) {
			WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a valid Innate Stat value !"), hOptions );
			return true;
		}
	}

	// Compute Required Random Stat Count
	UInt iRequiredRandomStatsCount = GameDataFn->GetRuneRandomStatCount( iQuality, iLevel );

	// Retrieve Rune RandomStats
	UInt iRandomStatsCount = 0;
	RuneStat arrRandomStats[RUNE_RANDOM_STAT_COUNT];
	UInt arrRandomStatsValues[RUNE_RANDOM_STAT_COUNT];

	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		// Retrieve Rune RandomStat
		WinGUIComboBox * pRuneRandomStat = pRuneCreation->GetRandomStat( i );
		iSelected = pRuneRandomStat->GetSelectedItem();
		
		arrRandomStats[iRandomStatsCount] = RUNE_STAT_COUNT;
		if ( iSelected != INVALID_OFFSET )
			arrRandomStats[iRandomStatsCount] = (RuneStat)(UIntPtr)( pRuneRandomStat->GetItemData(iSelected) );

		// Retrieve Rune RandomStat Value
		WinGUITextEdit * pRuneRandomStatValue = pRuneCreation->GetRandomStatValue( i );

		arrRandomStatsValues[iRandomStatsCount] = 0;
		if ( arrRandomStats[iRandomStatsCount] != RUNE_STAT_COUNT ) {
			GChar strBuffer[64];
			pRuneRandomStatValue->GetText( strBuffer, 63 );

			arrRandomStatsValues[iRandomStatsCount] = (UInt)( StringFn->ToUInt(strBuffer) );
			if ( arrRandomStatsValues[iRandomStatsCount] == 0 ) {
				WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a valid Random Stat value !"), hOptions );
				return true;
			}

			++iRandomStatsCount;
		}
	}
	if ( iRandomStatsCount < iRequiredRandomStatsCount ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please fill in the required Random Stats and their values !"), hOptions );
		return true;
	}

	// Confirmation Message
	hOptions.iType = WINGUI_MESSAGEBOX_OKCANCEL;
	hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_INFO;
	hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_OK;
	hOptions.bMustAnswer = true;

	GChar strBuffer[512];
	GChar * pAppend = strBuffer;
	pAppend = StringFn->Format( pAppend, TEXT("You are about to create a slot %d +%d %s %s %s Rune with the following stats :"),
							    iSlot,
							    iLevel,
							    GameDataFn->GetRuneRankName(iRank),
							    GameDataFn->GetRuneQualityName(iQuality),
							    GameDataFn->GetRuneSetName(iSet) );
	pAppend = StringFn->Format( pAppend, TEXT("\n - Main Stat : %s"), GameDataFn->GetRuneStatName(iMainStat) );
	if ( iInnateStat != RUNE_STAT_COUNT )
		pAppend = StringFn->Format( pAppend, TEXT("\n - Innate Stat : %s = %d"), GameDataFn->GetRuneStatName(iInnateStat), iInnateStatValue );
	for( UInt i = 0; i < iRandomStatsCount; ++i )
		pAppend = StringFn->Format( pAppend, TEXT("\n - Random Stat (%d) : %s = %d"), i, GameDataFn->GetRuneStatName(arrRandomStats[i]), arrRandomStatsValues[i] );
	pAppend = StringFn->Format( pAppend, TEXT("\n\n Do you want to continue ?") );

	WinGUIMessageBoxResponse iResponse = WinGUIFn->SpawnMessageBox( TEXT("Confirmation"), strBuffer, hOptions );

	// Abort
	if ( iResponse != WINGUI_MESSAGEBOX_RESPONSE_OK )
		return true;

	// Create the Rune
	RuneID iRuneID = CCGOPFn->CreateRune( iSlot, iSet, iRank, iQuality, iLevel, iMainStat, iInnateStat, iInnateStatValue,
										  iRandomStatsCount, arrRandomStats, arrRandomStatsValues );

	// Update RuneTable
	WinGUITable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();
	UIRuneTableModel * pModel = (UIRuneTableModel*)( pRuneTable->GetModel() );
	pModel->UpdateAfterRuneCreation( iRuneID );

	// Set Unsaved Changes Mark
	m_pGUI->GetImportExport()->GetLoadSave()->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneCreation implementation
UIRuneCreation::UIRuneCreation( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pSlot = NULL;
	m_pSet = NULL;
	m_pRank = NULL;
	m_pQuality = NULL;
	m_pLevel = NULL;
	m_pMainStat = NULL;
	m_pInnateStat = NULL;
	m_pInnateStatValue = NULL;
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		m_arrRandomStats[i].pStat = NULL;
		m_arrRandomStats[i].pValue = NULL;
	}
	m_pButton = NULL;
}
UIRuneCreation::~UIRuneCreation()
{
	// nothing to do
}

Void UIRuneCreation::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_RUNE_EXPLORER );

	// Build Hero Creation UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &(m_hGroupModel) );

	m_hSlotModel.Initialize( m_pGUI );
	m_pSlot = WinGUIFn->CreateComboBox( m_pRoot, &(m_hSlotModel) );
	m_hSlotModel.Update();

	m_hSetModel.Initialize( m_pGUI );
	m_pSet = WinGUIFn->CreateComboBox( m_pRoot, &(m_hSetModel) );
	m_hSetModel.Update();

	m_hRankModel.Initialize( m_pGUI );
	m_pRank = WinGUIFn->CreateComboBox( m_pRoot, &(m_hRankModel) );
	m_hRankModel.Update();

	m_hQualityModel.Initialize( m_pGUI );
	m_pQuality = WinGUIFn->CreateComboBox( m_pRoot, &(m_hQualityModel) );
	m_hQualityModel.Update();

	m_hLevelModel.Initialize( m_pGUI );
	m_pLevel = WinGUIFn->CreateComboBox( m_pRoot, &(m_hLevelModel) );
	m_hLevelModel.Update();

	m_hMainStatModel.Initialize( m_pGUI );
	m_pMainStat = WinGUIFn->CreateComboBox( m_pRoot, &(m_hMainStatModel) );
	m_hMainStatModel.Update( RUNE_SLOT_COUNT, NULL, 0 );

	m_hInnateStatModel.Initialize( m_pGUI );
	m_pInnateStat = WinGUIFn->CreateComboBox( m_pRoot, &(m_hInnateStatModel) );
	m_hInnateStatModel.Update( NULL, 0 );

	m_hInnateStatValueModel.Initialize( m_pGUI );
	m_pInnateStatValue = WinGUIFn->CreateTextEdit( m_pRoot, &(m_hInnateStatValueModel) );
	m_hInnateStatValueModel.Update();

	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		m_arrRandomStats[i].hStatModel.Initialize( m_pGUI, i );
		m_arrRandomStats[i].pStat = WinGUIFn->CreateComboBox( m_pRoot, &(m_arrRandomStats[i].hStatModel) );
		m_arrRandomStats[i].hStatModel.Update( NULL, 0 );

		m_arrRandomStats[i].hValueModel.Initialize( m_pGUI, i );
		m_arrRandomStats[i].pValue = WinGUIFn->CreateTextEdit( m_pRoot, &(m_arrRandomStats[i].hValueModel) );
		m_arrRandomStats[i].hValueModel.Update();
	}

	m_hButtonModel.Initialize( m_pGUI );
	m_pButton = WinGUIFn->CreateButton( m_pRoot, &(m_hButtonModel) );
}
Void UIRuneCreation::Cleanup()
{
	// nothing to do (for now)
}

Void UIRuneCreation::UpdateAvailableMainStats()
{
	// Retrieve Selected Slot
	UInt iSelected = m_pSlot->GetSelectedItem();

	UInt iSlot = RUNE_SLOT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iSlot = (UInt)(UIntPtr)( m_pSlot->GetItemData(iSelected) );

	// Update MainStatModel content
	m_hMainStatModel.Update( iSlot, NULL, 0 );
}
Void UIRuneCreation::UpdateRandomStatsCount()
{
	// Retrieve selected Quality
	UInt iSelected = m_pQuality->GetSelectedItem();

	RuneQuality iQuality = (RuneQuality)(UIntPtr)( m_pQuality->GetItemData(iSelected) );

	// Retrieve selected Level
	iSelected = m_pLevel->GetSelectedItem();

	UInt iLevel = (UInt)(UIntPtr)( m_pLevel->GetItemData(iSelected) );

	// Get number of random stats allowed
	UInt iAllowedRandomStats = GameDataFn->GetRuneRandomStatCount( iQuality, iLevel );
	
	// Update RandomStat controllers
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		WinGUIComboBox * pStat = m_arrRandomStats[i].pStat;
		WinGUITextEdit * pStatValue = m_arrRandomStats[i].pValue;

		if ( i < iAllowedRandomStats ) {
			pStat->Enable();
			pStatValue->Enable();
		} else {
			pStat->SelectItem( INVALID_OFFSET );
			ExcludeRuneStats( pStat );

			pStat->Disable();
			pStatValue->Disable();
		}
	}
}
Void UIRuneCreation::ExcludeRuneStats( WinGUIComboBox * pJustSelected )
{
	UInt i, iSelected, iSelectedStatsCount;
	RuneStat arrSelectedStats[2+RUNE_RANDOM_STAT_COUNT];

	// Retrieve selected MainStat
	iSelected = m_pMainStat->GetSelectedItem();

	RuneStat iMainStat = RUNE_STAT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iMainStat = (RuneStat)(UIntPtr)( m_pMainStat->GetItemData(iSelected) );

	// Retrieve selected InnateStat
	iSelected = m_pInnateStat->GetSelectedItem();

	RuneStat iInnateStat = RUNE_STAT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iInnateStat = (RuneStat)(UIntPtr)( m_pInnateStat->GetItemData(iSelected) );

	// Retrieve selected RandomStats
	RuneStat arrRandomStats[RUNE_RANDOM_STAT_COUNT];
	for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		iSelected = m_arrRandomStats[i].pStat->GetSelectedItem();

		arrRandomStats[i] = RUNE_STAT_COUNT;
		if ( iSelected != INVALID_OFFSET )
			arrRandomStats[i] = (RuneStat)(UIntPtr)( m_arrRandomStats[i].pStat->GetItemData(iSelected) );
	}

	// Update MainStat model
	if ( m_pMainStat != pJustSelected ) {
		arrSelectedStats[0] = iInnateStat;
		iSelectedStatsCount = 1;
		for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
			arrSelectedStats[iSelectedStatsCount] = arrRandomStats[i];
			++iSelectedStatsCount;
		}

		m_hMainStatModel.Update( INVALID_OFFSET, arrSelectedStats, iSelectedStatsCount );

		if ( iMainStat != RUNE_STAT_COUNT ) {
			UInt iIndex, iItemCount = m_pMainStat->GetItemCount();
			for( iIndex = 0; iIndex < iItemCount; ++iIndex ) {
				RuneStat iTmpStat = (RuneStat)(UIntPtr)( m_pMainStat->GetItemData(iIndex) );
				if ( iTmpStat == iMainStat ) {
					m_pMainStat->SelectItem( iIndex );
					break;
				}
			}
		}
	}

	// Update InnateStat model
	if ( m_pInnateStat != pJustSelected ) {
		arrSelectedStats[0] = iMainStat;
		iSelectedStatsCount = 1;
		for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
			arrSelectedStats[iSelectedStatsCount] = arrRandomStats[i];
			++iSelectedStatsCount;
		}

		m_hInnateStatModel.Update( arrSelectedStats, iSelectedStatsCount );

		if ( iInnateStat != RUNE_STAT_COUNT ) {
			UInt iIndex, iItemCount = m_pInnateStat->GetItemCount();
			for( iIndex = 0; iIndex < iItemCount; ++iIndex ) {
				RuneStat iTmpStat = (RuneStat)(UIntPtr)( m_pInnateStat->GetItemData(iIndex) );
				if ( iTmpStat == iInnateStat ) {
					m_pInnateStat->SelectItem( iIndex );
					break;
				}
			}
		}
	}

	// Update RandomStat models
	arrSelectedStats[0] = iMainStat;
	arrSelectedStats[1] = iInnateStat;

	for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		WinGUIComboBox * pStat = m_arrRandomStats[i].pStat;

		if ( pStat == pJustSelected )
			continue;

		iSelectedStatsCount = 2;
		for( UInt j = 0; j < RUNE_RANDOM_STAT_COUNT; ++j ) {
			if ( j != i ) {
				arrSelectedStats[iSelectedStatsCount] = arrRandomStats[j];
				++iSelectedStatsCount;
			}
		}

		m_arrRandomStats[i].hStatModel.Update( arrSelectedStats, iSelectedStatsCount );

		if ( arrRandomStats[i] != RUNE_STAT_COUNT ) {
			UInt iIndex, iItemCount = pStat->GetItemCount();
			for( iIndex = 0; iIndex < iItemCount; ++iIndex ) {
				RuneStat iTmpStat = (RuneStat)(UIntPtr)( pStat->GetItemData(iIndex) );
				if ( iTmpStat == arrRandomStats[i] ) {
					pStat->SelectItem( iIndex );
					break;
				}
			}
		}
	}
}

