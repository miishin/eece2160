#include <iostream>
#include <cmath>
#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "GPIO.h"

using namespace std;


void basePos(int angle, int duration);
void bicepPos(int angle, int duration);
void elbowPos(int angle, int duration);
void wristPos(int angle, int duration);
void gripPos(int angle, int duration);

void baseSpeed(int start, int end, int speed);
void bicepSpeed(int start, int end, int speed);
void elbowSpeed(int start, int end, int speed);
void wristSpeed(int start, int end, int speed);
void gripSpeed(int start, int end, int speed);

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;
 
// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;

const int gpio_pbtnl_offset = 0x16C;

//Define servos
GPIO base(13);
GPIO bicep(10);
GPIO elbow(11);
GPIO wrist(12);
GPIO grip(0);

void reset();
void moveArm(int baseDegree);
void moveWrist(int baseDegree);
void swing();
void grab();


/**
 * Read a 4-byte value from the specified general-purpose I/O location.
 *
 * @param pBase     Base address returned by 'mmap'.
 * @param offset    Offset where device is mapped.
 * @return      Value read.
 */
int RegisterRead(char *pBase, int offset)
{
    return * (int *) (pBase + offset);
}


bool hold = false;

char *Initialize(int *fd)
{
    *fd = open( "/dev/mem", O_RDWR);
    return (char *) mmap(
            NULL,
            gpio_size,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            *fd,
            gpio_address);
}
 
/**
 * Close general-purpose I/O.
 *
 * @param pBase Virtual address where I/O was mapped.
 * @param fd    File descriptor previously returned by 'open'.
 */
void Finalize(char *pBase, int fd)
{
    munmap(pBase, gpio_size);
    close(fd);
}

int PushButtonGet(char *pBase, int current)
{
  for (int i = 0; i < 5; i++) {
    if (RegisterRead(pBase, 4 * i + gpio_pbtnl_offset) == 1) {
      if (i + 1 != current) {
      hold = false;
      return i + 1;
      } else {
	hold = true;
	return i + 1;
      }}
  }
  return 0;
}

int main() {

   int fd;
   char *pBase = Initialize(&fd);
   int button = 0;
   
   while (button == 0) {
   reset();
   button = PushButtonGet(pBase, button);
   }
   moveArm(180);
   grab();
   //moveWrist(180);
   swing();
   reset();
  

  return 0;
}



//Move to position
void basePos(int angle, int duration)
{
 base.GeneratePWM(20000, angle, duration);
}

void bicepPos(int angle, int duration)
{
 bicep.GeneratePWM(20000, angle, duration);
}

void elbowPos(int angle, int duration)
{
 elbow.GeneratePWM(20000, angle, duration);
}

void wristPos(int angle, int duration)
{
 wrist.GeneratePWM(20000, angle, duration);
}

void gripPos(int angle, int duration)
{
 grip.GeneratePWM(20000, angle, duration);
}


//Move to position at specific speed
void baseSpeed(int start, int end, int speed)
{
 base.GenerateVariablePWM(20000, start, end, (abs(start - end) / speed) * 50);
}

void bicepSpeed(int start, int end, int speed)
{
 bicep.GenerateVariablePWM(20000, start, end, (abs(start - end) / speed) * 50);
}

void elbowSpeed(int start, int end, int speed)
{
 elbow.GenerateVariablePWM(20000, start, end, (abs(start - end) / speed) * 50);
}

void wristSpeed(int start, int end, int speed)
{
 wrist.GenerateVariablePWM(20000, start, end, (abs(start - end) / speed) * 50);
}

void gripSpeed(int start, int end, int speed)
{
 grip.GenerateVariablePWM(20000, start, end, (abs(start - end) / speed) * 50);
}


//Reset Position (standing up straight)
void reset()
{
 thread t1 (basePos, 135, 100);
 thread t2 (bicepPos, 90, 100);
 thread t3 (elbowPos, 135, 100);
 thread t4 (wristPos, 90, 100);
 thread t5 (gripPos, 180, 100);
 
 t1.join();
 t2.join();
 t3.join();
 t4.join();
 t5.join();
}

void moveArm(int baseDegree)
{
 

 thread t7(bicepSpeed, 90, 50, 20);
 thread t8(elbowPos, 135, 100);
 thread t9(wristPos, 40, 100);
 thread t10(basePos, baseDegree, 100);

 t7.join();
 t8.join();
 t9.join();
 t10.join();
}

void grab() {
  thread t1(bicepPos, 50, 100);
  thread t2(elbowPos, 135, 100);
  thread t3(wristPos, 40, 100);
  thread t4(gripPos, 20, 100);
  
  t1.join();
  t2.join();
  t3.join();
  t4.join();
}

void moveWrist(int baseDegree)
{
 thread t1(basePos, baseDegree, 100);
 thread t2(bicepPos, 50, 100);
 thread t3(elbowPos, 135, 100);
 thread t4(wristSpeed, 70, 100, 90);
 thread t5(gripPos, 20, 100);
 
 t1.join();
 t2.join();
 t3.join();
 t4.join();
 t5.join();
}

void swing()
{
 thread t1(basePos, 30, 100);
 thread t2(bicepPos, 50, 100);
 thread t3(elbowPos, 135, 100);
 thread t4(wristPos, 100, 100);
 thread t5(gripPos, 0, 100);
 
 t1.join();
 t2.join();
 t3.join();
 t4.join();
 t5.join();
}
