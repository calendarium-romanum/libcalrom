#include <stdlib.h>

#include "calrom.h"
#include "dates.h"

CRLiturgicalYear calrom_year(const GDate *date)
{
  GDateYear year = g_date_get_year(date);
  GDate first_advent;
  date_first_advent_in_year(&first_advent, year);

  CRLiturgicalYear result = year;
  if (g_date_compare(date, &first_advent) < 0) {
    result = year - 1;
  }

  return result;
}

void calrom_build_calendar(CRCalendar *calendar, CRLiturgicalYear year, const CRSanctorale *sanctorale)
{
  calendar->year = year;
}

int calrom_day(CRDay *day, const GDate *date, const CRCalendar *calendar)
{
  // fake
  day->season_info.season = CR_SEASON_ORDINARY;
  day->season_info.week = 0;

  return 0;
}
