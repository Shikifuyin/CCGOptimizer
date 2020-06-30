/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/CCGOPManager.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
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
#include "CCGOPManager.h"

/////////////////////////////////////////////////////////////////////////////////
// CCGOPManager implementation
CCGOPManager::CCGOPManager():
    m_hRuneInventory(), m_hHeroInventory(), m_hGearSetInventory()
{
	// nothing to do
}
CCGOPManager::~CCGOPManager()
{
	// nothing to do
}

Void CCGOPManager::ImportFromXML( const GChar * strFileName )
{
    XMLDocument * pXMLDoc = XMLFn->CreateDocument( strFileName );
    Assert( pXMLDoc != NULL );
    Assert( StringFn->Cmp(pXMLDoc->GetTagName(), TEXT("ccgop_data")) == 0 );

    XMLNode * pNode = pXMLDoc->GetChildByTag( TEXT("inventory_runes"), 0 );
    Assert( pNode != NULL );
    m_hRuneInventory.ImportFromXML( pNode );

    pNode = pXMLDoc->GetChildByTag( TEXT("inventory_heroes"), 0 );
    Assert( pNode != NULL );
    m_hHeroInventory.ImportFromXML( pNode );

    pNode = pXMLDoc->GetChildByTag( TEXT("inventory_gearsets"), 0 );
    Assert( pNode != NULL );
    m_hGearSetInventory.ImportFromXML( pNode );

    XMLFn->DestroyDocument( pXMLDoc );
}
Void CCGOPManager::ExportToXML( const GChar * strFileName ) const
{
    XMLDocument * pXMLDoc = XMLFn->CreateDocument( TEXT("ccgop_data"), XML_VERSION, XML_ENCODING_DEFAULT );

    XMLNode * pNode = XMLFn->CreateNode( TEXT("inventory_runes"), false );
    m_hRuneInventory.ExportToXML( pNode );
    pXMLDoc->AppendChild( pNode );

    pNode = XMLFn->CreateNode( TEXT("inventory_heroes"), false );
    m_hHeroInventory.ExportToXML( pNode );
    pXMLDoc->AppendChild( pNode );

    pNode = XMLFn->CreateNode( TEXT("inventory_gearsets"), false );
    m_hGearSetInventory.ExportToXML( pNode );
    pXMLDoc->AppendChild( pNode );

    pXMLDoc->Render( strFileName );

    XMLFn->DestroyDocument( pXMLDoc );
}

Bool CCGOPManager::EquipRuneToGearSet( RuneID iRuneID, GearSetID iGearSetID )
{
    Rune * pRune = m_hRuneInventory.GetRune( iRuneID );
    GearSet * pGearSet = m_hGearSetInventory.GetGearSet( iGearSetID );
    UInt iSlot = pRune->GetSlot();

    if ( pRune->GetGearSetCount() >= RUNE_MAX_GEARSETS )
        return false;

    UInt iOldRuneID = pGearSet->GetEquippedRune( iSlot );
    if ( iOldRuneID != INVALID_OFFSET ) {
        Rune * pOldRune = m_hRuneInventory.GetRune( iOldRuneID );
        pOldRune->_UnequipFromGearSet( iGearSetID );
    }

    UInt iIndex = pRune->_EquipToGearSet( iGearSetID );
    Assert( iIndex != INVALID_OFFSET );

    pGearSet->_EquipRune( iRuneID, iSlot );

    return true;
}
Void CCGOPManager::UnequipRuneFromGearSet( RuneID iRuneID, GearSetID iGearSetID )
{
    Rune * pRune = m_hRuneInventory.GetRune( iRuneID );
    GearSet * pGearSet = m_hGearSetInventory.GetGearSet( iGearSetID );
    UInt iSlot = pRune->GetSlot();
    pRune->_UnequipFromGearSet( iGearSetID );
    pGearSet->_UnequipRune( iSlot );
}
Void CCGOPManager::UnequipAllRunesFromGearSet( GearSetID iGearSetID )
{
    GearSet * pGearSet = m_hGearSetInventory.GetGearSet( iGearSetID );
    for( UInt i = 0; i < RUNE_SLOT_COUNT; ++i ) {
        RuneID iRuneID = pGearSet->GetEquippedRune(i);
        if ( iRuneID != INVALID_OFFSET ) {
            Rune * pRune = m_hRuneInventory.GetRune( iRuneID );
            pRune->_UnequipFromGearSet( iGearSetID );
        }
    }
    pGearSet->_UnequipAllRunes();
}
Void CCGOPManager::UnequipRuneFromAllGearSets( RuneID iRuneID )
{
    Rune * pRune = m_hRuneInventory.GetRune( iRuneID );
    UInt iSlot = pRune->GetSlot();
    UInt iCount = pRune->GetGearSetCount();
    for( UInt i = 0; i < iCount; ++i ) {
        GearSetID iGearSetID = pRune->GetGearSet(i);
        GearSet * pGearSet = m_hGearSetInventory.GetGearSet( iGearSetID );
        pGearSet->_UnequipRune( iSlot );
    }
    pRune->_UnequipFromAllGearSets();
}
Void CCGOPManager::UnequipAllRunes()
{
    m_hRuneInventory._UnequipAll();
    m_hGearSetInventory._UnequipAll();
}

