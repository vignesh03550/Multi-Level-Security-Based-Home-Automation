#define MOTOR_H 1<<12
#define MOTOR_L 1<<13
void motor_init(void)
{
  IODIR0=MOTOR_H|MOTOR_L;
  IOSET0=MOTOR_H|MOTOR_L;
}
void motor_forward(void)
{
  IOCLR0=MOTOR_H;
  IOSET0=MOTOR_L;
}
void motor_backward(void)
{
  IOCLR0=MOTOR_L;
  IOSET0=MOTOR_H;
}
void motor_off(void)
{
  IOSET0=MOTOR_H|MOTOR_L;
}
				  