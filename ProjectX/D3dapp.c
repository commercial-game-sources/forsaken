/*
 * The X Men, June 1996
 * Copyright (c) 1996 Probe Entertainment Limited
 * All Rights Reserved
 *
 * $Revision: 38 $
 *
 * $Header: /PcProjectX/D3dapp.c 38    11/11/98 16:00 Philipy $
 *
 * $Log: /PcProjectX/D3dapp.c $
 * 
 * 38    11/11/98 16:00 Philipy
 * various fixes for warnings / errors when compiling under VC6
 * 
 * 37    3/09/98 14:25 Philipy
 * tidied up window mode slightly
 * ( no resize allowed, removed menu bar )
 * 
 * 36    18/08/98 18:14 Philipy
 * all pings in server game are now from server perspective
 * windowed mode re-enabled ( still needs some work )
 * 
 * 35    15/06/98 15:42 Collinsd
 * Fixed software menus in demo mode.
 * 
 * 34    10/04/98 18:03 Collinsd
 * 
 * 33    10/04/98 17:11 Philipy
 * 
 * 32    8/04/98 10:14 Philipy
 * removed error message when checking alt+tabbing back into game on 3dfx
 * 
 * 31    7/04/98 22:13 Collinsd
 * Hack for chris's goals.  CWClear screen added.
 * 
 * 30    4/04/98 17:38 Collinsd
 * Updated Software
 * 
 * 29    3/04/98 11:25 Collinsd
 * Mono lighting and acclaim logo now work and display of goals added
 * again.
 * 
 * 28    26/03/98 15:15 Collinsd
 * Mods for Chris
 * 
 * 27    6/03/98 14:25 Collinsd
 * 
 * 26    16/02/98 16:53 Collinsd
 * Added Chris's new code.
 * 
 * 25    5/01/98 19:58 Oliverc
 * Current screen mode, texture format and sound volume settings now saved
 * to registry on exit and restored on startup
 * 
 * 24    12/11/97 18:26 Collinsd
 * 
 * 23    7/11/97 14:25 Philipy
 * fixed bug when changing mode from title room: InitTitle was not being
 * called
 * 
 * 22    23/10/97 13:52 Collinsd
 * Added code to enable/disable compilation of software version.
 * SOFTWARE_ENABLE & softblit.lib.
 * 
 * 21    22/09/97 10:40 Collinsd
 * Software version works again. ( Now with trasnsluecency )
 * 
 * 20    9/18/97 12:16p Phillipd
 * 
 * 19    17/09/97 16:37 Collinsd
 * Blit now works in software.
 * 
 * 18    17/09/97 9:55 Collinsd
 * Blitting now works in software versions in 320x240 mode.
 * 
 * 17    16/09/97 17:52 Collinsd
 * More of Chris's stuff works.
 * 
 * 16    16/09/97 10:59 Collinsd
 * Added Chris's code
 * 
 * 15    31/07/97 15:57 Oliverc
 * Added special SELF_PLAY features, including disabling critical unused
 * code and setting default values appropriate to demo attract mode
 * 
 * 14    6/16/97 2:57p Phillipd
 * Tripple buffering can now be done....
 * 
 * 13    1/10/97 11:30a Phillipd
 * movies are now doable
 * 
 * 12    11/06/96 6:10p Phillipd
 * Got rid of some useless files...
 * 
 * 11    5/11/96 17:19 Oliverc
 * Added calls to FlipToGDISurface() when in fullscreen mode and entering
 * DPlay Wizard or pausing game to use menus so that 3Dfx card works
 * 
 * 10    10/24/96 3:01p Phillipd
 * 
 * 9     10/23/96 4:23p Phillipd
 * Lots of crap taken out of D3dapp and its associated functions and
 * files....
 * 
 * 8     10/03/96 9:09a Phillipd
 * 
 * 7     17/09/96 16:19 Oliverc
 * Added auto unpause whenever window moved or resized
 * 
 * 6     9/17/96 11:26a Phillipd
 * 
 * 5     7/26/96 4:27p Phillipd
 * 
 * 4     7/22/96 11:16a Phillipd
 * 
 * 3     4/07/96 11:56 Oliverc
 * 
 * 2     6/25/96 11:37a Phillipd
 * First SS update
 * 
 */

/*
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: d3dapp.c
 *
 *  Top level D3DApp functions and internal global variables.  See
 *  d3dapp.h for more information.
 *
 *  D3DApp is a collection of helper functions for Direct3D applications.
 *  D3DApp consists of the following files:
 *      d3dapp.h    Main D3DApp header to be included by application
 *      d3dappi.h   Internal header
 *      d3dapp.c    D3DApp functions seen by application.
 *      ddcalls.c   All calls to DirectDraw objects except textures
 *      d3dcalls.c  All calls to Direct3D objects except textures
 *      texture.c   Texture loading and managing texture list
 *      misc.c      Miscellaneous calls
 */

#include "typedefs.h"
#include "d3dappi.h"
#include "main.h"
#include "title.h"

extern void SetCursorClip( void );
extern BOOL cursorclipped;
extern BOOL	DrawPanel;
extern BOOL	DrawCrosshair;
extern	uint16 PanelHeight;
extern void ProcessTextItems (void);


extern	int		TexturePalettized;
extern	int		TextureRedBPP;
extern	int		TextureGreenBPP;
extern	int		TextureBlueBPP;
extern	int		TextureAlphaBPP;
extern	int		TextureIndexBPP;
extern BOOL CanRenderWindowed;

extern d3dmainglobals myglobs;     /* collection of global variables */
//#define INITGUID

#ifdef SOFTWARE_ENABLE
/*---------------------------------------------------------------------------
	Chris Walsh's code
---------------------------------------------------------------------------*/
extern void SetVTables();
extern void CWFlip( void );
//extern void CWStretchBlit( WORD, WORD, long, char *);
extern long LineWidth;
extern char * ScreenBase;
extern WORD SurfBpp;
extern void ClrOT();
extern void SWRendView();
extern long Highestz;
extern char DrawnYet;
extern WORD SurfWidth, SurfHeight;
extern BYTE MyGameStatus;
extern BOOL	ServerMode;
extern BOOL	DrawSimplePanel;
extern BOOL	JustExitedMenu;
extern BOOL Our_CalculateFrameRate(void);
extern BOOL	SoftwareVersion;
extern void CWAfterModeSwitch(void);
extern	long	zRW;

void CWClearScreen( void );

char CWInTitle = 1;
/*-------------------------------------------------------------------------*/
#endif

/***************************************************************************/
/*                           GLOBAL VARIABLES                              */
/***************************************************************************/
/*
 * All DD and D3D objects which are also available to the application
 * See d3dapp.h for typedef
 */
D3DAppInfo d3dappi;
/*
 * Internal record of the render state.  See d3dapp.h for typedef
 */
D3DAppRenderState d3dapprs; 
/* 
 * Callback functions for D3D device creation and destruction
 */
