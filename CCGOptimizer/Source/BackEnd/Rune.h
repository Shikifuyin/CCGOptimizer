<?php
/////////////////////////////////////////////////////////////////////////////////
// File : Source/PHP/BackEnd/Rune.php
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
/////////////////////////////////////////////////////////////////////////////////
// Description : Rune Representation
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : Need more data ...
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Includes

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

/////////////////////////////////////////////////////////////////////////////////
// The Rune class
class Rune
{
    // Constructor / Destructor
    public function __construct( int $iRuneID = 0, int $iSlot = 1, int $iSet = RUNE_SET_BLESSING,
                                 int $iRank = RUNE_RANK_1S, int $iQuality = RUNE_QUALITY_COMMON, int $iLevel = 0,
                                 int $iMainStat = RUNE_STAT_ATTACK_FLAT, int $iInnateStat = 0, int $iInnateStatValue = 0,
                                 array $arrRandomStats = array(0,0,0,0), array $arrRandomStatValues = array(0,0,0,0) )
    {
        $hGameData = &GameData::GetSingleton();

        $this->m_iRuneID = $iRuneID;
        $this->m_iSlot = $iSlot;
        $this->m_iSet = $iSet;
        $this->m_iRank = $iRank;
        $this->m_iQuality = $iQuality;
        $this->m_iLevel = $iLevel;

        $this->m_iMainStat = $iMainStat;
        assert( $hGameData->IsRuneMainStatAllowed($this->m_iMainStat, $this->m_iSlot) );

        $this->m_iInnateStat = $iInnateStat;
        $this->m_iInnateStatValue = $iInnateStatValue;
        for( $i = 0; $i < RUNE_RANDOM_STAT_COUNT; ++$i ) {
            $this->m_arrRandomStats[$i] = $arrRandomStats[$i];
            $this->m_arrRandomStatValues[$i] = $arrRandomStatValues[$i];
        }

        $this->m_fScoreEfficiency = 0.0;
        $this->m_fScoreDamage = 0.0;
        $this->m_fScoreTanking = 0.0;
        $this->_ComputeScores();

        $this->m_bLocked = false;
        $this->m_arrEquippedGearSets = array();
	}
	public function __destruct()
    {
        // nothing to do
	}

