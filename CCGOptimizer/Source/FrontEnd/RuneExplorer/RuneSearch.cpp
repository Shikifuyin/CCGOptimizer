/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/RuneExplorer/RuneSearch.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : RuneExplorer GUI : Rune Search
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
#include "RuneSearch.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchGroupModel implementation
UIRuneSearchGroupModel::UIRuneSearchGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_GROUP)
{
	m_pGUI = NULL;
}
UIRuneSearchGroupModel::~UIRuneSearchGroupModel()
{
	// nothing to do
}

Void UIRuneSearchGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Rune Search :") );
}

const WinGUILayout * UIRuneSearchGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(0,0,4,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,1,3,2) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_RUNEEXPLORER_ROOM_LEFT + CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_RUNEEXPLORER_ROOM_WIDTH );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_RUNEEXPLORER_ROOM_TOP + CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iY, CCGOP_LAYOUT_RUNEEXPLORER_ROOM_HEIGHT );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchSlotModel implementation
UIRuneSearchSlotModel::UIRuneSearchSlotModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_SLOT)
{
	m_pGUI = NULL;
}
UIRuneSearchSlotModel::~UIRuneSearchSlotModel()
{
	// nothing to do
}

Void UIRuneSearchSlotModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneSearchSlotModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Slot ...") );
}

const WinGUILayout * UIRuneSearchSlotModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Void UIRuneSearchSlotModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure available MainStats are consistent
		m_pGUI->GetRuneExplorer()->GetRuneSearch()->UpdateAvailableMainStats();
	}
}

Bool UIRuneSearchSlotModel::OnSelectionOK()
{
	// Ensure available MainStats are consistent
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->UpdateAvailableMainStats();

	// Done
	return true;
}

Void UIRuneSearchSlotModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_SLOT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iSlot = (UInt)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->FromUInt( outBuffer, iSlot + 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchSetModel implementation
UIRuneSearchSetModel::UIRuneSearchSetModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_SET)
{
	m_pGUI = NULL;
}
UIRuneSearchSetModel::~UIRuneSearchSetModel()
{
	// nothing to do
}

Void UIRuneSearchSetModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneSearchSetModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_SET_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Set ...") );
}

const WinGUILayout * UIRuneSearchSetModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,1,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Void UIRuneSearchSetModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SelectItem( INVALID_OFFSET );
}

Bool UIRuneSearchSetModel::OnSelectionOK()
{
	// nothing to do
	return true;
}

Void UIRuneSearchSetModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_SET_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneSet iSet = (RuneSet)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneSetName(iSet), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchRankModel implementation
UIRuneSearchRankModel::UIRuneSearchRankModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_RANK)
{
	m_pGUI = NULL;
}
UIRuneSearchRankModel::~UIRuneSearchRankModel()
{
	// nothing to do
}

Void UIRuneSearchRankModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneSearchRankModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_RANK_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Rank ...") );
}

const WinGUILayout * UIRuneSearchRankModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,2,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Void UIRuneSearchRankModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SelectItem( INVALID_OFFSET );
}

Bool UIRuneSearchRankModel::OnSelectionOK()
{
	// nothing to do
	return true;
}

Void UIRuneSearchRankModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_RANK_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneRank iRank = (RuneRank)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneRankName(iRank), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchQualityModel implementation
UIRuneSearchQualityModel::UIRuneSearchQualityModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_QUALITY)
{
	m_pGUI = NULL;
}
UIRuneSearchQualityModel::~UIRuneSearchQualityModel()
{
	// nothing to do
}

Void UIRuneSearchQualityModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneSearchQualityModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_QUALITY_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Quality ...") );
}

const WinGUILayout * UIRuneSearchQualityModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	return &hLayout;
}

Void UIRuneSearchQualityModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SelectItem( INVALID_OFFSET );
}

Bool UIRuneSearchQualityModel::OnSelectionOK()
{
	// Done
	return true;
}