BOOL(*D3DDeviceDestroyCallback)(LPVOID);
LPVOID D3DDeviceDestroyCallbackContext;
BOOL(*D3DDeviceCreateCallback)(int, int, LPDIRECT3DVIEWPORT*, LPVOID);
LPVOID D3DDeviceCreateCallbackContext;
/*
 * The last error code and string
 */
HRESULT LastError;
char LastErrorString[256];
/*
 * List of texture handles which is copied to D3DAppInfo structure when
 * necessary
 */

void InitModeCase(void);

LPDIRECTDRAWCLIPPER lpClipper; /* Clipper in windowed case */
LPDIRECTDRAWPALETTE lpPalette; /* Front buffer's palette */
PALETTEENTRY ppe[256];         /* Current palette entries */
PALETTEENTRY Originalppe[256]; /* Windows palette entries at startup */
BOOL bD3DAppInitialized;       /* Is D3DApp initialized? */
BOOL bPrimaryPalettized;       /* Is the front buffer palettized? */
BOOL bPaletteActivate;         /* Is the front buffer's palette valid? */
BOOL bIgnoreWM_SIZE;           /* Ignore this WM_SIZE messages */
SIZE szLastClient;             /* Dimensions of the last window */
SIZE szBuffers;                /* Current buffer dimensions, not necessarily
                                  the same as the client window */
int CallbackRefCount;          /* How many times DeviceCreateCallback has
                                  been called in a row */

/***************************************************************************/
/*                               FUNCTIONS                                 */
/***************************************************************************/
/*
 * D3DAppCreateFromHWND
 */
BOOL D3DAppCreateFromHWND(DWORD flags, HWND hwnd,
                          BOOL(*DeviceCreateCallback)(int, int,
                                                      LPDIRECT3DVIEWPORT*,
                                                      LPVOID),
                          LPVOID lpCreateContext,
                          BOOL(*DeviceDestroyCallback)(LPVOID),
                          LPVOID lpDestroyContext,
                          D3DAppInfo** D3DApp)
{
    int driver, mode, w, h;
    /* 
     * Clean the global varaibles and check the flags
     */
    D3DAppISetDefaults();
    if (flags & D3DAPP_ONLYSYSTEMMEMORY) {
        d3dappi.bOnlySystemMemory = TRUE;
        d3dappi.bOnlyEmulation = TRUE;
    }
    if (flags & D3DAPP_ONLYD3DEMULATION)
        d3dappi.bOnlyEmulation = TRUE;
    /* 
     * Create DirectDraw, remember the Windows display mode and enumerate the
     * display modes
     */
    ATTEMPT(D3DAppICreateDD(d3dappi.bOnlyEmulation ?
                            D3DAPP_ONLYDDEMULATION : 0L));
    ATTEMPT(D3DAppIRememberWindowsMode());
    ATTEMPT(D3DAppIEnumDisplayModes());
    /*
     * Create Direct3D and enumerate the D3D drivers
     */
    ATTEMPT(D3DAppICreateD3D());
    ATTEMPT(D3DAppIEnumDrivers());
    /*
     * Set the device creation and destroy callback functions
     */
    D3DDeviceDestroyCallback = DeviceDestroyCallback;
    D3DDeviceDestroyCallbackContext = lpDestroyContext;
    D3DDeviceCreateCallback = DeviceCreateCallback;
    D3DDeviceCreateCallbackContext = lpCreateContext;
    *D3DApp = &d3dappi;
    d3dappi.hwnd = hwnd;
    /*
     * Choose a driver and display mode.  Using the current window is 
     * prefered, but a fullscreen mode may be selected.  Set the cooperative
     * level and create the front and back buffers for this mode.
     */
    driver = D3DAPP_YOUDECIDE;
    mode = D3DAPP_YOUDECIDE;
    ATTEMPT(D3DAppIVerifyDriverAndMode(&driver, &mode));
    D3DAppIGetClientWin(hwnd);
    if (mode == D3DAPP_USEWINDOW) {
        w = d3dappi.szClient.cx;
        h = d3dappi.szClient.cy;
        ATTEMPT(D3DAppISetCoopLevel(hwnd, FALSE));
        ATTEMPT(D3DAppICreateBuffers(hwnd, w, h, D3DAPP_BOGUS, FALSE));
    } else {
        szLastClient = d3dappi.szClient;
        w = d3dappi.Mode[mode].w;
        h = d3dappi.Mode[mode].h;
        d3dappi.szClient.cx = w; d3dappi.szClient.cy = h;
        ATTEMPT(D3DAppISetCoopLevel(hwnd, TRUE));
        ATTEMPT(D3DAppISetDisplayMode(w, h, d3dappi.Mode[mode].bpp));
        d3dappi.CurrMode = mode;
        ATTEMPT(D3DAppICreateBuffers(hwnd, w, h, d3dappi.Mode[mode].bpp, TRUE));
    }
    /*
     * If the front buffer is palettized, initialize its palette
     */
    ATTEMPT(D3DAppICheckForPalettized());
    /*
     * Create the Z-buffer
     */
    ATTEMPT(D3DAppICreateZBuffer(w, h, driver));
    /*
     * Create the D3D device, load the textures, call the device create
     * callback and set a default render state
     */
    ATTEMPT(D3DAppICreateDevice(driver));
    ATTEMPT(D3DAppIFilterDisplayModes(driver));  /* bThisDriverCanDo flags */
    ATTEMPT(D3DAppICallDeviceCreateCallback(w, h));
    ATTEMPT(D3DAppISetRenderState());
    /*
     * Ready to render
     */
    bD3DAppInitialized = TRUE;
    d3dappi.bRenderingIsOK = TRUE;

#ifdef SOFTWARE_ENABLE
	if( SoftwareVersion )
	{
		CWAfterModeSwitch();
	}
#endif
    return TRUE;

exit_with_error:
    D3DAppICallDeviceDestroyCallback();
    RELEASE(d3dappi.lpD3DDevice);
    RELEASE(d3dappi.lpZBuffer);
    RELEASE(lpPalette);
    RELEASE(lpClipper);
    RELEASE(d3dappi.lpBackBuffer);
    RELEASE(d3dappi.lpFrontBuffer);
    if (d3dappi.bFullscreen) {
        D3DAppIRestoreDispMode();
        D3DAppISetCoopLevel(hwnd, FALSE);
    }
    RELEASE(d3dappi.lpD3D);
    RELEASE(d3dappi.lpDD);
    return FALSE;
}   

/*
 * D3DAppFullscreen
 */