    // Import/Export
    public function ImportFromXML( XMLElement & $hXMLElement ):void {
        assert( $hXMLElement->GetTagName() == "rune" );
        $hGameData = &GameData::GetSingleton();

        $this->m_iRuneID = intval( $hXMLElement->GetAttributeValue("rune_id") );
        $this->m_iSlot = intval( $hXMLElement->GetAttributeValue("slot") );
        $this->m_iSet = intval( $hXMLElement->GetAttributeValue("set") );
        $this->m_iRank = intval( $hXMLElement->GetAttributeValue("rank") );
        $this->m_iQuality = intval( $hXMLElement->GetAttributeValue("quality") );
        $this->m_iLevel = intval( $hXMLElement->GetAttributeValue("level") );

        $this->m_iMainStat = intval( $hXMLElement->GetAttributeValue("main_stat") );
        assert( $hGameData->IsRuneMainStatAllowed($this->m_iMainStat, $this->m_iSlot) );

        $hInnateStatElement = $hXMLElement->GetChildByTag( "innate_stat" );
        $this->m_iInnateStat = intval( $hInnateStatElement->GetAttributeValue("type") );
        $this->m_iInnateStatValue = intval( $hInnateStatElement->GetAttributeValue("value") );

        for( $i = 0; $i < RUNE_RANDOM_STAT_COUNT; ++$i ) {
            $strNodeName = sprintf( "random_stat_%d", $i );
            $hRandomStatElement = $hXMLElement->GetChildByTag( $strNodeName );
            $this->m_arrRandomStats[$i] = intval( $hRandomStatElement->GetAttributeValue("type") );
            $this->m_arrRandomStatValues[$i] = intval( $hRandomStatElement->GetAttributeValue("value") );
        }

        $this->m_fScoreEfficiency = 0.0;
        $this->m_fScoreDamage = 0.0;
        $this->m_fScoreTanking = 0.0;
        $this->_ComputeScores();

        $this->m_bLocked = ( $hXMLElement->GetAttributeValue("locked") == "true" );

        $this->m_arrEquippedGearSets = array();
        $hEquippedGearSetsElement = $hXMLElement->GetChildByTag( "equipped_gearsets" );
        $iCount = intval( $hEquippedGearSetsElement->GetAttributeValue("count") );
        for( $i = 0; $i < $iCount; ++$i ) {
            $strAttributeName = sprintf( "gearset_%d", $i );
            $strGearSetName = $hEquippedGearSetsElement->GetAttributeValue( $strAttributeName );
            array_push( $this->m_arrEquippedGearSets, $strGearSetName );
        }
    }
    public function ExportToXML( XMLDocument & $hRootDocument, XMLElement & $hXMLElement ):void {
        $hXMLElement = $hRootDocument->CreateElement( "rune" );

        $hXMLElement->SetAttributeValue( "rune_id", $this->m_iRuneID );
        $hXMLElement->SetAttributeValue( "slot", $this->m_iSlot );
        $hXMLElement->SetAttributeValue( "set", $this->m_iSet );
        $hXMLElement->SetAttributeValue( "rank", $this->m_iRank );
        $hXMLElement->SetAttributeValue( "quality", $this->m_iQuality );
        $hXMLElement->SetAttributeValue( "level", $this->m_iLevel );

        $hXMLElement->SetAttributeValue( "main_stat", $this->m_iMainStat );

        $hInnateStatElement = $hRootDocument->CreateElement( "innate_stat" );
        $hInnateStatElement->SetAttributeValue( "type", $this->m_iInnateStat );
        $hInnateStatElement->SetAttributeValue( "value", $this->m_iInnateStatValue );
        $hXMLElement->AppendChild( $hInnateStatElement );

        for( $i = 0; $i < RUNE_RANDOM_STAT_COUNT; ++$i ) {
            $strNodeName = sprintf( "random_stat_%d", $i );
            $hRandomStatElement = $hRootDocument->CreateElement( $strNodeName );
            $hRandomStatElement->SetAttributeValue( "type", $this->m_arrRandomStats[$i] );
            $hRandomStatElement->SetAttributeValue( "value", $this->m_arrRandomStatValues[$i] );
            $hXMLElement->AppendChild( $hRandomStatElement );
        }

        $hXMLElement->SetAttributeValue( "locked", $this->m_bLocked ? "true" : "false" );

        $hEquippedGearSetsElement = $hRootDocument->CreateElement( "equipped_gearsets" );
        $iCount = count( $this->m_arrEquippedGearSets );
        $hEquippedGearSetsElement->SetAttributeValue( "count", $iCount );
        for( $i = 0; $i < $iCount; ++$i ) {
            $strAttributeName = sprintf( "gearset_%d", $i );
            $strGearSetName = $this->m_arrEquippedGearSets[$i];
            $hEquippedGearSetsElement->SetAttributeValue( $strAttributeName, $strGearSetName );
        }
        $hXMLElement->AppendChild( $hEquippedGearSetsElement );
    }

    // Rune Characteristics
    public function GetID():int {
        return $this->m_iRuneID;
    }
    public function GetSlot():int {
        return $this->m_iSlot;
    }
    public function GetSet():int {
        return $this->m_iSet;
    }
    public function GetRank():int {
        return $this->m_iRank;
    }
    public function GetQuality():int {
        return $this->m_iQuality;
    }
    public function GetLevel():int {
        return $this->m_iLevel;
    }

    public function GetMainStat():int {
        return $this->m_iMainStat;
    }
    public function GetMainStatValue():int {
        $hGameData = &GameData::GetSingleton();
        return $hGameData->GetRuneMainStatValue( $this->m_iMainStat, $this->m_iLevel, $this->m_iRank );
    }

    public function GetInnateStat():int {
        return $this->m_iInnateStat;
    }
    public function GetInnateStatValue():int {
        return $this->m_iInnateStatValue;
    }

