/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Rune.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Representation
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "Rune.h"

/////////////////////////////////////////////////////////////////////////////////
// Rune implementation
Rune::Rune():
    m_arrEquippedGearSets()
{
    m_iRuneID = INVALID_OFFSET;
    m_iSlot = INVALID_OFFSET;
    m_iSet = RUNE_SET_COUNT;
    m_iRank = RUNE_RANK_COUNT;
    m_iQuality = RUNE_QUALITY_COUNT;
    m_iLevel = INVALID_OFFSET;

    m_iMainStat = RUNE_STAT_COUNT;

    m_iInnateStat = RUNE_STAT_COUNT;
    m_iInnateStatValue = 0;

    m_iRandomStatCount = 0;
    for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i )
        m_arrRandomStats[i] = RUNE_STAT_COUNT;
    for( UInt i = 0; i < RUNE_STAT_COUNT; ++i )
        m_arrRandomStatValues[i] = 0;

    m_bLocked = false;
    m_iEquippedGearSetsCount = 0;

    m_fScoreEfficiency = 0.0f;
    m_fScoreDamage = 0.0f;
    m_fScoreTanking = 0.0f;
}
Rune::Rune( RuneID iRuneID, UInt iSlot, RuneSet iSet, RuneRank iRank, RuneQuality iQuality, UInt iLevel,
            RuneStat iMainStat, RuneStat iInnateStat, UInt iInnateStatValue,
            UInt iRandomStatCount, const RuneStat * arrRandomStats, const UInt * arrRandomStatValues ):
    m_arrEquippedGearSets()
{
    m_iRuneID = iRuneID;
    m_iSlot = iSlot;
    m_iSet = iSet;
    m_iRank = iRank;
    m_iQuality = iQuality;
    m_iLevel = iLevel;

    m_iMainStat = iMainStat;

    m_iInnateStat = iInnateStat;
    m_iInnateStatValue = iInnateStatValue;

    for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i )
        m_arrRandomStats[i] = RUNE_STAT_COUNT;
    for( UInt i = 0; i < RUNE_STAT_COUNT; ++i )
        m_arrRandomStatValues[i] = 0;

    Assert( iRandomStatCount <= RUNE_RANDOM_STAT_COUNT );
    m_iRandomStatCount = iRandomStatCount;
    for( UInt i = 0; i < iRandomStatCount; ++i ) {
        m_arrRandomStats[i] = arrRandomStats[i];
        if ( arrRandomStats[i] < RUNE_STAT_COUNT ) {
            Assert( arrRandomStatValues[i] > 0 );
            m_arrRandomStatValues[arrRandomStats[i]] = arrRandomStatValues[i];
        }
    }

    m_bLocked = false;
    m_iEquippedGearSetsCount = 0;

    m_fScoreEfficiency = 0.0f;
    m_fScoreDamage = 0.0f;
    m_fScoreTanking = 0.0f;
    _ComputeScores();
}
Rune::~Rune()
{
    // nothing to do
}