BOOL D3DAppFullscreen(int mode)
{
    int w, h, bpp;
    BOOL b; /* was already in a fullscreen mode? */

    d3dappi.bRenderingIsOK = FALSE;
    /* 
     * Make sure this is a valid request, otherwise doctor mode so it will
     * work with this driver.
     */
    ATTEMPT(D3DAppIVerifyDriverAndMode(&d3dappi.CurrDriver, &mode));
    /* 
     * Release everything
     */
    ATTEMPT(D3DAppICallDeviceDestroyCallback());
    if (d3dappi.bFullscreen) {
        ATTEMPT(D3DAppIClearBuffers());
    }
    RELEASE(d3dappi.lpD3DDevice);
    RELEASE(d3dappi.lpZBuffer);
    RELEASE(lpPalette);
    RELEASE(lpClipper);
    RELEASE(d3dappi.lpBackBuffer);
    RELEASE(d3dappi.lpFrontBuffer);
    /*
     * Record information about the current status
     */
    b = d3dappi.bFullscreen;
    w = d3dappi.Mode[mode].w;
    h = d3dappi.Mode[mode].h;
    bpp = d3dappi.Mode[mode].bpp;
    if (!b) {
        /*
         * If this is not a fullscreen mode, we'll need to record the window
         * size for when we return to it.
         */
        szLastClient = d3dappi.szClient;
    }
    /*
     * Set the cooperative level and create front and back buffers
     */
    d3dappi.szClient.cx = w; d3dappi.szClient.cy = h;

	InitModeCase();

    ATTEMPT(D3DAppISetCoopLevel(d3dappi.hwnd, TRUE));
    ATTEMPT(D3DAppISetDisplayMode(w, h, bpp));
    d3dappi.CurrMode = mode;
    ATTEMPT(D3DAppICreateBuffers(d3dappi.hwnd, w, h, bpp, TRUE));
    /*
     * If the front buffer is palettized, initialize its palette
     */
    ATTEMPT(D3DAppICheckForPalettized());
    /*
     * Create the Z-buffer
     */
    ATTEMPT(D3DAppICreateZBuffer(w, h, d3dappi.CurrDriver));
    /*
     * Create the D3D device, load the textures, call the device create
     * callback and set a default render state
     */
    ATTEMPT(D3DAppICreateDevice(d3dappi.CurrDriver));
    ATTEMPT(D3DAppICallDeviceCreateCallback(w, h));
    ATTEMPT(D3DAppISetRenderState());
    /* 
     * Set current mode
     */
    d3dappi.CurrMode = mode;
    d3dappi.bRenderingIsOK = TRUE;

#ifdef SOFTWARE_ENABLE
	if( SoftwareVersion )
	{
		CWAfterModeSwitch();
	}
#endif

    return TRUE;

exit_with_error:
    D3DAppICallDeviceDestroyCallback();
    RELEASE(d3dappi.lpD3DDevice);
    RELEASE(d3dappi.lpZBuffer);
    RELEASE(lpPalette);
    RELEASE(lpClipper);
    RELEASE(d3dappi.lpBackBuffer);
    RELEASE(d3dappi.lpFrontBuffer);
    if (!b) {
        D3DAppIRestoreDispMode();
        D3DAppISetCoopLevel(d3dappi.hwnd, FALSE);
    }
    return FALSE;
}

/*
 * D3DAppWindow
 */
BOOL
D3DAppWindow(int w, int h)
{
    BOOL b; /* changing from a fullscreen mode? */

    /*
	if (!d3dappi.bIsPrimary) {
        D3DAppISetErrorString("It is not possible to create a D3D window with a hardware DirectDraw device.  Check the bIsPrimary flag before calling D3DAppWindow.");
        return FALSE;
    }
	*/
	if ( !CanRenderWindowed )
	{
		Msg("this video card cannot render to a window\n");
		return FALSE;
	}

    b = d3dappi.bFullscreen;
    /*
     * If asked to set the window size, return it to the last value or use
     * a default value.
     */
    if (w == D3DAPP_YOUDECIDE) {
        w = b ? szLastClient.cx : D3DAPP_DEFAULTWINDOWDIM;
    }
    if (h == D3DAPP_YOUDECIDE) {
        h = b ? szLastClient.cy : D3DAPP_DEFAULTWINDOWDIM;
    }
    /*
     * Release everything
     */
    d3dappi.bRenderingIsOK = FALSE;
    ATTEMPT(D3DAppICallDeviceDestroyCallback());
    if (b) {
        ATTEMPT(D3DAppIClearBuffers());
    }
    RELEASE(d3dappi.lpD3DDevice);
    RELEASE(d3dappi.lpZBuffer);
    RELEASE(lpPalette);
    RELEASE(lpClipper);
    RELEASE(d3dappi.lpBackBuffer);
    RELEASE(d3dappi.lpFrontBuffer);
    /* 
     * Restore the display mode if we were in a fullscreen mode
     */
    if (b) {
        D3DAppIRestoreDispMode();
    }
    /* 
     * Set the cooperative level and create front and back buffers
     */
    D3DAppISetCoopLevel(d3dappi.hwnd, FALSE);
    D3DAppISetClientSize(d3dappi.hwnd, w, h, b);
    ATTEMPT(D3DAppICreateBuffers(d3dappi.hwnd, w, h, D3DAPP_BOGUS, FALSE));
    /*
     * If the front buffer is palettized, initialize its palette
     */
    ATTEMPT(D3DAppICheckForPalettized());
    /*
     * Create the Z-buffer
     */
    ATTEMPT(D3DAppICreateZBuffer(szBuffers.cx, szBuffers.cy,
                                 d3dappi.CurrDriver));
    /*
     * Create the D3D device, load the textures, call the device create
     * callback and set a default render state
     */
    ATTEMPT(D3DAppICreateDevice(d3dappi.CurrDriver));
    ATTEMPT(D3DAppICallDeviceCreateCallback(szBuffers.cx, szBuffers.cy));
    ATTEMPT(D3DAppISetRenderState());
    d3dappi.bRenderingIsOK = TRUE;
    return TRUE;

exit_with_error:
    D3DAppICallDeviceDestroyCallback();
    RELEASE(d3dappi.lpD3DDevice);
    RELEASE(d3dappi.lpZBuffer);
    RELEASE(lpPalette);
    RELEASE(lpClipper);
    RELEASE(d3dappi.lpBackBuffer);
    RELEASE(d3dappi.lpFrontBuffer);
    return FALSE;  
}


/*
 * D3DAppChangeDriver 
 */
