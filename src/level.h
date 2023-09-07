#ifndef _LEVEL_H_
#define _LEVEL_H_

class Level {
public:
    Level();

    int getCurrentLevel() const;
    int getLinesCleared() const;
    void linesClearedEvent(int lines);
    void reset();

private:
    int level;
    int linesCleared;
};

#endif
