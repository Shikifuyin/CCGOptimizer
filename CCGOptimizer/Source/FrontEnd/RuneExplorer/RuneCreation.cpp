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

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = (200 - CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH) / 2;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = 212;

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

Bool RuneCreationSlotModel::OnSelectionOK()
{
	// Retrieve Selected Slot
	WinGUIComboBox * pSlot = (WinGUIComboBox*)m_pController;
	UInt iSelectedItem = pSlot->GetSelectedItem();

	UInt iSelectedSlot = (UInt)(UIntPtr)( pSlot->GetItemData(iSelectedItem) );

	// Update MainStatModel content
	RuneCreationMainStatModel * pRuneMainStatModel = &( m_pGUI->GetRuneExplorer()->GetRuneCreation()->m_hMainStatModel );
	pRuneMainStatModel->Update( iSelectedSlot );

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
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,1,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
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
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,2,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
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
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,3,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneCreationQualityModel::OnSelectionOK()
{
	// nothing to do
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
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,4,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneCreationLevelModel::OnSelectionOK()
{
	// nothing to do
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

	m_iSelectedSlot = 0;
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
Void RuneCreationMainStatModel::Update( UInt iSelectedSlot )
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	m_iSelectedSlot = iSelectedSlot;

	UInt iIndex = 0;
	for( UInt i = 0; i < RUNE_STAT_COUNT; ++i ) {
		if ( GameDataFn->IsRuneMainStatAllowed( (RuneStat)i, m_iSelectedSlot ) ) {
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
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,5,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneCreationMainStatModel::OnSelectionOK()
{
	// nothing to do
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
Void RuneCreationInnateStatModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	UInt iIndex = 0;
	for( UInt i = 0; i < RUNE_STAT_COUNT; ++i ) {
		// Check if the stat is selected elsewhere

		pController->AddItem( iIndex );
		pController->SetItemData( iIndex, (Void*)i );
		++iIndex;
	}

	pController->SetCueText( TEXT("Rune InnateStat ...") );
}

const WinGUILayout * RuneCreationInnateStatModel::GetLayout() const
{
	RuneCreation * pRuneCreation = m_pGUI->GetRuneExplorer()->GetRuneCreation();
	WinGUIGroupBox * pGroupBox = pRuneCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,6,0);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool RuneCreationInnateStatModel::OnSelectionOK()
{
	// nothing to do
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
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,0,8,1);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool RuneCreationButtonModel::OnClick()
{
	//////////////////////////////////////

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
	m_hMainStatModel.Update( 0 );

	m_hInnateStatModel.Initialize( m_pGUI );
	m_pInnateStat = WinGUIFn->CreateComboBox( m_pRoot, &(m_hInnateStatModel) );
	m_hInnateStatModel.Update();


	m_hButtonModel.Initialize( m_pGUI );
	m_pButton = WinGUIFn->CreateButton( m_pRoot, &(m_hButtonModel) );
}
Void RuneCreation::Cleanup()
{
	// nothing to do (for now)
}

