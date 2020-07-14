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

#include "CCGOPManager.h"

/////////////////////////////////////////////////////////////////////////////////
// GearSet implementation
GearSet::GearSet():
    m_arrAttachedHeroes()
{
    UInt i;

    m_iGearSetID = INVALID_OFFSET;
    m_strName[0] = NULLBYTE;

    m_bHasFull6Set = false;
    m_iActiveSetsCount = 0;
    for( i = 0; i < 4; ++i )
        m_arrActiveSets[i] = RUNE_SET_COUNT;

    for( i = 0; i < HERO_STAT_COUNT; ++i ) {
        m_arrEffectiveStatsPercent[i] = 0;
        m_arrEffectiveStatsFlat[i] = 0;
    }

    for( i = 0; i < RUNE_SLOT_COUNT; ++i )
        m_arrEquippedRunes[i] = INVALID_OFFSET;

    m_iAttachedHeroesCount = 0;

    m_fScoreEfficiency = 0.0f;
    m_fScoreDamage = 0.0f;
    m_fScoreTanking = 0.0f;
}
GearSet::GearSet( GearSetID iGearSetID, const GChar * strName ):
    m_arrAttachedHeroes()
{
    UInt i;

    m_iGearSetID = iGearSetID;
    StringFn->NCopy( m_strName, strName, GAMEDATA_NAMES_MAX_LENGTH - 1 );

    m_bHasFull6Set = false;
    m_iActiveSetsCount = 0;
    for( i = 0; i < 4; ++i )
        m_arrActiveSets[i] = RUNE_SET_COUNT;

    for( i = 0; i < HERO_STAT_COUNT; ++i ) {
        m_arrEffectiveStatsPercent[i] = 0;
        m_arrEffectiveStatsFlat[i] = 0;
    }

    for( i = 0; i < RUNE_SLOT_COUNT; ++i )
        m_arrEquippedRunes[i] = INVALID_OFFSET;

    m_iAttachedHeroesCount = 0;

    m_fScoreEfficiency = 0.0f;
    m_fScoreDamage = 0.0f;
    m_fScoreTanking = 0.0f;
}
GearSet::~GearSet()
{
    // nothing to do
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

    m_iAttachedHeroesCount = 0;
    XMLNode * pSubNode = pNode->GetChildByTag( TEXT("attached_heroes"), 0 );
    Assert( pSubNode != NULL );

    pAttribute = pSubNode->GetAttribute( TEXT("count") );
    Assert( pAttribute != NULL );
    UInt iHeroCount = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

    for( i = 0; i < iHeroCount; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("hero_%d"), i );
        pAttribute = pSubNode->GetAttribute( strNameBuffer );
        Assert( pAttribute != NULL );

        if ( m_iAttachedHeroesCount >= GEARSET_MAX_HEROES )
            break;

        m_arrAttachedHeroes[m_iAttachedHeroesCount] = (HeroID)( StringFn->ToUInt(pAttribute->GetValue()) );
        ++m_iAttachedHeroesCount;
    }

    // Update
    _ComputeActiveSets();
    _ComputeEffectiveStats();

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

    UInt iHeroCount = m_iAttachedHeroesCount;
    StringFn->FromUInt( strValueBuffer, iHeroCount );
    pSubNode->CreateAttribute( TEXT("count"), strValueBuffer );

    for( i = 0; i < iHeroCount; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("hero_%d"), i );
        StringFn->FromUInt( strValueBuffer, m_arrAttachedHeroes[i] );
        pSubNode->CreateAttribute( strNameBuffer, strValueBuffer );
    }

    pNode->AppendChild( pSubNode );
}

Bool GearSet::HasActiveSet( RuneSet iRuneSet, UInt * outAmount ) const
{
	if ( outAmount != NULL ) {
		*outAmount = 0;
		for( UInt i = 0; i < m_iActiveSetsCount; ++i ) {
			if ( m_arrActiveSets[i] == iRuneSet )
				++(*outAmount);
		}
		return ( *outAmount > 0 );
	} else {
		for( UInt i = 0; i < m_iActiveSetsCount; ++i ) {
			if ( m_arrActiveSets[i] == iRuneSet )
				return true;
		}
		return false;
	}
}

