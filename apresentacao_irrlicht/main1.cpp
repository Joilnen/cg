/*****************************************************
 * Hello world da apresentacao de CG sobre irrlicht 3D
 * Joilnen Leite
 *****************************************************/

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;
using namespace gui;

IrrlichtDevice *device = NULL;

// declara a classe que trara eventos
class PegadorDeEventos: public IEventReceiver {

    vector2di mousePos;
    public:
        bool OnEvent(const SEvent &ev) {
            if (ev.EventType == EET_KEY_INPUT_EVENT &&
                (ev.KeyInput.Key == KEY_ESCAPE || ev.KeyInput.Key == KEY_KEY_Q)
               )
                    device->closeDevice();

            return false;
        }
};

int main()
{
   // Define seu objeto listener de eventos
   PegadorDeEventos ev;

   // cria uma device grhfico, com tamanho, e numero de bits da cor, nao fullscreen
   device = createDevice(EDT_OPENGL, dimension2d<u32>(800, 600), 24, false, true, false, &ev);

   // seta titulo da janela
   device->setWindowCaption(L"Irrlicht3D Hello World");

   // referencias para outros dois importantes ojetos o responsavel
   // pelo visao clipping o viewport e scenemanager gerencia 
   // os objetos na cena 3D
   IVideoDriver *driver = device->getVideoDriver();
   ISceneManager *smgr = device->getSceneManager();

   // cria uma camara
   smgr->addCameraSceneNode(0, vector3df(0, 25, -30), vector3df(0,0,0));
   // smgr->addLightSceneNode(smgr->addCameraSceneNodeFPS(), vector3df(0, 10, -15))->setRadius(30);
   // smgr->getSceneNodeFromType(ESNT_CAMERA)->setPosition(vector3df(0, 25, -20));
   // static_cast<ICameraSceneNode*>(smgr->getSceneNodeFromType(ESNT_CAMERA))->setTarget(vector3df(0, 0, 0));

   // Lembrar de comentar aqui se adicionar luz com camera FPS
   smgr->addLightSceneNode(0, vector3df(0, 50, -30))->setRadius(15);

   // cria dois nos de cena um cubo e uma esfera
   // nao preciso me preocupar com textura ou se eles reagem 
   // a iliminacao eles jah se comportam como o q normalmente
   // desejado por default
   smgr->addCubeSceneNode()->setPosition(vector3df(-15, 0, 0));
   smgr->addSphereSceneNode(5, 8)->setPosition(vector3df(15, 0, 0));

   // smgr->getSceneNodeFromType(ESNT_CUBE)->getMaterial(0).EmissiveColor.set(5, 155, 0, 0);
   // smgr->getSceneNodeFromType(ESNT_SPHERE)->getMaterial(0).EmissiveColor.set(7, 0, 155, 0);
   // smgr->getSceneNodeFromType(ESNT_SPHERE)->setMaterialFlag(EMF_WIREFRAME, true);


   // main loop 
   while (device->run()) {
      driver->beginScene(ECBF_COLOR | ECBF_DEPTH, SColor(255,10,10,10));
      smgr->drawAll();

      driver->endScene();
   }

   device->drop();

   return 0;
}


