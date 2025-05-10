#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool Tecla_pressionada(){
    return _kbhit();
}

char Tecla(){
    return _getch();
}

void print_tela(int altura, int largura){ //a tela será de 20x20, mas deixar isso varialvel depois
    system("cls");
    string tela;
    for (int i=-1;i<=20;i++){
        for (int j=-1;j<=20;j++){
            if (i == -1 || i == 20 || j == -1 || j == 20){
                tela += "#";
            }
            else if (i == altura && j == largura){
                tela += "O";
            }
            else {
                tela += " ";
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

    while (1){
        print_tela(altura, largura);
        if (Tecla_pressionada()){
            char c = Tecla();

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
                    
                }
             
        }
        Sleep(200);
    }
    return 0;


}
