# Smoke Screen Build Script
# Builds all the sneaky remote desktop shit

Write-Host "==========================================" -ForegroundColor Cyan
Write-Host "    Smoke Screen System Builder v1.0" -ForegroundColor Cyan  
Write-Host "    Remote Desktop Sneaky Shit Suite" -ForegroundColor Cyan
Write-Host "==========================================" -ForegroundColor Cyan
Write-Host ""

# Check if we have the compiler shit
$gccPath = Get-Command g++ -ErrorAction SilentlyContinue
if (-not $gccPath) {
    Write-Host "ERROR: g++ compiler not found! This won't work without it!" -ForegroundColor Red
    Write-Host "Install MinGW-w64 or Visual Studio Build Tools first" -ForegroundColor Yellow
    exit 1
}

Write-Host "Found compiler: $($gccPath.Source)" -ForegroundColor Green
Write-Host ""

# Build smoke_capture.exe (Normal Version You Can See)
Write-Host "Building Smoke Capture (Normal Version)..." -ForegroundColor Yellow
$captureCmd = "g++ -std=c++17 -O2 -s smoke_capture.cpp -o smoke_capture.exe -lgdi32 -lws2_32 -lgdiplus -luser32 -lkernel32 -lshell32"

try {
    Invoke-Expression $captureCmd
    if (Test-Path "smoke_capture.exe") {
        Write-Host "✓ smoke_capture.exe built successfully" -ForegroundColor Green
    } else {
        Write-Host "✗ Failed to build smoke_capture.exe" -ForegroundColor Red
    }
} catch {
    Write-Host "✗ Error building smoke_capture.exe: $($_.Exception.Message)" -ForegroundColor Red
}

Write-Host ""

# Build smoke_capture_stealth.exe (Invisible Ghost Shit)
Write-Host "Building Smoke Capture Ghost (Invisible as Fuck)..." -ForegroundColor Magenta
$captureStealthCmd = "g++ -std=c++17 -O2 -s smoke_capture_stealth.cpp -o smoke_capture_ghost.exe -lgdi32 -lws2_32 -lgdiplus -luser32 -lkernel32 -lshell32 -lntdll -lpsapi -ladvapi32"

try {
    Invoke-Expression $captureStealthCmd
    if (Test-Path "smoke_capture_ghost.exe") {
        Write-Host "✓ smoke_capture_ghost.exe built successfully" -ForegroundColor Green
    } else {
        Write-Host "✗ Failed to build smoke_capture_ghost.exe" -ForegroundColor Red
    }
} catch {
    Write-Host "✗ Error building smoke_capture_ghost.exe: $($_.Exception.Message)" -ForegroundColor Red
}

Write-Host ""

# Build smoke_receiver.exe (Normal Version You Can See)
Write-Host "Building Smoke Receiver (Normal Version)..." -ForegroundColor Yellow
$receiverCmd = "g++ -std=c++17 -O2 -s smoke_receiver.cpp -o smoke_receiver.exe -lgdi32 -lws2_32 -luser32 -lkernel32"

try {
    Invoke-Expression $receiverCmd
    if (Test-Path "smoke_receiver.exe") {
        Write-Host "✓ smoke_receiver.exe built successfully" -ForegroundColor Green
    } else {
        Write-Host "✗ Failed to build smoke_receiver.exe" -ForegroundColor Red
    }
} catch {
    Write-Host "✗ Error building smoke_receiver.exe: $($_.Exception.Message)" -ForegroundColor Red
}

Write-Host ""

# Build smoke_receiver_stealth.exe (Invisible Ghost Shit)
Write-Host "Building Smoke Receiver Ghost (Invisible as Fuck)..." -ForegroundColor Magenta
$receiverStealthCmd = "g++ -std=c++17 -O2 -s smoke_receiver_stealth.cpp -o smoke_receiver_ghost.exe -lgdi32 -lws2_32 -luser32 -lkernel32 -lntdll -lpsapi -ladvapi32"

try {
    Invoke-Expression $receiverStealthCmd
    if (Test-Path "smoke_receiver_ghost.exe") {
        Write-Host "✓ smoke_receiver_ghost.exe built successfully" -ForegroundColor Green
    } else {
        Write-Host "✗ Failed to build smoke_receiver_ghost.exe" -ForegroundColor Red
    }
} catch {
    Write-Host "✗ Error building smoke_receiver_ghost.exe: $($_.Exception.Message)" -ForegroundColor Red
}

