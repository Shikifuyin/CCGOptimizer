/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetBuild.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Builder
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
#include "GearSetBuild.h"

#include "../CCGOPGUI.h"

#pragma warning(disable:4312) // Converting UInts to Void*

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildGroupModel implementation
UIGearSetBuildGroupModel::UIGearSetBuildGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_GROUP)
{
	m_pGUI = NULL;
}
UIGearSetBuildGroupModel::~UIGearSetBuildGroupModel()
{
	// nothing to do
}

Void UIGearSetBuildGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("GearSet Builder :") );
}

const WinGUILayout * UIGearSetBuildGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = ( CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH + CCGOP_LAYOUT_SPACING_GAP_HORIZ ) * RUNE_SLOT_COUNT + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(3,8,1,0) + CCGOP_LAYOUT_SPACING_GAP_VERT + 2 * CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_GEARSETEXPLORER_ROOM_LEFT;
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_GEARSETEXPLORER_ROOM_TOP + CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iY, CCGOP_LAYOUT_GEARSETEXPLORER_ROOM_HEIGHT );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildSlotGroupModel implementation
UIGearSetBuildSlotGroupModel::UIGearSetBuildSlotGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_SLOTGROUP)
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
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(2,8,1,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + ( m_iSlot * (hLayout.FixedSize.iX + CCGOP_LAYOUT_SPACING_GAP_HORIZ) );
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildHeadLineModel implementation
UIGearSetBuildHeadLineModel::UIGearSetBuildHeadLineModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_HEADLINE)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildHeadLineModel::~UIGearSetBuildHeadLineModel()
{
	// nothing to do
}

Void UIGearSetBuildHeadLineModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("---") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetBuildHeadLineModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected Rune
	WinGUIComboBox * pRunePool = m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetRunePool( m_iSlot );
	UInt iSelected = pRunePool->GetSelectedItem();

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("---") );
		return;
	}

	// Retrieve Rune
	RuneID iRuneID = (RuneID)(UIntPtr)( pRunePool->GetItemData(iSelected) );
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// Build HeadLine
	GChar strHeadLine[64];
	StringFn->Format( strHeadLine, TEXT("(%d) %s %s %s +%d"),
		iRuneID,
		GameDataFn->GetRuneRankName( pRune->GetRank() ),
		GameDataFn->GetRuneQualityName( pRune->GetQuality() ),
		GameDataFn->GetRuneSetName( pRune->GetSet() ),
		pRune->GetLevel()
	);

	// Done
	pController->SetText( strHeadLine );
}

const WinGUILayout * UIGearSetBuildHeadLineModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetSlotArea( &hClientArea, m_iSlot );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = ( CCGOP_LAYOUT_STATICTEXT_HEIGHT << 1 );

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildMainStatModel implementation
UIGearSetBuildMainStatModel::UIGearSetBuildMainStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_MAINSTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildMainStatModel::~UIGearSetBuildMainStatModel()
{
	// nothing to do
}

Void UIGearSetBuildMainStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetBuildMainStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected Rune
	WinGUIComboBox * pRunePool = m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetRunePool( m_iSlot );
	UInt iSelected = pRunePool->GetSelectedItem();

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve Rune
	RuneID iRuneID = (RuneID)(UIntPtr)( pRunePool->GetItemData(iSelected) );
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// Build Main Stat String
	GChar strMainStat[64];
	StringFn->Format( strMainStat, TEXT("(Main) %s %d"),
		GameDataFn->GetRuneStatName( pRune->GetMainStat() ),
		pRune->GetMainStatValue()
	);

	// Done
	pController->SetText( strMainStat );
}

const WinGUILayout * UIGearSetBuildMainStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetSlotArea( &hClientArea, m_iSlot );

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
// UIGearSetBuildInnateStatModel implementation
UIGearSetBuildInnateStatModel::UIGearSetBuildInnateStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_INNATESTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildInnateStatModel::~UIGearSetBuildInnateStatModel()
{
	// nothing to do
}

Void UIGearSetBuildInnateStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetBuildInnateStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected Rune
	WinGUIComboBox * pRunePool = m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetRunePool( m_iSlot );
	UInt iSelected = pRunePool->GetSelectedItem();

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve Rune
	RuneID iRuneID = (RuneID)(UIntPtr)( pRunePool->GetItemData(iSelected) );
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// No Innate Stat case
	if ( pRune->GetInnateStat() == RUNE_STAT_COUNT ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Build Innate Stat String
	GChar strInnateStat[64];
	StringFn->Format( strInnateStat, TEXT("(Innate) %s %d"),
		GameDataFn->GetRuneStatName( pRune->GetInnateStat() ),
		pRune->GetInnateStatValue()
	);

	// Done
	pController->SetText( strInnateStat );
}

const WinGUILayout * UIGearSetBuildInnateStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetSlotArea( &hClientArea, m_iSlot );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,3,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildRandomStatModel implementation
UIGearSetBuildRandomStatModel::UIGearSetBuildRandomStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_RANDOMSTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
	m_iIndex = INVALID_OFFSET;
}
UIGearSetBuildRandomStatModel::~UIGearSetBuildRandomStatModel()
{
	// nothing to do
}

Void UIGearSetBuildRandomStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot, UInt iIndex )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;
	m_iIndex = iIndex;

	m_hCreationParameters.iType = WINGUI_STATIC_TEXT;
	m_hCreationParameters.bAddSunkenBorder = false;

	StringFn->Copy( m_hCreationParameters.hText.strLabel, TEXT("") );
	m_hCreationParameters.hText.iAlign = WINGUI_STATIC_TEXT_ALIGN_LEFT;
	m_hCreationParameters.hText.iEllipsis = WINGUI_STATIC_TEXT_ELLIPSIS_NONE;

	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetBuildRandomStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected Rune
	WinGUIComboBox * pRunePool = m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetRunePool( m_iSlot );
	UInt iSelected = pRunePool->GetSelectedItem();

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve Rune
	RuneID iRuneID = (RuneID)(UIntPtr)( pRunePool->GetItemData(iSelected) );
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// No Random Stat case
	if ( pRune->GetRandomStatCount() <= m_iIndex ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve Random Stat
	RuneStat iRuneStat = pRune->GetRandomStat( m_iIndex );

	// Build Random Stat String
	GChar strRandomStat[64];
	StringFn->Format( strRandomStat, TEXT("%s %d"),
		GameDataFn->GetRuneStatName( iRuneStat ),
		pRune->GetRandomStatValue( iRuneStat )
	);

	// Done
	pController->SetText( strRandomStat );
}

const WinGUILayout * UIGearSetBuildRandomStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetSlotArea( &hClientArea, m_iSlot );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_STATICTEXT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_STATICTEXT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,4 + m_iIndex,0,0);

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildRunePoolModel implementation
UIGearSetBuildRunePoolModel::UIGearSetBuildRunePoolModel():
	WinGUIComboBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_RUNE)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildRunePoolModel::~UIGearSetBuildRunePoolModel()
{
	// nothing to do
}

Void UIGearSetBuildRunePoolModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
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
Void UIGearSetBuildRunePoolModel::Update()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;
	pController->RemoveAllItems();

	pController->SetCueText( TEXT("Pooled Runes ...") );
}

const WinGUILayout * UIGearSetBuildRunePoolModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetSlotArea( &hClientArea, m_iSlot );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_COMBOBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_COMBOBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,4 + RUNE_RANDOM_STAT_COUNT,0,0);

	return &hLayout;
}

Void UIGearSetBuildRunePoolModel::OnMousePress( const WinGUIPoint & hPoint, KeyCode iKey )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);

	if ( iKey == KEYCODE_MOUSERIGHT ) {
		pController->SelectItem( INVALID_OFFSET );

		// Update Models
		m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->UpdateModels( m_iSlot );
	}
}

Bool UIGearSetBuildRunePoolModel::OnSelectionOK()
{
	// Update Models
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->UpdateModels( m_iSlot );

	return true;
}

Void UIGearSetBuildRunePoolModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	WinGUIComboBox * pController = ((WinGUIComboBox*)m_pController);
	RuneID iRuneID = (RuneID)(UIntPtr)( pController->GetItemData(iItemIndex) );

	StringFn->FromUInt( outBuffer, iRuneID );
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildRuneRemoveModel implementation
UIGearSetBuildRuneRemoveModel::UIGearSetBuildRuneRemoveModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_RUNEREMOVE)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildRuneRemoveModel::~UIGearSetBuildRuneRemoveModel()
{
	// nothing to do
}

Void UIGearSetBuildRuneRemoveModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Remove") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetBuildRuneRemoveModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetSlotArea( &hClientArea, m_iSlot );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,4 + RUNE_RANDOM_STAT_COUNT,1,0);

	return &hLayout;
}

Bool UIGearSetBuildRuneRemoveModel::OnClick()
{
	// Retrieve selected Rune
	WinGUIComboBox * pRunePool = m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetRunePool( m_iSlot );
	UInt iSelected = pRunePool->GetSelectedItem();
	if ( iSelected == INVALID_OFFSET )
		return true;

	// Remove from pool
	pRunePool->RemoveItem( iSelected );
	pRunePool->SelectItem( INVALID_OFFSET );

	// Update Models
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->UpdateModels( m_iSlot );

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildRuneEquipModel implementation
UIGearSetBuildRuneEquipModel::UIGearSetBuildRuneEquipModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_RUNEEQUIP)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetBuildRuneEquipModel::~UIGearSetBuildRuneEquipModel()
{
	// nothing to do
}

Void UIGearSetBuildRuneEquipModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Equip") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetBuildRuneEquipModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetSlotArea( &hClientArea, m_iSlot );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,4 + RUNE_RANDOM_STAT_COUNT,1,0);

	return &hLayout;
}

Bool UIGearSetBuildRuneEquipModel::OnClick()
{
	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelectedGearSet = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelectedGearSet, 1 );

	if ( iSelectedGearSet == INVALID_OFFSET )
		return true;

	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelectedGearSet) );

	// Retrieve selected Rune
	WinGUIComboBox * pRunePool = m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetRunePool( m_iSlot );
	UInt iSelectedRune = pRunePool->GetSelectedItem();

	if ( iSelectedRune == INVALID_OFFSET )
		return true;

	RuneID iRuneID = (RuneID)(UIntPtr)( pRunePool->GetItemData(iSelectedRune) );

	// Equip the rune
	CCGOPFn->EquipRuneToGearSet( iRuneID, iGearSetID );

	// Update Models
	pGearSetTable->UpdateItem( iSelectedGearSet );
	m_pGUI->GetGearSetExplorer()->GetGearSetDetails()->UpdateModels( m_iSlot );
	m_pGUI->GetGearSetExplorer()->GetGearSetStats()->UpdateModels();

	// Set Unsaved Changes Mark
	m_pGUI->GetImportExport()->GetLoadSave()->SetUnsavedChangesMark();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuildClearPoolsModel implementation
UIGearSetBuildClearPoolsModel::UIGearSetBuildClearPoolsModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETBUILD_CLEARPOOLS)
{
	m_pGUI = NULL;
}
UIGearSetBuildClearPoolsModel::~UIGearSetBuildClearPoolsModel()
{
	// nothing to do
}

Void UIGearSetBuildClearPoolsModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Clear All Pools") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetBuildClearPoolsModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + CCGOP_LAYOUT_CENTER( hLayout.FixedSize.iX, hClientArea.iWidth );
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(2,4 + RUNE_RANDOM_STAT_COUNT,1,0) + CCGOP_LAYOUT_SPACING_GAP_VERT + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	return &hLayout;
}

Bool UIGearSetBuildClearPoolsModel::OnClick()
{
	// Enum all slots
	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		WinGUIComboBox * pRunePool = m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->GetRunePool( i );
		pRunePool->RemoveAllItems();

		m_pGUI->GetGearSetExplorer()->GetGearSetBuild()->UpdateModels( i );
	}

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetBuild implementation
UIGearSetBuild::UIGearSetBuild( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		m_arrBuildSlots[i].pSlotGroup = NULL;
		m_arrBuildSlots[i].pHeadLine = NULL;
		m_arrBuildSlots[i].pMainStat = NULL;
		m_arrBuildSlots[i].pInnateStat = NULL;
		for( UInt j = 0; j < RUNE_RANDOM_STAT_COUNT; ++j )
			m_arrBuildSlots[i].arrRandomStats[j].pStat = NULL;

		m_arrBuildSlots[i].pRunePool = NULL;
		m_arrBuildSlots[i].pRuneRemove = NULL;
		m_arrBuildSlots[i].pRuneEquip = NULL;
	}

	m_pClearPools = NULL;
}
UIGearSetBuild::~UIGearSetBuild()
{
	// nothing to do
}

