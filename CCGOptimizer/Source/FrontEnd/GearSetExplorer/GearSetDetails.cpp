/////////////////////////////////////////////////////////////////////////////////
// File : Source/FrontEnd/GearSetExplorer/GearSetDetails.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSetExplorer GUI : GearSet Runes Display
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
#include "GearSetDetails.h"

#include "../CCGOPGUI.h"

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetDetailsGroupModel implementation
UIGearSetDetailsGroupModel::UIGearSetDetailsGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETDETAILS_GROUP)
{
	m_pGUI = NULL;
}
UIGearSetDetailsGroupModel::~UIGearSetDetailsGroupModel()
{
	// nothing to do
}

Void UIGearSetDetailsGroupModel::Initialize( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("GearSet Runes :") );
}

const WinGUILayout * UIGearSetDetailsGroupModel::GetLayout() const
{
	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = ( CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH + CCGOP_LAYOUT_SPACING_GAP_HORIZ ) * (RUNE_SLOT_COUNT >> 1) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = ( CCGOP_LAYOUT_SHIFT_VERT(2,8,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT + CCGOP_LAYOUT_SPACING_GAP_VERT ) * 2 + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = CCGOP_LAYOUT_ALIGNRIGHT( hLayout.FixedSize.iX, CCGOP_LAYOUT_CLIENT_WIDTH );
	hLayout.FixedPosition.iY = CCGOP_LAYOUT_SPACING_BORDER;

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetDetailsSlotGroupModel implementation
UIGearSetDetailsSlotGroupModel::UIGearSetDetailsSlotGroupModel():
	WinGUIGroupBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETDETAILS_SLOTGROUP)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetDetailsSlotGroupModel::~UIGearSetDetailsSlotGroupModel()
{
	// nothing to do
}

Void UIGearSetDetailsSlotGroupModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->Format( m_hCreationParameters.strLabel, TEXT("Slot %d :"), m_iSlot + 1 );
}

const WinGUILayout * UIGearSetDetailsSlotGroupModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetDetails()->GetArea( &hClientArea );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_SHIFT_HORIZ(1,0,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_SHIFT_VERT(2,8,0,0) + CCGOP_LAYOUT_GROUPBOX_FIT_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft + ( (m_iSlot >> 1) * (hLayout.FixedSize.iX + CCGOP_LAYOUT_SPACING_GAP_HORIZ) );
	hLayout.FixedPosition.iY = hClientArea.iTop + ( (m_iSlot & 1) * (hLayout.FixedSize.iY + CCGOP_LAYOUT_SPACING_GAP_VERT) );

	return &hLayout;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetDetailsHeadLineModel implementation
UIGearSetDetailsHeadLineModel::UIGearSetDetailsHeadLineModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETDETAILS_HEADLINE)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetDetailsHeadLineModel::~UIGearSetDetailsHeadLineModel()
{
	// nothing to do
}

Void UIGearSetDetailsHeadLineModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
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
Void UIGearSetDetailsHeadLineModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("---") );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET ) {
		pController->SetText( TEXT("---") );
		return;
	}

	// Retrieve Rune
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

const WinGUILayout * UIGearSetDetailsHeadLineModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetDetails()->GetSlotArea( &hClientArea, m_iSlot );

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
// UIGearSetDetailsMainStatModel implementation
UIGearSetDetailsMainStatModel::UIGearSetDetailsMainStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETDETAILS_MAINSTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetDetailsMainStatModel::~UIGearSetDetailsMainStatModel()
{
	// nothing to do
}

Void UIGearSetDetailsMainStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
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
Void UIGearSetDetailsMainStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve Rune
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

const WinGUILayout * UIGearSetDetailsMainStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetDetails()->GetSlotArea( &hClientArea, m_iSlot );

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
// UIGearSetDetailsInnateStatModel implementation
UIGearSetDetailsInnateStatModel::UIGearSetDetailsInnateStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETDETAILS_INNATESTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetDetailsInnateStatModel::~UIGearSetDetailsInnateStatModel()
{
	// nothing to do
}

Void UIGearSetDetailsInnateStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
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
Void UIGearSetDetailsInnateStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve Rune
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

const WinGUILayout * UIGearSetDetailsInnateStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetDetails()->GetSlotArea( &hClientArea, m_iSlot );

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
// UIGearSetDetailsRandomStatModel implementation
UIGearSetDetailsRandomStatModel::UIGearSetDetailsRandomStatModel():
	WinGUIStaticModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETDETAILS_RANDOMSTAT)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
	m_iIndex = INVALID_OFFSET;
}
UIGearSetDetailsRandomStatModel::~UIGearSetDetailsRandomStatModel()
{
	// nothing to do
}

