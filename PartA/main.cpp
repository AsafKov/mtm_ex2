/*
 * sortedList
 * (Version 1)
 *
 * Visit: mtmtests.website
 * Tests by Robert
 *
 * Remember:    (1) Passing the below tests doesn't mean you will pass their tests.
 *              (2) Always check memory leak of your own implementation - Use the operation: valgrind ./your_excuted_project
 *                  check the above website for more about memory leak.
 */

/*
 * Make sure you already have the same files (sortedList.h examDetails.h and examDetails.cpp)
 * in the same folder that the file (main.cpp) is found.
 */
#include <iostream>
#include "examDetails.h"
#include "sortedList.h"
#include <cassert>
#include <cmath>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using namespace mtm;

#define LET_ME_TEST(thing, count) cout << endl << "(" << count << ") " << "Testing the " << thing << "..." << endl;
#define PASSED_THE(thing) cout << "(Excellent) Passed the " << thing << "!" << endl;
#define LET_ME_TEST_(thing, count) to_the_file << endl << "(" << count << ") " << "Testing the " << thing << "..." << endl;
#define PASSED_THE_(thing) to_the_file << "(Excellent) Passed the " << thing << "!" << endl;

class Point
{
private:
    double x;
    double y;
public:
    Point(double x, double y) : x(x), y(y){}
    Point() : x(0), y(0){}
    Point(const Point& target)
    {
        x = target.x;
        y = target.y;
    }
    bool operator==(const Point& target) const
    {
        if(target.Distance() > Distance())
        {
            return true;
        }
        return false;
    }
    bool operator<(const Point& target) const
    {
        double distance_a = (x*x+y*y);
        double distance_b = (target.x*target.x+target.y*target.y);
        if(distance_a<distance_b)
        {
            return true;
        }
        return false;
    }
    double Distance() const
    {
        return sqrt(x*x+y*y);
    }
    double operator*() const
    {
        return Distance();
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &point)
    {

        os << point.x << point.y;
        return os;
    }
    int operator$() const
    {
        return x;
    }
    int operator_() const
    {
        return y;
    }
};

void printDouble(SortedList<double>& d, std::ofstream& to_the_file)
{

    cout << "Double List: ";
    to_the_file << "Double List: ";
    for(auto iterator = d.begin(); !(iterator==d.end()); ++iterator)
    {
        cout << (*iterator) << " ";
        to_the_file << (*iterator) << " ";
    }
    cout << endl << endl;
    to_the_file << endl << endl;
}

void printExam(SortedList<ExamDetails>& exam, std::ofstream& to_the_file)
{
    for(auto iterator = exam.begin(); !(iterator==exam.end()); ++iterator)
    {
        cout << (*iterator) << endl;
        to_the_file << (*iterator) << endl;
    }
}

void printShape(SortedList<Point>& shape, std::ofstream& to_the_file)
{
    int matrix[10][10]= {0};
    for(auto iterator = shape.begin(); !(iterator==shape.end()); ++iterator)
    {
        Point temp = *iterator;
        matrix[temp.operator_()+2][temp.operator$()+2] = 1;
    }

    for(int i = 0; i<10; i++)
    {
        int counter = 0;
        for(int k = 0; k<10; k++)
        {
            if(matrix[i][k]==0)
            {
                counter++;
            }
        }
        if(counter == 10)
        {
            continue;
        }
        for(int j = 0; j<10; j++)
        {
            cout << ((matrix[i][j]==0)?" ":"*");
            to_the_file << ((matrix[i][j]==0)?" ":"*");
        }
        cout << endl;
        to_the_file << endl;
    }
    std::cout << "Shape Code: ";
    to_the_file << "Shape Code: ";
    for(auto iterator = shape.begin(); !(iterator==shape.end()); ++iterator)
    {
        std::cout << (*iterator);
        to_the_file << (*iterator);
    }
    cout << endl << endl;
    to_the_file << endl << endl;
}

bool isPositivePoint(const Point& target)
{
    if(target.operator_()>0 && target.operator$()>0)
    {
        return true;
    }
    return false;
}

bool isntEmptyLink(const ExamDetails& target)
{
    if((target.getLink()==""))
    {
        return false;
    }
    return true;
}

