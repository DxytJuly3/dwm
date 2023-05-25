#include <stdio.h>

int main() {
	FILE* openF = fopen("/sys/devices/pci0000:00/0000:00:08.1/0000:33:00.0/backlight/amdgpu_bl0/brightness", "r");
	unsigned int lightNow;
	fscanf(openF, "%u", &lightNow);
	
	if(lightNow <= 242) 
		lightNow += 13;
	else 
		lightNow = 255;

	fclose(openF);
	printf("%u", lightNow);

	return 0;
}
