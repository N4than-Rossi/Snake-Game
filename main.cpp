#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

map <pair<int, int>, char> snake; // corpo da cobra
queue<pair<int,int>> corpo; // corpo da cobra
map <pair<int, int>, char> apple; // maçã
char direcao = 'a';
bool apple_bool = false; // se a maçã já foi comida


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

void print_tela(){ //a tela será de 20x20, mas deixar isso varialvel depois
    system("cls");
    string tela;
    for (int i=-1;i<=20;i++){
        for (int j=-1;j<=20;j++){
            if (i == -1 || i == 20 || j == -1 || j == 20){
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

void load_snake(){
    corpo.push({10,10});
    snake[{10,10}] = 'O';

}

void move(){
    int cabeca_x = corpo.front().first;
    int cabeca_y = corpo.front().second;
    int rabo_x = corpo.back().first;
    int rabo_y = corpo.back().second;
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
            snake[{cabeca_x,corpo.front().second+1}] = 'O';
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
            apple_x = rand() % 20;
            apple_y = rand() % 20;
        }while (snake.find({apple_x,apple_y}) != snake.end());
        apple[{apple_x,apple_y}] = 'A';
    }
    apple_bool = true;
    if (corpo.front().first == apple.begin()->first.first && corpo.front().second == apple.begin()->first.second){
        apple_bool = false;
        /*snake[{apple.begin()->first.first,apple.begin()->first.second}] = 'O';
        corpo.push({apple.begin()->first.first,apple.begin()->first.second});*/
        apple.erase(apple.begin());
    }
}

int main() {
    system("color 0F");
    system("cls");
    srand(time(0));

    load_snake();

    cout << "Pressione Qualquer tecla para comecar" << endl;
    int qualquer;
    cin >> qualquer;

    while (1){
        apple_spawn();
        print_tela();
        
        char tecla_anterior = direcao;
        direcao = Tecla();
        if (direcao==' '){
            direcao = tecla_anterior;
        }

        move();
             
        Sleep(200);
    }
    return 0;


}
