#include "pch.h"
#include "httprequest.h"


constexpr wchar_t apihost[] = L"api.snapgenshin.com";
constexpr wchar_t apipath[] = L"/client/UnlockerIsland_Compact2_5.6.0.json";

void httprequest(std::vector<char>* config)
{
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL bResults = FALSE;
    HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;
    DWORD POLICY = WINHTTP_OPTION_REDIRECT_POLICY_ALWAYS;
    hSession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, NULL);
    if (hSession)
        hConnect = WinHttpConnect(hSession, apihost, INTERNET_DEFAULT_HTTPS_PORT, NULL);

    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect, L"GET", apipath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    if (hRequest) {
        //WinHttpSetOption(hRequest, WINHTTP_OPTION_REDIRECT_POLICY, &POLICY, sizeof(POLICY));
        bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
    }
    if (!bResults)
        printf("Error %d has occurred.\n", GetLastError());
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);

    if (bResults)
    {
        do
        {
            // Check for available data.
            dwSize = 0;
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());

            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize + 1];

            // Read the data.
            ZeroMemory(pszOutBuffer, dwSize + 1);

            if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
                dwSize, &dwDownloaded))
                printf("Error %u in WinHttpReadData.\n", GetLastError());
            else
                config->insert(config->end(), pszOutBuffer, pszOutBuffer + dwSize);
            //printf("%s", config->data());

        // Free the memory allocated to the buffer.
            delete[] pszOutBuffer;

        } while (dwSize > 0);
        config->push_back('\00');
    }

    // Close any open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
}
