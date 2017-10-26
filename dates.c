#include "dates.h"

void date_first_advent(GDate *date, const GDate *nativity)
{
  g_date_set_dmy(
                 date,
                 g_date_get_day(nativity),
                 g_date_get_month(nativity),
                 g_date_get_year(nativity)
                 );
  GDateWeekday nativity_wday = g_date_get_weekday(nativity);

  int sub = 0;
  switch (nativity_wday) {
  case G_DATE_MONDAY:
    sub = 1; break;
  case G_DATE_TUESDAY:
    sub = 2; break;
  case G_DATE_WEDNESDAY:
    sub = 3; break;
  case G_DATE_THURSDAY:
    sub = 4; break;
  case G_DATE_FRIDAY:
    sub = 5; break;
  case G_DATE_SATURDAY:
    sub = 6; break;
  case G_DATE_SUNDAY:
    sub = 7; break;
  }

  g_date_subtract_days(date, 3 * WEEK + sub);
}

void date_first_advent_in_year(GDate *date, CRLiturgicalYear year)
{
  GDate nativity;
  date_nativity(&nativity, year);
  date_first_advent(date, &nativity);
}

void date_nativity(GDate *date, CRLiturgicalYear year)
{
  g_date_set_dmy(date, 25, 12, year);
}
