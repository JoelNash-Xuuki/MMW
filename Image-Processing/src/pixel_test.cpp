#include <string> 
#include <iostream> 
#include <list> 
#include <Magick++.h>

using namespace std; 
using namespace Magick;

int main(int argc,char **argv)
{ 
	try
	{
		InitializeMagick(*argv);
		Image image( Geometry(1920,1080), Color("White") );
	}

	catch( exception & error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl; 
      return 1; 
    }

	return 0; 
}
