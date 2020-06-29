/////////////////////////////////////////////////////////////////////////////////
// File : Main.cpp
/////////////////////////////////////////////////////////////////////////////////
// Version : 0.1
// Status : Alpha
/////////////////////////////////////////////////////////////////////////////////
// Description : CCGOptimizer Entry Point
/////////////////////////////////////////////////////////////////////////////////
// Part of Scarab-Engine, licensed under the
// Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License
//   http://creativecommons.org/licenses/by-nc-nd/3.0/
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Known Bugs : None.
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
// Third-Party Includes (Required for Entry-Point)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////
// Includes
#include "Main.h"

/////////////////////////////////////////////////////////////////////////////////
// CCGOPApplication implementation
CCGOPApplication::CCGOPApplication():
    m_hGUI(this)
{
    // nothing to do
}
CCGOPApplication::~CCGOPApplication()
{
    // nothing to do
}

Void CCGOPApplication::Initialize()
{
    // Initialize Memory Manager
    MemoryManager::Create();

    // Initialize Back-End
    GameDataFn->ImportFromXML();

    // Initialize Front-End
    m_hGUI.Initialize();
}
Void CCGOPApplication::Cleanup()
{
    // Cleanup Front-End
    m_hGUI.Cleanup();

    // Cleanup Back-End
    // Nothing to do

    // Cleanup Memory Manager
    MemoryManager::Destroy();
}

Void CCGOPApplication::IdleTime( Void * pUserData )
{
    CCGOPApplication * pApp = (CCGOPApplication*)pUserData;

    ///////////////////////////////////////////////////////////
    // Can launch multi-threaded background work here ...
}

/////////////////////////////////////////////////////////////////////////////////
// Entry Point
int APIENTRY wWinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow )
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    CCGOPApplication hApplication;

    hApplication.Initialize();

    Int iReturnCode = WinGUIFn->MessageLoop( CCGOPApplication::IdleTime, &hApplication );

    hApplication.Cleanup();

    return iReturnCode;
}

