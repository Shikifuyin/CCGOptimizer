<?php
/////////////////////////////////////////////////////////////////////////////////
// File : Source/PHP/BackEnd/CCGOPManager.php
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
// Portability : Any
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOP Main Interface
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
require_once "GameData.php";

require_once "Rune.php";
require_once "Hero.php";
require_once "GearSet.php";

require_once "RuneInventory.php";
require_once "HeroInventory.php";
require_once "GearSetInventory.php";

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

/////////////////////////////////////////////////////////////////////////////////
// The CCGOPManager class
class CCGOPManager
{
    // Singleton interface
    public static function &GetSingleton():CCGOPManager {
        if ( CCGOPManager::$m_hInstance == NULL )
            CCGOPManager::$m_hInstance = new CCGOPManager();
        return CCGOPManager::$m_hInstance;
    }
    protected static $m_hInstance;

    // Constructor / Destructor
    public function __construct()
    {
        $this->m_hGameData = &GameData::GetSingleton();
        $this->m_hGameData->ImportFromXML();

        $this->m_hRuneInventory = &RuneInventory::GetSingleton();
        $this->m_hHeroInventory = &HeroInventory::GetSingleton();
        $this->m_hGearSetInventory = &GearSetInventory::GetSingleton();
	}
	public function __destruct()
    {
		// nothing to do
    }

    // Import / Export
    public function ImportFromXML( string $strXMLFile ):void
    {
        $hXML = &XMLManager::GetSingleton();
        $hDocument = $hXML->CreateDocument();

        $hDocument->LoadFromFile( $strXMLFile );

        $hNodeList = $hDocument->GetElementsByTag( "ccgop_data" );
        $hRoot = $hNodeList->GetNode(0);

        $hNodeList = $hRoot->GetElementsByTag( "inventory_runes" );
        assert( $hNodeList->GetCount() == 1 );
        $hRuneInventoryElement = $hNodeList->GetNode(0);
        $this->m_hRuneInventory->ImportFromXML( $hRuneInventoryElement );

        $hNodeList = $hRoot->GetElementsByTag( "inventory_heroes" );
        assert( $hNodeList->GetCount() == 1 );
        $hHeroInventoryElement = $hNodeList->GetNode(0);
        $this->m_hHeroInventory->ImportFromXML( $hHeroInventoryElement );

        $hNodeList = $hRoot->GetElementsByTag( "inventory_gearsets" );
        assert( $hNodeList->GetCount() == 1 );
        $hGearSetInventoryElement = $hNodeList->GetNode(0);
        $this->m_hGearSetInventory->ImportFromXML( $hGearSetInventoryElement );
    }
    public function ExportToXML( string $strXMLFile ):void
    {
        $hXML = &XMLManager::GetSingleton();
        $hDocument = $hXML->CreateDocument();

        $hRoot = $hDocument->CreateElement( "ccgop_data" );
        $hDocument->AppendChild( $hRoot );

        $hRuneInventoryElement = NULL;
        $this->m_hRuneInventory->ExportToXML( $hDocument, $hRuneInventoryElement );
        $hRoot->AppendChild( $hRuneInventoryElement );

        $hHeroInventoryElement = NULL;
        $this->m_hHeroInventory->ExportToXML( $hDocument, $hHeroInventoryElement );
        $hRoot->AppendChild( $hHeroInventoryElement );

        $hGearSetInventoryElement = NULL;
        $this->m_hGearSetInventory->ExportToXML( $hDocument, $hGearSetInventoryElement );
        $hRoot->AppendChild( $hGearSetInventoryElement );

        $hDocument->SaveToFile( $strXMLFile );
    }

    // Rune Management
    public function GetRuneCount():int {
        return $this->m_hRuneInventory->GetRuneCount();
    }
    public function &GetRune( int $iRuneID ):Rune {
        return $this->m_hRuneInventory->GetRune( $iRuneID );
    }

    public function CreateRune( int $iSlot, int $iSet, int $iRank, int $iQuality, int $iLevel,
                                int $iMainStat, int $iInnateStat, int $iInnateStatValue, array $arrRandomStats, array $arrRandomStatValues ):int {
        return $this->m_hRuneInventory->_CreateRune(
            $iSlot, $iSet, $iRank, $iQuality, $iLevel, $iMainStat,
            $iInnateStat, $iInnateStatValue, $arrRandomStats, $arrRandomStatValues
        );
    }
    public function DestroyRune( int $iRuneID ):void {
        $this->UnequipRuneFromAllGearSets( $iRuneID );
        $this->m_hRuneInventory->_DestroyRune( $iRuneID );
    }
    public function DestroyAllRunes():void {
        $this->UnequipAllRunes();
        $this->m_hRuneInventory->_DestroyAllRunes();
    }