Void UIRuneSearchQualityModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_QUALITY_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneQuality iQuality = (RuneQuality)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneQualityName(iQuality), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchLevelModel implementation
UIRuneSearchLevelModel::UIRuneSearchLevelModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_LEVEL)
{
	m_pGUI = NULL;
}
UIRuneSearchLevelModel::~UIRuneSearchLevelModel()
{
	// nothing to do
}

Void UIRuneSearchLevelModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneSearchLevelModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i <= RUNE_MAX_LEVEL; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Level ...") );
}

const WinGUILayout * UIRuneSearchLevelModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,1,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	return &hLayout;
}

Void UIRuneSearchLevelModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SelectItem( INVALID_OFFSET );
}

Bool UIRuneSearchLevelModel::OnSelectionOK()
{
	// Done
	return true;
}

Void UIRuneSearchLevelModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex <= RUNE_MAX_LEVEL );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iLevel = (RuneQuality)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->Format( outBuffer, TEXT("+%d"), iLevel );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchMainStatModel implementation
UIRuneSearchMainStatModel::UIRuneSearchMainStatModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_MAINSTAT)
{
	m_pGUI = NULL;

	m_iSelectedSlot = INVALID_OFFSET;
	m_iExcludedStatsCount = 0;
}
UIRuneSearchMainStatModel::~UIRuneSearchMainStatModel()
{
	// nothing to do
}

Void UIRuneSearchMainStatModel::Initialize( CCGOPGUI * pGUI )
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
Void UIRuneSearchMainStatModel::Update( UInt iSelectedSlot, RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
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

const WinGUILayout * UIRuneSearchMainStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,2,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	return &hLayout;
}

Void UIRuneSearchMainStatModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure RuneStat selection doesn't collide
		m_pGUI->GetRuneExplorer()->GetRuneSearch()->ExcludeRuneStats( pController );
	}
}

Bool UIRuneSearchMainStatModel::OnSelectionOK()
{
	// Ensure RuneStat selection doesn't collide
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->ExcludeRuneStats( (WinGUIComboBox*)m_pController );

	// Done
	return true;
}

Void UIRuneSearchMainStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_STAT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchSubStatsModeModel implementation
UIRuneSearchSubStatsModeModel::UIRuneSearchSubStatsModeModel():
	WinGUICheckBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_SUBSTATSMODE)
{
	m_pGUI = NULL;
}
UIRuneSearchSubStatsModeModel::~UIRuneSearchSubStatsModeModel()
{
	// nothing to do
}

Void UIRuneSearchSubStatsModeModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->NCopy( m_hCreationParameters.strLabel, TEXT("Subs : AND Mode"), 63 );

	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneSearchSubStatsModeModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_CHECKBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_CHECKBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,3,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	return &hLayout;
}

Bool UIRuneSearchSubStatsModeModel::OnClick()
{
	WinGUICheckBox * pController = (WinGUICheckBox*)m_pController;

	if ( pController->IsChecked() )
		pController->SetText( TEXT("Subs : OR Mode") );
	else
		pController->SetText( TEXT("Subs : AND Mode") );

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchSubStatModel implementation
UIRuneSearchSubStatModel::UIRuneSearchSubStatModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_SUBSTAT)
{
	m_pGUI = NULL;
	m_iIndex = INVALID_OFFSET;

	m_iExcludedStatsCount = 0;
}
UIRuneSearchSubStatModel::~UIRuneSearchSubStatModel()
{
	// nothing to do
}

Void UIRuneSearchSubStatModel::Initialize( CCGOPGUI * pGUI, UInt iIndex )
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
Void UIRuneSearchSubStatModel::Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
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

	pController->SetCueText( TEXT("SubStat ...") );
}

const WinGUILayout * UIRuneSearchSubStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,m_iIndex,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,2,1);

	return &hLayout;
}

Void UIRuneSearchSubStatModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure RuneStat selection doesn't collide
		m_pGUI->GetRuneExplorer()->GetRuneSearch()->ExcludeRuneStats( pController );
	}
}

Bool UIRuneSearchSubStatModel::OnSelectionOK()
{
	// Ensure RuneStat selection doesn't collide
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->ExcludeRuneStats( (WinGUIComboBox*)m_pController );
	
	// Done
	return true;
}

Void UIRuneSearchSubStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_STAT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchSubStatValueModel implementation
UIRuneSearchSubStatValueModel::UIRuneSearchSubStatValueModel():
	WinGUITextEditModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_SUBSTATVALUE)
{
	m_pGUI = NULL;
	m_iIndex = INVALID_OFFSET;
}
UIRuneSearchSubStatValueModel::~UIRuneSearchSubStatValueModel()
{
	// nothing to do
}

Void UIRuneSearchSubStatValueModel::Initialize( CCGOPGUI * pGUI, UInt iIndex )
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
Void UIRuneSearchSubStatValueModel::Update()
{
	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;
	pController->SetText( TEXT("") );

	pController->SetCueText( TEXT("SubStat Threshold ..."), false );
}

const WinGUILayout * UIRuneSearchSubStatValueModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,m_iIndex,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,3,1);

	return &hLayout;
}

Void UIRuneSearchSubStatValueModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUITextEdit * pController = ((WinGUITextEdit*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SetText( TEXT("") );
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchIndicatorModel implementation
UIRuneSearchIndicatorModel::UIRuneSearchIndicatorModel():
	WinGUIStaticModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_INDICATOR)
{
	m_pGUI = NULL;
}
UIRuneSearchIndicatorModel::~UIRuneSearchIndicatorModel()
{
	// nothing to do
}

Void UIRuneSearchIndicatorModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = true;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("No Active Filter !") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_CENTER;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneSearchIndicatorModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,3,2);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchClearModel implementation
UIRuneSearchClearModel::UIRuneSearchClearModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_CLEAR)
{
	m_pGUI = NULL;
}
UIRuneSearchClearModel::~UIRuneSearchClearModel()
{
	// nothing to do
}

Void UIRuneSearchClearModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Clear Filters") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneSearchClearModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,2,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,3,2);

	return &hLayout;
}

Bool UIRuneSearchClearModel::OnClick()
{
	WinGUITable * pTableController = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();
	UIRuneTableModel * pTableModel = (UIRuneTableModel*)( pTableController->GetModel() );

	UIRuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();

	// Reset all
	pRuneSearch->GetSlot()->SelectItem( INVALID_OFFSET );
	pRuneSearch->GetSet()->SelectItem( INVALID_OFFSET );
	pRuneSearch->GetRank()->SelectItem( INVALID_OFFSET );
	pRuneSearch->GetQuality()->SelectItem( INVALID_OFFSET );
	pRuneSearch->GetLevel()->SelectItem( INVALID_OFFSET );
	pRuneSearch->GetMainStat()->SelectItem( INVALID_OFFSET );
	pRuneSearch->GetSubStatsMode()->Uncheck();
	pRuneSearch->GetSubStatsMode()->SetText( TEXT("Subs : AND Mode") );
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		pRuneSearch->GetSubStat(i)->SelectItem( INVALID_OFFSET );
		pRuneSearch->GetSubStatValue(i)->SetText( TEXT("") );
	}
	pRuneSearch->UpdateAvailableMainStats();
	pRuneSearch->ExcludeRuneStats( NULL );

	// Reset Table
	pTableController->RemoveAllItems();
	pTableModel->UpdateAfterDataLoad();

	// Toggle Indicator
	pRuneSearch->GetIndicator()->SetText( TEXT("No Active Filter !") );

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearchApplyModel implementation
UIRuneSearchApplyModel::UIRuneSearchApplyModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_APPLY)
{
	m_pGUI = NULL;
}
UIRuneSearchApplyModel::~UIRuneSearchApplyModel()
{
	// nothing to do
}

