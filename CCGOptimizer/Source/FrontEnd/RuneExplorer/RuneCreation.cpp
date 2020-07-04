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
// RuneCreationGroupModel implementation
RuneCreationGroupModel::RuneCreationGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_GROUP)
{
	m_pGUI = NULL;
}
RuneCreationGroupModel::~RuneCreationGroupModel()
{
	// nothing to do
}

Void RuneCreationGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Rune Creation :") );
}

const WinGUILayout * RuneCreationGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(0,0,4,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(1,1,3,2) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ROOM_LEFT;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ROOM_TOP + CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iY, CCGOP_LAYOUT_ROOM_HEIGHT );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationSlotModel implementation
RuneCreationSlotModel::RuneCreationSlotModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_SLOT)
{
	m_pGUI = NULL;
}
RuneCreationSlotModel::~RuneCreationSlotModel()
{
	// nothing to do
}

Void RuneCreationSlotModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneCreationSlotModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Slot ...") );
}

const WinGUILayout * RuneCreationSlotModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

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

Void RuneCreationSlotModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure available MainStats are consistent
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->_UpdateAvailableMainStats();
	}
}

Bool RuneCreationSlotModel::OnSelectionOK()
{
	// Ensure available MainStats are consistent
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->_UpdateAvailableMainStats();

	// Done
	return true;
}

Void RuneCreationSlotModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_SLOT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iSlot = (UInt)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->FromUInt( outBuffer, iSlot + 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationSetModel implementation
RuneCreationSetModel::RuneCreationSetModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_SET)
{
	m_pGUI = NULL;
}
RuneCreationSetModel::~RuneCreationSetModel()
{
	// nothing to do
}

Void RuneCreationSetModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneCreationSetModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_SET_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Set ...") );
}

const WinGUILayout * RuneCreationSetModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

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

Void RuneCreationSetModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SelectItem( INVALID_OFFSET );
}

Bool RuneCreationSetModel::OnSelectionOK()
{
	// nothing to do
	return true;
}

Void RuneCreationSetModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_SET_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneSet iSet = (RuneSet)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneSetName(iSet), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationRankModel implementation
RuneCreationRankModel::RuneCreationRankModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_RANK)
{
	m_pGUI = NULL;
}
RuneCreationRankModel::~RuneCreationRankModel()
{
	// nothing to do
}

Void RuneCreationRankModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneCreationRankModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_RANK_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Rank ...") );
}

const WinGUILayout * RuneCreationRankModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

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

Void RuneCreationRankModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SelectItem( INVALID_OFFSET );
}

Bool RuneCreationRankModel::OnSelectionOK()
{
	// nothing to do
	return true;
}

Void RuneCreationRankModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_RANK_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneRank iRank = (RuneRank)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneRankName(iRank), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationQualityModel implementation
RuneCreationQualityModel::RuneCreationQualityModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_QUALITY)
{
	m_pGUI = NULL;
}
RuneCreationQualityModel::~RuneCreationQualityModel()
{
	// nothing to do
}

Void RuneCreationQualityModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneCreationQualityModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < RUNE_QUALITY_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Quality ...") );
}

const WinGUILayout * RuneCreationQualityModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

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

Void RuneCreationQualityModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure available RandomStat Count is consistent
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->_UpdateRandomStatsCount();
	}
}

Bool RuneCreationQualityModel::OnSelectionOK()
{
	// Ensure available RandomStat Count is consistent
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->_UpdateRandomStatsCount();

	// Done
	return true;
}

Void RuneCreationQualityModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_QUALITY_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneQuality iQuality = (RuneQuality)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneQualityName(iQuality), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationLevelModel implementation
RuneCreationLevelModel::RuneCreationLevelModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_LEVEL)
{
	m_pGUI = NULL;
}
RuneCreationLevelModel::~RuneCreationLevelModel()
{
	// nothing to do
}

Void RuneCreationLevelModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneCreationLevelModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i <= RUNE_MAX_LEVEL; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Rune Level ...") );
}

const WinGUILayout * RuneCreationLevelModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

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

Void RuneCreationLevelModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure available RandomStat Count is consistent
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->_UpdateRandomStatsCount();
	}
}

Bool RuneCreationLevelModel::OnSelectionOK()
{
	// Ensure available RandomStat Count is consistent
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->_UpdateRandomStatsCount();

	// Done
	return true;
}