Bool CCGOPManager::AttachGearSetToHero( GearSetID iGearSetID, HeroID iHeroID )
{
    GearSet * pGearSet = m_hGearSetInventory.GetGearSet( iGearSetID );
    Hero * pHero = m_hHeroInventory.GetHero( iHeroID );

    if ( pGearSet->GetAttachedHeroCount() >= GEARSET_MAX_HEROES )
        return false;
    if ( pHero->GetGearSetCount() >= HERO_MAX_GEARSETS )
        return false;

    UInt iIndex = pGearSet->_AttachToHero( iHeroID );
    Assert( iIndex != INVALID_OFFSET );

    iIndex = pHero->_AttachGearSet( iGearSetID );
    Assert( iIndex != INVALID_OFFSET );

    return true;
}
Void CCGOPManager::DetachGearSetFromHero( GearSetID iGearSetID, HeroID iHeroID )
{
    GearSet * pGearSet = m_hGearSetInventory.GetGearSet( iGearSetID );
    Hero * pHero = m_hHeroInventory.GetHero( iHeroID );
    pGearSet->_DetachFromHero( iHeroID );
    pHero->_DetachGearSet( iGearSetID );
}
Void CCGOPManager::DetachAllGearSetsFromHero( HeroID iHeroID )
{
    Hero * pHero = m_hHeroInventory.GetHero( iHeroID );
    UInt iCount = pHero->GetGearSetCount();
    for( UInt i = 0; i < iCount; ++i ) {
        GearSetID iGearSetID = pHero->GetGearSet(i);
        GearSet * pGearSet = m_hGearSetInventory.GetGearSet( iGearSetID );
        pGearSet->_DetachFromHero( iHeroID );
    }
    pHero->_DetachAllGearSets();
}
Void CCGOPManager::DetachGearSetFromAllHeroes( GearSetID iGearSetID )
{
    GearSet * pGearSet = m_hGearSetInventory.GetGearSet( iGearSetID );
    UInt iCount = pGearSet->GetAttachedHeroCount();
    for( UInt i = 0; i < iCount; ++i ) {
        HeroID iHeroID = pGearSet->GetAttachedHero(i);
        Hero * pHero = m_hHeroInventory.GetHero( iHeroID );
        pHero->_DetachGearSet( iGearSetID );
    }
    pGearSet->_DetachFromAllHeroes();
}
Void CCGOPManager::DetachAllGearSets()
{
    m_hGearSetInventory._DetachAll();
    m_hHeroInventory._DetachAll();
}