BOOL
D3DAppChangeDriver(int driver, DWORD flags)
{
    int mode;

    /*
     * Verify the compatibility of this mode with the specified driver.
     * The mode may change.
     */
    if (d3dappi.bFullscreen)
        mode = d3dappi.CurrMode;
    else
        mode = D3DAPP_USEWINDOW;
    ATTEMPT(D3DAppIVerifyDriverAndMode(&driver, &mode));
    if (driver == D3DAPP_BOGUS || mode == D3DAPP_BOGUS)
        goto exit_with_error;
    /*
     * Update the current driver and set bThisDriverCanDo flags
     */
    d3dappi.CurrDriver = driver;
    ATTEMPT(D3DAppIFilterDisplayModes(driver));
    /*
     * Either call D3DAppWindow or D3DAppFullscreen depending on mode
     */
    if (mode == D3DAPP_USEWINDOW) {
        if (d3dappi.bFullscreen) {
            /*
             * We need to switch to a window.  D3DApp will either use the
             * size of the last window it saw or use a default size.
             */
            ATTEMPT(D3DAppWindow(D3DAPP_YOUDECIDE, D3DAPP_YOUDECIDE));
        } else {
            /*
             * We need to recreate the current window.  Don't let D3DApp
             * decide on the size.
             */
            ATTEMPT(D3DAppWindow(d3dappi.szClient.cx, d3dappi.szClient.cy));
        }
        /*
         * Change the currently selected mode if it's not compatible with
         * this driver.  Just to make sure that CurrMode is always a mode the
         * current driver can do.
         */
        if (!(d3dappi.Driver[driver].Desc.dwDeviceRenderBitDepth &
              D3DAppIBPPToDDBD(d3dappi.Mode[d3dappi.CurrMode].bpp))){
            ATTEMPT(D3DAppIPickDisplayMode(&d3dappi.CurrMode,
                        d3dappi.Driver[driver].Desc.dwDeviceRenderBitDepth));
        }
        return TRUE;
    } else {
        /*
         * We need to switch to fullscreen or switch fullscreen modes or stay
         * in the same fullscreen mode.  In any of these cases, we call the
         * same function.
         */
        ATTEMPT(D3DAppFullscreen(mode));
        return TRUE;
    }

exit_with_error:
    /*
     * The failed mode setting call would have released everything
     */
    return FALSE;
}


/*
 * D3DAppWindowProc
 */
BOOL
D3DAppWindowProc(BOOL* bStopProcessing, LRESULT* lresult, HWND hwnd,
                 UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    *bStopProcessing = FALSE;
    if (!bD3DAppInitialized)
        return TRUE;
    /*
     * Look for messages which effect rendering.  In some cases, we will not
     * want the app to continue processing the message, so set the flag and
     * provide a return value in lresult.
     */
    switch(message) {
		case WM_WINDOWPOSCHANGED:
            d3dappi.pClientOnPrimary.x = d3dappi.pClientOnPrimary.y = 0;
            ClientToScreen(hwnd, &d3dappi.pClientOnPrimary);
			SetCursorClip();
			break;
        case WM_SIZE:
#if 0
            if (!bIgnoreWM_SIZE) {
                /*
                 * Too long to fit here, see ddcalls.c. Updates the buffers
                 * and re-creates the device.
                 */
                ATTEMPT(D3DAppIHandleWM_SIZE(lresult, d3dappi.hwnd, message,
                                             wParam, lParam));
                *bStopProcessing = TRUE;
            }
#endif
            break;
        case WM_MOVE:
            /*
             * Update client window position information
             */
            d3dappi.pClientOnPrimary.x = d3dappi.pClientOnPrimary.y = 0;
            ClientToScreen(hwnd, &d3dappi.pClientOnPrimary);
            break;
#if 1
        case WM_MOUSEACTIVATE:
            if (d3dappi.bFullscreen && !d3dappi.bPaused) {
				*lresult = MA_ACTIVATEANDEAT;
                *bStopProcessing = TRUE;
				return TRUE;
			}
			break;
#endif
        case WM_ACTIVATE:
            /*
             * Set the front buffer's palette
             */
            if (bPaletteActivate && bPrimaryPalettized &&
                d3dappi.lpFrontBuffer) {
                d3dappi.lpFrontBuffer->lpVtbl->SetPalette(d3dappi.lpFrontBuffer,
                                                          lpPalette);
            }
			// handle cursor clipping
			if ( LOWORD( wParam ) == WA_INACTIVE )
			{
				cursorclipped = FALSE;
			}
			else
			{
				cursorclipped = !d3dappi.bPaused;
			}
			SetCursorClip();
            break;
        case WM_ACTIVATEAPP:
            d3dappi.bAppActive = (BOOL)wParam;
            break;
        case WM_SETCURSOR:
            /*
             * Prevent the cursor from being shown in fullscreen
             */
            if (d3dappi.bFullscreen && !d3dappi.bPaused) {
//                SetCursor(NULL);
                *lresult = 1;
                *bStopProcessing = TRUE;
                return TRUE;
            }
            break;
        case WM_MOVING:
            /*
             * Prevent the window from moving in fullscreen
             */
            if (d3dappi.bFullscreen) {
                GetWindowRect(hwnd, (LPRECT)lParam);
                *lresult = 1;
                *bStopProcessing = TRUE;
                return TRUE;
            }
            break;
        case WM_GETMINMAXINFO:
            /*
             * Ensure the window won't resize in fullscreen
             */
            if (d3dappi.bFullscreen) {
                ((LPMINMAXINFO)lParam)->ptMaxTrackSize.x= d3dappi.ThisMode.w;
                ((LPMINMAXINFO)lParam)->ptMaxTrackSize.y= d3dappi.ThisMode.h;
                ((LPMINMAXINFO)lParam)->ptMinTrackSize.x= d3dappi.ThisMode.w;
                ((LPMINMAXINFO)lParam)->ptMinTrackSize.y= d3dappi.ThisMode.h;
                *lresult = 0;
                *bStopProcessing = TRUE;
                return TRUE;
            } else {
                ((LPMINMAXINFO)lParam)->ptMaxTrackSize.x =
                                                    d3dappi.WindowsDisplay.w;
                ((LPMINMAXINFO)lParam)->ptMaxTrackSize.y =
                                                    d3dappi.WindowsDisplay.h;
                *lresult = 0;
                *bStopProcessing = TRUE;
                return TRUE;
            }
            break;
        case WM_PAINT:
            /*
             * Clear the rectangle and blt the backbuffer image
             */
            BeginPaint(hwnd, &ps);
            if (d3dappi.bRenderingIsOK && !d3dappi.bFullscreen) {
                D3DAppShowBackBuffer(D3DAPP_SHOWALL);
            }
            EndPaint(hwnd, &ps);
            *lresult = 1;
            *bStopProcessing = TRUE;
            return TRUE;
        case WM_NCPAINT:
            /*
             * When in fullscreen mode, don't draw the window frame.
             */
            if (d3dappi.bFullscreen && !d3dappi.bPaused) {
                *lresult = 0;
                *bStopProcessing = TRUE;
                return TRUE;
            }
            break;
    }
    return TRUE;

}


/*
 * D3DAppChangeTextureFormat
 */
