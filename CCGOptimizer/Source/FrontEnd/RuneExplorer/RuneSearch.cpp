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
// RuneSearchGroupModel implementation
RuneSearchGroupModel::RuneSearchGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_GROUP)
{
	m_pGUI = NULL;
}
RuneSearchGroupModel::~RuneSearchGroupModel()
{
	// nothing to do
}

Void RuneSearchGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Rune Search :") );
}

const WinGUILayout * RuneSearchGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(0,0,4,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,1,3,2) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ROOM_LEFT + CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_ROOM_WIDTH );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ROOM_TOP + CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iY, CCGOP_LAYOUT_ROOM_HEIGHT );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchSlotModel implementation
RuneSearchSlotModel::RuneSearchSlotModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_SLOT)
{
	m_pGUI = NULL;
}
RuneSearchSlotModel::~RuneSearchSlotModel()
{
	// nothing to do
}

Void RuneSearchSlotModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneSearchSlotModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Slot ...") );
}

const WinGUILayout * RuneSearchSlotModel::GetLayout() const
{
	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneSearchSlotModel::OnSelectionOK()
{
	// Ensure available MainStats are consistent
	m_pGUI->GetRuneExplorer()->GetRuneSearch()->_UpdateAvailableMainStats();

	// Done
	return true;
}

Void RuneSearchSlotModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_SLOT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iSlot = (UInt)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->FromUInt( outBuffer, iSlot + 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchSetModel implementation
RuneSearchSetModel::RuneSearchSetModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_SET)
{
	m_pGUI = NULL;
}
RuneSearchSetModel::~RuneSearchSetModel()
{
	// nothing to do
}

Void RuneSearchSetModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneSearchSetModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_SET_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Set ...") );
}

const WinGUILayout * RuneSearchSetModel::GetLayout() const
{
	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,1,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneSearchSetModel::OnSelectionOK()
{
	// nothing to do
	return true;
}

Void RuneSearchSetModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_SET_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneSet iSet = (RuneSet)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneSetName(iSet), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchRankModel implementation
RuneSearchRankModel::RuneSearchRankModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_RANK)
{
	m_pGUI = NULL;
}
RuneSearchRankModel::~RuneSearchRankModel()
{
	// nothing to do
}

Void RuneSearchRankModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneSearchRankModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_RANK_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Rank ...") );
}

const WinGUILayout * RuneSearchRankModel::GetLayout() const
{
	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,2,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneSearchRankModel::OnSelectionOK()
{
	// nothing to do
	return true;
}

Void RuneSearchRankModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_RANK_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneRank iRank = (RuneRank)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneRankName(iRank), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchQualityModel implementation
RuneSearchQualityModel::RuneSearchQualityModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_QUALITY)
{
	m_pGUI = NULL;
}
RuneSearchQualityModel::~RuneSearchQualityModel()
{
	// nothing to do
}

Void RuneSearchQualityModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneSearchQualityModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_QUALITY_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Quality ...") );
}

const WinGUILayout * RuneSearchQualityModel::GetLayout() const
{
	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneSearchQualityModel::OnSelectionOK()
{
	// Done
	return true;
}

Void RuneSearchQualityModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_QUALITY_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneQuality iQuality = (RuneQuality)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneQualityName(iQuality), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchLevelModel implementation
RuneSearchLevelModel::RuneSearchLevelModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_LEVEL)
{
	m_pGUI = NULL;
}
RuneSearchLevelModel::~RuneSearchLevelModel()
{
	// nothing to do
}

Void RuneSearchLevelModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneSearchLevelModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i <= RUNE_MAX_LEVEL; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Level ...") );
}

