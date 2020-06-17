<?php
/////////////////////////////////////////////////////////////////////////////////
// File : Source/PHP/BackEnd/RuneInventory.php
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Inventory Manager
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
define( "RUNE_QUERY_SLOT",          0 ); // value = array( slot ids )
define( "RUNE_QUERY_SET",           1 ); // value = array( set ids )
define( "RUNE_QUERY_MAINSTAT",      2 ); // value = array( stat ids )
define( "RUNE_QUERY_SUBSTATS",      3 ); // value = array( "and" | "or", array(stat id, stat threshold) )
define( "RUNE_QUERY_EFFICIENCY",    4 ); // value = efficiency score threshold
define( "RUNE_QUERY_DAMAGE",        5 ); // value = damage score threshold
define( "RUNE_QUERY_TANKING",       6 ); // value = tanking score threshold

/////////////////////////////////////////////////////////////////////////////////
// The RuneInventory class
class RuneInventory
{
    // Singleton interface
    public static function &GetSingleton():RuneInventory {
        if ( RuneInventory::$m_hInstance == NULL )
            RuneInventory::$m_hInstance = new RuneInventory();
        return RuneInventory::$m_hInstance;
    }
    protected static $m_hInstance;

    // Constructor / Destructor
    public function __construct()
    {
        // RuneID Allocator
        $this->m_iNextFreeRuneID = 1;

        // Rune Inventory
        $this->m_arrRuneInventory = array();
	}
	public function __destruct()
    {
		// nothing to do
    }

    // Import/Export
    public function ImportFromXML( XMLElement & $hXMLElement ):void {
        assert( $hXMLElement->GetTagName() == "inventory_runes" );

        $this->m_arrRuneInventory = array();
        $hRuneNodeList = $hXMLElement->GetElementsByTag( "rune" );
        $iCount = $hRuneNodeList->GetCount();
        $iBiggestID = 0;
        for( $i = 0; $i < $iCount; ++$i ) {
            $hRuneElement = $hRuneNodeList->GetNode( $i );
            $hRune = new Rune();
            $hRune->ImportFromXML( $hRuneElement );
            $this->m_arrRuneInventory[$hRune->GetID()] = $hRune;
            if ( $hRune->GetID() > $iBiggestID )
                $iBiggestID = $hRune->GetID();
        }
        $this->m_iNextFreeRuneID = $iBiggestID + 1;
    }
    public function ExportToXML( XMLDocument & $hRootDocument, XMLElement & $hXMLElement ):void {
        $hXMLElement = $hRootDocument->CreateElement( "inventory_runes" );

        foreach( $this->m_arrRuneInventory as &$hRune ) {
            $hRuneElement = NULL;
            $hRune->ExportToXML( $hRootDocument, $hRuneElement );
            $hXMLElement->AppendChild( $hRuneElement );
        }
    }

    // Rune Inventory
    public function GetRuneCount():int {
        return count( $this->m_arrRuneInventory );
    }
    public function &GetRune( int $iRuneID ):Rune {
        assert( array_key_exists($iRuneID, $this->m_arrRuneInventory) );
        return $this->m_arrRuneInventory[$iRuneID];
    }

    // Rune Locks
    public function LockAll():void {
        foreach( $this->m_arrRuneInventory as $iRuneID => &$hRune ) {
            $hRune->Lock();
        }
    }
    public function UnlockAll():void {
        foreach( $this->m_arrRuneInventory as $iRuneID => &$hRune ) {
            $hRune->Unlock();
        }
    }

