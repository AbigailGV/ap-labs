#include <stdio.h>
#include <stdlib.h>

/* Month name method */
char *month_name(int n){
  static char *name[] = {
    "Month not available", "Jan", "Feb", "Mar",
    "Apr", "May", "Jun", "Jul", "Aug",
    "Sep", "Oct", "Nov", "Dec"
  };
/* An if */
  return (n < 1 || n > 12) ? name[0]: name[n];
}

static int daytable[2][13] /*rows and columns */ = {
  {0,31,28,31,30,31,30,31,31,30,31,30,31},
  {0,31,29,31,30,31,30,31,31,30,31,30,31}
};
/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday){

  int leap = year%100 != 0 && year%4 == 0|| year%400 == 0;
  *pmonth += 1;

  while (yearday >= daytable[0][*pmonth] && *pmonth < 12){
    pday = &daytable[leap][*pmonth];
    yearday -= *pday;
    /* pointer */
    *pmonth += 1;
  }
  /* validate that the day exists */
  if ( yearday > daytable[leap][*pmonth] || *pmonth > 12 || *pmonth < 1){
    printf("Error: The value was too large for being a day!\n");
    return;
  }
  
  char *monthToChar = month_name(*pmonth);
  printf("%s %d, %d\n", monthToChar, yearday, year);
}


int main(int argc, char const *argv[])
{
  int pmonth = 0;
  int pday = 0;

  if (argc < 3){
    printf("Error: You need more arguments!\n");
    return 1;
  }

  int year = atoi(argv[1]);
  int day = atoi(argv[2]);

  month_day(year,day, &pmonth, &pday);
  return 0;
}