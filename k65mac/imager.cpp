
#include "stdafx.h"
#include "common.h"





void Imager::Reset()
{
    bit_len     = 8;
    bit_dx      = 1;
    bit_dy      = 0;
    bit_init    = 0x80;
    bit_shift   = -1;
    bit_white   = 1;
    bit_outer   = 0;
    bit_pos.clear();

    img_xp = img_x0 = 0;
    img_xp = img_y0 = 0;
    img_dx = 0;
    img_dy = 1;
    img_len = 8;
	img_currow = 0;

    tile_dx = 0;
    tile_dy = 0;

    filename = "<unknown>";
    data.clear();
    w = 0;
    h = 0;
}

void Imager::Load(const char *path)
{
    Reset();
    filename = path;

    vector<uint8_t> raw;
	if(!NFS.GetFileBytes(fixpath(path).c_str(),raw)) Error("Can't open file");
    if(raw.size()<54) Error("Bad file format");

	uint16_t *head = (uint16_t*)&raw[0];
    int ww = head[ 9];
    int hh = head[11];
    if(head[ 0]!=0x4D42) Error("Bad file format");					//  0   2   signature, must be 4D42 hex
    if(head[ 3]!= 0) Error("Unsupported file mode");                //  6   2   reserved, must be zero
    if(head[ 4]!= 0) Error("Unsupported file mode");                //  8   2   reserved, must be zero
    if(head[ 5]!=54) Error("Unsupported file mode");                // 10   4   offset to start of image data in bytes
    if(head[ 6]!= 0) Error("Unsupported file mode");
    if(head[ 7]!=40) Error("Unsupported file mode");                // 14   4   size of BITMAPINFOHEADER structure, must be 40
    if(head[ 8]!= 0) Error("Unsupported file mode");
    if(head[10]!= 0) Error("Bitmap too large");
    if(head[12]!= 0) Error("Bitmap too large");
    if(head[13]!= 1) Error("Unsupported file mode");                // 26   2   number of planes in the image, must be 1
    if(head[14]!=24) Error("Unsupported BPP depth (must be 24)");   // 28   2   number of bits per pixel (1, 4, 8, or 24)
    if(head[15]!= 0) Error("Unsupported file compression");         // 30   4   compression type (0=none, 1=RLE-8, 2=RLE-4)
    if(head[16]!= 0) Error("Unsupported file mode");
//    if(head[17]!=LOWORD(3*ww*hh)) Error("Unsupported file mode"); // 34   4   size of image data in bytes (including padding)
//    if(head[18]!=HIWORD(3*ww*hh)) Error("Unsupported file mode");
    if((int)raw.size()<54+3*ww*hh) Error("File too short");

    w = ww;
    h = hh;
    data.clear();

    for(int y=0;y<h;y++)
    {
		uint8_t *dd = (uint8_t*)&raw[54 + (h-1-y)*w*3];

        for(int x=0;x<w;x++,dd+=3)
            data.push_back( (int(dd[2])<<16) | (int(dd[1])<<8) | int(dd[0]) );
    }
}

int Imager::GetRow()
{
    int b = bit_init;
    int v = 0xFF*bit_outer;
	int color = 0;
    for(int i=0;i<bit_len;i++)
    {
        bool smp = false;
        int ii = i;

        if(bit_pos.size()>=2)
        {
            char bp = i+1<(int)bit_pos.size() ? bit_pos[i+1] : '-';
            ii = -1;
            if(bp=='-') smp = false;
            if(bp=='+') smp = true;
            if(bp>='0' && bp<='9') ii = bp - '0';
            if(bp>='a' && bp<='z') ii = bp - 'a' + 10;
            if(bp>='A' && bp<='Z') ii = bp - 'A' + 10;
        }
        
        if(ii>=0)
        {
            smp = Sample(img_xp+ii*bit_dx,img_yp+ii*bit_dy);
            if(!bit_white) smp = !smp;
            if(!color) color = ColorSample(img_xp+ii*bit_dx,img_yp+ii*bit_dy);
        }

        if(smp) v |=  b;
        else    v &= ~b;

        if(bit_shift>0) b<<= bit_shift;
        if(bit_shift<0) b>>=-bit_shift;
    }

	int nd = (img_steps.size()>0) ? img_steps[img_currow%img_steps.size()] : 1;
	while(nd>0) nd--, img_xp += img_dx, img_yp += img_dy;
	while(nd<0) nd++, img_xp -= img_dx, img_yp -= img_dy;
	img_currow++;

	if(color_mode)
	{
		float r = ( (color>>16)&0xFF )/255.f;
		float g = ( (color>> 8)&0xFF )/255.f;
		float b = ( (color    )&0xFF )/255.f;
		v = (int)cmp.make_color(r,g,b);
	}

    return v&0xFF;
}

void Imager::NextTile()
{
    img_xp = img_x0 += tile_dx;
    img_yp = img_y0 += tile_dy;
	img_currow = 0;
}

bool Imager::Sample(int x,int y)
{
    if(x<0 || y<0 || x>=w || y>=h)
        return false;
    
    return (data[x+y*w]&0xF0F0F0) != 0;
}

int Imager::ColorSample(int x,int y)
{
    if(x<0 || y<0 || x>=w || y>=h)
        return false;
    
    return data[x+y*w]&0xFFFFFF;
}

void Imager::Error(const char *e)
{
    static string err;
    err = format("Image '%s' error: %s",filename.c_str(),e);
    throw err.c_str();
}