bool isEven(int target)
{
    return (int(target/2)*2==target);
}

Point makeRect(const Point& target)
{
    if((target.operator_()==1 && target.operator$()==0) ||
       (target.operator_()==0 && target.operator$()==1)||
       (target.operator_()==-1 && target.operator$()==0)||
       (target.operator_()==0 && target.operator$()==-1)||
       (target.operator_()==1 && target.operator$()==1)||
       (target.operator_()==1 && target.operator$()==-1)||
       (target.operator_()==-1 && target.operator$()==1))
    {
        Point copied(target.operator_(), target.operator$());
        return copied;
    }
    else
    {
        Point copied(0, 0);
        return copied;
    }
}

double isInteger(const double& target)
{
    if((int(target)!=target))
    {
        return 0;
    }
    return 1;
}

ExamDetails isM(const ExamDetails& exam)
{
    if(exam.getLink().find("m.") != std::string::npos)
    {
        return exam;
    }
    return ExamDetails::makeMatamExam();
}

/*
 * C++ TESTS COURSE MATAM (234214) - SPRING 2020
 * ---------------------------------------------
 * -------------------PART A--------------------
 * ----------------SORTED LIST-----------------
 * ---------------------------------------------
 */

int main()
{
    std::ofstream to_the_file;
    to_the_file.open("Your_output.txt");

    int test_counter = 0;
    test_counter++;
    LET_ME_TEST("SortedList Constructor (Version 1)",test_counter)
    LET_ME_TEST_("SortedList Constructor (Version 1)",test_counter)
    SortedList<double> Double_list;
    SortedList<double> Empty_Double_List;
    SortedList<Point> Shape;
    SortedList<Point> Rect;
    SortedList<Point> Empty_Shape;
    SortedList<ExamDetails> Exams_list;
    SortedList<ExamDetails> Empty_Exams_list;
    PASSED_THE("SortedList Constructor (Version 1)")
    PASSED_THE_("SortedList Constructor (Version 1)")

    test_counter++;
    LET_ME_TEST("SortedList Copy Constructor (Version 1)", test_counter)
    LET_ME_TEST_("SortedList Copy Constructor (Version 1)", test_counter)
    SortedList<double> Copied_Double_list = Double_list;
    SortedList<double> Copied_Empty_Double_List = Empty_Double_List;
    SortedList<Point> Copied_Shape = Shape;
    SortedList<Point> Copied_Empty_Shape = Empty_Shape;
    SortedList<ExamDetails> Copied_Exams_list = Exams_list;
    SortedList<ExamDetails> Copied_Empty_Exams_list = Empty_Exams_list;
    PASSED_THE("SortedList Copy Constructor (Version 1)")
    PASSED_THE_("SortedList Copy Constructor (Version 1)")

    test_counter++;
    LET_ME_TEST("SortedList Copy Assignment Operator (Version 1) - Normal Assignment", test_counter)
    LET_ME_TEST_("SortedList Copy Assignment Operator (Version 1) - Normal Assignment", test_counter)
    Copied_Double_list = Empty_Double_List;
    Copied_Double_list = Double_list;
    Copied_Shape = Empty_Shape;
    Copied_Shape = Shape;
    Copied_Exams_list = Exams_list;
    Copied_Exams_list = Empty_Exams_list;
    PASSED_THE("SortedList Copy Assignment Operator (Version 1) - Normal Assignment")
    PASSED_THE_("SortedList Copy Assignment Operator (Version 1) - Normal Assignment")

    test_counter++;
    LET_ME_TEST("SortedList Copy Assignment Operator (Version 2.1) - Self Assignment", test_counter)
    LET_ME_TEST_("SortedList Copy Assignment Operator (Version 2.1) - Self Assignment", test_counter)
    Double_list = Double_list;
    Empty_Double_List = Empty_Double_List;
    Shape = Shape;
    Empty_Shape = Empty_Shape;
    Exams_list = Exams_list;
    Copied_Exams_list = Copied_Exams_list;
    PASSED_THE("SortedList Copy Assignment Operator (Version 2.1) - Self Assignment")
    PASSED_THE_("SortedList Copy Assignment Operator (Version 2.1) - Self Assignment")

    test_counter++;
    LET_ME_TEST("SortedList Insert Method", test_counter)
    LET_ME_TEST_("SortedList Insert Method", test_counter)
    Point A(2, 2);
    Point B(-2, -2);
    Point C(-1, 3);
    Point D(1, 2);
    Point E(1, 2);
    Point F(3, 3);
    Point G(4, 0);
    Point H(0, 3);
    Point I(-1, 0);
    Point J(0, 2);
    Point K(2, 0);
    Point L(-2, 0);
    Point M(0, -2);
    Point N(-2, 2);
    Point P(2, -2);
    Point Q(4, 1);
    Point R(1, 4);
    Point S(4, 4);
    Point T(-4, -4);
    Point O(0, 0);
    Point AA(1, 1),AB(1, 0),BA(0, 1);
    Point CC(-1, -1),CD(-1, 0),DC(0, -1);
    Point Y(1, -1),Z(1, -1);

    ExamDetails exam5(2, 2, 2, 0, 1);
    ExamDetails exam6(1, 2, 2, 0, 1);
    ExamDetails exam7(2, 1, 1, 0, 1);
    ExamDetails exam8(2, 3, 3, 0, 1);
    ExamDetails exam9(3, 3, 2, 0, 1);
    ExamDetails exam10(4, 12, 30, 0, 1);
    ExamDetails exam1(104195, 1, 1, 0, 1, "infy1.com");
    ExamDetails exam2(104031, 12, 30, 23.5, 10000, "infy1m.com");
    ExamDetails exam3(104281, 9, 9, 9, 3, "infy2.com");
    ExamDetails exam4(104032, 10, 10, 10, 3, "infy2m.com");

    Double_list.insert(0.0);
    Double_list.insert(1.0);
    Double_list.insert(2.0);
    Double_list.insert(-1.0);
    Double_list.insert(1.5);
    Double_list.insert(3.0);
    Double_list.insert(3.0);
    Double_list.insert(3.0);
    Double_list.insert(4.0);
    Double_list.insert(3.5);
    Shape.insert(A);
    Shape.insert(B);
    Shape.insert(C);
    Shape.insert(D);
    Shape.insert(E);
    Shape.insert(F);
    Shape.insert(G);
    Shape.insert(H);
    Shape.insert(I);
    Shape.insert(J);
    Shape.insert(K);
    Shape.insert(L);
    Shape.insert(M);
    Shape.insert(N);
    Shape.insert(O);
    Shape.insert(P);
    Rect.insert(A);
    Rect.insert(B);
    Rect.insert(J);
    Rect.insert(K);
    Rect.insert(L);
    Rect.insert(M);
    Rect.insert(N);
    Rect.insert(P);
    Exams_list.insert(exam1);
    Exams_list.insert(exam2);
    Exams_list.insert(exam3);
    Exams_list.insert(exam4);
    Exams_list.insert(exam5);
    Exams_list.insert(exam6);
    Exams_list.insert(exam7);
    Exams_list.insert(exam8);
    Exams_list.insert(exam9);
    Exams_list.insert(exam10);
    PASSED_THE("SortedList Insert Method")
    PASSED_THE_("SortedList Insert Method")

    test_counter++;
    LET_ME_TEST("SortedList Begin Method", test_counter)
    LET_ME_TEST_("SortedList Begin Method", test_counter)
    Double_list.begin();
    Empty_Double_List.begin();
    Shape.begin();
    Empty_Shape.begin();
    Exams_list.begin();
    Empty_Exams_list.begin();
    PASSED_THE("SortedList Begin Method")
    PASSED_THE_("SortedList Begin Method")

    test_counter++;
    LET_ME_TEST("const_iterator Copy Constructor", test_counter)
    LET_ME_TEST_("const_iterator Copy Constructor", test_counter)
    SortedList<double>::const_iterator double_iterator = Double_list.begin();
    SortedList<double>::const_iterator empty_double_iterator = Empty_Double_List.begin();
    SortedList<Point>::const_iterator shape_iterator = Shape.begin();
    SortedList<Point>::const_iterator empty_shape_iterator = Empty_Shape.begin();
    SortedList<ExamDetails>::const_iterator exam_iterator = Exams_list.begin();
    SortedList<ExamDetails>::const_iterator empty_exam_iterator = Empty_Exams_list.begin();
    PASSED_THE("const_iterator Copy Constructor")
    PASSED_THE_("const_iterator Copy Constructor")

    test_counter++;
    LET_ME_TEST("const_iterator Copy Assignment Operator (=) - Version 1.1 - Normal Assignment", test_counter)
    LET_ME_TEST_("const_iterator Copy Assignment Operator (=) - Version 1.1 - Normal Assignment", test_counter)
    empty_double_iterator = double_iterator;
    empty_shape_iterator = shape_iterator;
    empty_exam_iterator = exam_iterator;
    PASSED_THE("const_iterator Copy Assignment Operator (=) - Version 1.1 - Normal Assignment")
    PASSED_THE_("const_iterator Copy Assignment Operator (=) - Version 1.1 - Normal Assignment")

    test_counter++;
    LET_ME_TEST("const_iterator Copy Assignment Operator (=) - Version 1.2 - Self Assignment", test_counter)
    LET_ME_TEST_("const_iterator Copy Assignment Operator (=) - Version 1.2 - Self Assignment", test_counter)
    double_iterator = double_iterator;
    shape_iterator = shape_iterator;
    exam_iterator = exam_iterator;
    PASSED_THE("const_iterator Copy Assignment Operator (=) - Version 1.2 - Self Assignment")
    PASSED_THE_("const_iterator Copy Assignment Operator (=) - Version 1.2 - Self Assignment")

    test_counter++;
    LET_ME_TEST("const_iterator Statement Operator (==)", test_counter)
    LET_ME_TEST_("const_iterator Statement Operator (==)", test_counter)
    assert((empty_double_iterator==double_iterator)==true);
    assert((empty_shape_iterator==shape_iterator)==true);
    assert((empty_exam_iterator==exam_iterator)==true);
    PASSED_THE("const_iterator Statement Operator (==)")
    PASSED_THE_("const_iterator Statement Operator (==)")

    test_counter++;
    LET_ME_TEST("const_iterator Statement Operator (++) - PreFix (++it)", test_counter)
    LET_ME_TEST_("const_iterator Statement Operator (++) - PreFix (++it)", test_counter)
    SortedList<double>::const_iterator temp1 = double_iterator;
    SortedList<double>::const_iterator temp2 = double_iterator;
    temp1++;
    temp1++;
    temp2++;
    temp2++;
    assert(temp1==temp2);
    PASSED_THE("const_iterator Statement Operator (++) - PreFix (++it)")
    PASSED_THE_("const_iterator Statement Operator (++) - PreFix (++it)")

    test_counter++;
    LET_ME_TEST("const_iterator Statement Operator (++) - PostFix (it++)", test_counter)
    LET_ME_TEST_("const_iterator Statement Operator (++) - PostFix (it++)", test_counter)
    temp1 = double_iterator;
    temp2 = double_iterator;
    SortedList<double>::const_iterator temp3 = temp1++;
    assert(temp3==temp2);
    temp3++;
    temp2++;
    assert(temp2==temp1);
    PASSED_THE("const_iterator Statement Operator (++) - PostFix (it++)")
    PASSED_THE_("const_iterator Statement Operator (++) - PostFix (it++)")

    test_counter++;
    LET_ME_TEST("const_iterator Operator (*)", test_counter)
    LET_ME_TEST_("const_iterator Operator (*)", test_counter)
    temp1 = double_iterator;
    assert((*(temp1))==-1);
    PASSED_THE("const_iterator Operator (*)")
    PASSED_THE_("const_iterator Operator (*)")

    test_counter++;
    LET_ME_TEST("SortedList End Method", test_counter)
    LET_ME_TEST_("SortedList End Method", test_counter)
    SortedList<double>::const_iterator end_double_iterator = Double_list.end();
    SortedList<Point>::const_iterator end_shape_iterator = Shape.end();
    PASSED_THE("SortedList End Method")
    PASSED_THE_("SortedList End Method")

    test_counter++;
    LET_ME_TEST("const_iterator OutOfRange Exception", test_counter)
    LET_ME_TEST_("const_iterator OutOfRange Exception", test_counter)
    try{
        end_double_iterator++;
        end_shape_iterator++;
    }
    catch(std::out_of_range& e){
        cout << "SUCCESS - Exception Caught" << endl;
        to_the_file << "SUCCESS - Exception Caught" << endl;
    }
    try{
        ++end_double_iterator;
        ++end_shape_iterator;
    }
    catch(std::out_of_range& e){
        cout << "SUCCESS - Exception Caught" << endl;
        to_the_file << "SUCCESS - Exception Caught" << endl;
    }
    PASSED_THE("const_iterator OutOfRange Exception")
    PASSED_THE_("const_iterator OutOfRange Exception")
    cout<<endl;
    to_the_file<<endl;
    printDouble(Double_list, to_the_file);
    printShape(Shape, to_the_file);
    printShape(Rect, to_the_file);
    printExam(Exams_list, to_the_file);

    test_counter++;
    LET_ME_TEST("SortedList Remove Method", test_counter)
    LET_ME_TEST_("SortedList Remove Method", test_counter)
    temp1 = Double_list.begin();
    while(*temp1!=1.5)
    {
        temp1++;
    }
    Double_list.remove(temp1);
    temp1 = double_iterator;
    while(*temp1!=3.5)
    {
        temp1++;
    }
    Double_list.remove(temp1);
    temp1 = double_iterator;
    while(*temp1!=3)
    {
        temp1++;
    }
    Double_list.remove(temp1);
    temp1 = double_iterator;
    while(*temp1!=3)
    {
        temp1++;
    }
    Double_list.remove(temp1);
    temp1 = double_iterator;
    while(*temp1!=4)
    {
        temp1++;
    }
    Double_list.remove(temp1);
    Double_list.remove(Double_list.begin());

    SortedList<Point>::const_iterator temp = Shape.begin();
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);
    temp = Shape.begin();
    temp++;
    temp++;
    Shape.remove(temp);
    temp = Shape.begin();
    Shape.remove(temp);

    SortedList<ExamDetails>::const_iterator temp_exam = Exams_list.begin();
    temp_exam++;
    temp_exam++;
    temp_exam++;
    Exams_list.remove(temp_exam);

    printDouble(Double_list, to_the_file);
    printShape(Shape, to_the_file);
    printExam(Exams_list, to_the_file);
    PASSED_THE("SortedList Remove Method")
    PASSED_THE_("SortedList Remove Method")

    test_counter++;
    LET_ME_TEST("SortedList Length Method", test_counter)
    LET_ME_TEST_("SortedList Length Method", test_counter)
    cout << Double_list.length() << endl;
    cout << Empty_Double_List.length() << endl;
    cout << Shape.length() << endl;
    cout << Empty_Shape.length() << endl;
    cout << Exams_list.length() << endl;
    cout << Empty_Exams_list.length() << endl;
    to_the_file << Double_list.length() << endl;
    to_the_file << Empty_Double_List.length() << endl;
    to_the_file << Shape.length() << endl;
    to_the_file << Empty_Shape.length() << endl;
    to_the_file << Exams_list.length() << endl;
    to_the_file << Empty_Exams_list.length() << endl;
    PASSED_THE("SortedList Length Method")
    PASSED_THE_("SortedList Length Method")

    Double_list.insert(0.0);
    Double_list.insert(1.0);
    Double_list.insert(2.0);
    Double_list.insert(-1.0);
    Double_list.insert(1.5);
    Double_list.insert(3.0);
    Double_list.insert(3.0);
    Double_list.insert(3.0);
    Double_list.insert(4.0);
    Double_list.insert(3.5);
    Shape.insert(A);
    Shape.insert(B);
    Shape.insert(C);
    Shape.insert(D);
    Shape.insert(E);
    Shape.insert(F);
    Shape.insert(G);
    Shape.insert(H);
    Shape.insert(I);
    Shape.insert(J);
    Shape.insert(K);
    Shape.insert(L);
    Shape.insert(M);
    Shape.insert(N);
    Shape.insert(O);
    Shape.insert(P);
    Shape.insert(AA);
    Shape.insert(AB);
    Shape.insert(BA);
    Shape.insert(CC);
    Shape.insert(CD);
    Shape.insert(DC);
    Shape.insert(Y);
    Shape.insert(Z);
    Rect.insert(A);
    Rect.insert(B);
    Rect.insert(J);
    Rect.insert(K);
    Rect.insert(L);
    Rect.insert(M);
    Rect.insert(N);
    Rect.insert(P);
    Exams_list.insert(exam1);
    Exams_list.insert(exam2);
    Exams_list.insert(exam3);
    Exams_list.insert(exam4);
    Exams_list.insert(exam5);
    Exams_list.insert(exam6);
    Exams_list.insert(exam7);
    Exams_list.insert(exam8);
    Exams_list.insert(exam9);
    Exams_list.insert(exam10);

    test_counter++;
    LET_ME_TEST("SortedList Filter Method", test_counter)
    LET_ME_TEST_("SortedList Filter Method", test_counter)
    SortedList<double> Filtered_Double_List = Double_list.filter(isEven);
    SortedList<Point> Filtered_Shape = Shape.filter(isPositivePoint);
    SortedList<ExamDetails> Filtered_Exam_List = Exams_list.filter(isntEmptyLink);
    printDouble(Filtered_Double_List, to_the_file);
    printShape(Filtered_Shape, to_the_file);
    printExam(Filtered_Exam_List, to_the_file);
    PASSED_THE("SortedList Filter Method")
    PASSED_THE_("SortedList Filter Method")

    Double_list.insert(0.0);
    Double_list.insert(1.0);
    Double_list.insert(2.0);
    Double_list.insert(-1.0);
    Double_list.insert(1.5);
    Double_list.insert(3.0);
    Double_list.insert(3.0);
    Double_list.insert(3.0);
    Double_list.insert(4.0);
    Double_list.insert(3.5);
    Shape.insert(A);
    Shape.insert(B);
    Shape.insert(C);
    Shape.insert(D);
    Shape.insert(E);
    Shape.insert(F);
    Shape.insert(G);
    Shape.insert(H);
    Shape.insert(I);
    Shape.insert(J);
    Shape.insert(K);
    Shape.insert(L);
    Shape.insert(M);
    Shape.insert(N);
    Shape.insert(O);
    Shape.insert(P);
    Shape.insert(Q);
    Shape.insert(R);
    Shape.insert(S);
    Rect.insert(A);
    Rect.insert(B);
    Rect.insert(J);
    Rect.insert(K);
    Rect.insert(L);
    Rect.insert(M);
    Rect.insert(N);
    Rect.insert(P);
    Exams_list.insert(exam1);
    Exams_list.insert(exam2);
    Exams_list.insert(exam3);
    Exams_list.insert(exam4);
    Exams_list.insert(exam5);
    Exams_list.insert(exam6);
    Exams_list.insert(exam7);
    Exams_list.insert(exam8);
    Exams_list.insert(exam9);
    Exams_list.insert(exam10);

    test_counter++;
    LET_ME_TEST("SortedList Apply Method", test_counter)
    LET_ME_TEST_("SortedList Apply Method", test_counter)
    Filtered_Double_List = Double_list.apply(isInteger);
    Filtered_Shape = Shape.apply(makeRect);
    Filtered_Exam_List = Exams_list.apply(isM);
    printDouble(Filtered_Double_List, to_the_file);
    printShape(Filtered_Shape, to_the_file);
    printExam(Filtered_Exam_List, to_the_file);
    PASSED_THE("SortedList Apply Method")
    PASSED_THE_("SortedList Apply Method")

    cout << endl << "Now compare the output in the file 'Your_output.txt' with 'My_output.txt' manually or with diffmerge.";
    cout << endl << "Then, Check Memory Leak.";
    to_the_file << endl << "Now compare the output in the file 'Your_output.txt' with 'My_output.txt' manually or with diffmerge.";
    to_the_file << endl << "Then, Check Memory Leak.";
    to_the_file.close();
    return 0;
}