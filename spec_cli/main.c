#define _XOPEN_SOURCE

#include <glib.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>

#include "../calrom.h"

void print_day_json(CRDay *day)
{
  char output_date[11];
  g_date_strftime(output_date, 11, "%Y-%m-%d", &(day->date));

  char *season;
  season = "unknown";
  switch (day->season_info.season) {
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

  printf("{\"date\": \"%s\", \"season\": \"%s\", \"season_week\": \"%i\", \"celebrations\": []}", output_date, season, day->season_info.week);
}

int main(int argc, char *argv[])
{
  struct tm input_time;
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;

  if (argc < 2) {
    fprintf(stderr, "Date required as command line argument.\n");
    return 1;
  }
  strptime(argv[1], "%Y-%m-%d", &input_time);

  GDate *date = g_date_new_dmy(
                               input_time.tm_mday,
                               input_time.tm_mon + 1,
                               input_time.tm_year + 1900
                               );
  CRLiturgicalYear year = calrom_year(date);

  calrom_build_calendar(&calendar, year, &sanctorale);
  int result = calrom_day(&day, date, &calendar);
  g_date_free(date);

  if (result < 0) {
    fprintf(stderr, "Error when resolving liturgical day.");
    return 1;
  }

  print_day_json(&day);
  printf("\n");

  return 0;
}