const WinGUILayout * RuneSearchLevelModel::GetLayout() const
{
	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,1,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneSearchLevelModel::OnSelectionOK()
{
	// Done
	return true;
}

Void RuneSearchLevelModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex <= RUNE_MAX_LEVEL );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iLevel = (RuneQuality)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->Format( outBuffer, TEXT("+%d"), iLevel );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchMainStatModel implementation
RuneSearchMainStatModel::RuneSearchMainStatModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_MAINSTAT)
{
	m_pGUI = NULL;

	m_iSelectedSlot = INVALID_OFFSET;
	m_iExcludedStatsCount = 0;
}
RuneSearchMainStatModel::~RuneSearchMainStatModel()
{
	// nothing to do
}

Void RuneSearchMainStatModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneSearchMainStatModel::Update( UInt iSelectedSlot, RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
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

const WinGUILayout * RuneSearchMainStatModel::GetLayout() const
{
	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,2,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneSearchMainStatModel::OnSelectionOK()
{
	// Ensure RuneStat selection doesn't collide
	//m_pGUI->GetRuneExplorer()->GetRuneSearch()->_ExcludeRuneStats( (WinGUIComboBox*)m_pController );

	// Done
	return true;
}

Void RuneSearchMainStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_STAT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchRandomStatModel implementation
//RuneSearchRandomStatModel::RuneSearchRandomStatModel():
//	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_RANDOMSTAT)
//{
//	m_pGUI = NULL;
//	m_iIndex = INVALID_OFFSET;
//
//	m_iExcludedStatsCount = 0;
//}
//RuneSearchRandomStatModel::~RuneSearchRandomStatModel()
//{
//	// nothing to do
//}
//
//Void RuneSearchRandomStatModel::Initialize( CCGOPGUI * pGUI, UInt iIndex )
//{
//	m_pGUI = pGUI;
//	m_iIndex = iIndex;
//
//	m_hCreationParameters.iItemCallBackMode = WINGUI_COMBOBOX_ITEMCALLBACK_LABELS;
//
//	m_hCreationParameters.iType = WINGUI_COMBOBOX_BUTTON;
//	m_hCreationParameters.iCase = WINGUI_COMBOBOX_CASE_BOTH;
//	m_hCreationParameters.iInitialSelectedItem = 0;
//	m_hCreationParameters.bAllowHorizontalScroll = false;
//	m_hCreationParameters.bItemTextEllipsis = true;
//	m_hCreationParameters.bCaseSensitiveSearch = false;
//	m_hCreationParameters.bAutoSort = false;
//	m_hCreationParameters.bEnableTabStop = true;
//}
//Void RuneSearchRandomStatModel::Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
//{
//	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
//	pController->RemoveAllItems();
//
//	if ( arrExcludedStats != NULL ) {
//		Assert( iExcludedStatsCount < 2 + RUNE_RANDOM_STAT_COUNT );
//		m_iExcludedStatsCount = iExcludedStatsCount;
//		for( UInt i = 0; i < iExcludedStatsCount; ++i )
//			m_arrExcludedStats[i] = arrExcludedStats[i];
//	}
//
//	UInt iIndex = 0;
//	for( UInt i = 0; i < RUNE_STAT_COUNT; ++i ) {
//		// Check if the stat is excluded
//		Bool bExcluded = false;
//		for( UInt j = 0; j < m_iExcludedStatsCount; ++j ) {
//			if ( m_arrExcludedStats[j] == (RuneStat)i ) {
//				bExcluded = true;
//				break;
//			}
//		}
//		if ( bExcluded )
//			continue;
//
//		pController->AddItem( iIndex );
//		pController->SetItemData( iIndex, (Void*)i );
//		++iIndex;
//	}
//
//	pController->SetCueText( TEXT("RandomStat ...") );
//}
//
//const WinGUILayout * RuneSearchRandomStatModel::GetLayout() const
//{
//	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
//	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;
//
//	WinGUIRectangle hClientArea;
//	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );
//
//	static WinGUIManualLayout hLayout;
//
//	hLayout.UseScalingPosition = false;
//	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,m_iIndex,0);
//	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,2,1);
//
//	hLayout.UseScalingSize = false;
//	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
//	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;
//
//	return &hLayout;
//}
//
//Bool RuneSearchRandomStatModel::OnSelectionOK()
//{
//	// Ensure RuneStat selection doesn't collide
//	m_pGUI->GetRuneExplorer()->GetRuneSearch()->_ExcludeRuneStats( (WinGUIComboBox*)m_pController );
//	
//	// Done
//	return true;
//}
//
//Void RuneSearchRandomStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
//{
//	Assert( iItemIndex < RUNE_STAT_COUNT );
//
//	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
//	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );
//
//	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
//}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchRandomStatValueModel implementation
//RuneSearchRandomStatValueModel::RuneSearchRandomStatValueModel():
//	WinGUITextEditModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_RANDOMSTATVALUE)
//{
//	m_pGUI = NULL;
//	m_iIndex = INVALID_OFFSET;
//}
//RuneSearchRandomStatValueModel::~RuneSearchRandomStatValueModel()
//{
//	// nothing to do
//}
//
//Void RuneSearchRandomStatValueModel::Initialize( CCGOPGUI * pGUI, UInt iIndex )
//{
//	m_pGUI = pGUI;
//	m_iIndex = iIndex;
//
//	StringFn->Copy( m_hCreationParameters.strInitialText, TEXT("") );
//	m_hCreationParameters.iAlign = WINGUI_TEXTEDIT_ALIGN_RIGHT;
//	m_hCreationParameters.iCase = WINGUI_TEXTEDIT_CASE_BOTH;
//	m_hCreationParameters.iMode = WINGUI_TEXTEDIT_MODE_NUMERIC;
//	m_hCreationParameters.bAllowHorizontalScroll = false;
//	m_hCreationParameters.bDontHideSelection = false;
//	m_hCreationParameters.bReadOnly = false;
//	m_hCreationParameters.bEnableTabStop = true;
//}
//Void RuneSearchRandomStatValueModel::Update()
//{
//	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;
//	pController->SetText( TEXT("") );
//
//	pController->SetCueText( TEXT("RandomStat Value ..."), false );
//}
//
//const WinGUILayout * RuneSearchRandomStatValueModel::GetLayout() const
//{
//	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
//	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;
//
//	WinGUIRectangle hClientArea;
//	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );
//
//	static WinGUIManualLayout hLayout;
//
//	hLayout.UseScalingPosition = false;
//	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,m_iIndex,0,0);
//	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,3,1);
//
//	hLayout.UseScalingSize = false;
//	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
//	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;
//
//	return &hLayout;
//}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchIndicatorModel implementation
RuneSearchIndicatorModel::RuneSearchIndicatorModel():
	WinGUIStaticModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_INDICATOR)
{
	m_pGUI = NULL;

	
}
RuneSearchIndicatorModel::~RuneSearchIndicatorModel()
{
	// nothing to do
}

Void RuneSearchIndicatorModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = true;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("No Active Filter !") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_CENTER;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * RuneSearchIndicatorModel::GetLayout() const
{
	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,3,2);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchClearModel implementation
RuneSearchClearModel::RuneSearchClearModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_CLEAR)
{
	m_pGUI = NULL;
}
RuneSearchClearModel::~RuneSearchClearModel()
{
	// nothing to do
}

