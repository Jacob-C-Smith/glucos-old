#include <GlucOS/VBE.h>

u32 VBERow    = 0;
u32 VBEColumn = 0;
u32 VBEColor  = 0;

u64 font[130] = {
	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,
	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,
	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,
	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,	0x0000000000000000,
	0x0000000000000000,	0x183C3C1818001800,	0x3636000000000000,	0x36367F367F363600,	0x0C3E031E301F0C00,	0x006333180C666300,	0x1C361C6E3B336E00,	0x0606030000000000,
	0x180C0606060C1800,	0x060C1818180C0600,	0x00663CFF3C660000,	0x000C0C3F0C0C0000,	0x00000000000C0C06,	0x0000003F00000000,	0x00000000000C0C00,	0x6030180C06030100,
	0x3E63737B6F673E00,	0x0C0E0C0C0C0C3F00,	0x1E33301C06333F00,	0x1E33301C30331E00,	0x383C36337F307800,	0x3F031F3030331E00,	0x1C06031F33331E00,	0x3F3330180C0C0C00,
	0x1E33331E33331E00,	0x1E33333E30180E00,	0x000C0C00000C0C00,	0x000C0C00000C0C06,	0x180C0603060C1800,	0x00003F00003F0000,	0x060C1830180C0600,	0x1E3330180C000C00,
	0x3E637B7B7B031E00,	0x0C1E33333F333300,	0x3F66663E66663F00,	0x3C66030303663C00,	0x1F36666666361F00,	0x7F46161E16467F00,	0x7F46161E16060F00,	0x3C66030373667C00,
	0x3333333F33333300,	0x1E0C0C0C0C0C1E00,	0x7830303033331E00,	0x6766361E36666700,	0x0F06060646667F00,	0x63777F7F6B636300,	0x63676F7B73636300,	0x1C36636363361C00,
	0x3F66663E06060F00,	0x1E3333333B1E3800,	0x3F66663E36666700,	0x1E33070E38331E00,	0x3F2D0C0C0C0C1E00,	0x3333333333333F00,	0x33333333331E0C00,	0x6363636B7F776300,
	0x6363361C1C366300,	0x3333331E0C0C1E00,	0x7F6331184C667F00,	0x1E06060606061E00,	0x03060C1830604000,	0x1E18181818181E00,	0x081C366300000000,	0x00000000000000FF,
	0x0C0C180000000000,	0x00001E303E336E00,	0x0706063E66663B00,	0x00001E3303331E00,	0x3830303e33336E00,	0x00001E333f031E00,	0x1C36060f06060F00,	0x00006E33333E301F,
	0x0706366E66666700,	0x0C000E0C0C0C1E00,	0x300030303033331E,	0x070666361E366700,	0x0E0C0C0C0C0C1E00,	0x0000337F7F6B6300,	0x00001F3333333300,	0x00001E3333331E00,
	0x00003B66663E060F,	0x00006E33333E3078,	0x00003B6E66060F00,	0x00003E031E301F00,	0x080C3E0C0C2C1800,	0x0000333333336E00,	0x00003333331E0C00,	0x0000636B7F7F3600,
	0x000063361C366300,	0x00003333333E301F,	0x00003F190C263F00,	0x380C0C070C0C3800,	0x1818180018181800,	0x070C0C380C0C0700,	0x6E3B000000000000,	0x0000000000000000,
	// GlucOS UI specific
	0x80C0E070371E1C08, 0x003C7E7E7E7E3C00
};
VBEScreen_t* activeScreen = 0;

VBEScreen_t* VBE_initialize ( void* frameBufferAddr, u32 width, u32 height, u8 colorDepth )
{
    VBEScreen_t* ret       = malloc(sizeof(VBEScreen_t));

    ret->framebufferAddress = frameBufferAddr;
    ret->width              = width;
    ret->height             = height;
    ret->colorDepth         = colorDepth;

    activeScreen = ret;

	VBE_drawRect(0,0,ret->width, ret->height, 0xFFFFFFFF);

    return ret;
}
inline void VBE_putPixel ( u32 color, size_t x, size_t y )
{
    activeScreen->framebufferAddress[y*activeScreen->width+x] = color;
}
void VBE_putcharat( char c, size_t x, size_t y, u32 color )
{
    u64 bmc = font[(unsigned char)c];
	for(u32 h = (x+8); h>x;h--)
	{
		for(u32 w = y; w<(8+y);w++)
		{
			if(bmc & 1)
				activeScreen->framebufferAddress[h*activeScreen->width+w] = color;
			bmc>>=1;		
		}
	}
}
void VBE_putchar ( char c )
{
    if(c == '\n')
    {
        if(++VBERow > 24)
		{
			memcpy((void*)(activeScreen->framebufferAddress),(void*)(activeScreen->framebufferAddress+(activeScreen->width*activeScreen->colorDepth)),(activeScreen->width*activeScreen->height));
			memset((void*)0xB8F00,0,0xA0);
			VBERow = (activeScreen->height / 8) - 1;
		}
        VBEColumn = 0;
        return;
    }
	VBE_putcharat(c, VBEColor, VBEColumn*8, VBERow*8);
	if (++VBEColumn == activeScreen->width) {
		VBEColumn = 0;
		if (++VBERow == activeScreen->height)
			VBERow = 0;
	}
}

 
void VBE_write ( size_t size, const char* data )
{
    for(size_t i = 0; i < size;i++)
        VBE_putchar(data[i]);
}

void VBE_writestringat ( const char* data, size_t x, size_t y )
{
	for (size_t i = 0; i < strlen(data); i++)
	{
		VBE_putcharat(data[i],y,x+(i*8),VBEColor);
	}
}

void VBE_writestring ( const char* data )
{
    VBE_write(strlen(data), data);
}

void VBE_drawRect( u32 x, u32 y, u32 w, u32 h, u32 c )
{
	for(u32 ly = y; ly<h+y;ly++)
		for (u32 lx = x; lx < w+x; lx++)
			activeScreen->framebufferAddress[ly*activeScreen->width+lx] = c;
		
}

void VBE_drawLine ( u32 x0, u32 y0, u32 x1, u32 y1, u32 c )
{
	s32 dx = abs(x1-x0);
	s32 sx = x0<x1 ? 1 : -1;
	s32 dy = -abs(y1-y0);
	s32 sy = y0<y1 ? 1 : -1;
	s32 err = dx+dy;
	while(1)
	{
		VBE_putPixel(c,x0,y0);
		if(x0 == x1 && y0 == y1) break;
		s32 e2 = 2*err;
		if(e2>=dy)
		{
			err += dy;
			x0 += sx;
		}
		if(e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void VBE_drawHollowRect( u32 x, u32 y, u32 w, u32 h, u32 c )
{
	VBE_drawLine(x  , y    ,x+w  ,y  ,c); // Top 
    VBE_drawLine(x  , y+h  , x+w ,y+h,c); // Bottom
    VBE_drawLine(x  , y    , x   ,y+h,c); // Left
    VBE_drawLine(x+w, y    , x+w ,y+h,c); // Right
}
