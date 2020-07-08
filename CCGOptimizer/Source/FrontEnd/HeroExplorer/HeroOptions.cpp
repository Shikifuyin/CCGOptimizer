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
// UIHeroOptionsGroupModel implementation
UIHeroOptionsGroupModel::UIHeroOptionsGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_GROUP)
{
	m_pGUI = NULL;
}
UIHeroOptionsGroupModel::~UIHeroOptionsGroupModel()
{
	// nothing to do
}

Void UIHeroOptionsGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Hero Options :") );
}

const WinGUILayout * UIHeroOptionsGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(3,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(2,0,0,1) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_HEROEXPLORER_ROOM_LEFT;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_HEROEXPLORER_ROOM_TOP;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroOptionsMaxRankModel implementation
UIHeroOptionsMaxRankModel::UIHeroOptionsMaxRankModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_MAXRANK)
{
	m_pGUI = NULL;
}
UIHeroOptionsMaxRankModel::~UIHeroOptionsMaxRankModel()
{
	// nothing to do
}

Void UIHeroOptionsMaxRankModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Max Rank") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroOptionsMaxRankModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIHeroOptionsMaxRankModel::OnClick()
{
	// Retrieve Hero Table
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	// Find all checked elements
	Bool bChanged = false;
	UInt iItemCount = pHeroTable->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemChecked(i) ) {
			// Max Hero Rank
			HeroID iHeroID = (HeroID)(UIntPtr)( pHeroTable->GetItemData(i) );
			Hero * pHero = CCGOPFn->GetHero( iHeroID );
			pHero->SetRank( HERO_RANK_6S );

			// Update HeroTable
			pHeroTable->UpdateItem( i );

			bChanged = true;
		}
	}

	// Set Unsaved Changes Mark
	if ( bChanged )
		m_pGUI->GetImportExport()->GetLoadSave()->SetUnsavedChangesMark();
	
	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroOptionsMaxLevelModel implementation
UIHeroOptionsMaxLevelModel::UIHeroOptionsMaxLevelModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_MAXLEVEL)
{
	m_pGUI = NULL;
}
UIHeroOptionsMaxLevelModel::~UIHeroOptionsMaxLevelModel()
{
	// nothing to do
}

Void UIHeroOptionsMaxLevelModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Max Level") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroOptionsMaxLevelModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIHeroOptionsMaxLevelModel::OnClick()
{
	// Retrieve Hero Table
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	// Find all checked elements
	Bool bChanged = false;
	UInt iItemCount = pHeroTable->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		if ( pHeroTable->IsItemChecked(i) ) {
			// Max Hero Level
			HeroID iHeroID = (HeroID)(UIntPtr)( pHeroTable->GetItemData(i) );
			Hero * pHero = CCGOPFn->GetHero( iHeroID );
			pHero->SetLevel( HERO_MAX_LEVEL );

			// Update HeroTable
			pHeroTable->UpdateItem( i );

			bChanged = true;
		}
	}
	
	// Set Unsaved Changes Mark
	if ( bChanged )
		m_pGUI->GetImportExport()->GetLoadSave()->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroOptionsEvolveModel implementation
UIHeroOptionsEvolveModel::UIHeroOptionsEvolveModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_EVOLVED)
{
	m_pGUI = NULL;
}
UIHeroOptionsEvolveModel::~UIHeroOptionsEvolveModel()
{
	// nothing to do
}

Void UIHeroOptionsEvolveModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Toggle Evolved") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroOptionsEvolveModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(2,0,0,0);
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

Bool UIHeroOptionsEvolveModel::OnClick()
{
	// Retrieve Hero Table
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	// Find all checked elements
	Bool bChanged = false;
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

			bChanged = true;
		}
	}

	// Set Unsaved Changes Mark
	if ( bChanged )
		m_pGUI->GetImportExport()->GetLoadSave()->SetUnsavedChangesMark();
	
	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroOptionsSanctifyChoiceModel implementation
