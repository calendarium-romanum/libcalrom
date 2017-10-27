#include "calrom.h"
#include "dates.h"
#include "temporale.h"

// date comparison shorthands
#define dt_lt(a, b) g_date_compare(a, b) < 0
#define dt_le(a, b) g_date_compare(a, b) <= 0

void temporale_init(CRTemporale *temporale, CRLiturgicalYear year)
{
  // slightly dirty use of pointer arithmetics
  g_date_clear(&(temporale->first_advent_date), sizeof(CRTemporale) / sizeof(GDate));

  date_nativity(&(temporale->nativity_date), year);
  date_first_advent(&(temporale->first_advent_date), &(temporale->nativity_date));
  date_baptism_of_lord(&(temporale->baptism_of_lord_date), year);
  date_easter(&(temporale->easter_date), year);
  date_ash_wednesday(&(temporale->ash_wednesday_date), &(temporale->easter_date));
  date_pentecost(&(temporale->pentecost_date), &(temporale->easter_date));
}

void temporale_season(CRSeasonInfo *season_info, const GDate *date, const CRTemporale *temporale)
{
  // season
  if (dt_lt(date, &(temporale->nativity_date))) {
    season_info->season = CR_SEASON_ADVENT;
  } else if (dt_le(date, &(temporale->baptism_of_lord_date))) {
    season_info->season = CR_SEASON_CHRISTMAS;
  } else if (dt_lt(date, &(temporale->ash_wednesday_date))) {
    season_info->season = CR_SEASON_ORDINARY;
  } else if (dt_lt(date, &(temporale->easter_date))) {
    season_info->season = CR_SEASON_LENT;
  } else if (dt_le(date, &(temporale->pentecost_date))) {
    season_info->season = CR_SEASON_EASTER;
  } else {
    season_info->season = CR_SEASON_ORDINARY;
  }

  // season week
  season_info->week = 0;

  GDate week1_beginning;
  g_date_clear(&week1_beginning, 1);

  switch (season_info->season) {
  case CR_SEASON_ADVENT:
    week1_beginning = temporale->first_advent_date;
    break;
  case CR_SEASON_CHRISTMAS:
    week1_beginning = temporale->nativity_date;
    break;
  case CR_SEASON_LENT:
    week1_beginning = temporale->ash_wednesday_date;
    break;
  case CR_SEASON_EASTER:
    week1_beginning = temporale->easter_date;
    break;
  default: // Ordinary Time
    week1_beginning = temporale->baptism_of_lord_date;
    g_date_add_days(&week1_beginning, 1);
    break;
  }

  GDateWeekday week1_weekday = g_date_get_weekday(&week1_beginning);

  if (week1_weekday != G_DATE_SUNDAY) {
    date_following_sunday(&week1_beginning);
  }

  if (dt_lt(date, &week1_beginning)) {
    season_info->week = 0;
  } else {
    season_info->week = g_date_days_between(&week1_beginning, date) / WEEK + 1;
  }

  if (season_info->season == CR_SEASON_ORDINARY) {
    // Ordinary Time's first Sunday is 2nd
    season_info->week++;

    if (dt_lt(&(temporale->pentecost_date), date)) {
      GDate next_first_advent;
      g_date_clear(&next_first_advent, 1);
      date_first_advent_in_year(&next_first_advent, g_date_get_year(date));

      int weeks_after_date = g_date_days_between(date, &next_first_advent) / WEEK;
      const int OT_WEEKS_TOTAL = 34;
      season_info->week = OT_WEEKS_TOTAL - weeks_after_date;

      GDateWeekday date_weekday = g_date_get_weekday(date);
      if (date_weekday == G_DATE_SUNDAY) {
        season_info->week++;
      }
    }
  }
}
