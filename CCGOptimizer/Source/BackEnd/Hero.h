<?php
/////////////////////////////////////////////////////////////////////////////////
// File : Source/PHP/BackEnd/Hero.php
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
/////////////////////////////////////////////////////////////////////////////////
// Description : Hero Representation
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
// The Hero class
class Hero
{
    // Constructor / Destructor
	public function __construct( int $iHeroID = 0, string $strName = "Slime",
								 int $iRank = HERO_RANK_1S, int $iLevel = 1, bool $bEvolved = false, int $iSanctify = HERO_SANCTIFY_NONE )
    {
		$hGameData = &GameData::GetSingleton();

		$this->m_iHeroID = $iHeroID;
		$this->m_strName = $strName;
		assert( $hGameData->IsHeroNameValid($this->m_strName) );
		$this->m_iFaction = $hGameData->GetHeroFaction( $this->m_strName );
		$this->m_iRank = $iRank;
		assert( $this->m_iRank >= $hGameData->GetHeroNaturalRank($this->m_strName) );
		$this->m_iLevel = $iLevel;
		assert( $this->m_iLevel > 0 && $this->m_iLevel <= $hGameData->GetHeroRankMaxLevel($this->m_iRank) );
		$this->m_bEvolved = $bEvolved;
		$this->m_iSanctify = $iSanctify;

		$this->m_arrAttachedGearSets = array();
		$this->m_strSelectedGearSet = "";
	}
	public function __destruct()
    {
		// nothing to do
	}

	// Import/Export
    public function ImportFromXML( XMLElement & $hXMLElement ):void {
		assert( $hXMLElement->GetTagName() == "hero" );
		$hGameData = &GameData::GetSingleton();
		
		$this->m_iHeroID = intval( $hXMLElement->GetAttributeValue("hero_id") );
		$this->m_strName = $hXMLElement->GetAttributeValue( "name" );
		assert( $hGameData->IsHeroNameValid($this->m_strName) );
		$this->m_iFaction = $hGameData->GetHeroFaction( $this->m_strName );
        $this->m_iRank = intval( $hXMLElement->GetAttributeValue("rank") );
        $this->m_iLevel = intval( $hXMLElement->GetAttributeValue("level") );
		$this->m_bEvolved = ( $hXMLElement->GetAttributeValue("evolved") == "true" );
		$this->m_iSanctify = intval( $hXMLElement->GetAttributeValue("sanctify") );
		
		$this->m_arrAttachedGearSets = array();
		$hAttachedGearSetsElement = $hXMLElement->GetChildByTag( "attached_gearsets" );
        $iCount = intval( $hAttachedGearSetsElement->GetAttributeValue("count") );
        for( $i = 0; $i < $iCount; ++$i ) {
            $strAttributeName = sprintf( "gearset_%d", $i );
            $strGearSetName = $hAttachedGearSetsElement->GetAttributeValue( $strAttributeName );
            array_push( $this->m_arrAttachedGearSets, $strGearSetName );
        }

		$this->m_strSelectedGearSet = $hXMLElement->GetAttributeValue( "gearset_selected" );
	}	
	public function ExportToXML( XMLDocument & $hRootDocument, XMLElement & $hXMLElement ):void {
		$hXMLElement = $hRootDocument->CreateElement( "hero" );

		$hXMLElement->SetAttributeValue( "hero_id", $this->m_iHeroID );
        $hXMLElement->SetAttributeValue( "name", $this->m_strName );
        $hXMLElement->SetAttributeValue( "rank", $this->m_iRank );
		$hXMLElement->SetAttributeValue( "level", $this->m_iLevel );
		$hXMLElement->SetAttributeValue( "evolved", $this->m_bEvolved ? "true" : "false" );
		$hXMLElement->SetAttributeValue( "sanctify", $this->m_iSanctify );

		$hAttachedGearSetsElement = $hRootDocument->CreateElement( "attached_gearsets" );
        $iCount = count( $this->m_arrAttachedGearSets );
        $hAttachedGearSetsElement->SetAttributeValue( "count", $iCount );
        for( $i = 0; $i < $iCount; ++$i ) {
            $strAttributeName = sprintf( "gearset_%d", $i );
            $strGearSetName = $this->m_arrAttachedGearSets[$i];
            $hAttachedGearSetsElement->SetAttributeValue( $strAttributeName, $strGearSetName );
        }
        $hXMLElement->AppendChild( $hAttachedGearSetsElement );

		$hXMLElement->SetAttributeValue( "gearset_selected", $this->m_strSelectedGearSet );
	}

	// Hero Characteristics
	public function GetID():int {
		return $this->m_iHeroID;
	}
	public function GetName():string {
		return $this->m_strName;
	}
	public function GetFaction():int {
		return $this->m_iFaction;
	}
	public function GetRank():int {
        return $this->m_iRank;
    }
    public function GetLevel():int {
        return $this->m_iLevel;
	}
	public function IsEvolved():bool {
        return $this->m_bEvolved;
	}
	public function IsSanctified():bool {
        return ( $this->m_iSanctify != HERO_SANCTIFY_NONE );
	}
	public function GetSanctification():int {
		return $this->m_iSanctify;
	}
	public function SetSanctification( int $iSanctify ):void {
		assert( $iSanctify < HERO_SANCTIFY_COUNT );
		$this->m_iSanctify = $iSanctify;
	}

	// GearSet Attach
	public function GetGearSetCount():int {
		return count( $this->m_arrAttachedGearSets );
	}
	public function GetGearSet( int $iIndex ):string {
		assert( $iIndex < count($this->m_arrAttachedGearSets) );
		return $this->m_arrAttachedGearSets[$iIndex];
	}
	public function HasGearSet( string $strGearSetName ):bool {
		return in_array( $strGearSetName, $this->m_arrAttachedGearSets );
	}

	public function GetSelectedGearSet():string {
		return $this->m_strSelectedGearSet;
	}
	public function SelectGearSet( string $strGearSetName ):void {
		assert( in_array($strGearSetName, $this->m_arrAttachedGearSets) );
		$this->m_strSelectedGearSet = $strGearSetName;
	}
	public function UnselectGearSet():void {
		$this->m_strSelectedGearSet = "";
	}

	// Internals
	public function _AttachGearSet( string $strGearSetName ):int {
		$iFound = array_search( $strGearSetName, $this->m_arrAttachedGearSets );
		if ( $iFound !== false )
			return $iFound;
		$iNewCount = array_push( $this->m_arrAttachedGearSets, $strGearSetName );
		return ( $iNewCount - 1 );
	}
	public function _DetachGearSet( string $strGearSetName ):void {
		$iFound = array_search( $strGearSetName, $this->m_arrAttachedGearSets );
		if ( $iFound === false )
			return;
		if ( $this->m_strSelectedGearSet == $strGearSetName )
			$this->m_strSelectedGearSet = "";
		array_splice( $this->m_arrAttachedGearSets, $iFound, 1 );
	}
	public function _DetachAllGearSets():void {
		$this->m_arrAttachedGearSets = array();
		$this->m_strSelectedGearSet = "";
	}

	// Helpers

	// Members
	private $m_iHeroID;
	private $m_strName;
	private $m_iFaction;
	private $m_iRank;
	private $m_iLevel;
	private $m_bEvolved;
	private $m_iSanctify;

	private $m_arrAttachedGearSets;
	private $m_strSelectedGearSet;
}

?>