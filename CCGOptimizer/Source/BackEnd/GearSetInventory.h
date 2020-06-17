<?php
/////////////////////////////////////////////////////////////////////////////////
// File : Source/PHP/BackEnd/GearSetInventory.php
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
/////////////////////////////////////////////////////////////////////////////////
// Description : GearSet Inventory Manager
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

    // GearSet Queries
define( "GEARSET_QUERY_NAME",       0 ); // value = name to match
define( "GEARSET_QUERY_HEROES",     1 ); // value = array( "and" | "or", hero ids )
define( "GEARSET_QUERY_RUNES",      2 ); // value = array( "and" | "or", rune ids )
define( "GEARSET_QUERY_STATE",      3 ); // value = "complete" | "partial" | "empty"
define( "GEARSET_QUERY_EFFICIENCY", 4 ); // value = efficiency score threshold
define( "GEARSET_QUERY_DAMAGE",     5 ); // value = damage score threshold
define( "GEARSET_QUERY_TANKING",    6 ); // value = tanking score threshold

/////////////////////////////////////////////////////////////////////////////////
// The GearSetInventory class
class GearSetInventory
{
    // Singleton interface
    public static function &GetSingleton():GearSetInventory {
        if ( GearSetInventory::$m_hInstance == NULL )
            GearSetInventory::$m_hInstance = new GearSetInventory();
        return GearSetInventory::$m_hInstance;
    }
    protected static $m_hInstance;

    // Constructor / Destructor
    public function __construct()
    {
        // GearSet Inventory
        $this->m_arrGearSetInventory = array();
	}
	public function __destruct()
    {
		// nothing to do
    }

    // Import/Export
    public function ImportFromXML( XMLElement & $hXMLElement ):void {
        assert( $hXMLElement->GetTagName() == "inventory_gearsets" );

        $this->m_arrGearSetInventory = array();
        $hGearSetNodeList = $hXMLElement->GetElementsByTag( "gearset" );
        $iCount = $hGearSetNodeList->GetCount();
        for( $i = 0; $i < $iCount; ++$i ) {
            $hGearSetElement = $hGearSetNodeList->GetNode( $i );
            $hGearSet = new GearSet();
            $hGearSet->ImportFromXML( $hGearSetElement );
            $this->m_arrGearSetInventory[$hGearSet->GetName()] = $hGearSet;
        }
    }
    public function ExportToXML( XMLDocument & $hRootDocument, XMLElement & $hXMLElement ):void {
        $hXMLElement = $hRootDocument->CreateElement( "inventory_gearsets" );

        foreach( $this->m_arrGearSetInventory as &$hGearSet ) {
            $hGearSetElement = NULL;
            $hGearSet->ExportToXML( $hRootDocument, $hGearSetElement );
            $hXMLElement->AppendChild( $hGearSetElement );
        }
    }

    // GearSet Inventory
    public function GetGearSetCount():int {
        return count( $this->m_arrGearSetInventory );
    }
    public function &GetGearSet( string $strGearSetName ):GearSet {
        assert( array_key_exists($strGearSetName, $this->m_arrGearSetInventory) );
        return $this->m_arrGearSetInventory[$strGearSetName];
    }

