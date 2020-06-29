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

	m_hCreationParameters.iType = WINGUI_COMBOBOX_BUTTON;
	m_hCreationParameters.iCase = WINGUI_COMBOBOX_CASE_BOTH;
	m_hCreationParameters.iInitialSelectedItem = 0;
	m_hCreationParameters.bAllowHorizontalScroll = false;
	m_hCreationParameters.bAutoSort = false;
	m_hCreationParameters.bEnableTabStop = true;

	GameData::HeroDataMap::Iterator itHeroData = GameDataFn->EnumHeroData();
	while( !(itHeroData.IsNull()) ) {
		m_arrHeroNames.Push( itHeroData.GetKey() );
		++itHeroData;
	}
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

UInt HeroCreationNameModel::GetItemCount() const
{
	return m_arrHeroNames.Count();
}
const GChar * HeroCreationNameModel::GetItemString( UInt iIndex ) const
{
	Assert( iIndex < m_arrHeroNames.Count() );
	return m_arrHeroNames[iIndex];
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

	m_hCreationParameters.iType = WINGUI_COMBOBOX_BUTTON;
	m_hCreationParameters.iCase = WINGUI_COMBOBOX_CASE_BOTH;
	m_hCreationParameters.iInitialSelectedItem = 0;
	m_hCreationParameters.bAllowHorizontalScroll = false;
	m_hCreationParameters.bAutoSort = false;
	m_hCreationParameters.bEnableTabStop = true;
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

UInt HeroCreationRankModel::GetItemCount() const
{
	return HERO_RANK_COUNT;
}
const GChar * HeroCreationRankModel::GetItemString( UInt iIndex ) const
{
	Assert( iIndex < HERO_RANK_COUNT );
	return GameDataFn->GetHeroRankName( (HeroRank)iIndex );
}
Void * HeroCreationRankModel::GetItemData( UInt iIndex ) const
{
	Assert( iIndex < HERO_RANK_COUNT );
	static HeroRank arrValues[HERO_RANK_COUNT] = {
		HERO_RANK_1S,
		HERO_RANK_2S,
		HERO_RANK_3S,
		HERO_RANK_4S,
		HERO_RANK_5S,
		HERO_RANK_6S
	};
	return ( arrValues + iIndex );
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

	m_hRankModel.Initialize( m_pGUI );
	m_pRank = WinGUIFn->CreateComboBox( m_pRoot, &(m_hRankModel) );
}
Void HeroCreation::Cleanup()
{
	// nothing to do (for now)
}

