/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer/HeroCreation.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : HeroExplorer GUI : Hero Creation
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
#include "HeroCreation.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// HeroCreationGroupModel implementation
HeroCreationGroupModel::HeroCreationGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_HEROEXPLORER_HEROCREATION_GROUP)
{
	m_pGUI = NULL;
}
HeroCreationGroupModel::~HeroCreationGroupModel()
{
	// nothing to do
}

Void HeroCreationGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Hero Creation :") );
}

const WinGUILayout * HeroCreationGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = (200 - CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH) / 2;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = 204;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroCreationNameModel implementation
HeroCreationNameModel::HeroCreationNameModel():
	WinGUIComboBoxModel(CCGOP_RESID_HEROEXPLORER_HEROCREATION_NAME),
	m_arrHeroNames()
{
	m_pGUI = NULL;
	m_arrHeroNames.Create();
}
HeroCreationNameModel::~HeroCreationNameModel()
{
	m_arrHeroNames.Destroy();
}

Void HeroCreationNameModel::Initialize( CCGOPGUI * pGUI )
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

	GameData::HeroDataMap::Iterator itHeroData = GameDataFn->EnumHeroData();
	while( !(itHeroData.IsNull()) ) {
		m_arrHeroNames.Push( itHeroData.GetKeyPtr()->strName );
		++itHeroData;
	}
}
Void HeroCreationNameModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < m_arrHeroNames.Count(); ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)(m_arrHeroNames[i]) );
	}

	pController->SetCueText( TEXT("Hero Name ...") );
}

const WinGUILayout * HeroCreationNameModel::GetLayout() const
{
	HeroCreation * pHeroCreation = m_pGUI->GetHeroExplorer()->GetHeroCreation();
	WinGUIGroupBox * pGroupBox = pHeroCreation->m_pGroup;

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

Bool HeroCreationNameModel::OnSelectionOK()
{
	// Retrieve Natural Rank
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iSelected = pController->GetSelectedItem();

	HeroRank iNaturalRank = GameDataFn->GetHeroNaturalRank( m_arrHeroNames[iSelected] );

	// Update RankModel content
	HeroCreationRankModel * pHeroRankModel = &( m_pGUI->GetHeroExplorer()->GetHeroCreation()->m_hRankModel );
	pHeroRankModel->Update( iNaturalRank );

	// Update LevelModel content
	HeroCreationLevelModel * pHeroLevelModel = &( m_pGUI->GetHeroExplorer()->GetHeroCreation()->m_hLevelModel );
	pHeroLevelModel->Update( 1, HERO_MAX_LEVEL );

	// Update SanctifyModel content
	HeroCreationSanctifyModel * pHeroSanctifyModel = &( m_pGUI->GetHeroExplorer()->GetHeroCreation()->m_hSanctifyModel );
	pHeroSanctifyModel->Update( false );

	return true;
}

Void HeroCreationNameModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < m_arrHeroNames.Count() );

	StringFn->NCopy( outBuffer, m_arrHeroNames[iItemIndex], iMaxLength - 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// HeroCreationRankModel implementation
HeroCreationRankModel::HeroCreationRankModel():
	WinGUIComboBoxModel(CCGOP_RESID_HEROEXPLORER_HEROCREATION_RANK)
{
	m_pGUI = NULL;

	m_iFirstAvailableRank = HERO_RANK_1S;
}
HeroCreationRankModel::~HeroCreationRankModel()
{
	// nothing to do
}

Void HeroCreationRankModel::Initialize( CCGOPGUI * pGUI )
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
Void HeroCreationRankModel::Update( HeroRank iFirstAvailableRank )
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	m_iFirstAvailableRank = iFirstAvailableRank;

	for( UInt i = m_iFirstAvailableRank; i < HERO_RANK_COUNT; ++i ) {
		pController->AddItem( i - m_iFirstAvailableRank );
		pController->SetItemData( i - m_iFirstAvailableRank, (Void*)i );
	}

	pController->SetCueText( TEXT("Hero Rank ...") );
}

