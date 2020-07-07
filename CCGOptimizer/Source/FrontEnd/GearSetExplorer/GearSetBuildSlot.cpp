/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetBuildSlot.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Build Slots
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
#include "GearSetBuildSlot.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlotGroupModel implementation
UIGearSetBuildSlotGroupModel::UIGearSetBuildSlotGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILDSLOT_GROUP)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildSlotGroupModel::~UIGearSetBuildSlotGroupModel()
{
	// nothing to do
}

Void UIGearSetBuildSlotGroupModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->Format( m_hCreationParameters.strLabel, TEXT("Slot %d :"), m_iSlot + 1 );
}

const WinGUILayout * UIGearSetBuildSlotGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(2,7,1,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ROOM_LEFT + CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_ROOM_WIDTH )
							 - ( (RUNE_SLOT_COUNT - m_iSlot) * (hLayout.FixedSize.iX + CCGOP_LAYOUT_SPACING_GAP_HORIZ) );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_ROOM_TOP + CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iY, CCGOP_LAYOUT_ROOM_HEIGHT );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlotHeadLineModel implementation
UIGearSetBuildSlotHeadLineModel::UIGearSetBuildSlotHeadLineModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILDSLOT_HEADLINE)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildSlotHeadLineModel::~UIGearSetBuildSlotHeadLineModel()
{
	// nothing to do
}

Void UIGearSetBuildSlotHeadLineModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("Rune : ---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetBuildSlotHeadLineModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected Rune
	WinGUIComboBox * pRuneBox = m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetRune();
	UInt iSelected = pRuneBox->GetSelectedItem();

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("Rune : ---") );
		return;
	}

	// Retrieve Rune
	RuneID iRuneID = (RuneID)(UIntPtr)( pRuneBox->GetItemData(iSelected) );
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// Build HeadLine
	GChar strHeadLine[64];
	StringFn->Format( strHeadLine, TEXT("Rune (%d) : %s %s %s +%d"),
		iRuneID,
		GameDataFn->GetRuneRankName( pRune->GetRank() ),
		GameDataFn->GetRuneQualityName( pRune->GetQuality() ),
		GameDataFn->GetRuneSetName( pRune->GetSet() ),
		pRune->GetLevel()
	);

	// Done
	pController->SetText( strHeadLine );
}

const WinGUILayout * UIGearSetBuildSlotHeadLineModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlotMainStatModel implementation
UIGearSetBuildSlotMainStatModel::UIGearSetBuildSlotMainStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILDSLOT_MAINSTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildSlotMainStatModel::~UIGearSetBuildSlotMainStatModel()
{
	// nothing to do
}

Void UIGearSetBuildSlotMainStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("Main Stat : ---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetBuildSlotMainStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected Rune
	WinGUIComboBox * pRuneBox = m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetRune();
	UInt iSelected = pRuneBox->GetSelectedItem();

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("Main Stat : ---") );
		return;
	}

	// Retrieve Rune
	RuneID iRuneID = (RuneID)(UIntPtr)( pRuneBox->GetItemData(iSelected) );
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// Build Main Stat String
	GChar strMainStat[64];
	StringFn->Format( strMainStat, TEXT("Main Stat : %s %d"),
		GameDataFn->GetRuneStatName( pRune->GetMainStat() ),
		pRune->GetMainStatValue()
	);

	// Done
	pController->SetText( strMainStat );
}

const WinGUILayout * UIGearSetBuildSlotMainStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,1,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlotInnateStatModel implementation
UIGearSetBuildSlotInnateStatModel::UIGearSetBuildSlotInnateStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILDSLOT_INNATESTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildSlotInnateStatModel::~UIGearSetBuildSlotInnateStatModel()
{
	// nothing to do
}

Void UIGearSetBuildSlotInnateStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("Innate Stat : ---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetBuildSlotInnateStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected Rune
	WinGUIComboBox * pRuneBox = m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetRune();
	UInt iSelected = pRuneBox->GetSelectedItem();

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("Innate Stat : ---") );
		return;
	}

	// Retrieve Rune
	RuneID iRuneID = (RuneID)(UIntPtr)( pRuneBox->GetItemData(iSelected) );
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// No Innate Stat case
	if ( pRune->GetInnateStat() == RUNE_STAT_COUNT ) {
		pController->SetText( TEXT("Innate Stat : ---") );
		return;
	}

	// Build Innate Stat String
	GChar strInnateStat[64];
	StringFn->Format( strInnateStat, TEXT("Innate Stat : %s %d"),
		GameDataFn->GetRuneStatName( pRune->GetInnateStat() ),
		pRune->GetInnateStatValue()
	);

	// Done
	pController->SetText( strInnateStat );
}

