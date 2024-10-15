#include <iostream>
#define NOMINMAX
#define WINDOWS32LEANANDMEAN
#include <windows.h>

void shutdown() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

        tkp.PrivilegeCount = 1;
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

        if (GetLastError() != ERROR_SUCCESS) {
            std::cerr << "Failed to adjust token privileges" << std::endl;
            CloseHandle(hToken);
            return;
        }
    }
    else {
        std::cerr << "Failed to open process token" << std::endl;
        return;
    }

    UINT flags = EWX_REBOOT | EWX_FORCE;

    if (!ExitWindowsEx(flags, SHTDN_REASON_MAJOR_OTHER)) {
        std::cerr << "Failed to shutdown the system." << std::endl;
    }
    else {
        std::cout << "Shutdown initiated." << std::endl;
    }

    CloseHandle(hToken);
}

static void message() {
    int boxno;
    int boxyes;
    int boxone = MessageBox(0, L"Do you support palestine", L"IMPORTANT", MB_YESNO | MB_ICONQUESTION);
    if(boxone == IDNO) {

        shutdown();

        /*boxno = MessageBox(0, L"FUCK YOU >:(", L"IMPORTANT", MB_RETRYCANCEL | MB_ICONERROR);
        boxone = MessageBox(0, L"Do you support palestine", L"IMPORTANT", MB_YESNO | MB_ICONQUESTION);*/

    }
    else {

        boxyes = MessageBox(0, L" I LOVE YOU <3", L"IMPORTANT", MB_OK | MB_ICONINFORMATION);
    }
}
int WinMain(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nShowCmd
)
{

    message();




    //std::cout << "Hello World!\n";
    std::cin.get();
    return 0;
}