    public function LockAllRunes():void {
        $this->m_hRuneInventory->LockAll();
    }
    public function UnlockAllRunes():void {
        $this->m_hRuneInventory->UnlockAll();
    }

    // Hero Management
    public function GetHeroCount():int {
        return $this->m_hHeroInventory->GetHeroCount();
    }
    public function &GetHero( int $iHeroID ):Hero {
        return $this->m_hHeroInventory->GetHero( $iHeroID );
    }

    public function CreateHero( string $strName, int $iRank, int $iLevel, bool $bEvolved, int $iSanctify ):int {
        return $this->m_hHeroInventory->_CreateHero(
            $strName, $iRank, $iLevel, $bEvolved, $iSanctify
        );
    }
    public function DestroyHero( int $iHeroID ):void {
        $this->DetachAllGearSetsFromHero( $iHeroID );
        $this->m_hHeroInventory->_DestroyHero( $iHeroID );
    }
    public function DestroyAllHeroes():void {
        $this->DetachAllGearSets();
        $this->m_hHeroInventory->_DestroyAllHeroes();
    }

    public function UnselectAllHeroGearSets():void {
        $this->m_hHeroInventory->UnselectAllGearSets();
    }

    // GearSet Management
    public function GetGearSetCount():int {
        return $this->m_hGearSetInventory->GetGearSetCount();
    }
    public function &GetGearSet( string $strGearSetName ):GearSet {
        return $this->m_hGearSetInventory->GetGearSet( $strGearSetName );
    }

    public function CreateGearSet( string $strGearSetName ):bool {
        return $this->m_hGearSetInventory->_CreateGearSet( $strGearSetName );
    }
    public function DestroyGearSet( string $strGearSetName ):void {
        $this->UnequipAllRunesFromGearSet( $strGearSetName );
        $this->DetachGearSetFromAllHeroes( $strGearSetName );
        $this->m_hGearSetInventory->DestroyGearSet( $strGearSetName );
    }
    public function DestroyAllGearSets():void {
        $this->UnequipAllRunes();
        $this->DetachAllGearSets();
        $this->m_hGearSetInventory->DestroyAllGearSets();
    }

    // Rune Equip management
    public function EquipRuneToGearSet( int $iRuneID, string $strGearSetName ):void
    {
        $hRune = &$this->m_hRuneInventory->GetRune( $iRuneID );
        $hGearSet = &$this->m_hGearSetInventory->GetGearSet( $strGearSetName );
        $iSlot = $hRune->GetSlot();
        $iOldRuneID = $hGearSet->GetEquippedRune( $iSlot );
        if ( $iOldRuneID != NULL ) {
            $hOldRune = &$this->m_hRuneInventory->GetRune( $iOldRuneID );
            $hOldRune->_UnequipFromGearSet( $strGearSetName );
        }
        $hRune->_EquipToGearSet( $strGearSetName );
        $hGearSet->_EquipRune( $iRuneID, $iSlot );
    }
    public function UnequipRuneFromGearSet( int $iRuneID, string $strGearSetName ):void
    {
        $hRune = &$this->m_hRuneInventory->GetRune( $iRuneID );
        $hGearSet = &$this->m_hGearSetInventory->GetGearSet( $strGearSetName );
        $iSlot = $hRune->GetSlot();
        $hRune->_UnequipFromGearSet( $strGearSetName );
        $hGearSet->_UnequipRune( $iSlot );
    }
    public function UnequipAllRunesFromGearSet( string $strGearSetName ):void
    {
        $hGearSet = &$this->m_hGearSetInventory->GetGearSet( $strGearSetName );
        for( $i = 0; $i < RUNE_SLOT_COUNT; ++$i ) {
            $iRuneID = $hGearSet->GetEquippedRune( $i );
            if ( $iRuneID != NULL ) {
                $hRune = &$this->m_hRuneInventory->GetRune( $iRuneID );
                $hRune->_UnequipFromGearSet( $strGearSetName );
            }
        }
        $hGearSet->_UnequipAllRunes();
    }
    public function UnequipRuneFromAllGearSets( int $iRuneID ):void
    {
        $hRune = &$this->m_hRuneInventory->GetRune( $iRuneID );
        $iSlot = $hRune->GetSlot();
        $iCount = $hRune->GetGearSetCount();
        for( $i = 0; $i < $iCount; ++$i ) {
            $strGearSetName = $hRune->GetGearSet( $i );
            $hGearSet = &$this->m_hGearSetInventory->GetGearSet( $strGearSetName );
            $hGearSet->_UnequipRune( $iSlot );
        }
        $hRune->_UnequipFromAllGearSets();
    }
    public function UnequipAllRunes():void
    {
        $this->m_hRuneInventory->_UnequipAll();
        $this->m_hGearSetInventory->_UnequipAll();
    }

