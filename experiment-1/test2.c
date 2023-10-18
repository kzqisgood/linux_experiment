#include <stdio.h>

struct Student {
    int year;
    // 其他属性
};

int main() {
    int n = 10;  // 假设有10个学生数据
    struct Student students[n];

    // 写入数据到文件
    FILE *file = fopen("a.dat", "w");  // 以二进制写入模式打开文件
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }

    // 假设有一个保存学生数据的数组students
    for (int i = 0; i < n; i++) {
        // 假设给每个学生的年份赋值
        students[i].year = 2000 + i;

        // 写入结构体数据到文件
        if (fwrite(&students[i], sizeof(struct Student), 1, file) != 1) {
            perror("写入文件失败");
            fclose(file);
            return 1;
        }
    }

    // 关闭文件
    fclose(file);

    // 从文件中读取并输出属性信息
    file = fopen("a.dat", "r");  // 以二进制读取模式打开文件
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }

    struct Student readStudent;
    while (fread(&readStudent, sizeof(struct Student), 1, file) == 1) {
        printf("年份：%d\n", readStudent.year);
        // 输出其他属性信息
    }

    // 关闭文件
    fclose(file);

    return 0;
}

