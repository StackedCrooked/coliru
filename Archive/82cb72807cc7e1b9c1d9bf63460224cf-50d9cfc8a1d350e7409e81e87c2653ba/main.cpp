#include <string>
#include <vector>
#include <iostream>

using namespace std;

#ifndef QUESTION_H
#define QUESTION_H

class Question{
public:
    Question(int thePointValue, int theChapterNumber, \
        string theQuestionText);
    int getPointValue() const;
    int getChapterNumber() const;
    string getQuestionText() const;
    virtual void writeQuestion(ostream& outfile) const;
    virtual void writeKey(ostream& outfile) const;

private:
    int pointValue;
    int chapterNumber;
    string questionText;

    void writePointValue(ostream& outfile) const;
};




#endif


Question::Question(int thePointValue, int theChapterNumber, \
        string theQuestionText)
{
    pointValue = thePointValue;
    chapterNumber = theChapterNumber;
    questionText = theQuestionText;

        //HERE THIS WORKS PERFECTLY
        cout << questionText << endl;
}

int Question::getPointValue() const
{
    return pointValue;
}

int Question::getChapterNumber() const
{
    return chapterNumber;
}

string Question::getQuestionText() const
{
        //THIS IS THE PROBLEM. HERE IT OUPUTS AN EMPTY STRING NO MATTER WHAT!
        cout << questionText << endl;
    return questionText;
}

void Question::writeQuestion(ostream& outfile) const
{
    writePointValue(outfile);
    outfile << questionText << endl;
}

void Question::writeKey(ostream& outfile) const
{
    writePointValue(outfile);
    outfile << endl;
}

void Question::writePointValue(ostream& outfile) const
{
    string pt_noun;

    if (pointValue == 1)
        pt_noun = "point";
    else
        pt_noun = "points";

    outfile << "(" << pointValue << " " << pt_noun << ") ";
}



int main() {
    Question q(1, 1, "TestString");
    q.getQuestionText();
}