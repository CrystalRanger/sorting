#include <raylib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>

#define SCREENWIDTH 800
#define SCREENHEIGHT 600
#define MAXSIZE 300
using namespace std;

vector<int> genVec(int n, int max) {
    vector<int> vec;
    for(int i = 0; i < n; i++) {
        vec.push_back(rand() % max);
    }
    return vec;
}

void printVec(vector <int> const a) {
   for(int i=0; i < a.size(); i++)
   cout << a.at(i) << ' ';
   cout << endl;
}

int main() {
    const int vecsize = 100;
    vector<int> vec = genVec(vecsize, MAXSIZE);
    
    int index = 0;
    Color col = WHITE;
    int current;
    int next = 1;
    int prev;
    float timer = 0.0;
    float totaltime = 0.0;

    bool sorted = false;
    bool swapped;
    bool wooped = false;
    bool reset = false;

    const int UNITHEIGHT = SCREENHEIGHT / MAXSIZE;
    const int UNITWIDTH = SCREENWIDTH / vec.size();

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Sorter");
    InitAudioDevice();
    Sound sine = LoadSound("src/assets/sine.wav");
    float position = 0.0;
    while(!WindowShouldClose()) {

        timer += GetFrameTime();
        if(!sorted) totaltime += GetFrameTime();
        

        if(timer >= 0.0 && !sorted) {
            index = (index == vec.size() - 2) ? 0 : index + 1;
            next = (index == vec.size() - 1) ? 1: index + 1;

            
            
            if(vec[index] > vec[next]) {
                swapped = true;
                int temp = vec[index];
                vec[index] = vec[next];
                vec[next] = temp;
            }
            if(index == 0) {
                sorted = !swapped;
                swapped = false;
            }
            
            SetSoundPitch(sine, vec[index]/60.0);
            PlaySound(sine);
            // cout << "Index: " << index << endl;
            // cout << "Next: " << next << endl;
            // printVec(vec);
            timer = 0;
        }
        if(sorted && !reset) {
            index = 0;
            next = -1;
            reset = true;
        }

        if(timer >= 0.03 && reset && sorted && !wooped) {
            index++;
            SetSoundPitch(sine, vec[index] / 60.0);
            PlaySound(sine);
            if(index == vec.size() - 1) wooped = true;
            timer = 0;
        }

        if(IsKeyPressed(KEY_SPACE)) {
            vec = genVec(vecsize, MAXSIZE);
            index = 0;
            totaltime = 0;
            sorted = false;
            wooped = false;
            swapped = true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        stringstream parser;
        string result;
        parser << totaltime;
        parser >> result;
        DrawText(result.c_str(),0,0,25,RAYWHITE);

        
        for(int i = 0; i < vec.size(); i++) {
            current = vec[i];
            prev = (i == 0) ? current : vec[i-1];
            if(wooped) {
                col = GREEN;
            } else if(i == index) {
                col = GREEN;
            } else if(i == next) {
                col = RED;
            } else { 
                col = WHITE;
            };
            DrawRectangle(position, SCREENHEIGHT - UNITHEIGHT * vec[i], UNITWIDTH, UNITHEIGHT * vec[i], col);
            position += UNITWIDTH;
        }
        position = 0;
        
        EndDrawing();
    }

    UnloadSound(sine);

    CloseAudioDevice();
    CloseWindow();
}