Void RuneCreationLevelModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex <= RUNE_MAX_LEVEL );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iLevel = (RuneQuality)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->Format( outBuffer, TEXT("+%d"), iLevel );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationMainStatModel implementation
RuneCreationMainStatModel::RuneCreationMainStatModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_MAINSTAT)
{
	m_pGUI = NULL;

	m_iSelectedSlot = INVALID_OFFSET;
	m_iExcludedStatsCount = 0;
}
RuneCreationMainStatModel::~RuneCreationMainStatModel()
{
	// nothing to do
}

Void RuneCreationMainStatModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneCreationMainStatModel::Update( UInt iSelectedSlot, RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
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

const WinGUILayout * RuneCreationMainStatModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

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

Void RuneCreationMainStatModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure RuneStat selection doesn't collide
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->_ExcludeRuneStats( pController );
	}
}

Bool RuneCreationMainStatModel::OnSelectionOK()
{
	// Ensure RuneStat selection doesn't collide
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->_ExcludeRuneStats( (WinGUIComboBox*)m_pController );

	// Done
	return true;
}

Void RuneCreationMainStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_STAT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationInnateStatModel implementation
RuneCreationInnateStatModel::RuneCreationInnateStatModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_INNATESTAT)
{
	m_pGUI = NULL;

	m_iExcludedStatsCount = 0;
}
RuneCreationInnateStatModel::~RuneCreationInnateStatModel()
{
	// nothing to do
}

Void RuneCreationInnateStatModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneCreationInnateStatModel::Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
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

const WinGUILayout * RuneCreationInnateStatModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,3,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Void RuneCreationInnateStatModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure RuneStat selection doesn't collide
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->_ExcludeRuneStats( pController );
	}
}

Bool RuneCreationInnateStatModel::OnSelectionOK()
{
	// Ensure RuneStat selection doesn't collide
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->_ExcludeRuneStats( (WinGUIComboBox*)m_pController );

	// Done
	return true;
}

Void RuneCreationInnateStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_STAT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationInnateStatValueModel implementation
RuneCreationInnateStatValueModel::RuneCreationInnateStatValueModel():
	WinGUITextEditModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_INNATESTATVALUE)
{
	m_pGUI = NULL;
}
RuneCreationInnateStatValueModel::~RuneCreationInnateStatValueModel()
{
	// nothing to do
}

Void RuneCreationInnateStatValueModel::Initialize( CCGOPGUI * pGUI )
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
Void RuneCreationInnateStatValueModel::Update()
{
	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;
	pController->SetText( TEXT("") );

	pController->SetCueText( TEXT("InnateStat Value ..."), false );
}

const WinGUILayout * RuneCreationInnateStatValueModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,3,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	return &hLayout;
}

Void RuneCreationInnateStatValueModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUITextEdit * pController = ((WinGUITextEdit*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SetText( TEXT("") );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationRandomStatModel implementation
RuneCreationRandomStatModel::RuneCreationRandomStatModel():
	WinGUIComboBoxModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_RANDOMSTAT)
{
	m_pGUI = NULL;
	m_iIndex = INVALID_OFFSET;

	m_iExcludedStatsCount = 0;
}
RuneCreationRandomStatModel::~RuneCreationRandomStatModel()
{
	// nothing to do
}

Void RuneCreationRandomStatModel::Initialize( CCGOPGUI * pGUI, UInt iIndex )
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
Void RuneCreationRandomStatModel::Update( RuneStat * arrExcludedStats, UInt iExcludedStatsCount )
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

const WinGUILayout * RuneCreationRandomStatModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,m_iIndex,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,2,1);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Void RuneCreationRandomStatModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Ensure RuneStat selection doesn't collide
		m_pGUI->GetRuneExplorer()->GetRuneCreation()->_ExcludeRuneStats( pController );
	}
}

Bool RuneCreationRandomStatModel::OnSelectionOK()
{
	// Ensure RuneStat selection doesn't collide
	m_pGUI->GetRuneExplorer()->GetRuneCreation()->_ExcludeRuneStats( (WinGUIComboBox*)m_pController );
	
	// Done
	return true;
}

Void RuneCreationRandomStatModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < RUNE_STAT_COUNT );

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	RuneStat iStat = (RuneStat)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetRuneStatName(iStat), iMaxLength );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationRandomStatValueModel implementation
RuneCreationRandomStatValueModel::RuneCreationRandomStatValueModel():
	WinGUITextEditModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_RANDOMSTATVALUE)
{
	m_pGUI = NULL;
	m_iIndex = INVALID_OFFSET;
}
RuneCreationRandomStatValueModel::~RuneCreationRandomStatValueModel()
{
	// nothing to do
}