BOOL
D3DAppChangeTextureFormat(int format)
{
    /*
     * Release all the textures, change the format and load them again
     */
    d3dappi.bRenderingIsOK = FALSE;
    d3dappi.CurrTextureFormat = format;
    memcpy(&d3dappi.ThisTextureFormat, &d3dappi.TextureFormat[format],
           sizeof(D3DAppTextureFormat));
	TexturePalettized = d3dappi.ThisTextureFormat.bPalettized;
	TextureRedBPP = d3dappi.ThisTextureFormat.RedBPP;
	TextureGreenBPP = d3dappi.ThisTextureFormat.GreenBPP;
	TextureBlueBPP = d3dappi.ThisTextureFormat.BlueBPP;
	TextureAlphaBPP = d3dappi.ThisTextureFormat.AlphaBPP;
	TextureIndexBPP = d3dappi.ThisTextureFormat.IndexBPP;
    d3dappi.bRenderingIsOK = TRUE;
    return TRUE;

}



/*
 * D3DAppSetRenderState
 */
BOOL
D3DAppSetRenderState(D3DAppRenderState* lpState)
{
    /*
     * If none was provided, reset the current render state.
     */
    if (!lpState)
        lpState = &d3dapprs;
    /*
     * Record this render state and set it.
     */
    if (lpState != &d3dapprs)
        memcpy(&d3dapprs, lpState, sizeof(D3DAppRenderState));
    if (d3dappi.bRenderingIsOK) {
        ATTEMPT(D3DAppISetRenderState());
    }
    return TRUE;

exit_with_error:
    return FALSE;
}

/*
 * D3DAppGetRenderState
 */
BOOL
D3DAppGetRenderState(D3DAppRenderState* lpState)
{
    memcpy(lpState, &d3dapprs, sizeof(D3DAppRenderState));
    return TRUE;
}

/*
 * D3DAppShowBackBuffer
 */
BOOL
D3DAppShowBackBuffer(DWORD flags)
{
    if (!d3dappi.bRenderingIsOK) {
        D3DAppISetErrorString("Cannot call D3DAppShowBackBuffer while bRenderingIsOK is FALSE.\n");
        return FALSE;
    }
    if (d3dappi.bPaused)
        return TRUE;

#ifdef SOFTWARE_ENABLE
	if( SoftwareVersion )
	{
/*-----------------------------------------------------------------------------
	Chris Walsh's Code
-----------------------------------------------------------------------------*/
		// SETUP V TABLE.

		if (d3dappi.bFullscreen)
		{  
		//   . . . . . . . . . F U L L S C R E E N     M O D E . . . . . . . . . . . 

		// LOCK THE BACK BUFFER.

			if ( (SurfBpp!=8 && SurfBpp!=16) ) //|| (SurfBpp==16 && CWInTitle) )
			{
				CWInTitle = 0;
				ClrOT();

				LastError = d3dappi.lpFrontBuffer->lpVtbl->Flip(d3dappi.lpFrontBuffer,
															d3dappi.lpBackBuffer,
															0);
					
				if (LastError == DDERR_SURFACELOST)
				{
				 d3dappi.lpFrontBuffer->lpVtbl->Restore(d3dappi.lpFrontBuffer);
				 d3dappi.lpBackBuffer->lpVtbl->Restore(d3dappi.lpBackBuffer);
				 //D3DAppIClearBuffers();
				}
				else if (LastError != DD_OK)
				{
				   return TRUE; //FALSE;
				}

				return TRUE;
			}

			SetVTables();
			if( CWInTitle )
			{
				zRW = 1;
			}
			SWRendView();
			d3dappi.lpBackBuffer->lpVtbl->Unlock( d3dappi.lpBackBuffer, NULL );

			if( CWInTitle )
			{
				ProcessTextItems();
			}
			else
			{
				if( (MyGameStatus == STATUS_Normal) || (MyGameStatus == STATUS_PlayingDemo) ||(MyGameStatus == STATUS_SinglePlayer) )
				{
					if( Our_CalculateFrameRate() != TRUE)
						return FALSE;

					if( CurrentMenu && CurrentMenuItem )
					{
						MenuDraw( CurrentMenu );
						MenuItemDrawCursor( CurrentMenuItem );

						if ( DrawSimplePanel )
							TestBlt();
						MenuProcess();
						// Just to make sure that another press of escape doesnt take you back into the menu you wanted to exit!!
						JustExitedMenu = TRUE;
					}
					else
					{
						if( !ServerMode )
						{
							TestBlt();
						}
				//		TaskDispatch();
					}
				}
			}

			CWInTitle = 0;
			Highestz = 1;				//cw: for next time round.
#if 0
			if (SurfWidth == 320 && SurfHeight == 240)
			{
				if (!DrawnYet || (SurfWidth==320 && SurfHeight==240))
		   		LastError = d3dappi.lpFrontBuffer->lpVtbl->Flip(d3dappi.lpFrontBuffer,
															d3dappi.lpBackBuffer,
															0);
				if (LastError == DDERR_SURFACELOST)
				{
				 d3dappi.lpFrontBuffer->lpVtbl->Restore(d3dappi.lpFrontBuffer);
				 d3dappi.lpBackBuffer->lpVtbl->Restore(d3dappi.lpBackBuffer);
				 //D3DAppIClearBuffers();
				}
				else if (LastError != DD_OK)
				{
				   return TRUE; //FALSE;
				}
			}
			else
			{
				CWStretchBlit( SurfWidth, SurfHeight, LineWidth, ScreenBase); // Stretch it up..
			}
#else
			CWFlip();
#endif
		}
/*---------------------------------------------------------------------------*/
	}
	else
#endif
	{
		if (d3dappi.bFullscreen) {  
			/*
			 * Flip the back and front buffers
			 */
			LastError = d3dappi.lpFrontBuffer->lpVtbl->Flip(d3dappi.lpFrontBuffer,
															d3dappi.lpBackBuffer,
															1);
	//        LastError = d3dappi.lpFrontBuffer->lpVtbl->Flip(d3dappi.lpFrontBuffer,
	//                                                        NULL,
	//                                                        DDFLIP_WAIT );
			if (LastError == DDERR_SURFACELOST) {
				d3dappi.lpFrontBuffer->lpVtbl->Restore(d3dappi.lpFrontBuffer);
				d3dappi.lpBackBuffer->lpVtbl->Restore(d3dappi.lpBackBuffer);
				D3DAppIClearBuffers();
			} else if (LastError != DD_OK) {
				//D3DAppISetErrorString("Flipping complex display surface failed.\n%s", D3DAppErrorToString(LastError));
				//return FALSE;
				return TRUE;
			}
		} else {
			RECT front;
			RECT buffer;
			/*
			 * Set the rectangle to blt from the back to front bufer ..Set to entire client window
			 */
			SetRect(&buffer, 0, 0, d3dappi.szClient.cx,
					d3dappi.szClient.cy);
			SetRect(&front,
					d3dappi.pClientOnPrimary.x, d3dappi.pClientOnPrimary.y,
					d3dappi.szClient.cx + d3dappi.pClientOnPrimary.x,
					d3dappi.szClient.cy + d3dappi.pClientOnPrimary.y);
			/*
			 * Blt the list of rectangles from the back to front buffer
			 */
			LastError =	d3dappi.lpFrontBuffer->lpVtbl->Blt(d3dappi.lpFrontBuffer,
												 &front, d3dappi.lpBackBuffer,
												 &buffer, DDBLT_WAIT , NULL);
			if (LastError == DDERR_SURFACELOST) {
				d3dappi.lpFrontBuffer->lpVtbl->Restore(d3dappi.lpFrontBuffer);
				d3dappi.lpBackBuffer->lpVtbl->Restore(d3dappi.lpBackBuffer);
				D3DAppIClearBuffers();
			} else if (LastError != DD_OK) {
				D3DAppISetErrorString("Blt of back buffer to front buffer failed.\n%s", D3DAppErrorToString(LastError));
				return FALSE;
			}
		}
	}
    return TRUE;
}