Void UIGearSetDetailsRandomStatModel::Initialize( CCGOPGUI * pGUI, UInt iSlot, UInt iIndex )
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
Void UIGearSetDetailsRandomStatModel::Update()
{
	WinGUIStatic * pController = (WinGUIStatic*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET ) {
		pController->SetText( TEXT("") );
		return;
	}

	// Retrieve Rune
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

const WinGUILayout * UIGearSetDetailsRandomStatModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetDetails()->GetSlotArea( &hClientArea, m_iSlot );

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
// UIGearSetDetailsLockModel implementation
UIGearSetDetailsLockModel::UIGearSetDetailsLockModel():
	WinGUICheckBoxModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETDETAILS_LOCK)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetDetailsLockModel::~UIGearSetDetailsLockModel()
{
	// nothing to do
}

Void UIGearSetDetailsLockModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->NCopy( m_hCreationParameters.strLabel, TEXT("Locked"), 63 );

	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}
Void UIGearSetDetailsLockModel::Update()
{
	WinGUICheckBox * pController = (WinGUICheckBox*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET ) {
		pController->Disable();
		return;
	}

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET ) {
		pController->Disable();
		return;
	}

	// Retrieve Rune
	const Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// Done
	pController->Enable();
	if ( pRune->IsLocked() )
		pController->Check();
	else
		pController->Uncheck();
}

const WinGUILayout * UIGearSetDetailsLockModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetDetails()->GetSlotArea( &hClientArea, m_iSlot );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_CHECKBOX_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_CHECKBOX_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(0,4 + RUNE_RANDOM_STAT_COUNT,0,0);

	return &hLayout;
}

Bool UIGearSetDetailsLockModel::OnClick()
{
	WinGUICheckBox * pController = (WinGUICheckBox*)m_pController;

	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelected = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelected, 1 );

	// Nothing selected case
	if ( iSelected == INVALID_OFFSET )
		return true;

	// Retrieve GearSet
	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelected) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// No Rune Equipped case
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );
	if ( iRuneID == INVALID_OFFSET )
		return true;

	// Retrieve Rune
	Rune * pRune = CCGOPFn->GetRune( iRuneID );

	// Update Rune State
	if ( pController->IsChecked() )
		pRune->Lock();
	else
		pRune->Unlock();

	// Done
	return true;
}

/////////////////////////////////////////////////////////////////////////////////
// UIGearSetDetailsUnequipModel implementation
UIGearSetDetailsUnequipModel::UIGearSetDetailsUnequipModel():
	WinGUIButtonModel(CCGOP_RESID_GEARSETEXPLORER_GEARSETDETAILS_UNEQUIP)
{
	m_pGUI = NULL;
	m_iSlot = INVALID_OFFSET;
}
UIGearSetDetailsUnequipModel::~UIGearSetDetailsUnequipModel()
{
	// nothing to do
}

Void UIGearSetDetailsUnequipModel::Initialize( CCGOPGUI * pGUI, UInt iSlot )
{
	m_pGUI = pGUI;
	m_iSlot = iSlot;

	StringFn->Copy( m_hCreationParameters.strLabel, TEXT("Unequip") );
	m_hCreationParameters.bCenterLabel = true;
	m_hCreationParameters.bEnableTabStop = true;
	m_hCreationParameters.bEnableNotify = false;
}

const WinGUILayout * UIGearSetDetailsUnequipModel::GetLayout() const
{
	WinGUIRectangle hClientArea;
	m_pGUI->GetGearSetExplorer()->GetGearSetDetails()->GetSlotArea( &hClientArea, m_iSlot );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = CCGOP_LAYOUT_BUTTON_WIDTH;
	hLayout.FixedSize.iY = CCGOP_LAYOUT_BUTTON_HEIGHT;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + CCGOP_LAYOUT_SHIFT_VERT(1,4 + RUNE_RANDOM_STAT_COUNT,0,0);

	return &hLayout;
}

