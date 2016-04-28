/*****************************************************
 * Hello world da apresentacao de CG sobre irrlicht 3D
 * Joilnen Leite
 *****************************************************/

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace core;


int main()
{
   // cria uma device grhfico, com tamanho, e numero de bits da cor, nao fullscreen
   IrrlichtDevice *device = createDevice(EDT_OPENGL, dimension2d<u32>(640, 480));
   IVideoDriver *video =  device->getVideoDriver();

   // seta titulo da janela
   device->setWindowCaption(L"Irrlicht3D Hello World");


   // main loop 
   while (device->run()) {
      video->beginScene(ECBF_COLOR);
      video->draw2DPolygon(position2di(200, 200), 80);
      video->endScene();
   }

   device->drop();

   return 0;
}