    // Search Engine
    public function FilterSearch( array $arrQueries ):array {
        $arrGearSetCollection = array();

        // Name Query
        $strQueryName = NULL;
        if ( array_key_exists(GEARSET_QUERY_NAME, $arrQueries) )
            $strQueryName = $arrQueries[GEARSET_QUERY_NAME];

        // Heroes Query
        $arrQueryHeroes = NULL;
        if ( array_key_exists(GEARSET_QUERY_HEROES, $arrQueries) )
            $arrQueryHeroes = $arrQueries[GEARSET_QUERY_HEROES];

        // Runes Query
        $arrQueryRunes = NULL;
        if ( array_key_exists(GEARSET_QUERY_RUNES, $arrQueries) )
            $arrQueryRunes = $arrQueries[GEARSET_QUERY_RUNES];

        // State Query
        $strQueryState = NULL;
        if ( array_key_exists(GEARSET_QUERY_STATE, $arrQueries) )
            $strQueryState = $arrQueries[GEARSET_QUERY_STATE];

        // Efficiency Query
        $fQueryEfficiency = NULL;
        if ( array_key_exists(GEARSET_QUERY_EFFICIENCY, $arrQueries) )
            $fQueryEfficiency = $arrQueries[GEARSET_QUERY_EFFICIENCY];

        // Damage Query
        $fQueryDamage = NULL;
        if ( array_key_exists(GEARSET_QUERY_DAMAGE, $arrQueries) )
            $fQueryDamage = $arrQueries[GEARSET_QUERY_DAMAGE];

        // Tanking Query
        $fQueryTanking = NULL;
        if ( array_key_exists(GEARSET_QUERY_TANKING, $arrQueries) )
            $fQueryTanking = $arrQueries[GEARSET_QUERY_TANKING];

        // Search
        foreach( $this->m_arrGearSetInventory as $strGearSetName => &$hGearSet ) {
            // Filter Name
            if ( $strQueryName != NULL ) {
                if ( strpos($strGearSetName, $strQueryName) === false )
                    continue;
            }
            // Filter Heroes
            if ( $arrQueryHeroes != NULL ) {
                $bFilterOut = false;
                $bAndElseOr = ( $arrQueryHeroes[0] == "and" );
                if ( $bAndElseOr ) { // match all specified heroes
                    $bFilterOut = false;
                    $iCount = count( $arrQueryHeroes );
                    for( $i = 1; $i < $iCount; ++$i ) {
                        $iQueryHeroID = $arrQueryHeroes[$i];
                        if ( !$hGearSet->HasAttachedHero($iQueryHeroID) ) {
                            $bFilterOut = true;
                            break;
                        }
                    }
                } else { // match at least one specified hero
                    $bFilterOut = true;
                    $iCount = count( $arrQueryHeroes );
                    for( $i = 1; $i < $iCount; ++$i ) {
                        $iQueryHeroID = $arrQueryHeroes[$i];
                        if ( $hGearSet->HasAttachedHero($iQueryHeroID) ) {
                            $bFilterOut = false;
                            break;
                        }
                    }
                }
                if ( $bFilterOut )
                    continue;
            }
            // Filter Runes
            if ( $arrQueryRunes != NULL ) {
                $bFilterOut = false;
                $bAndElseOr = ( $arrQueryRunes[0] == "and" );
                if ( $bAndElseOr ) { // match all specified runes
                    $bFilterOut = false;
                    $iCount = count( $arrQueryRunes );
                    for( $i = 1; $i < $iCount; ++$i ) {
                        if ( !$hGearSet->HasEquippedRune($arrQueryRunes[$i]) ) {
                            $bFilterOut = true;
                            break;
                        }
                    }
                } else { // match at least one specified rune
                    $bFilterOut = true;
                    $iCount = count( $arrQueryRunes );
                    for( $i = 1; $i < $iCount; ++$i ) {
                        if ( $hGearSet->HasEquippedRune($arrQueryRunes[$i]) ) {
                            $bFilterOut = false;
                            break;
                        }
                    }
                }
                if ( $bFilterOut )
                    continue;
            }
            // Filter State
            if ( $strQueryState != NULL ) {
                $bComplete = true;
                $bEmpty = true;
                for( $iSlot = 0; $iSlot < RUNE_SLOT_COUNT; ++$iSlot ) {
                    if ( $hGearSet->GetRuneID($iSlot) == NULL )
                        $bComplete = false;
                    else
                        $bEmpty = false;
                }
                $bFilterOut = false;
                switch( $strQueryState ) {
                    case "complete": if ( !$bComplete ) $bFilterOut = true; break;
                    case "empty":    if ( !$bEmpty ) $bFilterOut = true; break;
                    case "partial":  if ( $bComplete || $bEmpty ) $bFilterOut = true; break;
                    default: assert( false ); break;
                }
                if ( $bFilterOut )
                    continue;
            }
            // Filter Efficiency
            if ( $fQueryEfficiency != NULL ) {
                if ( $hGearSet->GetScoreEfficiency() < $fQueryEfficiency )
                    continue;
            }
            // Filter Damage
            if ( $fQueryDamage != NULL ) {
                if ( $hGearSet->GetScoreDamage() < $fQueryDamage )
                    continue;
            }
            // Filter Tanking
            if ( $fQueryTanking != NULL ) {
                if ( $hGearSet->GetScoreTanking() < $fQueryTanking )
                    continue;
            }

            // Passed all filters, collect
            array_push( $arrGearSetCollection, $strGearSetName );
        }

        return $arrGearSetCollection;
    }

    // Internals
    public function _CreateGearSet( string $strGearSetName ):bool {
        if ( array_key_exists($strGearSetName, $this->m_arrGearSetInventory) )
            return false;
        $this->m_arrGearSetInventory[$strGearSetName] = new GearSet( $strGearSetName );
        return true;
    }
    public function _DestroyGearSet( string $strGearSetName ):void {
        assert( array_key_exists($strGearSetName, $this->m_arrGearSetInventory) );
        unset( $this->m_arrRuneInventory[$strGearSetName] );
    }
    public function _DestroyAllGearSets():void {
        $this->m_arrGearSetInventory = array();
    }

    public function _UnequipAll():void {
        foreach( $this->m_arrGearSetInventory as $strGearSetName => &$hGearSet ) {
            $hGearSet->_UnequipAllRunes();
        }
    }
    public function _DetachAll():void {
        foreach( $this->m_arrGearSetInventory as $strGearSetName => &$hGearSet ) {
            $hGearSet->_DetachFromAllHeroes();
        }
    }

    // Members
    private $m_arrGearSetInventory;
}

?>