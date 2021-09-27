// CycloidCurve.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Preprocess.h"
#include "CycloidGear.h"

using namespace std;

int main()
{
    string foldername;
    string gearname;
    string file_name; //= "E:\\10C\\00 摆线轮齿形分析\\01 修形用点\\T031.txt";
    string file_name1; //= "E:\\10C\\00 摆线轮齿形分析\\01 修形用点\\T031_pol.txt";
    cout << "输入原始点云所在文件夹位置:" << endl;
    getline(cin, foldername);
    cout << endl << "\n输入减速机拆机编号（例如，10C输入T）:" << endl;
    getline(cin, gearname);
    Preprocess original;
    vector<string> svec{"011", "012", "021", "022", "031", "032" };
    for (const string& postfix : svec) {
        CycloidGear rv;
        file_name = foldername + "\\" + gearname + postfix + ".txt";
        file_name1 = foldername + "\\" + gearname + postfix + "_converted.txt";
        cout << endl << "<" << file_name << "> is processing..." << endl;
        original.readData(file_name, rv.zeiss, rv.zeiss_ang);
        if (original.Car2Pol(rv.zeiss, rv.zeiss_pol))
            cout << "Cloud Points are converted successfully!" << endl;
        original.writeData(file_name1, rv.zeiss);
    }
    cout << endl << "Conversion finished!" << endl;
    getchar();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