/*
 * D3DAppClearScreenOnly
 */
BOOL
D3DAppClearScreenOnly()
{
    int clearflags;
    D3DRECT dummy;

#ifdef SOFTWARE_ENABLE
	if( SoftwareVersion )
	{
		CWClearScreen();
		return( TRUE );
	}
#endif

    if (!d3dappi.bRenderingIsOK)
	{
        D3DAppISetErrorString("Cannot call D3DAppClearBackBuffer while bRenderingIsOK is FALSE.\n");
        return FALSE;
    }
    /*
     * clear just back buffer
     */
	clearflags = D3DCLEAR_TARGET;

	if( clearflags != 0 )
	{
		dummy.x1 = dummy.y1 = 0;
		dummy.x2 = d3dappi.szClient.cx;
		dummy.y2 = d3dappi.szClient.cy;
		LastError =d3dappi.lpD3DViewport->lpVtbl->Clear(d3dappi.lpD3DViewport,
														1, &dummy,
		                                                clearflags);
		if (LastError != D3D_OK)
		{
		    D3DAppISetErrorString("Viewport clear failed.\n%s",
		                          D3DAppErrorToString(LastError));
		    return FALSE;
		}
	}
    return TRUE;
}


/*
 * D3DAppCheckForLostSurfaces
 */
#define CHECKSURF(x) if (x) {                                               \
                        if (x->lpVtbl->IsLost(x) == DDERR_SURFACELOST) {    \
                            LastError = x->lpVtbl->Restore(x);              \
                            if (LastError != DD_OK) goto exit_with_error;   \
                            b = TRUE;                                       \
                        }                                                   \
                     }
BOOL
D3DAppCheckForLostSurfaces(void)
{
    BOOL b = FALSE;
    /*
     * Check all the surfaces D3DApp owns and restore them if lost.
     */
    CHECKSURF(d3dappi.lpFrontBuffer);
    CHECKSURF(d3dappi.lpBackBuffer);
    CHECKSURF(d3dappi.lpZBuffer);
    if (b) {
        /*
         * If any of the surfaces were lost and restored, clear all the buffers.
         * If this fails, that's fine, just move on.
         */
        D3DAppIClearBuffers();
    }
    return TRUE;

exit_with_error:
    D3DAppISetErrorString("Restoring of a lost surface failed.\n%s",
                          D3DAppErrorToString(LastError));
    return FALSE;
}

/*
 * D3DAppPause
 */
BOOL
D3DAppPause(BOOL flag)
{
    static int pausecount;

    /*
     * Keep a count of the number of times D3DAppPause has been called to 
     * prevent pausing more than once in a row.
     */
    if (pausecount != 0) {
        if (flag) {
            ++pausecount;
            return TRUE;
        } else {
            --pausecount;
            if (pausecount != 0)
                return TRUE;
        } 
    }

    d3dappi.bPaused = flag;
    if (!flag) {
        /*
         * Returning from a pause
         */
        if (d3dappi.bFullscreen && bPrimaryPalettized && lpPalette) {
            /*
             * Set front buffer's palette back to what it was before pause
             */
            LastError = lpPalette->lpVtbl->SetEntries(lpPalette, 0, 0, 256,
                                                      &ppe[0]);
            if (LastError != DD_OK) {
                D3DAppISetErrorString("Setting palette entries during unpause failed.\n%s", D3DAppErrorToString(LastError));
                goto exit_with_error;
            }
        }
    }
    if (flag && d3dappi.bFullscreen) {
        /*
         * Pausing in a fullscreen mode
         */
        if (bPrimaryPalettized && lpPalette) {
            /*
             * Save the front buffer's current palette and restore the
             * original Windows palette.
             */
            int i;
            LastError = lpPalette->lpVtbl->GetEntries(lpPalette, 0, 0, 256,
                                                      &ppe[0]);
            if (LastError != DD_OK) {
                D3DAppISetErrorString("Getting palette entries before a pause failed.\n%s", D3DAppErrorToString(LastError));
                goto exit_with_error;
            }
            for (i = 10; i < 246; i++)
                Originalppe[i] = ppe[i];
            LastError = lpPalette->lpVtbl->SetEntries(lpPalette, 0, 0, 256,
                                                      &Originalppe[0]);
            if (LastError != DD_OK) {
                D3DAppISetErrorString("Returning palette entries to defaults failed.\n%s", D3DAppErrorToString(LastError));
                goto exit_with_error;
            }
        }
        /*
         * Flip to GDI surface (either front or back buffer)
         */
        if (d3dappi.lpDD) {
//        if (d3dappi.bIsPrimary && d3dappi.lpDD) {
            LastError = d3dappi.lpDD->lpVtbl->FlipToGDISurface(d3dappi.lpDD);
            if (LastError != DD_OK) {
                D3DAppISetErrorString("Flipping to GDI surface failed.\n%s", D3DAppErrorToString(LastError));
                goto exit_with_error;
            }
        }
        /*
         * Draw the menu and frame
         */
        DrawMenuBar(d3dappi.hwnd);
        RedrawWindow(d3dappi.hwnd, NULL, NULL, RDW_FRAME);
    }
    return TRUE;
exit_with_error:
    return FALSE;
}

/*
 * D3DAppCreateSurface
 */
BOOL
D3DAppCreateSurface(DDSURFACEDESC *ddsd, LPDIRECTDRAWSURFACE *lplpSurf)
{
    return D3DAppICreateSurface(ddsd, lplpSurf);
}

/*
 * D3DAppLastError
 */
HRESULT
D3DAppLastError(void)
{
    return LastError;  
}

/*
 * D3DAppLastD3DAppISetErrorString
 */
char*
D3DAppLastErrorString(void)
{
    return LastErrorString;
}


/*
 * D3DAppDestroy
 */
BOOL
D3DAppDestroy(void)
{
    /*
     * Destroys all objects including Direct Draw.
     */
    d3dappi.bRenderingIsOK = FALSE;
    d3dappi.hwnd = NULL;
    ATTEMPT(D3DAppICallDeviceDestroyCallback());
    RELEASE(d3dappi.lpD3DDevice);
    RELEASE(d3dappi.lpZBuffer);
    RELEASE(lpPalette);
    RELEASE(lpClipper);
    RELEASE(d3dappi.lpBackBuffer);
    RELEASE(d3dappi.lpFrontBuffer);
    if (d3dappi.bFullscreen) {
        D3DAppIRestoreDispMode();
        D3DAppISetCoopLevel(d3dappi.hwnd, FALSE);
    }
    D3DAppIReleasePathList();
    RELEASE(d3dappi.lpD3D);
    RELEASE(d3dappi.lpDD);
    return TRUE;
exit_with_error:
    return FALSE;
}


