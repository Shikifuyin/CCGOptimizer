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
    for( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
        m_arrRandomStats[i] = RUNE_STAT_COUNT;
        m_arrRandomStatValues[i] = 0;
    }

    m_bLocked = false;
    m_arrEquippedGearSets.Create();

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
    for( UInt i = 0; i < iRandomStatCount; ++i ) {
        m_arrRandomStats[i] = arrRandomStats[i];
        m_arrRandomStatValues[i] = arrRandomStatValues[i];
    }

    m_bLocked = false;
    m_arrEquippedGearSets.Create();

    m_fScoreEfficiency = 0.0f;
    m_fScoreDamage = 0.0f;
    m_fScoreTanking = 0.0f;
    _ComputeScores();
}
Rune::~Rune()
{
    m_arrEquippedGearSets.Destroy();
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
    for( i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("random_stat_%d"), i );
        pSubNode = pNode->GetChildByTag( strNameBuffer, 0 );
        Assert( pSubNode != NULL );

        pAttribute = pSubNode->GetAttribute( TEXT("type") );
        Assert( pAttribute != NULL );
        m_arrRandomStats[i] = (RuneStat)( StringFn->ToUInt(pAttribute->GetValue()) );

        pAttribute = pSubNode->GetAttribute( TEXT("value") );
        Assert( pAttribute != NULL );
        m_arrRandomStatValues[i] = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );
    }

    // State
    pAttribute = pNode->GetAttribute( TEXT("locked") );
    Assert( pAttribute != NULL );
    m_bLocked = ( StringFn->Cmp(pAttribute->GetValue(),TEXT("true")) == 0 );

    m_arrEquippedGearSets.Clear();
    pSubNode = pNode->GetChildByTag( TEXT("equipped_gearsets"), 0 );
    Assert( pSubNode != NULL );

    pAttribute = pSubNode->GetAttribute( TEXT("count") );
    Assert( pAttribute != NULL );
    UInt iGearSetCount = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

    for( i = 0; i < iGearSetCount; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("gearset_%d"), i );
        pAttribute = pSubNode->GetAttribute( strNameBuffer );
        Assert( pAttribute != NULL );

        m_arrEquippedGearSets.Push( (GearSetID)( StringFn->ToUInt(pAttribute->GetValue()) ) );
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

        StringFn->FromUInt( strValueBuffer, m_arrRandomStats[i] );
        pSubNode->CreateAttribute( TEXT("type"), strValueBuffer );

        StringFn->FromUInt( strValueBuffer, m_arrRandomStatValues[i] );
        pSubNode->CreateAttribute( TEXT("value"), strValueBuffer );

        pNode->AppendChild( pSubNode );
    }

    // State
    pNode->CreateAttribute( TEXT("locked"), m_bLocked ? TEXT("true") : TEXT("false") );

    pSubNode = XMLFn->CreateNode( TEXT("equipped_gearsets"), true );

    UInt iGearSetCount = m_arrEquippedGearSets.Count();
    StringFn->FromUInt( strValueBuffer, iGearSetCount );
    pSubNode->CreateAttribute( TEXT("count"), strValueBuffer );

    for( i = 0; i < iGearSetCount; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("gearset_%d"), i );
        StringFn->FromUInt( strValueBuffer, m_arrEquippedGearSets[i] );
        pSubNode->CreateAttribute( strNameBuffer, strValueBuffer );
    }

    pNode->AppendChild( pSubNode );
}

UInt Rune::HasRandomStat( RuneStat iRuneStat ) const
{
    UInt iIndex = INVALID_OFFSET;
    for ( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
        if ( m_arrRandomStats[i] == iRuneStat ) {
            iIndex = i;
            break;
        }
    }
    if ( iIndex != INVALID_OFFSET )
        return m_arrRandomStatValues[iIndex];
    return 0;
}
UInt Rune::HasSubStat( RuneStat iRuneStat ) const
{
    if ( m_iInnateStat == iRuneStat )
        return m_iInnateStatValue;
    UInt iIndex = INVALID_OFFSET;
    for ( UInt i = 0; i < RUNE_RANDOM_STAT_COUNT; ++i ) {
        if ( m_arrRandomStats[i] == iRuneStat ) {
            iIndex = i;
            break;
        }
    }
    if ( iIndex != INVALID_OFFSET )
        return m_arrRandomStatValues[iIndex];
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////

Void Rune::_ComputeScores()
{
    /////////////////////////////////////
    // Need some math infos here ....
}