Void Rune::ImportFromXML( XMLNode * pNode )
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("rune")) == 0 );

    UInt i;
    GChar strNameBuffer[XML_NAME_SIZE];

    // Rune ID
    XMLAttribute * pAttribute = pNode->GetAttribute( TEXT("rune_id") );
    Assert( pAttribute != NULL );
    m_iRuneID = (RuneID)( StringFn->ToUInt(pAttribute->GetValue()) );

    // Slot
    pAttribute = pNode->GetAttribute( TEXT("slot") );
    Assert( pAttribute != NULL );
    m_iSlot = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

    // Set
    pAttribute = pNode->GetAttribute( TEXT("set") );
    Assert( pAttribute != NULL );
    m_iSet = (RuneSet)( StringFn->ToUInt(pAttribute->GetValue()) );

    // Rank
    pAttribute = pNode->GetAttribute( TEXT("rank") );
    Assert( pAttribute != NULL );
    m_iRank = (RuneRank)( StringFn->ToUInt(pAttribute->GetValue()) );

    // Quality
    pAttribute = pNode->GetAttribute( TEXT("quality") );
    Assert( pAttribute != NULL );
    m_iQuality = (RuneQuality)( StringFn->ToUInt(pAttribute->GetValue()) );

    // Level
    pAttribute = pNode->GetAttribute( TEXT("level") );
    Assert( pAttribute != NULL );
    m_iLevel = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

    // Main Stat
    pAttribute = pNode->GetAttribute( TEXT("main_stat") );
    Assert( pAttribute != NULL );
    m_iMainStat = (RuneStat)( StringFn->ToUInt(pAttribute->GetValue()) );

    Bool bAllowed = GameDataFn->IsRuneMainStatAllowed( m_iMainStat, m_iSlot );
    Assert( bAllowed );

    // Innate Stat
    XMLNode * pSubNode = pNode->GetChildByTag( TEXT("innate_stat"), 0 );
    Assert( pSubNode != NULL );

    pAttribute = pSubNode->GetAttribute( TEXT("type") );
    Assert( pAttribute != NULL );
    m_iInnateStat = (RuneStat)( StringFn->ToUInt(pAttribute->GetValue()) );

    pAttribute = pSubNode->GetAttribute( TEXT("value") );
    Assert( pAttribute != NULL );
    m_iInnateStatValue = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

    // Random Stats
    m_iRandomStatCount = 0;
    for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i )
        m_arrRandomStats[i] = RUNE_STAT_COUNT;
    for( i = 0; i < RUNE_STAT_COUNT; ++i )
        m_arrRandomStatValues[i] = 0;
    for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("random_stat_%d"), i );
        pSubNode = pNode->GetChildByTag( strNameBuffer, 0 );
        Assert( pSubNode != NULL );

        pAttribute = pSubNode->GetAttribute( TEXT("type") );
        Assert( pAttribute != NULL );
        RuneStat iRuneStat = (RuneStat)( StringFn->ToUInt(pAttribute->GetValue()) );

        pAttribute = pSubNode->GetAttribute( TEXT("value") );
        Assert( pAttribute != NULL );
        UInt iValue = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

        if ( iRuneStat < RUNE_STAT_COUNT ) {
            Assert( iValue > 0 );
            m_arrRandomStats[m_iRandomStatCount] = iRuneStat;
            m_arrRandomStatValues[iRuneStat] = iValue;
            ++m_iRandomStatCount;
        }
    }

    // State
    pAttribute = pNode->GetAttribute( TEXT("locked") );
    Assert( pAttribute != NULL );
    m_bLocked = ( StringFn->Cmp(pAttribute->GetValue(),TEXT("true")) == 0 );

    m_iEquippedGearSetsCount = 0;
    pSubNode = pNode->GetChildByTag( TEXT("equipped_gearsets"), 0 );
    Assert( pSubNode != NULL );

    pAttribute = pSubNode->GetAttribute( TEXT("count") );
    Assert( pAttribute != NULL );
    UInt iGearSetCount = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

    for( i = 0; i < iGearSetCount; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("gearset_%d"), i );
        pAttribute = pSubNode->GetAttribute( strNameBuffer );
        Assert( pAttribute != NULL );

        if ( m_iEquippedGearSetsCount >= RUNE_MAX_GEARSETS )
            break;

        m_arrEquippedGearSets[m_iEquippedGearSetsCount] = (GearSetID)( StringFn->ToUInt(pAttribute->GetValue()) );
        ++m_iEquippedGearSetsCount;
    }

    // Score System
    m_fScoreEfficiency = 0.0f;
    m_fScoreDamage = 0.0f;
    m_fScoreTanking = 0.0f;
    _ComputeScores();
}
Void Rune::ExportToXML( XMLNode * pNode ) const
{
    Assert( StringFn->Cmp(pNode->GetTagName(), TEXT("rune")) == 0 );

    UInt i;
    GChar strNameBuffer[XML_NAME_SIZE];
    GChar strValueBuffer[64];

    // Rune ID
    StringFn->FromUInt( strValueBuffer, m_iRuneID );
    pNode->CreateAttribute( TEXT("rune_id"), strValueBuffer );

    // Slot
    StringFn->FromUInt( strValueBuffer, m_iSlot );
    pNode->CreateAttribute( TEXT("slot"), strValueBuffer );

    // Set
    StringFn->FromUInt( strValueBuffer, m_iSet );
    pNode->CreateAttribute( TEXT("set"), strValueBuffer );

    // Rank
    StringFn->FromUInt( strValueBuffer, m_iRank );
    pNode->CreateAttribute( TEXT("rank"), strValueBuffer );

    // Quality
    StringFn->FromUInt( strValueBuffer, m_iQuality );
    pNode->CreateAttribute( TEXT("quality"), strValueBuffer );

    // Level
    StringFn->FromUInt( strValueBuffer, m_iLevel );
    pNode->CreateAttribute( TEXT("level"), strValueBuffer );

    // Main Stat
    StringFn->FromUInt( strValueBuffer, m_iMainStat );
    pNode->CreateAttribute( TEXT("main_stat"), strValueBuffer );

    // Innate Stat
    XMLNode * pSubNode = XMLFn->CreateNode( TEXT("innate_stat"), true );

    StringFn->FromUInt( strValueBuffer, m_iInnateStat );
    pSubNode->CreateAttribute( TEXT("type"), strValueBuffer );

    StringFn->FromUInt( strValueBuffer, m_iInnateStatValue );
    pSubNode->CreateAttribute( TEXT("value"), strValueBuffer );

    pNode->AppendChild( pSubNode );

    // Random Stats
    for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("random_stat_%d"), i );
        pSubNode = XMLFn->CreateNode( strNameBuffer, true );

        UInt iValue = 0;
        if ( m_arrRandomStats[i] < RUNE_STAT_COUNT )
            iValue = m_arrRandomStatValues[m_arrRandomStats[i]];

        StringFn->FromUInt( strValueBuffer, m_arrRandomStats[i] );
        pSubNode->CreateAttribute( TEXT("type"), strValueBuffer );

        StringFn->FromUInt( strValueBuffer, iValue );
        pSubNode->CreateAttribute( TEXT("value"), strValueBuffer );

        pNode->AppendChild( pSubNode );
    }

    // State
    pNode->CreateAttribute( TEXT("locked"), m_bLocked ? TEXT("true") : TEXT("false") );

    pSubNode = XMLFn->CreateNode( TEXT("equipped_gearsets"), true );

    UInt iGearSetCount = m_iEquippedGearSetsCount;
    StringFn->FromUInt( strValueBuffer, iGearSetCount );
    pSubNode->CreateAttribute( TEXT("count"), strValueBuffer );

    for( i = 0; i < iGearSetCount; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("gearset_%d"), i );
        StringFn->FromUInt( strValueBuffer, m_arrEquippedGearSets[i] );
        pSubNode->CreateAttribute( strNameBuffer, strValueBuffer );
    }

    pNode->AppendChild( pSubNode );
}