/*
 * D3DAppErrorToString
 */
char*
D3DAppErrorToString(HRESULT error)
{
    switch(error) {
        case DD_OK:
            return "No error.\0";
        case DDERR_ALREADYINITIALIZED:
            return "This object is already initialized.\0";
        case DDERR_BLTFASTCANTCLIP:
            return "Return if a clipper object is attached to the source surface passed into a BltFast call.\0";
        case DDERR_CANNOTATTACHSURFACE:
            return "This surface can not be attached to the requested surface.\0";
        case DDERR_CANNOTDETACHSURFACE:
            return "This surface can not be detached from the requested surface.\0";
        case DDERR_CANTCREATEDC:
            return "Windows can not create any more DCs.\0";
        case DDERR_CANTDUPLICATE:
            return "Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.\0";
        case DDERR_CLIPPERISUSINGHWND:
            return "An attempt was made to set a cliplist for a clipper object that is already monitoring an hwnd.\0";
        case DDERR_COLORKEYNOTSET:
            return "No src color key specified for this operation.\0";
        case DDERR_CURRENTLYNOTAVAIL:
            return "Support is currently not available.\0";
        case DDERR_DIRECTDRAWALREADYCREATED:
            return "A DirectDraw object representing this driver has already been created for this process.\0";
        case DDERR_EXCEPTION:
            return "An exception was encountered while performing the requested operation.\0";
        case DDERR_EXCLUSIVEMODEALREADYSET:
            return "An attempt was made to set the cooperative level when it was already set to exclusive.\0";
        case DDERR_GENERIC:
            return "Generic failure.\0";
        case DDERR_HEIGHTALIGN:
            return "Height of rectangle provided is not a multiple of reqd alignment.\0";
        case DDERR_HWNDALREADYSET:
            return "The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes created.\0";
        case DDERR_HWNDSUBCLASSED:
            return "HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.\0";
        case DDERR_IMPLICITLYCREATED:
            return "This surface can not be restored because it is an implicitly created surface.\0";
        case DDERR_INCOMPATIBLEPRIMARY:
            return "Unable to match primary surface creation request with existing primary surface.\0";
        case DDERR_INVALIDCAPS:
            return "One or more of the caps bits passed to the callback are incorrect.\0";
        case DDERR_INVALIDCLIPLIST:
            return "DirectDraw does not support the provided cliplist.\0";
        case DDERR_INVALIDDIRECTDRAWGUID:
            return "The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.\0";
        case DDERR_INVALIDMODE:
            return "DirectDraw does not support the requested mode.\0";
        case DDERR_INVALIDOBJECT:
            return "DirectDraw received a pointer that was an invalid DIRECTDRAW object.\0";
        case DDERR_INVALIDPARAMS:
            return "One or more of the parameters passed to the function are incorrect.\0";
        case DDERR_INVALIDPIXELFORMAT:
            return "The pixel format was invalid as specified.\0";
        case DDERR_INVALIDPOSITION:
            return "Returned when the position of the overlay on the destination is no longer legal for that destination.\0";
        case DDERR_INVALIDRECT:
            return "Rectangle provided was invalid.\0";
        case DDERR_LOCKEDSURFACES:
            return "Operation could not be carried out because one or more surfaces are locked.\0";
        case DDERR_NO3D:
            return "There is no 3D present.\0";
        case DDERR_NOALPHAHW:
            return "Operation could not be carried out because there is no alpha accleration hardware present or available.\0";
        case DDERR_NOBLTHW:
            return "No blitter hardware present.\0";
        case DDERR_NOCLIPLIST:
            return "No cliplist available.\0";
        case DDERR_NOCLIPPERATTACHED:
            return "No clipper object attached to surface object.\0";
        case DDERR_NOCOLORCONVHW:
            return "Operation could not be carried out because there is no color conversion hardware present or available.\0";
        case DDERR_NOCOLORKEY:
            return "Surface doesn't currently have a color key\0";
        case DDERR_NOCOLORKEYHW:
            return "Operation could not be carried out because there is no hardware support of the destination color key.\0";
        case DDERR_NOCOOPERATIVELEVELSET:
            return "Create function called without DirectDraw object method SetCooperativeLevel being called.\0";
        case DDERR_NODC:
            return "No DC was ever created for this surface.\0";
        case DDERR_NODDROPSHW:
            return "No DirectDraw ROP hardware.\0";
        case DDERR_NODIRECTDRAWHW:
            return "A hardware-only DirectDraw object creation was attempted but the driver did not support any hardware.\0";
        case DDERR_NOEMULATION:
            return "Software emulation not available.\0";
        case DDERR_NOEXCLUSIVEMODE:
            return "Operation requires the application to have exclusive mode but the application does not have exclusive mode.\0";
        case DDERR_NOFLIPHW:
            return "Flipping visible surfaces is not supported.\0";
        case DDERR_NOGDI:
            return "There is no GDI present.\0";
        case DDERR_NOHWND:
            return "Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.\0";
        case DDERR_NOMIRRORHW:
            return "Operation could not be carried out because there is no hardware present or available.\0";
        case DDERR_NOOVERLAYDEST:
            return "Returned when GetOverlayPosition is called on an overlay that UpdateOverlay has never been called on to establish a destination.\0";
        case DDERR_NOOVERLAYHW:
            return "Operation could not be carried out because there is no overlay hardware present or available.\0";
        case DDERR_NOPALETTEATTACHED:
            return "No palette object attached to this surface.\0";
        case DDERR_NOPALETTEHW:
            return "No hardware support for 16 or 256 color palettes.\0";
        case DDERR_NORASTEROPHW:
            return "Operation could not be carried out because there is no appropriate raster op hardware present or available.\0";
        case DDERR_NOROTATIONHW:
            return "Operation could not be carried out because there is no rotation hardware present or available.\0";
        case DDERR_NOSTRETCHHW:
            return "Operation could not be carried out because there is no hardware support for stretching.\0";
        case DDERR_NOT4BITCOLOR:
            return "DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.\0";
        case DDERR_NOT4BITCOLORINDEX:
            return "DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index palette.\0";
        case DDERR_NOT8BITCOLOR:
            return "DirectDrawSurface is not in 8 bit color mode and the requested operation requires 8 bit color.\0";
        case DDERR_NOTAOVERLAYSURFACE:
            return "Returned when an overlay member is called for a non-overlay surface.\0";
        case DDERR_NOTEXTUREHW:
            return "Operation could not be carried out because there is no texture mapping hardware present or available.\0";
        case DDERR_NOTFLIPPABLE:
            return "An attempt has been made to flip a surface that is not flippable.\0";
        case DDERR_NOTFOUND:
            return "Requested item was not found.\0";
        case DDERR_NOTLOCKED:
            return "Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has been attempted.\0";
        case DDERR_NOTPALETTIZED:
            return "The surface being used is not a palette-based surface.\0";
        case DDERR_NOVSYNCHW:
            return "Operation could not be carried out because there is no hardware support for vertical blank synchronized operations.\0";
        case DDERR_NOZBUFFERHW:
            return "Operation could not be carried out because there is no hardware support for zbuffer blitting.\0";
        case DDERR_NOZOVERLAYHW:
            return "Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z layering of overlays.\0";
        case DDERR_OUTOFCAPS:
            return "The hardware needed for the requested operation has already been allocated.\0";
        case DDERR_OUTOFMEMORY:
            return "DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OUTOFVIDEOMEMORY:
            return "DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OVERLAYCANTCLIP:
            return "The hardware does not support clipped overlays.\0";
        case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
            return "Can only have ony color key active at one time for overlays.\0";
        case DDERR_OVERLAYNOTVISIBLE:
            return "Returned when GetOverlayPosition is called on a hidden overlay.\0";
        case DDERR_PALETTEBUSY:
            return "Access to this palette is being refused because the palette is already locked by another thread.\0";
        case DDERR_PRIMARYSURFACEALREADYEXISTS:
            return "This process already has created a primary surface.\0";
        case DDERR_REGIONTOOSMALL:
            return "Region passed to Clipper::GetClipList is too small.\0";
        case DDERR_SURFACEALREADYATTACHED:
            return "This surface is already attached to the surface it is being attached to.\0";
        case DDERR_SURFACEALREADYDEPENDENT:
            return "This surface is already a dependency of the surface it is being made a dependency of.\0";
        case DDERR_SURFACEBUSY:
            return "Access to this surface is being refused because the surface is already locked by another thread.\0";
        case DDERR_SURFACEISOBSCURED:
            return "Access to surface refused because the surface is obscured.\0";
        case DDERR_SURFACELOST:
            return "Access to this surface is being refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have Restore called on it.\0";
        case DDERR_SURFACENOTATTACHED:
            return "The requested surface is not attached.\0";
        case DDERR_TOOBIGHEIGHT:
            return "Height requested by DirectDraw is too large.\0";
        case DDERR_TOOBIGSIZE:
            return "Size requested by DirectDraw is too large, but the individual height and width are OK.\0";
        case DDERR_TOOBIGWIDTH:
            return "Width requested by DirectDraw is too large.\0";
        case DDERR_UNSUPPORTED:
            return "Action not supported.\0";
        case DDERR_UNSUPPORTEDFORMAT:
            return "FOURCC format requested is unsupported by DirectDraw.\0";
        case DDERR_UNSUPPORTEDMASK:
            return "Bitmask in the pixel format requested is unsupported by DirectDraw.\0";
        case DDERR_VERTICALBLANKINPROGRESS:
            return "Vertical blank is in progress.\0";
        case DDERR_WASSTILLDRAWING:
            return "Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is incomplete.\0";
        case DDERR_WRONGMODE:
            return "This surface can not be restored because it was created in a different mode.\0";
        case DDERR_XALIGN:
            return "Rectangle provided was not horizontally aligned on required boundary.\0";
        case D3DERR_BADMAJORVERSION:
            return "D3DERR_BADMAJORVERSION\0";
        case D3DERR_BADMINORVERSION:
            return "D3DERR_BADMINORVERSION\0";
        case D3DERR_EXECUTE_LOCKED:
            return "D3DERR_EXECUTE_LOCKED\0";
        case D3DERR_EXECUTE_NOT_LOCKED:
            return "D3DERR_EXECUTE_NOT_LOCKED\0";
        case D3DERR_EXECUTE_CREATE_FAILED:
            return "D3DERR_EXECUTE_CREATE_FAILED\0";
        case D3DERR_EXECUTE_DESTROY_FAILED:
            return "D3DERR_EXECUTE_DESTROY_FAILED\0";
        case D3DERR_EXECUTE_LOCK_FAILED:
            return "D3DERR_EXECUTE_LOCK_FAILED\0";
        case D3DERR_EXECUTE_UNLOCK_FAILED:
            return "D3DERR_EXECUTE_UNLOCK_FAILED\0";
        case D3DERR_EXECUTE_FAILED:
            return "D3DERR_EXECUTE_FAILED\0";
        case D3DERR_EXECUTE_CLIPPED_FAILED:
            return "D3DERR_EXECUTE_CLIPPED_FAILED\0";
        case D3DERR_TEXTURE_NO_SUPPORT:
            return "D3DERR_TEXTURE_NO_SUPPORT\0";
        case D3DERR_TEXTURE_NOT_LOCKED:
            return "D3DERR_TEXTURE_NOT_LOCKED\0";
        case D3DERR_TEXTURE_LOCKED:
            return "D3DERR_TEXTURELOCKED\0";
        case D3DERR_TEXTURE_CREATE_FAILED:
            return "D3DERR_TEXTURE_CREATE_FAILED\0";
        case D3DERR_TEXTURE_DESTROY_FAILED:
            return "D3DERR_TEXTURE_DESTROY_FAILED\0";
        case D3DERR_TEXTURE_LOCK_FAILED:
            return "D3DERR_TEXTURE_LOCK_FAILED\0";
        case D3DERR_TEXTURE_UNLOCK_FAILED:
            return "D3DERR_TEXTURE_UNLOCK_FAILED\0";
        case D3DERR_TEXTURE_LOAD_FAILED:
            return "D3DERR_TEXTURE_LOAD_FAILED\0";
        case D3DERR_MATRIX_CREATE_FAILED:
            return "D3DERR_MATRIX_CREATE_FAILED\0";
        case D3DERR_MATRIX_DESTROY_FAILED:
            return "D3DERR_MATRIX_DESTROY_FAILED\0";
        case D3DERR_MATRIX_SETDATA_FAILED:
            return "D3DERR_MATRIX_SETDATA_FAILED\0";
        case D3DERR_SETVIEWPORTDATA_FAILED:
            return "D3DERR_SETVIEWPORTDATA_FAILED\0";
        case D3DERR_MATERIAL_CREATE_FAILED:
            return "D3DERR_MATERIAL_CREATE_FAILED\0";
        case D3DERR_MATERIAL_DESTROY_FAILED:
            return "D3DERR_MATERIAL_DESTROY_FAILED\0";
        case D3DERR_MATERIAL_SETDATA_FAILED:
            return "D3DERR_MATERIAL_SETDATA_FAILED\0";
        case D3DERR_LIGHT_SET_FAILED:
            return "D3DERR_LIGHT_SET_FAILED\0";
        default:
            return "Unrecognized error value.\0";
    }
}
