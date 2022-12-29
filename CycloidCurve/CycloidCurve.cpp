// CycloidCurve.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Preprocess.cpp"
#include "CycloidGear.cpp"
#include "PointInspection.cpp"

using namespace std;

int main()
{
            string foldername;
            string file_name; //= "E:\\10C\\00 摆线轮齿形分析\\01 修形用点\\T031.txt";
            string file_name1, file_name2, file_name3; //= "E:\\10C\\00 摆线轮齿形分析\\01 修形用点\\T031_pol.txt";
            string file_name10, file_name20, file_name30;
            cout << "\n**********************************************\n" << endl;
            string gearname;
            string sharedFolder = "\\\\172.21.110.160\\技术部共享\\RV-项目\\03-数据分析\\摆线点云\\";
            int Z = 0;
            cout << "输入原始点云所在文件夹位置:" << endl;
            getline(cin, foldername);
            cout << endl << "\n输入样机拆机编号（例如，10C输入T01 T02 T03）:" << endl;
            getline(cin, gearname);
            cout << endl << "\n输入摆线齿轮齿数:" << endl;
            cin >> Z;
            Preprocess original;
            PointInspection pi;
            istringstream iss(gearname);
            string gear;
            string assemblynum;
            assemblynum.push_back(gearname[0]);
            vector<string> svec;
            if (isalpha(gearname[1]))
                assemblynum.push_back(gearname[1]);
            while (iss >> gear) {
                cout << gear << endl;
                svec.push_back(gear + "1");
                svec.push_back(gear + "2");
            }
            for (const string& postfix : svec) {
                bool flag = false;
                CycloidGear rv;
                file_name = foldername + "\\" + postfix + ".txt";
                file_name1 = foldername + "\\" + postfix + "_dev.txt";
                file_name3 = foldername + "\\" + postfix + "_mod.txt";
                file_name2 = foldername + "\\" + postfix + "_pol.txt";

                file_name10 = sharedFolder + postfix + "_dev.txt";
                file_name30 = sharedFolder + postfix + "_mod.txt";
                file_name20 = sharedFolder + postfix + "_pol.txt";
                ifstream ifs(file_name);
                if (ifs) {
                    ifs.close();
                    cout << endl << "<" << file_name << "> is processing..." << endl;
                    original.readData(file_name, rv.zeiss);
                    original.Car2Pol(rv.zeiss, rv.zeiss_pol);
                    if (pi.DisorderInspection(rv.zeiss_pol)) {
                        if (!pi.DuplicateInspection(rv.zeiss)) {
                            if (pi.AxisToAddendum(rv.zeiss, rv.zeiss_pol))
                                pi.PointRotation(rv.zeiss, rv.zeiss_pol, -3.1415926 / Z);
                            pi.SwitchInitialPoint(rv.zeiss, rv.zeiss_pol, Z);
                            original.writeDataDev(file_name1, rv.zeiss);
                            original.writeDataMod(file_name3, rv.zeiss);
                            // original.writeDataDev(file_name2, rv.zeiss_pol);
                            flag = true;
                        }
                        //pi.PointRotation(rv.zeiss, rv.zeiss_pol, -(rv.zeiss_pol[0].second));   
                    }
                }
                else
                    cout << file_name << " does not exist!" << endl;
                if (flag)
                    cout << file_name << " is converted successfully!" << endl;
                else
                    cout << "Problems above occurs, " << file_name << " has not been converted!" << endl;
            }
            cout << endl << "Conversion finished!" << endl;

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
