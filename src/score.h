#ifndef _SCORE_H_
#define _SCORE_H_

class Score {
public:
    Score();
    int getScore() const;
    void addPoints(int points);
    void reset();

private:
    int score;
};

#endif