Void UIGearSetBuild::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_GEARSET_EXPLORER );

	// Build GearSet Build UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroupModel );

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		m_arrBuildSlots[i].hSlotGroupModel.Initialize( m_pGUI, i );
		m_arrBuildSlots[i].pSlotGroup = WinGUIFn->CreateGroupBox( m_pRoot, &(m_arrBuildSlots[i].hSlotGroupModel) );

		m_arrBuildSlots[i].hHeadLineModel.Initialize( m_pGUI, i );
		m_arrBuildSlots[i].pHeadLine = WinGUIFn->CreateStatic( m_pRoot, &(m_arrBuildSlots[i].hHeadLineModel) );

		m_arrBuildSlots[i].hMainStatModel.Initialize( m_pGUI, i );
		m_arrBuildSlots[i].pMainStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrBuildSlots[i].hMainStatModel) );

		m_arrBuildSlots[i].hInnateStatModel.Initialize( m_pGUI, i );
		m_arrBuildSlots[i].pInnateStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrBuildSlots[i].hInnateStatModel) );

		for( UInt j = 0; j < RUNE_RANDOM_STAT_COUNT; ++j ) {
			m_arrBuildSlots[i].arrRandomStats[j].hStatModel.Initialize( m_pGUI, i, j );
			m_arrBuildSlots[i].arrRandomStats[j].pStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrBuildSlots[i].arrRandomStats[j].hStatModel) );
		}

		m_arrBuildSlots[i].hRunePoolModel.Initialize( m_pGUI, i );
		m_arrBuildSlots[i].pRunePool = WinGUIFn->CreateComboBox( m_pRoot, &(m_arrBuildSlots[i].hRunePoolModel) );
		m_arrBuildSlots[i].hRunePoolModel.Update();

		m_arrBuildSlots[i].hRuneRemoveModel.Initialize( m_pGUI, i );
		m_arrBuildSlots[i].pRuneRemove = WinGUIFn->CreateButton( m_pRoot, &(m_arrBuildSlots[i].hRuneRemoveModel) );

		m_arrBuildSlots[i].hRuneEquipModel.Initialize( m_pGUI, i );
		m_arrBuildSlots[i].pRuneEquip = WinGUIFn->CreateButton( m_pRoot, &(m_arrBuildSlots[i].hRuneEquipModel) );
	}

	m_hClearPoolsModel.Initialize( m_pGUI );
	m_pClearPools = WinGUIFn->CreateButton( m_pRoot, &m_hClearPoolsModel );
}
Void UIGearSetBuild::Cleanup()
{
	// nothing to do (for now)
}

Void UIGearSetBuild::UpdateModels( UInt iSlot )
{
	Assert( iSlot < RUNE_SLOT_COUNT );

	m_arrBuildSlots[iSlot].hHeadLineModel.Update();
	m_arrBuildSlots[iSlot].hMainStatModel.Update();
	m_arrBuildSlots[iSlot].hInnateStatModel.Update();
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i )
		m_arrBuildSlots[iSlot].arrRandomStats[i].hStatModel.Update();
}
Void UIGearSetBuild::AddPooledRune( RuneID iRuneID )
{
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );
	UInt iSlot = pRune->GetSlot();

	WinGUIComboBox * pRunePool = m_arrBuildSlots[iSlot].pRunePool;

	UInt iItemCount = pRunePool->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		RuneID iAlreadyPooled = (RuneID)(UIntPtr)( pRunePool->GetItemData(i) );
		if ( iAlreadyPooled == iRuneID )
			return;
	}

	pRunePool->AddItem( iItemCount );
	pRunePool->SetItemData( iItemCount, (Void*)iRuneID );
}
Void UIGearSetBuild::RemovePooledRune( RuneID iRuneID )
{
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );
	UInt iSlot = pRune->GetSlot();

	WinGUIComboBox * pRunePool = m_arrBuildSlots[iSlot].pRunePool;

	UInt iItemCount = pRunePool->GetItemCount();
	for ( UInt i = 0; i < iItemCount; ++i ) {
		RuneID iPooledRuneID = (RuneID)(UIntPtr)( pRunePool->GetItemData(i) );
		if ( iPooledRuneID == iRuneID ) {
			pRunePool->RemoveItem( i );
			return;
		}
	}
}
