// HelloCPlusPlus.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HttpExt.h"
#include <string>

BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO *pVer) {
	pVer->dwExtensionVersion = HSE_VERSION;
	strncpy_s(pVer->lpszExtensionDesc,
		HSE_MAX_EXT_DLL_NAME_LEN,
		"Hello ISAPI Extension", _TRUNCATE);
	return TRUE;
}

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK *pECB) {
	const char *header = "<html>"
		"<head>"
		"<title>Hello from ISAPI</title>"
		"</head>"
		"<body>"
		"<h1>Hello from an ISAPI Extension</h1>";

	DWORD size = static_cast< DWORD >(strlen(header));
	pECB->WriteClient(pECB->ConnID, const_cast<char*>(header), &size, 0);

	const char *intro = "<p>Your name is: ";
	size = static_cast< DWORD >(strlen(intro));
	pECB->WriteClient(pECB->ConnID, const_cast<char*>(intro), &size, 0);
	size = static_cast< DWORD >(
		strlen(pECB->lpszQueryString));
	pECB->WriteClient(pECB->ConnID, pECB->lpszQueryString,

		&size, 0);

	const char *footer = "</p></body></html>";

	size = static_cast< DWORD >(strlen(footer));
	pECB->WriteClient(pECB->ConnID, const_cast<char*>(footer), &size, 0);

	return HSE_STATUS_SUCCESS;
}

BOOL WINAPI TerminateExtension(DWORD dwFlags) {
	return TRUE;
}