UIHeroOptionsSanctifyChoiceModel::UIHeroOptionsSanctifyChoiceModel():
	WinGUIComboBoxModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_SANCTIFYCHOICE)
{
	m_pGUI = NULL;
}
UIHeroOptionsSanctifyChoiceModel::~UIHeroOptionsSanctifyChoiceModel()
{
	// nothing to do
}

Void UIHeroOptionsSanctifyChoiceModel::Initialize( CCGOPGUI * pGUI )
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
Void UIHeroOptionsSanctifyChoiceModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	for( UInt i = 0; i < HERO_SANCTIFY_COUNT; ++i ) {
		pController->AddItem( i );
		pController->SetItemData( i, (Void*)i );
	}

	pController->SetCueText( TEXT("Hero Sanctify ...") );
}

const WinGUILayout * UIHeroOptionsSanctifyChoiceModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,0,0,1);

	return &hLayout;
}

Void UIHeroOptionsSanctifyChoiceModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT )
		pController->SelectItem( INVALID_OFFSET );
}

Void UIHeroOptionsSanctifyChoiceModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < HERO_SANCTIFY_COUNT );

	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);
	HeroSanctify iSanctify = (HeroSanctify)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->NCopy( outBuffer, GameDataFn->GetHeroSanctifyName(iSanctify), iMaxLength - 1 );
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroOptionsSanctifyModel implementation
UIHeroOptionsSanctifyModel::UIHeroOptionsSanctifyModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_SANCTIFY)
{
	m_pGUI = NULL;
}
UIHeroOptionsSanctifyModel::~UIHeroOptionsSanctifyModel()
{
	// nothing to do
}

Void UIHeroOptionsSanctifyModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Sanctify") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroOptionsSanctifyModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(0,0,1,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,0,0,1);

	return &hLayout;
}

Bool UIHeroOptionsSanctifyModel::OnClick()
{
	// Retrieve Hero Table
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	// Retrieve Sanctify Choice
	WinGUIComboBox * pSanctifyChoice = m_pGUI->GetHeroExplorer()->GetHeroOptions()->GetSanctifyChoice();
	UInt iSelected = pSanctifyChoice->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET )
		return true;

	HeroSanctify iSanctify = (HeroSanctify)(UIntPtr)( pSanctifyChoice->GetItemData(iSelected) );

	// Find all checked elements
	Bool bChanged = false;
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

			bChanged = true;
		}
	}

	// Set Unsaved Changes Mark
	if ( bChanged )
		m_pGUI->GetImportExport()->GetLoadSave()->SetUnsavedChangesMark();
	
	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroOptionsDeleteModel implementation
UIHeroOptionsDeleteModel::UIHeroOptionsDeleteModel():
	WinGUIButtonModel(CCGOP_RESID_HEROEXPLORER_HEROOPTIONS_DELETE)
{
	m_pGUI = NULL;
}
UIHeroOptionsDeleteModel::~UIHeroOptionsDeleteModel()
{
	// nothing to do
}

Void UIHeroOptionsDeleteModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("DELETE !") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIHeroOptionsDeleteModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetHeroExplorer()->GetHeroOptions()->GetOptionsArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_SHIFT_HORIZ(1,0,1,0);
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,0,0,1);

	return &hLayout;
}

Bool UIHeroOptionsDeleteModel::OnClick()
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
	WinGUITable * pHeroTable = m_pGUI->GetHeroExplorer()->GetHeroTable()->GetTable();

	// Delete all checked elements
	Bool bChanged = false;
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

				bChanged = true;

				// Bail out
				bRemoved = true;
				break;
			}
		}

		// Done
		if ( !bRemoved )
			break;
	}

	// Set Unsaved Changes Mark
	if ( bChanged )
		m_pGUI->GetImportExport()->GetLoadSave()->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIHeroOptions implementation
UIHeroOptions::UIHeroOptions( CCGOPGUI * pGUI )
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
UIHeroOptions::~UIHeroOptions()
{
	// nothing to do
}

Void UIHeroOptions::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_HERO_EXPLORER );

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
Void UIHeroOptions::Cleanup()
{
	// nothing to do (for now)
}