    public function GetRandomStat( int $iIndex ):int {
        assert( $iIndex < RUNE_RANDOM_STAT_COUNT );
        return $this->m_arrRandomStats[$iIndex];
    }
    public function GetRandomStatValue( int $iIndex ):int {
        assert( $iIndex < RUNE_RANDOM_STAT_COUNT );
        return $this->m_arrRandomStatValues[$iIndex];
    }

    // Rune Stat Queries
    public function HasMainStat( int $iRuneStat ):int {
        if ( $this->m_iMainStat == $iRuneStat ) {
            $hGameData = &GameData::GetSingleton();
            return $hGameData->GetRuneMainStatValue( $iRuneStat, $this->m_iLevel, $this->m_iRank );
        }
        return NULL;
    }
    public function HasInnateStat( int $iRuneStat ):int {
        if ( $this->m_iInnateStat == $iRuneStat )
            return $this->m_iInnateStatValue;
        return NULL;
    }
    public function HasRandomStat( int $iRuneStat ):int {
        $iFound = array_search( $iRuneStat, $this->m_arrRandomStats );
        if ( $iFound !== false )
            return $this->m_arrRandomStatValues[$iFound];
        return NULL;
    }
    public function HasSubStat( int $iRuneStat ):int {
        if ( $this->m_iInnateStat == $iRuneStat )
            return $this->m_iInnateStatValue;
        $iFound = array_search( $iRuneStat, $this->m_arrRandomStats );
        if ( $iFound !== false )
            return $this->m_arrRandomStatValues[$iFound];
        return NULL;
    }

    // Rune Locks
    public function IsLocked():bool {
        return $this->m_bLocked;
    }
    public function Lock():void {
        $this->m_bLocked = true;
    }
    public function Unlock():void {
        $this->m_bLocked = false;
    }

    // GearSet Equip
    public function IsEquipped():bool {
        return ( count($this->m_arrEquippedGearSets) > 0 );
    }
    public function GetGearSetCount():int {
        return count( $this->m_arrEquippedGearSets );
    }
    public function GetGearSet( int $iIndex ):string {
        assert( $iIndex < count($this->m_arrEquippedGearSets) );
        return $this->m_arrEquippedGearSets[$iIndex];
    }
    public function HasGearSet( string $strGearSetName ):bool {
        return in_array( $strGearSetName, $this->m_arrEquippedGearSets );
	}

    // Score system
    public function GetScoreEfficiency():float {
        return $this->m_fScoreEfficiency;
    }
    public function GetScoreDamage():float {
        return $this->m_fScoreDamage;
    }
    public function GetScoreTanking():float {
        return $this->m_fScoreTanking;
    }

    // Internals
    public function _EquipToGearSet( string $strGearSetName ):int {
        $iFound = array_search( $strGearSetName, $this->m_arrEquippedGearSets );
        if ( $iFound !== false )
            return $iFound;
        $iNewCount = array_push( $this->m_arrEquippedGearSets, $strGearSetName );
        return ( $iNewCount - 1 );
    }
    public function _UnequipFromGearSet( string $strGearSetName ):void {
        $iFound = array_search( $strGearSetName, $this->m_arrEquippedGearSets );
        if ( $iFound === false )
            return;
        array_splice( $this->m_arrEquippedGearSets, $iFound, 1 );
    }
    public function _UnequipFromAllGearSets():void {
        $this->m_arrEquippedGearSets = array();
    }

    // Helpers
    private function _ComputeScores():void {
        /////////////////////////////////////
        // Need some math infos here ....
    }

    // Members
    private $m_iRuneID;
    private $m_iSlot;
    private $m_iSet;
    private $m_iRank;
    private $m_iQuality;
    private $m_iLevel;

    private $m_iMainStat;
    private $m_iInnateStat;
    private $m_iInnateStatValue;
    private $m_arrRandomStats;
    private $m_arrRandomStatValues;

    private $m_bLocked;
    private $m_arrEquippedGearSets;

        // Score System
    private $m_fScoreEfficiency; // How close the rune is to max rolls
    private $m_fScoreDamage;     // How much damage the rune provides (factor attack and crit)
    private $m_fScoreTanking;    // How much tankyness the rune provides (factor hp and def)
}

?>