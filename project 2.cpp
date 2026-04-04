#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

enum enQuestionLevel { easy = 1, med = 2, hard = 3, mix = 4 };

enum enOpType { add = 1, sub = 2, mul = 3, Div = 4, mixOp = 5 };

struct stQuestion
{
    short num1;
    short num2;
    enOpType optype;
    enQuestionLevel questionlevel;
    int correctanser = 0;
    int playeranser = 0;
    bool anserresult = false;
};

struct stQuizz
{
    stQuestion questionlist[100];
    short numofquestion;
    enQuestionLevel questionlevel;
    enOpType optype;
    short numofcorrectanser = 0;
    short numofwronganser = 0;
    bool ispass = false;
};

int RandomNum(int from, int to)
{
    int randomnum = rand() % (to - from + 1) + from;
    return  randomnum;
}

int ReadNumOfQuestion()
{
    int question;
    do
    {
        cout << "How Many Question Do You Want To Anser?" << endl;
        cin >> question;
    } while (question<1||question>10);
    return question;
}

enQuestionLevel ReadQuestionLevel()
{
    short level;

    do
    {
        cout << "\nEnter Question Level [1]Easy , [2]Med , [3]Hard , [4]Mix" << endl;
        cin >> level;
    } while (level<1||level>4);
    return (enQuestionLevel)level;
}

enOpType ReadOpType()
{
    short optype;

    do
    {
        cout << "\nEnter Opration Type [1]Add , [2]Sub , [3]Mul , [4]Div , [5]Mix" << endl;
        cin >> optype;
    } while (optype<1||optype>5);
    return (enOpType)optype;
}

string GetOpType(enOpType optype)
{
    switch (optype)
    {
    case enOpType::add:
        return "+";

    case enOpType::sub:
        return "-";

    case enOpType::mul:
        return "*";

    case enOpType::Div:
        return "/";
    default:
        return "Mix";
    }
}

enOpType GetRandomOpType()
{
    return (enOpType)RandomNum(1, 4);
}

string GetQuestionLevelText(enQuestionLevel level)
{
    string arrlevel[4] = { "Easy","Med","Hard","Mix" };
    return arrlevel[level - 1];
}

void SetScreenColor(bool right)
{
    if (right)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

int SimpleCalculater(int num, int num2, enOpType optype)
{
    switch (optype)
    {
    case enOpType::add:
        return num + num2;

    case enOpType::sub:
        return num - num2;

    case enOpType::mul:
        return num * num2;

    case enOpType::Div:
        return num / num2;

    default:
        return num + num2;
    }
}

stQuestion GenerateQuestion(enQuestionLevel level,enOpType optype)
{
    stQuestion question;

    if (level == enQuestionLevel::mix)
    {
        level = (enQuestionLevel)RandomNum(1, 3);
    }

    if (optype == enOpType::mixOp)
    {
        optype = GetRandomOpType();
    }
    question.optype = optype;

    switch (level)
    {
    case enQuestionLevel::easy:
        question.num1 = RandomNum(1, 10);
        question.num2 = RandomNum(1, 10);
        question.correctanser = SimpleCalculater(question.num1, question.num2, question.optype);
        question.questionlevel = level;
        return question;


    case enQuestionLevel::med:
        question.num1 = RandomNum(50, 100);
        question.num2 = RandomNum(50, 100);
        question.correctanser = SimpleCalculater(question.num1, question.num2, question.optype);
        question.questionlevel = level;
        return question;


    case enQuestionLevel::hard:
        question.num1 = RandomNum(1, 100);
        question.num2 = RandomNum(1, 100);
        question.correctanser = SimpleCalculater(question.num1, question.num2, question.optype);
        question.questionlevel = level;
        return question;
    }
    return question;
}

void GenerateQuizzQuestion(stQuizz& quizz)
{
    for (int i = 0; i < quizz.numofquestion; i++)
    {
        quizz.questionlist[i] = GenerateQuestion(quizz.questionlevel, quizz.optype);
    }
}

int ReadQuestionAnser()
{
    int num;
    cin >> num;
    return num;
}

void CorrectTheQuestionAnser(stQuizz& quizz, short numquestion)
{
    if (quizz.questionlist[numquestion].playeranser != quizz.questionlist[numquestion].correctanser)
    {
        quizz.questionlist[numquestion].anserresult = false;
        quizz.numofwronganser++;

        cout << "Wrong Anser :-(\n";
        cout << "The Right Anser is: ";
        cout << quizz.questionlist[numquestion].correctanser;
        cout << endl;
    }
    else
    {
        quizz.questionlist[numquestion].anserresult = true;
        quizz.numofcorrectanser++;

        cout << "Right Anser :-)\n";
    }
    SetScreenColor(quizz.questionlist[numquestion].anserresult);
}

void PrintTheQuestion(stQuizz& quizz,short numquestion)
{
    cout << "\nQuestion [ " << numquestion + 1 << "/" << quizz.numofquestion << "]\n\n";
    cout << quizz.questionlist[numquestion].num1 << endl;
    cout << quizz.questionlist[numquestion].num2 << " ";
    cout << GetOpType(quizz.questionlist[numquestion].optype) << endl;
    cout << "___________________\n\n";
}

void AskAndCorrectQuestionAnser(stQuizz& quizz)
{
    for (int i = 0; i < quizz.numofquestion; i++)
    {
        PrintTheQuestion(quizz, i);
        quizz.questionlist[i].playeranser = ReadQuestionAnser();
        CorrectTheQuestionAnser(quizz, i);
    }
    quizz.ispass = (quizz.numofcorrectanser >= quizz.numofwronganser);
}

string GetFinalResult(bool pass)
{
    if (pass)
    {
        return "Pass :-)";
    }
    else
    {
        return "Fail :-(";
    }
}

void PrintQuizzResult(stQuizz quizz)
{
    cout << "\n\n--------------------------\n\n";
    cout << "Final Result is " << GetFinalResult(quizz.ispass);
    cout << "\n\n--------------------------\n\n";
    cout << "Number Of Question is: " << quizz.numofquestion << endl;
    cout << "Question Level: " << GetQuestionLevelText(quizz.questionlevel) << endl;
    cout << "Opration Type: " << GetOpType(quizz.optype) << endl;
    cout << "Number Of Right Answer: " << quizz.numofcorrectanser << endl;
    cout << "Number Of Wrong answer: " << quizz.numofwronganser << endl;
    cout << "\n\n_____________________________\n\n";
}

void PlayGame()
{
    stQuizz quizz;

    quizz.numofquestion = ReadNumOfQuestion();
    quizz.questionlevel = ReadQuestionLevel();
    quizz.optype = ReadOpType();
    GenerateQuizzQuestion(quizz);
    AskAndCorrectQuestionAnser(quizz);
    PrintQuizzResult(quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char play = 'Y';

    do
    {
        ResetScreen();
        PlayGame();

        cout << "Do You Want To  Play Again?" << endl;
        cin >> play;
    } while (play=='Y'||play=='y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}