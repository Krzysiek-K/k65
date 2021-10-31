
#pragma once



class Imager {
public:
    // bit scanning
    int bit_len;            // bit count
    int bit_dx, bit_dy;     // bit step
    int bit_init;           // first bit
    int bit_shift;          // shift for next bits  (+1: x<<1, -1: x>>1)
    int bit_white;          // 0/1 - bit value put for white
    int bit_outer;          // 0/1 - bit value for outside
    string bit_pos;         // bit positions
	int	color_mode;			// 0-bits, 1-colors

    // image gen
    int img_x0, img_y0;     // image start
    int img_xp, img_yp;     // image position
    int img_dx, img_dy;     // step for each data row
    int img_len;            // row count
	int	img_currow;			// current row
	vector<int>	img_steps;	// number of steps after each line

    // tiling
    int tile_dx, tile_dy;   // step after each tile


    Imager() : color_mode(0) { Reset(); }

    void Reset();
    void Load(const char *path);
    void ImgPos(int x,int y) { img_xp=img_x0=x; img_yp=img_y0=y; }
    int  GetRow();
    void NextTile();

private:
    string          filename;

public:
    vector<int>     data;
    int             w, h;

    bool Sample(int x,int y);
	int  ColorSample(int x,int y);
    void Error(const char *e);

};
