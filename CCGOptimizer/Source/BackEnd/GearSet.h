<?php
/////////////////////////////////////////////////////////////////////////////////
// File : Source/PHP/BackEnd/GearSet.php
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
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

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

/////////////////////////////////////////////////////////////////////////////////
// The GearSet class
class GearSet {
	public function __construct( string $strName = NULL )
	{
        $this->m_strName = $strName;
        
        $this->m_arrEquippedRunes = array();
        for( $i = 0; $i < RUNE_SLOT_COUNT; ++$i ) {
            array_push( $this->m_arrEquippedRunes, NULL );
        }
        $this->m_arrAttachedHeroes = array();

        $this->m_fScoreEfficiency = 0.0;
        $this->m_fScoreDamage = 0.0;
        $this->m_fScoreTanking = 0.0;
        $this->_ComputeScores();
	}
	public function __destruct()
    {
		// nothing to do
	}

    // Import/Export
    public function ImportFromXML( XMLElement & $hXMLElement ):void {
		assert( $hXMLElement->GetTagName() == "gearset" );
        
        $this->m_strName = $hXMLElement->GetAttributeValue( "name" );

        for( $i = 0; $i < RUNE_SLOT_COUNT; ++$i ) {
            $strAttributeName = sprintf( "rune_slot_%d", $i );
            $this->m_arrEquippedRunes[$i] = intval( $hXMLElement->GetAttributeValue($strAttributeName) );
        }

        $this->m_arrAttachedHeroes = array();
		$hAttachedHeroesElement = $hXMLElement->GetChildByTag( "attached_heroes" );
        $iCount = intval( $hAttachedHeroesElement->GetAttributeValue("count") );
        for( $i = 0; $i < $iCount; ++$i ) {
            $strAttributeName = sprintf( "hero_%d", $i );
            $iHeroID = intval( $hAttachedHeroesElement->GetAttributeValue($strAttributeName) );
            array_push( $this->m_arrAttachedHeroes, $iHeroID );
        }

        $this->m_fScoreEfficiency = 0.0;
        $this->m_fScoreDamage = 0.0;
        $this->m_fScoreTanking = 0.0;
        $this->_ComputeScores();
	}
	public function ExportToXML( XMLDocument & $hRootDocument, XMLElement & $hXMLElement ):void {
        $hXMLElement = $hRootDocument->CreateElement( "gearset" );

        $hXMLElement->SetAttributeValue( "name", $this->m_strName );

        for( $i = 0; $i < RUNE_SLOT_COUNT; ++$i ) {
            $strAttributeName = sprintf( "rune_slot_%d", $i );
            $hXMLElement->SetAttributeValue( $strAttributeName, $this->m_arrEquippedRunes[$i] );
        }

        $hAttachedHeroesElement = $hRootDocument->CreateElement( "attached_heroes" );
        $iCount = count( $this->m_arrAttachedHeroes );
        $hAttachedHeroesElement->SetAttributeValue( "count", $iCount );
        for( $i = 0; $i < $iCount; ++$i ) {
            $strAttributeName = sprintf( "hero_%d", $i );
            $iHeroID = $this->m_arrAttachedHeroes[$i];
            $hAttachedHeroesElement->SetAttributeValue( $strAttributeName, $iHeroID );
        }
        $hXMLElement->AppendChild( $hAttachedHeroesElement );
    }

	// Name
	public function GetName():string {
		return $this->m_strName;
	}

    // Rune Equip
    public function GetEquippedRune( int $iSlot ):int {
        assert( $iSlot < RUNE_SLOT_COUNT );
        return $this->m_arrEquippedRunes[$iSlot];
    }
    public function HasEquippedRune( int $iRuneID ):int {
        $iFound = array_search( $iRuneID, $this->m_arrEquippedRunes );
        if ( $iFound !== false )
            return $iFound;
        return NULL;
    }

    // Hero Attach
    public function GetAttachedHeroCount():int {
        return count( $this->m_arrAttachedHeroes );
    }
    public function GetAttachedHero( int $iIndex ):int {
        assert( $iIndex < count($this->m_arrAttachedHeroes) );
        return $this->m_arrAttachedHeroes[$iIndex];
    }
    public function HasAttachedHero( int $iHeroID ):int {
        $iFound = array_search( $iHeroID, $this->m_arrAttachedHeroes );
        if ( $iFound !== false )
            return $iFound;
        return NULL;
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
    public function _EquipRune( int $iRuneID, int $iSlot ):void {
        assert( $iSlot < RUNE_SLOT_COUNT );
        $this->m_arrEquippedRunes[$iSlot] = $iRuneID;
        $this->_ComputeScores();
	}
	public function _UnequipRune( int $iSlot ):void {
        assert( $iSlot < RUNE_SLOT_COUNT );
        $this->m_arrEquippedRunes[$iSlot] = NULL;
        $this->_ComputeScores();
    }
    public function _UnequipAllRunes():void {
        for( $i = 0; $i < RUNE_SLOT_COUNT; ++$i ) {
            $this->m_arrEquippedRunes[$i] = NULL;
        }
        $this->_ComputeScores();
    }

    public function _AttachToHero( int $iHeroID ):int {
        $iFound = array_search( $iHeroID, $this->m_arrAttachedHeroes );
        if ( $iFound !== false )
            return $iFound;
        $iNewCount = array_push( $this->m_arrAttachedHeroes, $iHeroID );
		return ( $iNewCount - 1 );
    }
    public function _DetachFromHero( int $iHeroID ):void {
        $iFound = array_search( $iHeroID, $this->m_arrAttachedHeroes );
        if ( $iFound === false )
            return;
        array_splice( $this->m_arrAttachedHeroes, $iFound, 1 );
    }
    public function _DetachFromAllHeroes():void {
        $this->m_arrAttachedHeroes = array();
    }

    // Helpers
    private function _ComputeScores():void {
        /////////////////////////////////////
        // Need some math infos here ....
    }

    // Members
    private $m_strName;

    private $m_arrEquippedRunes;
    private $m_arrAttachedHeroes;

        // Score System
    private $m_fScoreEfficiency;
    private $m_fScoreDamage;
    private $m_fScoreTanking;
}

?>