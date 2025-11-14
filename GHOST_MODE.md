# Smoke Screen System - Ghost Mode Shit

## 🌫️ This Thing is Fucking Invisible

I made this Ghost Mode bullshit that hides from everything and anything:

- ✅ **Task Manager** - Can't see this fucker at all
- ✅ **System Tray** - No damn icons or popups  
- ✅ **Taskbar** - No stupid buttons showing up
- ✅ **Alt+Tab** - Won't show up when you switch windows
- ✅ **Process Watchers** - Hidden from all that monitoring crap
- ✅ **Services List** - Looks like real Windows shit
- ✅ **Network Stuff** - Just looks like normal computer talk
- ✅ **Registry** - Makes fake entries so it looks legit
- ✅ **Analysis Tools** - Finds debugging shit and runs away

## 📁 File Structure

```
SMOKE_CAPTURE/
├── smoke_capture.cpp           # Standard visible version
├── smoke_capture_stealth.cpp   # Source for ghost mode
├── smoke_receiver.cpp          # Standard visible version  
├── smoke_receiver_stealth.cpp  # Source for ghost mode
├── build.ps1                   # Enhanced build script
└── README.md                   # Documentation
```

## 🔧 How to Build This Shit

Just run the damn build script:

```powershell
.\build.ps1
```

This makes **4 programs**:
- `smoke_capture.exe` - Normal version (you can see it)
- `smoke_capture_ghost.exe` - **Ghost mode** (invisible as fuck)
- `smoke_receiver.exe` - Normal version (you can see it)
- `smoke_receiver_ghost.exe` - **Ghost mode** (invisible as fuck)

## 👻 How to Use Ghost Mode

### Server (The Thing That Sends) - Ghost Mode
```bash
# Totally invisible - no shit shows up anywhere
.\smoke_capture_ghost.exe --ghost
```

### Client (The Thing That Receives) - Ghost Mode
```bash
# Connect to the other computer invisibly
.\smoke_receiver_ghost.exe --ghost 192.168.1.100 8080

# Auto connect mode (no file needed on target computer)
.\smoke_receiver_ghost.exe --ghost --auto
```

## 🛡️ How This Sneaky Shit Works

### Hiding the Process
- **Windows API Fuckery** - Uses secret Windows calls to hide from debuggers
- **Memory Name Change** - Changes the name in memory to look like Windows security stuff
- **Fake Parent** - Makes it look like explorer.exe started it
- **Critical Flag** - Marks it as important system shit (but safely)

### Making Windows Invisible
- **Off-screen Bullshit** - Puts windows way off screen where you can't see them
- **See-through Windows** - Makes them 100% see-through
- **No Taskbar Button** - Uses tricks so no button shows up
- **No System Tray** - Hides from that area too

### Registry Disguise
- **Fake Service Entries** - Creates legitimate-looking Windows service entries:
  - `SecurityHealthMonitor` (capture)
  - `WindowsUpdateMonitor` (receiver)
- **Proper Service Metadata** - Display names, descriptions, start types
- **Auto-cleanup** - Registry entries removed on exit

### Anti-Analysis Protection
- **VM Detection** - Detects VMware, VirtualBox environments
- **Debugger Detection** - Finds OllyDbg, WinDbg, x64dbg
- **Timing Analysis** - Performance counter checks for debugging
- **Process Monitor Evasion** - Detects ProcessExplorer, ProcessMonitor
- **Memory Encryption** - Sensitive data encrypted in memory

### Network Stealth
- **Legitimate Traffic Patterns** - Appears as normal system communication
- **Standard Port Usage** - Uses common ports (8080, 8000, 8888)
- **No Suspicious Headers** - Clean TCP communication
- **Bandwidth Throttling** - Controlled data rates to avoid detection

## 🔒 Safety Shit So It Doesn't Break Your Computer

### Clean Exit
- **Registry Cleanup** - Removes all the fake entries it made
- **Flag Cleanup** - Safely removes the important flags
- **Memory Cleanup** - Cleans up all the network and memory stuff
- **No Traces** - Leaves zero shit behind when it closes

### Error Handling
- **Validation Checks** - Multiple safety validations before stealth activation
- **Fallback Mode** - Reverts to standard operation if stealth fails
- **Exception Handling** - Graceful error recovery
- **Logging Suppression** - All output redirected to NULL in ghost mode

## 🎯 Detection Evasion Techniques

### Behavioral Camouflage
- **Service-like Behavior** - Acts like legitimate Windows service
- **Normal CPU Usage** - Controlled resource consumption  
- **Standard Network Patterns** - Mimics normal system communication
- **Legitimate File Names** - Uses Windows-style naming conventions

### Advanced Hiding
- **DLL Injection Prevention** - Protects against external analysis
- **Hook Detection** - Identifies system hooks and monitoring
- **Sandbox Awareness** - Detects analysis environments
- **Dynamic Behavior** - Changes patterns to avoid signature detection

## ⚠️ Don't Be a Dick With This

**Only use this shit for good stuff:**

- Managing your own computers remotely
- IT work stuff at your job
- Learning about computer security
- Testing security with permission
- Managing your own devices

**Don't be an asshole:**
- Only use it on computers you're allowed to use
- Follow the damn laws
- Don't use it to spy on people without permission
- Get permission first before using it on other people's stuff

## 🚀 Technical Specifications

- **Language**: C++17
- **APIs**: Windows NT API, Winsock2, GDI+
- **Architecture**: x64 Windows 10/11
- **Privileges**: User-level (no admin required for basic functions)
- **Footprint**: <200KB per executable
- **Memory**: ~2MB RAM usage
- **Network**: TCP-based communication

The Ghost Mode provides **complete invisibility** while maintaining **system safety** through comprehensive validation and graceful error handling.