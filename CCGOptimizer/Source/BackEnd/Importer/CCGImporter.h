/////////////////////////////////////////////////////////////////////////////////
// File : Source/BackEnd/Importer/CCGImporter.h
/////////////////////////////////////////////////////////////////////////////////
// Version : 1.0
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : Game Account Data Importer (The tricky part !)
/////////////////////////////////////////////////////////////////////////////////
// License :
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Header prelude
#ifndef CCGOP_BACKEND_IMPORTER_CCGIMPORTER_H
#define CCGOP_BACKEND_IMPORTER_CCGIMPORTER_H

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "../CCGOPManager.h"

/////////////////////////////////////////////////////////////////////////////////
// Constants definitions

/////////////////////////////////////////////////////////////////////////////////
// The CCGImporter class
class CCGImporter
{
    // Discrete singleton interface
public:
    inline static CCGImporter * GetInstance();

private:
    CCGImporter();
    ~CCGImporter();

public:
  

private:
 
};

/////////////////////////////////////////////////////////////////////////////////
// Backward Includes (Inlines & Templates)
#include "CCGImporter.inl"

/////////////////////////////////////////////////////////////////////////////////
// Header end
#endif // CCGOP_BACKEND_IMPORTER_CCGIMPORTER_H