Bool UIGearSetDetailsUnequipModel::OnClick()
{
	// Retrieve selected GearSet
	WinGUITable * pGearSetTable = m_pGUI->GetGearSetExplorer()->GetGearSetTable()->GetTable();
	UInt iSelectedGearSet = INVALID_OFFSET;
	pGearSetTable->GetSelectedItems( &iSelectedGearSet, 1 );

	if ( iSelectedGearSet == INVALID_OFFSET )
		return true;

	GearSetID iGearSetID = (GearSetID)(UIntPtr)( pGearSetTable->GetItemData(iSelectedGearSet) );
	const GearSet * pGearSet = CCGOPFn->GetGearSet( iGearSetID );

	// Retrieve this slot's rune
	RuneID iRuneID = pGearSet->GetEquippedRune( m_iSlot );

	if ( iRuneID == INVALID_OFFSET )
		return true;

	// Unequip the rune
	CCGOPFn->UnequipRuneFromGearSet( iRuneID, iGearSetID );

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
// UIGearSetDetails implementation
UIGearSetDetails::UIGearSetDetails( CCGOPGUI * pGUI )
{
	m_pGUI = pGUI;
	m_pRoot = NULL;

	m_pGroup = NULL;

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		m_arrDetailsSlots[i].pSlotGroup = NULL;
		m_arrDetailsSlots[i].pHeadLine = NULL;
		m_arrDetailsSlots[i].pMainStat = NULL;
		m_arrDetailsSlots[i].pInnateStat = NULL;
		for( UInt j = 0; j < RUNE_RANDOM_STAT_COUNT; ++j )
			m_arrDetailsSlots[i].arrRandomStats[j].pStat = NULL;

		m_arrDetailsSlots[i].pLock = NULL;
		m_arrDetailsSlots[i].pUnequip = NULL;
	}
}
UIGearSetDetails::~UIGearSetDetails()
{
	// nothing to do
}

Void UIGearSetDetails::Initialize()
{
	// Grab Root
	m_pRoot = m_pGUI->GetTabPane( UI_MAINMENU_GEARSET_EXPLORER );

	// Build GearSet Stats UI
	m_hGroupModel.Initialize( m_pGUI );
	m_pGroup = WinGUIFn->CreateGroupBox( m_pRoot, &m_hGroupModel );

	for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		m_arrDetailsSlots[i].hSlotGroupModel.Initialize( m_pGUI, i );
		m_arrDetailsSlots[i].pSlotGroup = WinGUIFn->CreateGroupBox( m_pRoot, &(m_arrDetailsSlots[i].hSlotGroupModel) );

		m_arrDetailsSlots[i].hHeadLineModel.Initialize( m_pGUI, i );
		m_arrDetailsSlots[i].pHeadLine = WinGUIFn->CreateStatic( m_pRoot, &(m_arrDetailsSlots[i].hHeadLineModel) );

		m_arrDetailsSlots[i].hMainStatModel.Initialize( m_pGUI, i );
		m_arrDetailsSlots[i].pMainStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrDetailsSlots[i].hMainStatModel) );

		m_arrDetailsSlots[i].hInnateStatModel.Initialize( m_pGUI, i );
		m_arrDetailsSlots[i].pInnateStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrDetailsSlots[i].hInnateStatModel) );

		for( UInt j = 0; j < RUNE_RANDOM_STAT_COUNT; ++j ) {
			m_arrDetailsSlots[i].arrRandomStats[j].hStatModel.Initialize( m_pGUI, i, j );
			m_arrDetailsSlots[i].arrRandomStats[j].pStat = WinGUIFn->CreateStatic( m_pRoot, &(m_arrDetailsSlots[i].arrRandomStats[j].hStatModel) );
		}

		m_arrDetailsSlots[i].hLockModel.Initialize( m_pGUI, i );
		m_arrDetailsSlots[i].pLock = WinGUIFn->CreateCheckBox( m_pRoot, &(m_arrDetailsSlots[i].hLockModel) );
		m_arrDetailsSlots[i].hLockModel.Update();

		m_arrDetailsSlots[i].hUnequipModel.Initialize( m_pGUI, i );
		m_arrDetailsSlots[i].pUnequip = WinGUIFn->CreateButton( m_pRoot, &(m_arrDetailsSlots[i].hUnequipModel) );
	}
}
Void UIGearSetDetails::Cleanup()
{
	// nothing to do
}

Void UIGearSetDetails::UpdateModels( UInt iSlot )
{
	Assert( iSlot < RUNE_SLOT_COUNT );

	m_arrDetailsSlots[iSlot].hHeadLineModel.Update();
	m_arrDetailsSlots[iSlot].hMainStatModel.Update();
	m_arrDetailsSlots[iSlot].hInnateStatModel.Update();
	for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i )
		m_arrDetailsSlots[iSlot].arrRandomStats[i].hStatModel.Update();
	m_arrDetailsSlots[iSlot].hLockModel.Update();
}