Void RuneCreationRandomStatValueModel::Initialize( CCGOPGUI * pGUI, UInt iIndex )
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
Void RuneCreationRandomStatValueModel::Update()
{
	WinGUITextEdit * pController = (WinGUITextEdit*)m_pController;
	pController->SetText( TEXT("") );

	pController->SetCueText( TEXT("RandomStat Value ..."), false );
}

const WinGUILayout * RuneCreationRandomStatValueModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,m_iIndex,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,3,1);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_TEXTEDIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_TEXTEDIT_HEIGHT;

	return &hLayout;
}

Void RuneCreationRandomStatValueModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUITextEdit * pController = ((WinGUITextEdit*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SetText( TEXT("") );
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreationButtonModel implementation
RuneCreationButtonModel::RuneCreationButtonModel():
	WinGUIButtonModel(CCGOP_RESID_RUNEEXPLORER_RUNECREATION_CREATE)
{
	m_pGUI = NULL;
}
RuneCreationButtonModel::~RuneCreationButtonModel()
{
	// nothing to do
}

Void RuneCreationButtonModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Create") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * RuneCreationButtonModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

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

Bool RuneCreationButtonModel::OnClick()
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();

	// Error Message
	WinGUIMessageBoxOptions hOptions;
	hOptions.iType = WINGUI_MESSAGEBOX_OK;
	hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_ERROR;
	hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_OK;
	hOptions.bMustAnswer = true;

	// Retrieve Rune Slot
	WinGUIComboBox * pRuneSlot = pRuneCreation->m_pSlot;
	UInt iSelected = pRuneSlot->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Slot !"), hOptions );
		return true;
	}

	UInt iSlot = (UInt)(UIntPtr)( pRuneSlot->GetItemData(iSelected) );

	// Retrieve Rune Set
	WinGUIComboBox * pRuneSet = pRuneCreation->m_pSet;
	iSelected = pRuneSet->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Set !"), hOptions );
		return true;
	}

	RuneSet iSet = (RuneSet)(UIntPtr)( pRuneSet->GetItemData(iSelected) );

	// Retrieve Rune Rank
	WinGUIComboBox * pRuneRank = pRuneCreation->m_pRank;
	iSelected = pRuneRank->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Rank !"), hOptions );
		return true;
	}

	RuneRank iRank = (RuneRank)(UIntPtr)( pRuneRank->GetItemData(iSelected) );

	// Retrieve Rune Quality
	WinGUIComboBox * pRuneQuality = pRuneCreation->m_pQuality;
	iSelected = pRuneQuality->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Quality !"), hOptions );
		return true;
	}

	RuneQuality iQuality = (RuneQuality)(UIntPtr)( pRuneQuality->GetItemData(iSelected) );

	// Retrieve Rune Level
	WinGUIComboBox * pRuneLevel = pRuneCreation->m_pLevel;
	iSelected = pRuneLevel->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Rune Level !"), hOptions );
		return true;
	}

	UInt iLevel = (UInt)(UIntPtr)( pRuneLevel->GetItemData(iSelected) );

	// Retrieve Rune MainStat
	WinGUIComboBox * pRuneMainStat = pRuneCreation->m_pMainStat;
	iSelected = pRuneMainStat->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Main Stat !"), hOptions );
		return true;
	}

	RuneStat iMainStat = (RuneStat)(UIntPtr)( pRuneMainStat->GetItemData(iSelected) );

	// Retrieve Rune InnateStat
	WinGUIComboBox * pRuneInnateStat = pRuneCreation->m_pInnateStat;
	iSelected = pRuneInnateStat->GetSelectedItem();
	
	RuneStat iInnateStat = RUNE_STAT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iInnateStat = (RuneStat)(UIntPtr)( pRuneInnateStat->GetItemData(iSelected) );

	// Retrieve Rune InnateStat Value
	WinGUITextEdit * pRuneInnateStatValue = pRuneCreation->m_pInnateStatValue;

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
		WinGUIComboBox * pRuneRandomStat = pRuneCreation->m_arrRandomStats[i].m_pRandomStat;
		iSelected = pRuneRandomStat->GetSelectedItem();
		
		arrRandomStats[iRandomStatsCount] = RUNE_STAT_COUNT;
		if ( iSelected != INVALID_OFFSET )
			arrRandomStats[iRandomStatsCount] = (RuneStat)(UIntPtr)( pRuneRandomStat->GetItemData(iSelected) );

		// Retrieve Rune RandomStat Value
		WinGUITextEdit * pRuneRandomStatValue = pRuneCreation->m_arrRandomStats[i].m_pRandomStatValue;

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
	RuneTable * pRuneTable = m_pGUI->GetRuneExplorer()->GetRuneTable();
	pRuneTable->m_hRuneTableModel.UpdateAfterRuneCreation( iRuneID );

	// Set Unsaved Changes Mark
	m_pGUI->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// RuneCreation implementation
