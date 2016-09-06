#include <SDL2/SDL.h>
#include "ui.h"
#include "event.h"
#include "app_state_and_events.h"
#include <iostream>

using namespace std;

static bool open_goals = false;
static bool open_control = false;
static bool open_modeler = false;
static bool open_help = false;

static void ShowGoals(bool* opened);
static void ShowControl(bool* opened, AppStateAndEvents &);
static void ShowHelp(bool* opened);
static void ShowModeler(bool* opened, AppStateAndEvents &);

void ui(AppStateAndEvents &ae) {

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Visualizer 3D - Joilnen Leite")) {
            ImGui::MenuItem("Goals", NULL, &open_goals);
            ImGui::MenuItem("Control", NULL, &open_control);
            ImGui::MenuItem("Modeler", NULL, &open_modeler);
            ImGui::MenuItem("Help", NULL, &open_help);
            if(ImGui::MenuItem("Exit", "ESC/Q")) {
                SDL_Event sdlevent;
                sdlevent.type = SDL_KEYDOWN;
                sdlevent.key.keysym.sym = SDLK_q;

                SDL_PushEvent(&sdlevent);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if(open_goals)
        ShowGoals(&open_goals);
    if(open_control)
        ShowControl(&open_control, ae);
    if(open_modeler)
        ShowModeler(&open_modeler, ae);
    if(open_help)
        ShowHelp(&open_help);
}

void ShowGoals(bool* opened) {
    ImGui::Begin("Goals", opened);
        ImGui::Text("What this project achieved (in portuguese)");
        ImGui::Bullet(); ImGui::TextColored(ImVec4(1.0f,0.0f,1.0f,1.0f), "A fachada externa do CH");
        ImGui::BulletText("O interior do CH");
        ImGui::BulletText("5 objetos do CH");
        ImGui::BulletText("1 Porta");
        ImGui::BulletText("O usuário irá navegar com o teclado/mouse na modelagem permitindo ao usuário visualizar a parte externa e interna do CH");
        ImGui::BulletText("A porta do CH deverá ser aberta ou fechada através da ação de um botão criado em uma interface gráfica");
        ImGui::BulletText("Refinar a modelagem realizada no primeiro Bimestre");
        ImGui::BulletText("Aplicar Iluminação a modelagem");

        ImGui::BulletText("Aplicar mapeamento de textura");
    ImGui::End();
}

float col1[3] = { 1.0f,0.0f,0.2f };
float col2[3] = { 1.0f,0.8f,0.2f };
float col_computer[3] = { 1.0f,0.4f,0.7f };
float col_table[3] = { 0.3f,0.4f,0.7f };
float col_aircond[3] = { 0.3f,0.2f,0.0f };
bool is_door_open = false;
void ShowControl(bool* opened, AppStateAndEvents &ae) {

    ImVec2 size = ImGui::GetItemRectSize();

    float step = ae.getStep();
    ImGui::Begin("Controler",  opened);
        ImGui::Text("General");
        if(is_door_open) {
            if(ImGui::Button("Fechar Porta"))
                is_door_open = false;
        }
        else if(ImGui::Button("Abrir Porta"))
                is_door_open = true;
        ImGui::SameLine();
        if(ae.isWire()) {
            if(ImGui::Button("Sólido"))
                ae.setWire(false);
        }
        else if(ImGui::Button("Aramado"))
                ae.setWire(true);

        ImGui::Text("Posso");
        ImGui::SliderFloat("#1", &step, 0.0f, 10.0f, "ratio = %.3f");
        ae.setStep(step);

        ImGui::Text("Color");
        ImGui::ColorEdit3("Lab", col1);
        ImGui::ColorEdit3("Porta", col2);
        ImGui::ColorEdit3("Computador", col_computer);
        ImGui::ColorEdit3("Mesa", col_table);
        ImGui::ColorEdit3("Ar condicionado", col_aircond);
    ImGui::End();
}

void ShowHelp(bool* opened) {
    ImGui::Begin("Help", opened, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Move camera quake like commands A,W,S,D,");
        ImGui::Text("activate/deactivate camara rotation C, all other");
        ImGui::Text("commands are intuitive.");
        ImGui::Text("Autor: Joilnen Batista Leite, 02-05-2016");
    ImGui::End();
}

void ShowModeler(bool* opened, AppStateAndEvents &ae) {
    ImGui::Begin("Modeler", opened, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Aqui será ferramentas de modelagem");
        ImGui::Text("Autor: Joilnen Batista Leite, 02-05-2016");
    ImGui::End();
}


