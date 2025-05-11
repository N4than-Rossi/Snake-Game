#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

map <pair<int, int>, char> snake; // corpo da cobra
queue<pair<int,int>> corpo; // corpo da cobra
map <pair<int, int>, char> apple; // maçã
char direcao = 'a';
bool apple_bool = false; // se a maçã já foi comida
int tamanho_tela = 10, pontuacao = 0;


/*bool Tecla_pressionada(){
    return _kbhit();
}*/

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

void direction(){
    char tecla_anterior = direcao;
        direcao = Tecla();
        if (direcao==' '){
            direcao = tecla_anterior;
        }
        else if (direcao == 'w' && tecla_anterior == 's'){
            direcao = tecla_anterior;
        }
        else if (direcao == 's' && tecla_anterior == 'w'){
            direcao = tecla_anterior;
        }
        else if (direcao == 'a' && tecla_anterior == 'd'){
            direcao = tecla_anterior;
        }
        else if (direcao == 'd' && tecla_anterior == 'a'){
            direcao = tecla_anterior;
        }
}

void print_tela(){ //a tela será de 20x20, mas deixar isso varialvel depois
    system("cls");
    string tela;
    for (int i=-1;i<=tamanho_tela;i++){
        for (int j=-1;j<=tamanho_tela;j++){
            if (i == -1 || i == tamanho_tela || j == -1 || j == tamanho_tela){
                tela += "# ";
            }
            else if (snake.find({i,j}) != snake.end()){
                tela += snake[{i,j}];
                tela += " ";
            }
            else if (apple.find({i,j}) != apple.end()){
                tela += apple[{i,j}];
                tela += " ";
            }
            else {
                tela += "  ";
            }
        }
        tela += "\n";
    }
    cout << tela;
}

void start(){
    snake.clear();
    queue<pair<int,int>> fila_vazia;
    corpo.swap(fila_vazia);
    apple.clear();
    apple_bool = false;
// zerando o jogo
//---------------------------------------
    int meio = tamanho_tela/2; //meio da tela
    corpo.push({meio,meio});
    corpo.push({meio,meio+1});
    corpo.push({meio,meio+2});
    snake[{meio,meio}] = 'O';
    snake[{meio,meio+1}] = 'O';
    snake[{meio,meio+2}] = 'O';

}

void move(){
    int rabo_x = corpo.front().first;
    int rabo_y = corpo.front().second;
    int cabeca_x = corpo.back().first;
    int cabeca_y = corpo.back().second;
    switch (direcao){
        case 'a':
            //largura--;
            corpo.push({cabeca_x,cabeca_y-1});
            snake[{cabeca_x,cabeca_y-1}] = 'O';
            snake.erase({rabo_x,rabo_y});
            corpo.pop();
            break;
        case 'd':
            //largura++;
            corpo.push({cabeca_x,cabeca_y+1});
            snake[{cabeca_x,cabeca_y+1}] = 'O';
            snake.erase({rabo_x,rabo_y});
            corpo.pop();
            break;
        case 'w':
            //altura--;
            corpo.push({cabeca_x-1,cabeca_y});
            snake[{cabeca_x-1,cabeca_y}] = 'O';
            snake.erase({rabo_x,rabo_y});
            corpo.pop();
            break;
        case 's':
            //altura++;
            corpo.push({cabeca_x+1,cabeca_y});
            snake[{cabeca_x+1,cabeca_y}] = 'O';
            snake.erase({rabo_x,rabo_y});
            corpo.pop();
            break;
        default:
            break;
                    
    }
}

void apple_spawn(){
    
    if (!apple_bool){
        int apple_x, apple_y;
        do {
            apple_x = rand() % tamanho_tela;
            apple_y = rand() % tamanho_tela;
        }while (snake.find({apple_x,apple_y}) != snake.end());
        apple[{apple_x,apple_y}] = 'A';
    }
    apple_bool = true;
    if (corpo.back().first == apple.begin()->first.first && corpo.back().second == apple.begin()->first.second){
        apple_bool = false;
        snake[{apple.begin()->first.first,apple.begin()->first.second}] = 'O';
        corpo.push({apple.begin()->first.first,apple.begin()->first.second});
        apple.erase(apple.begin());
        pontuacao++;
    }
}

bool game_over(){
    bool alive = true;
    int cabeca_x = corpo.back().first;
    int cabeca_y = corpo.back().second;
    if (cabeca_x == -1 || cabeca_x == tamanho_tela || cabeca_y == -1 || cabeca_y == tamanho_tela){
        alive = false;
    }
    int aux = 0;
    for (auto it = snake.begin(); it != snake.end(); it++){
        if (it->first.first == cabeca_x && it->first.second == cabeca_y){
            aux++;
            if (aux > 1){
                alive = false;
            }
        }
    }
    
    if (alive == false){
        system("color 0C");
        system("cls");
        cout << "Game Over" << endl;
        system("color 0F");
        cout << "Pontuacao: " << pontuacao << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nDeseja jogar novamente? (s/n) " << endl;
        char opc;
        cin >> opc;
        if (opc == 's' || opc == 'S'){
            start();
            return false;
        }
        else {
            return true;
        }
    }
    return false;
}

int main() {
    system("cls");
    system("color 0F");
    srand(time(0));

    start();
    cout << "Escolha o tamanho de jogo (7-20):\n";
    cin >> tamanho_tela;
    cout << "Pressione Qualquer tecla para comecar" << endl;
    int qualquer;
    cin >> qualquer;
    
    while (1){
        apple_spawn();
        print_tela();
        direction();
        move();
        if (game_over())return 0;  
        Sleep(200);//delay
    }
    return 0;


}