const WinGUILayout * HeroCreationRankModel::GetLayout() const
{
	HeroCreation * pHeroCreation = m_pGUI->GetHeroExplorer()->GetHeroCreation();
	WinGUIGroupBox * pGroupBox = pHeroCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool HeroCreationRankModel::OnSelectionOK()
{
	// Retrieve Selected Name
	HeroCreationNameModel * pHeroNameModel = &( m_pGUI->GetHeroExplorer()->GetHeroCreation()->m_hNameModel );
	WinGUIComboBox * pHeroNameController = (WinGUIComboBox*)( pHeroNameModel->GetController() );

	UInt iSelectedHeroName = pHeroNameController->GetSelectedItem();
	if ( iSelectedHeroName == INVALID_OFFSET ) {
		// Retrieve Selected Rank
		WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
		UInt iSelectedHeroRank = pController->GetSelectedItem();

		HeroRank iRank = (HeroRank)(UIntPtr)( pController->GetItemData(iSelectedHeroRank) );

		// Cannot compute Min Level, assume 1 unless we're at 6*
		UInt iMinLevel = 1;
		if ( iRank == HERO_RANK_6S )
			iMinLevel = GameDataFn->GetHeroRankMaxLevel( HERO_RANK_5S );
		UInt iMaxLevel = GameDataFn->GetHeroRankMaxLevel( iRank );

		// Update LevelModel content
		HeroCreationLevelModel * pHeroLevelModel = &( m_pGUI->GetHeroExplorer()->GetHeroCreation()->m_hLevelModel );
		pHeroLevelModel->Update( iMinLevel, iMaxLevel );

		// Update SanctifyModel content
		HeroCreationSanctifyModel * pHeroSanctifyModel = &( m_pGUI->GetHeroExplorer()->GetHeroCreation()->m_hSanctifyModel );
		pHeroSanctifyModel->Update( false );

		return false;
	}

	const GChar * strSelectedHeroName = (const GChar *)( pHeroNameController->GetItemData(iSelectedHeroName) );

	// Retrieve Selected Rank
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iSelectedHeroRank = pController->GetSelectedItem();

	HeroRank iRank = (HeroRank)(UIntPtr)( pController->GetItemData(iSelectedHeroRank) );

	// Compute Allowed Level Range
	UInt iMinLevel = GameDataFn->GetHeroRankMinLevel( strSelectedHeroName, iRank );
	UInt iMaxLevel = GameDataFn->GetHeroRankMaxLevel( iRank );

	// Update LevelModel content
	HeroCreationLevelModel * pHeroLevelModel = &( m_pGUI->GetHeroExplorer()->GetHeroCreation()->m_hLevelModel );
	pHeroLevelModel->Update( iMinLevel, iMaxLevel );

	// Update SanctifyModel content
	HeroCreationSanctifyModel * pHeroSanctifyModel = &( m_pGUI->GetHeroExplorer()->GetHeroCreation()->m_hSanctifyModel );
	pHeroSanctifyModel->Update( false );

	return true;
}

Void HeroCreationRankModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < HERO_RANK_COUNT );

	StringFn->NCopy( outBuffer, GameDataFn->GetHeroRankName((HeroRank)(m_iFirstAvailableRank + iItemIndex)), iMaxLength - 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// HeroCreationLevelModel implementation
HeroCreationLevelModel::HeroCreationLevelModel():
	WinGUIComboBoxModel(CCGOP_RESID_HEROEXPLORER_HEROCREATION_LEVEL)
{
	m_pGUI = NULL;

	m_iMinLevel = 1;
	m_iMaxLevel = HERO_MAX_LEVEL;
}
HeroCreationLevelModel::~HeroCreationLevelModel()
{
	// nothing to do
}

Void HeroCreationLevelModel::Initialize( CCGOPGUI * pGUI )
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
Void HeroCreationLevelModel::Update( UInt iMinLevel, UInt iMaxLevel )
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	m_iMinLevel = iMinLevel;
	m_iMaxLevel = iMaxLevel;

	for( UInt i = m_iMinLevel; i <= m_iMaxLevel; ++i ) {
		pController->AddItem( i - m_iMinLevel );
		pController->SetItemData( i - m_iMinLevel, (Void*)i );
	}

	pController->SetCueText( TEXT("Hero Level ...") );
}

