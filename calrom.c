#include <stdlib.h>

#include "calrom.h"
#include "dates.h"
#include "temporale.h"

static gboolean is_in_range(const CRCalendar *calendar, const GDate *date);

CRLiturgicalYear calrom_year(const GDate *date)
{
  GDateYear year = g_date_get_year(date);
  GDate first_advent;
  g_date_clear(&first_advent, 1);
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

  temporale_init(&(calendar->temporale), year);
}

int calrom_day(CRDay *day, const GDate *date, const CRCalendar *calendar)
{
  if (!is_in_range(calendar, date)) {
    return CR_ERROR_DATE_OUT_OF_YEAR_RANGE;
  }

  day->date = *date;
  temporale_season(&(day->season_info), date, &(calendar->temporale));

  return CR_SUCCESS;
}

static gboolean is_in_range(const CRCalendar *calendar, const GDate *date)
{
  return
    g_date_compare(date, &(calendar->temporale.first_advent_date)) >= 0 &&
    g_date_compare(date, &(calendar->temporale.last_date)) <= 0;
}