Write-Host ""

# Check results
$captureExists = Test-Path "smoke_capture.exe"
$receiverExists = Test-Path "smoke_receiver.exe"
$captureGhostExists = Test-Path "smoke_capture_ghost.exe"
$receiverGhostExists = Test-Path "smoke_receiver_ghost.exe"

$successCount = 0
if ($captureExists) { $successCount++ }
if ($receiverExists) { $successCount++ }
if ($captureGhostExists) { $successCount++ }
if ($receiverGhostExists) { $successCount++ }

if ($successCount -gt 0) {
    Write-Host "========================================" -ForegroundColor Green
    Write-Host "    BUILD RESULTS ($successCount/4 successful)" -ForegroundColor Green
    Write-Host "========================================" -ForegroundColor Green
    Write-Host ""
    
    # Show file info
    Write-Host "Files created:" -ForegroundColor Cyan
    
    if ($captureExists) {
        $captureInfo = Get-Item "smoke_capture.exe"
        Write-Host "  ✓ smoke_capture.exe      - $([math]::Round($captureInfo.Length/1KB, 1)) KB (Standard)" -ForegroundColor Green
    } else {
        Write-Host "  ✗ smoke_capture.exe      - Failed" -ForegroundColor Red
    }
    
    if ($captureGhostExists) {
        $captureGhostInfo = Get-Item "smoke_capture_ghost.exe"
        Write-Host "  ✓ smoke_capture_ghost.exe - $([math]::Round($captureGhostInfo.Length/1KB, 1)) KB (Ghost Mode)" -ForegroundColor Magenta
    } else {
        Write-Host "  ✗ smoke_capture_ghost.exe - Failed" -ForegroundColor Red
    }
    
    if ($receiverExists) {
        $receiverInfo = Get-Item "smoke_receiver.exe"
        Write-Host "  ✓ smoke_receiver.exe     - $([math]::Round($receiverInfo.Length/1KB, 1)) KB (Standard)" -ForegroundColor Green
    } else {
        Write-Host "  ✗ smoke_receiver.exe     - Failed" -ForegroundColor Red
    }
    
    if ($receiverGhostExists) {
        $receiverGhostInfo = Get-Item "smoke_receiver_ghost.exe"
        Write-Host "  ✓ smoke_receiver_ghost.exe - $([math]::Round($receiverGhostInfo.Length/1KB, 1)) KB (Ghost Mode)" -ForegroundColor Magenta
    } else {
        Write-Host "  ✗ smoke_receiver_ghost.exe - Failed" -ForegroundColor Red
    }
    
    Write-Host ""
    
    Write-Host "How To Use This Shit:" -ForegroundColor Cyan
    Write-Host "Normal Mode (You Can See It):" -ForegroundColor Yellow
    Write-Host "  Server: .\smoke_capture.exe --service" -ForegroundColor White
    Write-Host "  Client: .\smoke_receiver.exe <server_ip> 8080" -ForegroundColor White
    Write-Host ""
    Write-Host "Ghost Mode (Invisible as Fuck):" -ForegroundColor Magenta
    Write-Host "  Server: .\smoke_capture_ghost.exe --ghost" -ForegroundColor White
    Write-Host "  Client: .\smoke_receiver_ghost.exe --ghost <server_ip> 8080" -ForegroundColor White
    Write-Host "  Auto:   .\smoke_receiver_ghost.exe --ghost --auto" -ForegroundColor White
    Write-Host ""
    
} else {
    Write-Host "========================================" -ForegroundColor Red
    Write-Host "    BUILD FAILED!" -ForegroundColor Red  
    Write-Host "========================================" -ForegroundColor Red
    Write-Host ""
    
    if (-not $captureExists) {
        Write-Host "✗ smoke_capture.exe not created" -ForegroundColor Red
    }
    if (-not $receiverExists) {
        Write-Host "✗ smoke_receiver.exe not created" -ForegroundColor Red
    }
    
    Write-Host ""
    Write-Host "Common solutions:" -ForegroundColor Yellow
    Write-Host "- Install MinGW-w64: https://www.mingw-w64.org/" -ForegroundColor White
    Write-Host "- Install Visual Studio Build Tools" -ForegroundColor White
    Write-Host "- Check Windows SDK is installed" -ForegroundColor White
    Write-Host "- Run as Administrator if needed" -ForegroundColor White
}

Write-Host ""
Write-Host "Build script completed." -ForegroundColor Gray