RuneCreation::RuneCreation( CCGOPGUI * pGUI )
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
		m_arrRandomStats[i].m_pRandomStat = NULL;
		m_arrRandomStats[i].m_pRandomStatValue = NULL;
	}
	m_pButton = NULL;
}
RuneCreation::~RuneCreation()
{
	// nothing to do
}

Void RuneCreation::Initialize()
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

	m_hInnateStatModel.Initialize( m_pGUI );
	m_pInnateStat = WinGUIFn->CreateComboBox( m_pRoot, &(m_hInnateStatModel) );
	m_hInnateStatModel.Update( NULL, 0 );

	m_hInnateStatValueModel.Initialize( m_pGUI );
	m_pInnateStatValue = WinGUIFn->CreateTextEdit( m_pRoot, &(m_hInnateStatValueModel) );
	m_hInnateStatValueModel.Update();

	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		m_arrRandomStats[i].m_hRandomStatModel.Initialize( m_pGUI, i );
		m_arrRandomStats[i].m_pRandomStat = WinGUIFn->CreateComboBox( m_pRoot, &(m_arrRandomStats[i].m_hRandomStatModel) );
		m_arrRandomStats[i].m_hRandomStatModel.Update( NULL, 0 );

		m_arrRandomStats[i].m_hRandomStatValueModel.Initialize( m_pGUI, i );
		m_arrRandomStats[i].m_pRandomStatValue = WinGUIFn->CreateTextEdit( m_pRoot, &(m_arrRandomStats[i].m_hRandomStatValueModel) );
		m_arrRandomStats[i].m_hRandomStatValueModel.Update();
	}

	m_hButtonModel.Initialize( m_pGUI );
	m_pButton = WinGUIFn->CreateButton( m_pRoot, &(m_hButtonModel) );
}
Void RuneCreation::Cleanup()
{
	// nothing to do (for now)
}

/////////////////////////////////////////////////////////////////////////////////

Void RuneCreation::_UpdateAvailableMainStats()
{
	// Retrieve Selected Slot
	UInt iSelected = m_pSlot->GetSelectedItem();

	UInt iSlot = RUNE_SLOT_COUNT;
	if ( iSelected != INVALID_OFFSET )
		iSlot = (UInt)(UIntPtr)( m_pSlot->GetItemData(iSelected) );

	// Update MainStatModel content
	m_hMainStatModel.Update( iSlot, NULL, 0 );
}
Void RuneCreation::_UpdateRandomStatsCount()
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
		WinGUIComboBox * pStat = m_arrRandomStats[i].m_pRandomStat;
		WinGUITextEdit * pStatValue = m_arrRandomStats[i].m_pRandomStatValue;

		if ( i < iAllowedRandomStats ) {
			pStat->Enable();
			pStatValue->Enable();
		} else {
			pStat->SelectItem( INVALID_OFFSET );
			_ExcludeRuneStats( pStat );

			pStat->Disable();
			pStatValue->Disable();
		}
	}
}
Void RuneCreation::_ExcludeRuneStats( WinGUIComboBox * pJustSelected )
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
		iSelected = m_arrRandomStats[i].m_pRandomStat->GetSelectedItem();

		arrRandomStats[i] = RUNE_STAT_COUNT;
		if ( iSelected != INVALID_OFFSET )
			arrRandomStats[i] = (RuneStat)(UIntPtr)( m_arrRandomStats[i].m_pRandomStat->GetItemData(iSelected) );
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
		WinGUIComboBox * pStat = m_arrRandomStats[i].m_pRandomStat;

		if ( pStat == pJustSelected )
			continue;

		iSelectedStatsCount = 2;
		for( UInt j = 0; j < RUNE_RANDOM_STAT_COUNT; ++j ) {
			if ( j != i ) {
				arrSelectedStats[iSelectedStatsCount] = arrRandomStats[j];
				++iSelectedStatsCount;
			}
		}

		m_arrRandomStats[i].m_hRandomStatModel.Update( arrSelectedStats, iSelectedStatsCount );

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

