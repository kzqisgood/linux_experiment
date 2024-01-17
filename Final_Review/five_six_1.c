#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semNorthSouth; // 南北方向的信号量
sem_t semEastWest;   // 东西方向的信号量
void *northSouthTraffic(void *arg) {
    while (1) {
        sem_wait(&semEastWest); // 等待东西方向红灯
        printf("南北方向绿灯，车辆通行\n");
        sleep(5); // 模拟车辆通行时间
        printf("南北方向红灯\n");
        sem_post(&semEastWest); // 东西方向绿灯
        sleep(1); // 短暂等待，模拟交通信号切换
    }
}

void *eastWestTraffic(void *arg) {
    while (1) {
        sem_wait(&semNorthSouth); // 等待南北方向红灯
        printf("东西方向绿灯，车辆通行\n");
        sleep(5); // 模拟车辆通行时间
        printf("东西方向红灯\n");
        sem_post(&semNorthSouth); // 南北方向绿灯
        sleep(1); // 短暂等待，模拟交通信号切换
    }
}
int main() {
    // 初始化信号量
    sem_init(&semNorthSouth, 0, 1); // 南北方向初始绿灯
    sem_init(&semEastWest, 0, 0);   // 东西方向初始红灯

    pthread_t th1, th2;

    // 创建线程
    pthread_create(&th1, NULL, northSouthTraffic, NULL);
    pthread_create(&th2, NULL, eastWestTraffic, NULL);

    // 等待线程结束（实际上这些线程是无限循环的）
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    // 销毁信号量
    sem_destroy(&semNorthSouth);
    sem_destroy(&semEastWest);

    return 0;
}