    // Search Engine
    public function FilterSearch( array $arrQueries, array $arrExcluded = NULL, bool $bAllowLocked = false, bool $bAllowEquipped = false ):array {
        $arrRuneCollection = array();

        // Slot Query
        $arrQuerySlot = NULL;
        if ( array_key_exists(RUNE_QUERY_SLOT, $arrQueries) )
            $arrQuerySlot = $arrQueries[RUNE_QUERY_SLOT];

        // Set Query
        $arrQuerySet = NULL;
        if ( array_key_exists(RUNE_QUERY_SET, $arrQueries) )
            $arrQuerySet = $arrQueries[RUNE_QUERY_SET];

        // MainStat Query
        $arrQueryMainStat = NULL;
        if ( array_key_exists(RUNE_QUERY_MAINSTAT, $arrQueries) )
            $arrQueryMainStat = $arrQueries[RUNE_QUERY_MAINSTAT];

        // SubStats Query
        $arrQuerySubStats = NULL;
        if ( array_key_exists(RUNE_QUERY_SUBSTATS, $arrQueries) ) {
            $arrQuerySubStats = $arrQueries[RUNE_QUERY_SUBSTATS];
        }

        // Efficiency Query
        $fQueryEfficiency = NULL;
        if ( array_key_exists(RUNE_QUERY_EFFICIENCY, $arrQueries) )
            $fQueryEfficiency = $arrQueries[RUNE_QUERY_EFFICIENCY];

        // Damage Query
        $fQueryDamage = NULL;
        if ( array_key_exists(RUNE_QUERY_DAMAGE, $arrQueries) )
            $fQueryDamage = $arrQueries[RUNE_QUERY_DAMAGE];

        // Tanking Query
        $fQueryTanking = NULL;
        if ( array_key_exists(RUNE_QUERY_TANKING, $arrQueries) )
            $fQueryTanking = $arrQueries[RUNE_QUERY_TANKING];

        // Search
        foreach( $this->m_arrRuneInventory as $iRuneID => &$hRune ) {
            // Filter Excluded
            if ( $arrExcluded != NULL ) {
                if ( in_array($iRuneID, $arrExcluded) )
                    continue;
            }
            // Filter Locked
            if ( !$bAllowLocked ) {
                if ( $hRune->IsLocked() )
                    continue;
            }
            // Filter Equipped
            if ( !$bAllowEquipped ) {
                if ( $hRune->IsEquipped() )
                    continue;
            }

            // Filter Slot
            if ( $arrQuerySlot != NULL ) {
                $bFilterOut = true;
                $iCount = count( $arrQuerySlot );
                for( $i = 1; $i < $iCount; ++$i ) {
                    $iQuerySlot = $arrQuerySlot[$i];
                    if ( $hRune->GetSlot() == $iQuerySlot ) {
                        $bFilterOut = false;
                        break;
                    }
                }
                if ( $bFilterOut )
                    continue;
            }
            // Filter Set
            if ( $arrQuerySet != NULL ) {
                $bFilterOut = true;
                $iCount = count( $arrQuerySet );
                for( $i = 1; $i < $iCount; ++$i ) {
                    $iQuerySet = $arrQuerySet[$i];
                    if ( $hRune->GetSet() == $iQuerySet ) {
                        $bFilterOut = false;
                        break;
                    }
                }
                if ( $bFilterOut )
                    continue;
            }
            // Filter MainStat
            if ( $arrQueryMainStat != NULL ) {
                $bFilterOut = true;
                $iCount = count( $arrQueryMainStat );
                for( $i = 1; $i < $iCount; ++$i ) {
                    $iQueryMainStat = $arrQueryMainStat[$i];
                    if ( $hRune->GetMainStat() == $iQueryMainStat ) {
                        $bFilterOut = false;
                        break;
                    }
                }
                if ( $bFilterOut )
                    continue;
            }
            // Filter SubStats
            if ( $arrQuerySubStats != NULL ) {
                $bFilterOut = false;
                $bAndElseOr = ( $arrQuerySubStats[0] == "and" );
                if ( $bAndElseOr ) { // match all specified sub stats
                    $bFilterOut = false;
                    $iCount = count( $arrQuerySubStats );
                    for( $i = 1; $i < $iCount; ++$i ) {
                        $iQuerySubStat = $arrQuerySubStats[$i][0];
                        $iQuerySubStatThreshold = $arrQuerySubStats[$i][1];
                        $iValue = $hRune->HasSubStat( $iQuerySubStat );
                        if ( $iValue == 0 || $iValue < $iQuerySubStatThreshold ) {
                            $bFilterOut = true;
                            break;
                        }
                    }
                } else { // match at least one specified sub stat
                    $bFilterOut = true;
                    $iCount = count( $arrQuerySubStats );
                    for( $i = 1; $i < $iCount; ++$i ) {
                        $iQuerySubStat = $arrQuerySubStats[$i][0];
                        $iQuerySubStatThreshold = $arrQuerySubStats[$i][1];
                        $iValue = $hRune->HasSubStat( $iQuerySubStat );
                        if ( $iValue >= $iQuerySubStatThreshold ) {
                            $bFilterOut = false;
                            break;
                        }
                    }
                }
                if ( $bFilterOut )
                    continue;
            }
            // Filter Efficiency
            if ( $fQueryEfficiency != NULL ) {
                if ( $hRune->GetScoreEfficiency() < $fQueryEfficiency )
                    continue;
            }
            // Filter Damage
            if ( $fQueryDamage != NULL ) {
                if ( $hRune->GetScoreDamage() < $fQueryDamage )
                    continue;
            }
            // Filter Tanking
            if ( $fQueryTanking != NULL ) {
                if ( $hRune->GetScoreTanking() < $fQueryTanking )
                    continue;
            }

            // Passed all filters, collect
            array_push( $arrRuneCollection, $iRuneID );
        }

        return $arrRuneCollection;
    }

    // Internals
    public function _CreateRune( int $iSlot, int $iSet, int $iRank, int $iQuality, int $iLevel,
                                 int $iMainStat, int $iInnateStat, int $iInnateStatValue, array $arrRandomStats, array $arrRandomStatValues ):int {
        $iRuneID = $this->_AllocateRuneID();
        $this->m_arrRuneInventory[$iRuneID] = new Rune(
            $iRuneID, $iSlot, $iSet, $iRank, $iQuality, $iLevel,
            $iMainStat, $iInnateStat, $iInnateStatValue, $arrRandomStats, $arrRandomStatValues
        );
        return $iRuneID;
    }
    public function _DestroyRune( int $iRuneID ):void {
        assert( array_key_exists($iRuneID, $this->m_arrRuneInventory) );
        unset( $this->m_arrRuneInventory[$iRuneID] );
    }
    public function _DestroyAllRunes():void {
        $this->m_iNextFreeRuneID = 1;
        $this->m_arrRuneInventory = array();
    }

    public function _UnequipAll():void {
        foreach( $this->m_arrRuneInventory as $iRuneID => &$hRune ) {
            $hRune->_UnequipFromAllGearSets();
        }
    }

    // Helpers
    private function _AllocateRuneID():int {
        assert( $this->m_iNextFreeRuneID < PHP_INT_MAX );
        $iRuneID = $this->m_iNextFreeRuneID;
        ++$this->m_iNextFreeRuneID;
        return $iRuneID;
    }

    // Members
    private $m_iNextFreeRuneID;

    private $m_arrRuneInventory;
}

?>