const WinGUILayout * UIGearSetBuildSlotInnateStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,2,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlotRandomStatModel implementation
UIGearSetBuildSlotRandomStatModel::UIGearSetBuildSlotRandomStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILDSLOT_RANDOMSTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
	m_iIndex = INVALID_OFFSET;
}
UIGearSetBuildSlotRandomStatModel::~UIGearSetBuildSlotRandomStatModel()
{
	// nothing to do
}

Void UIGearSetBuildSlotRandomStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot, UInt iIndex )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;
	m_iIndex = iIndex;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("Random Stat : ---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetBuildSlotRandomStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected Rune
	WinGUIComboBox * pRuneBox = m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetRune();
	UInt iSelected = pRuneBox->GetSelectedItem();

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("Random Stat : ---") );
		return;
	}

	// Retrieve Rune
	RuneID iRuneID = (RuneID)(UIntPtr)( pRuneBox->GetItemData(iSelected) );
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// No Random Stat case
	if ( pRune->GetRandomStatCount() <= m_iIndex ) {
		pController->SetText( TEXT("Random Stat : ---") );
		return;
	}

	// Retrieve Random Stat
	RuneStat iRuneStat = pRune->GetRandomStat( m_iIndex );

	// Build Random Stat String
	GChar strRandomStat[64];
	StringFn->Format( strRandomStat, TEXT("Random Stat : %s %d"),
		GameDataFn->GetRuneStatName( iRuneStat ),
		pRune->GetRandomStatValue( iRuneStat )
	);

	// Done
	pController->SetText( strRandomStat );
}

const WinGUILayout * UIGearSetBuildSlotRandomStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,3 + m_iIndex,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlotRuneModel implementation
UIGearSetBuildSlotRuneModel::UIGearSetBuildSlotRuneModel():
	WinGUIComboBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILDSLOT_RUNE)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildSlotRuneModel::~UIGearSetBuildSlotRuneModel()
{
	// nothing to do
}

Void UIGearSetBuildSlotRuneModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

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
Void UIGearSetBuildSlotRuneModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	pController->SetCueText( TEXT("Pooled Runes ...") );
}

const WinGUILayout * UIGearSetBuildSlotRuneModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,3 + RUNE_RANDOM_STAT_COUNT,0,0);

	return &hLayout;
}

Void UIGearSetBuildSlotRuneModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Update Models
		m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->UpdateModels();
	}
}

Bool UIGearSetBuildSlotRuneModel::OnSelectionOK()
{
	// Update Models
	m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->UpdateModels();

	return true;
}

Void UIGearSetBuildSlotRuneModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);
	RuneID iRuneID = (RuneID)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->FromUInt( outBuffer, iRuneID );
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlotRuneRemoveModel implementation
UIGearSetBuildSlotRuneRemoveModel::UIGearSetBuildSlotRuneRemoveModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILDSLOT_RUNEREMOVE)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildSlotRuneRemoveModel::~UIGearSetBuildSlotRuneRemoveModel()
{
	// nothing to do
}

Void UIGearSetBuildSlotRuneRemoveModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Remove") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetBuildSlotRuneRemoveModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,3 + RUNE_RANDOM_STAT_COUNT,1,0);

	return &hLayout;
}

Bool UIGearSetBuildSlotRuneRemoveModel::OnClick()
{
	// Retrieve selected Rune
	WinGUIComboBox * pRuneBox = m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetRune();
	UInt iSelected = pRuneBox->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET )
		return true;

	// Remove from pool
	pRuneBox->RemoveItem( iSelected );
	pRuneBox->SelectItem( INVALID_OFFSET );

	// Update Models
	m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->UpdateModels();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlotRuneEquipModel implementation
UIGearSetBuildSlotRuneEquipModel::UIGearSetBuildSlotRuneEquipModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILDSLOT_RUNEEQUIP)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildSlotRuneEquipModel::~UIGearSetBuildSlotRuneEquipModel()
{
	// nothing to do
}

Void UIGearSetBuildSlotRuneEquipModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Equip") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetBuildSlotRuneEquipModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetSlotArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,3 + RUNE_RANDOM_STAT_COUNT,1,0);

	return &hLayout;
}

Bool UIGearSetBuildSlotRuneEquipModel::OnClick()
{
	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelectedGearSet = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelectedGearSet, 1 );

	if ( iSelectedGearSet == INVALID_OFFSET )
		return true;

	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelectedGearSet) );

	// Retrieve selected Rune
	WinGUIComboBox * pRuneBox = m_pGUI->GetGearSetExplorer()->GetGearSetBuildSlot(m_iSlot)->GetRune();
	UInt iSelectedRune = pRuneBox->GetSelectedItem();

	if ( iSelectedRune == INVALID_OFFSET )
		return true;

	RuneID iRuneID = (RuneID)(UIntPtr)( pRuneBox->GetItemData(iSelectedRune) );

	// Equip the rune
	CCGOPFn->EquipRuneToGearSet( iRuneID, iGearSetID );

	// Update Models
	pGearSetTable->UpdateItem( iSelectedGearSet );
	m_pGUI->GetGearSetExplorer()->GetGearSetSlot(m_iSlot)->UpdateModels();
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->UpdateModels();

	// Set Unsaved Changes Mark
	m_pGUI->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlot implementation
UIGearSetBuildSlot::UIGearSetBuildSlot()
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
	m_pRoot = NULL;

	m_pGroup = NULL;
	m_pHeadLine = NULL;
	m_pMainStat = NULL;
	m_pInnateStat = NULL;
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i )
		m_arrRandomStats[i].pStat = NULL;

	m_pRune = NULL;
	m_pRuneRemove = NULL;
}
UIGearSetBuildSlot::~UIGearSetBuildSlot()
{
	// nothing to do
}

Void UIGearSetBuildSlot::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_GEARSET_EXPLORER );

	// Build GearSet Stats UI
	m_hGroupModel.Initialize( m_pGUI, m_iSlot );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroupModel );

	m_hHeadLineModel.Initialize( m_pGUI, m_iSlot );
	m_pHeadLine = WinGUIFn->CreateStatic( m_pRoot, &m_hHeadLineModel );

	m_hMainStatModel.Initialize( m_pGUI, m_iSlot );
	m_pMainStat = WinGUIFn->CreateStatic( m_pRoot, &m_hMainStatModel );

	m_hInnateStatModel.Initialize( m_pGUI, m_iSlot );
	m_pInnateStat = WinGUIFn->CreateStatic( m_pRoot, &m_hInnateStatModel );

	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
		m_arrRandomStats[i].hStatModel.Initialize( m_pGUI, m_iSlot, i );
		m_arrRandomStats[i].pStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrRandomStats[i].hStatModel) );
	}

	m_hRuneModel.Initialize( m_pGUI, m_iSlot );
	m_pRune = WinGUIFn->CreateComboBox( m_pRoot, &m_hRuneModel );
	m_hRuneModel.Update();

	m_hRuneRemoveModel.Initialize( m_pGUI, m_iSlot );
	m_pRuneRemove = WinGUIFn->CreateButton( m_pRoot, &m_hRuneRemoveModel );

	m_hRuneEquipModel.Initialize( m_pGUI, m_iSlot );
	m_pRuneEquip = WinGUIFn->CreateButton( m_pRoot, &m_hRuneEquipModel );
}
Void UIGearSetBuildSlot::Cleanup()
{
	// nothing to do
}

Void UIGearSetBuildSlot::UpdateModels()
{
	m_hHeadLineModel.Update();
	m_hMainStatModel.Update();
	m_hInnateStatModel.Update();
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i )
		m_arrRandomStats[i].hStatModel.Update();
}
Void UIGearSetBuildSlot::AddPooledRune( RuneID iRuneID )
{
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );
	Assert( pRune->GetSlot() == m_iSlot );

	UInt iItemCount = m_pRune->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		RuneID iAlreadyPooled = (RuneID)(UIntPtr)( m_pRune->GetItemData(i) );
		if ( iAlreadyPooled == iRuneID )
			return;
	}

	m_pRune->AddItem( iItemCount );
	m_pRune->SetItemData( iItemCount, (Void*)iRuneID );
}
