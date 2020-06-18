/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/GearSet.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Gear Sets
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
#include "GearSet.h"

/////////////////////////////////////////////////////////////////////////////////
// GearSet implementation
GearSet::GearSet():
    m_arrAttachedHeroes()
{
    m_iGearSetID = INVALID_OFFSET;
    m_strName[0] = NULLBYTE;
        
    for ( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
        m_arrEquippedRunes[i] = INVALID_OFFSET;
    m_arrAttachedHeroes.Create();

    m_fScoreEfficiency = 0.0f;
    m_fScoreDamage = 0.0f;
    m_fScoreTanking = 0.0f;
}
GearSet::GearSet( GearSetID iGearSetID, const GChar * strName ):
    m_arrAttachedHeroes()
{
    m_iGearSetID = iGearSetID;
    StringFn->NCopy( m_strName, strName, GAMEDATA_NAMES_MAX_LENGTH - 1 );
        
    for ( UInt i = 0; i < RUNE_SLOT_COUNT; ++i )
        m_arrEquippedRunes[i] = INVALID_OFFSET;
    m_arrAttachedHeroes.Create();

    m_fScoreEfficiency = 0.0f;
    m_fScoreDamage = 0.0f;
    m_fScoreTanking = 0.0f;
}
GearSet::~GearSet()
{
    m_arrAttachedHeroes.Destroy();
}

Void GearSet::ImportFromXML( XMLNode * pNode )
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("gearset")) == 0 );

    UInt i;
    GChar strNameBuffer[XML_NAME_SIZE];

	// GearSet ID
	XMLAttribute * pAttribute = pNode->GetAttribute( TEXT("gearset_id") );
	Assert( pAttribute != NULL );
	m_iGearSetID = (GearSetID)( StringFn->ToUInt(pAttribute->GetValue()) );

    // Name
    pAttribute = pNode->GetAttribute( TEXT("name") );
	Assert( pAttribute != NULL );
	StringFn->NCopy( m_strName, pAttribute->GetValue(), GAMEDATA_NAMES_MAX_LENGTH - 1 );

    // State
    for( i = 0; i < RUNE_SLOT_COUNT; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("rune_slot_%d"), i );
        pAttribute = pNode->GetAttribute( strNameBuffer );
	    Assert( pAttribute != NULL );

        m_arrEquippedRunes[i] = (RuneID)( StringFn->ToUInt(pAttribute->GetValue()) );
    }

    m_arrAttachedHeroes.Clear();
    XMLNode * pSubNode = pNode->GetChildByTag( TEXT("attached_heroes"), 0 );
    Assert( pSubNode != NULL );

    pAttribute = pSubNode->GetAttribute( TEXT("count") );
    Assert( pAttribute != NULL );
    UInt iHeroCount = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

    for( i = 0; i < RUNE_SLOT_COUNT; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("hero_%d"), i );
        pAttribute = pSubNode->GetAttribute( strNameBuffer );
        Assert( pAttribute != NULL );

        m_arrAttachedHeroes.Push( (HeroID)( StringFn->ToUInt(pAttribute->GetValue()) ) );
    }

    // Score System
    m_fScoreEfficiency = 0.0f;
    m_fScoreDamage = 0.0f;
    m_fScoreTanking = 0.0f;
    _ComputeScores();
}
Void GearSet::ExportToXML( XMLNode * pNode ) const
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("gearset")) == 0 );

    UInt i;
    GChar strNameBuffer[XML_NAME_SIZE];
    GChar strValueBuffer[64];

	// GearSet ID
    StringFn->FromUInt( strValueBuffer, m_iGearSetID );
    pNode->CreateAttribute( TEXT("gearset_id"), strValueBuffer );

    // Name
    pNode->CreateAttribute( TEXT("name"), m_strName );

    // State
    for( i = 0; i < RUNE_SLOT_COUNT; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("rune_slot_%d"), i );
        StringFn->FromUInt( strValueBuffer, m_arrEquippedRunes[i] );
        pNode->CreateAttribute( strNameBuffer, strValueBuffer );
    }

    XMLNode * pSubNode = XMLFn->CreateNode( TEXT("attached_heroes"), true );

    UInt iHeroCount = m_arrAttachedHeroes.Count();
    StringFn->FromUInt( strValueBuffer, iHeroCount );
    pSubNode->CreateAttribute( TEXT("count"), strValueBuffer );

    for( i = 0; i < iHeroCount; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("hero_%d"), i );
        StringFn->FromUInt( strValueBuffer, m_arrAttachedHeroes[i] );
        pSubNode->CreateAttribute( strNameBuffer, strValueBuffer );
    }

    pNode->AppendChild( pSubNode );
}

/////////////////////////////////////////////////////////////////////////////////

Void GearSet::_ComputeScores()
{
    /////////////////////////////////////
    // Need some math infos here ....
}

