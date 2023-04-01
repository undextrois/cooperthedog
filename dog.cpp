//
//  dog.cpp
//  cooper
//
//  Created by Cooper Sanchez on 4/1/23.
//


#include <iostream>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

int main() {
    initscr();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    
    int x = 0;
    int y = LINES - 1;
    int ground_level = LINES - 4;
    int cloud_x = COLS;
    int cloud_y = rand() % (ground_level - 3) + 1;
    bool jumping = false;
    int jump_height = 0;
    
    while (true) {
        clear();
        
        // draw ground
        attron(COLOR_PAIR(2));
        for (int i = 0; i < COLS; i++) {
            mvaddch(ground_level, i, ACS_BLOCK);
        }
        attroff(COLOR_PAIR(2));
        
        // draw player
        attron(COLOR_PAIR(1));
        if (jumping) {
            if (jump_height < 10) {
                y--;
                jump_height++;
            } else {
                jumping = false;
                jump_height = 0;
            }
        } else {
            y = ground_level;
            if (x >= COLS) {
                x = 0;
            }
        }
        mvaddch(y, x, ACS_DIAMOND);
        attroff(COLOR_PAIR(1));
        
        // draw cloud
        attron(COLOR_PAIR(3));
        if (cloud_x < -10) {
            cloud_x = COLS;
            cloud_y = rand() % (ground_level - 3) + 1;
        }
        for (int i = 0; i < 5; i++) {
            mvaddch(cloud_y + i, cloud_x + i, ACS_CKBOARD);
            mvaddch(cloud_y + i, cloud_x + i + 1, ACS_CKBOARD);
            mvaddch(cloud_y + i, cloud_x + i + 2, ACS_CKBOARD);
        }
        cloud_x--;
        attroff(COLOR_PAIR(3));
        
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
        int c = getch();
        if (c == KEY_LEFT) {
            x--;
        } else if (c == KEY_RIGHT) {
            x++;
        } else if (c == 27) {
            break;
        } else if (c == KEY_UP) {
            jumping = true;
        }
    }
    
    endwin();
    return 0;
}
