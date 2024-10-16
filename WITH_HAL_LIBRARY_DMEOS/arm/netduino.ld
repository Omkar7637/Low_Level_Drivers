MEMORY
{
	FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
	SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 112K
}
SECTIONS 
{
	.text : {
		* (.vectors);
		* (.text);
		etext = .;
	} > FLASH

	.data : {
		sdata = .;
		* (.data);
		edata = .;
	} > SRAM AT> FLASH

	.bss : {
		sbss = .;
		* (.bss);
		ebss = .;
	} > SRAM

	.rodata : {
		* (.rodata);
	} > FLASH
}

