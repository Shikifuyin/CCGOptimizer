<?php
/////////////////////////////////////////////////////////////////////////////////
// File : Source/PHP/BackEnd/HeroInventory.php
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
/////////////////////////////////////////////////////////////////////////////////
// Description : Hero Inventory Manager
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

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

    // Search Queries
define( "HERO_QUERY_NAME",      0 ); // value = hero name
define( "HERO_QUERY_FACTION",   1 ); // value = faction id
define( "HERO_QUERY_RANK",      2 ); // value = rank id
define( "HERO_QUERY_LEVEL",     3 ); // value = level
define( "HERO_QUERY_EVOLVED",   4 ); // value = is evolved
define( "HERO_QUERY_GEARSET",   5 ); // value = name to match
define( "HERO_QUERY_RUNES",     6 ); // value = array( "and" | "or", rune ids )

    // Sorting Rules
define( "HERO_SORTING_ID",          "_HeroComparator_ID" );
define( "HERO_SORTING_NAME",        "_HeroComparator_Name" );
define( "HERO_SORTING_FACTION",     "_HeroComparator_Faction" );
define( "HERO_SORTING_LEVEL",       "_HeroComparator_Level" );
define( "HERO_SORTING_EVOLVED",     "_HeroComparator_Evolved" );
define( "HERO_SORTING_HP",          "_HeroComparator_HP" );
define( "HERO_SORTING_ATT",         "_HeroComparator_ATT" );
define( "HERO_SORTING_DEF",         "_HeroComparator_DEF" );
define( "HERO_SORTING_SPD",         "_HeroComparator_SPD" );
define( "HERO_SORTING_CRITRATE",    "_HeroComparator_CritRate" );
define( "HERO_SORTING_CRITDMG",     "_HeroComparator_CritDmg" );
define( "HERO_SORTING_HIT",         "_HeroComparator_Hit" );
define( "HERO_SORTING_RES",         "_HeroComparator_Res" );
define( "HERO_SORTING_GEARSET",     "_HeroComparator_GearSet" );

/////////////////////////////////////////////////////////////////////////////////
// The HeroInventory class
class HeroInventory
{
    // Singleton interface
    public static function &GetSingleton():HeroInventory {
        if ( HeroInventory::$m_hInstance == NULL )
            HeroInventory::$m_hInstance = new HeroInventory();
        return HeroInventory::$m_hInstance;
    }
    protected static $m_hInstance;

    // Constructor / Destructor
    public function __construct()
    {
        // HeroID Allocator
        $this->m_iNextFreeHeroID = 1;

        // Hero Inventory
        $this->m_arrHeroInventory = array();

        // Sorted View
        $this->SortHeroView( HERO_SORTING_ID );
	}
	public function __destruct()
    {
		// nothing to do
    }

    // Import/Export
    public function ImportFromXML( XMLElement & $hXMLElement ):void
    {
        assert( $hXMLElement->GetTagName() == "inventory_heroes" );

        $this->m_arrHeroInventory = array();
        $hHeroNodeList = $hXMLElement->GetElementsByTag( "hero" );
        $iCount = $hHeroNodeList->GetCount();
        $iBiggestID = 0;
        for( $i = 0; $i < $iCount; ++$i ) {
            $hHeroElement = $hHeroNodeList->GetNode( $i );
            $hHero = new Hero();
            $hHero->ImportFromXML( $hHeroElement );
            $this->m_arrHeroInventory[$hHero->GetID()] = $hHero;
            if ( $hHero->GetID() > $iBiggestID )
                $iBiggestID = $hHero->GetID();
        }
        $this->m_iNextFreeHeroID = $iBiggestID + 1;
    }
    public function ExportToXML( XMLDocument & $hRootDocument, XMLElement & $hXMLElement ):void
    {
        $hXMLElement = $hRootDocument->CreateElement( "inventory_heroes" );

        foreach( $this->m_arrHeroInventory as &$hHero ) {
            $hHeroElement = NULL;
            $hHero->ExportToXML( $hRootDocument, $hHeroElement );
            $hXMLElement->AppendChild( $hHeroElement );
        }
    }

    // Hero Inventory
    public function GetHeroCount():int {
        return count( $this->m_arrHeroInventory );
    }
    public function &GetHero( int $iHeroID ):Hero {
        assert( array_key_exists($iHeroID, $this->m_arrHeroInventory) );
        return $this->m_arrHeroInventory[$iHeroID];
    }

    // Selected GearSets
    public function UnselectAllGearSets():void {
        foreach( $this->m_arrHeroInventory as $iHeroID => &$hHero ) {
            $hHero->UnselectGearSet();
        }
    }
    
