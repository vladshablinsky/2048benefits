/*This game is based on 2048 game http://gabrielecirulli.github.io/2048/


---------Created by Vladislav Shablinsky------------


*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <string>
#include <cstring>
#include <cstdlib>
#include <memory.h>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cmath>

using namespace std;

class Game
{
protected:
    int fibnumbers[20];
    int dbls[20];
    int **field;
    int flag; // if the field changes
    int score, deltascore;
    int n; // the number of rows and colomns
    map< pair< int, int >, int > substitute;
public:
    Game()
    {
        fibnumbers[0] = 1;
        fibnumbers[1] = 1;
        dbls[0] = 2;
        dbls[1] = 4;
        for (int i = 2; i < 20; ++i)
            fibnumbers[i] = fibnumbers[i - 1] + fibnumbers[i - 2],
            dbls[i] = dbls[i - 1] * 2;
        flag = 0, score = 0, deltascore = 0, n = 4;
        field = new int* [n];
        for (int i = 0; i < n; ++i)
            field[i] = new int [n];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                field[i][j] = 0;
    }
    Game(int n): n(n)
    {
        fibnumbers[0] = 1;
        fibnumbers[1] = 1;
        dbls[0] = 2;
        dbls[1] = 4;
        for (int i = 2; i < 20; ++i)
            fibnumbers[i] = fibnumbers[i - 1] + fibnumbers[i - 2],
            dbls[i] = dbls[i - 1] * 2;
        flag = 0, score = 0, deltascore = 0;
        field = new int* [n];
        for (int i = 0; i < n; ++i)
            field[i] = new int [n];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                field[i][j] = 0;
    }
    ~Game()
    {
        for (int i = 0; i < n; ++i)
            delete[] field[i];
        delete[] field;
    }
    void Init(int flag)
    {
        srand(time(NULL));
        fibnumbers[0] = 1;
        fibnumbers[1] = 1;
        switch (flag)
        {
            case 3:
                freopen("regulations.txt", "r", stdin);
                int tkey1, tkey2, tvalue;
                while (scanf("%d%d%d", &tkey1, &tkey2, &tvalue) != EOF)
                    substitute[make_pair(tkey1, tkey2)] = tvalue;
                break;
            case 2:
                for (int i = 2; i < 20; ++i)
                    substitute[make_pair(fibnumbers[i - 1], fibnumbers[i - 2])] = fibnumbers[i];
                break;
            case 1:
                for (int i = 1; i < 20; ++i)
                    substitute[make_pair(dbls[i - 1], dbls[i - 1])] = dbls[i];
                break;
        }
        FillEmpty();
    }
    void FillEmpty()
    {
        vector< pair< int, int > > v;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (field[i][j] == 0)
                    v.push_back(make_pair(i, j));
        pair< int, int > res = v[rand() % v.size()];
        field[res.first][res.second] = substitute.begin()->first.first;
        if (score == 0)
        {
            v.clear();
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (field[i][j] == 0)
                        v.push_back(make_pair(i, j));
            res = v[rand() % v.size()];
            field[res.first][res.second] = substitute.begin()->first.second;
        }
        if (score > 1000 && (rand() % 5 == 1)) field[res.first][res.second] = substitute.begin()->second;
        else if (rand() % 10 == 1) field[res.first][res.second] = substitute.begin()->second;

    }
    vector< int > Move(vector< int > in)
    {
        for (int i = 0; i < (int)in.size(); ++i)
            if (in[i] == 0)
                for (int k = i + 1; k < (int)in.size(); ++k)
                    if (in[k] != 0)
                    {
                        swap(in[i], in[k]);
                        break;
                    }
        return in;
    }
    vector< int > Merge(vector< int > in)
    {
        for (int i = 0; i < (int)in.size() - 1; ++i)
        {
            if (substitute.find(make_pair(in[i], in[i + 1])) != substitute.end())
            {
                deltascore = -score;
                score += in[i] + in[i + 1];
                deltascore += score;
                in[i] = substitute[make_pair(in[i], in[i + 1])];
                in[i + 1] = 0;
                ++i;
            }
            else if (substitute.find(make_pair(in[i + 1], in[i])) != substitute.end())
            {
                deltascore = -score;
                score += in[i] + in[i + 1];
                deltascore += score;
                in[i] = substitute[make_pair(in[i + 1], in[i])];
                in[i + 1] = 0;
                ++i;
            }
        }
        for (int i = 0; i < (int)in.size(); ++i)
            if (in[i] == 0)
                for (int k = i + 1; k < (int)in.size(); ++k)
                    if (in[k] != 0)
                    {
                        swap(in[i], in[k]);
                        break;
                    }
        return in;
    }
    void Move(int direction)
    {
        flag = 0;
        deltascore = 0;
        bool stps = (direction == 1 || direction == 3);
        bool rvrs = (direction == 0 || direction == 1);
        for (int i = 0; i < n; ++i)
        {
            vector < int > transposition(n);
            for (int j = 0; j < n; ++j)
            {
                int ii = i, jj = j;
                int idx = stps ? n - j - 1 : j;
                if (rvrs) swap(ii, jj);
                transposition[idx] = field[ii][jj];
            }
            transposition = Move(transposition);
            transposition = Merge(transposition);
            for (int j = 0; j < n; ++j)
            {
                int ii = i, jj = j;
                int idx = stps ? n - j - 1 : j;
                if (rvrs) swap(ii, jj);
                if (field[ii][jj] != transposition[idx])
                    flag = true;
                field[ii][jj] = transposition[idx];
            }
        }
        if (flag) FillEmpty(); // if something has changed then we have to add another number and it will be definitely added
    }
    bool GameOver()
    {
        for (int i = 0; i < n - 1; ++i)
            for (int j = 0; j < n - 1; ++j)
            {
                if (substitute.find(make_pair(field[i][j], field[i + 1][j])) != substitute.end()) return false;
                if (substitute.find(make_pair(field[i][j], field[i][j + 1])) != substitute.end()) return false;
                if (substitute.find(make_pair(field[i + 1][j], field[i][j])) != substitute.end()) return false;
                if (substitute.find(make_pair(field[i][j + 1], field[i][j])) != substitute.end()) return false;
                if (field[i][j] == 0) return false;
                if (field[i + 1][j] == 0) return false;
                if (field[i][j + 1] == 0) return false;
                if (field[i + 1][j + 1] == 0) return false;
            }
        return true;
    }
    void PrintField()
    {
        if (!GameOver())
        {
            printf("\nSCORE");
            if (deltascore == 0)
                for (int i = 0; i < 6 * n - 5 - 6 ; ++i)
                    printf(" ");
            else
            {
                printf(" +%4d", deltascore);
                for (int i = 0; i < 6 * n - 5 - 6 - 6; ++i)
                    printf(" ");
            }
            printf("%6d", score);
            printf("\n");
        }
        else
        {
            printf("\nGAMEOVER");
            for (int i = 0; i < 6 * n - 8; ++i)
                printf(" ");
            printf("\n");
        }
        for (int i = 0; i < 6 * n; ++i)
                printf("-");
            printf("\n\n");

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                if (field[i][j] != 0)
                    printf("%6d", field[i][j]);
                else printf("     *");
            printf("\n\n\n");
        }
    }
    bool IsChanged()
    {
        return flag;
    }
    int Score()
    {
        return score;
    }
};

class Play
{
    Game *A;
    int gameflag;
    int n;
    int key;
public:
    Play():n(4){};
    ~Play()
    {
        delete A;
    }
    void StartGame()
    {
        printf("Chose the type of game:\n");
        printf("1. Simple 2048\n");
        printf("2. 2584 (Almost the same as 'Simple' is but Fibbonachi numbers are used instead of doubles)\n");
        printf("3. Load from file. For more information read README\n");
        printf("Waiting for the type number...\n");
        scanf("%d", &gameflag);
        printf("Do you want to use your own value and play NxN instead of 4x4? y/n...\n");
        char c = 'n';
        cin >> c;
        if (c == 'y')
        {
            printf("Type then N and the field will be NxN\n");
            printf("Waiting for N...\n");
            scanf("%d", &n);
            if (n == 4)
            {
                printf("Are you seriously? You're a funny guy!\n");
                Sleep(1700);
            }
        }
        system("cls");
        c = 'r';
        while(c == 'r')
        {
            A = new Game(n);
            A->Init(gameflag);
            A->PrintField();
            while (!A->GameOver())
            {
                int key = getch();
                switch(key)
                {
                    case 72: A->Move(0); break;
                    case 80: A->Move(1); break;
                    case 75: A->Move(2); break;
                    case 77: A->Move(3); break;
                }
                if (A->IsChanged())
                {
                    system("cls");
                    A->PrintField();
                }
            }
            printf("The game has overed, your score is %d\n", A->Score());
            printf("Press 'r' if you want to restart, otherwise press 'e'...\n");
            while (cin >> c)
                if (c == 'e' || c == 'r')
                    break;
            system("cls");
        }
    }
};

int main()
{
    Play *game = new Play;
    game->StartGame();
    return 0;
}
