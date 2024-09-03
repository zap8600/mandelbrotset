

//Make it so we don't need to include any other C files in our build.
#define CNFG_IMPLEMENTATION

#include <stdio.h>
#include "rawdraw_sf.h"

void HandleKey( int keycode, int bDown ) { }
void HandleButton( int x, int y, int button, int bDown ) { }
void HandleMotion( int x, int y, int mask ) { }
int HandleDestroy() { return 0; }
int main()
{
	CNFGSetup( "Mandelbrot Set", 1024, 768 );
	while(CNFGHandleInput())
	{
		CNFGBGColor = 0x000080ff; //Dark Blue Background

		short w, h;
		CNFGClearFrame();
		CNFGGetDimensions( &w, &h );

		for(int xT = 0; xT < w; xT++) {
            for(int yT = 0; yT < h; yT++) {
                float xZ = (((float)xT / (float)w) * ((float)w / (float)h) * 0.47f);
                float yZ = ((float)yT / (float)h);

                float x = 0.0f;
                float y = 0.0f;

                int iteration = 0;
                int max_iteration = 0;

                while(x*x + y*y <= (2*2) && iteration < max_iteration) {
                    float xtemp = x*x - y*y + xZ;
                    y = 2*x*y + yZ;

                    x = xtemp;

                    iteration += 1;
                }

                if(iteration == max_iteration) {
                    CNFGColor(0x00000000);
                    CNFGTackPixel(xT, yT);
                } else {
                    CNFGColor(iteration);
                    CNFGTackPixel(xT, yT);
                }
            }
        }

		//Display the image and wait for time to display next frame.
		CNFGSwapBuffers();		
	}
}