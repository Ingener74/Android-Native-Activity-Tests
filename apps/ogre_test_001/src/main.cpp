
#include <iostream>
#include <OGRE/Ogre.h> 

const char* caption = 
	"OGRE Test application"
	;
using namespace Ogre;

int main( int argc, char* argv[] ){
	std::cout << caption << std::endl;
	Root* root = new Root;

	if(root){
	}else{
		std::cout << "root is NULL" << std::endl;
	}

	return 0;
}
