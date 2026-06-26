/**
 * 文件: 日期与时间.c
 * 描述: 日期与时间的相关运算操作，包含闰年判断、日期合法性检验、乱序日期时间进位整理规范化、计算星期几以及时间重叠判断。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 静态查找数组：保存平年每月天数
static int dayof[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
 * 判断指定年份是否为闰年
 * 参数：
 * - y: 待判断的整型年份值
 * 返回值：1 表示为闰年，0 表示平年
 */
int isleapyear(int y) {
    return (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0));
}

/**
 * 校验指定日期格式数字 (yyyymmdd，例如 20241025) 是否为合法有效日期
 * 参数：
 * - x: 待校验的整型日期数值
 * 返回值：1 表示为合法日期，0 表示非合法有效日期
 */
int checkdate(int x) {
    int y = x / 10000;
    int m = (x / 100) % 100;
    int d = x % 100;
    if (m <= 0 || m >= 13)
        return 0;
    int day = dayof[m];
    if (m == 2 && isleapyear(y))
        day++;
    if (d <= 0 || d > day)
        return 0;
    return 1;
}

/**
 * 规范化可能包含越界/异常数值的日期时间，自动向高位进位(或借位)并打印规范化时间
 * 参数：
 * - y: 整型年份数值
 * - mon: 整型月份数值
 * - d: 整型天数值
 * - h: 整型小时数值
 * - min: 整型分钟数值
 * 返回值：无
 */
void normalize_and_print_time(int y, int mon, int d, int h, int min) {
    // 1. 分钟进/借位到小时
    h += (min / 60);
    min %= 60;
    if (min < 0) {
        min += 60;
        h--;
    }
    
    // 2. 小时进/借位到天数
    d += (h / 24);
    h %= 24;
    if (h < 0) {
        h += 24;
        d--;
    }
    
    // 3. 月份向年份进行进位 (先减去偏移基准再运算)
    y += (mon - 1) / 12;
    mon = (mon - 1) % 12 + 1;
    if (mon <= 0) {
        mon += 12;
        y--;
    }
    
    int tempday = dayof[mon] + (isleapyear(y) && (mon == 2));
    
    // 4. 天数正向超限进位 (递推减去当月天数，月份+1)
    while (d > tempday) {
        d -= tempday;
        mon++;
        y += (mon - 1) / 12;
        mon = (mon - 1) % 12 + 1;
        tempday = dayof[mon] + (isleapyear(y) && (mon == 2));
    }
    
    // 5. 天数负向超限借位 (递推加上上月天数，月份-1)
    while (d <= 0) {
        mon--;
        if (mon <= 0) {
            mon = 12;
            y--;
        }
        tempday = dayof[mon] + (isleapyear(y) && (mon == 2));
        d += tempday;
    }
    
    // 6. 按标准格式输出
    printf("%04d.%02d.%02d %02d:%02d\n", y, mon, d, h, min);
}

/**
 * 根据日期整数 ttime (格式为 yyyymmdd) 使用基姆拉尔森计算公式得到星期几
 * 参数：
 * - ttime: 待计算 of 日期整型数值
 * 返回值：表示星期几的整型代号 (0: 星期日, 1: 星期一, 2: 星期二, ..., 6: 星期六)
 */
int getweek(int ttime) {
    int year = ttime / 10000;
    int month = (ttime % 10000) / 100;
    int day = ttime % 100;
    
    if (month < 3) {
        month += 12;
        year--;
    }
    int y = year % 100;
    int c = year / 100;
    
    int w = (y + (y / 4) + (c / 4) - 2 * c + (13 * (month + 1)) / 5 + day - 1) % 7;
    if (w < 0) {
        w += 7;
    }
    return w;
}

/**
 * 打印星期几代号数值对应的英文名称
 * 参数：
 * - w: 表示星期几的整型代号数值 (0..6)
 * 返回值：无
 */
void printweek(int w) {
    const char *weeks[] = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    if (w >= 0 && w < 7) {
        printf("%s\n", weeks[w]);
    } else {
        printf("Invalid week value\n");
    }
}

/**
 * 判断两段 6 位时间串 [in1,out1] 与 [in2,out2] 是否重叠 (端点重合也算重叠)
 * 参数：
 * - in1: 第一段的开始时间
 * - out1: 第一段的结束时间
 * - in2: 第二段的开始时间
 * - out2: 第二段的结束时间
 * 返回值：1 表示时间重叠，0 表示未重叠
 */
int timeOverlap(const char *in1, const char *out1,
                const char *in2, const char *out2)
{
    if (strcmp(in1, in2) >= 0 && strcmp(in1, out2) <= 0)
        return 1;
    if (strcmp(in2, in1) >= 0 && strcmp(in2, out1) <= 0)
        return 1;
    return 0;
}
