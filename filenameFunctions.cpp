
#include <string>
#include <Windows.h>
#include <tchar.h>

// Function to open windows file explorer and to return string of selected filename
std::string getFileName()
{
    // Open the file browser
    OPENFILENAME ofn;
    wchar_t fileName[MAX_PATH] = L"";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = sizeof(fileName);
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    if (GetOpenFileName(&ofn))
    {
        std::wstring fileNameW(fileName);
        std::string fileNameStr(fileNameW.begin(), fileNameW.end());
        return fileNameStr;
    }
    else
    {
        return "";
    }
}