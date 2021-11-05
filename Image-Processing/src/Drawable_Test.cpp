#include <string> 
#include <iostream> 
#include <list> 
#include <Magick++.h>

using namespace std; 
using namespace Magick;

int main(int argc,char **argv)
{ 
  try { 

    InitializeMagick(*argv);

    Image image( Geometry(1920,1080), Color("Transparent") );

    // Construct drawing list 
    std::vector<Magick::Drawable> drawList;

    drawList.push_back(DrawableFillColor("Transparent")); // Fill color
	drawList.push_back(DrawableStrokeWidth(10));
	drawList.push_back(DrawableStrokeColor("Red"));  

    drawList.push_back(DrawableRectangle(720, 1080, 10,0));

    image.draw(drawList);

    // Display the result 
    image.write("player_square.png" ); 
  } 
  catch( exception & error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl; 
      return 1; 
    }

  return 0; 
}
