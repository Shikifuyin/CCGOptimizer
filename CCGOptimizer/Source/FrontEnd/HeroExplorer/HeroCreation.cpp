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
	hLayout.FixedPosition.iX = 10;
	hLayout.FixedPosition.iY = 620;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = 200;
	hLayout.FixedSize.iY = 200;

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
Void HeroCreationNameModel::Populate()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;

	for( UInt i = 0; i < m_arrHeroNames.Count(); ++i )
		pController->AddItem( i );

	pController->SetCueText( TEXT("Hero Name ...") );
}

const WinGUILayout * HeroCreationNameModel::GetLayout() const
{
	HeroCreation * pHeroCreation = m_pGUI->GetHeroExplorer()->GetHeroCreation();
	WinGUIGroupBox * pGroupBox = pHeroCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, 8 );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = 100;
	hLayout.FixedSize.iY = 100;

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
	pHeroRankModel->UpdateFirstAvailableRank( iNaturalRank );

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
Void HeroCreationRankModel::Populate()
{
	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;

	for( UInt i = m_iFirstAvailableRank; i < HERO_RANK_COUNT; ++i ) {
		pController->AddItem( i - m_iFirstAvailableRank );
		pController->SetItemData( i - m_iFirstAvailableRank, (Void*)i );
	}

	pController->SetCueText( TEXT("Hero Rank ...") );
}

Void HeroCreationRankModel::UpdateFirstAvailableRank( HeroRank iFirstAvailableRank )
{
	m_iFirstAvailableRank = iFirstAvailableRank;

	WinGUIComboBox * pController = (WinGUIComboBox*)m_pController;

	pController->RemoveAllItems();
	Populate();
}

const WinGUILayout * HeroCreationRankModel::GetLayout() const
{
	HeroCreation * pHeroCreation = m_pGUI->GetHeroExplorer()->GetHeroCreation();
	WinGUIGroupBox * pGroupBox = pHeroCreation->m_pGroup;

	WinGUIRectangle hClientArea;
	pGroupBox->ComputeClientArea( &hClientArea, 8 );

	static WinGUIManualLayout hLayout;

	hLayout.UseScalingPosition = false;
	hLayout.FixedPosition.iX = hClientArea.iLeft;
	hLayout.FixedPosition.iY = hClientArea.iTop + 24;

	hLayout.UseScalingSize = false;
	hLayout.FixedSize.iX = 100;
	hLayout.FixedSize.iY = 120;

	return &hLayout;
}

Bool HeroCreationRankModel::OnSelectionOK()
{
	return true;
}

Void HeroCreationRankModel::OnRequestItemLabel( GChar * outBuffer, UInt iMaxLength, UInt iItemIndex, Void * pItemData )
{
	Assert( iItemIndex < HERO_RANK_COUNT );

	StringFn->NCopy( outBuffer, GameDataFn->GetHeroRankName((HeroRank)(m_iFirstAvailableRank + iItemIndex)), iMaxLength - 1 );
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
	m_hNameModel.Populate();

	m_hRankModel.Initialize( m_pGUI );
	m_pRank = WinGUIFn->CreateComboBox( m_pRoot, &(m_hRankModel) );
	m_hRankModel.Populate();
}
Void HeroCreation::Cleanup()
{
	// nothing to do (for now)
}

