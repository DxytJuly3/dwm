#!/usr/bin/zsh
sudo chmod a+w /sys/devices/pci0000:00/0000:00:08.1/0000:33:00.0/backlight/amdgpu_bl0/brightness
lightdown |sudo tee /sys/devices/pci0000:00/0000:00:08.1/0000:33:00.0/backlight/amdgpu_bl0/brightness
sudo chmod 644 /sys/devices/pci0000:00/0000:00:08.1/0000:33:00.0/backlight/amdgpu_bl0/brightness
