#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool Tecla_pressionada(){
    return _kbhit();
}

char Tecla(){
    if (GetAsyncKeyState(0x57) & 0x8000) {
        return 'w';
    }
    else if (GetAsyncKeyState(0x41) & 0x8000) {
        return 'a';
    }
    else if (GetAsyncKeyState(0x53) & 0x8000) {
        return 's';
    }
    else if (GetAsyncKeyState(0x44) & 0x8000) {
        return 'd';
    }
    else {return ' ';}
    //return _getch();
}

void print_tela(int altura, int largura){ //a tela será de 20x20, mas deixar isso varialvel depois
    system("cls");
    string tela;
    for (int i=-1;i<=20;i++){
        for (int j=-1;j<=20;j++){
            if (i == -1 || i == 20 || j == -1 || j == 20){
                tela += "# ";
            }
            else if (i == altura && j == largura){
                tela += "O ";
            }
            else {
                tela += "  ";
            }
        }
        tela += "\n";
    }
    cout << tela;
}
    
int main() {
    system("cls");
    int altura = 10;
    int largura = 10;
    char c = 'a';
    srand(time(0));
    bool apple = true;
    int apple_x = rand() % 20;
    int apple_y = rand() % 20;

    cout << "Pressione Qualquer tecla para comecar" << endl;
    int qualquer;
    cin >> qualquer;

    while (1){
        print_tela(altura, largura);
        altura = altura % 20;
        if (altura < 0){
            altura = 20 + altura;
        }
        largura = largura % 20;
        if (largura < 0){
            largura = 20 + largura;
        }
        char tecla_anterior = c;
        c = Tecla();
        if (c==' '){
            c = tecla_anterior;
        }


                switch (c){
                    case 'a':
                      largura--;
                      break;
                    case 'd':
                        largura++;
                       break;
                    case 'w':
                     altura--;
                        break;
                    case 's':
                      altura++;
                     break;
                    default:
                        break;
                    
                }
             
        Sleep(200);
    }
    return 0;


}
