/**
 * Tests of the library's public interface
 */

#include <stdlib.h>

#include "../calrom.h"

typedef struct {
  CRCalendar calendar;
  CRSanctorale sanctorale;
  CRDay day;
  GDate date;
} CalRomTestFixture;

static CalRomTestFixture* build_fixture(CRLiturgicalYear year)
{
  // allocate
  CalRomTestFixture *fixture = malloc(sizeof(CalRomTestFixture));
  // initialize
  calrom_build_calendar(&(fixture->calendar), year, &(fixture->sanctorale));
  g_date_clear(&(fixture->date), 1);

  return fixture;
}

static void free_fixture(CalRomTestFixture *fixture)
{
  free(fixture);
}



void test_day_advent_first_sunday(void)
{
  CalRomTestFixture *fixture = build_fixture(2016);

  g_date_set_dmy(&(fixture->date), 27, 11, 2016);
  int result = calrom_day(&(fixture->day), &(fixture->date), &(fixture->calendar));

  g_assert_cmpint(result, ==, 0);
  g_assert(fixture->day.season_info.season == CR_SEASON_ADVENT);
  g_assert_cmpint(fixture->day.season_info.week, ==, 1);

  free_fixture(fixture);
}

void test_day_ordinary_first_ferial(void)
{
  CalRomTestFixture *fixture = build_fixture(2016);

  g_date_set_dmy(&(fixture->date), 9, 1, 2017);
  int result = calrom_day(&(fixture->day), &(fixture->date), &(fixture->calendar));

  g_assert_cmpint(result, ==, 0);
  g_assert(fixture->day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(fixture->day.season_info.week, ==, 1);

  free_fixture(fixture);
}

void test_day_ordinary_first_saturday(void)
{
  CalRomTestFixture *fixture = build_fixture(2016);

  g_date_set_dmy(&(fixture->date), 14, 1, 2017);
  int result = calrom_day(&(fixture->day), &(fixture->date), &(fixture->calendar));

  g_assert_cmpint(result, ==, 0);
  g_assert(fixture->day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(fixture->day.season_info.week, ==, 1);

  free_fixture(fixture);
}

void test_day_ordinary_second_sunday(void)
{
  CalRomTestFixture *fixture = build_fixture(2016);

  g_date_set_dmy(&(fixture->date), 15, 1, 2017);
  int result = calrom_day(&(fixture->day), &(fixture->date), &(fixture->calendar));

  g_assert_cmpint(result, ==, 0);
  g_assert(fixture->day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(fixture->day.season_info.week, ==, 2); // because there is no 1st Sunday in the OT

  free_fixture(fixture);
}

void test_day_ordinary_second_monday(void)
{
  CalRomTestFixture *fixture = build_fixture(2016);

  g_date_set_dmy(&(fixture->date), 16, 1, 2017);
  int result = calrom_day(&(fixture->day), &(fixture->date), &(fixture->calendar));

  g_assert_cmpint(result, ==, 0);
  g_assert(fixture->day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(fixture->day.season_info.week, ==, 2);

  free_fixture(fixture);
}

void test_day_ordinary_last_sunday(void)
{
  CalRomTestFixture *fixture = build_fixture(2016);

  g_date_set_dmy(&(fixture->date), 26, 11, 2017);
  int result = calrom_day(&(fixture->day), &(fixture->date), &(fixture->calendar));

  g_assert_cmpint(result, ==, 0);
  g_assert(fixture->day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(fixture->day.season_info.week, ==, 34);

  free_fixture(fixture);
}

void test_day_ordinary_last_saturday(void)
{
  CalRomTestFixture *fixture = build_fixture(2016);

  g_date_set_dmy(&(fixture->date), 2, 12, 2017);
  int result = calrom_day(&(fixture->day), &(fixture->date), &(fixture->calendar));

  g_assert_cmpint(result, ==, 0);
  g_assert(fixture->day.season_info.season == CR_SEASON_ORDINARY);
  g_assert_cmpint(fixture->day.season_info.week, ==, 34);

  free_fixture(fixture);
}
