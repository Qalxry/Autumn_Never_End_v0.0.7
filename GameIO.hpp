#ifndef GAMEIO_HPP
#define GAMEIO_HPP
#include <string>
using namespace std;

//-----------------------------------------------------------------------------------------------

//快速读取文件数据
char fileReadBuffer[1 << 20], *read_p1 = fileReadBuffer, *read_p2 = fileReadBuffer;
inline int getChar() {
    //如果 p1 != p2，说明 fread 所读数据未完全输出，输出当前字符并移动指针到下一字符
    //如果 p1 == p2，说明为文件开端或末尾，进行 fread 并判断是否继续读取到数据
    return read_p1 == read_p2 && (read_p2 = (read_p1 = fileReadBuffer) + fread(fileReadBuffer, 1, 1 << 20, stdin), read_p1 == read_p2) ? EOF : *read_p1++;
}

template <typename T>
inline T qread() {
    T a = 0; 
    char c = getChar(), f = 1;
    //忽略数字以外的符号
    for (; c < '0' || c > '9'; c = getChar())
        //读取到负数的符号，则在输出下一个数字的时候乘-1
        if (c == '-') 
             f = -f;
        //读取到文件的末尾，终止读取
        else if (c == -1) 
            return -1;
    //正式读取数字符号
    for (; c >= '0' && c <= '9'; c = getChar())
        //利用位运算把上一位乘10，再加上下一位
        a = (a << 1) + (a << 3) + (c ^ 48);
    return a * f;
}

//-----------------------------------------------------------------------------------------------

//快速输出数据至输出流
char fastWriteBuffer[1 << 20], * write_p = fastWriteBuffer;
inline void qwrite(register int x) {
    static int _tempNumber[35]; 
    register char _it = 0; // _q 是一个栈
    do { 
        _tempNumber[_it++] = x % 10;
        x /= 10;
    } while (x);
    for (register char c = _tempNumber[--_it] + 48; _it; c = _tempNumber[--_it] + 48) {
        if (write_p - fastWriteBuffer == 1 << 20) {
            fwrite(fastWriteBuffer, 1, 1 << 20, stdout);
            write_p = fastWriteBuffer;
        }
        *write_p++ = c;
    }
}

//fwrite(fastWriteBuffer, 1, write_p - fastWriteBuffer, stdout);

//-----------------------------------------------------------------------------------------------

////快速读取图像数据并输出像素点数据
//short picBuffer[1 << 20], * pic_p = picBuffer, * pic_p1 = picBuffer, * pic_p2 = picBuffer;
//char consoleInitChar[22] = "\033[48;2;000;000;000m  ";
//inline short getShort() {
//    //如果 p1 != p2，说明 fread 所读数据未完全输出，输出当前字符并移动指针到下一字符
//    //如果 p1 == p2，说明为文件开端或末尾，进行 fread 并判断是否继续读取到数据
//    return pic_p1 == pic_p2 && (pic_p2 = (pic_p1 = picBuffer) + fread(picBuffer, 2, 1 << 20, stdin), pic_p1 == pic_p2) ? EOF : *pic_p1++;
//}
//inline void quickPrintPic(register int x) {
//    register short _qPP_it = 0, _qPP_temp = getShort();
//    while(_qPP_temp != EOF) {
//        picBuffer[_qPP_it++] = getShort();
//        _qPP_temp = getShort();
//    }
//    for (register char c = _tempNumber[--_it] + 48; _it; c = _tempNumber[--_it] + 48) {
//        if (write_p - fastWriteBuffer == 1 << 20) {
//            fwrite(fastWriteBuffer, 1, 1 << 20, stdout);
//            write_p = fastWriteBuffer;
//        }
//    }
//}

//-----------------------------------------------------------------------------------------------

#endif