Void UIRuneSearchApplyModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Apply Filters") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIRuneSearchApplyModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,3,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,3,2);

	return &hLayout;
}

Bool UIRuneSearchApplyModel::OnClick()
{
	WinGUITable * pTableController = m_pGUI->GetRuneExplorer()->GetRuneTable()->GetTable();
	UIRuneTableModel * pTableModel = (UIRuneTableModel*)( pTableController->GetModel() );

	UIRuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();

	// Clear Table
	pTableController->RemoveAllItems();

	// Retrieve Rune Slot
	WinGUIComboBox * pRuneSlot = pRuneSearch->GetSlot();
	UInt iSelected = pRuneSlot->GetSelectedItem();

	UInt iSlot = RUNE_SLOT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iSlot = (UInt)(UIntPtr)( pRuneSlot->GetItemData(iSelected) );

	// Retrieve Rune Set
	WinGUIComboBox * pRuneSet = pRuneSearch->GetSet();
	iSelected = pRuneSet->GetSelectedItem();

	RuneSet iSet = RUNE_SET_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iSet = (RuneSet)(UIntPtr)( pRuneSet->GetItemData(iSelected) );

	// Retrieve Rune Rank
	WinGUIComboBox * pRuneRank = pRuneSearch->GetRank();
	iSelected = pRuneRank->GetSelectedItem();

	RuneRank iRank = RUNE_RANK_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iRank = (RuneRank)(UIntPtr)( pRuneRank->GetItemData(iSelected) );

	// Retrieve Rune Quality
	WinGUIComboBox * pRuneQuality = pRuneSearch->GetQuality();
	iSelected = pRuneQuality->GetSelectedItem();

	RuneQuality iQuality = RUNE_QUALITY_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iQuality = (RuneQuality)(UIntPtr)( pRuneQuality->GetItemData(iSelected) );

	// Retrieve Rune Level
	WinGUIComboBox * pRuneLevel = pRuneSearch->GetLevel();
	iSelected = pRuneLevel->GetSelectedItem();

	UInt iLevel = INVALID_OFFSET;
	if ( iSelected != INVALID_OFFSET )
		iLevel = (UInt)(UIntPtr)( pRuneLevel->GetItemData(iSelected) );

	// Retrieve Rune MainStat
	WinGUIComboBox * pRuneMainStat = pRuneSearch->GetMainStat();
	iSelected = pRuneMainStat->GetSelectedItem();

	RuneStat iMainStat = RUNE_STAT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iMainStat = (RuneStat)(UIntPtr)( pRuneMainStat->GetItemData(iSelected) );

	// Retrieve SubStat Mode
	WinGUICheckBox * pSubStatsMode = pRuneSearch->GetSubStatsMode();
	Bool bAndElseOr = !( pSubStatsMode->IsChecked() );

	// Retrieve SubStats
	RuneStat arrSubStats[RUNE_RANDOM_STAT_COUNT];
	UInt arrSubStatsValues[RUNE_RANDOM_STAT_COUNT];
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		WinGUIComboBox * pSubStat = pRuneSearch->GetSubStat( i );
		iSelected = pSubStat->GetSelectedItem();

		arrSubStats[i] = RUNE_STAT_COUNT;
		if ( iSelected != INVALID_OFFSET )
			arrSubStats[i] = (RuneStat)(UIntPtr)( pSubStat->GetItemData(iSelected) );

		WinGUITextEdit * pSubStatValue = pRuneSearch->GetSubStatValue( i );

		arrSubStatsValues[i] = 0;
		if ( arrSubStats[i] != RUNE_STAT_COUNT ) {
			GChar strBuffer[64];
			pSubStatValue->GetText( strBuffer, 63 );
			arrSubStatsValues[i] = (UInt)( StringFn->ToUInt(strBuffer) );
		}
	}

	// Create temporary data
	RuneQueryMap hQueryMap;
	hQueryMap.SetComparator( RuneQueryMap_Compare );
	hQueryMap.Create();

	Array<RuneID> hQueryResults;
	hQueryResults.Create();

	// Build a filter search query
	RuneQueryParameter hQuery;

	if ( iSlot != RUNE_SLOT_COUNT ) {
		hQuery.hQuerySlot.iSlotCount = 1;
		hQuery.hQuerySlot.arrSlots[0] = iSlot;
		hQueryMap.Insert( RUNE_QUERY_SLOT, hQuery );
	}
	if ( iSet != RUNE_SET_COUNT ) {
		hQuery.hQuerySet.iSetCount = 1;
		hQuery.hQuerySet.arrSets[0] = iSet;
		hQueryMap.Insert( RUNE_QUERY_SET, hQuery );
	}
	if ( iRank != RUNE_RANK_COUNT ) {
		hQuery.hQueryRank.iRankCount = 1;
		hQuery.hQueryRank.arrRanks[0] = iRank;
		hQueryMap.Insert( RUNE_QUERY_RANK, hQuery );
	}
	if ( iQuality != RUNE_QUALITY_COUNT ) {
		hQuery.hQueryQuality.iQualityCount = 1;
		hQuery.hQueryQuality.arrQualities[0] = iQuality;
		hQueryMap.Insert( RUNE_QUERY_QUALITY, hQuery );
	}
	if ( iLevel != INVALID_OFFSET ) {
		hQuery.hQueryLevel.iLevelCount = 1;
		hQuery.hQueryLevel.arrLevels[0] = iLevel;
		hQueryMap.Insert( RUNE_QUERY_LEVEL, hQuery );
	}
	if ( iMainStat != RUNE_STAT_COUNT ) {
		hQuery.hQueryMainStat.iStatCount = 1;
		hQuery.hQueryMainStat.arrStats[0] = iMainStat;
		hQueryMap.Insert( RUNE_QUERY_MAINSTAT, hQuery );
	}

	hQuery.hQuerySubStats.bAndElseOr = bAndElseOr;
	hQuery.hQuerySubStats.iStatCount = 0;
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		if ( arrSubStats[i] != RUNE_STAT_COUNT ) {
			hQuery.hQuerySubStats.arrStats[hQuery.hQuerySubStats.iStatCount] = arrSubStats[i];
			hQuery.hQuerySubStats.arrStatValues[hQuery.hQuerySubStats.iStatCount] = arrSubStatsValues[i];
			++(hQuery.hQuerySubStats.iStatCount);
		}
	}
	if ( hQuery.hQuerySubStats.iStatCount > 0 )
		hQueryMap.Insert( RUNE_QUERY_SUBSTATS, hQuery );

	// Perform the Query
	CCGOPFn->FilterRunes( &hQueryResults, hQueryMap, NULL, true, true );

	// Update the Table
	pTableModel->UpdateAfterFiltering( hQueryResults );

	// Clear temporary data
	hQueryResults.Destroy();
	hQueryMap.Destroy();

	// Toggle Indicator
	pRuneSearch->GetIndicator()->SetText( TEXT("Filters are Active !") );

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIRuneSearch implementation
UIRuneSearch::UIRuneSearch( CCGOPGUI * pGUI )
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
	m_pSubStatsMode = NULL;
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		m_arrSubStats[i].pStat = NULL;
		m_arrSubStats[i].pValue = NULL;
	}
	m_pIndicator = NULL;
	m_pClear = NULL;
	m_pApply = NULL;
}
UIRuneSearch::~UIRuneSearch()
{
	// nothing to do
}