const WinGUILayout * HeroCreationLevelModel::GetLayout() const
{
	HeroCreation * pHeroCreation = m_pGUI->GetHeroExplorer()->GetHeroCreation();
	WinGUIGroupBox * pGroupBox = pHeroCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + 2 * (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Bool HeroCreationLevelModel::OnSelectionOK()
{
	// Retrieve selected Level
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	UInt iSelectedLevel = pController->GetSelectedItem();

	UInt iLevel = (UInt)(UIntPtr)( pController->GetItemData(iSelectedLevel) );

	// Update SanctifyModel content
	HeroCreationSanctifyModel * pHeroSanctifyModel = &( m_pGUI->GetHeroExplorer()->GetHeroCreation()->m_hSanctifyModel );
	pHeroSanctifyModel->Update( iLevel == HERO_MAX_LEVEL );

	return true;
}

Void HeroCreationLevelModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( m_iMinLevel + iItemIndex <= HERO_MAX_LEVEL );

	GChar strBuffer[32];
	StringFn->FromUInt( strBuffer, (m_iMinLevel + iItemIndex) );
	StringFn->NCopy( outBuffer, strBuffer, iMaxLength - 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// HeroCreationEvolvedModel implementation
HeroCreationEvolvedModel::HeroCreationEvolvedModel():
	WinGUICheckBoxModel(CCGOP_RESID_HEROEXPLORER_HEROCREATION_EVOLVED)
{
	m_pGUI = NULL;
}
HeroCreationEvolvedModel::~HeroCreationEvolvedModel()
{
	// nothing to do
}

Void HeroCreationEvolvedModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->NCopy( m_hCreationParameters.strLabel, TEXT("Evolved"), 63 );

	m_hCreationParameters.bEnableNotify = false;
	m_hCreationParameters.bEnableTabStop = true;
}

const WinGUILayout * HeroCreationEvolvedModel::GetLayout() const
{
	HeroCreation * pHeroCreation = m_pGUI->GetHeroExplorer()->GetHeroCreation();
	WinGUIGroupBox * pGroupBox = pHeroCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + 3 * (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_CHECKBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_CHECKBOX_HEIGHT;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroCreationSanctifyModel implementation
HeroCreationSanctifyModel::HeroCreationSanctifyModel():
	WinGUIComboBoxModel(CCGOP_RESID_HEROEXPLORER_HEROCREATION_SANCTIFY)
{
	m_pGUI = NULL;

	m_bSanctifyAllowed = false;
}
HeroCreationSanctifyModel::~HeroCreationSanctifyModel()
{
	// nothing to do
}

Void HeroCreationSanctifyModel::Initialize( CCGOPGUI * pGUI )
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
Void HeroCreationSanctifyModel::Update( Bool bSanctifyAllowed )
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	m_bSanctifyAllowed = bSanctifyAllowed;

	if ( m_bSanctifyAllowed ) {
		for( UInt i = 0; i < HERO_SANCTIFY_COUNT; ++i ) {
			pController->AddItem( i );
			pController->SetItemData( i, (Void*)i );
		}
	} else {
		pController->AddItem( 0 );
		pController->SetItemData( 0, (Void*)HERO_SANCTIFY_NONE );
	}

	pController->SetCueText( TEXT("Hero Sanctify ...") );
}

const WinGUILayout * HeroCreationSanctifyModel::GetLayout() const
{
	HeroCreation * pHeroCreation = m_pGUI->GetHeroExplorer()->GetHeroCreation();
	WinGUIGroupBox * pGroupBox = pHeroCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + 3 * (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT) + (CCGOP_LAYOUT_CHECKBOX_HEIGHT + CCGOP_LAYOUT_SPACING_VERT);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Void HeroCreationSanctifyModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < HERO_SANCTIFY_COUNT );

	StringFn->NCopy( outBuffer, GameDataFn->GetHeroSanctifyName((HeroSanctify)iItemIndex), iMaxLength - 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// HeroCreationButtonModel implementation
HeroCreationButtonModel::HeroCreationButtonModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROCREATION_BUTTON)
{
	m_pGUI = NULL;
}
HeroCreationButtonModel::~HeroCreationButtonModel()
{
	// nothing to do
}

Void HeroCreationButtonModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Create") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroCreationButtonModel::GetLayout() const
{
	HeroCreation * pHeroCreation = m_pGUI->GetHeroExplorer()->GetHeroCreation();
	WinGUIGroupBox * pGroupBox = pHeroCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + 4 * (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT) + (CCGOP_LAYOUT_CHECKBOX_HEIGHT + CCGOP_LAYOUT_SPACING_VERT) + CCGOP_LAYOUT_SPACING_GAP_VERT;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroCreationButtonModel::OnClick()
{
	HeroCreation * pHeroCreation = m_pGUI->GetHeroExplorer()->GetHeroCreation();

	// Error Message
	WinGUIMessageBoxOptions hOptions;
	hOptions.iType = WINGUI_MESSAGEBOX_OK;
	hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_ERROR;
	hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_OK;
	hOptions.bMustAnswer = true;

	// Retrieve Hero Name
	WinGUIComboBox * pHeroName = pHeroCreation->m_pName;
	UInt iSelected = pHeroName->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Hero Name !"), hOptions );
		return true;
	}

	const GChar * strName = (const GChar *)( pHeroName->GetItemData(iSelected) );

	// Retrieve Hero Rank
	WinGUIComboBox * pHeroRank = pHeroCreation->m_pRank;
	iSelected = pHeroRank->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Hero Rank !"), hOptions );
		return true;
	}

	HeroRank iRank = (HeroRank)(UIntPtr)( pHeroRank->GetItemData(iSelected) );

	// Retrieve Hero Level
	WinGUIComboBox * pHeroLevel = pHeroCreation->m_pLevel;
	iSelected = pHeroLevel->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Hero Level !"), hOptions );
		return true;
	}

	UInt iLevel = (UInt)(UIntPtr)( pHeroLevel->GetItemData(iSelected) );

	// Retrieve Hero Evolved
	WinGUICheckBox * pHeroEvolved = pHeroCreation->m_pEvolved;
	Bool bEvolved = pHeroEvolved->IsChecked();

	// Retrieve Hero Sanctify
	WinGUIComboBox * pHeroSanctify = pHeroCreation->m_pSanctify;
	iSelected = pHeroSanctify->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET ) {
		WinGUIFn->SpawnMessageBox( TEXT("Error !"), TEXT("Please select a Hero Sanctification !"), hOptions );
		return true;
	}

	HeroSanctify iSanctify = (HeroSanctify)(UIntPtr)( pHeroSanctify->GetItemData(iSelected) );

	// Confirmation Message
	hOptions.iType = WINGUI_MESSAGEBOX_OKCANCEL;
	hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_INFO;
	hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_OK;
	hOptions.bMustAnswer = true;

	GChar strBuffer[256];
	StringFn->Format( strBuffer, TEXT("You are about to create a level %d %s %s %s with %s sanctification ... \n\n Do you want to continue ?"),
					  iLevel,
					  GameDataFn->GetHeroRankName(iRank),
					  bEvolved ? TEXT("Evolved") : TEXT("Unevolved"),
					  strName,
					  GameDataFn->GetHeroSanctifyName(iSanctify) );

	WinGUIMessageBoxResponse iResponse = WinGUIFn->SpawnMessageBox( TEXT("Confirmation"), strBuffer, hOptions );

	// Abort
	if ( iResponse != WINGUI_MESSAGEBOX_RESPONSE_OK )
		return true;

	// Create the Hero
	HeroID iHeroID = CCGOPFn->CreateHero( strName, iRank, iLevel, bEvolved, iSanctify );

	// Update HeroTable
	HeroTable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable();
	pHeroTable->m_hHeroTableModel.UpdateAfterHeroCreation( iHeroID );

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroCreation implementation
HeroCreation::HeroCreation( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pName = NULL;
	m_pRank = NULL;
	m_pLevel = NULL;
	m_pEvolved = NULL;
	m_pSanctify = NULL;
	m_pButton = NULL;
}
HeroCreation::~HeroCreation()
{
	// nothing to do
}

Void HeroCreation::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_HERO_EXPLORER );

	// Build Hero Creation UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &(m_hGroupModel) );

	m_hNameModel.Initialize( m_pGUI );
	m_pName = WinGUIFn->CreateComboBox( m_pRoot, &(m_hNameModel) );
	m_hNameModel.Update();

	m_hRankModel.Initialize( m_pGUI );
	m_pRank = WinGUIFn->CreateComboBox( m_pRoot, &(m_hRankModel) );
	m_hRankModel.Update( HERO_RANK_1S );

	m_hLevelModel.Initialize( m_pGUI );
	m_pLevel = WinGUIFn->CreateComboBox( m_pRoot, &(m_hLevelModel) );
	m_hLevelModel.Update( 1, HERO_MAX_LEVEL );

	m_hEvolvedModel.Initialize( m_pGUI );
	m_pEvolved = WinGUIFn->CreateCheckBox( m_pRoot, &(m_hEvolvedModel) );
	m_pEvolved->Check();

	m_hSanctifyModel.Initialize( m_pGUI );
	m_pSanctify = WinGUIFn->CreateComboBox( m_pRoot, &(m_hSanctifyModel) );
	m_hSanctifyModel.Update( false );

	m_hButtonModel.Initialize( m_pGUI );
	m_pButton = WinGUIFn->CreateButton( m_pRoot, &(m_hButtonModel) );
}
Void HeroCreation::Cleanup()
{
	// nothing to do (for now)
}