    // Search Engine
    public function FilterSearch( array $arrQueries ):array
    {
        $arrHeroCollection = array();

        // Name Query
        $strQueryName = NULL;
        if ( array_key_exists(HERO_QUERY_NAME, $arrQueries) )
            $strQueryName = $arrQueries[HERO_QUERY_NAME];

        // Faction Query
        $iQueryFaction = NULL;
        if ( array_key_exists(HERO_QUERY_FACTION, $arrQueries) )
            $iQueryFaction = $arrQueries[HERO_QUERY_FACTION];

        // Rank Query
        $iQueryRank = NULL;
        if ( array_key_exists(HERO_QUERY_RANK, $arrQueries) )
            $iQueryRank = $arrQueries[HERO_QUERY_RANK];

        // Level Query
        $iQueryLevel = NULL;
        if ( array_key_exists(HERO_QUERY_LEVEL, $arrQueries) )
            $iQueryLevel = $arrQueries[HERO_QUERY_LEVEL];

        // Evolved Query
        $bQueryEvolved = NULL;
        if ( array_key_exists(HERO_QUERY_EVOLVED, $arrQueries) )
            $bQueryEvolved = $arrQueries[HERO_QUERY_EVOLVED];

        // GearSet Query
        $strQueryGearSet = NULL;
        if ( array_key_exists(HERO_QUERY_GEARSET, $arrQueries) )
            $strQueryGearSet = $arrQueries[HERO_QUERY_GEARSET];
        
        // Runes Query
        $arrQueryRunes = NULL;
        if ( array_key_exists(HERO_QUERY_RUNES, $arrQueries) )
            $arrQueryRunes = $arrQueries[HERO_QUERY_RUNES];

        // Search
        foreach( $this->m_arrHeroInventory as $iHeroID => &$hHero ) {
            // Filter Name
            if ( $strQueryName != NULL ) {
                if ( $hHero->GetName() != $strQueryName )
                    continue;
            }
            // Filter Faction
            if ( $iQueryFaction != NULL ) {
                if ( $hHero->GetFaction() != $iQueryFaction )
                    continue;
            }
            // Filter Rank
            if ( $iQueryRank != NULL ) {
                if ( $hHero->GetRank() < $iQueryRank )
                    continue;
            }
            // Filter Level
            if ( $iQueryLevel != NULL ) {
                if ( $hHero->GetLevel() < $iQueryLevel )
                    continue;
            }
            // Filter Evolved
            if ( $bQueryEvolved != NULL ) {
                if ( $hHero->IsEvolved() != $bQueryEvolved )
                    continue;
            }
            // Filter GearSet
            if ( $strQueryGearSet != NULL ) {
                $bFilterOut = true;
                $iGearSetCount = $hHero->GetGearSetCount();
                for( $i = 0; $i < $iGearSetCount; ++$i ) {
                    $strGearSetName = $hHero->GetGearSet( $i );
                    if ( strpos($strGearSetName, $strQueryGearSet) !== false ) {
                        $bFilterOut = false;
                        break;
                    }
                }
                if ( $bFilterOut )
                    continue;
            }
            // Filter Runes
            if ( $arrQueryRunes != NULL ) {
                $bFilterOut = false;
                $iGearSetCount = $hHero->GetGearSetCount();
                $hGearSetInventory = &GearSetInventory::GetSingleton();
                $bAndElseOr = ( $arrQueryRunes[0] == "and" );
                if ( $bAndElseOr ) { // match all specified runes
                    $bFilterOut = false;
                    $iCount = count( $arrQueryRunes );
                    for( $i = 1; $i < $iCount; ++$i ) {
                        $bFound = false;
                        for( $iGearSet = 0; $iGearSet < $iGearSetCount; ++$iGearSet ) {
                            $strGearSetName = $hHero->GetGearSet( $iGearSet );
                            $hGearSet = &$hGearSetInventory->GetGearSet( $strGearSetName );
                            if ( $hGearSet->HasEquippedRune($arrQueryRunes[$i]) ) {
                                $bFound = true;
                                break;
                            }
                        }
                        if ( !$bFound ) {
                            $bFilterOut = true;
                            break;
                        }
                    }
                } else { // match at least one specified rune
                    $bFilterOut = true;
                    $iCount = count( $arrQueryRunes );
                    for( $i = 1; $i < $iCount; ++$i ) {
                        $bFound = false;
                        for( $iGearSet = 0; $iGearSet < $iGearSetCount; ++$iGearSet ) {
                            $strGearSetName = $hHero->GetGearSet( $iGearSet );
                            $hGearSet = &$hGearSetInventory->GetGearSet( $strGearSetName );
                            if ( $hGearSet->HasEquippedRune($arrQueryRunes[$i]) ) {
                                $bFound = true;
                                break;
                            }
                        }
                        if ( $bFound ) {
                            $bFilterOut = false;
                            break;
                        }
                    }
                }
                if ( $bFilterOut )
                    continue;
            }

            // Passed all filters, collect
            array_push( $arrHeroCollection, $iHeroID );
        }

        return $arrHeroCollection;
    }

    // Sorted View
    public function GetHeroViewEntry( int $iIndex ):int {
        assert( $iIndex < count($this->m_arrSortedView) );
        return $this->m_arrSortedView[$iIndex];
    }

