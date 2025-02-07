# SALE_ECE491-02
Smart Assistive Living Environment (SALE) Senior Design project at Lafayette College

## Setup

### If you're downloading this on a new device, follow these steps

Open a Developer PowerShell from the Start Menu using the Start->All apps- >Raspberry Pi Pico SDK v1.5.5->Pico – Developer PowerShell I also suggest that you right-click on this menu entry and select “Pin to Start” for faster access in the future.

cd into your Documents folder

Run the following commands:
```bash
mkdir pico
cd pico
git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk 
git submodule update --init 
cd .. 
git clone -b master https://github.com/raspberrypi/pico-examples.git
git clone https://github.com/priskillaw/SALE_ECE491-02.git
```

## Before making any changes, follow these steps

Open a Developer PowerShell 

cd into SALE_ECE491-02

Run "git pull"

You can start working now. Open Pico - Visual Studio Code

## To run things
```bash
cd build 
cmake -G "NMake Makefiles" .. 
nmake
```

Reboot the pico, then drag and drop the .uf2 file from the build file into the pico in file explorer

## To push things
cd into SALE_ECE491-02
```bash
git add Folder_Name
git commit -m "Folder_Name"
git push
```
