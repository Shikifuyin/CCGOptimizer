/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/HeroExplorer/HeroOptions.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : HeroExplorer GUI : Hero Options
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
#include "HeroOptions.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// HeroOptionsGroupModel implementation
HeroOptionsGroupModel::HeroOptionsGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_GROUP)
{
	m_pGUI = NULL;
}
HeroOptionsGroupModel::~HeroOptionsGroupModel()
{
	// nothing to do
}

Void HeroOptionsGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Hero Options :") );
}

const WinGUILayout * HeroOptionsGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = 1400 + (200 - CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH) / 2;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = 220;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroOptionsMaxRankModel implementation
HeroOptionsMaxRankModel::HeroOptionsMaxRankModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_MAXRANK)
{
	m_pGUI = NULL;
}
HeroOptionsMaxRankModel::~HeroOptionsMaxRankModel()
{
	// nothing to do
}

Void HeroOptionsMaxRankModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Max Rank") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroOptionsMaxRankModel::GetLayout() const
{
	HeroOptions * pHeroOptions = m_pGUI->GetHeroExplorer()->GetHeroOptions();
	WinGUIGroupBox * pGroupBox = pHeroOptions->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroOptionsMaxRankModel::OnClick()
{
	// Retrieve Hero Table
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	// Find all checked elements
	UInt iItemCount = pHeroTable->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemChecked(i) ) {
			// Max Hero Rank
			HeroID iHeroID = (HeroID)(UIntPtr)( pHeroTable->GetItemData(i) );
			Hero * pHero = CCGOPFn->GetHero( iHeroID );
			pHero->SetRank( HERO_RANK_6S );

			// Update HeroTable
			pHeroTable->UpdateItem( i );
		}
	}
	
	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroOptionsMaxLevelModel implementation
HeroOptionsMaxLevelModel::HeroOptionsMaxLevelModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_MAXLEVEL)
{
	m_pGUI = NULL;
}
HeroOptionsMaxLevelModel::~HeroOptionsMaxLevelModel()
{
	// nothing to do
}

Void HeroOptionsMaxLevelModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Max Level") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroOptionsMaxLevelModel::GetLayout() const
{
	HeroOptions * pHeroOptions = m_pGUI->GetHeroExplorer()->GetHeroOptions();
	WinGUIGroupBox * pGroupBox = pHeroOptions->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroOptionsMaxLevelModel::OnClick()
{
	// Retrieve Hero Table
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	// Find all checked elements
	UInt iItemCount = pHeroTable->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemChecked(i) ) {
			// Max Hero Level
			HeroID iHeroID = (HeroID)(UIntPtr)( pHeroTable->GetItemData(i) );
			Hero * pHero = CCGOPFn->GetHero( iHeroID );
			pHero->SetLevel( HERO_MAX_LEVEL );

			// Update HeroTable
			pHeroTable->UpdateItem( i );
		}
	}
	
	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroOptionsEvolveModel implementation
HeroOptionsEvolveModel::HeroOptionsEvolveModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_EVOLVED)
{
	m_pGUI = NULL;
}
HeroOptionsEvolveModel::~HeroOptionsEvolveModel()
{
	// nothing to do
}

Void HeroOptionsEvolveModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Toggle Evolved") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroOptionsEvolveModel::GetLayout() const
{
	HeroOptions * pHeroOptions = m_pGUI->GetHeroExplorer()->GetHeroOptions();
	WinGUIGroupBox * pGroupBox = pHeroOptions->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + 2 * (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT);

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroOptionsEvolveModel::OnClick()
{
	// Retrieve Hero Table
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	// Find all checked elements
	UInt iItemCount = pHeroTable->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemChecked(i) ) {
			// Toggle Hero Evolved
			HeroID iHeroID = (HeroID)(UIntPtr)( pHeroTable->GetItemData(i) );
			Hero * pHero = CCGOPFn->GetHero( iHeroID );
			Bool bEvolved = pHero->IsEvolved();
			pHero->SetEvolved( !bEvolved );

			// Update HeroTable
			pHeroTable->UpdateItem( i );
		}
	}
	
	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroOptionsSanctifyChoiceModel implementation
HeroOptionsSanctifyChoiceModel::HeroOptionsSanctifyChoiceModel():
	WinGUIComboBoxModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_SANCTIFYCHOICE)
{
	m_pGUI = NULL;
}
HeroOptionsSanctifyChoiceModel::~HeroOptionsSanctifyChoiceModel()
{
	// nothing to do
}

Void HeroOptionsSanctifyChoiceModel::Initialize( CCGOPGUI * pGUI )
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
Void HeroOptionsSanctifyChoiceModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < HERO_SANCTIFY_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Hero Sanctify ...") );
}

const WinGUILayout * HeroOptionsSanctifyChoiceModel::GetLayout() const
{
	HeroOptions * pHeroOptions = m_pGUI->GetHeroExplorer()->GetHeroOptions();
	WinGUIGroupBox * pGroupBox = pHeroOptions->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + 3 * (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT) + CCGOP_LAYOUT_SPACING_GAP_VERT;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	return &hLayout;
}

Void HeroOptionsSanctifyChoiceModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < HERO_SANCTIFY_COUNT );

	StringFn->NCopy( outBuffer, GameDataFn->GetHeroSanctifyName((HeroSanctify)iItemIndex), iMaxLength - 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// HeroOptionsSanctifyModel implementation
HeroOptionsSanctifyModel::HeroOptionsSanctifyModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_SANCTIFY)
{
	m_pGUI = NULL;
}
HeroOptionsSanctifyModel::~HeroOptionsSanctifyModel()
{
	// nothing to do
}

Void HeroOptionsSanctifyModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Sanctify") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroOptionsSanctifyModel::GetLayout() const
{
	HeroOptions * pHeroOptions = m_pGUI->GetHeroExplorer()->GetHeroOptions();
	WinGUIGroupBox * pGroupBox = pHeroOptions->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + 4 * (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT) + CCGOP_LAYOUT_SPACING_GAP_VERT;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroOptionsSanctifyModel::OnClick()
{
	// Retrieve Hero Table
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	// Retrieve Sanctify Choice
	WinGUIComboBox * pSanctifyChoice = m_pGUI->GetHeroExplorer()->GetHeroOptions()->m_pSanctifyChoice;
	UInt iSelected = pSanctifyChoice->GetSelectedItem();
	HeroSanctify iSanctify = (HeroSanctify)(UIntPtr)( pSanctifyChoice->GetItemData(iSelected) );

	// Find all checked elements
	UInt iItemCount = pHeroTable->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemChecked(i) ) {
			HeroID iHeroID = (HeroID)(UIntPtr)( pHeroTable->GetItemData(i) );
			Hero * pHero = CCGOPFn->GetHero( iHeroID );

			// Check if Hero is eligible
			if ( pHero->GetRank() < HERO_RANK_6S || pHero->GetLevel() < HERO_MAX_LEVEL )
				continue;

			// Sanctify Hero
			pHero->SetSanctification( iSanctify );

			// Update HeroTable
			pHeroTable->UpdateItem( i );
		}
	}
	
	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroOptionsDeleteModel implementation
HeroOptionsDeleteModel::HeroOptionsDeleteModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_DELETE)
{
	m_pGUI = NULL;
}
HeroOptionsDeleteModel::~HeroOptionsDeleteModel()
{
	// nothing to do
}

Void HeroOptionsDeleteModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("DELETE !") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * HeroOptionsDeleteModel::GetLayout() const
{
	HeroOptions * pHeroOptions = m_pGUI->GetHeroExplorer()->GetHeroOptions();
	WinGUIGroupBox * pGroupBox = pHeroOptions->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, CCGOP_LAYOUT_GROUPBOX_PADDING );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + 5 * (CCGOP_LAYOUT_BUTTON_HEIGHT + CCGOP_LAYOUT_SPACING_VERT) + 2 * CCGOP_LAYOUT_SPACING_GAP_VERT;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	return &hLayout;
}

Bool HeroOptionsDeleteModel::OnClick()
{
	// Confirmation Message
	WinGUIMessageBoxOptions hOptions;
	hOptions.iType = WINGUI_MESSAGEBOX_OKCANCEL;
	hOptions.iIcon = WINGUI_MESSAGEBOX_ICON_WARNING;
	hOptions.iDefaultResponse = WINGUI_MESSAGEBOX_RESPONSE_CANCEL;
	hOptions.bMustAnswer = true;

	WinGUIMessageBoxResponse iResponse = WinGUIFn->SpawnMessageBox(
		TEXT("Confirmation"),
		TEXT("YOU ARE ABOUT TO DELETE ALL CHECKED HEROES !!!\nAre you sure you want to continue ?"),
		hOptions
	);

	// Abort
	if ( iResponse != WINGUI_MESSAGEBOX_RESPONSE_OK )
		return true;

	// Retrieve Hero Table
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->m_pHeroTable;

	// Delete all checked elements
	while( true ) {
		Bool bRemoved = false;

		UInt iItemCount = pHeroTable->GetItemCount();
		for( UInt i = 0; i < iItemCount; ++i ) {
			if ( pHeroTable->IsItemChecked(i) ) {
				HeroID iHeroID = (HeroID)(UIntPtr)( pHeroTable->GetItemData(i) );

				// Remove from HeroTable
				pHeroTable->RemoveItem( i );

				// Delete Hero
				CCGOPFn->DestroyHero( iHeroID );

				// Bail out
				bRemoved = true;
				break;
			}
		}

		// Done
		if ( !bRemoved )
			break;
	}

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// HeroOptions implementation
HeroOptions::HeroOptions( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pMaxRank = NULL;
	m_pMaxLevel = NULL;
	m_pEvolve = NULL;
	m_pSanctifyChoice = NULL;
	m_pSanctify = NULL;
	m_pDelete = NULL;
}
HeroOptions::~HeroOptions()
{
	// nothing to do
}

Void HeroOptions::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetRoot( CCGOP_MAINMENU_HERO_EXPLORER );

	// Build Hero Options UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &(m_hGroupModel) );

	m_hMaxRankModel.Initialize( m_pGUI );
	m_pMaxRank = WinGUIFn->CreateButton( m_pRoot, &(m_hMaxRankModel) );

	m_hMaxLevelModel.Initialize( m_pGUI );
	m_pMaxLevel = WinGUIFn->CreateButton( m_pRoot, &(m_hMaxLevelModel) );

	m_hEvolveModel.Initialize( m_pGUI );
	m_pEvolve = WinGUIFn->CreateButton( m_pRoot, &(m_hEvolveModel) );

	m_hSanctifyChoiceModel.Initialize( m_pGUI );
	m_pSanctifyChoice = WinGUIFn->CreateComboBox( m_pRoot, &(m_hSanctifyChoiceModel) );
	m_hSanctifyChoiceModel.Update();

	m_hSanctifyModel.Initialize( m_pGUI );
	m_pSanctify = WinGUIFn->CreateButton( m_pRoot, &(m_hSanctifyModel) );

	m_hDeleteModel.Initialize( m_pGUI );
	m_pDelete = WinGUIFn->CreateButton( m_pRoot, &(m_hDeleteModel) );
}
Void HeroOptions::Cleanup()
{
	// nothing to do (for now)
}


