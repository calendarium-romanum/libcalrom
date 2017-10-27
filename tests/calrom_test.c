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
  g_assert(day.season_info.season == CR_SEASON_ADVENT);
  g_assert_cmpint(day.season_info.week, ==, 1);
}

void test_day_ordinary_first_ferial(void)
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
  g_assert(day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(day.season_info.week, ==, 1);
}

void test_day_ordinary_first_saturday(void)
{
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;

  GDate date;
  g_date_clear(&date, 1);
  g_date_set_dmy(&date, 14, 1, 2017);

  calrom_build_calendar(&calendar, 2016, &sanctorale);
  int result = calrom_day(&day, &date, &calendar);

  g_assert_cmpint(result, ==, 0);
  g_assert(day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(day.season_info.week, ==, 1);
}

void test_day_ordinary_second_sunday(void)
{
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;

  GDate date;
  g_date_clear(&date, 1);
  g_date_set_dmy(&date, 15, 1, 2017);

  calrom_build_calendar(&calendar, 2016, &sanctorale);
  int result = calrom_day(&day, &date, &calendar);

  g_assert_cmpint(result, ==, 0);
  g_assert(day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(day.season_info.week, ==, 2); // because there is no 1st Sunday in the OT
}

void test_day_ordinary_second_monday(void)
{
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;

  GDate date;
  g_date_clear(&date, 1);
  g_date_set_dmy(&date, 16, 1, 2017);

  calrom_build_calendar(&calendar, 2016, &sanctorale);
  int result = calrom_day(&day, &date, &calendar);

  g_assert_cmpint(result, ==, 0);
  g_assert(day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(day.season_info.week, ==, 2);
}

void test_day_ordinary_last_sunday(void)
{
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;

  GDate date;
  g_date_clear(&date, 1);
  g_date_set_dmy(&date, 26, 11, 2017);

  calrom_build_calendar(&calendar, 2016, &sanctorale);
  int result = calrom_day(&day, &date, &calendar);

  g_assert_cmpint(result, ==, 0);
  g_assert(day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(day.season_info.week, ==, 34);
}

void test_day_ordinary_last_saturday(void)
{
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;

  GDate date;
  g_date_clear(&date, 1);
  g_date_set_dmy(&date, 2, 12, 2017);

  calrom_build_calendar(&calendar, 2016, &sanctorale);
  int result = calrom_day(&day, &date, &calendar);

  g_assert_cmpint(result, ==, 0);
  g_assert(day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(day.season_info.week, ==, 34);
}