Bool GearSet::HasAttachedHero( HeroID iHeroID ) const
{
    for( UInt i = 0; i < m_iAttachedHeroesCount; ++i ) {
		if ( m_arrAttachedHeroes[i] == iHeroID )
			return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////

UInt GearSet::_AttachToHero( HeroID iHeroID )
{
    UInt iIndex = INVALID_OFFSET;
	for( UInt i = 0; i < m_iAttachedHeroesCount; ++i ) {
		if ( m_arrAttachedHeroes[i] == iHeroID ) {
			iIndex = i;
			break;
		}
	}
	if ( iIndex != INVALID_OFFSET )
		return iIndex;

	if ( m_iAttachedHeroesCount >= GEARSET_MAX_HEROES )
		return INVALID_OFFSET;

	m_arrAttachedHeroes[m_iAttachedHeroesCount] = iHeroID;
	++m_iAttachedHeroesCount;

	return ( m_iAttachedHeroesCount - 1 );
}
Void GearSet::_DetachFromHero( HeroID iHeroID )
{
    UInt iIndex = INVALID_OFFSET;
	for( UInt i = 0; i < m_iAttachedHeroesCount; ++i ) {
		if ( m_arrAttachedHeroes[i] == iHeroID ) {
			m_arrAttachedHeroes[i] = m_arrAttachedHeroes[m_iAttachedHeroesCount - 1];
			--m_iAttachedHeroesCount;
			break;
		}
	}
}

Void GearSet::_ComputeActiveSets()
{
    UInt i;

    // Compute Set Counts
	UInt arrSetCounts[RUNE_SET_COUNT];
	for( i = 0; i < RUNE_SET_COUNT; ++i )
		arrSetCounts[i] = 0;

	for( i = 0; i < RUNE_SLOT_COUNT; ++i ) {
		RuneID iRuneID = m_arrEquippedRunes[i];
		if ( iRuneID == INVALID_OFFSET )
			continue;
		const Rune * pRune = CCGOPFn->GetRune( iRuneID );
		++( arrSetCounts[pRune->GetSet()] );
	}

	// Compute Active Set Bonuses
    m_bHasFull6Set = false;
    m_iActiveSetsCount = 0;

	for( i = 0; i < RUNE_SET_COUNT; ++i ) {
		UInt iSetSize = GameDataFn->GetRuneSetSize( (RuneSet)i );
		if ( arrSetCounts[i] < iSetSize )
			continue;

        if ( iSetSize == 4 && arrSetCounts[i] == 6 ) {
            m_bHasFull6Set = true;
            m_arrActiveSets[m_iActiveSetsCount] = (RuneSet)i;
            ++m_iActiveSetsCount;
            break;
        }

        while( arrSetCounts[i] >= iSetSize ) {
            m_arrActiveSets[m_iActiveSetsCount] = (RuneSet)i;
            ++m_iActiveSetsCount;
            arrSetCounts[i] -= iSetSize;
        }
	}
}
Void GearSet::_ComputeEffectiveStats()
{
    UInt iHeroStat, iSlot;

    // Enum all hero stats
    for ( iHeroStat = 0; iHeroStat < HERO_STAT_COUNT; ++iHeroStat ) {
        // Compute total stat
		UInt iStatFlatTotal = 0;
		UInt iStatFlatTotalMaxed = 0;
		UInt iStatFlatTotalMaxed12Odd = 0;
		UInt iStatPercentTotal = 0;
		UInt iStatPercentTotalMaxed = 0;
		UInt iStatPercentTotalMaxed12Odd = 0;

		switch( iHeroStat ) {
			case HERO_STAT_HP: {
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						RuneID iRuneID = m_arrEquippedRunes[iSlot];
						if ( iRuneID == INVALID_OFFSET )
							continue;
						const Rune * pRune = CCGOPFn->GetRune( iRuneID );
						
						// Main stat
						if ( pRune->GetMainStat() == RUNE_STAT_HP_FLAT ) {
							Assert( (iSlot & 1) == 0 );
							iStatFlatTotal += pRune->GetMainStatValue();
							iStatFlatTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HP_FLAT, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatFlatTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HP_FLAT, pRune->GetRank(), 12 );
						} else if ( pRune->GetMainStat() == RUNE_STAT_HP_PERCENT ) {
							Assert( (iSlot & 1) != 0 );
							iStatPercentTotal += pRune->GetMainStatValue();
							iStatPercentTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HP_PERCENT, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatPercentTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HP_PERCENT, pRune->GetRank(), RUNE_MAX_LEVEL );
						}

						// Innate stat
						if ( pRune->GetInnateStat() == RUNE_STAT_HP_FLAT ) {
							iStatFlatTotal += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed12Odd += pRune->GetInnateStatValue();
						} else if ( pRune->GetInnateStat() == RUNE_STAT_HP_PERCENT ) {
							iStatPercentTotal += pRune->GetInnateStatValue();
							iStatPercentTotalMaxed += pRune->GetInnateStatValue();
							iStatPercentTotalMaxed12Odd += pRune->GetInnateStatValue();
						}

						// Random stats
						if ( pRune->HasRandomStat(RUNE_STAT_HP_FLAT) ) {
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_HP_FLAT );
							iStatFlatTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_HP_FLAT );
							iStatFlatTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_HP_FLAT );
						}
						if ( pRune->HasRandomStat(RUNE_STAT_HP_PERCENT) ) {
							iStatPercentTotal += pRune->GetRandomStatValue( RUNE_STAT_HP_PERCENT );
							iStatPercentTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_HP_PERCENT );
							iStatPercentTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_HP_PERCENT );
						}
					}
				} break;
			case HERO_STAT_ATTACK: {
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						RuneID iRuneID = m_arrEquippedRunes[iSlot];
						if ( iRuneID == INVALID_OFFSET )
							continue;
						const Rune * pRune = CCGOPFn->GetRune( iRuneID );

						// Main stat
						if ( pRune->GetMainStat() == RUNE_STAT_ATTACK_FLAT ) {
							Assert( (iSlot & 1) == 0 );
							iStatFlatTotal += pRune->GetMainStatValue();
							iStatFlatTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_ATTACK_FLAT, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatFlatTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_ATTACK_FLAT, pRune->GetRank(), 12 );
						} else if ( pRune->GetMainStat() == RUNE_STAT_ATTACK_PERCENT ) {
							Assert( (iSlot & 1) != 0 );
							iStatPercentTotal += pRune->GetMainStatValue();
							iStatPercentTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_ATTACK_PERCENT, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatPercentTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_ATTACK_PERCENT, pRune->GetRank(), RUNE_MAX_LEVEL );
						}

						// Innate stat
						if ( pRune->GetInnateStat() == RUNE_STAT_ATTACK_FLAT ) {
							iStatFlatTotal += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed12Odd += pRune->GetInnateStatValue();
						} else if ( pRune->GetInnateStat() == RUNE_STAT_ATTACK_PERCENT ) {
							iStatPercentTotal += pRune->GetInnateStatValue();
							iStatPercentTotalMaxed += pRune->GetInnateStatValue();
							iStatPercentTotalMaxed12Odd += pRune->GetInnateStatValue();
						}

						// Random stats
						if ( pRune->HasRandomStat(RUNE_STAT_ATTACK_FLAT) ) {
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_FLAT );
							iStatFlatTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_FLAT );
							iStatFlatTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_FLAT );
						}
						if ( pRune->HasRandomStat(RUNE_STAT_ATTACK_PERCENT) ) {
							iStatPercentTotal += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_PERCENT );
							iStatPercentTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_PERCENT );
							iStatPercentTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_ATTACK_PERCENT );
						}
					}
				} break;
			case HERO_STAT_DEFENSE: {
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						RuneID iRuneID = m_arrEquippedRunes[iSlot];
						if ( iRuneID == INVALID_OFFSET )
							continue;
						const Rune * pRune = CCGOPFn->GetRune( iRuneID );

						// Main stat
						if ( pRune->GetMainStat() == RUNE_STAT_DEFENSE_FLAT ) {
							Assert( (iSlot & 1) == 0 );
							iStatFlatTotal += pRune->GetMainStatValue();
							iStatFlatTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_DEFENSE_FLAT, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatFlatTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_DEFENSE_FLAT, pRune->GetRank(), 12 );
						} else if ( pRune->GetMainStat() == RUNE_STAT_DEFENSE_PERCENT ) {
							Assert( (iSlot & 1) != 0 );
							iStatPercentTotal += pRune->GetMainStatValue();
							iStatPercentTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_DEFENSE_PERCENT, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatPercentTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_DEFENSE_PERCENT, pRune->GetRank(), RUNE_MAX_LEVEL );
						}

						// Innate stat
						if ( pRune->GetInnateStat() == RUNE_STAT_DEFENSE_FLAT ) {
							iStatFlatTotal += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed12Odd += pRune->GetInnateStatValue();
						} else if ( pRune->GetInnateStat() == RUNE_STAT_DEFENSE_PERCENT ) {
							iStatPercentTotal += pRune->GetInnateStatValue();
							iStatPercentTotalMaxed += pRune->GetInnateStatValue();
							iStatPercentTotalMaxed12Odd += pRune->GetInnateStatValue();
						}

						// Random stats
						if ( pRune->HasRandomStat(RUNE_STAT_DEFENSE_FLAT) ) {
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_FLAT );
							iStatFlatTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_FLAT );
							iStatFlatTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_FLAT );
						}
						if ( pRune->HasRandomStat(RUNE_STAT_DEFENSE_PERCENT) ) {
							iStatPercentTotal += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_PERCENT );
							iStatPercentTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_PERCENT );
							iStatPercentTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_DEFENSE_PERCENT );
						}
					}
				} break;
			case HERO_STAT_SPEED: {
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						RuneID iRuneID = m_arrEquippedRunes[iSlot];
						if ( iRuneID == INVALID_OFFSET )
							continue;
						const Rune * pRune = CCGOPFn->GetRune( iRuneID );

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_SPEED ) {
							Assert( (iSlot & 1) != 0 );
							iStatFlatTotal += pRune->GetMainStatValue();
							iStatFlatTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_SPEED, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatFlatTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_SPEED, pRune->GetRank(), RUNE_MAX_LEVEL );
						} else if ( pRune->GetInnateStat() == RUNE_STAT_SPEED ) {
							iStatFlatTotal += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed12Odd += pRune->GetInnateStatValue();
						} else if ( pRune->HasRandomStat(RUNE_STAT_SPEED) ) {
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_SPEED );
							iStatFlatTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_SPEED );
							iStatFlatTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_SPEED );
						}
					}
				} break;
			case HERO_STAT_CRIT_RATE: {
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						RuneID iRuneID = m_arrEquippedRunes[iSlot];
						if ( iRuneID == INVALID_OFFSET )
							continue;
						const Rune * pRune = CCGOPFn->GetRune( iRuneID );

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_CRIT_RATE ) {
							Assert( (iSlot & 1) != 0 );
							iStatFlatTotal += pRune->GetMainStatValue();
							iStatFlatTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_CRIT_RATE, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatFlatTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_CRIT_RATE, pRune->GetRank(), RUNE_MAX_LEVEL );
						} else if ( pRune->GetInnateStat() == RUNE_STAT_CRIT_RATE ) {
							iStatFlatTotal += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed12Odd += pRune->GetInnateStatValue();
						} else if ( pRune->HasRandomStat(RUNE_STAT_CRIT_RATE) ) {
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_CRIT_RATE );
							iStatFlatTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_CRIT_RATE );
							iStatFlatTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_CRIT_RATE );
						}
					}
				} break;
			case HERO_STAT_CRIT_DMG: {
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						RuneID iRuneID = m_arrEquippedRunes[iSlot];
						if ( iRuneID == INVALID_OFFSET )
							continue;
						const Rune * pRune = CCGOPFn->GetRune( iRuneID );

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_CRIT_DMG ) {
							Assert( (iSlot & 1) != 0 );
							iStatFlatTotal += pRune->GetMainStatValue();
							iStatFlatTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_CRIT_DMG, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatFlatTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_CRIT_DMG, pRune->GetRank(), RUNE_MAX_LEVEL );
						} else if ( pRune->GetInnateStat() == RUNE_STAT_CRIT_DMG ) {
							iStatFlatTotal += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed12Odd += pRune->GetInnateStatValue();
						} else if ( pRune->HasRandomStat(RUNE_STAT_CRIT_DMG) ) {
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_CRIT_DMG );
							iStatFlatTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_CRIT_DMG );
							iStatFlatTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_CRIT_DMG );
						}
					}
				} break;
			case HERO_STAT_HIT: {
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						RuneID iRuneID = m_arrEquippedRunes[iSlot];
						if ( iRuneID == INVALID_OFFSET )
							continue;
						const Rune * pRune = CCGOPFn->GetRune( iRuneID );

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_HIT ) {
							Assert( (iSlot & 1) != 0 );
							iStatFlatTotal += pRune->GetMainStatValue();
							iStatFlatTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HIT, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatFlatTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_HIT, pRune->GetRank(), RUNE_MAX_LEVEL );
						} else if ( pRune->GetInnateStat() == RUNE_STAT_HIT ) {
							iStatFlatTotal += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed12Odd += pRune->GetInnateStatValue();
						} else if ( pRune->HasRandomStat(RUNE_STAT_HIT) ) {
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_HIT );
							iStatFlatTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_HIT );
							iStatFlatTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_HIT );
						}
					}
				} break;
			case HERO_STAT_RESISTANCE: {
					for( iSlot = 0; iSlot < RUNE_SLOT_COUNT; ++iSlot ) {
						RuneID iRuneID = m_arrEquippedRunes[iSlot];
						if ( iRuneID == INVALID_OFFSET )
							continue;
						const Rune * pRune = CCGOPFn->GetRune( iRuneID );

						// Main/Innate/Random stat
						if ( pRune->GetMainStat() == RUNE_STAT_RESISTANCE ) {
							Assert( (iSlot & 1) != 0 );
							iStatFlatTotal += pRune->GetMainStatValue();
							iStatFlatTotalMaxed += GameDataFn->GetRuneMainStatValue( RUNE_STAT_RESISTANCE, pRune->GetRank(), RUNE_MAX_LEVEL );
							iStatFlatTotalMaxed12Odd += GameDataFn->GetRuneMainStatValue( RUNE_STAT_RESISTANCE, pRune->GetRank(), RUNE_MAX_LEVEL );
						} else if ( pRune->GetInnateStat() == RUNE_STAT_RESISTANCE ) {
							iStatFlatTotal += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed += pRune->GetInnateStatValue();
							iStatFlatTotalMaxed12Odd += pRune->GetInnateStatValue();
						} else if ( pRune->HasRandomStat(RUNE_STAT_RESISTANCE) ) {
							iStatFlatTotal += pRune->GetRandomStatValue( RUNE_STAT_RESISTANCE );
							iStatFlatTotalMaxed += pRune->GetRandomStatValue( RUNE_STAT_RESISTANCE );
							iStatFlatTotalMaxed12Odd += pRune->GetRandomStatValue( RUNE_STAT_RESISTANCE );
						}
					}
				} break;
			default: Assert(false); break;
		}

		// Save
		m_arrEffectiveStatsPercent[iHeroStat] = iStatPercentTotal;
		m_arrEffectiveStatsFlat[iHeroStat] = iStatFlatTotal;
		m_arrEffectiveStatsPercentMaxed[iHeroStat] = iStatPercentTotalMaxed;
		m_arrEffectiveStatsFlatMaxed[iHeroStat] = iStatFlatTotalMaxed;
		m_arrEffectiveStatsPercentMaxed12Odd[iHeroStat] = iStatPercentTotalMaxed12Odd;
		m_arrEffectiveStatsFlatMaxed12Odd[iHeroStat] = iStatFlatTotalMaxed12Odd;
    }

	// Apply Set Bonuses
	for( UInt i = 0; i < m_iActiveSetsCount; ++i ) {
		RuneSet iRuneSet = m_arrActiveSets[i];
		switch( iRuneSet ) {
			case RUNE_SET_BLESSING:
				m_arrEffectiveStatsPercent[HERO_STAT_HP] += 15;
				m_arrEffectiveStatsPercentMaxed[HERO_STAT_HP] += 15;
				m_arrEffectiveStatsPercentMaxed12Odd[HERO_STAT_HP] += 15;
				break;
			case RUNE_SET_ATTACK:
				m_arrEffectiveStatsPercent[HERO_STAT_ATTACK] += 35;
				m_arrEffectiveStatsPercentMaxed[HERO_STAT_ATTACK] += 35;
				m_arrEffectiveStatsPercentMaxed12Odd[HERO_STAT_ATTACK] += 35;
				break;
			case RUNE_SET_DEFENSE:
				m_arrEffectiveStatsPercent[HERO_STAT_DEFENSE] += 15;
				m_arrEffectiveStatsPercentMaxed[HERO_STAT_DEFENSE] += 15;
				m_arrEffectiveStatsPercentMaxed12Odd[HERO_STAT_DEFENSE] += 15;
				break;
			case RUNE_SET_AGILE:
				m_arrEffectiveStatsPercent[HERO_STAT_SPEED] += 25;
				m_arrEffectiveStatsPercentMaxed[HERO_STAT_SPEED] += 25;
				m_arrEffectiveStatsPercentMaxed12Odd[HERO_STAT_SPEED] += 25;
				break;
			case RUNE_SET_WILD:
				m_arrEffectiveStatsFlat[HERO_STAT_CRIT_RATE] += 12;
				m_arrEffectiveStatsFlatMaxed[HERO_STAT_CRIT_RATE] += 12;
				m_arrEffectiveStatsFlatMaxed12Odd[HERO_STAT_CRIT_RATE] += 12;
				break;
			case RUNE_SET_DESTRUCTION:
				m_arrEffectiveStatsFlat[HERO_STAT_CRIT_DMG] += 40;
				m_arrEffectiveStatsFlatMaxed[HERO_STAT_CRIT_DMG] += 40;
				m_arrEffectiveStatsFlatMaxed12Odd[HERO_STAT_CRIT_DMG] += 40;
				if ( m_bHasFull6Set ) {
					m_arrEffectiveStatsPercent[HERO_STAT_ATTACK] += 15;
					m_arrEffectiveStatsPercentMaxed[HERO_STAT_ATTACK] += 15;
					m_arrEffectiveStatsPercentMaxed12Odd[HERO_STAT_ATTACK] += 15;
				}
				break;
			case RUNE_SET_FOCUS:
				m_arrEffectiveStatsFlat[HERO_STAT_HIT] += 20;
				m_arrEffectiveStatsFlatMaxed[HERO_STAT_HIT] += 20;
				m_arrEffectiveStatsFlatMaxed12Odd[HERO_STAT_HIT] += 20;
				break;
			case RUNE_SET_STALWART:
				m_arrEffectiveStatsFlat[HERO_STAT_RESISTANCE] += 20;
				m_arrEffectiveStatsFlatMaxed[HERO_STAT_RESISTANCE] += 20;
				m_arrEffectiveStatsFlatMaxed12Odd[HERO_STAT_RESISTANCE] += 20;
				break;
			case RUNE_SET_DESPERATION:
			case RUNE_SET_DRAIN:
			case RUNE_SET_FRENZY:
			case RUNE_SET_BERSERK:
			case RUNE_SET_COUNTER:
			case RUNE_SET_GUARD:
			case RUNE_SET_IMMUNITY:
			case RUNE_SET_RAVAGE:
			case RUNE_SET_PRAYER:   // Team bonuses are not taken into account !
			case RUNE_SET_CONFLICT:
			case RUNE_SET_UNITY:
			case RUNE_SET_HIT:
			case RUNE_SET_FORTITUDE: break;
			default: Assert(false); break;
		}
	}
}

Void GearSet::_ComputeScores()
{
    /////////////////////////////////////
    // Need some math infos here ....
}

