#include <stdlib.h>
#include <time.h>
#include <string>
#include <Windows.h>
using namespace std;

enum makros{
	
};

int min1 = 10, max1 = 335, zufall1;
int min2 = 10, max2 = 239, zufall2;
HWND hButton;

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

void initWndClassEx( WNDCLASSEX &WndClassEx, HINSTANCE &hInstance, const char* szClassName );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow ){
	
	WNDCLASSEX	WndClassEx;
	MSG			msg;
	HWND		hWnd;

	initWndClassEx( WndClassEx, hInstance, "WndClassEx" );

	hWnd = CreateWindowEx( WS_EX_CLIENTEDGE, "WndClassEx", "Du hast Langeweile | © 2012 by Robin Buck", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
							CW_USEDEFAULT, CW_USEDEFAULT, 400, 300, NULL, NULL, hInstance, NULL );

	ShowWindow( hWnd, iCmdShow );
	//UpdateWindow( hWnd );

	while( GetMessage( &msg, hWnd, NULL, NULL ) > NULL ){
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}

	return 0;
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ){
	switch( msg ){
	case WM_CREATE:
		srand(time(NULL));
		hButton = CreateWindow( "button", "Klick!", WS_CHILD | WS_VISIBLE, 10, 10, 45, 20, hWnd, (HMENU)0, NULL, NULL );
		break;
	case WM_COMMAND:
		switch(wParam){
		case 0:
			zufall1 = min1 + rand() % ( max1 - min1 + 1 );
			zufall2 = min2 + rand() % ( max2 - min2 + 1 );
			DestroyWindow(hButton);
			hButton = CreateWindow( "button", "Klick!", WS_CHILD | WS_VISIBLE, zufall1, zufall2, 45, 20, hWnd, (HMENU)0, NULL, NULL );
			break;
		}
		break;
	default:
		return DefWindowProc( hWnd, msg, wParam, lParam );
	}
}

void initWndClassEx( WNDCLASSEX &WndClassEx, HINSTANCE &hInstance, const char* szClassName ){
	WndClassEx.cbSize			= sizeof( WNDCLASSEX );
	WndClassEx.style			= NULL;
	WndClassEx.lpfnWndProc		= WndProc;
	WndClassEx.cbClsExtra		= NULL;
	WndClassEx.cbWndExtra		= NULL;
	WndClassEx.hInstance		= hInstance;
	WndClassEx.hIcon			= NULL;
	WndClassEx.hCursor			= NULL;
	WndClassEx.hbrBackground	= GetSysColorBrush( COLOR_3DFACE );
	WndClassEx.lpszMenuName		= NULL;
	WndClassEx.lpszClassName	= szClassName;
	WndClassEx.hIconSm			= NULL;

	if( !RegisterClassEx( &WndClassEx ) ){
		MessageBox( NULL, "Die Registrierung der WndClassEx-Klasse hat fehlgeschlagen.", "Fehlermeldung", MB_OK | MB_ICONERROR );
	}
}