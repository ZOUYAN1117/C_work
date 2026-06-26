/**
 * 文件: 文件读写模板.c
 * 描述: C 语言文件操作核心模板与技巧，包含只读/只写文件打开校验、字符级/行级/格式化读写、文件定位及结构化读写样例。
 * 
 * 记忆要点速查：
 * 1. fopen 必须检查返回值是否为 NULL。
 * 2. fgets 最多读 n-1 个字符并保留行末的 '\n'，读到文件尾返回 NULL。
 * 3. fputs 写入字符串时不会像 puts 那样自动追加 '\n'，需要换行时手动 fputs("\n", fp)。
 * 4. fscanf / scanf 遇到空格会截断，读入整行应使用 fgets。
 * 5. fseek(fp, 0, SEEK_SET) 可将读写指针重新定位到文件头部。
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * 结构体: Student - 学生结构化数据结构定义 (供格式化读写演示使用)
 * 成员：
 * - no: 学号
 * - name: 姓名
 * - score: 成绩
 */
struct Student {
    int no;
    char name[32];
    int score;
};

/**
 * 演示：基本的只读和只写文件打开及其错误检查
 * 参数：无
 * 返回值：无
 */
void demo_file_open(void) {
    FILE *fp;

    // 1. 只读方式打开 (文件必须存在，若不存在则 fopen 返回 NULL)
    if ((fp = fopen("input.txt", "r")) == NULL) {
        printf("Can't open file %s!\n", "input.txt");
        return; // 出错返回
    }
    
    // 2. 只写方式打开 (文件若存在会被覆盖，若不存在则新建)
    FILE *out;
    if ((out = fopen("output.txt", "w")) == NULL) {
        printf("Can't open file %s!\n", "output.txt");
        fclose(fp); // 关闭刚才打开的文件以释放资源
        return;
    }

    // 正常关闭文件流
    fclose(fp);
    fclose(out);
}

/**
 * 演示：字符级的文件输入输出 (fgetc / fputc)
 * 参数：
 * - in: 输入文件指针
 * - out: 输出文件指针
 * 返回值：无
 */
void demo_char_io(FILE *in, FILE *out) {
    int c; // 必须用 int 接收，因为 EOF 的值为 -1
    
    // 循环读入单个字符，直到读到文件尾 (EOF)
    while ((c = fgetc(in)) != EOF) {
        fputc(c, out); // 输出字符到文件
    }
}

/**
 * 演示：行级的文件输入输出 (fgets / fputs)
 * 参数：
 * - in: 输入文件指针
 * - out: 输出文件指针
 * 返回值：无
 */
void demo_line_io(FILE *in, FILE *out) {
    char line[1024];

    // fgets 最多读取 sizeof(line)-1 个字符，保留行末 '\n'
    // 读到文件尾或出错时返回 NULL
    while (fgets(line, sizeof(line), in) != NULL) {
        fputs(line, out); // 注意：fputs 不会自动添加 '\n'
    }
}

/**
 * 演示：格式化读写 (fscanf / fprintf)
 * 参数：
 * - in: 输入文件指针
 * - out: 输出文件指针
 * 返回值：无
 */
void demo_formatted_io(FILE *in, FILE *out) {
    int n = 0;
    struct Student info[51];
    
    // 1. 从输入文件读取学生个数
    if (fscanf(in, "%d", &n) != 1) {
        return;
    }
    
    // 2. 循环读取格式化学生信息并打印到输出文件
    for (int i = 0; i < n && i < 51; i++) {
        // fscanf 读取时，遇到空格、换行等空白符会自动截断
        if (fscanf(in, "%d%s%d", &info[i].no, info[i].name, &info[i].score) == 3) {
            // fprintf 可以将格式化后的文本输出到目标文件
            fprintf(out, "%d %s %d\n", info[i].no, info[i].name, info[i].score);
        }
    }
}

/**
 * 演示：文件定位操作 (fseek)
 * 参数：
 * - fp: 文件指针
 * 返回值：无
 */
void demo_file_seek(FILE *fp) {
    // 将文件读写指针重置到文件头部 (重新从头扫描)
    fseek(fp, 0, SEEK_SET);
}

/**
 * 自定义字符串子串匹配函数 (在字符串 s 中查找子串 t)
 * 参数：
 * - s: 源字符串
 * - t: 待匹配的目标子串
 * 返回值：子串第一次出现的首字符下标位置，若未匹配成功则返回 -1
 */
int str_index(char s[], char t[]) {
    int i, j, k;
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        // 若子串 t 匹配完毕，说明匹配成功
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

/**
 * 演示：经典文本过滤/查找应用程序 (从文件逐行读取，打印包含关键词的行)
 * 参数：
 * - filename: 待读取文件名
 * - search_str: 待查找的关键词
 * 返回值：0 表示执行完成，1 表示文件打开失败
 */
int run_text_search_app(const char *filename, const char *search_str) {
    char line[1024];
    FILE *fp;

    // 打开文件并做防御性空指针校验
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("Can't open file %s!\n", filename);
        return 1;
    }

    // 逐行读取文件内容，检索匹配并打印
    char temp_line[1024];
    strcpy(temp_line, search_str); // 保证引用到 search_str
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (str_index(line, temp_line) >= 0) {
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}

/**
 * 主函数：演示完整骨架示例 (以行拷贝模式为例)
 * 参数：无
 * 返回值：0 表示运行正常，1 表示文件开启失败
 */
int main() {
    FILE *in, *out;

    // ===== 1. 打开输入文件（只读 + 错误检查） =====
    if ((in = fopen("input.txt", "r")) == NULL) {
        printf("Can't open file input.txt!\n");
        return 1;
    }

    // ===== 2. 打开输出文件（只写 + 错误检查） =====
    if ((out = fopen("output.txt", "w")) == NULL) {
        printf("Can't open file output.txt!\n");
        fclose(in); // 关闭已成功开启的文件指针
        return 1;
    }

    // ===== 3. 逐行读取拷贝演示 =====
    char line[1024];
    while (fgets(line, sizeof(line), in) != NULL) {
        // 在此处处理 line
        fputs(line, out); // 注意：fputs 不会自动追换行符
    }

    // ===== 4. 重置定位演示 =====
    demo_file_seek(in);

    // ===== 5. 关闭文件流释放资源 =====
    fclose(in);
    fclose(out);
    
    // 可选：为了消除函数未引用警告，做虚假引用
    if (0) {
        demo_file_open();
        demo_char_io(NULL, NULL);
        demo_line_io(NULL, NULL);
        demo_formatted_io(NULL, NULL);
        run_text_search_app(NULL, NULL);
    }
    
    return 0;
}
