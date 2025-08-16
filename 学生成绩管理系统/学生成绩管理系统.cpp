#include <iostream>
#include <cstring>
#include <windows.h>
#include <cstdio>
using namespace std;

typedef struct {
    // 英文单词
    char yingyu[20];
    // 中文释义
    char shiyi[80];
} danci;

// 函数声明
int creat(danci dan[200], int num);
void print(danci dan[200], int num);
int del(danci dan[200], int num);
int chaxun(danci dan[200], int num);
void bianji(danci dan[200], int n);

int main() {
    // 解决控制台乱码：设置为 UTF-8 编码
    SetConsoleOutputCP(65001);
    // 设置控制台输入编码为 UTF-8（关键！解决输入中文乱码）
    SetConsoleCP(65001);

    int num = 0, n = 0;
    char MenuItem;
    danci dan[200];

    cout << "\n";
    cout << "         |*********学生成绩管理系统*********|\n";
    cout << "         |--------------------------------|\n";
    cout << "         |             主菜单项             |\n";
    cout << "         |-------------------------------|\n";
    cout << "         |         1--- 增词功能            |\n";
    cout << "         |         2--- 查找功能            |\n";
    cout << "         |         3--- 修改功能            |\n";
    cout << "         |         4--- 删除功能            |\n";
    cout << "         |         5--- 维护功能            |\n";
    cout << "         |         0--- 退出系统            |\n";

    while (true) {
        cout << "\n    请输入选项(0-5):";
        cin >> MenuItem;

        switch (MenuItem) {
            case '1': {
                cout << " 欢迎进入添加功能\n";
                cout << "请输入要输入单词个数: ";
                cin >> num;
                num = creat(dan, num);
                break;
            }
            case '2': {
                cout << "欢迎进入查找功能：\n";
                n = chaxun(dan, num);
                break;
            }
            case '3': {
                cout << "欢迎进入修改功能：\n";
                // 增加判断，避免查询未找到时进入修改
                if (n != -1) bianji(dan, n);
                else cout << "请先通过【查找功能】定位单词！\n";
                break;
            }
            case '4': {
                cout << "欢迎进入删除功能：\n";
                num = del(dan, num);
                break;
            }
            case '5': {
                cout << "欢迎进入维护功能\n";
                print(dan, num);
                break;
            }
            case '0': {
                cout << "\n    谢谢使用！\n";
                cout << "\n     请按回车键继续..... \n";
                // 正常退出
                return 0;
            }
            default: {
                cout << "无效选项，请重新输入！\n";
                break;
            }
        }
    }
}

// 添加功能函数
int creat(danci dan[200], int num) {
    int i = 0;
    char yy;

    for (i = 0; i < num; i++) {
        cout << "单词[" << i + 1 << "]：";
        cin >> dan[i].yingyu;
        cout << "释义[" << i + 1 << "]：";
        cin >> dan[i].shiyi;
    }

    while (true) {
        cout << "是否继续添加（y/Y 继续，其他退出）: ";
        cin >> yy;
        if (yy != 'y' && yy != 'Y') break;

        int m;
        cout << "请输入要继续添加的单词个数: ";
        cin >> m;
        // 防止数组越界
        if (num + m >= 200) {
            cout << "最多只能添加到 200 个单词，剩余容量: " << 200 - num << "\n";
            m = 200 - num;
        }
        for (int j = num; j < num + m; j++) {
            cout << "单词[" << j + 1 << "]：";
            cin >> dan[j].yingyu;
            cout << "释义[" << j + 1 << "]：";
            cin >> dan[j].shiyi;
        }
        num += m;
    }
    return num;
}

// 输出功能
void print(danci dan[200], int num) {
    char yy;
    do {
        cout << "\n=== 当前单词列表 ===\n";
        for (int i = 0; i < num; i++) {
            cout << "单词：" << dan[i].yingyu << "  |  释义：" << dan[i].shiyi << "\n";
        }
        cout << "是否继续查看（y/Y 继续，其他退出）: ";
        cin >> yy;
    } while (yy == 'y' || yy == 'Y');
}

// 删除功能
int del(danci dan[200], int num) {
    char d[20], yy;
    while (true) {
        cout << "请输入要删除的单词: ";
        cin >> d;

        int findIdx = -1;
        for (int i = 0; i < num; i++) {
            if (strcmp(dan[i].yingyu, d) == 0) {
                findIdx = i;
                break;
            }
        }

        if (findIdx != -1) {
            for (int j = findIdx; j < num - 1; j++) {
                // 前移覆盖
                strcpy(dan[j].yingyu, dan[j + 1].yingyu);
                strcpy(dan[j].shiyi, dan[j + 1].shiyi);
            }
            num--;
            cout << "删除成功！当前剩余 " << num << " 个单词\n";
        } else {
            cout << "未找到该单词，无法删除！\n";
        }

        cout << "是否继续删除（y/Y 继续，其他退出）: ";
        cin >> yy;
        if (yy != 'y' && yy != 'Y') break;
    }
    return num;
}

// 查询功能
int chaxun(danci dan[200], int num) {
    char d[20], yy;
    while (true) {
        cout << "请输入要查询的单词: ";
        cin >> d;

        int findIdx = -1;
        for (int i = 0; i < num; i++) {
            if (strcmp(dan[i].yingyu, d) == 0) {
                findIdx = i;
                cout << "单词：" << dan[i].yingyu << "  |  释义：" << dan[i].shiyi << "\n";
                break;
            }
        }
        if (findIdx == -1) {
            cout << "未找到该单词！\n";
        }

        cout << "是否继续查询（y/Y 继续，其他退出）: ";
        cin >> yy;
        if (yy != 'y' && yy != 'Y') {
            // 返回找到的索引，没找到返回 -1
            return findIdx;
        }
    }
}

// 修改功能
void bianji(danci dan[200], int n) {
    int men;
    cout << "修改单词请按1，修改释义请按2,退出请按0\n";
    while (true) {
        cout << "\n    请输入修改选项(0-2):";
        cin >> men;

        switch (men) {
            case 1: {
                cout << "请输入新单词: ";
                cin >> dan[n].yingyu;
                cout << "修改成功！\n";
                break;
            }
            case 2: {
                cout << "请输入新释义: ";
                cin >> dan[n].shiyi;
                cout << "修改成功！\n";
                break;
            }
            case 0: {
                cout << "\n    修改结束！\n";
                return;
            }
            default: {
                cout << "无效选项，请重新输入！\n";
                break;
            }
        }
    }
}