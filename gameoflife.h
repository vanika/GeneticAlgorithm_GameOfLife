#include <iostream>
#include <memory>
#include <ctime>
#include <cstring>

class CellMap
{
public:
    CellMap(unsigned x, unsigned y);
    ~CellMap();
    void Cell_Set(unsigned x, unsigned y);
    void Cell_Del(unsigned x, unsigned y);
    int Cell_State(int x, int y);
    void NextGen();
    void Init();
private:
    unsigned char *cells;
    unsigned char *tmp_cells;
    unsigned int width;
    unsigned int height;
    unsigned int length;
};

unsigned int cell_width = 500;
unsigned int cell_height = 500;
unsigned int cell_size = 1;
unsigned int seed;

CellMap::CellMap(unsigned int w,unsigned int h)
{
    width = w;
    height = h;
    length = w * h;
    cells = new unsigned char[length];
    tmp_cells = new unsigned char[length];
    memset(cells,0,length);
}

CellMap::~CellMap()
{
    delete[] cells;
    delete[] tmp_cells;

}

void CellMap::Cell_Set(unsigned int x,unsigned int y){

    int w = width;
    int h = height;
    int xleft,xright,yabove,ybelow;
    unsigned char *cell_ptr = cells + (x * width) + y;

    *cell_ptr |= 0x01;
    xleft = (x == 0) ? w - 1 : -1;
    xright = (x == (w - 1)) ? -(w - 1) : 1;
    yabove = (y == 0) ? length - w : -w;
    ybelow = (y == (h - 1)) ? -(length - w) : w;

    *(cell_ptr + yabove + xleft) += 0x02;
    *(cell_ptr + yabove) += 0x02;
    *(cell_ptr + yabove + xright) += 0x02;
    *(cell_ptr + xleft) += 0x02;
    *(cell_ptr + xright) += 0x02;
    *(cell_ptr + ybelow + xleft) += 0x02;
    *(cell_ptr + ybelow) += 0x02;
    *(cell_ptr + ybelow + xright) += 0x02;

}

void CellMap::Cell_Del(unsigned int x, unsigned int y){

    int w = width;
    int h = height;
    int xleft,xright,yabove,ybelow;
    unsigned char *cell_ptr = cells + (x * width) + y;

    *cell_ptr &= ~0x01;
    xleft = (x == 0) ? w - 1 : -1;
    xright = (x == (w - 1)) ? -(w - 1) : 1;
    yabove = (y == 0) ? length - w : -w;
    ybelow = (y == (h - 1)) ? -(length - w) : w;

    *(cell_ptr + yabove + xleft) -= 0x02;
    *(cell_ptr + yabove) -= 0x02;
    *(cell_ptr + yabove + xright) -= 0x02;
    *(cell_ptr + xleft) -= 0x02;
    *(cell_ptr + xright) -= 0x02;
    *(cell_ptr + ybelow + xleft) -= 0x02;
    *(cell_ptr + ybelow) -= 0x02;
    *(cell_ptr + ybelow + xright) -= 0x02;

}

int CellMap::Cell_State(int x, int y) {

    unsigned char *ptr_cells;
    ptr_cells = cells + (x * width) + y;
    return *ptr_cells & ~0x01;
}

void CellMap::Init() {

    unsigned int x,y,init_length;
    seed = (unsigned)time(NULL);
    srand(seed);
    init_length = (width * height) / 2;
    do
    {
        x = rand() % (width - 1);
        y = rand() % (height - 1);
        if (Cell_State(x, y) == 0)
            Cell_Set(x, y);
    } while (--init_length);

}

void CellMap::NextGen()
{
    unsigned int x, y, count;
    unsigned int h = height, w = width;
    unsigned char *cell_ptr;

    // Copy to temp map to keep an unaltered version
    memcpy(tmp_cells, cells, length);

    // Process all cells in the current cell map
    cell_ptr = tmp_cells;
    for (y = 0; y < h; y++) {

        x = 0;
        do {

            // Skip dead cells
            while (*cell_ptr == 0) {
                cell_ptr++; // Advance to the next cell
                // Need to do this when it's all off
                if (++x >= w) goto RowDone;
            }

            // Remaining cells are either on or have neighbours
            count = *cell_ptr >> 1; // # count of neighboring on-cells
            if (*cell_ptr & 0x01) {

                // Live cell must die if not 2 or 3 neighbours
                if ((count != 2) && (count != 3)) {
                    Cell_Del(x, y);
                    //DrawCell(x, y, OFF_COLOUR);
                }
            }
            else {

                // Dead cell must relive if 3 neighbours
                if (count == 3) {
                    Cell_Set(x, y);
                    //DrawCell(x, y, ON_COLOUR);
                }
            }

            // Advance to the next cell byte
            cell_ptr++;

        } while (++x < w);
        RowDone:;
    }
}