Void UIRuneSearch::Initialize()
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

	m_hSubStatsModeModel.Initialize( m_pGUI );
	m_pSubStatsMode = WinGUIFn->CreateCheckBox( m_pRoot, &(m_hSubStatsModeModel) );

	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		m_arrSubStats[i].hStatModel.Initialize( m_pGUI, i );
		m_arrSubStats[i].pStat = WinGUIFn->CreateComboBox( m_pRoot, &(m_arrSubStats[i].hStatModel) );
		m_arrSubStats[i].hStatModel.Update( NULL, 0 );

		m_arrSubStats[i].hValueModel.Initialize( m_pGUI, i );
		m_arrSubStats[i].pValue = WinGUIFn->CreateTextEdit( m_pRoot, &(m_arrSubStats[i].hValueModel) );
		m_arrSubStats[i].hValueModel.Update();
	}

	m_hIndicatorModel.Initialize( m_pGUI );
	m_pIndicator = WinGUIFn->CreateStatic( m_pRoot, &(m_hIndicatorModel) );

	m_hClearModel.Initialize( m_pGUI );
	m_pClear = WinGUIFn->CreateButton( m_pRoot, &(m_hClearModel) );

	m_hApplyModel.Initialize( m_pGUI );
	m_pApply = WinGUIFn->CreateButton( m_pRoot, &(m_hApplyModel) );
}
Void UIRuneSearch::Cleanup()
{
	// nothing to do (for now)
}