    // GearSet Attach management
    public function AttachGearSetToHero( string $strGearSetName, int $iHeroID ):void
    {
        $hGearSet = &$this->m_hGearSetInventory->GetGearSet( $strGearSetName );
        $hHero = &$this->m_hHeroInventory->GetHero( $iHeroID );
        $hGearSet->_AttachToHero( $iHeroID );
        $hHero->_AttachGearSet( $strGearSetName );
    }
    public function DetachGearSetFromHero( string $strGearSetName, int $iHeroID ):void
    {
        $hGearSet = &$this->m_hGearSetInventory->GetGearSet( $strGearSetName );
        $hHero = &$this->m_hHeroInventory->GetHero( $iHeroID );
        $hGearSet->_DetachFromHero( $iHeroID );
        $hHero->_DetachGearSet( $strGearSetName );
    }
    public function DetachAllGearSetsFromHero( int $iHeroID ):void
    {
        $hHero = &$this->m_hHeroInventory->GetHero( $iHeroID );
        $iCount = $hHero->GetGearSetCount();
        for( $i = 0; $i < $iCount; ++$i ) {
            $strGearSetName = $hHero->GetGearSet( $i );
            $hGearSet = &$this->m_hGearSetInventory->GetGearSet( $strGearSetName );
            $hGearSet->_DetachFromHero( $iHeroID );
        }
        $hHero->_DetachAllGearSets();
    }
    public function DetachGearSetFromAllHeroes( string $strGearSetName ):void
    {
        $hGearSet = &$this->m_hGearSetInventory->GetGearSet( $strGearSetName );
        $iCount = $hGearSet->GetAttachedHeroCount();
        for( $i = 0; $i < $iCount; ++$i ) {
            $iHeroID = $hGearSet->GetAttachedHero( $i );
            $hHero = &$this->m_hHeroInventory->GetHero( $iHeroID );
            $hHero->_DetachGearSet( $strGearSetName );
        }
        $hGearSet->_DetachFromAllHeroes();
    }
    public function DetachAllGearSets():void
    {
        $this->m_hGearSetInventory->_DetachAll();
        $this->m_hHeroInventory->_DetachAll();
    }

    // Search Engine
    public function FilterRunes( array $arrRuneQueries, array $arrExcluded = NULL, bool $bAllowLocked = false, bool $bAllowEquipped = false ):array {
        return $this->m_hRuneInventory->FilterSearch( $arrRuneQueries, $arrExcluded, $bAllowLocked, $bAllowEquipped );
    }
    public function FilterHeroes( array $arrHeroQueries ):array {
        return $this->m_hHeroInventory->FilterSearch( $arrHeroQueries );
    }
    public function FilterGearSets( array $arrGearSetQueries ):array {
        return $this->m_hGearSetInventory->FilterSearch( $arrGearSetQueries );
    }

    // Sorted Views
    public function GetRuneViewEntry( int $iIndex ):int {
        return $this->m_hRuneInventory->GetRuneViewEntry( $iIndex );
    }
    public function SortRuneView( $strRuneSortingRule ):void {
        $this->m_hRuneInventory->SortRuneView( $strRuneSortingRule );
    }

    public function GetHeroViewEntry( int $iIndex ):int {
        return $this->m_arrHeroInventory->GetHeroViewEntry( $iIndex );
    }
    public function SortHeroView( $strHeroSortingRule ):void {
        $this->m_hHeroInventory->SortHeroView( $strHeroSortingRule );
    }

    public function GetGearSetViewEntry( int $iIndex ):int {
        return $this->m_hGearSetInventory->GetGearSetViewEntry( $iIndex );
    }
    public function SortGearSetView( $strGearSetSortingRule ):void {
        $this->m_hGearSetInventory->SortGearSetView( $strGearSetSortingRule );
    }

    // Optimizer Engine

    // Members
    private $m_hGameData;
    private $m_hRuneInventory;
    private $m_hHeroInventory;
    private $m_hGearSetInventory;
}

?>