Void RuneSearchClearModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Clear Filters") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * RuneSearchClearModel::GetLayout() const
{
	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,2,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,3,2);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool RuneSearchClearModel::OnClick()
{
	RuneTable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable();
	RuneTableModel * pTableModel = &( pRuneTable->m_hRuneTableModel );
	WinGUITable * pTableController = pRuneTable->m_pRuneTable;

	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();

	// Unselect all
	pRuneSearch->m_pSlot->SelectItem( INVALID_OFFSET );
	pRuneSearch->m_pSet->SelectItem( INVALID_OFFSET );
	pRuneSearch->m_pRank->SelectItem( INVALID_OFFSET );
	pRuneSearch->m_pQuality->SelectItem( INVALID_OFFSET );
	pRuneSearch->m_pLevel->SelectItem( INVALID_OFFSET );
	pRuneSearch->m_pMainStat->SelectItem( INVALID_OFFSET );
	pRuneSearch->_UpdateAvailableMainStats();

	// Reset Table
	pTableController->RemoveAllItems();
	pTableModel->UpdateAfterDataLoad();

	// Toggle Indicator
	WinGUIStatic * pIndicator = pRuneSearch->m_pIndicator;
	pIndicator->SetText( TEXT("No Active Filter !") );

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearchApplyModel implementation
RuneSearchApplyModel::RuneSearchApplyModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNESEARCH_APPLY)
{
	m_pGUI = NULL;
}
RuneSearchApplyModel::~RuneSearchApplyModel()
{
	// nothing to do
}

