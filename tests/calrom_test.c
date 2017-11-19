/**
 * Tests of the library's public interface
 */

#include <stdlib.h>

#include "../calrom.h"

static void successful_calrom_day_test(
                                      CRLiturgicalYear liturgical_year,
                                      GDateDay date_day,
                                      GDateMonth date_month,
                                      GDateYear date_year,
                                      CRSeason expected_season,
                                      short expected_week
                                      )
{
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;
  GDate date;

  calrom_build_calendar(&calendar, liturgical_year, &sanctorale);
  g_date_clear(&date, 1);

  g_date_set_dmy(&date, date_day, date_month, date_year);
  int result = calrom_day(&day, &date, &calendar);

  g_assert_cmpint(result, ==, CR_SUCCESS);
  g_assert(day.season_info.season == expected_season);
  g_assert_cmpint(day.season_info.week, ==, expected_week);
}

static void error_calrom_day_test(
                                  CRLiturgicalYear liturgical_year,
                                  GDateDay date_day,
                                  GDateMonth date_month,
                                  GDateYear date_year,
                                  int expected_error_code
                                  )
{
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;
  GDate date;

  calrom_build_calendar(&calendar, liturgical_year, &sanctorale);
  g_date_clear(&date, 1);

  g_date_set_dmy(&date, date_day, date_month, date_year);
  int result = calrom_day(&day, &date, &calendar);

  g_assert_cmpint(result, ==, expected_error_code);
}



void test_day_advent_first_sunday(void)
{
  successful_calrom_day_test(
                            // given
                            2016, 27, 11, 2016,
                            // expected
                            CR_SEASON_ADVENT, 1
                            );
}

void test_day_ordinary_first_ferial(void)
{
  successful_calrom_day_test(
                            // given
                            2016, 9, 1, 2017,
                            // expected
                            CR_SEASON_ORDINARY, 1
                            );
}

void test_day_ordinary_first_saturday(void)
{
  successful_calrom_day_test(
                            // given
                            2016, 14, 1, 2017,
                            // expected
                            CR_SEASON_ORDINARY, 1
                            );
}

void test_day_ordinary_second_sunday(void)
{
  successful_calrom_day_test(
                            // given
                            2016, 15, 1, 2017,
                            // expected
                            CR_SEASON_ORDINARY, 2 // because there is no 1st Sunday in the OT
                            );
}

void test_day_ordinary_second_monday(void)
{
  successful_calrom_day_test(
                            // given
                            2016, 16, 1, 2017,
                            // expected
                            CR_SEASON_ORDINARY, 2
                            );
}

void test_day_ordinary_last_sunday(void)
{
  successful_calrom_day_test(
                            // given
                            2016, 26, 11, 2017,
                            // expected
                            CR_SEASON_ORDINARY, 34
                            );
}

void test_day_ordinary_last_saturday(void)
{
  successful_calrom_day_test(
                            // given
                            2016, 2, 12, 2017,
                            // expected
                            CR_SEASON_ORDINARY, 34
                            );
}

void test_day_date_out_of_range(void)
{
  error_calrom_day_test(
                        // given
                        2017, 1, 1, 2017,
                        // expected
                        CR_ERROR_DATE_OUT_OF_YEAR_RANGE
                        );
}
