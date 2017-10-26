#include "dates.h"

void date_first_advent(GDate *date, const GDate *nativity)
{
  *date = *nativity;
  GDateWeekday nativity_wday = g_date_get_weekday(nativity);

  // Sunday before
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
  g_date_clear(&nativity, 1);
  date_nativity(&nativity, year);
  date_first_advent(date, &nativity);
}

void date_nativity(GDate *date, CRLiturgicalYear year)
{
  g_date_set_dmy(date, 25, 12, year);
}

void date_baptism_of_lord(GDate *date, CRLiturgicalYear year)
{
  g_date_set_dmy(date, 6, 1, year + 1);
  GDateWeekday epiphany_wday = g_date_get_weekday(date);

  // Sunday before
  int add = 0;
  switch (epiphany_wday) {
    // this is a special case:
    // Epiphany on Sunday -> Baptism of the Lord is not on the next
    // Sunday, but on the Monday immediately following
  case G_DATE_SUNDAY:
    add = 1; break;

  case G_DATE_MONDAY:
    add = 6; break;
  case G_DATE_TUESDAY:
    add = 5; break;
  case G_DATE_WEDNESDAY:
    add = 4; break;
  case G_DATE_THURSDAY:
    add = 3; break;
  case G_DATE_FRIDAY:
    add = 2; break;
  case G_DATE_SATURDAY:
    add = 1; break;
  }

  g_date_add_days(date, add);
}

void date_ash_wednesday(GDate *date, const GDate *easter)
{
  *date = *easter;
  g_date_subtract_days(date, 6 * WEEK + 4);
}

void date_easter(GDate *date, CRLiturgicalYear year)
{
  GDateYear cyear = year + 1; // civil year

  // algorithm below ported from the 'easter' Ruby gem:
  // https://github.com/jrobertson/easter

  int golden_number = (cyear % 19) + 1;
  int dominical_number = (cyear + (cyear / 4) - (cyear / 100) + (cyear / 400)) % 7;
  int solar_correction = (cyear - 1600) / 100 - (cyear - 1600) / 400;
  int lunar_correction = (((cyear - 1400) / 100) * 8) / 25;
  int paschal_full_moon = (3 - 11 * golden_number + solar_correction - lunar_correction) % 30;

  do {
    dominical_number += 7;
  } while (dominical_number <= 0);

  do {
    paschal_full_moon += 30;
  } while (paschal_full_moon <= 0);

  if ((paschal_full_moon == 29) || ((paschal_full_moon == 28) && golden_number > 11)) {
    paschal_full_moon -= 1;
  }

  int difference = (4 - paschal_full_moon - dominical_number) % 7;
  if (difference < 0) {
    difference += 7;
  }

  int day_easter = paschal_full_moon + difference + 1;
  if (day_easter < 11) {
    // Easter occurs in March.
    g_date_set_dmy(date, day_easter + 21, 3, cyear);
  } else {
    // Easter occurs in April.
    g_date_set_dmy(date, day_easter - 10, 4, cyear);
  }
}

void date_pentecost(GDate *date, const GDate *easter)
{
  *date = *easter;
  g_date_add_days(date, 7 * WEEK);
}