Bool Rune::HasGearSet( GearSetID iGearSetID ) const
{
    for( UInt i = 0; i < m_iEquippedGearSetsCount; ++i ) {
		if ( m_arrEquippedGearSets[i] == iGearSetID )
			return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////

UInt Rune::_EquipToGearSet( GearSetID iGearSetID )
{
    UInt iIndex = INVALID_OFFSET;
	for( UInt i = 0; i < m_iEquippedGearSetsCount; ++i ) {
		if ( m_arrEquippedGearSets[i] == iGearSetID ) {
			iIndex = i;
			break;
		}
	}
	if ( iIndex != INVALID_OFFSET )
		return iIndex;

	if ( m_iEquippedGearSetsCount >= RUNE_MAX_GEARSETS )
		return INVALID_OFFSET;

	m_arrEquippedGearSets[m_iEquippedGearSetsCount] = iGearSetID;
	++m_iEquippedGearSetsCount;

	return ( m_iEquippedGearSetsCount - 1 );
}
Void Rune::_UnequipFromGearSet( GearSetID iGearSetID )
{
	UInt iIndex = INVALID_OFFSET;
	for( UInt i = 0; i < m_iEquippedGearSetsCount; ++i ) {
		if ( m_arrEquippedGearSets[i] == iGearSetID ) {
			m_arrEquippedGearSets[i] = m_arrEquippedGearSets[m_iEquippedGearSetsCount - 1];
			--m_iEquippedGearSetsCount;
			break;
		}
	}
}

Void Rune::_ComputeScores()
{
    /////////////////////////////////////
    // Need some math infos here ....
}