Void UIRuneSearch::UpdateAvailableMainStats()
{
	// Retrieve Selected Slot
	UInt iSelected = m_pSlot->GetSelectedItem();

	UInt iSlot = RUNE_SLOT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iSlot = (UInt)(UIntPtr)( m_pSlot->GetItemData(iSelected) );

	// Update MainStatModel content
	m_hMainStatModel.Update( iSlot, NULL, 0 );
}
Void UIRuneSearch::ExcludeRuneStats( WinGUIComboBox * pJustSelected )
{
	UInt i, iSelected, iSelectedStatsCount;
	RuneStat arrSelectedStats[2+RUNE_RANDOM_STAT_COUNT];

	// Retrieve selected MainStat
	iSelected = m_pMainStat->GetSelectedItem();

	RuneStat iMainStat = RUNE_STAT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iMainStat = (RuneStat)(UIntPtr)( m_pMainStat->GetItemData(iSelected) );

	// Retrieve selected SubStats
	RuneStat arrSubStats[RUNE_RANDOM_STAT_COUNT];
	for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		iSelected = m_arrSubStats[i].pStat->GetSelectedItem();

		arrSubStats[i] = RUNE_STAT_COUNT;
		if ( iSelected != INVALID_OFFSET )
			arrSubStats[i] = (RuneStat)(UIntPtr)( m_arrSubStats[i].pStat->GetItemData(iSelected) );
	}

	// Update MainStat model
	if ( m_pMainStat != pJustSelected ) {
		iSelectedStatsCount = 0;
		for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
			arrSelectedStats[iSelectedStatsCount] = arrSubStats[i];
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

	// Update SubStat models
	arrSelectedStats[0] = iMainStat;

	for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		WinGUIComboBox * pStat = m_arrSubStats[i].pStat;

		if ( pStat == pJustSelected )
			continue;

		iSelectedStatsCount = 1;
		for( UInt j = 0; j < RUNE_RANDOM_STAT_COUNT; ++j ) {
			if ( j != i ) {
				arrSelectedStats[iSelectedStatsCount] = arrSubStats[j];
				++iSelectedStatsCount;
			}
		}

		m_arrSubStats[i].hStatModel.Update( arrSelectedStats, iSelectedStatsCount );

		if ( arrSubStats[i] != RUNE_STAT_COUNT ) {
			UInt iIndex, iItemCount = pStat->GetItemCount();
			for( iIndex = 0; iIndex < iItemCount; ++iIndex ) {
				RuneStat iTmpStat = (RuneStat)(UIntPtr)( pStat->GetItemData(iIndex) );
				if ( iTmpStat == arrSubStats[i] ) {
					pStat->SelectItem( iIndex );
					break;
				}
			}
		}
	}
}

