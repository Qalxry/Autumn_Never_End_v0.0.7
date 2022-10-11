#ifndef GAMEIO_HPP
#define GAMEIO_HPP
#include <string>
using namespace std;

//-----------------------------------------------------------------------------------------------

//���ٶ�ȡ�ļ�����
char fileReadBuffer[1 << 20], *read_p1 = fileReadBuffer, *read_p2 = fileReadBuffer;
inline int getChar() {
    //��� p1 != p2��˵�� fread ��������δ��ȫ����������ǰ�ַ����ƶ�ָ�뵽��һ�ַ�
    //��� p1 == p2��˵��Ϊ�ļ����˻�ĩβ������ fread ���ж��Ƿ������ȡ������
    return read_p1 == read_p2 && (read_p2 = (read_p1 = fileReadBuffer) + fread(fileReadBuffer, 1, 1 << 20, stdin), read_p1 == read_p2) ? EOF : *read_p1++;
}

template <typename T>
inline T qread() {
    T a = 0; 
    char c = getChar(), f = 1;
    //������������ķ���
    for (; c < '0' || c > '9'; c = getChar())
        //��ȡ�������ķ��ţ����������һ�����ֵ�ʱ���-1
        if (c == '-') 
             f = -f;
        //��ȡ���ļ���ĩβ����ֹ��ȡ
        else if (c == -1) 
            return -1;
    //��ʽ��ȡ���ַ���
    for (; c >= '0' && c <= '9'; c = getChar())
        //����λ�������һλ��10���ټ�����һλ
        a = (a << 1) + (a << 3) + (c ^ 48);
    return a * f;
}

//-----------------------------------------------------------------------------------------------

//������������������
char fastWriteBuffer[1 << 20], * write_p = fastWriteBuffer;
inline void qwrite(register int x) {
    static int _tempNumber[35]; 
    register char _it = 0; // _q ��һ��ջ
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

////���ٶ�ȡͼ�����ݲ�������ص�����
//short picBuffer[1 << 20], * pic_p = picBuffer, * pic_p1 = picBuffer, * pic_p2 = picBuffer;
//char consoleInitChar[22] = "\033[48;2;000;000;000m  ";
//inline short getShort() {
//    //��� p1 != p2��˵�� fread ��������δ��ȫ����������ǰ�ַ����ƶ�ָ�뵽��һ�ַ�
//    //��� p1 == p2��˵��Ϊ�ļ����˻�ĩβ������ fread ���ж��Ƿ������ȡ������
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