/**
 * Tests of the library's public interface
 */

#include "../calrom.h"

void test_day_advent_first_sunday(void)
{
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;

  GDate date;
  g_date_clear(&date, 1);
  g_date_set_dmy(&date, 27, 11, 2016);

  calrom_build_calendar(&calendar, 2016, &sanctorale);
  int result = calrom_day(&day, &date, &calendar);

  g_assert_cmpint(result, ==, 0);
}

void test_day_ordinary_before_pentecost(void)
{
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;

  GDate date;
  g_date_clear(&date, 1);
  g_date_set_dmy(&date, 9, 1, 2017);

  calrom_build_calendar(&calendar, 2016, &sanctorale);
  int result = calrom_day(&day, &date, &calendar);

  g_assert_cmpint(result, ==, 0);
}
