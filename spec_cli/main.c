#define _XOPEN_SOURCE

#include <glib.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>

#include "../calrom.h"

int main(int argc, char *argv[])
{
  struct tm input_time;
  char output_date[11];
  char *season;
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;

  if (argc < 2) {
    fprintf(stderr, "Date required as command line argument.\n");
    return 1;
  }
  strptime(argv[1], "%Y-%m-%d", &input_time);

  strftime(output_date, 11, "%Y-%m-%d", &input_time);

  GDate *date = g_date_new_dmy(
                               input_time.tm_mday,
                               input_time.tm_mon + 1,
                               input_time.tm_year + 1900
                               );
  CRLiturgicalYear year = calrom_year(date);
  free(date);

  calrom_build_calendar(&calendar, year, &sanctorale);
  int result = calrom_day(&day, &calendar);
  if (result < 0) {
    fprintf(stderr, "Error when resolving liturgical day.");
    return 1;
  }

  season = "unknown";
  switch (day.season_info.season) {
  case CR_SEASON_ADVENT:
    season = "advent"; break;
  case CR_SEASON_CHRISTMAS:
    season = "christmas"; break;
  case CR_SEASON_LENT:
    season = "lent"; break;
  case CR_SEASON_EASTER:
    season = "easter"; break;
  case CR_SEASON_ORDINARY:
    season = "ordinary"; break;
  }

  printf("{\"date\": \"%s\", \"season\": \"%s\", \"season_week\": \"\", \"celebrations\": []}", output_date, season);
  printf("\n");

  return 0;
}
