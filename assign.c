#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUMPA1 10
#define NUMPA2 10
#define NUMEX 3
#define NUMIC 5
//
// WARNING: This program is for reference only. It may contain mistakes.
// Please refer to the syllabus about how grades are calculated
//
/* 
The course grading includes the following items:
* programming assignments 1 to 10, 2 points each
* programming assignments 11 to 20, 5 points each
* the total score of programming assignments is 70. The final score is capped at 60 points.
* exam 1 to 3, 10 points each
* in-class programming assignments 1 to 5, 2 points each
* bonus point, 5 points

Grade |  Total          | Program   |  Exam       | In-class Assignment
           | out of 105  | out of 60   |  out of 30  | out of 10
---------+---------------+--------------+--------------+---------------------------
A         |   90            |    50          |     24         |   6
---------+---------------+--------------+--------------+---------------------------
B         |   85            |    48          |     22         |   4
---------+---------------+--------------+--------------+---------------------------
C         |   80            |    46          |     20         |   4
---------+---------------+--------------+--------------+---------------------------
D         |  75            |     44          |     18         |   3
*/

typedef struct
{
  int total;
  int program;
  int exam;
  int inclass;
  int bonus;
} Grade;

void setgrades(Grade * requirements)
{
  // requirements for A
  requirements[0].total        = 90;
  requirements[0].program = 50;
  requirements[0].exam      = 24;
  requirements[0].inclass    = 6;
  requirements[0].bonus     = 0;
  // requirements for B
  requirements[1].total        = 85;
  requirements[1].program = 48;
  requirements[1].exam      = 22;
  requirements[1].inclass    = 4;
  requirements[1].bonus     = 0;
  // requirements for C
  requirements[2].total        = 80;
  requirements[2].program = 46;
  requirements[2].exam      = 20;
  requirements[2].inclass    = 4;
  requirements[2].bonus     = 0;
  // requirements for D
  requirements[3].total        = 75;
  requirements[3].program = 44;
  requirements[3].exam      = 18;
  requirements[3].inclass    = 3;
  requirements[3].bonus     = 0;
}

void assign(char name, Grade gd, Grade * requirements)
{
  int letter = 0;
  int assigned = 0;
  int cnt = 0;
  printf("in assign\n");
  printf("total = %d\n", gd.total);
  printf("program = %d\n", gd.program);
  printf("exam = %d\n", gd.exam);
  printf("inclass = %d\n", gd.inclass);
  printf("bonus = %d\n", gd.bonus);
  while ((assigned == 0) && (cnt < 4))
    {
      if ((gd.total >= requirements[cnt].total) &&
	  (gd.program >= requirements[cnt].program) &&
	  (gd.exam >= requirements[cnt].exam) &&
	  (gd.inclass >= requirements[cnt].inclass))
	{
	  assigned = 1;
	  letter = cnt;
	}
      cnt ++;
    }
  if (assigned == 0)
    {
      letter = 5; // fail
    }
  printf("name = %c, grade = %c\n\n", name, letter + 'A');
}

int main(int argc, char ** argv)
{
  if (argc < 2)
    {
      return EXIT_FAILURE;
    }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL)
    {
      return EXIT_FAILURE;
    }    
  Grade requirements[4];
  setgrades(requirements);
  /* ignore the first line */
  char line[10000];
  fgets(line, 9999, fptr);
  while (!feof(fptr))
    {
      int name;
      name = fgetc(fptr);
      printf("name = %c\n", name);
      fgetc(fptr); // remove ,
      int program = 0;
      int score = 0;
      for (int cnt = 0; cnt < NUMPA1; cnt ++)
	{
	  fscanf(fptr,"%d,", & score);
	  program += 2 * score;
	  // printf("score = %d, program = %d\n", score, program);
	}
      for (int cnt = 0; cnt < NUMPA2; cnt ++)
	{
	  fscanf(fptr,"%d,", & score);
	  program += 5 * score;
	  // printf("score = %d, program = %d\n", score, program);
	}
      int exam = 0;
      for (int cnt = 0; cnt < NUMEX; cnt ++)
	{
	  fscanf(fptr,"%d,", & score);
	  exam += score;
	  // printf("score = %d, exam = %d\n", score, exam);
	}
      int inclass = 0;
      for (int cnt = 0; cnt < NUMIC; cnt ++)
	{
	  fscanf(fptr,"%d,", & score);
	  inclass += 2 * score;
	  // printf("score = %d, inclass = %d\n", score, inclass);
	}
      int bonus;
      fscanf(fptr,"%d", & bonus);
      fscanf(fptr,"\n");
      printf("program = %d\n", program);
      printf("exam = %d\n", exam);
      printf("inclass = %d\n", inclass);
      printf("bonus = %d\n", bonus);
      Grade gd;
      gd.program = (int) ceil(0.01 * program);
      if (gd.program > 60)
	{
	  gd.program = 60;
	}
      gd.exam = (int) ceil(0.1 * exam);
      gd.inclass = (int) ceil(0.01 * inclass);
      gd.bonus = bonus;
      gd.total = gd.program + gd.exam + gd.inclass + gd.bonus;
      assign(name, gd, requirements);
    }
  return EXIT_SUCCESS;
}