Void RuneSearchApplyModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Apply Filters") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * RuneSearchApplyModel::GetLayout() const
{
	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();
	WinGUIGroupBox * pGroupBox = pRuneSearch->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,3,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,3,2);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool RuneSearchApplyModel::OnClick()
{
	RuneTable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable();
	RuneTableModel * pTableModel = &( pRuneTable->m_hRuneTableModel );
	WinGUITable * pTableController = pRuneTable->m_pRuneTable;

	RuneSearch * pRuneSearch = m_pGUI->GetRuneExplorer()->GetRuneSearch();

	// Clear Table
	pTableController->RemoveAllItems();

	// Retrieve Rune Slot
	WinGUIComboBox * pRuneSlot = pRuneSearch->m_pSlot;
	UInt iSelected = pRuneSlot->GetSelectedItem();

	UInt iSlot = RUNE_SLOT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iSlot = (UInt)(UIntPtr)( pRuneSlot->GetItemData(iSelected) );

	// Retrieve Rune Set
	WinGUIComboBox * pRuneSet = pRuneSearch->m_pSet;
	iSelected = pRuneSet->GetSelectedItem();

	RuneSet iSet = RUNE_SET_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iSet = (RuneSet)(UIntPtr)( pRuneSet->GetItemData(iSelected) );

	// Retrieve Rune Rank
	WinGUIComboBox * pRuneRank = pRuneSearch->m_pRank;
	iSelected = pRuneRank->GetSelectedItem();

	RuneRank iRank = RUNE_RANK_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iRank = (RuneRank)(UIntPtr)( pRuneRank->GetItemData(iSelected) );

	// Retrieve Rune Quality
	WinGUIComboBox * pRuneQuality = pRuneSearch->m_pQuality;
	iSelected = pRuneQuality->GetSelectedItem();

	RuneQuality iQuality = RUNE_QUALITY_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iQuality = (RuneQuality)(UIntPtr)( pRuneQuality->GetItemData(iSelected) );

	// Retrieve Rune Level
	WinGUIComboBox * pRuneLevel = pRuneSearch->m_pLevel;
	iSelected = pRuneLevel->GetSelectedItem();

	UInt iLevel = INVALID_OFFSET;
	if ( iSelected != INVALID_OFFSET )
		iLevel = (UInt)(UIntPtr)( pRuneLevel->GetItemData(iSelected) );

	// Retrieve Rune MainStat
	WinGUIComboBox * pRuneMainStat = pRuneSearch->m_pMainStat;
	iSelected = pRuneMainStat->GetSelectedItem();

	RuneStat iMainStat = RUNE_STAT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iMainStat = (RuneStat)(UIntPtr)( pRuneMainStat->GetItemData(iSelected) );

	///////////////////////////////////

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
	//if ( iRank != RUNE_RANK_COUNT ) {
	//	hQuery.hQueryRank.iRankCount = 1;
	//	hQuery.hQueryRank.arrRanks[0] = iRank;
	//	hQueryMap.Insert( RUNE_QUERY_RANK, hQuery );
	//}
	//if ( iQuality != RUNE_QUALITY_COUNT ) {
	//	hQuery.hQueryQuality.iQualityCount = 1;
	//	hQuery.hQueryQuality.arrQualities[0] = iQuality;
	//	hQueryMap.Insert( RUNE_QUERY_QUALITY, hQuery );
	//}
	//if ( iLevel != INVALID_OFFSET ) {
	//	hQuery.hQueryLevel.iLevelCount = 1;
	//	hQuery.hQueryLevel.arrLevels[0] = iLevel;
	//	hQueryMap.Insert( RUNE_QUERY_LEVEL, hQuery );
	//}
	if ( iMainStat != RUNE_STAT_COUNT ) {
		hQuery.hQueryMainStat.iStatCount = 1;
		hQuery.hQueryMainStat.arrStats[0] = iMainStat;
		hQueryMap.Insert( RUNE_QUERY_MAINSTAT, hQuery );
	}

	// Perform the Query
	CCGOPFn->FilterRunes( &hQueryResults, hQueryMap, NULL, true, true );

	// Update the Table
	pTableModel->UpdateAfterFiltering( hQueryResults );

	// Clear temporary data
	hQueryResults.Destroy();
	hQueryMap.Destroy();

	// Toggle Indicator
	WinGUIStatic * pIndicator = pRuneSearch->m_pIndicator;
	pIndicator->SetText( TEXT("Filters are Active !") );

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneSearch implementation
RuneSearch::RuneSearch( CCGOPGUI * pGUI )
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
	//for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
	//	m_arrRandomStats[i].m_pRandomStat = NULL;
	//	m_arrRandomStats[i].m_pRandomStatValue = NULL;
	//}
	m_pIndicator = NULL;
	m_pClear = NULL;
	m_pApply = NULL;
}
RuneSearch::~RuneSearch()
{
	// nothing to do
}

