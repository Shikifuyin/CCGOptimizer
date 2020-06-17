/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/GameData.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
/////////////////////////////////////////////////////////////////////////////////
// Description : Game-Specific Data
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : Requires more investigation ...
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "GameData.h"

/////////////////////////////////////////////////////////////////////////////////
// GameData implementation
GameData::GameData():
    m_mapHeroData()
{
    m_mapHeroData.Create();
}
GameData::~GameData()
{
    m_mapHeroData.Destroy();
}

Void GameData::ImportFromXML()
{
    UInt i, j, k, l;
    GChar strNameBuffer[XML_NAME_SIZE];

    // Rune Data
    XMLDocument * pRuneDocument = XMLFn->CreateDocument( GAMEDATA_FILE_RUNES );
    Assert( pRuneDocument != NULL );
    Assert( StringFn->Cmp(pRuneDocument->GetTagName(), TEXT("gamedata_runes")) == 0 );

        // Rune Set Sizes
    XMLNode * pNode = pRuneDocument->GetChildByTag( TEXT("rune_set_sizes"), 0 );
    Assert( pNode != NULL );
    for( i = 0; i < RUNE_SET_COUNT; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("rune_set_%d"), i );
        XMLAttribute * pAttribute = pNode->GetAttribute( strNameBuffer );
        Assert( pAttribute != NULL );

        m_arrRuneSetSizes[i] = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );
    }

        // Main Stats Allowed
    pNode = pRuneDocument->GetChildByTag( TEXT("main_stats_allowed"), 0 );
    Assert( pNode != NULL );
    for( i = 0; i < RUNE_STAT_COUNT; ++i ) {
        const GChar * strStatName = GetRuneStatName( (RuneStat)i );
        XMLNode * pSubNode = pNode->GetChildByTag( strStatName, 0 );
        Assert( pSubNode != NULL );

        for( j = 0; j < RUNE_SLOT_COUNT; ++j ) {
            StringFn->Format( strNameBuffer, TEXT("rune_slot_%d"), j );
            XMLAttribute * pAttribute = pSubNode->GetAttribute( strNameBuffer );
            Assert( pAttribute != NULL );

            m_arrRuneMainStatsAllowed[i * RUNE_SLOT_COUNT + j] = ( StringFn->Cmp(pAttribute->GetValue(), TEXT("true")) == 0 );
        }
    }

        // Main Stats Values
    pNode = pRuneDocument->GetChildByTag( TEXT("main_stats_values"), 0 );
    Assert( pNode != NULL );
    for( i = 0; i < RUNE_STAT_COUNT; ++i ) {
        const GChar * strStatName = GetRuneStatName( (RuneStat)i );
        XMLNode * pSubNode = pNode->GetChildByTag( strStatName, 0 );
        Assert( pSubNode != NULL );

        for( j = 0; j < RUNE_MAX_LEVEL; ++j ) {
            StringFn->Format( strNameBuffer, TEXT("rune_level_%d"), j );
            XMLNode * pSubSubNode = pSubNode->GetChildByTag( strNameBuffer, 0 );
            Assert( pSubSubNode != NULL );

            for( k = 0; k < RUNE_RANK_COUNT; ++k ) {
                StringFn->Format( strNameBuffer, TEXT("rune_rank_%d"), k );
                XMLAttribute * pAttribute = pSubSubNode->GetAttribute( strNameBuffer );
                Assert( pAttribute != NULL );

                m_arrRuneMainStatsValues[i * (RUNE_RANK_COUNT * RUNE_MAX_LEVEL) + k * RUNE_MAX_LEVEL + j] = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );
            }
        }
    }

        // SubStats Roll Ranges
    pNode = pRuneDocument->GetChildByTag( TEXT("sub_stats_roll_ranges"), 0 );
    Assert( pNode != NULL );
    for( i = 0; i < RUNE_STAT_COUNT; ++i ) {
        const GChar * strStatName = GetRuneStatName( (RuneStat)i );
        XMLNode * pSubNode = pNode->GetChildByTag( strStatName, 0 );
        Assert( pSubNode != NULL );

        for( j = 0; j < RUNE_RANK_COUNT; ++j ) {
            StringFn->Format( strNameBuffer, TEXT("rune_rank_%d"), j );
            XMLNode * pSubSubNode = pSubNode->GetChildByTag( strNameBuffer, 0 );
            Assert( pSubSubNode != NULL );

            XMLAttribute * pAttribute = pSubSubNode->GetAttribute( TEXT("min") );
            Assert( pAttribute != NULL );
            m_arrRuneSubStatsMinRoll[i * RUNE_RANK_COUNT + j] = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );

            pAttribute = pSubSubNode->GetAttribute( TEXT("max") );
            Assert( pAttribute != NULL );
            m_arrRuneSubStatsMaxRoll[i * RUNE_RANK_COUNT + j] = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );
        }
    }

    // Done with Rune Data
    XMLFn->DestroyDocument( pRuneDocument );
    pRuneDocument = NULL;

    // Hero Data
    XMLDocument * pHeroDocument = XMLFn->CreateDocument( GAMEDATA_FILE_HEROES );
    Assert( pHeroDocument != NULL );
    Assert( StringFn->Cmp(pHeroDocument->GetTagName(), TEXT("gamedata_heroes")) == 0 );

        // Hero Rank Max Level
    pNode = pHeroDocument->GetChildByTag( TEXT("sub_stats_roll_ranges"), 0 );
    Assert( pNode != NULL );
    for( i = 0; i < HERO_RANK_COUNT; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("hero_rank_%d"), i );
        XMLAttribute * pAttribute = pNode->GetAttribute( strNameBuffer );
        Assert( pAttribute != NULL );

        m_arrHeroRankMaxLevel[i] = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );
    }

        // Hero Sanctify Bonus
    pNode = pHeroDocument->GetChildByTag( TEXT("hero_sanctify_bonus"), 0 );
    Assert( pNode != NULL );
    for( i = 0; i < HERO_SANCTIFY_COUNT; ++i ) {
        StringFn->Format( strNameBuffer, TEXT("hero_sanctify_%d"), i );
        XMLAttribute * pAttribute = pNode->GetAttribute( strNameBuffer );
        Assert( pAttribute != NULL );

        m_arrHeroSanctifyBonus[i] = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );
    }

        // Hero Data
    UInt iHeroDataCount = pHeroDocument->GetChildCount() - 2;
    for( UInt iHero = 0; iHero < iHeroDataCount; ++iHero ) {
        pNode = pHeroDocument->GetChildNByTag( TEXT("hero_data"), iHero );
        Assert( pNode != NULL );

        HeroData hHeroData;

        // Get Name
        XMLAttribute * pAttribute = pNode->GetAttribute( TEXT("name") );
        Assert( pAttribute != NULL );

        StringFn->NCopy( hHeroData.strName, pAttribute->GetValue(), GAMEDATA_NAMES_MAX_LENGTH - 1 );

        // Get Faction
        pAttribute = pNode->GetAttribute( TEXT("faction") );
        Assert( pAttribute != NULL );

        hHeroData.iFaction = (HeroFaction)( StringFn->ToUInt(pAttribute->GetValue()) );

        // Get Natural Rank
        pAttribute = pNode->GetAttribute( TEXT("natural_rank") );
        Assert( pAttribute != NULL );

        hHeroData.iNaturalRank = (HeroRank)( StringFn->ToUInt(pAttribute->GetValue()) );

        // Base Stats
        XMLNode * pStatNode = pNode->GetChildByTag( TEXT("base_stats"), 0 );
        Assert( pStatNode != NULL );
        for( j = hHeroData.iNaturalRank; j < HERO_RANK_COUNT; ++j ) {
            StringFn->Format( strNameBuffer, TEXT("hero_rank_%d"), j );
            XMLNode * pSubNode = pStatNode->GetChildByTag( strNameBuffer, 0 );
            Assert( pSubNode != NULL );

            UInt iStartLevel = 1;
            if ( j > (UInt)(hHeroData.iNaturalRank) )
                iStartLevel = GetHeroRankMaxLevel( (HeroRank)(j-1) );
            UInt iMaxLevel = GetHeroRankMaxLevel( (HeroRank)j );

            for ( k = iStartLevel; k <= iMaxLevel; ++k ) {
                StringFn->Format( strNameBuffer, TEXT( "hero_level_%d" ), k );
                XMLNode * pSubSubNode = pSubNode->GetChildByTag( strNameBuffer, 0 );
                Assert( pSubSubNode != NULL );

                for( l = 0; l < HERO_STAT_COUNT; ++l ) {
                    const GChar * strStatName = GetHeroStatName( (HeroStat)l );
                    pAttribute = pSubSubNode->GetAttribute( strStatName );
                    Assert( pAttribute != NULL );

                    hHeroData.arrBaseStats[ l * (HERO_RANK_COUNT * HERO_MAX_LEVEL) + j * HERO_MAX_LEVEL + k ] = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );
                }
            }
        }

        // Base Stats Evolved
        pStatNode = pNode->GetChildByTag( TEXT("base_stats_evolved"), 0 );
        Assert( pStatNode != NULL );
        for( j = hHeroData.iNaturalRank; j < HERO_RANK_COUNT; ++j ) {
            StringFn->Format( strNameBuffer, TEXT("hero_rank_%d"), j );
            XMLNode * pSubNode = pStatNode->GetChildByTag( strNameBuffer, 0 );
            Assert( pSubNode != NULL );

            UInt iStartLevel = 1;
            if ( j > (UInt)(hHeroData.iNaturalRank) )
                iStartLevel = GetHeroRankMaxLevel( (HeroRank)(j-1) );
            UInt iMaxLevel = GetHeroRankMaxLevel( (HeroRank)j );

            for ( k = iStartLevel; k <= iMaxLevel; ++k ) {
                StringFn->Format( strNameBuffer, TEXT( "hero_level_%d" ), k );
                XMLNode * pSubSubNode = pSubNode->GetChildByTag( strNameBuffer, 0 );
                Assert( pSubSubNode != NULL );

                for( l = 0; l < HERO_STAT_COUNT; ++l ) {
                    const GChar * strStatName = GetHeroStatName( (HeroStat)l );
                    pAttribute = pSubSubNode->GetAttribute( strStatName );
                    Assert( pAttribute != NULL );

                    hHeroData.arrBaseStatsEvolved[ l * (HERO_RANK_COUNT * HERO_MAX_LEVEL) + j * HERO_MAX_LEVEL + k ] = (UInt)( StringFn->ToUInt(pAttribute->GetValue()) );
                }
            }
        }

        // Done
        m_mapHeroData.Insert( hHeroData.strName, hHeroData );
    }
}


