/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Hero.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Hero Representation
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "Hero.h"

/////////////////////////////////////////////////////////////////////////////////
// Hero implementation
Hero::Hero():
	m_arrAttachedGearSets()
{
	m_iHeroID = INVALID_OFFSET;
	m_strName[0] = NULLBYTE;
	m_iFaction = HERO_FACTION_COUNT;
	m_iRank = HERO_RANK_COUNT;
	m_iLevel = INVALID_OFFSET;
	m_bEvolved = false;
	m_iSanctify = HERO_SANCTIFY_COUNT;

	m_arrAttachedGearSets.Create();
	m_iSelectedGearSet = INVALID_OFFSET;
}
Hero::Hero( HeroID iHeroID, const GChar * strName, HeroRank iRank, UInt iLevel, Bool bEvolved, HeroSanctify iSanctify ):
	m_arrAttachedGearSets()
{
	m_iHeroID = iHeroID;
	StringFn->NCopy( m_strName, strName, GAMEDATA_NAMES_MAX_LENGTH - 1 );
	Assert( GameDataFn->IsHeroNameValid(m_strName) );
	m_iFaction = GameDataFn->GetHeroFaction( m_strName );
	m_iRank = iRank;
	Assert( m_iRank >= GameDataFn->GetHeroNaturalRank( m_strName ) );
	m_iLevel = iLevel;
	Assert( m_iLevel <= GameDataFn->GetHeroRankMaxLevel(m_iRank) );
	m_bEvolved = bEvolved;
	m_iSanctify = iSanctify;

	m_arrAttachedGearSets.Create();
	m_iSelectedGearSet = INVALID_OFFSET;
}
Hero::~Hero()
{
	m_arrAttachedGearSets.Destroy();
}

Void Hero::ImportFromXML( XMLNode * pNode )
{
	Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("hero")) == 0 );

	UInt i;
    GChar strNameBuffer[XML_NAME_SIZE];

	// Hero ID
	XMLAttribute * pAttribute = pNode->GetAttribute( TEXT("hero_id") );
	Assert( pAttribute != NULL );
	m_iHeroID = (HeroID)( StringFn->ToUInt(pAttribute->GetValue()) );

	// Name
	pAttribute = pNode->GetAttribute( TEXT("name") );
	Assert( pAttribute != NULL );
	StringFn->NCopy( m_strName, pAttribute->GetValue(), GAMEDATA_NAMES_MAX_LENGTH - 1 );
	Assert( GameDataFn->IsHeroNameValid(m_strName) );

	// Faction
	m_iFaction = GameDataFn->GetHeroFaction( m_strName );

	// Rank
	pAttribute = pNode->GetAttribute( TEXT("rank") );
	Assert( pAttribute != NULL );
	m_iRank = (HeroRank)( StringFn->ToUInt(pAttribute->GetValue()) );
	Assert( m_iRank >= GameDataFn->GetHeroNaturalRank(m_strName) );

	// Level
	pAttribute = pNode->GetAttribute( TEXT("level") );
	Assert( pAttribute != NULL );
	m_iLevel = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );
	Assert( m_iLevel <= GameDataFn->GetHeroRankMaxLevel(m_iRank) );

	// Evolved
	pAttribute = pNode->GetAttribute( TEXT("evolved") );
    Assert( pAttribute != NULL );
    m_bEvolved = ( StringFn->Cmp(pAttribute->GetValue(),TEXT("true")) == 0 );

	// Sanctify
	pAttribute = pNode->GetAttribute( TEXT("sanctify") );
	Assert( pAttribute != NULL );
	m_iSanctify = (HeroSanctify)( StringFn->ToUInt(pAttribute->GetValue()) );

	// State
	m_arrAttachedGearSets.Clear();
	XMLNode * pSubNode = pNode->GetChildByTag( TEXT("attached_gearsets"), 0 );
	Assert( pSubNode != NULL );

	pAttribute = pSubNode->GetAttribute( TEXT("count") );
    Assert( pAttribute != NULL );
    UInt iGearSetCount = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

	for( i = 0; i < iGearSetCount; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("gearset_%d"), i );
        pAttribute = pSubNode->GetAttribute( strNameBuffer );
        Assert( pAttribute != NULL );

        m_arrAttachedGearSets.Push( (GearSetID)( StringFn->ToUInt(pAttribute->GetValue()) ) );
    }

	pAttribute = pNode->GetAttribute( TEXT("gearset_selected") );
	Assert( pAttribute != NULL );
	m_iSelectedGearSet = (GearSetID)( StringFn->ToUInt(pAttribute->GetValue()) );
}	
Void Hero::ExportToXML( XMLNode * pNode ) const
{
	Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("hero")) == 0 );

	UInt i;
    GChar strNameBuffer[XML_NAME_SIZE];
    GChar strValueBuffer[64];

	// Hero ID
    StringFn->FromUInt( strValueBuffer, m_iHeroID );
    pNode->CreateAttribute( TEXT("hero_id"), strValueBuffer );

	// Name
    pNode->CreateAttribute( TEXT("name"), m_strName );

	// Rank
	StringFn->FromUInt( strValueBuffer, m_iRank );
    pNode->CreateAttribute( TEXT("rank"), strValueBuffer );

	// Level
	StringFn->FromUInt( strValueBuffer, m_iLevel );
    pNode->CreateAttribute( TEXT("level"), strValueBuffer );

	// Evolved
    pNode->CreateAttribute( TEXT("evolved"), m_bEvolved ? TEXT("true") : TEXT("false") );

	// Sanctify
	StringFn->FromUInt( strValueBuffer, m_iSanctify );
    pNode->CreateAttribute( TEXT("sanctify"), strValueBuffer );

	// State
	XMLNode * pSubNode = XMLFn->CreateNode( TEXT("attached_gearsets"), true );

    UInt iGearSetCount = m_arrAttachedGearSets.Count();
    StringFn->FromUInt( strValueBuffer, iGearSetCount );
    pSubNode->CreateAttribute( TEXT("count"), strValueBuffer );

    for( i = 0; i < iGearSetCount; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("gearset_%d"), i );
        StringFn->FromUInt( strValueBuffer, m_arrAttachedGearSets[i] );
        pSubNode->CreateAttribute( strNameBuffer, strValueBuffer );
    }

    pNode->AppendChild( pSubNode );

	StringFn->FromUInt( strValueBuffer, m_iSelectedGearSet );
    pNode->CreateAttribute( TEXT("gearset_selected"), strValueBuffer );
}