Void RuneSearch::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_RUNE_EXPLORER );

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

	//for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
	//	m_arrRandomStats[i].m_hRandomStatModel.Initialize( m_pGUI, i );
	//	m_arrRandomStats[i].m_pRandomStat = WinGUIFn->CreateComboBox( m_pRoot, &(m_arrRandomStats[i].m_hRandomStatModel) );
	//	m_arrRandomStats[i].m_hRandomStatModel.Update( NULL, 0 );

	//	m_arrRandomStats[i].m_hRandomStatValueModel.Initialize( m_pGUI, i );
	//	m_arrRandomStats[i].m_pRandomStatValue = WinGUIFn->CreateTextEdit( m_pRoot, &(m_arrRandomStats[i].m_hRandomStatValueModel) );
	//	m_arrRandomStats[i].m_hRandomStatValueModel.Update();
	//}

	m_hIndicatorModel.Initialize( m_pGUI );
	m_pIndicator = WinGUIFn->CreateStatic( m_pRoot, &(m_hIndicatorModel) );

	m_hClearModel.Initialize( m_pGUI );
	m_pClear = WinGUIFn->CreateButton( m_pRoot, &(m_hClearModel) );

	m_hApplyModel.Initialize( m_pGUI );
	m_pApply = WinGUIFn->CreateButton( m_pRoot, &(m_hApplyModel) );
}
Void RuneSearch::Cleanup()
{
	// nothing to do (for now)
}

/////////////////////////////////////////////////////////////////////////////////

Void RuneSearch::_UpdateAvailableMainStats()
{
	// Retrieve Selected Slot
	UInt iSelected = m_pSlot->GetSelectedItem();

	UInt iSlot = RUNE_SLOT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iSlot = (UInt)(UIntPtr)( m_pSlot->GetItemData(iSelected) );

	// Update MainStatModel content
	m_hMainStatModel.Update( iSlot, NULL, 0 );
}