    public function SortHeroView( $strSortingRule ):void
    {
        $this->m_arrSortedView = array();
        $hHeap = new Heap( "HeroInventory::$strSortingRule", $this );
        foreach( $this->m_arrHeroInventory as &$hHero ) {
            $hHeap->Merge( $hHero->GetID() );
        }
        while( !$hHeap->IsEmpty() ) {
            $iHeroID = NULL;
            $hHeap->Extract( $iHeroID );
            array_push( $this->m_arrSortedView, $iHeroID );
        }
    }

    // Internals
    public function _CreateHero( string $strName, int $iRank, int $iLevel, bool $bEvolved, int $iSanctify ):int {
        $iHeroID = $this->_AllocateHeroID();
        $this->m_arrHeroInventory[$iHeroID] = new Hero(
            $iHeroID, $strName, $iRank, $iLevel, $bEvolved, $iSanctify
        );
        return $iHeroID;
    }
    public function _DestroyHero( int $iHeroID ):void {
        assert( array_key_exists($iHeroID, $this->m_arrHeroInventory) );
        unset( $this->m_arrHeroInventory[$iHeroID] );
    }
    public function _DestroyAllHeroes():void {
        $this->m_iNextFreeHeroID = 1;
        $this->m_arrHeroInventory = array();
    }

    public function _DetachAll():void {
        foreach( $this->m_arrHeroInventory as $iHeroID => &$hHero ) {
            $hHero->_DetachAllGearSets();
        }
    }

    // Helpers
    private function _AllocateHeroID():int {
        assert( $this->m_iNextFreeHeroID < PHP_INT_MAX );
        $iHeroID = $this->m_iNextFreeHeroID;
        ++$this->m_iNextFreeHeroID;
        return $iHeroID;
    }

    public static function _HeroComparator_ID( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        if ( $iLeftHeroID < $iRightHeroID )
            return +1;
        if ( $iLeftHeroID > $iRightHeroID )
            return -1;
        return 0;
    }
    public static function _HeroComparator_Name( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        return -( strcasecmp($hLeftHero->GetName(), $hRightHero->GetName()) );
    }
    public static function _HeroComparator_Faction( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hLeftHero->GetFaction();
        $iRight = $hRightHero->GetFaction();
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_Level( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hLeftHero->GetLevel();
        $iRight = $hRightHero->GetLevel();
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_Evolved( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hLeftHero->IsEvolved() ? 1 : 0;
        $iRight = $hRightHero->IsEvolved() ? 1 : 0;
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_HP( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hGameData = &GameData::GetSingleton();
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_HP, $hLeftHero->IsEvolved() );
        $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_HP, $hRightHero->IsEvolved() );
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_ATT( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hGameData = &GameData::GetSingleton();
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_ATTACK, $hLeftHero->IsEvolved() );
        $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_ATTACK, $hRightHero->IsEvolved() );
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_DEF( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hGameData = &GameData::GetSingleton();
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_DEFENSE, $hLeftHero->IsEvolved() );
        $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_DEFENSE, $hRightHero->IsEvolved() );
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_SPD( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hGameData = &GameData::GetSingleton();
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_SPEED, $hLeftHero->IsEvolved() );
        $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_SPEED, $hRightHero->IsEvolved() );
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_CritRate( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hGameData = &GameData::GetSingleton();
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_CRIT_RATE, $hLeftHero->IsEvolved() );
        $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_CRIT_RATE, $hRightHero->IsEvolved() );
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_CritDmg( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hGameData = &GameData::GetSingleton();
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_CRIT_DMG, $hLeftHero->IsEvolved() );
        $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_CRIT_DMG, $hRightHero->IsEvolved() );
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_Hit( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hGameData = &GameData::GetSingleton();
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_HIT, $hLeftHero->IsEvolved() );
        $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_HIT, $hRightHero->IsEvolved() );
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_Res( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hGameData = &GameData::GetSingleton();
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        $iLeft = $hGameData->GetHeroBaseStat( $hLeftHero->GetName(), $hLeftHero->GetRank(), $hLeftHero->GetLevel(), HERO_STAT_RESISTANCE, $hLeftHero->IsEvolved() );
        $iRight = $hGameData->GetHeroBaseStat( $hRightHero->GetName(), $hRightHero->GetRank(), $hRightHero->GetLevel(), HERO_STAT_RESISTANCE, $hRightHero->IsEvolved() );
        if ( $iLeft < $iRight )
            return +1;
        if ( $iLeft > $iRight )
            return -1;
        return 0;
    }
    public static function _HeroComparator_GearSet( int & $iLeftHeroID, int & $iRightHeroID, HeroInventory & $hHeroInventory ):int {
        $hLeftHero = &$hHeroInventory->GetHero( $iLeftHeroID );
        $hRightHero = &$hHeroInventory->GetHero( $iRightHeroID );
        return -( strcasecmp($hLeftHero->GetSelectedGearSet(), $hRightHero->GetSelectedGearSet()) );
    }

    // Members
    private $m_iNextFreeHeroID;

    private $m_arrHeroInventory;

    private $m_arrSortedView;
}

?>