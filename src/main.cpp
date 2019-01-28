// We include some general things here to support our example.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <chrono>
#include <codecvt>
#include <d3d9.h>
#include <d3dx9core.h>
#include <string>
#include <thread>
#include "resource.h"

// This is our add-on include file
#include "../include/gw2addon-native.h"

using namespace std;

// Just a few states
HMODULE dllModule;
bool loader = false;
string apiKey;
HWND focusWindow;
IDirect3DDevice9* device;
int frame = 0;

// Forward declare a few functions in order to make this file an easier read
GW2ADDON_RESULT GW2ADDON_CALL Load(HWND hFocusWindow, IDirect3DDevice9* pDev);

//***************************************
// The actual implementation starts here
//***************************************

GW2AddonAPIV1* GW2ADDON_CALL GW2AddonInitialize(int loaderVersion) {
	// This is called whenever the add-on loader needs the information about your add-on.
	// So we export our information that's statically defined.
	// Refer to the header file for all possible fields.
	static GW2AddonAPIV1 addon;
	addon.id = "arcdps-updater";
	addon.name = "ArcDps Updater";
	addon.author = "Greaka";
	addon.version = "1.0";
	addon.description = "When activated, this addon will automatically update arcdps and selected plugins on startup when there is an update available.";
	addon.homepage = "https://github.com/greaka/addon-loader-arcdps-updater";
	addon.Load = &Load;
	addon.updateInfo.method = AddonUpdateMethod::GithubReleasesUpdateMethod;
	addon.updateInfo.githubRepo = "greaka/addon-loader-arcdps-updater";

	HRSRC hIconResInfo = FindResource(dllModule, MAKEINTRESOURCE(IDB_PNG1), L"PNG");
	HGLOBAL hIconRes = hIconResInfo ? LoadResource(dllModule, hIconResInfo) : NULL;
	if (hIconRes) {
		addon.icon = LockResource(hIconRes);
		addon.iconSize = SizeofResource(dllModule, hIconResInfo);
	}

	return &addon;
}

void GW2ADDON_CALL GW2AddonRelease() {
	// This is called whenever the add-on is being unloaded.
	// So do not neglect this and clean up your stuff.
	focusWindow = NULL;
	device = NULL;
}

GW2ADDON_RESULT GW2ADDON_CALL Load(HWND hFocusWindow, IDirect3DDevice9* pDev) {
	// Our loading entrypoint.
	// This is called before the add-on is activated.
	// You can initialize whatever you want to initialize here.
	focusWindow = hFocusWindow;
	device = pDev;

	// We return 0 on success.
	return 0;
}
