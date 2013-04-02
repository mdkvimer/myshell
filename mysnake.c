/*
 * =====================================================================================
 *
 *       Filename:  mysnake.c
 *
 *    Description:  mysnake game  curses.h  node  cc *.c  -o * -lcurses  
 *                  second node second code 
 *        Version:  7.3
 *        Created:  2012年08月19日 12时42分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ACman mdk (Orz), mdk@server.example.com
 *        Company:  ACM 309 JudgeOnline
 *
 * =====================================================================================
 */
#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<signal.h>
#include<sys/time.h>
#define NUM 60
struct direct
{
   int cx;
   int cy;
};
typedef struct node
{
  int cx;
  int cy;
  struct node *next;
  struct node *back;
}node;

void initGame();
int setTicker(int);
void show();
void showInformation();
void showSnake();
void getOrder();
void gameover(int i);

void creatLink();
void insertNode(int x,int y);
void deleteNode();
void deleteLink();

int ch;
int hour,minute,second;
int length, tTime,level;
struct direct dir,food;
node *head,*tail;
int main()
{
  initscr();
  initGame();
  signal(SIGALRM,show);
  getOrder();
  endwin();
  return 0;
}
void initGame()
{
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr,true);
  srand(time(0));
  hour=minute=second=tTime=0;
  length = 1;
  dir.cx = 1;
  dir.cy = 0;
  ch='A';
  food.cx = rand() % (COLS - 1)+1;
  food.cy = rand() % (LINES - 7) + 7;
  creatLink();
  setTicker(20);
}
int setTicker(int n_msecs)
{
   struct itimerval new_timeset;
   long n_sec,n_usecs;

   n_sec = n_msecs/1000;
   n_usecs = (n_msecs % 1000) * 1000L;

   new_timeset.it_interval.tv_sec = n_sec;
   new_timeset.it_interval.tv_usec = n_usecs;
   
   n_msecs = 1;
   n_sec = n_msecs/1000;
   n_usecs = (n_msecs % 1000) * 1000L;

   new_timeset.it_value.tv_sec = n_sec;
   new_timeset.it_value.tv_usec = n_usecs;

   return setitimer(ITIMER_REAL,&new_timeset,NULL);
}
void showInformation()
{
  tTime++;
  if(tTime >= 100000)
	  tTime = 0;
  if(1 != tTime % 50)
	  return;
  move(2,3);

  printw("time %d:%d:%d %c",hour,minute,second);
  second++;
  if(second > NUM)
  {
    second=0;
	minute++;
  }
  if(minute > NUM)
  {
    minute=0;
	hour++;
  }
  move(3,0);
  int i;
  for(i=0;i<COLS;i++)
	  addstr("#");
  move(1,0);
  for(i=0;i<COLS;i++)
	  addstr("#");
  move(2,COLS/2 - 5);
  printw("length : %d",length);
  move(2,COLS - 10);
  level = level/3+1;
  printw("level : %d",level);
  move(4,0);
  addstr("Please enjoy the snake game!!!This game make by mdk change again(come from internet)");
  move(5,0);
  for(i=0;i<COLS;i++)
	  addstr("#");
  move(5,0);
  for(i=5;i<LINES - 1;i++)
  { 
      move(i,0);
	  addstr("#");
  }
  move(LINES-1,0);
  for(i=0;i<COLS;i++)
	  addstr("#");
  move(5,COLS-1);
  for(i=5;i<LINES-1;i++)
  {
    move(i,COLS-1);
	addstr("#");
  }
}
void showSnake()
{
   if(1 != tTime % (30 -level))
	   return;
   bool lenChang=false;
   move(food.cy,food.cx);
   printw("O");
   if((COLS - 2==head->next->cx && 1 == dir.cx)
		   ||(1==head->next->cx && - 1 == dir.cx)
		   ||(LINES - 2==head->next->cy && 1 == dir.cy)
		   ||(5==head->next->cy && - 1 == dir.cy))
   {
      gameover(1);
	  return;
   }
   if('@'==mvinch(head->next->cy+dir.cy,head->next->cx+dir.cx))
   {
      gameover(2);
	  return;
   }
   insertNode(head->next->cx+dir.cx,head->next->cy+dir.cy);
   if(head->next->cx==food.cx&&head->next->cy==food.cy)
   {
	 lenChang=true;
	 length++;
	 if(length >= 50)
	 {
	    gameover(3);
		return;
	 }
	 food.cx=rand()%(COLS - 1)+1;
	 food.cy=rand()%(LINES - 7)+7;
   }
    if(!lenChang)
	{
	    move(tail->back->cy,tail->back->cx);
		printw(" ");
		deleteNode();
	}
	move(head->next->cy,head->next->cx);
	printw("@");
}
void show()
{
    signal(SIGALRM,show);
	showInformation();
	showSnake();
	refresh();
}
void getOrder()
{
   while(1)
   {
      ch = getch();
	  if(KEY_LEFT == ch)
	  {
	      dir.cx = -1;
		  dir.cy = 0;
	  }
	  else if(KEY_RIGHT == ch)
	  {
	      dir.cx = 1;
		  dir.cy = 0;
	  }
	  else if(KEY_UP == ch)
	  {
	     dir.cx = 0;
		 dir.cy = -1;
	  }
	  else if(KEY_DOWN == ch)
	  {
	     dir.cx = 0;
		 dir.cy = 1;
	  }
	  else if(KEY_ENTER == ch)
	  {
	     if(dir.cx<0)
			 dir.cx-=1;
		 else if(dir.cx>0)
			 dir.cx+=1;
		 else if(dir.cy<0)
			 dir.cy-=1;
		 else if(dir.cy>0)
			 dir.cy+=1;
	  }
	  setTicker(20);
   }
}
void gameover(int i)
{
   move(0,0);
   int j;
   for(j=0;j<COLS;j++)
	   addstr("");
   move(0,2);
   if(1 == i)
	   addstr("Crash the wall,Game over!!");
   else if(2 == i)
	   addstr("Crash itself,Game over!!");
   else if(3 == i)
	   addstr("Mission Complete!!");
  setTicker(0);
  deleteLink();
}
void creatLink()
{
  node *temp=(node *)malloc(sizeof(node));
       head = (node *)malloc(sizeof(node));
	   tail = (node *)malloc(sizeof(node));
	temp->cx = 5;
	temp->cy = 10;
	head->back = tail->next = NULL;
	head->next=temp;
	temp->next=tail;
	tail->back=temp;
	temp->back=head;
}
void insertNode(int x,int y)
{
   node *temp = (node *)malloc(sizeof(node));
   temp->cx = x;
   temp->cy = y;
   temp->next=head->next;
   head->next=temp;
   temp->back=head;
   temp->next->back=temp;
}
void deleteNode()
{
   node *temp = tail->back;
   node *bTemp = temp->back;
   bTemp->next = tail;
   tail->back = bTemp;
   temp->next=temp->back=NULL;
   free(temp);
   temp = NULL;
}
void deleteLink()
{
   while(head->next!=tail)
	   deleteNode();
   head->next=tail->back=NULL;
   free(head);
   free(tail);
}
